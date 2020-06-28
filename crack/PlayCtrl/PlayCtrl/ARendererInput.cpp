#include "StdAfx.h"
#include "ARendererInput.h"

CARendererInput::CARendererInput(void)
{
	m_pAudRender=NULL;
}

CARendererInput::~CARendererInput(void)
{
	m_pAudRender=NULL;
}

int CARendererInput::SetParent( CHikARenderer* a2 )
{
	int result; // eax@2

	if ( a2 )
	{
		m_pAudRender = a2;
		result = 0;
	}
	else
	{
		result = -2147483645;
	}
	return result;
}

int CARendererInput::SetInputSample( CHikSample *a2 )
{
	 return -2147483632;
}

int CARendererInput::InputData( BYTE *Dst,ULONG a3,ULONG a4 )
{
	int result; // eax@3

	else
	if( a3==0)
		result = m_pAudRender->OpenSound( Dst, a4);
	else if ( a3 == 1 )
		result = m_pAudRender->InputData( Dst, a4);
	else
		result = -2147483632;
	return result;
}

