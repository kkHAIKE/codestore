#pragma once

class CHikVRInput;
class CHikSample;

class CHikVRenderer:public IHikVideoRenderer
{
public:
	CHikVRenderer(void);
	~CHikVRenderer(void);

	int BackDisplayOneFrame(ULONG a2,IVSPLAY_FRAME_INFO *a3);
	int ClearVideoSample();
	int Close();
	int DirectlyDisplay(BYTE* a2,ULONG a3,DISPLAY_PARA *Dst);
	int DisableDisplayWindow(ULONG a2);
	int DisableIVS();
	int GetDisplayPara(BYTE *Src,DISPLAY_PARA* Dst);
	int Display(BYTE* Src,ULONG a3,BYTE* a4,ULONG a5,IVSPLAY_FRAME_INFO* Dst);
	int Operation(int a2);
	int SetPlaySpeed(float a2);
	int GetInput(IHikInput **a2);
	int InitVideoRenderer();
	int DisplayOneFrame(IVSPLAY_FRAME_INFO *a2,ULONG *a3,ULONG *a4);
	int EnableDisplayWindow(ULONG a2,HWND a3,RECT *a4);
	int RefreshDisplayWindow(ULONG a2,int a3);
	int DisplayPicture(BYTE* a2,ULONG a3,BYTE* a4,ULONG a5);
	int SetDisplayEffect(ULONG a2,ULONG a3,ULONG a4);
	int GetDisplayEffect(ULONG a2,ULONG a3,ULONG *a4);
	static int EnableDisplayDevice(ULONG a2,ULONG a3);
	int SetHikImage(CHikImage *a2);
	int SetStartFrame(ULONG a2);
	int SetOverlayFlipMode(ULONG a2,int a3,ULONG a4);
	int GetOverlayFlipMode(ULONG a2,int *a3,ULONG *a4);
	int SetOverlayMode(ULONG a2,int a3,ULONG a4);
	int GetOverlayMode(ULONG a2,int *a3,ULONG *a4);
	int SetFPSChangeCB(CB_FPSChange a2,ULONG a3);
	int SetPlayEndCB(CB_PlayEnd a2,ULONG a3);
	int SetDisplayCB(ULONG a2,CB_Display2 a3,ULONG a4);
	int SetDimChangeCB(CB_DimChange a2,ULONG a3);
	int SetHDCCB(ULONG a2,CB_HDC a3,ULONG a4);
	int SetVideoAdjustPara(ULONG a2,ULONG a3,ULONG a4);
	int GetVideoAdjustPara(ULONG a2,ULONG a3,ULONG *a4);
	int IsTimerNull(IVSPLAY_FRAME_INFO *a2);
	int GetOneFrameNeedDisplay(__int64 *a2,ULONG a3,float a4);
	int EnableIVS();
	int SetPos();
	int GetVideoTimeStamp(ULONG *a2);
	int GetCurrentFrameInfo(IVSPLAY_FRAME_INFO *a2);
	int GetJPEGData(BYTE *a2,ULONG a3,ULONG *a4,ULONG a5);
	int GetBMPData(BYTE *a2,ULONG a3,ULONG *a4);
	int GetJPEG(char *a2,ULONG a3);
	int GetBMP(char *a2);
	int SetInputSample(CHikSample *a2);
	int SetDisplayEngine(ULONG a2);
	int NeedAdjustFrameRate(float a2);

	static int InitHikD3D();
	static int InitHikDDraw();
	static int TempStop();
	static int Resume();
	static int Pause();
	int FrameForward();
	int FrameBack();
	int Play();
	int Stop();

protected:
	CB_Display2 m_cbDisplay;
	CB_PlayEnd m_cbPlayEnd;
	CB_DimChange m_cbDimChange;
	CB_FPSChange m_cbFPSChange;
	CB_HDC m_cbHDC;
	CHikVRInput* m_pVRInput;
	void* m_part8[4];
	float m_fSpeed;
	int m_part13;
	IVSPLAY_FRAME_INFO m_sIVSInfo;
	void* m_part30[4];
	int m_part34;
	int m_part35;
	int m_part36;
	int m_part37;
	int m_part38;
	ULONG m_nStartFrame;
	int m_part40;
	int m_part41;
	int m_nUserForDimChange;
	int m_nUserForPlayEnd;
	int m_nUserForDisplay;
	int m_nUserForFPSChange;
	int m_bHDCisSet[4];
	int m_nUserForHDC[4];
	ULONG m_nDisplayEngine;
	int m_part55;
	int m_part56;
	CHikSample* m_pSample;
	int m_part58;
	ULONG m_part59;
	ULONG m_part60;
};
