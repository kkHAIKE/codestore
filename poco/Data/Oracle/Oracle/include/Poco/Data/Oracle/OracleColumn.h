#pragma once

#include "Poco\Data\Oracle\Oracle.h"
#include <poco\data\MetaColumn.h>

namespace Poco {
namespace Data {
namespace Oracle {

class Oracle_API OracleColumn :
	public Poco::Data::MetaColumn
{
public:
	OracleColumn(OCI_Resultset* rs, std::size_t position);

	unsigned int GetOCIType() const
	{
		return _ociType;
	}
	unsigned int GetOCISubType() const
	{
		return _ociSubType;
	}

protected:
	Poco::Data::MetaColumn::ColumnDataType OCITypeConv(OCI_Column *col);

	unsigned int _ociType;
	unsigned int _ociSubType;
};

}}}