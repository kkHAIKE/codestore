#pragma once

#include <thread\WaitTimer.h>

#include <winsock2.h>
#include <iphlpapi.h>
#include <icmpapi.h>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

class CIcmpPing:public CRunnable,public CWaitTimer
{
public:
	explicit CIcmpPing(const char* ip)
	{
		m_ipAddr=inet_addr(ip);
		m_hIcmpFile = IcmpCreateFile();
	}
	virtual ~CIcmpPing(void)
	{
		IcmpCloseHandle(m_hIcmpFile);
	}

	void run()
	{
		BYTE sendbuf[33]="    abcdefghijklmnopqrstuvwxyz,.";
		BYTE recvbuf[sizeof (ICMP_ECHO_REPLY) + sizeof (sendbuf) + 8];
		PICMP_ECHO_REPLY pEchoReply = reinterpret_cast<PICMP_ECHO_REPLY>(recvbuf);

		*reinterpret_cast<DWORD*>(sendbuf)=GetTickCount();

		DWORD dwRetVal =IcmpSendEcho2(m_hIcmpFile, NULL, NULL, NULL,
			m_ipAddr, sendbuf, 32, NULL,
			recvbuf, sizeof(recvbuf), 1000);

		if(dwRetVal!=0 && pEchoReply->Status==IP_SUCCESS && GetLastError()==ERROR_SUCCESS)
			recvfuc(GetTickCount()-*reinterpret_cast<DWORD*>(recvbuf+sizeof(ICMP_ECHO_REPLY)),TRUE);
		else
			recvfuc(0,FALSE);
	}
	void start(DWORD delay=1000)
	{
		CWaitTimer::start(*this,delay);
	}

	virtual void recvfuc(DWORD time,BOOL isOK)
	{
		printf("%u\n",time);
	}

protected:
	DWORD m_ipAddr;
	HANDLE m_hIcmpFile;
};
