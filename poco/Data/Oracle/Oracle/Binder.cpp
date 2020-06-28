#include "Poco/Data/Oracle/Binder.h"
#include "Poco/Data/Oracle/OracleException.h"

namespace Poco{
namespace Data{
namespace Oracle{

Binder::Binder(OCI_Statement* stmt):
	_stmt(stmt)
{
}

void Binder::bind(std::size_t pos, const Poco::Int16& val)
{
	OCI_BindShort(_stmt,format(":%u",pos+1).c_str(),const_cast<short*>(&val));
}
/// Binds an Int16.

void Binder::bind(std::size_t pos, const Poco::UInt16& val)
{
	OCI_BindUnsignedShort(_stmt,format(":%u",pos+1).c_str(),const_cast<WORD*>(&val));
}
/// Binds an UInt16.

void Binder::bind(std::size_t pos, const Poco::Int32& val)
{
	OCI_BindInt(_stmt,format(":%u",pos+1).c_str(),const_cast<int*>(&val));
}
/// Binds an Int32.

void Binder::bind(std::size_t pos, const Poco::UInt32& val)
{
	OCI_BindUnsignedInt(_stmt,format(":%u",pos+1).c_str(),const_cast<unsigned int*>(&val));
}
/// Binds an UInt32.

void Binder::bind(std::size_t pos, const Poco::Int64& val)
{
	OCI_BindBigInt(_stmt,format(":%u",pos+1).c_str(),const_cast<big_int*>(&val));
}
/// Binds an Int64.

void Binder::bind(std::size_t pos, const Poco::UInt64& val)
{
	OCI_BindUnsignedBigInt(_stmt,format(":%u",pos+1).c_str(),const_cast<big_uint*>(&val));
}
/// Binds an UInt64.

void Binder::bind(std::size_t pos, const double& val)
{
	OCI_BindDouble(_stmt,format(":%u",pos+1).c_str(),const_cast<double*>(&val));
}
/// Binds a double.

void Binder::bind(std::size_t pos, const char* const& pVal)
{
	OCI_BindString(_stmt,format(":%u",pos+1).c_str(),const_cast<char*>(pVal),0);
}
/// Binds a const char ptr.

void Binder::bind(std::size_t pos, const std::string& val)
{
	OCI_BindString(_stmt,format(":%u",pos+1).c_str(),const_cast<char*>(val.c_str()),0);
}
/// Binds a string.
void Binder::bind(std::size_t pos)
{
	OCI_BindSetNull(OCI_GetBind2(_stmt,format(":%u",pos+1).c_str()));
}

void Binder::bind(std::size_t pos,const OracleBindHelpper & val)
{
	switch(val._type)
	{
	case ORACLE_BLONG:
	case ORACLE_CLONG:
		{
			COCILong *blob=new COCILong(_stmt,reinterpret_cast<BLOB*>(val._data));
			blob->create(val._type+1);
			blob->bind(pos);
			_bindlong.push_back(blob);
		}
		break;
	case ORACLE_BLOB:
	case ORACLE_CLOB:
	case ORACLE_NCLOB:
		{
			COCIBlob *blob=new COCILob(_stmt);
			blob->create(val._type-1);
			blob->write(*reinterpret_cast<BLOB*>(val._data));
			blob->bind(pos);
			_bindtmp[pos]=blob;
		}	
		break;
	case ORACLE_INTERVAL_YM:
	case ORACLE_INTERVAL_DS:
		{
			COCIDateTime *date=new COCIInterval(_stmt);
			date->create(val._type-4);
			date->write(*reinterpret_cast<DateTime*>(val._data));
			date->bind(pos);
			_bindtmp[pos]=date;
		}
	}
}
void Binder::bind(std::size_t pos, const BLOB& val)
{
	//不能Bind:CLOB
	
//   	COCILong *blob=new COCILong(_stmt,const_cast<BLOB*>(&val));
//   	blob->create(OCI_BLONG);
//   	blob->bind(pos);
//   	_bindlong.push_back(blob);

	OCI_BindRaw(_stmt,format(":%u",pos+1).c_str(),const_cast<char*>(val.rawContent()),val.size());
	//OCI_Bind* bind=OCI_GetBind2(_stmt,format(":%u",pos+1).c_str());
	
	//DWORD ocitype=OCI_BindGetType(bind);

// 	switch(ocitype)
// 	{
// 	case OCI_CDT_LONG:
// 	case OCI_CDT_LOB:
// 		{
// 			COCIBlob *blob=NULL;
// 			if(ocitype==OCI_CDT_LONG)
// 				blob=new COCILob(_stmt);
// 			else
// 				blob=new COCILong(_stmt);
// 
// 			blob->create(OCI_BindGetSubtype(bind));
// 			blob->write(val);
// 			blob->bind(pos);
// 			_bindtmp[pos]=blob;
// 		}
// 		break;
// 	case OCI_CDT_RAW:
// 		OCI_BindRaw(_stmt,format(":%u",pos+1).c_str(),const_cast<char*>(val.rawContent()),val.size());
// 		break;
// 	default:
// 		throw OracleException("Bind: Can't bind Blob to this pos.");
// 	}
}
/// Binds a BLOB.

void Binder::bind(std::size_t pos, const DateTime& val)
{
	//不能Bind:INTERVAL

	COCIDateTime *date=new COCIDate(_stmt);
	date->create(0);
	date->write(val);
	date->bind(pos);
	_bindtmp[pos]=date;

// 	OCI_Bind* bind=OCI_GetBind2(_stmt,format(":%u",pos+1).c_str());
// 
// 	DWORD ocitype=OCI_BindGetType(bind);
// 	switch(ocitype)
// 	{
// 	case OCI_CDT_DATETIME:
// 	case OCI_CDT_TIMESTAMP:
// 	case OCI_CDT_INTERVAL:
// 		{
// 			COCIDateTime *date=NULL;
// 			if(ocitype==OCI_CDT_DATETIME)
// 				date=new COCIDate(_stmt);
// 			else if(ocitype==OCI_CDT_TIMESTAMP)
// 				date=new COCITimestamp(_stmt);
// 			else
// 				date=new COCIInterval(_stmt);
// 			date->create(OCI_BindGetSubtype(bind));
// 			date->write(val);
// 			date->bind(pos);
// 			_bindtmp[pos]=date;
// 		}
// 		break;
// 	default:
// 		throw OracleException("Bind: Can't bind DateTime to this pos.");
// 	}
}

}}}