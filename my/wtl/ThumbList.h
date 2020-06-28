#pragma once
#include <atlcrack.h>

#include <vector_ptr.h>
#include <boost/circular_buffer.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/typeof/typeof.hpp>
//todo:先做成同步的

class IVirtualItem
{
public:
	virtual ~IVirtualItem(){}
	virtual LPTSTR getText()=0;
	virtual void *prepCache()=0;
	virtual void draw(void *pthis,LPNMLVCUSTOMDRAW lv,void *cache)=0;
	virtual void sel(LPNMLISTVIEW pnmv)=0;
};
//////////////////////////////////////////////////////////////////////////
template<class T, class TBase = CListViewCtrl, class TWinTraits = CControlWinTraits>
class ATL_NO_VTABLE CThumbListImpl : public CWindowImpl<T, TBase, TWinTraits>
	,public CCustomDraw<T>
{
public:
	DECLARE_WND_SUPERCLASS(NULL, TBase::GetWndClassName())

	CThumbListImpl(void){}
	virtual ~CThumbListImpl(void){}

	BEGIN_MSG_MAP(CThumbListImpl)
		REFLECTED_NOTIFY_CODE_HANDLER_EX(LVN_GETDISPINFO, OnLvnGetDispInfo)
		REFLECTED_NOTIFY_CODE_HANDLER_EX(LVN_ODCACHEHINT, OnODCacheHint)
		REFLECTED_NOTIFY_CODE_HANDLER_EX(LVN_ITEMCHANGED, OnLvnItemChanged)
		CHAIN_MSG_MAP_ALT(CCustomDraw<T>,1)
	END_MSG_MAP()

	virtual LRESULT OnLvnGetDispInfo(LPNMHDR pnmh)=0;
	virtual LRESULT OnODCacheHint(LPNMHDR pnmh)=0;
	virtual LRESULT OnLvnItemChanged(LPNMHDR pnmh)=0;
};
//////////////////////////////////////////////////////////////////////////
class ICirBuffer
{
public:
	virtual ~ICirBuffer(){}
	virtual void setLength(int len)=0;
	virtual int getLength()=0;
	virtual bool isCached(int id)=0;
	virtual void setBuffer(int id,void *buf)=0;
	virtual void *getBuffer(int id)=0;
	virtual void clear()=0;
#ifdef _DEBUG
	virtual void printID()=0;
#endif
};

template<class T>
class CCirBuffer:public ICirBuffer
{
public:
	CCirBuffer():m_idMap(128){}
	void setLength(int len){m_idMap.set_capacity(len);}
	int getLength(){return m_idMap.capacity();}
	bool isCached(int id)
	{
		for(BOOST_AUTO(it,m_idMap.begin());it!=m_idMap.end();++it)
			if(it->first==id)
				return true;
		return false;
	}
	void setBuffer(int id,void *buf)
	{
		for(BOOST_AUTO(it,m_idMap.begin());it!=m_idMap.end();++it)
			if(it->first==id)
				return;

		m_idMap.push_back(std::make_pair(id,boost::shared_ptr<T>(reinterpret_cast<T*>(buf))));
	}
	void* getBuffer(int id)
	{
		for(BOOST_AUTO(it,m_idMap.begin());it!=m_idMap.end();++it)
			if(it->first==id)
				return it->second.get();

		return NULL;
	}
	void clear(){m_idMap.clear();}
#ifdef _DEBUG
	void printID()
	{
		AtlTrace(_T("buf"));
		//std::wstring tt=_T("buf");
		//TCHAR tmp[20];
		for(BOOST_AUTO(it,m_idMap.begin());it!=m_idMap.end();++it)
		{
			AtlTrace(_T(",%d"),it->first);
			//_itot_s(it->first,tmp,_countof(tmp),10);
			//tt+=_T(',');
			//tt+=tmp;
		}
		AtlTrace(_T("\n"));
	}
#endif

protected:
	boost::circular_buffer<std::pair<int,boost::shared_ptr<T>>> m_idMap;
};
//////////////////////////////////////////////////////////////////////////

class CThumbList:public CThumbListImpl<CThumbList>
{
public:
	DECLARE_WND_CLASS(_T("CThumbList"));

	CThumbList():m_cache(NULL),m_lastSel(-1){}
	~CThumbList(){if(m_cache)delete m_cache;}
	//BOOL SubclassWindow(HWND hWnd);
template<class T>
	void init(int cx,int cy)
	{
		m_dummyImage.Create(cx,cy,ILC_COLOR24,0,0);
		SetImageList(m_dummyImage,LVSIL_NORMAL);
		SetExtendedListViewStyle(LVS_EX_DOUBLEBUFFER,LVS_EX_DOUBLEBUFFER);
		
		SetIconSpacing(cx+42,cy+20);

		m_cache=new CCirBuffer<T>();
	}
	//void setBufferLength(int len){m_cache.setLength(len);}
	void flush(){SetItemCount(m_itemList.size());}
	void AddItem(IVirtualItem *item,bool redraw=true);
	void clear(){DeleteAllItems();m_itemList.clear_delete();if(m_cache)m_cache->clear();}

	DWORD OnPrePaint(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/);
	DWORD OnItemPrePaint(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/);
	DWORD OnItemPostPaint(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/);

	LRESULT OnLvnGetDispInfo(LPNMHDR pnmh);
	LRESULT OnODCacheHint(LPNMHDR pnmh);
	LRESULT OnLvnItemChanged(LPNMHDR pnmh);

protected:
	void prepCache(int idstart,int idend){
		for(int i=idstart;i<=idend;++i)
			if(!m_cache->isCached(i))
				m_cache->setBuffer(i,m_itemList[i]->prepCache());
	}

	CImageList m_dummyImage;

	vector_ptr<IVirtualItem> m_itemList;
	ICirBuffer* m_cache;
	int m_lastSel;
};

