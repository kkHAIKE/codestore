#include "StdAfx.h"
#include "AudioRenderer.h"

CAudioRenderer::CAudioRenderer(void)
{
	InitMember();
}

CAudioRenderer::~CAudioRenderer(void)
{
	ReleaseAR();
}

void CAudioRenderer::InitMember()
{
	m_bIsInit=0;
	m_cTmpl=0;
}

int CAudioRenderer::AdjustWaveAudio( LONG a2 )
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->AdjustWaveAudio(a2);
	else
		result = -2147483646;
	return result;
}

int CAudioRenderer::AppOperation( int a2 )
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->Operation(a2);
	else
		result = -2147483646;
	return result;
}

int CAudioRenderer::ClearAudio()
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->ClearAudio();
	else
		result = -2147483646;
	return result;
}

void CAudioRenderer::Disconnect()
{
}

int CAudioRenderer::GetAudioTimeStamp( ULONG *a2 )
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->GetAudioTimeStamp(a2);
	else
		result = -2147483646;
	return result;
}

int CAudioRenderer::GetCurrentFrameInfo( IVSPLAY_FRAME_INFO* a2 )
{
	int result; // eax@2

	if ( m_cTmpl )
	{
		m_cTmpl->GetCurrentFrameInfo(a2);
		result = 0;
	}
	else
	{
		result = -2147483646;
	}
	return result;
}

int CAudioRenderer::GetFrameCountInBuf( ULONG *a2 )
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->GetFrameCountInBuf(a2);
	else
		result = -2147483646;
	return result;
}

int CAudioRenderer::GetInput( IHikInput** a2 )
{
	int result; // eax@2

	if ( v2 )
		result = m_cTmpl->GetInput(a2);
	else
		result = -2147483646;
	return result;
}

int CAudioRenderer::GetPlayBufCount( ULONG *a2 )
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->GetPlayBufCount(a2);
	else
		result = -2147483646;
	return result;
}

int CAudioRenderer::GetVolume( ULONG *a2 )
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->GetVolume(a2);
	else
		result = -2147483646;
	return result;
}

int CAudioRenderer::InitAR()
{
	int v8;
	try
	{
		try
		{
			ReleaseAR();
			m_cTmpl=new CHikARenderer;
			if(!m_cTmpl)
				throw -2147483641;
		}catch(...)
		{
			_LOG_RECORD("CAudioRenderer::InitAR failed to new!\n");
			throw -2147483641;
		}
		v8=m_cTmpl->InitAudioRenderer();
		if(v8)
			throw v8;
	}catch(int err)
	{
		ReleaseAR();
		return err;
	}
	return 0;
}

int CAudioRenderer::IsInit()
{
	return m_bIsInit;
}

void CAudioRenderer::ReleaseAR()
{
	if(m_cTmpl)
	{delete m_cTmpl;m_cTmpl=NULL;}
}

int CAudioRenderer::ResetPlayBuffer()
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->ResetPlayBuf();
	else
		result = -2147483646;
	return result;
}

int CAudioRenderer::SetHWND( HWND a2 )
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->SetHWND(a2);
	return result;
}

int CAudioRenderer::SetPlayBufCount( ULONG a2 )
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->SetPlayBufCount(a2);
	else
		result = -2147483646;
	return result;
}

int CAudioRenderer::SetPlaySpeed( float a2 )
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->SetPlaySpeed(LODWORD(a2));
	else
		result = -2147483646;
	return result;
}

int CAudioRenderer::SetVolume( ULONG a2 )
{
	int result; // eax@2

	if ( m_cTmpl )
		result = m_cTmpl->SetVolume(a2);
	else
		result = -2147483646;
	return result;
}

