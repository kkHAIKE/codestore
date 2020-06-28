#include "StdAfx.h"
#include "VideoRenderer.h"

int __stdcall FPSChange(ULONG a1, ULONG a2)
{
	return reinterpret_cast<CVideoRenderer*>(a1)->FPSChangeCB(a2);
}

CVideoRenderer::CVideoRenderer( CMediaManager *a2 )
{
	m_pMediaManager=a2;
	InitMember();
}

CVideoRenderer::~CVideoRenderer(void)
{
	ReleaseVR();
}

void CVideoRenderer::InitMember()
{
	m_FilePara2 = -1;
	m_FilePara1 = -1;
	m_cTmpl = 0;
	m_cbDimChange = 0;
	m_cbPlayEnd = 0;
	m_cbDisplay = 0;
	m_cbHDC = 0;
	m_nUserForDimChange = 0;
	part21 = 0;
	m_nUserForPlayEnd = 0;
	m_nUserForDisplay = 0;
	part19 = 0;
	m_bIsInit = 0;
	part25 = 1;

	for(int i=0;i<4;++i)
	{
		m_bHDCisSet[i]=0;
		m_nUserForHDC[i]=0;
	}

	m_bflagPlayEnd = 0;
}

void CVideoRenderer::ReleaseVR()
{
	if ( m_cTmpl )
	{
		delete m_cTmpl;
		m_cTmpl = NULL;
	}
	m_pMediaManager = NULL;
}

int CVideoRenderer::AppOperation( int a2 )
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->Operation(a2);
	else
		result = -2147483646;
	return result;
}

int CVideoRenderer::IsInit()
{
	return m_bIsInit;
}

int CVideoRenderer::InitVR()
{
	int ret;
	
	try
	{
		try
		{
			if(m_cTmpl)
			{delete m_cTmpl;m_cTmpl=NULL;};

			m_cTmpl=new CHikVRenderer;
			if(!m_cTmpl)
			{
				throw -2147483641;
			}
		}
		catch(...)
		{
			_LOG_RECORD("CVideoRenderer::InitVR failed to new!\n");
			return -2147483641;
		}
		ret=m_cTmpl->InitVideoRenderer();
		if(ret)
		{
			throw ret;
		}
		ret=SetCallBack();
		if(ret)
		{
			throw ret;
		}
		m_bIsInit=1;
	}
	catch(int err)
	{
		ReleaseVR();
		return err;
	}
	return 0;
}

int CVideoRenderer::BackDisplayOneFrame( ULONG a2,IVSPLAY_FRAME_INFO *a3 )
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->BackDisplayOneFrame(a2, a3);
	else
		result = -2147483646;
	return result;
}

int CVideoRenderer::ClearVideoSample()
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->ClearVideoSample();
	else
		result = -2147483646;
	return result;
}

int CVideoRenderer::DisableDisplayWindow( ULONG a2 )
{
	int result; // eax@3

	if ( m_cTmpl )
	{
		if ( a2 >= 4 )
			result = -2147483642;
		else
			result = m_cTmpl->DisableDisplayWindow(a2);
	}
	else
	{
		result = -2147483646;
	}
	return result;
}

int CVideoRenderer::DisableIVS()
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->DisableIVS();
	else
		result = -2147483646;
	return result;
}

int CVideoRenderer::Disconnect()
{
	int result; // eax@1
	IHikInput* v4=NULL; // [sp+4h] [bp-4h]@1

	result = GetInput(&v4);
	if ( !result )
	{
		if ( m_cTmpl )
			result = m_cTmpl->SetInputSample(NULL);
	}
	return result;
}

int CVideoRenderer::DisplayOneFrame( IVSPLAY_FRAME_INFO *a2,ULONG* a3,ULONG *a4 )
{
	int result; // eax@7

	if ( m_cTmpl )
	{
		result = result->DisplayOneFrame(a2, a3, a4);

		if ( m_pMediaManager->IsPlayEnd() )
		{
			if ( !m_bflagPlayEnd )
			{
				if ( m_cbPlayEnd )
				{
					m_bflagPlayEnd = 1;
					m_cbPlayEnd(m_nUserForPlayEnd);
				}
			}
		}
		else
		{
			m_bflagPlayEnd = 0;
		}
	}
	else
	{
		result = -2147483646;
	}
	return result;
}

int CVideoRenderer::SetCallBack()
{
	int result; // eax@2

	if ( m_cTmpl )
	{
		if ( !m_cbDisplay || (result = m_cTmpl->SetDisplayCB(0,m_cbDisplay,m_nUserForDisplay)) == 0 )
		{
			if ( !m_cbDimChange || (result = m_cTmpl->SetDimChangeCB(m_cbDimChange, m_nUserForDimChange)) == 0 )
			{
				result = m_cTmpl->SetFPSChangeCB(FPSChange,(ULONG) this);
				if ( !result )
				{
					for(int i=0;i<4;++i)
					{
						if(m_bHDCisSet[i])
						{
							result = m_cTmpl->SetHDCCB(i,m_cbHDC,m_nUserForHDC[i]);
							if(result)
								break;
						}
					}
					return 0;
				}
			}
		}
	}
	else
	{
		result = -2147483646;
	}
	return result;
}

int CVideoRenderer::SetDisplayEffect( ULONG a2,ULONG a3,ULONG a4 )
{
	int result; // eax@3

	if ( m_cTmpl )
	{
		if ( a2 >= 4 )
			result = -2147483642;
		else
			result = m_cTmpl->SetDisplayEffect(a2, a3, a4);
	}
	else
	{
		result = -2147483646;
	}
	return result;
}

int CVideoRenderer::SetDisplayHwnd( HWND hWnd )
{
	int result; // eax@3

	if ( m_cTmpl )
	{
		if ( IsWindow(hWnd) )
			result = m_cTmpl->EnableDisplayWindow(0, hWnd, 0);
		else
			result = -2147483645;
	}
	else
	{
		result = -2147483646;
	}
	return result;
}

int CVideoRenderer::SetFilePara( ULONG a2,ULONG a3 )
{
	if(!a2)
	{
		m_FilePara2 = a3;
	}
	else if ( a2==1 )
	{
		m_FilePara1 = a3;
	}
	else
		return -2147483632;	
	return 0;
}

int CVideoRenderer::SetHikImage( CHikImage *a2 )
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->SetHikImage(a2);
	else
		result = -2147483646;
	return result;
}

int CVideoRenderer::SetInputSample( CHikSample *a2 )
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->SetInputSample(a2);
	else
		result = -2147483646;
	return result;
}

int CVideoRenderer::SetOverlayFlipMode( ULONG a2,int a3,ULONG a4 )
{
	int result; // eax@3

	if ( m_cTmpl )
	{
		if ( a2 >= 4 )
			result = -2147483642;
		else
			result = m_cTmpl->SetOverlayFlipMode(a2, a3, a4);
	}
	else
	{
		result = -2147483646;
	}
	return result;
}

int CVideoRenderer::SetOverlayMode( ULONG a2,int a3,ULONG a4 )
{
	int result; // eax@3

	if ( m_cTmpl )
	{
		if ( a2 >= 4 )
			result = -2147483642;
		else
			result = m_cTmpl->SetOverlayMode(a2, a3, a4);
	}
	else
	{
		result = -2147483646;
	}
	return result;
}

int CVideoRenderer::SetPlaySpeed( float a2 )
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->SetPlaySpeed(a2);
	else
		result = -2147483646;
	return result;
}

int CVideoRenderer::SetStartFrameNum( ULONG a2 )
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->SetStartFrame(a2);
	else
		result = -2147483646;
	return result;
}

int CVideoRenderer::SetVideoAdjustPara( ULONG a2,ULONG a3,ULONG a4 )
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->SetVideoAdjustPara(a2, a3, a4);
	else
		result = -2147483646;
	return result;
}

int CVideoRenderer::GetInput( CHikVRInput* *a2 )
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->GetInput(a2);
	else
		result = -2147483646;
	return result;
}

int CVideoRenderer::GetJPEG( char *a2,ULONG a3 )
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->GetJPEG(a2, a3);
	else
		result = -2147483646;
	return result;
}

int CVideoRenderer::GetJPEGData( BYTE *a2,ULONG a3,ULONG *a4,ULONG a5 )
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->GetJPEGData(a2, a3, a4, a5);
	else
		result = -2147483646;
	return result;
}

int CVideoRenderer::GetOneFrameNeedDisplay( __int64 *a2 ,ULONG a3,float a4 )
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->GetOneFrameNeedDisplay(a2, a3, a4);
	else
		result = 0;
	return result;
}

int CVideoRenderer::GetOverlayFlipMode( ULONG a2,int *a3,ULONG *a4 )
{
	int result; // eax@3

	if ( m_cTmpl )
	{
		if ( a2 >= 4 )
			result = -2147483642;
		else
			result = m_cTmpl->GetOverlayFlipMode(a2, a3, a4);
	}
	else
	{
		result = -2147483646;
	}
	return result;
}

int CVideoRenderer::GetOverlayMode( ULONG a2,int *a3,ULONG *a4 )
{
	int result; // eax@3

	if ( m_cTmpl )
	{
		if ( a2 >= 4 )
			result = -2147483642;
		else
			result = m_cTmpl->GetOverlayMode(a2, a3, a4);
	}
	else
	{
		result = -2147483646;
	}
	return result;
}

int CVideoRenderer::GetVideoAdjustPara( ULONG a2,ULONG a3,ULONG *a4 )
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->GetVideoAdjustPara(a2, a3, a4);
	else
		result = -2147483646;
	return result;
}

int CVideoRenderer::GetVideoTimeStamp( ULONG *a2 )
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->GetVideoTimeStamp(a2);
	else
		result = -2147483646;
	return result;
}

int CVideoRenderer::RefreshDisplayWindow( ULONG a2,int a3 )
{
	int result; // eax@3

	if ( m_cTmpl )
	{
		if ( a2 >= 4 )
			result = -2147483642;
		else
			result = m_cTmpl->RefreshDisplayWindow(a2, a3);
	}
	else
	{
		result = -2147483646;
	}
	return result;
}

int CVideoRenderer::RegisterDimChangeCallBack( CB_DimChange a2,ULONG a3 )
{
	int result; // eax@2

	m_cbDimChange = a2;
	m_nUserForDimChange = a3;

	if ( m_cTmpl )
		result = m_cTmpl->SetDimChangeCB(a2, a3);
	else
		result = 0;
	return result;
}

int CVideoRenderer::RegisterHDCCallBack(ULONG a2,CB_HDC a3,ULONG a4 )
{
	int result; // eax@2

	if ( a2 < 4 )
	{
		m_bHDCisSet[a2] = 1;
		m_nUserForHDC[a2] = a4;
		m_cbHDC = a3;

		if ( m_cTmpl )
			m_cTmpl->SetHDCCB(a2, a3, a4);
		result = 0;
	}
	else
	{
		result = -2147483642;
	}
	return result;
}

int CVideoRenderer::RegisterPlayEndCallBack( CB_PlayEnd a2,ULONG a3 )
{
	int result; // eax@2

	m_cbPlayEnd = (void *)a2;
	m_nUserForPlayEnd = a3;

	if ( m_cTmpl )
		result = m_cTmpl->SetPlayEndCB(a2, a3);
	else
		result = 0;
	return result;
}

int CVideoRenderer::RegisterVideoDisplayCallBack( ULONG a2,CB_Display2 a3,ULONG a4 )
{
	int result; // eax@3

	if ( a2 >= 4 )
	{
		result = -2147483642;
	}
	else
	{
		m_cbDisplay = a3;
		m_nUserForDisplay = a4;

		if ( m_cTmpl )
			result = m_cTmpl->SetDisplayCB(0, a3, a4);
		else
			result = 0;
	}
	return result;
}

int CVideoRenderer::EnableDisplayDevice( ULONG a2,ULONG a3 )
{
	return 0;
}

int CVideoRenderer::EnableDisplayWindow( ULONG a2,HWND a3,RECT *a4 )
{
	int result; // eax@3

	if ( m_cTmpl )
	{
		if ( a2 >= 4 )
			result = -2147483642;
		else
			result = m_cTmpl->EnableDisplayWindow(a2, a3, a4);
	}
	else
	{
		result = -2147483646;
	}
	return result;
}

int CVideoRenderer::EnableIVS()
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->EnableIVS();
	else
		result = -2147483646;
	return result;
}

int CVideoRenderer::FPSChangeCB(ULONG a2)
{
	int result; // eax@2

	if ( m_pMediaManager )
		result = m_pMediaManager->SetTimePerFrame(a2);
	else
		result = -2147483646;
	return result;
}

int CVideoRenderer::GetBMP( char *a2 )
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl(a2);
	else
		result = -2147483646;
	return result;
}

int CVideoRenderer::GetBMPData( BYTE *a2,ULONG a3,ULONG *a4 )
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->GetBMPData(a2, a3, a4);
	else
		result = -2147483646;
	return result;
}

int CVideoRenderer::GetCurrentFrameInfo( IVSPLAY_FRAME_INFO *a2 )
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->GetCurrentFrameInfo(a2);
	else
		result = -2147483646;
	return result;
}

int CVideoRenderer::GetDecodedFrameNum( ULONG *a2 )
{
	return -2147483632;
}

int CVideoRenderer::GetDisplayEffect( ULONG a2,ULONG a3,ULONG *a4 )
{
	int result; // eax@3

	if ( m_cTmpl )
	{
		if ( a2 >= 4 )
			result = -2147483642;
		else
			result = m_cTmpl->GetDisplayEffect(a2, a3, a4);
	}
	else
	{
		result = -2147483646;
	}
	return result;
}

