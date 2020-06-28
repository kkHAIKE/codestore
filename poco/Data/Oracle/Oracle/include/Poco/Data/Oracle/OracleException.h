#pragma once

#include "Poco\Data\Oracle\Oracle.h"
#include <poco\data\dataexception.h>

namespace Poco {
namespace Data {
namespace Oracle {

POCO_DECLARE_EXCEPTION(Oracle_API, OracleException, Poco::Data::DataException)

}}}