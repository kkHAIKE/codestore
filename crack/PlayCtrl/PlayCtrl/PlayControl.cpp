3#include "StdAfx.h"
#include "PlayControl.h"

extern int g_lJpegQuality;

CPlayControl::CPlayControl(void)
{ 
	m_pMediaManager = NULL;
	part58 = NULL;
	part59 = NULL;
	part60 = NULL;
	part61 = NULL;
	part32 = -1;
	part2 = 0;
	part6 = 0;
	part3 = 0;
	part5 = 0;
	part7 = 0;
	part8 = 0;
	part10 = 0;
	part1 = 0;
	part4 = 0;
	part16 = 0;
	part17 = 0;
	part18 = 0;
	part19 = 0;
	part20 = 0;
	part63 = 0;
	part22 = 0;
	part23 = 0;
	part24 = 0;
	part25 = 0;
	part26 = 0;
	part27 = 0;
	part28 = 0;
	part29 = 0;
	part30 = 0;
	m_iWidth = 352;
	m_iHeight = 288;
	part14 = 0;
	part15 = 3;
	m_iError = 0;
	part64 = 0;
	part65 = 0;
	part66 = 0;
}

CPlayControl::~CPlayControl(void)
{
	if(part58)
	{delete part58;part58=NULL;}
	if(part59)
	{delete part58;part58=NULL;}
	if(part60)
	{delete part58;part58=NULL;}
	if(part61)
	{delete part58;part58=NULL;}

	if ( m_pMediaManager )
	{
		delete m_pMediaManager;
		m_pMediaManager=NULL;
		
	}

	part64 = 0;
	part65 = 0;
	part66 = 0;
}

int CPlayControl::AdjustWaveAudio( long a2 )
{
	int ret; // [sp-4h] [bp-8h]@2

	if ( m_pMediaManager )
		ret = m_pMediaManager->AdjustWaveAudio(a2);
	else
		ret = -2147483646;
	return JudgeRet(ret);
}

int CPlayControl::JudgeRet( long a2 )
{
	int result; // eax@2

	if ( a2 )
	{
		ConvertErrorCode(a2);
		result = 0;
	}
	else
	{
		result = 1;
	}
	return result;
}

int CPlayControl::ConvertErrorCode( long a2 )
{
	int result; // eax@1

	result = a2;
	if ( a2 > 1 )
	{
		m_iError = 99;
	}
	else
	{
		if ( a2 == 1 )
		{
			m_iError = 31;
		}
		else
		{
			result = a2 + 2147483646;
			switch ( a2 + 2147483646 )
			{
				case 1:
					m_iError = 1;
					break;
				case 2:
					m_iError = 7;
					break;
				case 6:
					m_iError = 11;
					break;
				case 0:
				case 7:
					m_iError = 2;
					break;
				case 14:
					m_iError = 16;
					break;
				case 5:
					m_iError = 6;
					break;
				case 15:
					m_iError = 9;
					break;
				case 17:
					m_iError = 4;
					break;
				case 18:
					m_iError = 5;
					break;
				case 3:
					m_iError = 17;
					break;
				case 19:
					m_iError = 33;
					break;
				default:
					m_iError = 99;
			}
		}
	}
	return result;
}

int CPlayControl::CheckDiscontinuousFrameNum( int a2 )
{
	int ret; // [sp-4h] [bp-8h]@2

	if ( m_pMediaManager )
		ret = m_pMediaManager->CheckDiscontinuousFrameNum(a2);
	else
		ret = -2147483646;
	return JudgeRet(ret);
}

void CPlayControl::Close()
{
	if(part58)
	{delete part58;part58=NULL;}
	if(part59)
	{delete part58;part58=NULL;}
	if(part60)
	{delete part58;part58=NULL;}
	if(part61)
	{delete part58;part58=NULL;}

	part2 = 0;
	part6 = 0;
	part3 = 0;
	part5 = 0;
	part7 = 0;
	part8 = 0;
	part16 = 0;
	part17 = 0;
	part18 = 0;
	part19 = 0;
	part20 = 0;
	part63 = 0;
	part24 = 0;
	part25 = 0;
	part26 = 0;
	part27 = 0;
	part28 = 0;
	part29 = 0;
	part30 = 0;
	part14 = 0;
	part65 = 0;
	part66 = 0;
	part64 = 0;
	m_iWidth = 352;
	m_iHeight = 288;
	part15 = 3;
}

int CPlayControl::CloseFile()
{
	int result; // eax@2
	int ret; // edi@3

	if ( m_pMediaManager )
	{
		ret=m_pMediaManager->CloseFile();
		Close();
		part30 = 0;
		result = JudgeRet(ret);
	}
	else
	{
		result = JudgeRet(-2147483646);
	}
	return result;
}

int CPlayControl::CloseStream()
{
	int result; // eax@2
	int ret; // edi@3

	if ( m_pMediaManager )
	{
		ret = m_pMediaManager->CloseStream();
		Close();
		result = JudgeRet(ret);
	}
	else
	{
		result = JudgeRet(-2147483646);
	}
	return result;
}

int CPlayControl::CloseStreamEx()
{
	int result; // eax@2
	int ret; // edi@3

	if ( m_pMediaManager )
	{
		ret = m_pMediaManager->CloseStream();
		Close();
		result = JudgeRet(ret);
	}
	else
	{
		result = JudgeRet(-2147483646);
	}
	return result;
}

int CPlayControl::CreateManager()
{
	try
	{
		CMediaManager *v3=new CMediaManager();
		m_pMediaManager = v3;
		if ( !v3 )
		{
			throw -2147483641;
		}
		int ret = v3->Initial();
		if ( ret )
		{
			throw ret;
		}
		return 1;
	}catch(int err)
	{
		_LOG_RECORD("CPlayControl::create manager failed!\n");
		if(m_pMediaManager)
		{delete m_pMediaManager;m_pMediaManager=NULL;}
		return JudgeRet(-2147483646);
	}
}

int CPlayControl::SetTimerType( ULONG a2,ULONG a3 )
{
	int ret; // [sp-4h] [bp-8h]@2

	if ( m_pMediaManager )
		ret = m_pMediaManager->SetTimerType(a2);
	else
		ret = -2147483646;
	return JudgeRet(ret);
}

void CPlayControl::DealADecCB( IVSPLAY_DECDATA_INFO *a2 )
{
	FRAME_INFO Dst={0}; // [sp+4h] [bp-18h]@1

	Dst.dwFrameNum = a2->def.dwFrameNum;
	Dst.nStamp = a2->def.nStamp;
	Dst.nType = a2->def.nType;
	Dst.nWidth = a2->def.nWidth;
	Dst.nHeight = a2->def.nHeight;
	Dst.nFrameRate = a2->def.nFrameRate;

	if ( m_cbDec )
		m_cbDec(m_nPort, a2->pBuf, a2->nSize, &Dst, m_nUserForDec, 0);
}


int CPlayControl::SetDecCallBack( CB_DEC cb,long a3,int a4 )
{
	DWORD a2;

	if(m_pMediaManager==NULL)
	{
		return JudgeRet(-2147483646);
	}

	m_cbDec=cb;
	m_nUser=a3;

	if(cb==NULL)
	{
		m_pMediaManager->InformNoDisplay(1);

		part64 = 0;
		
		if ( part15==1 )
		{
			m_pMediaManager->GetVideoDecCBType(&a2);
			a2& = 0xFFFFFFFE;
			m_pMediaManager->SetVideoDecCBType(a2);
			return 1;
		}
	
		if ( part15 != 2 )
		{
			if ( part15 != 3 )
			{
				return JudgeRet(-2147483645);
			}
			m_pMediaManager->GetVideoDecCBType(&a2);
			a2& = 0xFFFFFFFE;
			m_pMediaManager->SetVideoDecCBType(a2);
		}
		m_pMediaManager->RegisterAudioDecCallBack(NULL, NULL);
	}
	else
	{
		m_pMediaManager->InformNoDisplay(a4 == 0);

		part64 = 1;

		if (  part15==1 )
		{
			m_pMediaManager->GetVideoDecCBType(&a2);
			a2 |=1;
			m_pMediaManager->SetVideoDecCBType(a2);
			m_pMediaManager->RegisterVideoDecCallBack(VideoDecCallBack, (ULONG)this);
			return 1;
		}
		
		if ( part15 != 2 )
		{
			if ( part15 != 3 )
			{
				return JudgeRet(-2147483645);
			}
			m_pMediaManager->GetVideoDecCBType(&a2);
			a2 |= 1;
			m_pMediaManager->SetVideoDecCBType(a2);
			m_pMediaManager->RegisterVideoDecCallBack(VideoDecCallBack, (ULONG)this);
		}

		m_pMediaManager->RegisterAudioDecCallBack(AudioDecCallBack, (ULONG)this);
	}
	
	return 1;
}

int CPlayControl::SetDecCallBackEx( CB_DEC cb,char* a3,long a4,long a5 )
{
	return JudgeRet(-2147483632);
}

void CPlayControl::DealVDecCB( IVSPLAY_DECDATA_INFO *a2 )
{
	int v2; // edx@1
	FRAME_INFO v6={0}; // [sp+8h] [bp-18h]@1

	v6.dwFrameNum = a2->def.dwFrameNum;
	v6.nFrameRate = 1000 / a2->def.nFrameRate;
	v6.nWidth = a2->def.nWidth;
	v6.nHeight = a2->def.nHeight;
	v6.nStamp = a2->def.nStamp;
	v6.nType = a2->def.nType;
	if ( a2->def.part3 && a2->def.part4 && a2->def.part5)
		part65 = a2->def.part8 & 0x3F | ((v2 << 26) - 0x3C000001) & 0xFC000000 | ((a2->def.part7 & 0x3F | ((a2->def.part6 & 0x1F | 32 * (a2->def.part5 & 0x1F | 32 * (a2->def.part4 & 0xF))) << 6)) << 6);
	else
		part65 = 0;
	
	if ( m_cbDec )
		m_cbDec(m_nPort, a2->def.pBuf, a2->def.nSize, &v6, m_nUser, 0);
}

void CPlayControl::DealWatermarkCB( IVSPLAY_DECDATA_INFO *a2 )
{
	WATERMARK_INFO v4={0}; // [sp+0h] [bp-14h]@1

	v4.pDataBuf = a2->def.pWIDataBuf;
	v4.nSize = a2->def.nWISize;
	v4.nFrameNum = a2->def.nWIFrameNum;
	v4.nReserved = a2->def.nWIReserved;
	v4.bRsaRight =  a2->def.bWIRsaRight;
	if ( m_cbCWm )
		m_cbCWm(m_nPort, &v4, nUserForCWM);

}

void CPlayControl::DisplayCB( IVSPLAY_FRAME_INFO *a2 )
{
	DISPLAY_INFO Dst={0}; // [sp+8h] [bp-20h]@4

	if ( m_cbDisplay )
		m_cbDisplay(
		m_nPort,
		a2->dis.pBuf,
		a2->dis.nBufLen,
		a2->dis.nWidth,
		a2->dis.nHeight,
		a2->dis.nStamp,
		a2->dis.nType,
		nUserForDisplay);

	if ( m_cbDisplayEx )
	{
		Dst.nPort = m_nPort;
		Dst.pBuf = a2->dis.pBuf;
		Dst.nBufLen = a2->dis.nBufLen;
		Dst.nWidth = a2->dis.nWidth;
		Dst.nHeight = a2->dis.nHeight;
		Dst.nStamp = a2->dis.nStamp;
		Dst.nType = a2->dis.nType;
		Dst.nUser = nUserForDisplay;
		m_cbDisplayEx(&Dst);
	}
}

void CPlayControl::DrawFun( ULONG a2, HDC a3, IVSPLAY_FRAME_INFO *a4 )
{
	if(m_cbDrawFun)
		m_cbDrawFun(m_nPort,a3,nUserForDrawFun);
}

int CPlayControl::EnableDoubleFrame( ULONG a2 )
{
	int ret;

	if ( m_pMediaManager )
		ret = m_pMediaManager->EnableDoubleFrame(a2);
	else
		ret = -2147483646;
	return JudgeRet(ret);
}

int CPlayControl::EnableIVS( int a2 )
{
	int ret; // [sp-4h] [bp-8h]@5

	if ( m_pMediaManager )
	{
		if ( a2 )
			ret = m_pMediaManager->EnableIVS();
		else
			ret = m_pMediaManager->DisableIVS();
	}
	else
	{
		ret = -2147483646;
	}
	return JudgeRet(ret);
}

void CPlayControl::EncChangeCB()
{
	int v2; // ebx@2
	MSG Msg; // [sp+8h] [bp-1Ch]@3

	if ( part24 )
	{
		v2 = 0;
		do
		{
			if ( !PeekMessageA(&Msg, m_hWnd, m_idMsgForPort, m_idMsgForPort, 0) )
				break;
			if ( Msg.wParam == m_nPort )
			{
				if(m_cbEncChange)
					m_cbEncChange(m_nPort,nUserForEncChange);
				return;
			}
			++v2;
		}
		while ( v2 < 100 );
		PostMessageA(m_hWnd, m_idMsgForPort, m_nPort, 0);
	}
}

int CPlayControl::Fast()
{
	int ret;

	if ( m_pMediaManager )
		ret = m_pMediaManager->TryFast();
	else
		ret = -2147483646;
	return JudgeRet(ret);
}

void CPlayControl::FileIndexDone()
{
	if ( m_cbFileDone )
		m_cbFileDone(m_nPort, nUserForFileDone);
}

int CPlayControl::GetBMP( BYTE *a2, ULONG a3, ULONG *a4 )
{
	int ret;
	if ( a4 )
	{
		if ( m_pMediaManager )
			ret = m_pMediaManager->GetBMPData(a2, a3, a4);
		else
			ret = -2147483646;
	}
	else
	{
		ret = -2147483645;
	}
	return JudgeRet(ret);
}

int CPlayControl::GetBufferValue( ULONG a2 )
{
	int ret;
	int v6;
	ULONG v8; // [sp+4h] [bp-4h]@3

	if (m_pMediaManager==NULL)
	{
		ConvertErrorCode(-2147483646);
		return -1;
	}
	v8 = -1;
	switch ( a2 )
	{
	case 1:
		v6 = 0;
		break;
	case 2:
		v6 = 1;
		break;
	case 3:
		v6 = 6;
		break;
	default:
		if ( a2 != 4 )
		{
			ConvertErrorCode(-2147483645);
			return 0;
		}
		v6 = 7;
	}
	ret = m_pMediaManager->GetBufferSize(v6,&v8);
	if ( ret )
	{
		ConvertErrorCode(ret);
		return 0;
	}
	return v8;
}

int CPlayControl::GetColor( ULONG a2, int *a3, int *a4, int *a5, int *a6 )
{
	int v8; // edi@7
	int v9; // edi@7
	int v10; // edi@7
	int v11; // eax@7

	int ret; // [sp-4h] [bp-8h]@6

	if ( a3 && a4 && a5 && a6 )
	{
		if ( m_pMediaManager )
		{
			v8 = m_pMediaManager->GetVideoAdjustPara(a2, 0, a3);
			v9 = m_pMediaManager->GetVideoAdjustPara(a2, 1, a4) | v8;
			v10 = m_pMediaManager->GetVideoAdjustPara(a2, 2, a5) | v9;
			v11 = m_pMediaManager->GetVideoAdjustPara(a2, 3, a6);
			return JudgeRet(v11 | v10);
		}
		ret = -2147483646;
	}
	else
	{
		ret = -2147483645;
	}
	return JudgeRet(ret);
}

int CPlayControl::GetColorKey()
{
	int ret; // eax@3
	int v5; // [sp+4h] [bp-8h]@3
	int v6; // [sp+8h] [bp-4h]@3

	v6 =-1;
	if ( m_pMediaManager )
	{
		ret = m_pMediaManager->GetOverlayMode(0, &v5, &v6);
		JudgeRet(ret);
	}
	else
	{
		ConvertErrorCode(-2147483646);
	}
	return v6;
}

int CPlayControl::GetCurrentFrameNum()
{
	IVSPLAY_DECDATA_INFO v4;
	int result; // eax@3

	if ( m_pMediaManager && !m_pMediaManager->GetCurrentFrameInfo(&v4) );
	{
		result = v4.dis.part1;
	}
	else
	{
		ConvertErrorCode(-2147483646);
		result = -1;
	}
	return result;
}

int CPlayControl::GetCurrentFrameRate()
{
	IVSPLAY_DECDATA_INFO v4;
	int result; // eax@3

	if ( m_pMediaManager && !m_pMediaManager->GetCurrentFrameInfo(&v4) )
	{
		result = 1000 / v4.dis.part2;
	}
	else
	{
		ConvertErrorCode(-2147483646);
		result = -1;
	}
	return result;
}

int CPlayControl::GetDeviceCaps( ULONG a1 )
{
	int result; // eax@2

	if ( CHikDirectDraw::GetDeviceCaps(a1, &a1) )
		result = -1;
	else
		result = a1;
	return result;
}

int CPlayControl::GetDisplayBuf()
{
	int result; // eax@2
	int v4; // eax@3
	int v5; // [sp+4h] [bp-4h]@3

	if ( m_pMediaManager )
	{
		v5 = -1;
		v4 = m_pMediaManager->GetVideoDisplayBuf(&v5);
		JudgeRet(v4);
		result = v5;
	}
	else
	{
		ConvertErrorCode(-2147483646);
		result = -1;
	}
	return result;
}

int CPlayControl::GetDisplayType()
{
	int result; // eax@2
	int v4; // eax@3
	int v5; // [sp+4h] [bp-4h]@3

	if ( m_pMediaManager )
	{
		v5 = 0;
		v4 = m_pMediaManager->GetDisplayEffect(0, 0, &v5);
		JudgeRet(v4);
		result = v5;
	}
	else
	{
		ConvertErrorCode(-2147483646);
		result = 0;
	}
	return result;
}

int CPlayControl::GetFileSpecialAttr(ULONG *,ULONG *,ULONG *)
{
	return JudgeRet(-2147483632);
}

DWORD CPlayControl::GetFileTime()
{
	DWORD result; // eax@3

	if ( part30 && part33 != -1 )
	{
		result = m_pMediaManager->GetFileTime() / 1000;
	}
	else
	{
		ConvertErrorCode(-2147483646);
		result = -1;
	}
	return result;
}

int CPlayControl::GetFileTimeEx( ULONG *a2,ULONG *a3,ULONG *a4 )
{
	int v5; // [sp-4h] [bp-4h]@5

	if ( a2 && a3 && a4 )
	{
		if ( part30 )
		{
			*a2 = part39 & 0x3F | ((part34 << 26) - 0x3C000001) & 0xFC000000 | ((part38 & 0x3F | ((part37 & 0x1F | 32 * (part36 & 0x1F | 32 * (part35 & 0xF))) << 6)) << 6);
			*a3 = part46 & 0x3F | ((part41 << 26) - 0x3C000001) & 0xFC000000 | ((part45 & 0x3F | ((part44 & 0x1F | 32 * (part43 & 0x1F | 32 * (part42 & 0xF))) << 6)) << 6);
			*a4 = 0;
			return 1;
		}
		v5 = -2147483646;
	}
	else
	{
		v5 = -2147483645;
	}
	return JudgeRet(v5);
}

int CPlayControl::GetFileTotalFrames()
{
	int result; // eax@2

	if ( m_pMediaManager )
	{
		result = m_nTotalFrm;
	}
	else
	{
		ConvertErrorCode(-2147483646);
		result = -1;
	}
	return result;
}

int CPlayControl::GetJPEG( BYTE *a2,ULONG a3,ULONG *a4 )
{
	int v7; // [sp-4h] [bp-8h]@2

	if ( a4 )
	{
		if ( m_pMediaManager )
			v7 =m_pMediaManager->GetJPEGData(a2, a3, a4, g_lJpegQuality);
		else
			v7 = -2147483646;
	}
	else
	{
		v7 = -2147483645;
	}
	return JudgeRet(v7);
}

int CPlayControl::GetKeyFramePos( ULONG a2,ULONG a3,FRAME_POS *a4 )
{
	int v7; // [sp-4h] [bp-44h]@3
	FRAME_POS v8; // [sp+8h] [bp-38h]@3

	if ( m_pMediaManager && a4 )
	{
		v7 = m_pMediaManager->GetKeyFramePos(v5, a2, a3, &v8);
		a4->nFilePos = v8.nFilePos;
		a4->nFrameNum = v8.nErrorFrameNum;
		a4->nFrameTime = v8.nFrameTime;
	}
	else
	{
		v7 = -2147483646;
	}
	return JudgeRet(v7);
}

bool CPlayControl::GetMonitorDeviceInfo( ULONG a1,char* Dest,ULONG a3,char *a4,ULONG a5,HMONITOR a6 )
{
	return CHikDirectDraw::GetMonitorDeviceInfo(a1,Dest,a3,a4,a5,a6)==0;
}

int CPlayControl::GetMonitorDevicesNum()
{
	int v2;
   int result; // eax@2

	if ( CHikDirectDraw::GetMonitorDevicesNum(&v2) )
		result = -1;
	else
		result = v2;
	return result;
}

int CPlayControl::GetNextKeyFramePos( ULONG a2,ULONG a3,FRAME_POS *a4 )
{

	int v7; // [sp-4h] [bp-44h]@3
	FRAME_POS v8; // [sp+8h] [bp-38h]@3

	if ( m_pMediaManager && a4 )
	{
		v7 = m_pMediaManager->GetNextKeyFramePos(v5, a2, a3, &v8);
		a4->nFilePos = v8.nFilePos;
		a4->nFrameNum = v8.nErrorFrameNum;
		a4->nFrameTime = v8.nFrameTime;
	}
	else
	{
		v7 = -2147483646;
	}
	return JudgeRet(v7);
}

int CPlayControl::GetOverlayMode()
{
	int result; // eax@2
	int v4; // eax@3
	int v5; // [sp+4h] [bp-8h]@3
	int v6; // [sp+8h] [bp-4h]@3

	if ( m_pMediaManager )
	{
		v6 = -1;
		v4 = m_pMediaManager->GetOverlayMode(0, &v6, &v5);
		JudgeRet(v4);
		result = v6;
	}
	else
	{
		ConvertErrorCode(-2147483646);
		result = -1;
	}
	return result;
}

int CPlayControl::GetPictureQuality( int *a2 )
{
	int v5; // [sp-4h] [bp-8h]@2

	if ( m_pMediaManager )
	{
		if ( a2 )
			v5 =m_pMediaManager->GetVideoPostProcess(1, a2);
		else
			v5 = -2147483645;
	}
	else
	{
		v5 = -2147483646;
	}
	return JudgeRet(v5);
}

int CPlayControl::GetPictureSize( long *a2,long *a3 )
{
	int v5; // eax@6
	signed int v7; // [sp-4h] [bp-50h]@4
	IVSPLAY_DECDATA_INFO v8; // [sp+Ch] [bp-40h]@5
	int v9; // [sp+24h] [bp-28h]@6
	int v10; // [sp+28h] [bp-24h]@6


	if ( !a2 || !a3 )
	{
		v7 = -2147483645;
		return JudgeRet(v7);
	}

	if ( !m_pMediaManager )
	{
		v7 = -2147483646;
		return JudgeRet(v7);
	}
	if (m_pMediaManager->GetCurrentFrameInfo(&v8) )
	{
		*a2 = m_iWidth;
		*a3 = m_iHeight;
	}
	else
	{
		*a2 = v9;
		v5 = v10;
		*a3 = v10;
		if ( !*a2 || !v5 )
		{
			*a2 = 352;
			*a3 = 288;
		}
	}
	return 1;
}

double CPlayControl::GetPlayPos()
{
	double result; // st7@2

	if ( m_pMediaManager )
	{
		result = m_pMediaManager->GetPlayPos();
		if ( result < 0.000001 )
			ConvertErrorCode(-2147483646);
	}
	else
	{
		ConvertErrorCode(-2147483646);
		result = 0.0;
	}
	return result;
}

int CPlayControl::GetPlayedFrames()
{
	CPlayControl *v1; // esi@1
	CMediaManager *v2; // ecx@1
	int result; // eax@3
	IVSPLAY_DECDATA_INFO v4;;
	int v5; // [sp+Ch] [bp-38h]@4

	v1 = this;
	v2 = this->m_pMediaManager;
	if ( v2 && !CMediaManager::GetCurrentFrameInfo(v2, (int)&v4) )
	{
		result = v5 + 1;
	}
	else
	{
		CPlayControl::ConvertErrorCode(v1, -2147483646);
		result = -1;
	}
	return result;
}

