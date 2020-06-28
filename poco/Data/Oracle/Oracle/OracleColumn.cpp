#include "Poco\Data\Oracle\OracleColumn.h"

#include <ocilib.h>

namespace Poco {
namespace Data {
namespace Oracle {

Poco::Data::MetaColumn::ColumnDataType OracleColumn::OCITypeConv(OCI_Column *col)
{
	_ociType=OCI_ColumnGetType(col);

	switch(_ociType)
	{
	case OCI_CDT_NUMERIC:
		if(OCI_ColumnGetScale(col)==0)
			return Poco::Data::MetaColumn::FDT_INT64;
		else
			return Poco::Data::MetaColumn::FDT_DOUBLE;

	case OCI_CDT_TEXT:
		return Poco::Data::MetaColumn::FDT_STRING;

	case OCI_CDT_TIMESTAMP:
	case OCI_CDT_INTERVAL:
		_ociSubType=OCI_ColumnGetSubType(col);
	case OCI_CDT_DATETIME:
		return Poco::Data::MetaColumn::FDT_DATETIME;

	case OCI_CDT_LONG:
	case OCI_CDT_LOB:
		_ociSubType=OCI_ColumnGetSubType(col);
	case OCI_CDT_RAW:
		return Poco::Data::MetaColumn::FDT_BLOB; 
	}
	return Poco::Data::MetaColumn::FDT_UNKNOWN; 
}

OracleColumn::OracleColumn(OCI_Resultset* rs, std::size_t position):
	MetaColumn(position)
,	_ociSubType(0)
{
	OCI_Column *col=OCI_GetColumn(rs,position+1);

	setName(OCI_ColumnGetName(col));
	setType(OCITypeConv(col));
	setLength(OCI_ColumnGetSize(col));
	setPrecision(OCI_ColumnGetPrecision(col));
	setNullable(OCI_ColumnGetNullable(col) == TRUE);
}

}}}