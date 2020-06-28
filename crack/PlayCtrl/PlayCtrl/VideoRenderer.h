#pragma once

class CMediaManager;
class CHikVRenderer;

class CVideoRenderer
{
public:
	CVideoRenderer(CMediaManager *a2);
	~CVideoRenderer(void);
	int AppOperation(int a2);
	int BackDisplayOneFrame(ULONG a2,IVSPLAY_FRAME_INFO *a3);
	int ClearVideoSample();
	int DisableDisplayWindow(ULONG a2);
	int DisableIVS();
	int Disconnect();
	int DisplayOneFrame(IVSPLAY_FRAME_INFO *a2,ULONG* a3,ULONG *a4);
	static int EnableDisplayDevice(ULONG a2,ULONG a3);
	int EnableDisplayWindow(ULONG a2,HWND a3,RECT *a4);
	int EnableIVS();
	int FPSChangeCB(ULONG a2);
	int GetBMP(char *a2);
	int GetBMPData(BYTE *a2,ULONG a3,ULONG *a4);
	int GetCurrentFrameInfo(IVSPLAY_FRAME_INFO *a2);
	static int GetDecodedFrameNum(ULONG *a2);
	int GetDisplayEffect(ULONG a2,ULONG a3,ULONG *a4);
	int GetInput(CHikVRInput* *a2);
	int GetJPEG(char *a2,ULONG a3);
	int GetJPEGData(BYTE *a2,ULONG a3,ULONG *a4,ULONG a5);
	int GetOneFrameNeedDisplay(__int64 *a2 ,ULONG a3,float a4);
	int GetOverlayFlipMode(ULONG a2,int *a3,ULONG *a4);
	int GetOverlayMode(ULONG a2,int *a3,ULONG *a4);
	int GetVideoAdjustPara(ULONG a2,ULONG a3,ULONG *a4);
	int GetVideoTimeStamp(ULONG *a2);
	void InitMember();
	int IsInit();
	int InitVR();
	int RefreshDisplayWindow(ULONG a2,int a3);
	int RegisterDimChangeCallBack(CB_DimChange a2,ULONG a3);
	int RegisterHDCCallBack(ULONG a2,CB_HDC a3,ULONG a4);
	int RegisterPlayEndCallBack(CB_PlayEnd a2,ULONG a3);
	int RegisterVideoDisplayCallBack(ULONG a2,CB_Display2 a3,ULONG a4);
	void ReleaseVR();
	int SetCallBack();
	int SetDisplayEffect(ULONG a2,ULONG a3,ULONG a4);
	int SetDisplayHwnd(HWND hWnd);
	int SetFilePara(ULONG a2,ULONG a3);
	int SetHikImage(CHikImage *a2);
	int SetInputSample(CHikSample *a2);
	int SetOverlayFlipMode(ULONG a2,int a3,ULONG a4);
	int SetOverlayMode(ULONG a2,int a3,ULONG a4);
	int SetPlaySpeed(float a2);
	int SetStartFrameNum(ULONG a2);
	int SetVideoAdjustPara(ULONG a2,ULONG a3,ULONG a4);

protected:
	CB_Display2 m_cbDisplay;
	CB_PlayEnd m_cbPlayEnd;
	CB_DimChange m_cbDimChange;
	CB_HDC m_cbHDC;
	CMediaManager* m_pMediaManager;
	CHikVRenderer* m_cTmpl;
	int m_bHDCisSet[4];
	int m_nUserForHDC[4];
	int part15;
	int part16;
	int part17;
	int part18;
	int part19;
	int m_nUserForDimChange;
	int part21;
	int m_nUserForPlayEnd;
	int m_nUserForDisplay;
	int m_bIsInit;
	int part25;
	int m_FilePara1;
	int m_FilePara2;
	int m_bflagPlayEnd;
};
