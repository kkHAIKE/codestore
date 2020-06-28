#pragma once

#include <Debug.h>

#if defined(__ATLSYNC_H__) || defined(__AFXMT_H__)
namespace My{
#endif

class CSemaphore
{
public:
	explicit CSemaphore(int max=65535,TCHAR* name=NULL)
	{
		m_sem=CreateSemaphore(NULL,0,max,name);
		ASSERT(m_sem!=NULL);
	}
	CSemaphore(int n, int max,TCHAR* name=NULL)
	{
		m_sem=CreateSemaphore(NULL,n,max,name);
		ASSERT(m_sem!=NULL);
	}

	~CSemaphore()
	{
		CloseHandle(m_sem);
	}

	void set(int i=1)
	{
		VERIFY(ReleaseSemaphore(m_sem,i,NULL));
	}

	bool wait(long milliseconds=INFINITE)
	{
		DWORD result=WaitForSingleObject(m_sem,milliseconds);
		ASSERT(result==WAIT_OBJECT_0 || result==WAIT_TIMEOUT);
		if(result==WAIT_OBJECT_0)
			return true;
		else
			return false;
	}

protected:
	HANDLE m_sem;

private:
	CSemaphore(const CSemaphore&);
	void operator = (const CSemaphore&);

};

#if defined(__ATLSYNC_H__) || defined(__AFXMT_H__)
}
#endif
