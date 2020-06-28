#pragma once

class CMediaManager;
class CVideoRenderer;
class CAudioRenderer;

class CHikTimer
{
public:
	CHikTimer(CMediaManager* a2,CVideoRenderer* a3,CAudioRenderer* a4);
	~CHikTimer(void);
	int AppOperation(int a2);
	int ChangeTimerInterval(ULONG uDelay);
	int Close();
	int CloseTimer();
	int CloseTimerHigh();
	int CloseTimerLow();
	int CreateTimer();
	int CreateTimerHigh(UINT a2);
	int CreateTimerLow(UINT a2);
	int CreateTimerLow();
	int CreateTimerNull();
	int DisplayFrame();
	int DisplayFramebyFrameRate();
	int DisplayFramebyFrameTime();
	int FrameBack(ULONG a2);
	int FrameForward();
	int GetBackFrameNum(ULONG *a2);
	int GetDataNodeCount(ULONG *a2);
	int GetTimerType(ULONG *a2);
	static int InitTimer();
	int Pause();
	int Play();
	int ReTryFrameBack(ULONG a2);
	int Reflash();
	int Resume();
	int SetDisplayMode(ULONG a2);
	int SetPlaySpeed(float a2);
	void SetStatus(int a2);
	int SetStreamMode(ULONG a2);
	int SetTimePerFrame(ULONG a2);
	int SetTimerType(ULONG a2);
	int ShouldDisplay();
	int Stop();
	static int SyncToAudio(int a1);
	int TempStop();
	static int TryFrameBack(int a1);

protected:
	CVideoRenderer* m_pVidRender;
	CAudioRenderer* m_pAudRender;
	int m_uPeriodDef;
	int m_uPeriodHigh;
	int m_uPeriodLow;
	int m_uTimerID;
	int m_nStatus;
	int m_nTimePerFrame;
	float m_fSpeed;
	IVSPLAY_FRAME_INFO m_sIVSInfo;
	HANDLE m_hThread;
	int m_flagChangeLow;
	ULONG part28;
	ULONG m_nDataNodeCount;
	int m_bDisplay;
	int part31;
	CRITICAL_SECTION m_csTimer;
	int m_bDisplayByTime;
	CMediaManager* m_pMediaManager;
	int m_nTimerType;
	int m_nStreamMode;
	int part42;
	__int64 m_nFrameCount;
};
