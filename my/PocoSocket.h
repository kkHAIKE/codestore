#pragma once

// #ifndef MAX_RECV
// #define MAX_RECV 1024
// #endif
// #ifndef MAX_SEND
// #define MAX_SEND 1024
// #endif

class PocoSocket
{
public:
	PocoSocket(Poco::Net::StreamSocket &ss):m_ss(ss){}

	void FullRecv(void* buffer, int length)
	{
		char* p = reinterpret_cast<char*>(buffer);
		int remaining = length;
		int recvt = 0;
		bool blocking = m_ss.getBlocking();
		while (remaining > 0)
		{
			int n = m_ss.receiveBytes(p, remaining, 0);
			if(n<0)
				throw Poco::Net::NetException("My Unknow Recv Error");
			//poco_assert_dbg (n >= 0);
			p += n; 
			recvt += n;
			remaining -= n;
			if (blocking && remaining > 0)
				Sleep(0);
			else
				break;
		}

// 		BYTE *p_buf=reinterpret_cast<BYTE*>(buffer);
// 		int recvret=0;
// 
// 		do
// 		{
// 			recvret=m_ss.receiveBytes(p_buf,min(MAX_RECV,length));
// 			if(recvret==0)
// 				break;
// 			p_buf+=recvret;
// 			length-=recvret;
// 		}
// 		while(length!=0);
// 
// 		if(length!=0)
// 			throw NetException("My Unknow Recv Error");
	}

 	inline void FullSend(void* buffer, int length)
 	{
		m_ss.sendBytes(buffer,length,0);
// 		BYTE *p_buf=reinterpret_cast<BYTE*>(buffer);
// 		int sendret=0;
// 
// 		do
// 		{
// 			sendret=m_ss.sendBytes(p_buf,min(MAX_SEND,length));
// 			if(sendret==0)
// 				break;
// 			p_buf+=sendret;
// 			length-=sendret;
// 		}
// 		while(length!=0);
// 
// 		if(length!=0)
// 			throw NetException("My Unknow Send Error");
	}
protected:
	Poco::Net::StreamSocket &m_ss;
};

