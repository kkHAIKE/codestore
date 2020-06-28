#pragma once

#include "Poco/Data/Oracle/Oracle.h"
#include <Poco/Data/Connector.h>

namespace Poco {
namespace Data {
namespace Oracle {

class Oracle_API Connector :
	public  Poco::Data::Connector
{

public:
	enum Mode
	{
		DEFAULT = 0x00000000,
		OBJECT = 0x00000002,
		//SHARED = 0x00000010,
		//NO_USERCALLBACKS = 0x00000040,
		THREADED_MUTEXED = 0x00000001,
		//THREADED_UNMUTEXED = 0x00000001 | 0x00000080,
		EVENTS = 0x00000004,
		//USE_LDAP = 0x00001000
	};

	static const std::string KEY;
	/// Keyword for creating sessions

	Connector();
	/// Creates the Connector.

	virtual Poco::AutoPtr < Poco::Data::SessionImpl > createSession(const std::string& connectionString);
	/// Creates a SessionImpl object and initializes it with the given connectionString.

	static void registerConnector(Mode mode=DEFAULT,int charset=0);
	/// Registers the Connector under the Keyword Connector::KEY at the Poco::Data::SessionFactory

	static void unregisterConnector();
	/// Unregisters the Connector under the Keyword Connector::KEY at the Poco::Data::SessionFactory
};

	
}}}