#ifndef __MUTEX_H__
#define __MUTEX_H__

#include <pthread.h>

class CMutex
{
public:
	CMutex()
	{
		//pthread_mutexattr_t attr;
		//pthread_mutexattr_init(&attr);
		//pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_NORMAL);
		//pthread_mutex_init(&_mutex, &attr);
		//pthread_mutexattr_destroy(&attr);
		pthread_mutex_init(&_mutex, NULL);
	}
	~CMutex()
	{
		pthread_mutex_destroy(&_mutex);
	}
	void lock()
	{
		pthread_mutex_lock(&_mutex);
	}
	void unlock()
	{
		pthread_mutex_unlock(&_mutex);
	}

protected:
	pthread_mutex_t _mutex;
	
private:
	CMutex(const CMutex&);
	void operator=(const CMutex&);
};

class CScopedLock
{
public:
	CScopedLock(CMutex& lock):m_lock(lock)
	{
		m_lock.lock();
	}
	~CScopedLock()
	{
		m_lock.unlock();
	}

protected:
	CMutex &m_lock;

private:

	CScopedLock(const CScopedLock&);
	void operator=(const CScopedLock &);
};

#endif
