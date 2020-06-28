#include "Poco/Data/Oracle/OracleException.h"

#include <ocilib.h>
#include <sstream>

namespace Poco {
namespace Data {
namespace Oracle {

void err_handler(OCI_Error *err)
{
	std::ostringstream s;
	s << "ORA-" << OCI_ErrorGetOCICode(err) << ":" << OCI_ErrorGetString(err);

	throw OracleException(s.str());
}

POCO_IMPLEMENT_EXCEPTION(OracleException,Poco::Data::DataException,"Oracle error")

}}}