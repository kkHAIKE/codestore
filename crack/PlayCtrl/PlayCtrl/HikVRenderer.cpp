#include "StdAfx.h"
#include "HikVRenderer.h"

CHikVRenderer::CHikVRenderer(void)
{
	memset(m_part8,0,16);
	memset(m_part30,0,16);
	memset(m_part46,0,32);
	memset(m_part14, 0,64);
	m_part56 = -1;
	m_part40 = 0;
	m_part41 = 0;
	m_part7 = 0;
	m_part35 = 0;
	m_part36 = 0;
	m_part38 = 0;
	m_part34 = 0;
	m_part39 = 0;
	m_part5 = 0;
	m_part3 = 0;
	m_part4 = 0;
	m_part2 = 0;
	m_part6 = 0;
	m_part42 = 0;
	m_part43 = 0;
	m_part54 = 0;
	m_part55 = 0;
	m_part57 = 0;
	m_part59 = 0;
	m_part60 = 0;
	m_part37 = 40;
	m_part13 = 3;
	m_part58 = 1;
}

CHikVRenderer::~CHikVRenderer(void)
{
}

int CHikVRenderer::Operation( int a2 )
{
	
}

int CHikVRenderer::InitHikD3D()
{
	return 0;
}

int CHikVRenderer::InitHikDDraw()
{
	return 0;
}

int CHikVRenderer::InitVideoRenderer()
{
	try
	{
		if(m_pVRInput==0)
		{
			m_pVRInput=new CHikVRInput();
			if(!m_pVRInput)
				throw -2147483641;
			m_pVRInput->SetParent(this);
		}
	}catch(...)
	{
		_LOG_RECORD("CHikVRenderer::InitVideoRenderer failed to new!\n");
		return -2147483641;
	}
	return 0;
}

int CHikVRenderer::SetFPSChangeCB( CB_FPSChange a2,ULONG a3 )
{
	m_cbFPSChange=a2;
	m_nUserForFPSChange=a3;
	return 0;
}

int CHikVRenderer::SetPlayEndCB( CB_PlayEnd a2,ULONG a3 )
{
	int result; // eax@2

	if ( a2 )
	{
		m_cbPlayEnd = a2;
		m_nUserForPlayEnd = a3;
		result = 0;
	}
	else
	{
		result = -2147483645;
	}
	return result;
}

int CHikVRenderer::SetDisplayCB( ULONG a2,CB_Display2 a3,ULONG a4 )
{
	m_cbDisplay = a3;
	m_nUserForDisplay = a4;
	return 0;
}

int CHikVRenderer::SetDimChangeCB( CB_DimChange a2,ULONG a3 )
{
	m_cbDimChange = a2;
	m_nUserForDimChange = a3;
	return 0;
}

int CHikVRenderer::SetHDCCB( ULONG a2,CB_HDC a3,ULONG a4 )
{
	
}

int CHikVRenderer::SetInputSample( CHikSample *a2 )
{
	m_pSample = a2;
	return 0;
}

int CHikVRenderer::SetPlaySpeed( float a2 )
{
	m_part58 = 1;
	m_fSpeed = a2;
	return 0;
}

int CHikVRenderer::Stop()
{
	m_part39 = 0;
	m_part56 = -1;
	m_part37 = 40;
	return 0;
}

int CHikVRenderer::TempStop()
{
	return 0;
}

int CHikVRenderer::BackDisplayOneFrame( ULONG a2,IVSPLAY_FRAME_INFO *a3 )
{
	int result; // eax@11

	DISPLAY_PARA Dst; // [sp+Ch] [bp-48h]@6
	int v8; // [sp+4Ch] [bp-8h]@2
	BUF_NODE *v9; // [sp+50h] [bp-4h]@3

	if ( !m_pSample )
		return -2147483646;
	v8 = 0;
	while ( 1 )
	{
		while ( 1 )
		{
			v9 = 0;
			m_pSample->GetNode(&v9, 0);
			if ( v9 )
			{
				GetDisplayPara(v9->data1, &Dst);
				if ( Dst.part1 >= a2 )
					break;
				m_pSample->UsedDataNodeToSpareList(0);
				v8 = 1;
			}
			Sleep(1);
		}
		if ( Dst.part1 <= a2 )
			break;
		if ( v8 )
			return -2147483646;
		m_pSample->UsedDataNodeToSpareList(0);
	}
	result = Display(v9->data1, v9->part3, v9->data2, v9->part6, a3);
	if ( !result )
	{
		m_pSample->UsedDataNodeToSpareList(reinterpret_cast<DISPLAY_PARA*>(v9->data1)->part3 != 1);
		result = 0;
	}
	return result;
}

int CHikVRenderer::GetDisplayPara( BYTE *Src,DISPLAY_PARA* Dst )
{
	int result; // eax@15

	if ( Src )
		memcpy(Dst, Src, sizeof(DISPLAY_PARA));

	if ( Dst->nWidth < 0x60 || Dst->nWidth > 0xF00 || Dst->nHeight < 0x40 || Dst->nHeight > 0xC00 )
	{
		result = -2147483642;
	}
	else
	{
		m_sIVSInfo.nType = Dst->nType;
		m_sIVSInfo.part1 = Dst->part1;
		m_sIVSInfo.nStamp = Dst->nStamp;
		m_sIVSInfo.part2 = Dst->part2;
		m_sIVSInfo.nWidth = Dst->nWidth;
		m_sIVSInfo.nHeight = Dst->nHeight;
		m_sIVSInfo.part4 = Dst->part4;
		memcpy(m_sIVSInfo.part6, Dst->part6, 28);
		if ( m_part40 )
		{
			if ( m_sIVSInfo.part1 >= m_nStartFrame )
			{
				if ( m_part41 == -1 && m_sIVSInfo.part1 > m_nStartFrame )
					m_part41 = 1;
			}
			else
			{
				m_part41 = -1;
			}
			if ( m_part41 != 1 && m_sIVSInfo.part1 != m_nStartFrame )
			{
				reinterpret_cast<DISPLAY_PARA*>(Src)->part3  = 1;
				return -2147483646;
			}
			m_part40 = 0;
			m_part58 = 1;

			_DebugInfo("hytest: VR target frame arrived!\n");
		}
		result = 0;
	}
	return result;
}

int CHikVRenderer::DirectlyDisplay( BYTE* a2,ULONG a3,DISPLAY_PARA *Dst )
{
	int result; // eax@1

	result = GetDisplayPara(0, Dst);
	if ( !result )
	{
		m_sIVSInfo.pBuf = a2;
		m_sIVSInfo.nBufLen = a3;
		if ( Dst->part3 == 1 )
			result = 0;
		else
			result = DisplayPicture(a2, a3, 0, 0);
	}
	return result;
}

int CHikVRenderer::ClearVideoSample()
{
	int result; // eax@2

	if ( m_pSample )
		result = m_pSample->ResetBufList();
	else
		result = -2147483646;
	return result;
}

int CHikVRenderer::SetStartFrame( ULONG a2 )
{
	m_part41 = 0;
	m_nStartFrame = a2;
	m_part40 = 1;

	_DebugInfo("hytest: VR set target frame, framenum = %d!\n",a2);
	return 0;
}

int CHikVRenderer::SetPos()
{
	if ( m_part13 == 6 )
	{
		if ( !m_pSample )
			return -2147483646;
		m_pSample->ResetBufList();
		m_part56 = -1;
		m_part13 = 0;
	}
	return 0;
}

int CHikVRenderer::SetDisplayEngine( ULONG a2 )
{
	m_nDisplayEngine=a2;
}

int CHikVRenderer::Resume()
{
	return 0;
}

int CHikVRenderer::Play()
{
	m_part13=0;
	return 0;
}

int CHikVRenderer::Pause()
{
	return 0;
}

int CHikVRenderer::IsTimerNull( IVSPLAY_FRAME_INFO *a2 )
{
	int result; // eax@2

	if ( a2 )
	{
		memcpy(a2, &this->m_sIVSInfo, sizeof(IVSPLAY_FRAME_INFO));
		result = 1;
	}
	else
	{
		result = 0;
	}
	return result;
}

int CHikVRenderer::GetVideoTimeStamp( ULONG *a2 )
{
	int result; // eax@2
	BUF_NODE *node=NULL;

	if ( a2 )
	{		
		if ( m_pSample && (m_pSample->GetNode(&node, 0) , node) )
		{
			*a2 = reinterpret_cast<DISPLAY_PARA*>(node->data1)->nStamp;
			result = 0;
		}
		else
		{
			result = -2147483646;
		}
	}
	else
	{
		result = -2147483645;
	}
	return result;
}

int CHikVRenderer::GetOneFrameNeedDisplay( __int64 *a2,ULONG a3,float a4 )
{
	int result; // eax@5
	unsigned int v7; // qax@7
	unsigned int v9; // edi@8
	int v10; // eax@8
	int v11; // edi@11
	double v14; // st7@21
	double v15; // st6@21
	DISPLAY_PARA Dst; // [sp+Ch] [bp-4Ch]@3
	int v17k;
	BUF_NODE *v18=NULL; // [sp+54h] [bp-4h]@2

	if ( !m_pSample || (m_pSample->GetNode(&v18, 0), !v18) )
		return 0;
	if ( GetDisplayPara(v18->data1, &Dst) )
	{
		m_pSample->UsedDataNodeToSpareList(0);
		return 0;
	}

	v7 = Dst.part2 / a4;
	if ( v7 < a3 )
	{
		v9 = (a3 - v7) * 0.4;
		v17k = 0;
		m_pSample->GetDataNodeCount(&v17k);
		v10 = v17k - 1;
		if (v10 >= v9 )
			v10 = v9;
		if ( v10 > 0 )
		{
			v11 = v10;
			do
			{
				m_pSample->UsedDataNodeToSpareList(0);
				--v11;
			}
			while ( v11 );
		}
		m_pSample->GetNode(&v18, 0);
		if ( !v18 )
			return 0;
		GetDisplayPara(v18->data1, &Dst);
	}

	result = 1;

	if ( Dst.nStamp < m_part60 )
		m_part58 = 1;
	if ( Dst.nStamp - m_part60 >= 20000 )
		m_part58 = 1;

	if ( m_part58 )
	{
		m_part58 = 0;
		*a2 = 0;
		m_part59 = Dst.nStamp;
		m_part60 = Dst.nStamp;
	}
	else
	{
		v14 = *a2 * a3 * a4;
		v15 = Dst.nStamp - m_part59;

		if ( v14 < v15 && v15 - v14 >= 5.0 )
			return 0;
		m_part60 = Dst.nStamp;
		result = 1;
	}

	return result;
}

int CHikVRenderer::GetInput( IHikInput **a2 )
{
	int result; // eax@3

	if ( m_pVRInput && a2 )
	{
		*a2 = m_pVRInput;
		result = 0;
	}
	else
	{
		result = -2147483646;
	}
	return result;
}

int CHikVRenderer::GetCurrentFrameInfo( IVSPLAY_FRAME_INFO *a2 )
{
	int result; // eax@4
	BUF_NODE* v5; // [sp+4h] [bp-4h]@3

	if ( a2 && m_pSample)
	{
		v5 = 0;
		m_pSample->GetDisplayNode(&v5);
		if ( v5 )
		{
			memcpy(a2, &m_sIVSInfo, sizeof(IVSPLAY_FRAME_INFO));
			result = 0;
		}
		else
		{
			result = -2147483646;
		}
	}
	else
	{
		result = -2147483645;
	}
	return result;
}

int CHikVRenderer::FrameForward()
{
	m_part13=4;
	return 0;
}

int CHikVRenderer::FrameBack()
{
	m_part13=5;
	return 0;
}

int CHikVRenderer::EnableDisplayDevice( ULONG a2,ULONG a3 )
{
	return 0;
}

int CHikVRenderer::DisplayOneFrame( IVSPLAY_FRAME_INFO *a2,ULONG *a3,ULONG *a4 )
{
	BUF_NODE *v6=NULL; // ebx@3
	int result; // eax@6
	int a4k;
	int i;
	int v11;

	if ( !m_pVRInput || m_pSample == 0 )
		return -2147483646;

	m_pSample->GetSpareNodeCount(a3);
	m_pSample->GetDataNodeCount(a4);
	m_pSample->GetNode(&v6, 0);

	if ( !v6 )
	{
		_DebugInfo("hytest: no more video sample to display\n");
		for(i=0;i<4;++i)
			RefreshDisplayWindow(i, 0);
		return -2147483646;
	}
	a4k = Display(v6->data1, v6->part3, v6->data2, v6->part6, a2);
	v11 = m_pSample->UsedDataNodeToSpareList(reinterpret_cast<DISPLAY_PARA*>(v6->data1)->part3 != 1);
	--*a4;
	*a3 += v11;
	_DebugInfo("hytest: residual video sample is %d!\n",*a4);
	if ( a4k )
	{
		for(i=0;i<4;++i)
			RefreshDisplayWindow(i, 0);
		result = -2147483631;
	}
	else
	{
		result = 0;
	}
	return result;
}

int CHikVRenderer::Display( BYTE* Src,ULONG a3,BYTE* a4,ULONG a5,IVSPLAY_FRAME_INFO* Dst )
{
	int result; // eax@2
	DISPLAY_PARA v8={0}; // [sp+8h] [bp-40h]@1

	if ( GetDisplayPara( Src, &v8) )
	{
		result = -2147483645;
	}
	else
	{
		if ( v8.part3 == 1 )
		{
			Dst->nType = m_sIVSInfo.nType;
			Dst->part1 = m_sIVSInfo.part1;
			Dst->nStamp = m_sIVSInfo.nStamp;
			Dst->nHeight = m_sIVSInfo.nHeight;
			Dst->nWidth = m_sIVSInfo.nWidth;
			Dst->part2 = m_sIVSInfo.part2;
			memcpy(Dst->part6, m_sIVSInfo.part6, 28);
			_DebugInfo("hytest: Display one Skip frame, framenum = %d!\n",m_sIVSInfo.part1);
			result = 0;
		}
		else
		{
			m_sIVSInfo.pBuf = Src + 64;
			m_sIVSInfo.nBufLen = a3 - 64;
			memcpy(Dst, &m_sIVSInfo, sizeof(IVSPLAY_FRAME_INFO));
			_DebugInfo("hytest: Display one frame, framenum = %d!\n",m_sIVSInfo.part1);
			result = DisplayPicture(m_sIVSInfo.pBuf, m_sIVSInfo.nBufLen, a4, a5);
		}
	}
	return result;
}

int CHikVRenderer::Close()
{
	
}

int CHikVRenderer::NeedAdjustFrameRate( float a2 )
{
	double v2; // st7@1
	double v3; // st6@4
	double v4; // st7@10

	v2 = 1000.0 / (double)m_part37;
	v3 = a2 / v2;
	v4 = a2 - v2;

	return a2 >= 0.0625 && a2 < 1.0 && (v2 >= 1.0 ||  v3 >= 2.0 || v3 <= 0.5)
		|| a2 >= 1.0 && a2 <= 30.0 && (v2 >= 0.0625 && v2 < 1.0 || v4 > 3.0 || v4 < -3.0);
}

