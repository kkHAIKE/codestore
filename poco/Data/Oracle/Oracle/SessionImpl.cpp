#include "Poco/Data/Oracle/SessionImpl.h"
#include "Poco/Data/Oracle/Connector.h"
#include "Poco/Data/Oracle/OracleException.h"
#include "Poco/Data/Oracle/OracleStatementImpl.h"
#include "Poco/NumberParser.h"

#include <ocilib.h>

namespace
{
	//复制段然后去空格
	std::string copyStripped(std::string::const_iterator from, std::string::const_iterator to)
	{
		// skip leading spaces
		while ((from != to) && isspace(*from)) from++;
		// skip trailing spaces
		while ((from != to) && isspace(*(to - 1))) to--;

		return std::string(from, to);
	}
}

namespace Poco {
namespace Data {
namespace Oracle {

SessionImpl::SessionImpl(const std::string& connectionString):_conn(NULL),_inTransaction(0),_isAutoCommit(false)
{
	addFeature("autoCommit", 
		&SessionImpl::autoCommit, 
		&SessionImpl::isAutoCommit);

	std::map<std::string, std::string> options;

	options["host"] = "localhost";
	options["port"] = "1521";
	options["user"] = "root";
	options["password"] = "";
	options["db"] = "";

	for (std::string::const_iterator start = connectionString.begin();;) 
	{
		// find next ';'
		std::string::const_iterator finish = std::find(start, connectionString.end(), ';');

		// find '='
		std::string::const_iterator middle = std::find(start, finish, '=');

		if (middle == finish)
		{
			throw OracleException("create session: bad connection string format, can not find '='");
		}

		// Parse name and value, skip all spaces
		options[copyStripped(start, middle)] = copyStripped(middle + 1, finish);

		if (finish == connectionString.end())
		{
			// end of parse
			break;
		}

		// move start position after ';'
		start = finish + 1;
	}

	if (options["user"] == "")
	{
		throw OracleException("create session: specify user name");
	}

	if (options["db"] == "")
	{
		throw OracleException("create session: specify database");
	}

	unsigned int port = 0;
	if (!NumberParser::tryParseUnsigned(options["port"], port) || 0 == port || port > 65535)
	{
		throw OracleException("create session: specify correct port (numeric in decimal notation)");
	}

	_conn=OCI_ConnectionCreate((options["host"]+":"+options["port"]+"/"+options["db"]).c_str(),
		options["user"].c_str(),options["password"].c_str(),OCI_SESSION_DEFAULT);

	autoCommit("",true);
}

SessionImpl::~SessionImpl(void)
{
	close();
}

Poco::Data::StatementImpl* SessionImpl::createStatementImpl()
{
	return new OracleStatementImpl(_conn,_isAutoCommit);
}	


void SessionImpl::begin()
{
	if(!isAutoCommit())
		++_inTransaction;
}


void SessionImpl::commit()
{
	if(!isAutoCommit())
	{
		OCI_Commit(_conn);
		--_inTransaction;
	}
}


void SessionImpl::rollback()
{
	if(!isAutoCommit())
	{
		OCI_Rollback(_conn);
		--_inTransaction;
	}
}


void SessionImpl::close()
{
	if (isConnected())
	{
		OCI_ConnectionFree(_conn);_conn=NULL;
	}
}


bool SessionImpl::isConnected()
{
	return OCI_IsConnected(_conn)==1;
}

bool SessionImpl::isTransaction()
{
	return (_inTransaction > 0);
}

void SessionImpl::autoCommit(const std::string&, bool val)
{
	_isAutoCommit=val;
	//OCI_SetAutoCommit(_conn,val);
}

bool SessionImpl::isAutoCommit(const std::string&)
{
	return _isAutoCommit;
	//return OCI_GetAutoCommit(_conn)==1;
}

}}}