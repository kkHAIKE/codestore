#pragma once

class CMediaManager;

class CPlayControl
{
public:
	CPlayControl(void);
	~CPlayControl(void);

	int AdjustWaveAudio(long a2);
	int JudgeRet(long a2);
	int ConvertErrorCode(long a2);
	int CheckDiscontinuousFrameNum(int a2);
	void Close();
	int CloseFile();
	int CloseStream();
	int CloseStreamEx();
	int CreateManager();
	int SetTimerType(ULONG a2,ULONG a3);
	void DealADecCB(IVSPLAY_DECDATA_INFO *a2);
	void DealVDecCB(IVSPLAY_DECDATA_INFO *a2);
	void DealWatermarkCB(IVSPLAY_DECDATA_INFO *a2);
	void DisplayCB(IVSPLAY_FRAME_INFO *a2);
	void DrawFun(ULONG a2, HDC a3, IVSPLAY_FRAME_INFO *a4);
	int EnableDoubleFrame(ULONG a2);
	int EnableIVS(int a2);
	void EncChangeCB();
	int Fast();
	void FileIndexDone();
	int GetBMP(BYTE *a2, ULONG a3, ULONG *a4);
	int GetBufferValue(ULONG a2);
	int GetColor(ULONG a2, int *a3, int *a4, int *a5, int *a6);
	int GetColorKey();
	int GetCurrentFrameNum();
	int GetCurrentFrameRate();
	static int GetDeviceCaps(ULONG a1);
	int GetDisplayBuf();
	int GetDisplayType();
	int GetFileSpecialAttr(ULONG *,ULONG *,ULONG *);
	DWORD GetFileTime();
	int GetFileTimeEx(ULONG *a2,ULONG *a3,ULONG *a4);
	int GetFileTotalFrames();
	int GetJPEG(BYTE *a2,ULONG a3,ULONG *a4);
	int GetKeyFramePos(ULONG a2,ULONG a3,FRAME_POS *a4);
	static bool GetMonitorDeviceInfo(ULONG a1,char* Dest,ULONG a3,char *a4,ULONG a5,HMONITOR a6);
	int GetMonitorDevicesNum();
	int GetNextKeyFramePos(ULONG a2,ULONG a3,FRAME_POS *a4);
	int GetOverlayMode();
	int GetPictureQuality(int *a2);
	int GetPictureSize(long *a2,long *a3);
	double GetPlayPos();
	int GetPlayedFrames();
	int SetDecCallBack(CB_DEC cb,long a3,int a4);
	int SetDecCallBackEx(CB_DEC cb,char* a3,long a4,long a5);

protected:
	int part1;
	CB_EncChange m_cbEncChange;
	CB_Display m_cbDisplay;
	CB_DisplayEx m_cbDisplayEx;
	CB_FileDone m_cbFileDone;
	CB_DrawFun m_cbDrawFun;
	CB_DEC m_cbDec;
	int part8;
	CB_CWM m_cbCWm;
	int part10;
	int m_iWidth;
	int m_iHeight;
	int m_nPort;
	int part14;
	int part15;
	int nUserForFileDone;
	int nUserForDrawFun;
	int part18;
	int nUserForDisplay;
	int nUserForEncChange;
	int nUserForCWM;
	int part22;
	int part23;
	int part24;
	HWND m_hWnd;
	int m_idMsgForPort;
	int part27;
	int part28;
	int part29;
	int part30;
	CMediaManager* m_pMediaManager;
	int m_nTotalFrm;
	int part33;
	int part34;
	int part35;
	int part36;
	int part37;
	int part38;
	int part39;
	int part40;
	int part41;
	int part42;
	int part43;
	int part44;
	int part45;
	int part46;
	int part47;
	int part48;
	int part49;
	int part50;
	int part51;
	int part52;
	int part53;
	int part54;
	int part55;
	int part56;
	int part57;

	void* part58;
	void* part59;
	void* part60;
	void* part61;

	int m_iError;
	int m_nUserForDec;
	int part64;
	int part65;
	int part66;
};
