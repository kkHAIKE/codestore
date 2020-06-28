#pragma once

class CHikVDec;
class CHikADec;
class CHikTimer;
class CAudioRenderer;
class CVideoRenderer;
class CHikVideoTransform;
class CHikPDec;
class CHikDemux;
class CHikSource;
class CHikImage;

class CMediaManager
{
public:
	CMediaManager(void);
	~CMediaManager(void);

	int AdjustWaveAudio(long a2);
	int AftSetPos(int a2);
	int AnalyzeFile(LPCSTR a2,IVSPLAY_MEDIA_INFO* a3);
	int Initial();
	void Release();
	void DeConstructAll();
	int CloseFile();
	int CloseStream();
	int TryClose();
	int TryFast();
	int Stop();
	int Close();
	int DisconnectAll();
	int ResetBuffer(ULONG a2);
	int SetPlaySpeed(float a2);
	int VenderIVS(int a2);
	int Resume();
	int Play();

protected:
	CHikSource* m_cSource;
	CHikDemux* m_cDemux;
	CHikVDec* m_cVDec;
	CHikADec* m_cADec;
	CHikPDec* m_cPDec;
	CVideoRenderer* m_cVidRender;
	CAudioRenderer* m_cAudRender;
	CHikVideoTransform* m_cVidTrans;
	CHikTimer* m_cTimer;
	int m_bIsFile;
	float part11;
	BYTE part12;
	int part13[9];
	CHikImage* m_cImage;
	int part23;
	int part24;
	int part25;
	int part26;
	int m_nStatus;
	int part28;
	int part29;
	int part30;
	int part31;
	int part32;
	int part33;
	int part34[5];
	int part39[10];
	void* part49;
	int part50;
	int part51;
};
