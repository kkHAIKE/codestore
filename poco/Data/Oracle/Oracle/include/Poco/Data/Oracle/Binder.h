#pragma once

#include "Poco/Data/Oracle/Oracle.h"
#include "Poco/Data/Oracle/OracleTypeWrapper.h"
#include <Poco/Data/AbstractBinder.h>

#include <map>

namespace Poco {
namespace Data {
namespace Oracle {

class Oracle_API Binder :
	public Poco::Data::AbstractBinder
{
public:
	Binder(OCI_Statement *stmt);

	virtual void bind(std::size_t pos, const Poco::Int16& val);
	/// Binds an Int16.

	virtual void bind(std::size_t pos, const Poco::UInt16& val);
	/// Binds an UInt16.

	virtual void bind(std::size_t pos, const Poco::Int32& val);
	/// Binds an Int32.

	virtual void bind(std::size_t pos, const Poco::UInt32& val);
	/// Binds an UInt32.

	virtual void bind(std::size_t pos, const Poco::Int64& val);
	/// Binds an Int64.

	virtual void bind(std::size_t pos, const Poco::UInt64& val);
	/// Binds an UInt64.

	virtual void bind(std::size_t pos, const double& val);
	/// Binds a double.
	

	virtual void bind(std::size_t pos, const char* const &pVal);
	/// Binds a const char ptr.

	virtual void bind(std::size_t pos, const std::string& val);
	/// Binds a string.

	virtual void bind(std::size_t pos, const BLOB& val);
	/// Binds a BLOB.

	virtual void bind(std::size_t pos, const DateTime& val);

	virtual void bind(std::size_t pos);

	void bind(std::size_t pos,const OracleBindHelpper & val);

	std::vector<SharedPtr<COCILong>> &GetBindLong()
	{
		return _bindlong;
	}

protected:
	virtual void bind(std::size_t pos, const Poco::Int8& val){}
	/// Binds an Int8.

	virtual void bind(std::size_t pos, const Poco::UInt8& val){}
	/// Binds an UInt8.

	virtual void bind(std::size_t pos, const char& val){}
	/// Binds a single character.

	virtual void bind(std::size_t pos, const bool& val){}
	/// Binds a boolean.

	virtual void bind(std::size_t pos, const float& val){}
	/// Binds a float.

	OCI_Statement *_stmt;
	std::map<int,SharedPtr<COCITypeWrapper>> _bindtmp;
	std::vector<SharedPtr<COCILong>> _bindlong;
};

}}}