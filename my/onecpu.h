#pragma once

#ifndef ONECPU_NAME
#define ONECPU_NAME "one_cpu"
#endif

#pragma data_seg(ONECPU_NAME)
DWORD_PTR g_cpu1=0,g_cpu2=0;
#pragma data_seg()
#pragma comment(linker,"/SECTION:"ONECPU_NAME",RWS")

class COneCpu
{
public:
	static COneCpu& Instance()
	{
		static COneCpu instance;
		return instance;
	}
	~COneCpu()
	{
		if(m_mutex)
		{
			unsetcpu();
			CloseHandle(m_mutex);
		}
	}

protected:
	COneCpu():m_id(-1)
	{
		m_mutex=CreateMutex(NULL,FALSE,_T("Global\\"ONECPU_NAME));
		if(m_mutex==NULL)
			return;

		m_ncpu=getcpus();

		m_mask[0]=1;
		for(int i=1;i<sizeof(DWORD_PTR);++i)
		{
			m_mask[i]=m_mask[i-1]*2;
		}

		setcpu();
	}
	void setcpu()
	{
		lock();
		for(int i=0;i<m_ncpu;++i)
		{
			if((g_cpu1 & m_mask[i])==0)
			{
				m_id=i;
				SetProcessAffinityMask(GetCurrentProcess(),m_mask[i]);
				g_cpu1|=m_mask[i];
				break;
			}
		}
		if(m_id==-1)
		{
			for(int i=0;i<m_ncpu;++i)
			{
				if((g_cpu2 & m_mask[i])==0)
				{
					m_id=i+sizeof(DWORD_PTR);
					SetProcessAffinityMask(GetCurrentProcess(),m_mask[i]);
					g_cpu2|=m_mask[i];
					break;
				}
			}
		}
		unlock();
	}
	void unsetcpu()
	{
		if(m_id!=-1)
		{
			lock();
			if(m_id>=sizeof(DWORD_PTR))
			{
				g_cpu2&=~m_mask[m_id-sizeof(DWORD_PTR)];
			}
			else
			{
				g_cpu1&=~m_mask[m_id];
			}
			unlock();
		}
	}
	void lock()
	{
		WaitForSingleObject(m_mutex,INFINITE);
	}
	void unlock()
	{
		ReleaseMutex(m_mutex);
	}
	int getcpus()
	{
		SYSTEM_INFO info;
		GetSystemInfo(&info);
		return info.dwNumberOfProcessors;
	}

protected:
	HANDLE m_mutex;
	int m_id,m_ncpu;
	DWORD_PTR m_mask[sizeof(DWORD_PTR)];

private:
	COneCpu(const COneCpu&);
	void operator=(const COneCpu&);
};

