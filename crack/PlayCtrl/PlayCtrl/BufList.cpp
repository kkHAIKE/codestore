#include "StdAfx.h"
#include "BufList.h"

CBufList::CBufList(void)
{
	m_pBegin=NULL;
	m_pEnd=NULL;
	m_nCount=0;
}

CBufList::~CBufList(void)
{
	RemoveAll();
}

void CBufList::RemoveAll()
{
	BUF_NODE *v2; // esi@7

	while ( 1 )
	{
		v2 = m_pBegin;
		if ( !m_pBegin )
			break;
		m_pBegin = v2->next;
		if ( v2->data1 )
		{
			_aligned_free(v2->data1);
			v2->data1 = NULL;
		}
		if ( v2->data2 )
		{
			_aligned_free(v2->data2);
			v2->data2 = NULL;
		}
		DeleteCriticalSection(&v2->cs);
		delete v2;
	}
	m_pEnd = NULL;
	m_nCount = 0;
}

int CBufList::InitBufList( DWORD a2,DWORD Size,DWORD a4,DWORD Alignment )
{
	BUF_NODE *v6; // esi@3
	DWORD i; // [sp+10h] [bp-14h]@1

	try
	{
		for (i=0;i < a2;++i)
		{
			v6 = new BUF_NODE;
			if ( !v6 )
			{
				throw 0;
			}
			memset(v6, 0,sizeof(BUF_NODE));
			v6->data1 = _aligned_malloc(Size, Alignment);
			if ( !v6->data1 )
			{
				throw 0;
			}
			memset(v6->data1,0, Size);
			if ( a4 )
			{
				v6->data2 = _aligned_malloc(a4, Alignment);
				if ( !v6->data2 )
				{
					throw 0;
				}
				memset(v6->data2, 0,a4);
			}
			v6->size1 = Size;
			v6->size2 = a4;
			InitializeCriticalSection(&v6->cs);
			AddTail(v6);
		}
	}catch(int)
	{
		RemoveAll();
		return 0;
	}
	return 1;
}

void CBufList::AddHead( BUF_NODE* a2 )
{
	if ( a2 )
	{
		if ( m_nCount )
		{
			a2->prev = m_pEnd;
			m_pEnd->next = a2;
			m_pEnd = m_pEnd->next;
		}
		else
		{
			m_pBegin = a2;
			m_pEnd = a2;
		}
		++m_nCount;
	}
}

void CBufList::AddHead( BUF_NODE* a2 )
{
	BUF_NODE *v2; // eax@1

	v2 = a2;
	if ( a2 )
	{
		if ( m_nCount )
		{
			a2->next = m_pBegin;
			m_pBegin->prev = a2;
			v2 = m_pBegin->prev;
		}
		else
		{
			m_pEnd = a2;
		}
		++m_nCount;
		m_pBegin = v2;
	}
}

int CBufList::GetEleCount()
{
	return m_nCount;
}

BUF_NODE* CBufList::GetHead()
{
	return m_pBegin;
}

BUF_NODE* CBufList::GetTail()
{
	return m_pEnd;
}

BUF_NODE* CBufList::RemoveHead()
{
	BUF_NODE *result; // eax@1

	result = m_pBegin;
	if ( m_pBegin )
	{
		m_pBegin = result->next;
		result->next = NULL;
		if ( m_pBegin )
			m_pBegin->prev = NULL;
		else
			m_pEnd = NULL;
		--m_nCount;
	}
	return result;
}

BUF_NODE* CBufList::RemoveTail()
{
	BUF_NODE *result; // eax@1

	result = m_pEnd;
	if ( result )
	{
		m_pEnd = result->prev;
		result->prev = NULL;
		if ( m_pEnd )
			m_pEnd->next = NULL;
		else
			m_pBegin = NULL;
		--m_nCount;
	}
	return result;
}
