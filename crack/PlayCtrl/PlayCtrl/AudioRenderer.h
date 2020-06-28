#pragma once

class CAudioRenderer
{
public:
	CAudioRenderer(void);
	~CAudioRenderer(void);

	int AdjustWaveAudio(LONG a2);
	int AppOperation(int a2);
	int ClearAudio();
	static void Disconnect();
	int GetAudioTimeStamp(ULONG *a2);
	int GetCurrentFrameInfo(IVSPLAY_FRAME_INFO* a2);
	int GetFrameCountInBuf(ULONG *a2);
	int GetInput(IHikInput** a2);
	int GetPlayBufCount(ULONG *a2);
	int GetVolume(ULONG *a2);
	int InitAR();
	void InitMember();
	int IsInit();
	void ReleaseAR();
	int ResetPlayBuffer();
	int SetHWND(HWND a2);
	int SetPlayBufCount(ULONG a2);
	int SetPlaySpeed(float a2);
	int SetVolume(ULONG a2);

protected:
	int m_bIsInit;
	IHikAudioRenderer* m_cTmpl;
};
