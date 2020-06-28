#include "StdAfx.h"
#include "HikVRInput.h"

CHikVRInput::CHikVRInput(void)
{
	m_pVidRender=0;
	m_pPara=0;
}

CHikVRInput::~CHikVRInput(void)
{
	if(m_pPara)
	{delete m_pPara;m_pPara=NULL;}
}

int CHikVRInput::InputData( BYTE *Dst,ULONG a3,ULONG a4 )
{

	if ( !Dst )
		return -2147483646;
	if ( a3 )
	{
		if ( a3 != 1 )
			return -2147483632;

		if ( m_pVidRender )
			return m_pVidRender->DirectlyDisplay(Dst, a4, m_pPara);
		return -2147483646;
	}

	if ( m_pVidRender )
		m_pVidRender->GetDisplayPara(0, Dst);
	return 0;
}

int CHikVRInput::SetInputSample( CHikSample *a2 )
{
	return -2147483632;
}

void CHikVRInput::SetParent( CHikVRenderer* a2 )
{
	m_pVidRender=a2;
}
