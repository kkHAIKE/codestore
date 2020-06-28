#include "Poco/Data/Oracle/Extractor.h"
#include "Poco/Data/Oracle/OracleException.h"

namespace Poco{
namespace Data{
namespace Oracle{

Extractor::Extractor(OCI_Statement* stmt,std::vector<SharedPtr<OracleColumn>> &meta):
	_stmt(stmt)
	,_meta(meta)
{
}

bool Extractor::extract(std::size_t pos, Poco::Int8& val)
{
	OCI_Resultset *_res=OCI_GetResultset(_stmt);
	poco_assert(_res);

	val=static_cast<char>(OCI_GetShort(_res,pos+1));
	return true;
}
/// Extracts an Int8. Returns false if null was received.

bool Extractor::extract(std::size_t pos, Poco::UInt8& val)
{
	OCI_Resultset *_res=OCI_GetResultset(_stmt);
	poco_assert(_res);

	val=LOBYTE(OCI_GetUnsignedShort(_res,pos+1));
	return true;
}
/// Extracts an UInt8. Returns false if null was received.

bool Extractor::extract(std::size_t pos, Poco::Int16& val)
{
	OCI_Resultset *_res=OCI_GetResultset(_stmt);
	poco_assert(_res);

	val=OCI_GetShort(_res,pos+1);
	return true;
}
/// Extracts an Int16. Returns false if null was received.

bool Extractor::extract(std::size_t pos, Poco::UInt16& val)
{
	OCI_Resultset *_res=OCI_GetResultset(_stmt);
	poco_assert(_res);

	val=OCI_GetUnsignedShort(_res,pos+1);
	return true;
}
/// Extracts an UInt16. Returns false if null was received.

bool Extractor::extract(std::size_t pos, Poco::Int32& val)
{
	OCI_Resultset *_res=OCI_GetResultset(_stmt);
	poco_assert(_res);

	val=OCI_GetInt(_res,pos+1);
	return true;
}
/// Extracts an Int32. Returns false if null was received.

bool Extractor::extract(std::size_t pos, Poco::UInt32& val)
{
	OCI_Resultset *_res=OCI_GetResultset(_stmt);
	poco_assert(_res);

	val=OCI_GetUnsignedInt(_res,pos+1);
	return true;
}
/// Extracts an UInt32. Returns false if null was received.

bool Extractor::extract(std::size_t pos, Poco::Int64& val)
{
	OCI_Resultset *_res=OCI_GetResultset(_stmt);
	poco_assert(_res);

	val=OCI_GetBigInt(_res,pos+1);
	return true;
}
/// Extracts an Int64. Returns false if null was received.

bool Extractor::extract(std::size_t pos, Poco::UInt64& val)
{
	OCI_Resultset *_res=OCI_GetResultset(_stmt);
	poco_assert(_res);

	val=OCI_GetUnsignedBigInt(_res,pos+1);
	return true;
}
/// Extracts an UInt64. Returns false if null was received.

bool Extractor::extract(std::size_t pos, bool& val)
{
	OCI_Resultset *_res=OCI_GetResultset(_stmt);
	poco_assert(_res);

	val=(OCI_GetShort(_res,pos+1)==1);
	return true;
}
/// Extracts a boolean. Returns false if null was received.

bool Extractor::extract(std::size_t pos, float& val)
{
	OCI_Resultset *_res=OCI_GetResultset(_stmt);
	poco_assert(_res);

	val=static_cast<float>(OCI_GetDouble(_res,pos+1));
	return true;
}
/// Extracts a float. Returns false if null was received.

bool Extractor::extract(std::size_t pos, double& val)
{
	OCI_Resultset *_res=OCI_GetResultset(_stmt);
	poco_assert(_res);

	val=OCI_GetDouble(_res,pos+1);
	return true;
}
/// Extracts a double. Returns false if null was received.

bool Extractor::extract(std::size_t pos, char& val)
{
	OCI_Resultset *_res=OCI_GetResultset(_stmt);
	poco_assert(_res);

	val=static_cast<char>(OCI_GetShort(_res,pos+1));
	return true;
}
/// Extracts a single character. Returns false if null was received.

bool Extractor::extract(std::size_t pos, std::string& val)
{
	OCI_Resultset *_res=OCI_GetResultset(_stmt);
	poco_assert(_res);

	val=OCI_GetString(_res,pos+1);
	return true;
}
/// Extracts a string. Returns false if null was received.

bool Extractor::extract(std::size_t pos, BLOB& val)
{
	poco_assert(pos>=0 && pos<_meta.size());

	OCI_Resultset *_res=OCI_GetResultset(_stmt);
	poco_assert(_res);

	DWORD ocitype=_meta[pos]->GetOCIType();

	switch(ocitype)
	{
	case OCI_CDT_LONG:
	case OCI_CDT_LOB:
		{
			COCIBlob *blob=NULL;
			if(ocitype==OCI_CDT_LONG)
				blob=new COCILong(_stmt);
			else
				blob=new COCILob(_stmt);

			blob->get(pos);
			blob->read(val);
		}
		break;
	case OCI_CDT_RAW:
		{
			DWORD size=OCI_GetDataLength(_res,pos);
			val.resize(size);
			OCI_GetRaw(_res,pos,const_cast<char*>(val.rawContent()),size);
		}
		break;
	default:
		throw OracleException("Extract: Can't extract Blob from this pos.");
	}
	return true;
}
/// Extracts a BLOB. Returns false if null was received.

bool Extractor::extract(std::size_t pos, DateTime& val)
{
	poco_assert(pos>=0 && pos<_meta.size());

	OCI_Resultset *_res=OCI_GetResultset(_stmt);
	poco_assert(_res);

	DWORD ocitype=_meta[pos]->GetOCIType();
	switch(ocitype)
	{
	case OCI_CDT_DATETIME:
	case OCI_CDT_TIMESTAMP:
	case OCI_CDT_INTERVAL:
		{
			COCIDateTime *date=NULL;
			if(ocitype==OCI_CDT_DATETIME)
				date=new COCIDate(_stmt);
			else if(ocitype==OCI_CDT_TIMESTAMP)
				date=new COCITimestamp(_stmt);
			else
				date=new COCIInterval(_stmt);
			date->get(pos);
			date->read(val);
		}
		break;
	default:
		throw OracleException("Extract: Can't extract DateTime from this pos.");
	}
	return true;
}
}}}