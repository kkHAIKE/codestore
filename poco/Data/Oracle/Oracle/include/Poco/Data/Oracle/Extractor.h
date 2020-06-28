#pragma once

#include "Poco/Data/Oracle/Oracle.h"
#include "Poco/Data/Oracle/OracleColumn.h"
#include "Poco/Data/Oracle/OracleTypeWrapper.h"
#include <Poco/Data/AbstractExtractor.h>

namespace Poco {
namespace Data {
namespace Oracle {

class Extractor :
	public Poco::Data::AbstractExtractor
{
public:
	Extractor(OCI_Statement *stmt,std::vector<SharedPtr<OracleColumn>> &meta);

	virtual bool extract(std::size_t pos, Poco::Int8& val);
	/// Extracts an Int8. Returns false if null was received.

	virtual bool extract(std::size_t pos, Poco::UInt8& val);
	/// Extracts an UInt8. Returns false if null was received.

	virtual bool extract(std::size_t pos, Poco::Int16& val);
	/// Extracts an Int16. Returns false if null was received.

	virtual bool extract(std::size_t pos, Poco::UInt16& val);
	/// Extracts an UInt16. Returns false if null was received.

	virtual bool extract(std::size_t pos, Poco::Int32& val);
	/// Extracts an Int32. Returns false if null was received.

	virtual bool extract(std::size_t pos, Poco::UInt32& val);
	/// Extracts an UInt32. Returns false if null was received.

	virtual bool extract(std::size_t pos, Poco::Int64& val);
	/// Extracts an Int64. Returns false if null was received.

	virtual bool extract(std::size_t pos, Poco::UInt64& val);
	/// Extracts an UInt64. Returns false if null was received.

	virtual bool extract(std::size_t pos, bool& val);
	/// Extracts a boolean. Returns false if null was received.

	virtual bool extract(std::size_t pos, float& val);
	/// Extracts a float. Returns false if null was received.

	virtual bool extract(std::size_t pos, double& val);
	/// Extracts a double. Returns false if null was received.

	virtual bool extract(std::size_t pos, char& val);
	/// Extracts a single character. Returns false if null was received.

	virtual bool extract(std::size_t pos, std::string& val);
	/// Extracts a string. Returns false if null was received.

	virtual bool extract(std::size_t pos, BLOB& val);
	/// Extracts a BLOB. Returns false if null was received.

	virtual bool extract(std::size_t pos, DateTime& val);

protected:

	OCI_Statement *_stmt;
	std::vector<SharedPtr<OracleColumn>> &_meta;
};

}}}