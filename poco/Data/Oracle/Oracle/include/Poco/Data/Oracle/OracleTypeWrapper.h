#pragma once
#include <Poco\Format.h>
#include <Poco\Data\BLOB.h>
#include <ocilib.h>

namespace Poco{
namespace Data{
namespace Oracle{

class COCITypeWrapper
{
public:
	COCITypeWrapper(OCI_Statement* stmt):_stmt(stmt),_isCreate(false){}
	virtual ~COCITypeWrapper(){free();}

	virtual void create(DWORD subtype)=0;
	virtual void free(){}

	virtual void get(int pos)=0;
	virtual void bind(int pos)=0;

protected:
	OCI_Statement* _stmt;
	bool _isCreate;
};

class COCIBlob:public COCITypeWrapper
{
public:
	COCIBlob(OCI_Statement* stmt):COCITypeWrapper(stmt){}

	virtual void read(BLOB &blob)=0;
	virtual void write(const BLOB &blob)=0;
};

class COCILong:public COCIBlob
{
public:
	//初始化需要长度
	COCILong(OCI_Statement* stmt,BLOB* blob=NULL):COCIBlob(stmt),_blob(blob){}
	void create(DWORD subtype)
	{
		_long=OCI_LongCreate(_stmt,subtype);
		_isCreate=true;
	}
	void free()
	{
		if(_isCreate)
		{
			OCI_LongFree(_long);
		}
		_long=NULL;
	}
	void get(int pos)
	{
		OCI_Resultset *res=OCI_GetResultset(_stmt);
		poco_assert(res);

		_long=OCI_GetLong(res,pos+1);
	}
	void read(BLOB &blob)
	{
		blob.assignRaw(reinterpret_cast<const char *>(OCI_LongGetBuffer(_long)),OCI_LongGetSize(_long));
	}
	void write()
	{
		OCI_LongWrite(_long,const_cast<char*>(_blob->rawContent()),_blob->size());
	}
	void write(const BLOB &blob)
	{
		OCI_LongWrite(_long,const_cast<char*>(blob.rawContent()),blob.size());
	}
	void bind(int pos)
	{
		OCI_BindLong(_stmt,format(":%d",pos+1).c_str(),_long,_blob->size());
	}

protected:
	
	BLOB *_blob;
	OCI_Long* _long;
};

class COCILob:public COCIBlob
{
public:
	COCILob(OCI_Statement* stmt):COCIBlob(stmt){}
	void create(DWORD subtype)
	{
		_lob=OCI_LobCreate(OCI_StatementGetConnection(_stmt),subtype);
		_isCreate=true;
	}
	void free()
	{
		if(_isCreate)
		{
			OCI_LobFree(_lob);
		}
		_lob=NULL;
	}
	void get(int pos)
	{
		OCI_Resultset *res=OCI_GetResultset(_stmt);
		poco_assert(res);

		_lob=OCI_GetLob(res,pos+1);
	}
	void read(BLOB &blob)
	{
		int size=static_cast<int>(OCI_LobGetLength(_lob));
		blob.resize(size);

		OCI_LobRead(_lob,const_cast<char*>(blob.rawContent()),size);
	}
	void write(const BLOB &blob)
	{
		OCI_LobWrite(_lob,const_cast<char*>(blob.rawContent()),blob.size());
	}
	void bind(int pos)
	{
		OCI_BindLob(_stmt,format(":%d",pos+1).c_str(),_lob);
	}

protected:

	OCI_Lob* _lob;
};

class COCIDateTime:public COCITypeWrapper
{
public:
	COCIDateTime(OCI_Statement* stmt):COCITypeWrapper(stmt){}
	virtual void read(DateTime &date)=0;
	virtual void write(const DateTime &date)=0;
};

class COCIDate:public COCIDateTime
{
public:
	COCIDate(OCI_Statement* stmt):COCIDateTime(stmt){}
	void create(DWORD)
	{
		_date=OCI_DateCreate(OCI_StatementGetConnection(_stmt));
		_isCreate=true;
	}
	void free()
	{
		if(_isCreate)
		{
			OCI_DateFree(_date);
		}
		_date=NULL;
	}

	void get(int pos)
	{
		OCI_Resultset *res=OCI_GetResultset(_stmt);
		poco_assert(res);

		_date=OCI_GetDate(res,pos+1);
	}
	void read(DateTime &date)
	{
		int year,month,day,hour,min,sec;

		OCI_DateGetDateTime(_date,&year,&month,&day,&hour,&min,&sec);
		date.assign(year,month,day,hour,min,sec);
	}
	void write(const DateTime &date)
	{
		int year=date.year(),
			month=date.month(),
			day=date.day(),
			hour=date.hour(),
			min=date.minute(),
			sec=date.second();

		OCI_DateSetDateTime(_date,year,month,day,hour,min,sec);
	}
	void bind(int pos)
	{
		OCI_BindDate(_stmt,format(":%d",pos+1).c_str(),_date);
	}
protected:
	OCI_Date* _date;
};

class COCITimestamp:public COCIDateTime
{
public:
	COCITimestamp(OCI_Statement* stmt):COCIDateTime(stmt){}
	void create(DWORD subtype)
	{
		_timestamp=OCI_TimestampCreate(OCI_StatementGetConnection(_stmt),subtype);
		_isCreate=true;
	}
	void free()
	{
		if(_isCreate)
		{
			OCI_TimestampFree(_timestamp);
		}
		_timestamp=NULL;
	}
	void get(int pos)
	{
		OCI_Resultset *res=OCI_GetResultset(_stmt);
		poco_assert(res);

		_timestamp=OCI_GetTimestamp(res,pos+1);
	}
	void read(DateTime &date)
	{
		int year,month,day,hour,min,sec,fsec;

		OCI_TimestampGetDateTime(_timestamp,&year,&month,&day,&hour,&min,&sec,&fsec);
		date.assign(year,month,day,hour,min,sec);
	}
	void write(const DateTime &date)
	{
		int year=date.year(),
			month=date.month(),
			day=date.day(),
			hour=date.hour(),
			min=date.minute(),
			sec=date.second(),
			fsec=0;

		OCI_TimestampConstruct(_timestamp,year,month,day,hour,min,sec,fsec,NULL);
	}
	void bind(int pos)
	{
		OCI_BindTimestamp(_stmt,format(":%d",pos+1).c_str(),_timestamp);
	}

protected:
	OCI_Timestamp* _timestamp;
};

class COCIInterval:public COCIDateTime
{
public:
	COCIInterval(OCI_Statement* stmt):COCIDateTime(stmt){}
	void create(DWORD subtype)
	{
		_interval=OCI_IntervalCreate(OCI_StatementGetConnection(_stmt),subtype);
		_isCreate=true;
	}
	void free()
	{
		if(_isCreate)
		{
			OCI_IntervalFree(_interval);
		}
		_interval=NULL;
	}
	void get(int pos)
	{
		OCI_Resultset *res=OCI_GetResultset(_stmt);
		poco_assert(res);

		_interval=OCI_GetInterval(res,pos+1);
	}
	void read(DateTime &date)
	{
		int year=0,month=0,day=0,hour=0,min=0,sec=0,fsec=0;

		OCI_IntervalGetYearMonth(_interval,&year,&month);
		OCI_IntervalGetDaySecond(_interval,&day,&hour,&min,&sec,&fsec);
		
		date.assign(year,month?month:1,day?day:1,hour,min,sec);
	}
	void write(const DateTime &date)
	{
		int year=date.year(),
			month=date.month(),
			day=date.day(),
			hour=date.hour(),
			min=date.minute(),
			sec=date.second(),
			fsec=0;

		OCI_IntervalSetYearMonth(_interval,year,month);
		OCI_IntervalSetDaySecond(_interval,day,hour,min,sec,fsec);
	}
	void bind(int pos)
	{
		OCI_BindInterval(_stmt,format(":%d",pos+1).c_str(),_interval);
	}

protected:
	OCI_Interval* _interval;
};
}}}