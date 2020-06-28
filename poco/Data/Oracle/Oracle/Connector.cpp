#include "Poco/Data/Oracle/Connector.h"
#include "Poco/Data/Oracle/SessionImpl.h"
#include "Poco/Data/Oracle/OracleException.h"

//#include "Poco/Data/Oracle/OCIPlus.h"

#include <Poco/Data/SessionFactory.h>
#include <ocilib.h>

namespace Poco {
namespace Data {
namespace Oracle {

extern void err_handler(OCI_Error *err);
const std::string Connector::KEY("Oracle");


Connector::Connector(void)
{
}

Poco::AutoPtr<Poco::Data::SessionImpl> Connector::createSession(const std::string& connectionString)
{
	return Poco::AutoPtr<Poco::Data::SessionImpl>(new SessionImpl(connectionString));	
}

void Connector::registerConnector(Mode mode,int charset)
{
	//初始化
	OCI_Initialize(err_handler,NULL,mode,charset);
	//LoadOCI();
	Poco::Data::SessionFactory::instance().add(KEY, new Connector());
}


void Connector::unregisterConnector()
{
	Poco::Data::SessionFactory::instance().remove(KEY);
	//反初始化
	OCI_Cleanup();
	//FreeOCI();
}

}}}