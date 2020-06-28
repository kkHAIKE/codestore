#pragma once

#include <Debug.h>

#if !defined(__CSTRINGT_H__) && !defined(_WTL_USE_CSTRING)
#include <StdString.h>
#define CSTRING CStdString
#else
#define CSTRING CString
#endif

class CService
{
public:
	enum Startup
	{
		SVC_UNKNOW=0,
		SVC_AUTO_START,
		SVC_MANUAL_START,
		SVC_DISABLED
	};
	enum{STARTUP_TIMEOUT=30000};

	explicit CService(const TCHAR* name):_name(name),
		_svcHandle(0)
	{
		_scmHandle = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
		ASSERT(_scmHandle);
	}
	~CService()
	{
		close();
		CloseServiceHandle(_scmHandle);
	}

	bool isRegistered() 
	{
		return open();
	}
	bool isRunning()
	{
		open();
		SERVICE_STATUS ss;
		if (!QueryServiceStatus(_svcHandle, &ss))
			return false;
		return ss.dwCurrentState == SERVICE_RUNNING;
	}
	bool start()
	{
		open();
		if (!StartService(_svcHandle, 0, NULL))
			return false;

		SERVICE_STATUS svcStatus;
		long msecs = 0;
		while (msecs < STARTUP_TIMEOUT)
		{
			if (!QueryServiceStatus(_svcHandle, &svcStatus)) break;
			if (svcStatus.dwCurrentState != SERVICE_START_PENDING) break;
			Sleep(250);
			msecs += 250;
		}
		if (!QueryServiceStatus(_svcHandle, &svcStatus))
			return false;
		else return svcStatus.dwCurrentState == SERVICE_RUNNING;
	}

	bool stop()
	{
		open();
		SERVICE_STATUS svcStatus;
		if(!ControlService(_svcHandle, SERVICE_CONTROL_STOP, &svcStatus))
			return false;
		
		long msecs = 0;
		while (msecs < STARTUP_TIMEOUT)
		{
			if (!QueryServiceStatus(_svcHandle, &svcStatus)) break;
			if (svcStatus.dwCurrentState != SERVICE_STOP_PENDING) break;
			Sleep(250);
			msecs += 250;
		}
		if (!QueryServiceStatus(_svcHandle, &svcStatus))
			return false;
		else return svcStatus.dwCurrentState == SERVICE_STOPPED;
	}

	Startup getStartup()
	{	
		LPQUERY_SERVICE_CONFIG pSvcConfig=NULL;
		try
		{
			pSvcConfig = config();
		}
		catch (int)
		{
			return SVC_UNKNOW;
		}

		Startup result;
		switch (pSvcConfig->dwStartType)
		{
		case SERVICE_AUTO_START:
		case SERVICE_BOOT_START:
		case SERVICE_SYSTEM_START:
			result = SVC_AUTO_START;
			break;
		case SERVICE_DEMAND_START:
			result = SVC_MANUAL_START;
			break;
		case SERVICE_DISABLED:
			result = SVC_DISABLED;
			break;
		default:
			result = SVC_MANUAL_START;
		}

		LocalFree(pSvcConfig);
		return result;

	}

	void setStartup(Startup startup)
	{
		open();
		DWORD startType;
		switch (startup)
		{
		case SVC_AUTO_START:
			startType = SERVICE_AUTO_START;
			break;
		case SVC_MANUAL_START:
			startType = SERVICE_DEMAND_START;
			break;
		case SVC_DISABLED:
			startType = SERVICE_DISABLED;
			break;
		default:
			startType = SERVICE_NO_CHANGE;
		}
		VERIFY(ChangeServiceConfig(_svcHandle, SERVICE_NO_CHANGE, startType, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL));
	}

	CSTRING path()
	{
		LPQUERY_SERVICE_CONFIG pSvcConfig=NULL;
		try
		{
			pSvcConfig = config();
		}
		catch (int)
		{
			return _T("");
		}
		
		CSTRING ret(pSvcConfig->lpBinaryPathName);
		LocalFree(pSvcConfig);
		return ret;
	}

	void registerService(const TCHAR* path,const TCHAR*  displayName,const TCHAR* depend=NULL)//,bool reset=false) 
	{
		close();
		_svcHandle = CreateService(
			_scmHandle,
			_name,
			displayName, 
			SERVICE_ALL_ACCESS,
			SERVICE_WIN32_OWN_PROCESS,
			SERVICE_AUTO_START,
			SERVICE_ERROR_NORMAL,
			//(reset?SERVICE_ERROR_SEVERE:SERVICE_ERROR_NORMAL),
			path,
			NULL, NULL, depend, NULL, NULL);

		ASSERT(_svcHandle);
	}

protected:
	bool open()
	{
		_svcHandle = OpenService(_scmHandle, _name, SERVICE_ALL_ACCESS);
		return _svcHandle != 0;
	}
	void close()
	{
		if (_svcHandle)
		{
			CloseServiceHandle(_svcHandle);
		}
	}
	LPQUERY_SERVICE_CONFIG config()
	{
		open();
		int size = 4096;
		DWORD bytesNeeded;
		LPQUERY_SERVICE_CONFIG pSvcConfig = (LPQUERY_SERVICE_CONFIG) LocalAlloc(LPTR, size);
		ASSERT(pSvcConfig);
		try
		{
			while (!QueryServiceConfig(_svcHandle, pSvcConfig, size, &bytesNeeded))
			{
				if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
				{
					LocalFree(pSvcConfig);
					size = bytesNeeded;
					pSvcConfig = (LPQUERY_SERVICE_CONFIG) LocalAlloc(LPTR, size);
				}
				else throw 1;
			}
		}
		catch (...)
		{
			LocalFree(pSvcConfig);
			throw;
		}
		return pSvcConfig;
	}

	CSTRING _name;
	SC_HANDLE _scmHandle;
	SC_HANDLE _svcHandle;

private:
	CService(const CService&);
	void operator = (const CService&);
};
