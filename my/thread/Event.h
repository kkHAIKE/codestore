#pragma once
#include <Debug.h>

#if defined(__ATLSYNC_H__) || defined(__AFXMT_H__)
namespace My{
#endif

class CEvent
{
public:
	explicit
	CEvent(bool autoReset = true,bool initstate=false,TCHAR *name=NULL)
	{
		m_event=CreateEvent(NULL,!autoReset,initstate,name);
		ASSERT(m_event!=NULL);
	}

	~CEvent()
	{
		CloseHandle(m_event);
	}

	void set()
	{
		VERIFY(SetEvent(m_event));
	}

	bool wait(long milliseconds=INFINITE)
	{
		DWORD result=WaitForSingleObject(m_event,milliseconds);
		ASSERT(result==WAIT_OBJECT_0 || result==WAIT_TIMEOUT);
		if(result==WAIT_OBJECT_0)
			return true;
		else
			return false;
	}

	void reset()
	{
		VERIFY(ResetEvent(m_event));
	}
	
private:
	CEvent(const CEvent &);
	void operator=(const CEvent &);

protected:
	HANDLE m_event;
};

#if defined(__ATLSYNC_H__) || defined(__AFXMT_H__)
}
#endif
