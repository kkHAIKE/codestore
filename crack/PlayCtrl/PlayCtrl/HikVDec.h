#pragma once

class CMediaManager;
class IHikVideoDecoder;
class IHikInput;
class IHikOutput;
class CHikImage;

class CHikVDec
{
public:
	CHikVDec(CMediaManager* a2);
	~CHikVDec(void);
	
	int AppOperation(int a2);
	int CheckErrFrame(int a2);
	int Disconnect();
	int GetCurrentFrameNum(ULONG *a2);
	int	GetInput(IHikInput * *a2);
	int	GetOutput(IHikOutput * *a2);
	int GetVideoDecCBType(ULONG *a2);
	int GetVideoPostProcess(ULONG a2,ULONG* a3);
	int InformNoDisplay(int a2);
	void InitMember();
	int InitVDec(ULONG a2);
	int IsInit();
	int RegisterVideoDecCallBack(CB_Dec2 a2,ULONG a3);
	void ReleaseVDec();
	int SetAimFrame(ULONG a2,ULONG a3);
	int SetCallBack();
	int SetHikImage(CHikImage* a2);
	int SetPlaySpeed(float a2);
	int SetVideoDecCBType(ULONG a2);
	int SetVideoDecodeType(ULONG a2);
	int SetVideoPostProcess(ULONG a2,ULONG a3);
	int SkipBFrameNum(ULONG a2);
	int TargetFrameArrived();

protected:
	CB_Dec2 m_cbDec;
	CMediaManager* m_pMediaManager;
	IHikVideoDecoder* m_pVidDecoder;
	int m_bIsInit;
	int m_nUserForDec;
	int m_bInformNoDisplay;
	int m_nSkipB;
	int m_nDecCBType;
};
