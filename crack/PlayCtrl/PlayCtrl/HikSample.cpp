#include "StdAfx.h"
#include "HikSample.h"

CHikSample::CHikSample(void)
{
	m_pDisplayNode = 0;
	InitializeCriticalSection(&m_cs);
}

CHikSample::~CHikSample(void)
{
	ReleaseBufList();
	DeleteCriticalSection(&m_cs);
}

int CHikSample::InitBufList( DWORD a2,DWORD Size,DWORD a4,DWORD Alignment )
{
	int v7; // esi@2

	EnterCriticalSection(&m_cs);
	if ( m_cSpareNode->InitBufList(a2, Size, a4, Alignment) )
		v7 = 0;
	else
		v7 = -2147483641;
	LeaveCriticalSection(&m_cs);
	return v7;
}

int CHikSample::AddNode( BUF_NODE *a2,int a3 )
{
	int v5=0;

	EnterCriticalSection(&m_cs);

	if ( !a3 )
	{
		m_cDataNode.AddHead(a2);
	}
	else if ( a3 == 1 )
	{
		m_cDataNode.AddTail(a2);
	}
	else if ( a3 == 2 )
	{
		m_cSpareNode.AddHead(a2);
	}
	else if ( a3 == 3 )
	{
		m_cSpareNode.AddTail(a2);
	}
	else v5 = -2147483645;

	LeaveCriticalSection(&m_cs);
	return v5;
}

int CHikSample::GetDataNodeCount( ULONG *a2 )
{
	EnterCriticalSection(&m_cs);
	*a2 = m_cDataNode->GetEleCount(&m_cDataNode);
	LeaveCriticalSection(&m_cs);
	return 0;
}

int CHikSample::GetDisplayNode( BUF_NODE** a2 )
{
	EnterCriticalSection(&m_cs);
	*a2 = m_pDisplayNode;
	LeaveCriticalSection(&m_cs);
	return 0;
}

int CHikSample::GetNode( BUF_NODE** a2,int a3 )
{
	int v5=0;

	EnterCriticalSection(&m_cs);

	if ( !a3 )
	{
		*a2=m_cDataNode.GetHead();
	}
	else if ( a3 == 1 )
	{
		*a2=m_cDataNode.GetTail();
	}
	else if ( a3 == 2 )
	{
		*a2=m_cSpareNode.GetHead();
	}
	else if ( a3 == 3 )
	{
		*a2=m_cSpareNode.GetTail();	
	}
	else
	{
		v5 = -2147483645;
		*a2 = NULL;
	}
	LeaveCriticalSection(&m_cs);
	return v5;
}

int CHikSample::GetSpareNodeCount( ULONG *a2 )
{
	EnterCriticalSection(&m_cs);
	*a2 = m_cSpareNode.GetEleCount();
	LeaveCriticalSection(&m_cs);
	return 0;
}

int CHikSample::ReconfigNode( BUF_NODE* a2,DWORD Size,DWORD Alignment )
{
	int v5;

	EnterCriticalSection(&m_cs);
	if ( Size )
	{
		if ( a2->data1 )
		{
			_aligned_free(a2->data1);
			a2->data1 = NULL;
			a2->data1 = _aligned_malloc(Size, Alignment);
			if ( a2->data1 )
			{
				a2->part3 = 0;
				a2->size1 = Size;
				v5 = 0;
			}
			else
			{
				v5 = -2147483641;
			}
		}
		else
		{
			v5 = -2147483646;
		}
	}
	else
	{
		v5 = -2147483645;
	}
	LeaveCriticalSection(&m_cs);
	return v5;
}

int CHikSample::ReleaseBufList()
{
	EnterCriticalSection(&m_cs);

	if ( m_pDisplayNode )
	{
		m_cSpareNode.AddHead(m_pDisplayNode);
		m_pDisplayNode = NULL;
	}
	m_cSpareNode.RemoveAll();
	m_cDataNode.RemoveAll();
	LeaveCriticalSection(&m_cs);
	return 0;
}

int CHikSample::RemoveNode( BUF_NODE** a2,int a3 )
{
	int v5=0;

	EnterCriticalSection(&m_cs);
	if ( !a3 )
	{
		*a2=m_cDataNode.RemoveHead();
	}
	if ( a3 == 1 )
	{
		*a2=m_cDataNode.RemoveTail();
	}
	if ( a3 == 2 )
	{
		*a2=m_cSpareNode.RemoveHead();
	}
	if ( a3 == 3 )
	{
		*a2=m_cSpareNode.RemoveTail();
	}
	else 
	{	
		v5 = -2147483645;
		*a2 = 0;
	}

	LeaveCriticalSection(&m_cs);
	return v5;
}

int CHikSample::ResetBufList()
{
	EnterCriticalSection(&m_cs);

	if ( m_cDataNode.GetEleCount() )
	{
		do
		{
			BUF_NODE* v5 = m_cDataNode.RemoveHead();
			m_cSpareNode.AddTail(v5);
		}
		while ( m_cDataNode.GetEleCount() );
	}
	LeaveCriticalSection(&m_cs);
	return 0;
}

int CHikSample::SetDisplayNode( BUF_NODE* a2,int a3 )
{
	EnterCriticalSection(&m_cs);

	if ( m_pDisplayNode )
		AddNode(m_pDisplayNode,a3);
	m_pDisplayNode = a2;
	LeaveCriticalSection(&m_cs);
	return 0;
}

int CHikSample::UsedDataNodeToSpareList( int a2 )
{
	int v7=0;

	EnterCriticalSection(&m_cs);
	BUF_NODE* v5 = m_cDataNode.RemoveHead();

	if ( v5 )
	{
		if ( a2 )
		{
			if ( m_pDisplayNode )
			{
				m_cSpareNode.AddTail(m_pDisplayNode);
				v7 = 1;
			}
			m_pDisplayNode = v5;
		}
		else
		{
			m_cSpareNode.AddTail(v5);
			v7 = 1;
		}
	}
	LeaveCriticalSection(&m_cs);
	return v7;
}

