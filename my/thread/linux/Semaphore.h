#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include <pthread.h>
#include <sys/time.h>
#include <asm/errno.h>
//#include <asm-generic/errno.h>

class CSemaphore
{
public:
	explicit CSemaphore(int max=65535):_n(0),_max(max)
	{
		pthread_mutex_init(&_mutex, 0);
		pthread_cond_init(&_cond, 0);
	}

	CSemaphore(int n, int max):_n(n),_max(max)
	{
		pthread_mutex_init(&_mutex, 0);
		pthread_cond_init(&_cond, 0);
	}

	~CSemaphore()
	{
		pthread_cond_destroy(&_cond);
		pthread_mutex_destroy(&_mutex);
	}

	void set(int i=1)
	{
		pthread_mutex_lock(&_mutex);
		if (_n < _max)
		{
			_n+=i;
		}
		else
		{
			pthread_mutex_unlock(&_mutex);
			return;
		}	
		pthread_cond_signal(&_cond);
		pthread_mutex_unlock(&_mutex);
	}

	void wait()
	{
		pthread_mutex_lock(&_mutex);

		while (_n < 1)
		{
			if (pthread_cond_wait(&_cond, &_mutex))
			{
				pthread_mutex_unlock(&_mutex);
				return;
			}
		}
		--_n;
		pthread_mutex_unlock(&_mutex);
	}

	bool wait(long milliseconds)
	{
		int rc = 0;
		struct timespec abstime;

		struct timeval tv;
		gettimeofday(&tv, NULL);
		abstime.tv_sec  = tv.tv_sec + milliseconds / 1000;
		abstime.tv_nsec = tv.tv_usec*1000 + (milliseconds % 1000)*1000000;
		if (abstime.tv_nsec >= 1000000000)
		{
			abstime.tv_nsec -= 1000000000;
			abstime.tv_sec++;
		}

		pthread_mutex_lock(&_mutex);
		while (_n < 1) 
		{
			if ((rc = pthread_cond_timedwait(&_cond, &_mutex, &abstime)))
			{
				if (rc == ETIMEDOUT) break;
				pthread_mutex_unlock(&_mutex);
				return false;
			}
		}
		if (rc == 0) --_n;
		pthread_mutex_unlock(&_mutex);
		return rc == 0;
	}

protected:
	volatile int    _n;
	int             _max;
	pthread_mutex_t _mutex;
	pthread_cond_t  _cond;

private:
	CSemaphore(const CSemaphore&);
	void operator = (const CSemaphore&);

};

#endif

