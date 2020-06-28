#pragma once

#if defined(__ATLSYNC_H__) || defined(__AFXMT_H__)
namespace My{
#endif

class CCriticalSection
{
public:
	CCriticalSection()
	{
		InitializeCriticalSection(&cs);
	}
	~CCriticalSection()
	{
		DeleteCriticalSection(&cs);
	}
	void lock()
	{
		EnterCriticalSection(&cs);
	}

    bool tryLock()
	{
		return TryEnterCriticalSection(&cs) != 0;
	}
	
	bool tryLock(DWORD milliseconds)
	{
		const int sleepMillis = 5;
		DWORD now=GetTickCount();
		do
		{
			if (TryEnterCriticalSection(&cs) == TRUE)
				return true;
			Sleep(sleepMillis);
		}
		while (GetTickCount()-now<=milliseconds);
		return false;
	}

	void unlock()
	{
		LeaveCriticalSection(&cs);
	}

protected:
	CRITICAL_SECTION cs;

private:
	CCriticalSection(const CCriticalSection&);
	void operator=(const CCriticalSection &);
};

class CScopedLock
{
public:
	CScopedLock(CCriticalSection& lock):m_lock(lock)
	{
		m_lock.lock();
	}
	~CScopedLock()
	{
		m_lock.unlock();
	}

protected:
	CCriticalSection &m_lock;

private:

	CScopedLock(const CScopedLock&);
	void operator=(const CScopedLock &);
};

#if defined(__ATLSYNC_H__) || defined(__AFXMT_H__)
}
#endif
