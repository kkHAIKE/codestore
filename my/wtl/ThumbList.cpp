#include "StdAfx.h"
#include "ThumbList.h"

DWORD CThumbList::OnPrePaint(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/)
{
	return CDRF_NOTIFYITEMDRAW;
}

DWORD CThumbList::OnItemPrePaint( int /*idCtrl*/, LPNMCUSTOMDRAW lpNMCustomDraw )
{
	LPNMLVCUSTOMDRAW lv=(LPNMLVCUSTOMDRAW)lpNMCustomDraw;

	//if(lv->nmcd.lItemlParam==NULL)
	//	return CDRF_DODEFAULT;

	if (lv->nmcd.uItemState & CDIS_SELECTED)
	{
		RECT rc;
		GetItemRect(lv->nmcd.dwItemSpec,&rc,LVIR_BOUNDS);
		CDC dc;
		dc.Attach(lv->nmcd.hdc);
		CBrush brush;
		brush.CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));
		dc.FillRect(&rc,brush);
		dc.Detach();
	}

	return CDRF_NOTIFYPOSTPAINT;
}

DWORD CThumbList::OnItemPostPaint(int /*idCtrl*/, LPNMCUSTOMDRAW lpNMCustomDraw)
{
	LPNMLVCUSTOMDRAW lv=(LPNMLVCUSTOMDRAW)lpNMCustomDraw;
	if(IsRectEmpty(&lv->nmcd.rc))
		return CDRF_DODEFAULT;

	void *cache=m_cache->getBuffer(lv->nmcd.dwItemSpec);
	if(cache)
	{
		m_itemList[lv->nmcd.dwItemSpec]->draw(this,lv,cache);
#ifdef _DEBUG
		AtlTrace("draw:%d\n",lv->nmcd.dwItemSpec);
#endif
	}

	return CDRF_SKIPPOSTPAINT;
}

// BOOL CThumbList::SubclassWindow( HWND hWnd )
// {
// 	ATLASSERT(::IsWindow(hWnd));
// 	BOOL bRet = CThumbListImpl<CThumbList>::SubclassWindow(hWnd);
// 	///////////////////////////////////////////
// 
// 	return bRet;
// }

LRESULT CThumbList::OnLvnGetDispInfo( LPNMHDR pnmh )
{
	NMLVDISPINFO* pnmv = (NMLVDISPINFO*)pnmh;
	if(pnmv->item.iItem==-1 || (pnmv->item.mask&LVIF_TEXT)==0)return 0;
	
	//pnmv->item.mask|=LVIF_PARAM;
	pnmv->item.pszText=m_itemList[pnmv->item.iItem]->getText();
	//pnmv->item.lParam=reinterpret_cast<LPARAM>();
	if(m_cache->getBuffer(pnmv->item.iItem)==NULL)
	{
		prepCache(pnmv->item.iItem,pnmv->item.iItem);
		//pnmv->item.lParam=reinterpret_cast<LPARAM>(m_cache->getBuffer(pnmv->item.iItem));
	}

	return 0;
}

LRESULT CThumbList::OnODCacheHint( LPNMHDR pnmh )
{
	NMLVCACHEHINT* pChachehint = (NMLVCACHEHINT*)pnmh;

	//prepCache(max(0,m_itemList.size()-10),m_itemList.size()-1);
	//prepCache(0,min(9,m_itemList.size()-1));
	prepCache(pChachehint->iFrom,pChachehint->iTo);

	//AtlTrace(_T("%d => %d\n"),pChachehint->iFrom,pChachehint->iTo);
#ifdef _DEBUG
	m_cache->printID();
#endif
	return 0;
}

void CThumbList::AddItem( IVirtualItem *item ,bool redraw)
{
	m_itemList.push_back(item);
	if(redraw)
		flush();
}

LRESULT CThumbList::OnLvnItemChanged( LPNMHDR pnmh )
{
	LPNMLISTVIEW pnmv = (LPNMLISTVIEW)pnmh;
	//If the iItem member of the structure pointed to by pnmv is -1, 
	//the change has been applied to all items in the list view.
	if(pnmv->iItem==-1 || (pnmv->uChanged&LVIF_STATE)==0 ||
		(pnmv->uNewState&LVIS_SELECTED)==0 || m_lastSel==pnmv->iItem) return 0;
	
	m_itemList[pnmv->iItem]->sel(pnmv);

	m_lastSel=pnmv->iItem;
	//AtlTrace(_T("%d => %d\n"),pnmv->uOldState,pnmv->uNewState);

	return 0;
}

