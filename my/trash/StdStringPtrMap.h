#pragma once
#include <Debug.h>
#include <StdString.h>

template<typename _T>
class CStdStringPtrMap
{
public:

	class TITEM
	{
		friend class Ite;
		friend class CStdStringPtrMap;

	public:
		CStdString Key;
		_T Data;
	protected:
		TITEM * pNext;
	};

	class Ite
	{
		friend class CStdStringPtrMap;

	protected:
		TITEM** m_ptitem;
		TITEM** m_Slot;

	public:
		Ite(TITEM** ptitem=NULL,TITEM** Slot=NULL):m_ptitem(ptitem),m_Slot(Slot){};
		bool IsEnd() const
		{
			ASSERT(m_ptitem!=NULL);
			return *m_ptitem==reinterpret_cast<TITEM *>(-1);
		}
		TITEM* operator*() const
		{
			ASSERT(m_ptitem!=NULL);
			return *m_ptitem;
		}
		const Ite& operator++()
		{
			ASSERT(m_ptitem!=NULL);
			m_ptitem=&((*m_ptitem)->pNext);
			while(*m_ptitem==NULL)
			{
				m_ptitem=++m_Slot;
			}
			return *this;
		}
	};

	explicit CStdStringPtrMap(int nSize = 83):
		m_count(0)
	{
		ASSERT(nSize>0);
		m_nBuckets = nSize;
		m_aT = new TITEM*[nSize+1];
		m_aT[nSize]=reinterpret_cast<TITEM *>(-1);
		ZeroMemory(m_aT,nSize * sizeof(TITEM*));
	}
	~CStdStringPtrMap()
	{
		Empty();
	}

	void Empty()
	{
		int len = m_nBuckets;
		while(len--) 
		{
			TITEM* pItem = m_aT[len];
			while(pItem) 
			{
				TITEM* pKill=pItem;
				pItem=pItem->pNext;
				delete pKill;
			}
		}
		delete [] m_aT;

		m_count=0;
	}

	void Resize(int nSize = 83)
	{
		ASSERT(nSize>=0);

		Empty();

		if( nSize > 0 ) 
		{
			m_aT = new TITEM*[nSize+1];
			m_aT[nSize]=reinterpret_cast<TITEM *>(-1);
			ZeroMemory(m_aT,nSize * sizeof(TITEM*));
		}

		m_nBuckets = nSize;
	}
	bool Find(LPCTSTR key,Ite& ite) const
	{
		if( m_nBuckets == 0 || m_aT==NULL) 
			return false;

		UINT slot = HashKey(key) % m_nBuckets;
		TITEM** ppItem = &m_aT[slot];
		while( *ppItem ) 
		{
			if( (*ppItem)->Key == key ) 
			{
				ite=Ite(ppItem,&m_aT[slot]);
				return true;
			}
			ppItem = &((*ppItem)->pNext);
		}

		return false;
	}
	TITEM* Find(LPCTSTR key) const
	{
		if( m_nBuckets == 0 || m_aT==NULL) 
			return NULL;

		UINT slot = HashKey(key) % m_nBuckets;
		for(TITEM* pItem = m_aT[slot]; pItem; pItem = pItem->pNext ) 
		{
			if( pItem->Key == key ) 
			{
				return pItem;
			}        
		}

		return NULL;
	}

	_T Set(LPCTSTR key, const _T &pData)
	{
		if( m_nBuckets == 0 || m_aT==NULL) return pData;

		TITEM *pFind;
		if(pFind=Find(key))
		{
			_T pOldData=pFind->Data;
			pFind->Data=pData;
			return pOldData;
		}
		
		Insert(key, pData);
		return NULL;
	}
	bool Remove(Ite &ite)
	{
		if(ite.IsEnd())
			return false;
		TITEM* pKill = *(ite.m_ptitem);
		*(ite.m_ptitem) = (*(ite.m_ptitem))->pNext;
		delete pKill;

		while(*(ite.m_ptitem)==NULL)
		{
			ite.m_ptitem=++ite.m_Slot;
		}

		--m_count;
		return true;
	}
	bool Remove(LPCTSTR key)
	{
		if( m_nBuckets == 0 || m_aT==NULL) return false;

		UINT slot = HashKey(key) % m_nBuckets;
		TITEM** ppItem = &m_aT[slot];
		while( *ppItem ) 
		{
			if( (*ppItem)->Key == key ) 
			{
				TITEM* pKill = *ppItem;
				*ppItem = (*ppItem)->pNext;
				delete pKill;
				--m_count;
				return true;
			}
			ppItem = &((*ppItem)->pNext);
		}

		return false;
	}

	int GetSize() const
	{
		return m_count;
	}

	_T& operator[] (LPCTSTR key)
	{
		ASSERT(m_nBuckets!=0 && m_aT!=NULL);
		
		TITEM *pFind;
		if(pFind=Find(key))
			return pFind->Data;
		
		pFind=Insert(key,NULL);

		return pFind->Data;
	}
	Ite Begin()
	{
		for(int i=0;i<m_nBuckets;++i)
		{
			if(m_aT[i]!=NULL)
				return Ite(m_aT+i,m_aT+i);
		}
		return Ite(m_aT+m_nBuckets,m_aT+m_nBuckets);
	}

protected:
	TITEM* Insert(LPCTSTR key,const _T& pData)
	{
		UINT slot = HashKey(key) % m_nBuckets;

		TITEM* pItem = new TITEM;
		pItem->Key = key;
		pItem->Data = pData;
		pItem->pNext = m_aT[slot];

		m_aT[slot] = pItem;

		++m_count;
		return pItem;
	}

	UINT HashKey(LPCTSTR Key) const
	{
		UINT i = 0;
		SIZE_T len = _tcslen(Key);
		while( len-- > 0 ) i = (i << 5) + i + Key[len];
		return i;
	}
	TITEM** m_aT;
	int m_nBuckets;
	int m_count;

private:
	CStdStringPtrMap(const CStdStringPtrMap&);
	void operator=(const CStdStringPtrMap&);
};
