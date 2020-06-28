#include "StdAfx.h"
#include "HikVDec.h"

int __stdcall TargetFrameCB(CHikVDec *a1)
{
	a1->TargetFrameArrived();
}

CHikVDec::CHikVDec( CMediaManager* a2 )
{
	m_pMediaManager=a2;
	InitMember();
}

CHikVDec::~CHikVDec(void)
{
	ReleaseVDec();
	m_pMediaManager=NULL;
}

void CHikVDec::InitMember()
{
	m_bInformNoDisplay = 1;
	m_pVidDecoder = 0;
	m_bIsInit = 0;
	m_cbDec = 0;
	m_nUserForDec = 0;
	m_nSkipB = 0;
	m_nDecCBType = 0;
}

int CHikVDec::TargetFrameArrived()
{
	int result;

	if ( m_pMediaManager )
		result = m_pMediaManager->TargetFrameArrived();
	else
		result = -2147483646;
	return result;
}

int CHikVDec::IsInit()
{
	return m_bIsInit;
}

int CHikVDec::InitVDec( ULONG a2 )
{
	int v11;
	IHikVideoDecoder *v7;

	try
	{
		ReleaseVDec();
		try
		{
			if ( a2 == 1 || a2==256)
			{
				v7 = new CHikH264Dec;
			}
			else if ( a2 == 2 )
			{
				v7 = new CHikMpeg2Dec;
			}
			else if ( a2 == 3 )
			{
				v7 = new CHikMpeg4Dec;
			}
			else if ( a2 == 4 )
			{
				v7 = new CHikMJpegDec;
			}
			else
			{
				throw -2147483632;
			}
			if ( !v7 )
			{
				throw -2147483641;
			}

		}catch(...)
		{
			_LOG_RECORD("CHikVDec::InitVDec failed to new!\n");
			throw -2147483641;
		}

		m_pVidDecoder = v7;
		v11 = v7->InitVideoDecoder();
		if ( v11 )
		{
			throw v11;
		}

		InformNoDisplay(m_bInformNoDisplay);
		if (m_nSkipB )
		{
			SkipBFrameNum( m_nSkipB);
		}
		v11 = SetCallBack();
		if ( v11 )
		{
			throw v11;
		}
		m_bIsInit = 1;

	}catch(int err)
	{
		ReleaseVDec();
		return err;
	}
	return 0;
}

int CHikVDec::AppOperation( int a2 )
{
	int result;

	if ( m_pVidDecoder )
	{
		result = m_pVidDecoder->Operation(a2);
		if ( !result )
		{
			if ( a2 == 4 )
			{
				ReleaseVDec();
				InitMember();
			}
			result = 0;
		}
	}
	else
	{
		result = -2147483646;
	}
	return result;
}

int CHikVDec::CheckErrFrame( int a2 )
{
	int result; 

	if ( m_pVidDecoder )
		result = m_pVidDecoder->CheckErrFrame(a2);
	else
		result = -2147483646;
	return result;
}

int CHikVDec::Disconnect()
{
	int result; // eax@1
	IHikOutput *v2=NULL; // [sp+0h] [bp-4h]@1

	result = GetOutput(&v2);
	if ( !result )
	{
		if ( v2 )
			result = v2->SetConnectedInput(NULL);
	}
	return result;
}

int CHikVDec::GetInput( IHikInput * *a2 )
{
	int result; // eax@2

	if ( m_pVidDecoder )
		result = m_pVidDecoder->GetInput(a2);
	else
		result = -2147483646;
	return result;
}

int CHikVDec::GetOutput( IHikOutput * *a2 )
{
	int result; // eax@2

	if ( m_pVidDecoder )
		result = m_pVidDecoder->GetOutput(a2);
	else
		result = -2147483646;
	return result;
}

int CHikVDec::GetCurrentFrameNum( ULONG *a2 )
{
	int result; // eax@2

	if ( m_pVidDecoder )
		result = m_pVidDecoder->GetCurrentFrameNum(a2);
	else
		result = -2147483646;
	return result;
}

int CHikVDec::GetVideoDecCBType( ULONG *a2 )
{
	int result; // eax@2

	if ( m_pVidDecoder )
	{
		result = m_pVidDecoder->GetVideoDecCBType(a2);
	}
	else
	{
		*a2 = m_nDecCBType;
		result = 0;
	}
	return result;
}

int CHikVDec::GetVideoPostProcess( ULONG a2,ULONG* a3 )
{
	int result; // eax@2

	if ( m_pVidDecoder )
		result = m_pVidDecoder->GetVideoPostProcess(a2, a3);
	else
		result = -2147483646;
	return result;
}

int CHikVDec::InformNoDisplay( int a2 )
{
	int result;

	m_bInformNoDisplay = a2;
	if ( m_pVidDecoder )
		result = m_pVidDecoder->InformNoDisplay(a2);
	else
		result = -2147483646;
	return result;
}

int CHikVDec::RegisterVideoDecCallBack( CB_Dec2 a2,ULONG a3 )
{
	int result; // eax@3

	if ( a2 )
	{
		m_cbDec = a2;
		m_nUserForDec = a3;
		if ( m_pVidDecoder )
			result = m_pVidDecoder->SetVDecCB(a2, a3);
		else
			result = 0;
	}
	else
	{
		result = -2147483645;
	}
	return result;
}

void CHikVDec::ReleaseVDec()
{
	if ( m_pVidDecoder )
	{
		delete m_pVidDecoder;
		m_pVidDecoder = NULL;
	}
}

int CHikVDec::SetAimFrame( ULONG a2,ULONG a3 )
{
	int result; // eax@2

	if ( m_pVidDecoder )
		result =m_pVidDecoder->SetAimFrame(a2, a3);
	else
		result = -2147483646;
	return result;
}

int CHikVDec::SetCallBack()
{
	int result; // eax@2

	if ( m_pVidDecoder )
	{
		result = m_pVidDecoder->SetTargetFrameCB(TargetFrameCB,(ULONG)this);
		if ( !result )
		{
			m_pVidDecoder->SetVDecCBType(m_nDecCBType);
			if ( !m_cbDec || (result = m_pVidDecoder->SetVDecCB(m_cbDec,m_nUserForDec)) == 0 )
			result = 0;
		}
	}
	else
	{
		result = -2147483646;
	}
	return result;
}

int CHikVDec::SetHikImage( CHikImage* a2 )
{
	int result; // eax@2

	if ( m_pVidDecoder )
		result = m_pVidDecoder->SetHikImage(a2);
	else
		result = -2147483646;
	return result;
}

int CHikVDec::SetPlaySpeed( float a2 )
{
	int result; // eax@2

	if ( m_pVidDecoder )
		result = m_pVidDecoder->SetPlaySpeed(a2);
	else
		result = -2147483646;
	return result;
}

int CHikVDec::SetVideoDecCBType( ULONG a2 )
{
	int result; // eax@2

	this->m_nDecCBType = a2;

	if ( m_pVidDecoder )
		result = m_pVidDecoder->SetVDecCBType(a2);
	else
		result = 0;
	return result;
}

int CHikVDec::SetVideoDecodeType( ULONG a2 )
{
	int result; // eax@2

	if ( a2 < 3 )
	{
		if ( m_pVidDecoder )
			result = m_pVidDecoder->SetDecodeType(a2);
		else
			result = 0;
	}
	else
	{
		result = -2147483645;
	}
	return result;
}

int CHikVDec::SetVideoPostProcess( ULONG a2,ULONG a3 )
{
	int result; // eax@2

	if ( m_pVidDecoder )
		result = m_pVidDecoder->SetVideoPostProcess(a2, a3);
	else
		result = -2147483646;
	return result;
}

int CHikVDec::SkipBFrameNum( ULONG a2 )
{
	int result; // eax@2

	if ( a2 <= 2 )
	{
		m_nSkipB = a2;

		if ( m_pVidDecoder )
			result = m_pVidDecoder->SetBDecodeNum(2 - a2);
		else
			result = 0;
	}
	else
	{
		result = -2147483645;
	}
	return result;
}
