#pragma once

class CHikSample;
class IHikInput
{
	virtual int InputData(BYTE *,ULONG,ULONG)=0;
	virtual int SetInputSample(CHikSample *)=0;
	virtual ~IHikInput()=0;
};
class IHikOutput
{
	virtual int SetConnectedInput(IHikInput *)=0;
	virtual int CreateSample(CHikSample * *)=0;
	virtual int ConfigSample(ULONG,ULONG)=0;
	virtual int GetSample(CHikSample * *)=0;
	virtual ~IHikOutput()=0;
};
class CHikImage;

class IHikVideoDecoder
{
public:
	virtual ~IHikVideoDecoder(void)=0;
	int	InitVideoDecoder()=0;
	int	Operation(int)=0;
	int	SetPlaySpeed(float)=0;
	int	GetInput(IHikInput * *)=0;
	int	GetOutput(IHikOutput * *)=0;
	int	SetDetectWatermark(int)=0;
	int	SetBDecodeNum(ULONG)=0;
	int	SetVideoPostProcess(ULONG,ULONG)=0;
	int	GetVideoPostProcess(ULONG,ULONG *)=0;
	int	SetAimFrame(ULONG,ULONG)=0;
	int	SetVDecCBType(ULONG)=0;
	int	InformNoDisplay(int)=0;
	int	SetHikImage(CHikImage *)=0;
	int	SetDecodeType(ULONG)=0;
	int	CheckErrFrame(int)=0;
	int	SetTargetFrameCB(CB_TargetFrame,ULONG)=0;
	int	SetVDecCB(CB_Dec2,ULONG)=0;
	int	GetCurrentFrameNum(ULONG *)=0;
	int	GetVideoDecCBType(ULONG *)=0;
};

class IHikVideoRenderer
{
public:
	virtual ~IHikVideoRenderer(void)=0;
	virtual int Operation(int a2)=0;
	virtual int SetPlaySpeed(float a2)=0;
	virtual int GetInput(IHikInput **a2)=0;
	virtual int InitVideoRenderer();
	virtual int DisplayOneFrame(IVSPLAY_FRAME_INFO *a2,ULONG *a3,ULONG *a4)=0;
	virtual int EnableDisplayWindow(ULONG a2,HWND a3,RECT *a4)=0;
	virtual int DisableDisplayWindow(ULONG a2)=0;
	virtual int RefreshDisplayWindow(ULONG a2,int a3)=0;
	virtual int BackDisplayOneFrame(ULONG a2,IVSPLAY_FRAME_INFO *a3)=0;
	virtual int SetDisplayEffect(ULONG a2,ULONG a3,ULONG a4)=0;
	virtual int GetDisplayEffect(ULONG a2,ULONG a3,ULONG *a4)=0;
	virtual int EnableDisplayDevice(ULONG a2,ULONG a3)=0;
	virtual int SetHikImage(CHikImage *a2)=0;
	virtual int SetStartFrame(ULONG a2)=0;
	virtual int SetOverlayFlipMode(ULONG a2,int a3,ULONG a4)=0;
	virtual int GetOverlayFlipMode(ULONG a2,int *a3,ULONG *a4)=0;
	virtual int SetOverlayMode(ULONG a2,int a3,ULONG a4)=0;
	virtual int GetOverlayMode(ULONG a2,int *a3,ULONG *a4)=0;
	virtual int SetFPSChangeCB(CB_FPSChange a2,ULONG a3)=0;
	virtual int SetPlayEndCB(CB_PlayEnd a2,ULONG a3)=0;
	virtual int SetDisplayCB(ULONG a2,CB_Display2 a3,ULONG a4)=0;
	virtual int SetDimChangeCB(CB_DimChange a2,ULONG a3)=0;
	virtual int SetHDCCB(ULONG a2,CB_HDC a3,ULONG a4)=0;
	virtual int SetVideoAdjustPara(ULONG a2,ULONG a3,ULONG a4)=0;
	virtual int GetVideoAdjustPara(ULONG a2,ULONG a3,ULONG *a4)=0;
	virtual int IsTimerNull(IVSPLAY_FRAME_INFO *a2)=0;
	virtual int GetOneFrameNeedDisplay(__int64 *a2,ULONG a3,float a4)=0;
	virtual int EnableIVS()=0;
	virtual int DisableIVS()=0;
	virtual int GetVideoTimeStamp(ULONG *a2)=0;
	virtual int ClearVideoSample()=0;
	virtual int GetCurrentFrameInfo(IVSPLAY_FRAME_INFO *a2)=0;
	virtual int GetJPEGData(BYTE *a2,ULONG a3,ULONG *a4,ULONG a5)=0;
	virtual int GetBMPData(BYTE *a2,ULONG a3,ULONG *a4)=0;
	virtual int GetJPEG(char *a2,ULONG a3)=0;
	virtual int GetBMP(char *a2)=0;
	virtual int SetInputSample(CHikSample *a2)=0;
};

class IHikVideoTransform
{
public:
	virtual ~IHikVideoTransform()=0;
	virtual int InitVideoTransform(void)=0;
	virtual int	SetDisplayBufCount(ULONG)=0;
	virtual int	GetDisplayBufCount(ULONG *)=0;
	virtual int	ResetDisplayBuffer(void)=0;
	virtual int	Operation(int)=0;
	virtual int	SetPlaySpeed(float)=0;
	virtual int	GetInput(ULONG,IHikInput **)=0;
	virtual int	GetOutput(IHikOutput **)=0;
	virtual int	SetHikImage(CHikImage *)=0;
	virtual int	SetColorSpace(ULONG)=0;
	virtual int	GetDataNodeCount(ULONG *)=0;
	virtual int	SetTimerType(ULONG)=0;
	virtual int	EnableIVS(void)=0;
	virtual int	DisableIVS(void)=0;
	virtual int	SetVideoSyncBuf(ULONG)=0;
	virtual int	SetIVSSyncBuf(ULONG)=0;
	virtual int	EnableDoubleFrame(ULONG)=0;
	virtual int	SetDeinterlaceType(ULONG)=0;
};

class IHikAudioDecoder
{
public:
	virtual ~IHikAudioDecoder()=0;
	virtual int	Operation(int)=0;
	virtual int	SetPlaySpeed(float)=0;
	virtual int	InitAudioDecoder(void)=0;
	virtual int	GetInput(IHikInput * *)=0;
	virtual int	GetOutput(IHikOutput * *)=0;
	virtual int	SetADecCBType(ULONG)=0;
	virtual int	SetADecCB(CB_Dec2,ULONG)=0;
	virtual int	SetStreamType(ULONG)=0;
	virtual int	InformNoDisplay(int)=0;
};

class IHikAudioRenderer
{
public:
	virtual ~IHikAudioRenderer()=0;
	virtual int Operation(int)=0;
	virtual int	SetPlaySpeed(float)=0;
	virtual int	GetInput(IHikInput * *)=0;
	virtual int	InitAudioRenderer(void)=0;
	virtual int	SetVolume(ULONG)=0;
	virtual int	GetVolume(ULONG *)=0;
	virtual int	SetPlayBufCount(ULONG)=0;
	virtual int	GetPlayBufCount(ULONG *)=0;
	virtual int	ResetPlayBuf(void)=0;
	virtual int	GetFrameCountInBuf(ULONG *)=0;
	virtual int	GetAudioTimeStamp(ULONG *)=0;
	virtual int	ClearAudio(void)=0;
	virtual int	AdjustWaveAudio(long)=0;
	virtual int	GetCurrentFrameInfo(IVSPLAY_FRAME_INFO *)=0;
	virtual int	SetHWND(HWND)=0;
};
class IHikSource
{
public:
	virtual ~IHikSource();
	virtual int GetOutputCount(ULONG *)=0;
	virtual int Operation(int)=0;
	virtual int SetPlaySpeed(float)=0;
	virtual int OpenFile(char const *,IVSPLAY_FILE_INFO *)=0;
	virtual int CloseFile(void)=0;
	virtual int OpenStream(IVSPLAY_OPENSTREAM_PARA *)=0;
	virtual int CloseStream(void)=0;
	virtual int GetOutput(ULONG,IHikOutput * *)=0;
	virtual int InputData(BYTE *,ULONG)=0;
	virtual int InputVideoData(BYTE *,ULONG)=0;
	virtual int InputAudioData(BYTE *,ULONG=0;
	virtual int SetPosByFilePos(float)=0;
	virtual int SetPosByFrameNum(ULONG)=0;
	virtual int SetPosByFrameTime(ULONG)=0;
	virtual int GetFileIndex(BYTE *,ULONG *)=0;
	virtual int SetFileIndex(BYTE *,ULONG)=0;
	virtual int ResetSourceBuf(ULONG)=0;
	virtual int GetSrcBufSize(ULONG,ULONG *)=0;
	virtual int GetKeyFrameInfo(ULONG,ULONG *)=0;
	virtual int GetFileIndexStatus(ULONG *)=0;
	virtual int RegisterFileEndCallBack(void (*)(ULONG),ULONG)=0;
	virtual int RegisterFileIndexCallBack(void (*)(ULONG),ULONG)=0;
	virtual int RegisterSrcBufCallBack(void (*)(ULONG,ULONG),ULONG,ULONG)=0;
	virtual int IsFileEnd(void)=0;
	virtual int GetKeyFramePos(ULONG,ULONG,KEYFRAME_NODE *)=0;
	virtual int GetNextKeyFramePos(ULONG,ULONG,KEYFRAME_NODE *)=0;
	virtual int ResetSourceBufFlag(void)=0;
	virtual int GetFileTime(IVSPLAY_FILE_INFO *)=0;
	virtual int ResetSourceInfo(BYTE *)=0;
	virtual int GetPlayPos(void)=0;
};
