#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>

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
	CThread():m_thread(-1)
	{
	}
	void join()
	{
		pthread_join(m_thread,NULL);
	}
	void start(CRunnable& target)
	{
		m_pRunnableTarget = &target;
		pthread_create(&m_thread,NULL,runnableEntry,this);
	}
	CRunnable* getRunnable() const
	{
		return m_pRunnableTarget;
	}
protected:
	pthread_t m_thread;
	CRunnable*  m_pRunnableTarget;

	static void* runnableEntry(void* pThread)
	{
		reinterpret_cast<CThread*>(pThread)->m_pRunnableTarget->run();
		return 0;
	}

private:
	CThread(const CThread&);
	void operator=(const CThread&);
};

#endif

