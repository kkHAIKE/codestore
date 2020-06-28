#pragma once
#include <Debug.h>

class CRWLock
{
public:
	CRWLock():
		_readers(0)
,		_writersWaiting(0)
,		_writers(0)
	{
		_mutex = CreateMutex(NULL, FALSE, NULL);
		ASSERT(_mutex!=NULL);

		_readEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
		ASSERT(_readEvent!=NULL);

		_writeEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
		ASSERT(_writeEvent!=NULL);
	}
	~CRWLock()
	{
		CloseHandle(_mutex);
		CloseHandle(_readEvent);
		CloseHandle(_writeEvent);
	}
	void readLock()
	{
		HANDLE h[2];
		h[0] = _mutex;
		h[1] = _readEvent;
		DWORD result=WaitForMultipleObjects(2, h, TRUE, INFINITE);
		ASSERT(result==WAIT_OBJECT_0 || result==WAIT_OBJECT_0+1);

		++_readers;
		ResetEvent(_writeEvent);
		ReleaseMutex(_mutex);
		ASSERT(_writers == 0);
	}
	bool tryReadLock()
	{
		while(1)
		{
			if (_writers != 0 || _writersWaiting != 0)
				return false;

			DWORD result = tryReadLockOnce();
			ASSERT(result==WAIT_OBJECT_0 || result==WAIT_OBJECT_0+1 || result==WAIT_TIMEOUT);
			if(result==WAIT_TIMEOUT)
				continue;

			return true;
		}
	}
	void writeLock()
	{
		addWriter();
		HANDLE h[2];
		h[0] = _mutex;
		h[1] = _writeEvent;
		DWORD result=WaitForMultipleObjects(2, h, TRUE, INFINITE);
		ASSERT(result==WAIT_OBJECT_0 || result==WAIT_OBJECT_0+1);

		--_writersWaiting;
		++_readers;
		++_writers;
		ResetEvent(_readEvent);
		ResetEvent(_writeEvent);
		ReleaseMutex(_mutex);
		ASSERT(_writers == 1);
	}
	bool tryWriteLock()
	{
		addWriter();
		HANDLE h[2];
		h[0] = _mutex;
		h[1] = _writeEvent;
		DWORD result=WaitForMultipleObjects(2, h, TRUE, 1);
		ASSERT(result==WAIT_OBJECT_0 || result==WAIT_OBJECT_0+1 || result==WAIT_TIMEOUT);
		if(result==WAIT_TIMEOUT)
		{
			removeWriter();
			return false;
		}
		--_writersWaiting;
		++_readers;
		++_writers;
		ResetEvent(_readEvent);
		ResetEvent(_writeEvent);
		ReleaseMutex(_mutex);
		ASSERT(_writers == 1);
		return true;
	}
	void unlock()
	{
		VERIFY(WaitForSingleObject(_mutex, INFINITE)==WAIT_OBJECT_0);
		_writers = 0;
		if (_writersWaiting == 0) 
			SetEvent(_readEvent);
		if (--_readers == 0) 
			SetEvent(_writeEvent);
		ReleaseMutex(_mutex);
	}
private:
	CRWLock(const CRWLock&);
	void operator = (const CRWLock&);

	void addWriter()
	{
		VERIFY(WaitForSingleObject(_mutex, INFINITE)==WAIT_OBJECT_0);

		if (++_writersWaiting == 1)
			ResetEvent(_readEvent);
		ReleaseMutex(_mutex);
	}
	void removeWriter()
	{
		VERIFY(WaitForSingleObject(_mutex, INFINITE)==WAIT_OBJECT_0);

		if (--_writersWaiting == 0 && _writers == 0)
			SetEvent(_readEvent);
		ReleaseMutex(_mutex);
	}
	DWORD tryReadLockOnce()
	{
		HANDLE h[2];
		h[0] = _mutex;
		h[1] = _readEvent;
		DWORD result = WaitForMultipleObjects(2, h, TRUE, 1); 
		ASSERT(result==WAIT_OBJECT_0 || result==WAIT_OBJECT_0+1 || result==WAIT_TIMEOUT);

		if(result==WAIT_TIMEOUT)
			return result;

		++_readers;
		ResetEvent(_writeEvent);
		ReleaseMutex(_mutex);
		ASSERT(_writers == 0);
		return result;
	}

	HANDLE   _mutex;
	HANDLE   _readEvent;
	HANDLE   _writeEvent;
	unsigned _readers;
	unsigned _writersWaiting;
	unsigned _writers;
};
