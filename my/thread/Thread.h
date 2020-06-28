#pragma once
#include <Debug.h>
#include <process.h>

class CRunnable
{
public:	
	CRunnable()
	{
	}
	virtual ~CRunnable()
	{
	}

	virtual void run() = 0;
};


class CThread
{
public:
	CThread():
		m_thread(NULL)
,		m_threadId(0)
,		m_pRunnableTarget(NULL)
,		m_selfkill(FALSE)
		{}
	~CThread()
	{
		if (m_thread)
			CloseHandle(m_thread);
	}
	bool isRunning() const
	{
		if (m_thread)
		{
			DWORD ec = 0;
			return GetExitCodeThread(m_thread, &ec) && ec == STILL_ACTIVE;
		}
		return false;
	}
	bool join(long milliseconds=INFINITE)
	{
		if(m_thread==NULL)
			return true;

		DWORD result=WaitForSingleObject(m_thread,milliseconds);
		ASSERT(result==WAIT_OBJECT_0 || result==WAIT_TIMEOUT);
		if(result==WAIT_OBJECT_0)
		{
			return true;
			clear();
		}
		else
			return false;
	}
	void start(CRunnable& target,BOOL selfkill=FALSE)
	{
		ASSERT(!isRunning());
		m_pRunnableTarget = &target;
		m_selfkill=selfkill;
		create();
	}
	void stop()
	{
		ULONG exitcode;
		GetExitCodeThread(m_thread,&exitcode);
		TerminateThread(m_thread,exitcode);
		clear();

		if(m_pRunnableTarget)
		{
			delete m_pRunnableTarget;
			m_pRunnableTarget=NULL;
		}
	}

	static void startInPool(CRunnable& target)
	{
		VERIFY(QueueUserWorkItem(runnableEntryAlone,(PVOID)&target,WT_EXECUTEDEFAULT));
	}

	CRunnable* getRunnable() const
	{
		return m_pRunnableTarget;
	}

	bool post(UINT msg,WPARAM wp,LPARAM lp)
	{
		return PostThreadMessage(m_threadId,msg,wp,lp)==TRUE;
	}

protected:
	HANDLE m_thread;
	DWORD m_threadId;
	BOOL m_selfkill;

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

	static DWORD WINAPI runnableEntryAlone(LPVOID pRunnable)
	{
		reinterpret_cast<CRunnable*>(pRunnable)->run();
		return 0;
	}

	static unsigned WINAPI runnableEntry(LPVOID pThread)
	{
		reinterpret_cast<CThread*>(pThread)->m_pRunnableTarget->run();
		if(reinterpret_cast<CThread*>(pThread)->m_selfkill)
		{
			delete reinterpret_cast<CThread*>(pThread);
		}
		return 0;
	}
private:
	CThread(const CThread &);
	void operator=(const CThread &);
};
