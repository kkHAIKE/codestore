#pragma once

#include <thread\Thread.h>
#include <Debug.h>

class CWaitTimer
{
public:
	CWaitTimer():
		m_thread(NULL)
,		m_threadId(0)
,		m_pRunnableTarget(NULL)
,		is_end(false)
	{
		m_Timer=CreateWaitableTimer(NULL,FALSE,NULL);
		m_event=CreateEvent(NULL,FALSE,FALSE,NULL);
		ASSERT(m_Timer!=NULL);
	}
	~CWaitTimer()
	{
		CloseHandle(m_Timer);
		CloseHandle(m_event);
		if(m_thread)
			CloseHandle(m_thread);
	}
	
	void start(CRunnable& target,DWORD milliseconds)
	{
		LARGE_INTEGER li;
		li.QuadPart=0;

		m_pRunnableTarget = &target;
		is_end=false;
		VERIFY(SetWaitableTimer(m_Timer,&li,milliseconds,NULL,NULL,FALSE));
		create();
	}
	
	void stop(BOOL del=FALSE)
	{
		is_end=true;
		CancelWaitableTimer(m_Timer);
		SetEvent(m_event);
		//VERIFY(WaitForSingleObject(m_thread,INFINITE)==WAIT_OBJECT_0);
		WaitForSingleObject(m_thread,INFINITE);
		clear();
		if(del && m_pRunnableTarget)
		{
			delete m_pRunnableTarget;
			m_pRunnableTarget=NULL;
		}
	}

	CRunnable* getRunnable() const
	{
		return m_pRunnableTarget;
	}
protected:
	HANDLE m_Timer;
	HANDLE m_event;
	HANDLE m_thread;
	DWORD m_threadId;
	bool is_end;

	CRunnable*  m_pRunnableTarget;

	void clear()
	{
		if(m_thread)
		{
			CloseHandle(m_thread);
			m_thread=NULL;
		}
	}

	void create()
	{
		unsigned threadId;
		m_thread = reinterpret_cast<HANDLE>(_beginthreadex(NULL, 0, runnableEntry, this, 0, &threadId));
		m_threadId=threadId;
	}

	static unsigned WINAPI runnableEntry(LPVOID pThread)
	{
		HANDLE hand[2];
		hand[0]=reinterpret_cast<CWaitTimer*>(pThread)->m_Timer;
		hand[1]=reinterpret_cast<CWaitTimer*>(pThread)->m_event;
		while(1)
		{
			DWORD result=WaitForMultipleObjects(2,hand,FALSE,INFINITE);
			ASSERT(result==WAIT_OBJECT_0 || result==WAIT_OBJECT_0+1);
			if(reinterpret_cast<CWaitTimer*>(pThread)->is_end)
				break;
			reinterpret_cast<CWaitTimer*>(pThread)->m_pRunnableTarget->run();
		}
		return 0;
	}
private:
	CWaitTimer(const CWaitTimer &);
	void operator=(const CWaitTimer &);
};