#ifndef __EVENT_H__
#define __EVENT_H__

#include <pthread.h>

class CEvent
{
public:
	CEvent(bool autoReset = true,bool initstate=false):_auto(autoReset), _state(initstate)
	{
		pthread_mutex_init(&_mutex, NULL);
		pthread_cond_init(&_cond, NULL);
	}

	~CEvent()
	{
		pthread_cond_destroy(&_cond);
		pthread_mutex_destroy(&_mutex);
	}

	void set()
	{
		pthread_mutex_lock(&_mutex);
		_state = true;
		pthread_cond_broadcast(&_cond);
		pthread_mutex_unlock(&_mutex);
	}

	void wait()
	{
		pthread_mutex_lock(&_mutex);
		while (!_state) 
		{
			if (pthread_cond_wait(&_cond, &_mutex))
			{
				pthread_mutex_unlock(&_mutex);
				return;
			}
		}
		if (_auto)
			_state = false;
		pthread_mutex_unlock(&_mutex);
	}

	void reset()
	{
		pthread_mutex_lock(&_mutex);
		_state = false;
		pthread_mutex_unlock(&_mutex);
	}

private:
	CEvent(const CEvent &);
	void operator=(const CEvent &);

protected:
	bool            _auto;
	volatile bool   _state;
	pthread_mutex_t _mutex;
	pthread_cond_t  _cond;
};

#endif
