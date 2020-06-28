#pragma once
#include <Debug.h>

#if defined(__ATLSYNC_H__) || defined(__AFXMT_H__)
namespace My{
#endif

class CMutex
{
public:
	explicit CMutex(TCHAR *name=NULL)
	{
		m_mutex=CreateMutex(NULL, FALSE, name);
		ASSERT(m_mutex!=NULL);
	}
	~CMutex()
	{
		CloseHandle(m_mutex);
	}
	void lock()
	{
		WaitForSingleObject(m_mutex,INFINITE);
	}

	bool tryLock(DWORD milliseconds=0)
	{
		DWORD result=WaitForSingleObject(m_mutex,milliseconds);
		ASSERT(result==WAIT_OBJECT_0 || result==WAIT_TIMEOUT);
		if(result==WAIT_OBJECT_0)
			return true;
		else
			return false;
	}

	void unlock()
	{
		VERIFY(ReleaseMutex(m_mutex));
	}

protected:
	HANDLE m_mutex;

private:
	CMutex(const CMutex&);
	void operator=(const CMutex&);
};

class CScopedLockMutex
{
public:
	CScopedLockMutex(CMutex& lock):m_lock(lock)
	{
		m_lock.lock();
	}
	~CScopedLockMutex()
	{
		m_lock.unlock();
	}

protected:
	CMutex &m_lock;

private:
	CScopedLockMutex(const CScopedLockMutex&);
	void operator=(const CScopedLockMutex &);
};

#if defined(__ATLSYNC_H__) || defined(__AFXMT_H__)
}
#endif
