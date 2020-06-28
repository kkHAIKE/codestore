#pragma once
#include <Debug.h>

template<typename _T>
class CStdValArray
{
public:
	explicit CStdValArray(int iPreallocSize = 0):
		m_pVoid(NULL)
,		m_nCount(0)
,		m_iElementSize(sizeof(_T))
,		m_nAllocated(iPreallocSize)
	{
		ASSERT(iPreallocSize>=0);
		if(iPreallocSize>0)
		{
			m_pVoid=static_cast<_T*>(malloc(iPreallocSize * m_iElementSize));
			ASSERT(m_pVoid!=NULL);
		}
	}
	explicit CStdValArray(const CStdValArray<_T> &l_sva):
		m_pVoid(NULL)
,		m_nCount(0)
,		m_iElementSize(sizeof(_T))
,		m_nAllocated(0)
	{
		if(!l_sva.IsEmpty())
		{
			m_nCount=m_nAllocated=l_sva.m_nCount;
			m_pVoid=static_cast<_T*>(malloc(m_nAllocated * m_iElementSize));
			ASSERT(m_pVoid!=NULL);
			CopyMemory(m_pVoid,l_sva.m_pVoid,m_nCount*m_iElementSize);
		}
	}
	~CStdValArray()
	{
		if(m_pVoid!=NULL)
			free(m_pVoid);
	}
	CStdValArray<_T>& operator=(const CStdValArray<_T>& l_sva)
	{
		VERIFY(Resize(l_sva.m_nCount));
		m_nCount=l_sva.m_nCount;
		if(l_sva.m_nCount>0)
			CopyMemory(m_pVoid,l_sva.m_pVoid,m_nCount*m_iElementSize);
		return *this;
	}
 	void Empty()
	{
		m_nCount=0;
	}
 	bool Resize(int iSize)
	{
		if(iSize<0)
			return false;
		if(iSize==0)
		{
			if(m_pVoid!=NULL)
			{
				free(m_pVoid);
				m_pVoid=NULL;
			}
			m_nCount=m_nAllocated=0;
		}
		else if(iSize!=m_nAllocated)
		{
			m_nAllocated=iSize;
			m_pVoid=static_cast<_T*>(realloc(m_pVoid, m_nAllocated * m_iElementSize));
			if(m_pVoid==NULL)
				return false;
			if(m_nCount>m_nAllocated)
				m_nCount=m_nAllocated;
		}
		return true;
	}
 	bool IsEmpty() const
	{
		return m_nCount==0;
	}
 	int Find(const _T &iIndex) const
	{
		for(int i=0;i<m_nCount;++i)
		{
			if(m_pVoid[i]==iIndex)
				return i;
		}
		return -1;
	}
 	bool Add(const _T &pData)
	{
		return InsertAt(m_nCount,pData);
	}
 	bool SetAt(int iIndex, const _T &pData)
	{
		if(iIndex<0 || iIndex>=m_nCount)
			return false;
		m_pVoid[iIndex] = pData;
		return true;
	}
 	bool InsertAt(int iIndex,const _T &pData)
	{
		if(iIndex<0 || iIndex>m_nCount)
			return false;
		if(++m_nCount>=m_nAllocated) 
		{
			m_nAllocated*=2;
			//m_nAllocated+=10;
			if(m_nAllocated==0)
				m_nAllocated=10;
			m_pVoid=static_cast<_T*>(realloc(m_pVoid,m_nAllocated*m_iElementSize));
			if(m_pVoid==NULL)
				return false;
		}
		if(iIndex<m_nCount-1)
			::MoveMemory(&m_pVoid[iIndex + 1],&m_pVoid[iIndex],(m_nCount - iIndex - 1)*m_iElementSize);
		m_pVoid[iIndex] = pData;
		return true;
	}
 	bool Remove(int iIndex)
	{
		if(iIndex<0 || iIndex>=m_nCount)
			return false;
		if(iIndex <--m_nCount)
			::CopyMemory(m_pVoid+iIndex, m_pVoid+iIndex+1, (m_nCount - iIndex) * m_iElementSize);
		return true;
	}
	int GetSize() const
	{
		return m_nCount;
	}
	_T* GetData() const
	{
		return m_pVoid;
	}

	_T GetAt(int iIndex) const
	{
		ASSERT(iIndex>=0 && iIndex<m_nCount);
		return m_pVoid[nIndex];
	}
	_T& operator[] (int iIndex) const
	{
		ASSERT(iIndex>=0 && iIndex<m_nCount);
		return m_pVoid[iIndex];
	}

protected:
	_T* m_pVoid;
	const int m_iElementSize;
	int m_nCount;
	int m_nAllocated;
};

template<typename _T>
class CStdPtrArray:public CStdValArray<_T*>
{
public:
	explicit CStdPtrArray(int iPreallocSize = 0):
	  CStdValArray(iPreallocSize){};
	explicit CStdPtrArray(const CStdPtrArray<_T> &l_spa):
	  CStdValArray(l_spa){};
	  
	bool Remove_Delete(int iIndex)
	{
		if(iIndex<0 || iIndex>=m_nCount)
			return false;
		delete m_pVoid[iIndex];
		return Remove(iIndex);
	}
	bool Resize_Delete(int iSize)
	{
		if(iSize<0)
			return false;
		if(iSize<m_nCount)
		{
			for(int i=iSize;i<m_nCount;++i)
				delete m_pVoid[i];
		}
		return Resize(iSize);
	}
};
