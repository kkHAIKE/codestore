#include "StdAfx.h"
#include "HikTimer.h"

extern int g_nHighTimerNum;

VOID CALLBACK StopAPCProc(ULONG_PTR dwParam)
{
	reinterpret_cast<CHikTimer*>(dwParam)->Reflash();
}
DWORD WINAPI WaitableTimerThread(LPVOID lpParameter)
{
	reinterpret_cast<CHikTimer*>(lpParameter)->CreateTimerLow();
}
VOID CALLBACK TimerAPCProc( LPVOID lpArgToCompletionRoutine ,DWORD dwTimerLowValue , DWORD dwTimerHighValue)
{
	CHikTimer* a1=reinterpret_cast<CHikTimer*>(lpArgToCompletionRoutine);

	if ( a1->ShouldDisplay() )
		a1->DisplayFrame();
	else
		a1->Reflash();
}
void CALLBACK DisplayTimerThread(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
{
	CHikTimer* a1=reinterpret_cast<CHikTimer*>(dwUser);

	if ( a1->ShouldDisplay() )
		a1->DisplayFrame();
	else
		a1->Reflash();
}

CHikTimer::CHikTimer( CMediaManager* a2,CVideoRenderer* a3,CAudioRenderer* a4 )
{
	m_pMediaManager = a2;
	m_pVidRender = a3;
	m_pAudRender = a4;
	m_nStreamMode = -1;
	m_uPeriodDef = 10;
	m_uPeriodHigh = 10;
	m_uPeriodLow = 40;
	m_nTimePerFrame = 40;
	m_fSpeed = 1.0;
	m_nTimerType = 1;
	m_uTimerID = 0;
	m_hThread = 0;
	m_flagChangeLow = 0;
	m_bDisplay = 1;
	part31 = 0;
	memset(m_sIVSInfo, 0, 64);
	m_nStatus = 3;
	m_bDisplayByTime = 0;
	m_nFrameCount = 0;
	InitializeCriticalSection(&m_csTimer);
}

CHikTimer::~CHikTimer(void)
{
	CloseTimer();
	DeleteCriticalSection(&m_csTimer);
}

int CHikTimer::CloseTimerLow()
{
	if ( m_hThread )
	{
		m_nStatus = 2;
		QueueUserAPC(StopAPCProc, m_hThread, reinterpret_cast<ULONG_PTR>(this));
		WaitForSingleObject(m_hThread, INFINITE);
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
	return 0;
}

int CHikTimer::CloseTimer()
{
	int result; // eax@4

	m_nFrameCount = 0;
	if ( m_nTimerType )
	{
		if ( m_nTimerType == 1 )
			result = CloseTimerHigh();
		else if ( m_nTimerType == 2 )
			result = CloseTimerLow();
		else
			result = -2147483646;
	}
	else
	{
		result = 0;
	}
	return result;
}

int CHikTimer::CloseTimerHigh()
{
	EnterCriticalSection(&m_csTimer);
	if (m_uTimerID )
	{
		m_nStatus = 2;
		timeKillEvent(m_uTimerID);
		m_uTimerID = 0;
		--g_nHighTimerNum;
	}
	if ( !g_nHighTimerNum )
		timeEndPeriod(m_uPeriodHigh);
	LeaveCriticalSection(&m_csTimer);
	return 0;
}

int CHikTimer::Reflash()
{
	int ret; // esi@2

	EnterCriticalSection(&m_csTimer);
	if ( m_pVidRender )
		ret = m_pVidRender->RefreshDisplayWindow(0, 1);
	else
		ret = -2147483646;
	LeaveCriticalSection(&m_csTimer);
	return ret;
}

int CHikTimer::AppOperation( int a2 )
{
	if ( a2 )
	{
		switch ( a2 )
		{
		case 1:
			Pause();
			break;
		case 2:
			Resume();
			break;
		case 3:
			Stop();
			break;
		case 4:
			Close();
			break;
		case 8:
			FrameForward();
			break;
		case 10:
			TempStop();
			break;
		}
	}
	else
	{
		Play();
	}
	return 0;
}

int CHikTimer::ChangeTimerInterval( ULONG uDelay )
{
	if ( uDelay < m_uPeriodHigh )
		m_uPeriodHigh = uDelay;
	if ( m_nTimerType == 1 )
	{
		CloseTimerHigh();
		if ( CreateTimerHigh(uDelay) )
		{
			m_nTimerType = 2;
			if ( CreateTimerLow(uDelay) )
				return -2147483641;
		}
	}
	else
	{
		m_flagChangeLow = 1;
	}
	m_uPeriodLow = uDelay;
	return 0;
}

int CHikTimer::CreateTimerLow( UINT a2 )
{
	int result; // eax@2

	m_hThread = CreateThread(0, 0, WaitableTimerThread, this, 0, 0);

	if ( m_hThread )
	{
		SetThreadPriority(m_hThread, 2);
		m_nStatus = 0;
		result = 0;
	}
	else
	{
		result = -2147483641;
	}
	return result;
}

int CHikTimer::CreateTimerLow()
{
	HANDLE v2; // edi@1
	int result; // eax@8
	LARGE_INTEGER DueTime; // [sp+10h] [bp-8h]@2

	v2 = CreateWaitableTimerA(0, 0, 0);
	DueTime.QuadPart = -1;
	if ( v2 && SetWaitableTimer(v2, &DueTime, m_uPeriodLow, TimerAPCProc, this, 0))
	{
		while ( m_nStatus != 2 )
		{
			if ( m_flagChangeLow )
			{
				CancelWaitableTimer(v2);
	
				DueTime.QuadPart = -600000000i64 * m_uPeriodLow;
				if ( !SetWaitableTimer(v2, &DueTime, m_uPeriodLow, TimerAPCProc, this, 0) )
					return -2147483641;
				m_flagChangeLow = 0;
			}
			SleepEx(INFINITE, TRUE);
		}
		CancelWaitableTimer(v2);
		CloseHandle(v2);
		result = 0;
	}
	else
	{
		result = -2147483641;
	}
	return result;
}

int CHikTimer::ShouldDisplay()
{
	return m_bDisplay;
}

int CHikTimer::DisplayFrame()
{
	int ret; // eax@4

	EnterCriticalSection(&m_csTimer);

	if ( !m_bDisplayByTime )
	{
		ret = DisplayFramebyFrameRate();
	}
	else if ( m_bDisplayByTime == 1 )
	{
		ret = DisplayFramebyFrameTime();
	}
	else ret = -2147483646;
	
	LeaveCriticalSection(&m_csTimer);
	return ret;
}

int CHikTimer::DisplayFramebyFrameRate()
{
	int result; // eax@7

	int v8; // [sp+Ch] [bp-10h]@4
	int v9; // [sp+10h] [bp-Ch]@8
	int v10; // [sp+18h] [bp-4h]@8
	int v11;

	do
	{
		if ( !part31 || m_fSpeed != 1.0 || m_nTimePerFrame > 100 )
			break;

		v8 = -1;
		m_pAudRender->GetFrameCountInBuf(&v8);
		if ( !v8 )
		{
			_DebugInfo("hytest: no more audio sample to display, clear video sample\n");
			m_pVidRender->ClearVideoSample();
			m_pVidRender->RefreshDisplayWindow(0, 1);
			return -2147483646;
		}

		v10 = -1;
		m_pAudRender->GetAudioTimeStamp(&v10);
		v11 = -1;
		m_pVidRender->GetVideoTimeStamp(&v11);

		if ( v10 == -1 || v11 == -1 )
		{
			break;
		}
		if ( v11 - v10 <= 200 )
		{
			while ( v10 - v11 > 200 && m_nStatus != 2 )
			{
				_DebugInfo("hytest: video slower than audio, a/v = %d/%d\n",v10,v11);
				if ( m_pVidRender->DisplayOneFrame(m_sIVSInfo, &part28, &m_nDataNodeCount) )
					return -2147483646;
				m_pAudRender->GetAudioTimeStamp(&v10);
				m_pVidRender->GetVideoTimeStamp(&v11);
			}
			break;
		}
		_DebugInfo("hytest: audio slower than video, a/v = %d/%d\n",v10,v11);
		m_pAudRender->ClearAudio(m_pAudRender);
		m_pVidRender->RefreshDisplayWindow(0, 1);
		return -2147483646;
	}while(0);

	v8 = m_pVidRender->DisplayOneFrame(m_sIVSInfo, &part28, &m_nDataNodeCount);
	v9 = part28 + m_nDataNodeCount;
	v11 = 0;
	if ( m_nStreamMode
		|| part28 > 1
		&& (double)part28 / (double)v9 > 0.2 )
		result = v8;
	else
		result = m_pVidRender->DisplayOneFrame(m_sIVSInfo,&part28,&m_nDataNodeCount);
	return result;
}

int CHikTimer::DisplayFramebyFrameTime()
{
	int result;

	++m_nFrameCount;

	if ( m_pVidRender->GetOneFrameNeedDisplay(&m_nFrameCount, 10, m_fSpeed) )
	{
		result = m_pVidRender->DisplayOneFrame(m_sIVSInfo, &part28, &m_nDataNodeCount);
	}
	else
	{
		m_pVidRender->RefreshDisplayWindow(0, 1);
		result = -2147483646;
	}
	return result;
}

int CHikTimer::CreateTimerHigh( UINT a2 )
{
	int v4; // esi@3
	int v5;
	int v6;
	timecaps_tag ptc; // [sp+8h] [bp-8h]@2

	EnterCriticalSection(&m_csTimer);
	do 
	{
		if ( !g_nHighTimerNum )
		{
			if ( timeGetDevCaps(&ptc, 8) )
			{
				v4 = -2147483641;
				break;
			}
			v5 = m_uPeriodDef;
			v6 = ptc.wPeriodMin;
			if ( ptc.wPeriodMin <= v5 )
				v6 = m_uPeriodDef;
			if ( v6 >= ptc.wPeriodMax )
			{
				v5 = ptc.wPeriodMax;
			}
			else
			{
				if ( ptc.wPeriodMin > v5 )
					v5 = ptc.wPeriodMin;
			}
			m_uPeriodHigh = v5;
			if ( timeBeginPeriod(v5) )
			{
				v4 = -2147483641;
				break;
			}
		}
		m_uTimerID = timeSetEvent(a2, m_uPeriodHigh, DisplayTimerThread, (DWORD_PTR)this, 1);
		if ( m_uTimerID )
		{
			++g_nHighTimerNum;
			m_nStatus = 0;
			v4 = 0;
		}
		else
		{
			v4 = -2147483641;
		}
	} while (0);
	LeaveCriticalSection(&m_csTimer);
	return v4;
}

int CHikTimer::Pause()
{
	m_bDisplay = 0;
	m_nStatus = 1;
	return 0;
}

int CHikTimer::Play()
{
	CreateTimer();
	m_nStatus = 0;
	m_bDisplay = 1;
	return 0;
}

int CHikTimer::CreateTimer()
{
	CloseTimer();
	if ( m_bDisplayByTime == 1 )
	{
		m_uPeriodLow = 10;
		m_nTimePerFrame = 10;
	}

	if ( m_nTimerType )
	{
		if ( m_nTimerType == 1 )
		{
			if ( CreateTimerHigh(m_nTimePerFrame) )
			{
				m_nTimerType = 2;
				return CreateTimerLow(m_nTimePerFrame);
			}		
		}
		else if (m_nTimerType == 2 )
			return CreateTimerLow(m_nTimePerFrame);
		else
			return -2147483632;
	
	}
	return 0;
}

int CHikTimer::Resume()
{
	m_nStatus = 0;
	m_bDisplay = 1;
	return 0;
}

int CHikTimer::Stop()
{
	m_nStatus = 2;
	CloseTimer();
	m_bDisplay = 0;
	m_fSpeed = 1.0;
	m_uPeriodLow = 40;
	m_nTimePerFrame = 40;
	m_nDataNodeCount = 0;
	part28 = 0;
	return 0;
}

int CHikTimer::Close()
{
	CloseTimer();
	m_bDisplay = 0;
	m_nStatus = 3;
	return 0;
}

int CHikTimer::FrameForward()
{
	m_bDisplay = 1;
	DisplayFrame();
	return 0;
}

int CHikTimer::TempStop()
{
	m_bDisplay = 0;
	m_nStatus = 6;
	return 0;
}

int CHikTimer::CreateTimerNull()
{
	return 0;
}

int CHikTimer::FrameBack( ULONG a2 )
{
	int result;

	if ( m_pVidRender )
		result = m_pVidRender->BackDisplayOneFrame(a2, m_sIVSInfo);
	else
		result = -2147483646;
	return result;
}

int CHikTimer::GetBackFrameNum( ULONG *a2 )
{
	int result; // eax@3

	if ( a2 )
	{
		if ( m_sIVSInfo[2] < 1 )
		{
			result = -2147483642;
		}
		else
		{
			*a2 = m_sIVSInfo[2] - 1;
			result = 0;
		}
	}
	else
	{
		result = -2147483646;
	}
	return result;
}

int CHikTimer::GetDataNodeCount( ULONG *a2 )
{
	int result; // eax@2

	if ( a2 )
	{
		*a2 = m_nDataNodeCount;
		result = 0;
	}
	else
	{
		result = -2147483645;
	}
	return result;
}

int CHikTimer::GetTimerType( ULONG *a2 )
{
	int result; // eax@2

	if ( a2 )
	{
		*a2 = m_nTimerType;
		result = 0;
	}
	else
	{
		result = -2147483645;
	}
	return result;
}

int CHikTimer::InitTimer()
{
	return 0;
}

int CHikTimer::ReTryFrameBack( ULONG a2 )
{
	return FrameBack(a2);
}

int CHikTimer::SetDisplayMode( ULONG a2 )
{
	int result; // eax@4

	if ( m_hThread || m_uTimerID )
	{
		result = -2147483646;
	}
	else
	{
		if ( a2 > 1 )
		{
			result = -2147483645;
		}
		else
		{
			m_bDisplayByTime = a2;
			result = 0;
		}
	}
	return result;
}

int CHikTimer::SetPlaySpeed( float a2 )
{
	int result; // eax@3

	if ( m_fSpeed != a2 && ( m_fSpeed = a2, m_bDisplayByTime == 0) )
		result = ChangeTimerInterval((double)m_nTimePerFrame / a2);
	else
		result = 0;
	return result;
}

void CHikTimer::SetStatus( int a2 )
{
	if ( a2 )
		m_bDisplay = 0;
	else
		m_bDisplay = 1;
}

int CHikTimer::SetStreamMode( ULONG a2 )
{
	int result; // eax@2

	if ( a2 > 1 )
	{
		result = -2147483645;
	}
	else
	{
		m_nStreamMode = a2;
		result = 0;
	}
	return result;
}

int CHikTimer::SetTimePerFrame( ULONG a2 )
{
	int result; // eax@3

	if ( m_nTimePerFrame != a2 && (m_nTimePerFrame = a2,m_bDisplayByTime == 0) )
		result = ChangeTimerInterval((double)a2 / m_fSpeed);
	else
		result = 0;
	return result;
}

int CHikTimer::SetTimerType( ULONG a2 )
{
	int result; // eax@2

	if ( a2 <= 2 )
	{
		if ( m_hThread || m_uTimerID )
		{
			result = -2147483646;
		}
		else
		{
			if ( a2 != 1 || g_nHighTimerNum != 16 )
			{
				m_nTimerType = a2;
				result = 0;
			}
			else
			{
				result = -2147483645;
			}
		}
	}
	else
	{
		result = -2147483642;
	}
	return result;
}

int CHikTimer::SyncToAudio( int a1 )
{
	return -2147483632;
}

int CHikTimer::TryFrameBack( int a1 )
{
	return -2147483646;
}

