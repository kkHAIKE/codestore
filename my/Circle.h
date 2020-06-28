#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include <stdio.h>

#include "Mutex.h"
#include "Semaphore.h"

#include "../myconfig.h"

//线程安全打开适用于单POP多PUSH
//不打开适用于单POP单PUSH
template<typename T,int N,bool S=false,bool D=false>
class CCircle
{
public:
	CCircle():front(0),rear(0),m_mtSafe(NULL),m_cs(NULL)
	{
		if(S)
			m_mtSafe=new CMutex();
		if(D)
			m_cs=new CSemaphore();
	}
	~CCircle()
	{
		if(S)
			delete m_mtSafe;
		if(D)
			delete m_cs;
	}

	T* push_start()
	{
		if(S)
			m_mtSafe->lock();

		T* push_ptr = 0;

		if(((rear + 1) % N) == front)
		{
			printf("********************* image queue is full ********************\n");
			if(S)
				m_mtSafe->unlock();
			return 0;
		}

		push_ptr = m_tBuffer+rear;	
		return push_ptr;
	}
	
	void push_end()
	{
		rear = (rear + 1) % N;

		if(D)
			m_cs->set();
		if(S)
			m_mtSafe->unlock();
	}

	T* pop(long milliseconds=0)
	{
		if(D)
		{
			if(milliseconds>0)
			{
				if(!m_cs->wait(milliseconds))
					return 0;
			}
			else
				m_cs->wait();
		}
		
		T* pop_ptr = 0;

		if(front == rear)
		{
			printf("********************* image queue is empty *******************\n");
			return 0;
		}
		pop_ptr = m_tBuffer+front;
		front = (front + 1) % N;
		return pop_ptr;
	}
protected:
	T m_tBuffer[N];
	int front,rear;

	CMutex *m_mtSafe;
	CSemaphore *m_cs;
};

#endif

