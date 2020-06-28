
#include "StdAfx.h"
#include "UIlist.h"


/////////////////////////////////////////////////////////////////////////////////////
//
//
IMPLEMENT_DYNCREATE( CListUI )
CListUI::CListUI() : m_pCallback(NULL), m_iCurSel(-1), m_iExpandedItem(-1)
{
    m_pList = new CListBodyUI(this);
    m_pHeader = new CListHeaderUI;

    Add(m_pHeader);
    CVerticalLayoutUI::Add(m_pList);

    m_ListInfo.nColumns = 0;
    m_ListInfo.nFont = -1;
    m_ListInfo.uTextStyle = DT_VCENTER; // m_uTextStyle(DT_VCENTER | DT_END_ELLIPSIS)
    m_ListInfo.dwTextColor = 0xFF000000;
    m_ListInfo.dwBkColor = 0;
    m_ListInfo.dwSelectedTextColor = 0xFF000000;
    m_ListInfo.dwSelectedBkColor = 0xFFC1E3FF;
    m_ListInfo.dwHotTextColor = 0xFF000000;
    m_ListInfo.dwHotBkColor = 0xFFE9F5FF;
    m_ListInfo.dwDisabledTextColor = 0xFFCCCCCC;
    m_ListInfo.dwDisabledBkColor = 0xFFFFFFFF;
    m_ListInfo.dwLineColor = 0;
    m_ListInfo.bShowHtml = false;
    m_ListInfo.bExpandable = false;
    m_ListInfo.bMultiExpandable = false;
    ::ZeroMemory(&m_ListInfo.rcTextPadding, sizeof(m_ListInfo.rcTextPadding));
    ::ZeroMemory(&m_ListInfo.rcColumn, sizeof(m_ListInfo.rcColumn));
}

LPCTSTR CListUI::GetClass() const
{
    return _T("ListUI");
}

UINT CListUI::GetControlFlags() const
{
    return UIFLAG_TABSTOP;
}

LPVOID CListUI::GetInterface(LPCTSTR pstrName)
{
    if( _tcscmp(pstrName, _T("List")) == 0 ) return static_cast<IListUI*>(this);
    if( _tcscmp(pstrName, _T("ListOwner")) == 0 ) return static_cast<IListOwnerUI*>(this);
    return CVerticalLayoutUI::GetInterface(pstrName);
}

CControlUI* CListUI::GetItemAt(int iIndex) const
{
    return m_pList->GetItemAt(iIndex);
}

int CListUI::GetItemIndex(CControlUI* pControl) const
{
    if( pControl->GetInterface(_T("ListHeader")) != NULL ) return CVerticalLayoutUI::GetItemIndex(pControl);
    // We also need to recognize header sub-items
    if( pControl->GetInterface(_T("ListHeaderItem")) != NULL ) return m_pHeader->GetItemIndex(pControl);

    return m_pList->GetItemIndex(pControl);
}

bool CListUI::SetItemIndex(CControlUI* pControl, int iIndex)
{
    if( pControl->GetInterface(_T("ListHeader")) != NULL ) return CVerticalLayoutUI::SetItemIndex(pControl, iIndex);
    // We also need to recognize header sub-items
    if( pControl->GetInterface(_T("ListHeaderItem")) != NULL ) return m_pHeader->SetItemIndex(pControl, iIndex);

    int iOrginIndex = m_pList->GetItemIndex(pControl);
    if (iOrginIndex == -1) return false;

    if (!m_pList->SetItemIndex(pControl, iIndex)) return false;

    // The list items should know about us
    IListItemUI* pListItem = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
    if( pListItem != NULL ) {
		pListItem->SetIndex(iIndex);
	}

	if(index>iOrginIndex)
		for(int i=iOrginIndex;i<index;++i)
		{
			CControlUI* p = m_pList->GetItemAt(i);
			pListItem = static_cast<IListItemUI*>(p->GetInterface(_T("ListItem")));
			if( pListItem != NULL ) {
				 pListItem->SetIndex(pListItem->GetIndex() - 1);
			}
		}
	else if(index<iOrginIndex)
		for(int i=index+1;i<=iOrginIndex;++i)
		{
			CControlUI* p = m_pList->GetItemAt(i);
			pListItem = static_cast<IListItemUI*>(p->GetInterface(_T("ListItem")));
			if( pListItem != NULL ) {
				pListItem->SetIndex(pListItem->GetIndex() + 1);
			}
		}

//         pListItem->SetIndex(GetCount()); // 本来是GetCount() - 1的，不过后面有减一
//     }
// 
//     for(int i = iOrginIndex; i < m_pList->GetCount(); ++i)
//     {
//         CControlUI* p = m_pList->GetItemAt(i);
//         pListItem = static_cast<IListItemUI*>(p->GetInterface(_T("ListItem")));
//         if( pListItem != NULL ) {
//             pListItem->SetIndex(pListItem->GetIndex() - 1);
//         }
//     }

    SelectItem(FindSelectable(m_iCurSel, false));
    EnsureVisible(m_iCurSel);

    return true;
}

int CListUI::GetCount() const
{
    return m_pList->GetCount();
}

bool CListUI::Add(CControlUI* pControl)
{
    // Override the Add() method so we can add items specifically to
    // the intended widgets. Headers are assumed to be
    // answer the correct interface so we can add multiple list headers.
    if( pControl->GetInterface(_T("ListHeader")) != NULL ) {
		//如果原来的Header为空则替换
        if( m_pHeader != pControl && m_pHeader->GetCount() == 0 ) {
            CVerticalLayoutUI::Remove(m_pHeader);
            m_pHeader = dynamic_cast<CListHeaderUI*>(pControl);
        }
        return CVerticalLayoutUI::AddAt(pControl, 0);
    }
    // We also need to recognize header sub-items
	//如果是列头则用Header添加
    if( pControl->GetInterface(_T("ListHeaderItem")) != NULL ) return m_pHeader->Add(pControl);
    // The list items should know about us
    IListItemUI* pListItem = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
    if( pListItem != NULL ) {
        pListItem->SetOwner(this);
        pListItem->SetIndex(GetCount());
    }
    return m_pList->Add(pControl);
}

bool CListUI::AddAt(CControlUI* pControl, int iIndex)
{
    // Override the AddAt() method so we can add items specifically to
    // the intended widgets. Headers and are assumed to be
    // answer the correct interface so we can add multiple list headers.
    if( pControl->GetInterface(_T("ListHeader")) != NULL ) return CVerticalLayoutUI::AddAt(pControl, iIndex);
    // We also need to recognize header sub-items
    if( pControl->GetInterface(_T("ListHeaderItem")) != NULL ) return m_pHeader->AddAt(pControl, iIndex);

    if (!m_pList->AddAt(pControl, iIndex)) return false;

    // The list items should know about us
    IListItemUI* pListItem = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
    if( pListItem != NULL ) {
        pListItem->SetOwner(this);
        pListItem->SetIndex(iIndex);
    }

    for(int i = iIndex + 1; i < m_pList->GetCount(); ++i)
    {
        CControlUI* p = m_pList->GetItemAt(i);
        pListItem = static_cast<IListItemUI*>(p->GetInterface(_T("ListItem")));
        if( pListItem != NULL ) {
            pListItem->SetIndex(pListItem->GetIndex() + 1);
        }
    }
    return true;
}

bool CListUI::Remove(CControlUI* pControl)
{
    if( pControl->GetInterface(_T("ListHeader")) != NULL ) return CVerticalLayoutUI::Remove(pControl);
    // We also need to recognize header sub-items
    if( pControl->GetInterface(_T("ListHeaderItem")) != NULL ) return m_pHeader->Remove(pControl);

    int iIndex = m_pList->GetItemIndex(pControl);
    if (iIndex == -1) return false;

//     if (!m_pList->RemoveAt(iIndex)) return false;
// 
//     for(int i = iIndex; i < m_pList->GetCount(); ++i)
//     {
//         CControlUI* p = m_pList->GetItemAt(i);
//         IListItemUI* pListItem = static_cast<IListItemUI*>(p->GetInterface(_T("ListItem")));
//         if( pListItem != NULL ) {
//             pListItem->SetIndex(pListItem->GetIndex() - 1);
//         }
//     }
// 
//     SelectItem(FindSelectable(m_iCurSel, false));
//     EnsureVisible(m_iCurSel);
    return RemoveAt(iIndex);
}

bool CListUI::RemoveAt(int iIndex)
{
    if (!m_pList->RemoveAt(iIndex)) return false;

    for(int i = iIndex; i < m_pList->GetCount(); ++i)
    {
        CControlUI* p = m_pList->GetItemAt(i);
        IListItemUI* pListItem = static_cast<IListItemUI*>(p->GetInterface(_T("ListItem")));
        if( pListItem != NULL ) {
            pListItem->SetIndex(pListItem->GetIndex() - 1);
        }
    }

    SelectItem(FindSelectable(m_iCurSel, false));
    EnsureVisible(m_iCurSel);
    return true;
}

void CListUI::RemoveAll()
{
    m_iCurSel = -1;
    m_iExpandedItem = -1;
    m_pList->RemoveAll();
}

void CListUI::SetPos(RECT rc)
{
    CVerticalLayoutUI::SetPos(rc);
    if( m_pHeader == NULL ) return;
    // Determine general list information and the size of header columns
    m_ListInfo.nColumns = MIN(m_pHeader->GetCount(), UILIST_MAX_COLUMNS);
    // The header/columns may or may not be visible at runtime. In either case
    // we should determine the correct dimensions...

	//在主窗口setpos的时候获取全部的列宽
	bool bSetted=false;
    if( !m_pHeader->IsVisible() ) {
        m_pHeader->SetInternVisible(true);
		//只设置了宽
        m_pHeader->SetPos(CRect(rc.left, 0, rc.right, 0));
		bSetted=true;
    }
    int iOffset = m_pList->GetScrollPos().cx;
    for( int i = 0; i < m_ListInfo.nColumns; ++i ) {
        CControlUI* pControl = m_pHeader->GetItemAt(i);
        if( !pControl->IsVisible() ) continue;
        if( pControl->IsFloat() ) continue;

        RECT rcPos = pControl->GetPos();
        if( iOffset > 0 ) {
            rcPos.left -= iOffset;
            rcPos.right -= iOffset;
            pControl->SetPos(rcPos);
        }
        m_ListInfo.rcColumn[i] = pControl->GetPos();
    }
    if( bSetted ) {
        m_pHeader->SetInternVisible(false);
    }
}

void CListUI::Event(TEventUI& event)
{
    if( !IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND ) {
        if( m_pParent != NULL ) m_pParent->Event(event);
        else CVerticalLayoutUI::Event(event);
        return;
    }

//     if( event.Type == UIEVENT_SETFOCUS ) 
//     {
//         m_bFocused = true;
//         return;
//     }
//     if( event.Type == UIEVENT_KILLFOCUS ) 
//     {
//         m_bFocused = false;
//         return;
//     }

    switch( event.Type ) {
    case UIEVENT_KEYDOWN:
        switch( event.chKey ) {
        case VK_UP:
            SelectItem(FindSelectable(m_iCurSel - 1, false));
            EnsureVisible(m_iCurSel);
            return;
        case VK_DOWN:
            SelectItem(FindSelectable(m_iCurSel + 1, true));
            EnsureVisible(m_iCurSel);
            return;
//         case VK_PRIOR:
//             PageUp();
//             return;
//         case VK_NEXT:
//             PageDown();
//             return;
        case VK_HOME:
            SelectItem(FindSelectable(0, false));
            EnsureVisible(m_iCurSel);
            return;
        case VK_END:
            SelectItem(FindSelectable(GetCount() - 1, true));
            EnsureVisible(m_iCurSel);
            return;
			//在item flag里加入Return
//         case VK_RETURN:
//             if( m_iCurSel != -1 ) GetItemAt(m_iCurSel)->Activate();
//             return;
            }
        break;
		//滚轮应该不能选择
//     case UIEVENT_SCROLLWHEEL:
//         {
//             switch( LOWORD(event.wParam) ) {
//             case SB_LINEUP:
//                 SelectItem(FindSelectable(m_iCurSel - 1, false));
//                 EnsureVisible(m_iCurSel);
//                 return;
//             case SB_LINEDOWN:
//                 SelectItem(FindSelectable(m_iCurSel + 1, true));
//                 EnsureVisible(m_iCurSel);
//                 return;
//             }
//         }
//         break;
    }
    CVerticalLayoutUI::Event(event);
}

CListHeaderUI* CListUI::GetHeader() const
{
    return m_pHeader;
}

CContainerUI* CListUI::GetList() const
{
    return m_pList;
}

int CListUI::GetCurSel() const
{
	return m_iCurSel;
}

bool CListUI::SelectItem(int iIndex)
{
    if( iIndex == m_iCurSel ) return true;

    // We should first unselect the currently selected item
    if( m_iCurSel >= 0 ) {
        CControlUI* pControl = GetItemAt(m_iCurSel);
        if( pControl != NULL) {
            IListItemUI* pListItem = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
            if( pListItem != NULL ) pListItem->Select(false);
        }

        m_iCurSel = -1;
    }

    CControlUI* pControl = GetItemAt(iIndex);
    if( pControl == NULL || !pControl->IsVisible()||!pControl->IsEnabled() ) return false;

    IListItemUI* pListItem = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
    if( pListItem == NULL ) return false;
    m_iCurSel = iIndex;
    if( !pListItem->Select(true) ) {
        m_iCurSel = -1;
        return false;
    }
    pControl->SetFocus();
    if( m_pManager != NULL ) {
        m_pManager->SendNotify(this, _T("itemselect"));
    }

    return true;
}

TListInfoUI* CListUI::GetListInfo()
{
    return &m_ListInfo;
}

int CListUI::GetChildPadding() const
{
    return m_pList->GetChildPadding();
}

void CListUI::SetChildPadding(int iPadding)
{
    m_pList->SetChildPadding(iPadding);
}

void CListUI::SetItemFont(int index)
{
	if(m_ListInfo.nFont==index)return;
    m_ListInfo.nFont = index;
    NeedUpdate();
}

void CListUI::SetItemTextStyle(UINT uStyle)
{
	if(m_ListInfo.uTextStyle==uStyle)return;
    m_ListInfo.uTextStyle = uStyle;
    NeedUpdate();
}

void CListUI::SetItemTextPadding(RECT rc)
{
	if(::EqualRect(& m_ListInfo.rcTextPadding,&rc))return;
    m_ListInfo.rcTextPadding = rc;
    NeedUpdate();
}

void CListUI::SetItemTextColor(DWORD dwTextColor)
{
	if(m_ListInfo.dwTextColor==dwTextColor)return;
    m_ListInfo.dwTextColor = dwTextColor;
    NeedUpdate();
}

void CListUI::SetItemBkColor(DWORD dwBkColor)
{
	if(m_ListInfo.dwBkColor==dwBkColor)return;
    m_ListInfo.dwBkColor = dwBkColor;
    Invalidate();
}

void CListUI::SetItemImage(LPCTSTR pStrImage)
{
    m_ListInfo.sImage = pStrImage;
    Invalidate();
}

void CListUI::SetSelectedItemTextColor(DWORD dwTextColor)
{
	if(m_ListInfo.dwSelectedTextColor==dwTextColor)return;
    m_ListInfo.dwSelectedTextColor = dwTextColor;
    Invalidate();
}

void CListUI::SetSelectedItemBkColor(DWORD dwBkColor)
{
	if(m_ListInfo.dwSelectedBkColor==dwBkColor)return;
    m_ListInfo.dwSelectedBkColor = dwBkColor;
    Invalidate();
}

void CListUI::SetSelectedItemImage(LPCTSTR pStrImage)
{
    m_ListInfo.sSelectedImage = pStrImage;
    Invalidate();
}

void CListUI::SetHotItemTextColor(DWORD dwTextColor)
{
	if(m_ListInfo.dwHotTextColor==dwTextColor)return;
    m_ListInfo.dwHotTextColor = dwTextColor;
    Invalidate();
}

void CListUI::SetHotItemBkColor(DWORD dwBkColor)
{
	if(m_ListInfo.dwHotBkColor==dwBkColor)return;
    m_ListInfo.dwHotBkColor = dwBkColor;
    Invalidate();
}

void CListUI::SetHotItemImage(LPCTSTR pStrImage)
{
    m_ListInfo.sHotImage = pStrImage;
    Invalidate();
}

void CListUI::SetDisabledItemTextColor(DWORD dwTextColor)
{
	if(m_ListInfo.dwDisabledTextColor==dwTextColor)return;
    m_ListInfo.dwDisabledTextColor = dwTextColor;
    Invalidate();
}

void CListUI::SetDisabledItemBkColor(DWORD dwBkColor)
{
	if(m_ListInfo.dwDisabledBkColor==dwBkColor)return;
    m_ListInfo.dwDisabledBkColor = dwBkColor;
    Invalidate();
}

void CListUI::SetDisabledItemImage(LPCTSTR pStrImage)
{
    m_ListInfo.sDisabledImage = pStrImage;
    Invalidate();
}

void CListUI::SetItemLineColor(DWORD dwLineColor)
{
	if(m_ListInfo.dwLineColor==dwLineColor)return;
    m_ListInfo.dwLineColor = dwLineColor;
    Invalidate();
}

bool CListUI::IsItemShowHtml()
{
    return m_ListInfo.bShowHtml;
}

void CListUI::SetItemShowHtml(bool bShowHtml)
{
    if( m_ListInfo.bShowHtml == bShowHtml ) return;

    m_ListInfo.bShowHtml = bShowHtml;
    NeedUpdate();
}

void CListUI::SetExpanding(bool bExpandable)
{
    m_ListInfo.bExpandable = bExpandable;
}

void CListUI::SetMultiExpanding(bool bMultiExpandable)
{
    m_ListInfo.bMultiExpandable = bMultiExpandable;
}

bool CListUI::ExpandItem(int iIndex, bool bExpand /*= true*/)
{
    if( !m_ListInfo.bExpandable ) return false;
    if( m_iExpandedItem >= 0 && !m_ListInfo.bMultiExpandable) {
		//已有扩展的了，且不能多扩展，则收起原来的扩展
        CControlUI* pControl = GetItemAt(m_iExpandedItem);
        if( pControl != NULL ) {
            IListItemUI* pItem = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
            if( pItem != NULL ) pItem->Expand(false);
        }
        m_iExpandedItem = -1;
    }
    if( bExpand ) {
        CControlUI* pControl = GetItemAt(iIndex);
        if( pControl == NULL ) return false;
        if( !pControl->IsVisible() ) return false;
        IListItemUI* pItem = static_cast<IListItemUI*>(pControl->GetInterface(_T("ListItem")));
        if( pItem == NULL ) return false;
        m_iExpandedItem = iIndex;
        if( !pItem->Expand(true) ) {
            m_iExpandedItem = -1;
            return false;
        }
    }
    NeedUpdate();
    return true;
}

int CListUI::GetExpandedItem() const
{
    return m_iExpandedItem;
}

void CListUI::EnsureVisible(int iIndex)
{
    if( m_iCurSel < 0 ) return;
    RECT rcItem = m_pList->GetItemAt(iIndex)->GetPos();
    RECT rcList = m_pList->GetPos();
    RECT rcListInset = m_pList->GetInset();

    rcList.left += rcListInset.left;
    rcList.top += rcListInset.top;
    rcList.right -= rcListInset.right;
    rcList.bottom -= rcListInset.bottom;

    CScrollbarUI* pHorizontalScrollbar = m_pList->GetHorizontalScrollbar();
    if( pHorizontalScrollbar && pHorizontalScrollbar->IsVisible() ) rcList.bottom -= pHorizontalScrollbar->GetFixedHeight();

    int iPos = m_pList->GetScrollPos().cy;
	//已经看到了
    if( rcItem.top >= rcList.top && rcItem.bottom < rcList.bottom ) return;
    int dy = 0;
    if( rcItem.top < rcList.top ) dy = rcItem.top - rcList.top;
    if( rcItem.bottom > rcList.bottom ) dy = rcItem.bottom - rcList.bottom;
	
	if(dy==0) return;
	SIZE sz = m_pList->GetScrollPos();
	sz.cy+=dy;
	m_pList->SetScrollPos(sz);
    //Scroll(0, dx);
}

// void CListUI::Scroll(int dx, int dy)
// {
//     if( dx == 0 && dy == 0 ) return;
// 	SIZE sz = m_pList->GetScrollPos();
// 	m_pList->SetScrollPos(CSize(sz.cx + dx, sz.cy + dy));
// }

void CListUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
    if( _tcscmp(pstrName, _T("header")) == 0 ) GetHeader()->SetVisible(_tcscmp(pstrValue, _T("hidden")) != 0);
    if( _tcscmp(pstrName, _T("headerbkimage")) == 0 ) GetHeader()->SetBkImage(pstrValue);
    else if( _tcscmp(pstrName, _T("expanding")) == 0 ) SetExpanding(_tcscmp(pstrValue, _T("true")) == 0);
    else if( _tcscmp(pstrName, _T("multiexpanding")) == 0 ) SetMultiExpanding(_tcscmp(pstrValue, _T("true")) == 0);
    else if( _tcscmp(pstrName, _T("itemfont")) == 0 ) SetItemFont(_ttoi(pstrValue));
    else if( _tcscmp(pstrName, _T("itemalign")) == 0 ) {
        if( _tcsstr(pstrValue, _T("left")) != NULL ) {
            m_ListInfo.uTextStyle &= ~(DT_CENTER | DT_RIGHT);
            m_ListInfo.uTextStyle |= DT_LEFT;
        }
        if( _tcsstr(pstrValue, _T("center")) != NULL ) {
            m_ListInfo.uTextStyle &= ~(DT_LEFT | DT_RIGHT);
            m_ListInfo.uTextStyle |= DT_CENTER;
        }
        if( _tcsstr(pstrValue, _T("right")) != NULL ) {
            m_ListInfo.uTextStyle &= ~(DT_LEFT | DT_CENTER);
            m_ListInfo.uTextStyle |= DT_RIGHT;
        }
		if ( _tcsstr( pstrValue, _T( "top" ) ) != NULL ) {
			m_ListInfo.uTextStyle &= ~( DT_BOTTOM | DT_VCENTER );
			m_ListInfo.uTextStyle |= DT_TOP;
		}
		if ( _tcsstr( pstrValue, _T( "bottom" ) ) != NULL ) {
			m_ListInfo.uTextStyle &= ~( DT_TOP | DT_VCENTER );
			m_ListInfo.uTextStyle |= DT_BOTTOM;
		}
    }
    if( _tcscmp(pstrName, _T("itemtextpadding")) == 0 ) {
        SetItemTextPadding(RectFromString(pstrValue));
    }
    else if( _tcscmp(pstrName, _T("itemtextcolor")) == 0 ) {
        if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
        DWORD clrColor = _tcstoul(pstrValue, NULL, 16);
        SetItemTextColor(clrColor);
    }
    else if( _tcscmp(pstrName, _T("itembkcolor")) == 0 ) {
        if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
        DWORD clrColor = _tcstoul(pstrValue, NULL, 16);
        SetItemBkColor(clrColor);
    }
    else if( _tcscmp(pstrName, _T("itemimage")) == 0 ) SetItemImage(pstrValue);
    else if( _tcscmp(pstrName, _T("itemselectedtextcolor")) == 0 ) {
        if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
        DWORD clrColor = _tcstoul(pstrValue,NULL, 16);
        SetSelectedItemTextColor(clrColor);
    }
    else if( _tcscmp(pstrName, _T("itemselectedbkcolor")) == 0 ) {
        if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
        DWORD clrColor = _tcstoul(pstrValue,NULL, 16);
        SetSelectedItemBkColor(clrColor);
    }
    else if( _tcscmp(pstrName, _T("itemselectedimage")) == 0 ) SetSelectedItemImage(pstrValue);
    else if( _tcscmp(pstrName, _T("itemhottextcolor")) == 0 ) {
        if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
        DWORD clrColor = _tcstoul(pstrValue, NULL, 16);
        SetHotItemTextColor(clrColor);
    }
    else if( _tcscmp(pstrName, _T("itemhotbkcolor")) == 0 ) {
        if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
        DWORD clrColor = _tcstoul(pstrValue, NULL, 16);
        SetHotItemBkColor(clrColor);
    }
    else if( _tcscmp(pstrName, _T("itemhotimage")) == 0 ) SetHotItemImage(pstrValue);
    else if( _tcscmp(pstrName, _T("itemdisabledtextcolor")) == 0 ) {
        if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
        DWORD clrColor = _tcstoul(pstrValue, NULL, 16);
        SetDisabledItemTextColor(clrColor);
    }
    else if( _tcscmp(pstrName, _T("itemdisabledbkcolor")) == 0 ) {
        if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
        DWORD clrColor = _tcstoul(pstrValue, NULL, 16);
        SetDisabledItemBkColor(clrColor);
    }
    else if( _tcscmp(pstrName, _T("itemdisabledimage")) == 0 ) SetDisabledItemImage(pstrValue);
    else if( _tcscmp(pstrName, _T("itemlinecolor")) == 0 ) {
        if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
        DWORD clrColor = _tcstoul(pstrValue, NULL, 16);
        SetItemLineColor(clrColor);
    }
    else if( _tcscmp(pstrName, _T("itemshowhtml")) == 0 ) SetItemShowHtml(_tcscmp(pstrValue, _T("true")) == 0);
    else CVerticalLayoutUI::SetAttribute(pstrName, pstrValue);
}

IListCallbackUI* CListUI::GetTextCallback() const
{
    return m_pCallback;
}

void CListUI::SetTextCallback(IListCallbackUI* pCallback)
{
    m_pCallback = pCallback;
}

SIZE CListUI::GetScrollPos() const
{
    return m_pList->GetScrollPos();
}

SIZE CListUI::GetScrollRange() const
{
    return m_pList->GetScrollRange();
}

void CListUI::SetScrollPos(SIZE szPos)
{
    m_pList->SetScrollPos(szPos);
}

void CListUI::LineUp()
{
    m_pList->LineUp();
}

void CListUI::LineDown()
{
    m_pList->LineDown();
}

void CListUI::PageUp()
{
    m_pList->PageUp();
}

void CListUI::PageDown()
{
    m_pList->PageDown();
}

void CListUI::HomeUp()
{
    m_pList->HomeUp();
}

void CListUI::EndDown()
{
    m_pList->EndDown();
}

void CListUI::LineLeft()
{
    m_pList->LineLeft();
}

void CListUI::LineRight()
{
    m_pList->LineRight();
}

void CListUI::PageLeft()
{
    m_pList->PageLeft();
}

void CListUI::PageRight()
{
    m_pList->PageRight();
}

void CListUI::HomeLeft()
{
    m_pList->HomeLeft();
}

void CListUI::EndRight()
{
    m_pList->EndRight();
}

void CListUI::EnableScrollBar(bool bEnableVertical, bool bEnableHorizontal)
{
    m_pList->EnableScrollBar(bEnableVertical, bEnableHorizontal);
}

CScrollbarUI* CListUI::GetVerticalScrollbar() const
{
    return m_pList->GetVerticalScrollbar();
}

CScrollbarUI* CListUI::GetHorizontalScrollbar() const
{
    return m_pList->GetHorizontalScrollbar();
}

/////////////////////////////////////////////////////////////////////////////////////
//
//


CListBodyUI::CListBodyUI(CListUI* pOwner) : m_pOwner(pOwner)
{
    ASSERT(m_pOwner);
   // SetInset(CRect(0,0,0,0));
}

void CListBodyUI::SetScrollPos(SIZE szPos)
{
    int cx = 0;
    int cy = 0;
    if( m_pVerticalScrollbar && m_pVerticalScrollbar->IsVisible() ) {
        int iLastScrollPos = m_pVerticalScrollbar->GetScrollPos();
        m_pVerticalScrollbar->SetScrollPos(szPos.cy);
        cy = m_pVerticalScrollbar->GetScrollPos() - iLastScrollPos;
    }

    if( m_pHorizontalScrollbar && m_pHorizontalScrollbar->IsVisible() ) {
        int iLastScrollPos = m_pHorizontalScrollbar->GetScrollPos();
        m_pHorizontalScrollbar->SetScrollPos(szPos.cx);
        cx = m_pHorizontalScrollbar->GetScrollPos() - iLastScrollPos;
    }

    if( cx == 0 && cy == 0 ) return;

    RECT rcPos;
    for( int it2 = 0; it2 < m_items.GetSize(); ++it2 ) {
        CControlUI* pControl = m_items[it2];
        if( !pControl->IsVisible() ) continue;
        if( pControl->IsFloat() ) continue;

        rcPos = pControl->GetPos();
        rcPos.left -= cx;
        rcPos.right -= cx;
        rcPos.top -= cy;
        rcPos.bottom -= cy;
        pControl->SetPos(rcPos);
    }

    Invalidate();

	//以上和容器基类一致
	//以下根据x偏移移动列头，以及保存列块大小
    if( cx != 0 && m_pOwner ) {
        CListHeaderUI* pHeader = m_pOwner->GetHeader();
        if( pHeader == NULL ) return;
        TListInfoUI* pInfo = m_pOwner->GetListInfo();
        pInfo->nColumns = MIN(pHeader->GetCount(), UILIST_MAX_COLUMNS);

		//下面代码可能是要在不可视状态也要正确生成Headitem坐标
		//但在主可视子不可视的时候会出错会导致全可视出现，所以要设置flag
		bool bSetted=false;
		if( !pHeader->IsVisible() ) {pHeader->SetInternVisible(true);bSetted=true;}
        for( int i = 0; i < pInfo->nColumns; i++ ) {
            CControlUI* pControl = pHeader->GetItemAt(i);
            if( !pControl->IsVisible() ) continue;
            if( pControl->IsFloat() ) continue;

            RECT rcPos = pControl->GetPos();
            rcPos.left -= cx;
            rcPos.right -= cx;
            pControl->SetPos(rcPos);
            pInfo->rcColumn[i] = pControl->GetPos();
        }
        if( bSetted ) pHeader->SetInternVisible(false);
    }
}

void CListBodyUI::SetPos(RECT rc)
{
	CControlUI::SetPos( rc );
	rc = m_rcItem;

	// Adjust for inset
	rc.left += m_rcInset.left;
	rc.top += m_rcInset.top;
	rc.right -= m_rcInset.right;
	rc.bottom -= m_rcInset.bottom;

	if ( m_items.GetSize() == 0 ) {
		ProcessScrollbar( rc, 0, 0 );
		return;
	}

	// Determine the minimum size
	//这个是实际控制区域，加上了水平滚动条的范围
	SIZE szAvailable = { rc.right - rc.left, rc.bottom - rc.top };

	//记录空长度数
	int nAdjustables = 0;
	int cyFixed = 0;
	int nEstimateNum = 0;
	int cxNeeded = 0;
	for ( int it1 = 0; it1 < m_items.GetSize(); ++it1 ) {
		CControlUI* pControl = m_items[it1];
		if ( !pControl->IsVisible() ) continue;
		if ( pControl->IsFloat() ) continue;
		SIZE sz = pControl->EstimateSize( szAvailable );
		if ( sz.cy == 0 ) {
			nAdjustables++;
		}
		else {
			if ( sz.cy < pControl->GetMinHeight() ) sz.cy = pControl->GetMinHeight();
			if ( sz.cy > pControl->GetMaxHeight() ) sz.cy = pControl->GetMaxHeight();
		}
		cyFixed += sz.cy + pControl->GetPadding().top + pControl->GetPadding().bottom;

		if ( sz.cx < pControl->GetMinWidth() ) sz.cx = pControl->GetMinWidth();
		if ( sz.cx > pControl->GetMaxWidth() )sz.cx = pControl->GetMaxWidth();
		sz.cx += pControl->GetPadding().left + pControl->GetPadding().right;

		cxNeeded = MAX(cxNeeded,sz.cx) ;

		nEstimateNum++;
	}
	//计算完所有子控件的高
	cyFixed += ( nEstimateNum - 1 ) * m_iChildPadding;

	if( m_pOwner ) {
		CListHeaderUI* pHeader = m_pOwner->GetHeader();
		if( pHeader != NULL && pHeader->GetCount() > 0 ) {
			cxNeeded = MAX(cxNeeded, pHeader->EstimateSize(CSize(rc.right - rc.left, rc.bottom - rc.top)).cx);
		}
	}

	bool bflagSetV=false,bflagSetH=false;
	ProcessScrollbar( rc, cxNeeded, cyFixed );
	if ( m_pVerticalScrollbar && m_pVerticalScrollbar->IsVisible() )
	{rc.right -= m_pVerticalScrollbar->GetFixedWidth();bflagSetV=true;}
	if ( m_pHorizontalScrollbar && m_pHorizontalScrollbar->IsVisible() )
	{rc.bottom -= m_pHorizontalScrollbar->GetFixedHeight();bflagSetH=true;}
	ProcessScrollbar( rc, cxNeeded, cyFixed );
	if (!bflagSetV && m_pVerticalScrollbar && m_pVerticalScrollbar->IsVisible())
		rc.right -= m_pVerticalScrollbar->GetFixedWidth();
	if (!bflagSetH && m_pHorizontalScrollbar && m_pHorizontalScrollbar->IsVisible() )
		rc.bottom -= m_pHorizontalScrollbar->GetFixedHeight();

	if ( m_pVerticalScrollbar && m_pVerticalScrollbar->IsVisible() ) {
		RECT rcScrollbarPos = { rc.right, rc.top, rc.right + m_pVerticalScrollbar->GetFixedWidth(), rc.bottom };
		m_pVerticalScrollbar->SetPos( rcScrollbarPos );
	}
	if ( m_pHorizontalScrollbar && m_pHorizontalScrollbar->IsVisible() ) {
		RECT rcScrollbarPos = { rc.left, rc.bottom, rc.right , rc.bottom + m_pHorizontalScrollbar->GetFixedHeight() };
		m_pHorizontalScrollbar->SetPos( rcScrollbarPos );
	}
	szAvailable.cx = rc.right - rc.left; szAvailable.cy = rc.bottom - rc.top;
	if ( m_pHorizontalScrollbar && m_pHorizontalScrollbar->IsEnabled() )
		szAvailable.cx += m_pHorizontalScrollbar->GetScrollRange();

	// Place elements
	cxNeeded=0;
	int cyNeeded = 0;
	int cyExpand = 0;
	//如果客户区比所有控件要多则cyExpand=0高控件的平均剩余值
	if ( nAdjustables > 0 ) cyExpand = MAX( 0, ( szAvailable.cy - cyFixed ) / nAdjustables );
	// Position the elements
	SIZE szRemaining = szAvailable;
	int iPosY = rc.top;
	if ( m_pVerticalScrollbar ) {
		iPosY -= m_pVerticalScrollbar->GetScrollPos();
	}
	int iPosX = rc.left;
	if ( m_pHorizontalScrollbar ) {
		iPosX -= m_pHorizontalScrollbar->GetScrollPos();
	}
	//计算出滚动后显示的坐标
	int iAdjustable = 0;
	int cyFixedRemaining = cyFixed;
	for ( int it2 = 0; it2 < m_items.GetSize(); it2++ ) {
		//先设置完浮动的
		CControlUI* pControl = m_items[it2];
		if ( !pControl->IsVisible() ) continue;
		if ( pControl->IsFloat() ) {
			SetFloatPos( it2 );
			continue;
		}

		RECT rcPadding = pControl->GetPadding();
		szRemaining.cy -= rcPadding.top;
		SIZE sz = pControl->EstimateSize( szRemaining );
		if ( sz.cy == 0 ) {
			iAdjustable++;
			sz.cy = cyExpand;
			// Distribute remaining to last element (usually round-off left-overs)
			//最后的采用剩下的部分
			if ( iAdjustable == nAdjustables ) {
				sz.cy = MAX( 0, szRemaining.cy - rcPadding.bottom - cyFixedRemaining );
			}
			if ( sz.cy < pControl->GetMinHeight() ) sz.cy = pControl->GetMinHeight();
			if ( sz.cy > pControl->GetMaxHeight() ) sz.cy = pControl->GetMaxHeight();
		}
		else {
			if ( sz.cy < pControl->GetMinHeight() ) sz.cy = pControl->GetMinHeight();
			if ( sz.cy > pControl->GetMaxHeight() ) sz.cy = pControl->GetMaxHeight();
			cyFixedRemaining -= sz.cy;
		}

		//强行拉伸
		sz.cx = MAX( 0, szAvailable.cx - rcPadding.left - rcPadding.right );

		if ( sz.cx < pControl->GetMinWidth() ) sz.cx = pControl->GetMinWidth();
		if ( sz.cx > pControl->GetMaxWidth() ) sz.cx = pControl->GetMaxWidth();

		RECT rcCtrl = { iPosX + rcPadding.left, iPosY + rcPadding.top, iPosX + rcPadding.left + sz.cx, iPosY + sz.cy + rcPadding.top  };//+ rcPadding.bottom
		pControl->SetPos( rcCtrl );

		iPosY += sz.cy + m_iChildPadding + rcPadding.top + rcPadding.bottom;
		cyNeeded += sz.cy + rcPadding.top + rcPadding.bottom;
		szRemaining.cy -= sz.cy + m_iChildPadding + rcPadding.bottom;
		cxNeeded = MAX(cxNeeded,sz.cx) ;
	}
	cyNeeded += ( nEstimateNum - 1 ) * m_iChildPadding;

	if( m_pOwner ) {
		CListHeaderUI* pHeader = m_pOwner->GetHeader();
		if( pHeader != NULL && pHeader->GetCount() > 0 ) {
			cxNeeded = MAX(cxNeeded, pHeader->EstimateSize(CSize(rc.right - rc.left, rc.bottom - rc.top)).cx);
		}
	}
	ProcessScrollbar( rc, cxNeeded, cyNeeded );
// 
//     CControlUI::SetPos(rc);
//     rc = m_rcItem;
// 
//     // Adjust for inset
//     rc.left += m_rcInset.left;
//     rc.top += m_rcInset.top;
//     rc.right -= m_rcInset.right;
//     rc.bottom -= m_rcInset.bottom;
//     if( m_pVerticalScrollbar && m_pVerticalScrollbar->IsVisible() ) rc.right -= m_pVerticalScrollbar->GetFixedWidth();
//     if( m_pHorizontalScrollbar && m_pHorizontalScrollbar->IsVisible() ) rc.bottom -= m_pHorizontalScrollbar->GetFixedHeight();
// 
//     // Determine the minimum size
//     SIZE szAvailable = { rc.right - rc.left, rc.bottom - rc.top };
//     if( m_pHorizontalScrollbar && m_pHorizontalScrollbar->IsVisible() ) 
//         szAvailable.cx += m_pHorizontalScrollbar->GetScrollRange();
// 
//     int cxNeeded = 0;
//     int nAdjustables = 0;
//     int cyFixed = 0;
//     int nEstimateNum = 0;
//     for( int it1 = 0; it1 < m_items.GetSize(); it1++ ) {
//         CControlUI* pControl = static_cast<CControlUI*>(m_items[it1]);
//         if( !pControl->IsVisible() ) continue;
//         if( pControl->IsFloat() ) continue;
//         SIZE sz = pControl->EstimateSize(szAvailable);
//         if( sz.cy == 0 ) {
//             nAdjustables++;
//         }
//         else {
//             if( sz.cy < pControl->GetMinHeight() ) sz.cy = pControl->GetMinHeight();
//             if( sz.cy > pControl->GetMaxHeight() ) sz.cy = pControl->GetMaxHeight();
//         }
//         cyFixed += sz.cy + pControl->GetPadding().top + pControl->GetPadding().bottom;
// 
//         RECT rcPadding = pControl->GetPadding();
//         sz.cx = MAX(sz.cx, 0);
//         if( sz.cx < pControl->GetMinWidth() ) sz.cx = pControl->GetMinWidth();
//         if( sz.cx > pControl->GetMaxWidth() ) sz.cx = pControl->GetMaxWidth();
//         cxNeeded = MAX(cxNeeded, sz.cx);
//         nEstimateNum++;
//     }
//     cyFixed += (nEstimateNum - 1) * m_iChildPadding;
// 
// 
//     // Place elements
//     int cyNeeded = 0;
//     int cyExpand = 0;
//     if( nAdjustables > 0 ) cyExpand = MAX(0, (szAvailable.cy - cyFixed) / nAdjustables);
//     // Position the elements
//     SIZE szRemaining = szAvailable;
//     int iPosY = rc.top;
//     if( m_pVerticalScrollbar && m_pVerticalScrollbar->IsVisible() ) {
//         iPosY -= m_pVerticalScrollbar->GetScrollPos();
//     }
//     int iPosX = rc.left;
//     if( m_pHorizontalScrollbar && m_pHorizontalScrollbar->IsVisible() ) {
//         iPosX -= m_pHorizontalScrollbar->GetScrollPos();
//     }
//     int iAdjustable = 0;
//     int cyFixedRemaining = cyFixed;
//     for( int it2 = 0; it2 < m_items.GetSize(); it2++ ) {
//         CControlUI* pControl = static_cast<CControlUI*>(m_items[it2]);
//         if( !pControl->IsVisible() ) continue;
//         if( pControl->IsFloat() ) {
//             SetFloatPos(it2);
//             continue;
//         }
// 
//         RECT rcPadding = pControl->GetPadding();
//         szRemaining.cy -= rcPadding.top;
//         SIZE sz = pControl->EstimateSize(szRemaining);
//         if( sz.cy == 0 ) {
//             iAdjustable++;
//             sz.cy = cyExpand;
//             // Distribute remaining to last element (usually round-off left-overs)
//             if( iAdjustable == nAdjustables ) {
//                 sz.cy = MAX(0, szRemaining.cy - rcPadding.bottom - cyFixedRemaining);
//             } 
//             if( sz.cy < pControl->GetMinHeight() ) sz.cy = pControl->GetMinHeight();
//             if( sz.cy > pControl->GetMaxHeight() ) sz.cy = pControl->GetMaxHeight();
//         }
//         else {
//             if( sz.cy < pControl->GetMinHeight() ) sz.cy = pControl->GetMinHeight();
//             if( sz.cy > pControl->GetMaxHeight() ) sz.cy = pControl->GetMaxHeight();
//             cyFixedRemaining -= sz.cy;
//         }
// 
//         sz.cx = MAX(cxNeeded, szAvailable.cx - rcPadding.left - rcPadding.right);
// 
//         if( sz.cx < pControl->GetMinWidth() ) sz.cx = pControl->GetMinWidth();
//         if( sz.cx > pControl->GetMaxWidth() ) sz.cx = pControl->GetMaxWidth();
// 
//         RECT rcCtrl = { iPosX + rcPadding.left, iPosY + rcPadding.top, iPosX + rcPadding.left + sz.cx, iPosY + sz.cy + rcPadding.top + rcPadding.bottom };
//         pControl->SetPos(rcCtrl);
// 
//         iPosY += sz.cy + m_iChildPadding + rcPadding.top + rcPadding.bottom;
//         cyNeeded += sz.cy + rcPadding.top + rcPadding.bottom;
//         szRemaining.cy -= sz.cy + m_iChildPadding + rcPadding.bottom;
//     }
//     cyNeeded += (nEstimateNum - 1) * m_iChildPadding;
// 
//     if( m_pHorizontalScrollbar != NULL ) {
//         if( cxNeeded > rc.right - rc.left ) {
//             if( m_pHorizontalScrollbar->IsVisible() ) {
//                 m_pHorizontalScrollbar->SetScrollRange(cxNeeded - (rc.right - rc.left));
//             }
//             else {
//                 m_pHorizontalScrollbar->SetVisible(true);
//                 m_pHorizontalScrollbar->SetScrollRange(cxNeeded - (rc.right - rc.left));
//                 m_pHorizontalScrollbar->SetScrollPos(0);
//                 rc.bottom -= m_pHorizontalScrollbar->GetFixedHeight();
//             }
//         }
//         else {
//             if( m_pHorizontalScrollbar->IsVisible() ) {
//                 m_pHorizontalScrollbar->SetVisible(false);
//                 m_pHorizontalScrollbar->SetScrollRange(0);
//                 m_pHorizontalScrollbar->SetScrollPos(0);
//                 rc.bottom += m_pHorizontalScrollbar->GetFixedHeight();
//             }
//         }
//     }
// 
//     // Process the scrollbar
//     ProcessScrollbar(rc, cxNeeded, cyNeeded);
}
/////////////////////////////////////////////////////////////////////////////////////
//
//

// CListHeaderUI::CListHeaderUI()
// {
// }

LPCTSTR CListHeaderUI::GetClass() const
{
    return _T("ListHeaderUI");
}

LPVOID CListHeaderUI::GetInterface(LPCTSTR pstrName)
{
    if( _tcscmp(pstrName, _T("ListHeader")) == 0 ) return static_cast<CListHeaderUI*>(this);
    return CHorizontalLayoutUI::GetInterface(pstrName);
}

SIZE CListHeaderUI::EstimateSize(SIZE szAvailable)
{
    SIZE cXY = {0, m_cxyFixed.cy};
    if( cXY.cy == 0 && m_pManager != NULL ) {
        cXY.cy = m_pManager->GetDefaultFontInfo().tmHeight + 6;
    }

    for( int it = 0; it < m_items.GetSize(); ++it ) {
        cXY.cx +=  m_items[it]->EstimateSize(szAvailable).cx;
    }

    return cXY;
}
void CListHeaderUI::Event(TEventUI& event)
{
	if(event.Type==UIEVENT_SCROLLWHEEL)
	if(m_pParent && IsEnabled())
	{
		IListUI *listui=static_cast<IListUI*>(m_pParent->GetInterface("List"));
		if(listui)
			return listui->GetList()->Event(event);
	}
	CHorizontalLayoutUI::Event(event);
}
/////////////////////////////////////////////////////////////////////////////////////
//
//
IMPLEMENT_DYNCREATE( CListHeaderItemUI )
CListHeaderItemUI::CListHeaderItemUI() : m_bDragable(true), m_uButtonState(0), m_iSepWidth(4)
{
	m_uTextStyle=DT_SINGLELINE|DT_VCENTER | DT_CENTER;
    ptLastMouse.x = ptLastMouse.y = 0;
    SetMinWidth(16);
}

LPCTSTR CListHeaderItemUI::GetClass() const
{
    return _T("ListHeaderItemUI");
}

LPVOID CListHeaderItemUI::GetInterface(LPCTSTR pstrName)
{
    if( _tcscmp(pstrName, _T("ListHeaderItem")) == 0 ) return static_cast<CListHeaderItemUI*>(this);
    return CLabelUI::GetInterface(pstrName);
}

UINT CListHeaderItemUI::GetControlFlags() const
{
    if( IsEnabled() && m_iSepWidth != 0 ) return UIFLAG_SETCURSOR;
    else return 0;
}

void CListHeaderItemUI::SetEnabled(bool bEnable)
{
    CControlUI::SetEnabled(bEnable);
    if( !IsEnabled() ) {
        m_uButtonState = 0;
    }
}

void CListHeaderItemUI::SetDragable(bool bDragable)
{
    m_bDragable = bDragable;
    if ( !m_bDragable ) m_uButtonState &= ~UISTATE_CAPTURED;
}

void CListHeaderItemUI::SetSepWidth(int iWidth)
{
    m_iSepWidth = iWidth;
}

void CListHeaderItemUI::SetNormalImage(LPCTSTR pStrImage)
{
    m_sNormalImage = pStrImage;
    Invalidate();
}

LPCTSTR CListHeaderItemUI::GetHotImage()
{
    return m_sHotImage;
}

void CListHeaderItemUI::SetHotImage(LPCTSTR pStrImage)
{
    m_sHotImage = pStrImage;
    Invalidate();
}

LPCTSTR CListHeaderItemUI::GetPushedImage()
{
    return m_sPushedImage;
}

void CListHeaderItemUI::SetPushedImage(LPCTSTR pStrImage)
{
    m_sPushedImage = pStrImage;
    Invalidate();
}

LPCTSTR CListHeaderItemUI::GetFocusedImage()
{
    return m_sFocusedImage;
}

void CListHeaderItemUI::SetFocusedImage(LPCTSTR pStrImage)
{
    m_sFocusedImage = pStrImage;
    Invalidate();
}

// LPCTSTR CListHeaderItemUI::GetSepImage() const
// {
//     return m_sSepImage;
// }
// 
// void CListHeaderItemUI::SetSepImage(LPCTSTR pStrImage)
// {
//     m_sSepImage = pStrImage;
//     Invalidate();
// }

void CListHeaderItemUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
    if( _tcscmp(pstrName, _T("dragable")) == 0 ) SetDragable(_tcscmp(pstrValue, _T("true")) == 0);
    else if( _tcscmp(pstrName, _T("sepwidth")) == 0 ) SetSepWidth(_ttoi(pstrValue));
    else if( _tcscmp(pstrName, _T("normalimage")) == 0 ) SetNormalImage(pstrValue);
    else if( _tcscmp(pstrName, _T("hotimage")) == 0 ) SetHotImage(pstrValue);
    else if( _tcscmp(pstrName, _T("pushedimage")) == 0 ) SetPushedImage(pstrValue);
    else if( _tcscmp(pstrName, _T("focusedimage")) == 0 ) SetFocusedImage(pstrValue);
    //else if( _tcscmp(pstrName, _T("sepimage")) == 0 ) SetSepImage(pstrValue);
    else CLabelUI::SetAttribute(pstrName, pstrValue);
}

void CListHeaderItemUI::Event(TEventUI& event)
{
    if( !IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND ) {
        if( m_pParent != NULL ) m_pParent->Event(event);
        else CControlUI::Event(event);
        return;
    }

     if( event.Type == UIEVENT_SETFOCUS ) 
     {
         Invalidate();
     }
     if( event.Type == UIEVENT_KILLFOCUS ) 
     {
         Invalidate();
     }
    if( event.Type == UIEVENT_BUTTONDOWN || event.Type == UIEVENT_DBLCLICK )
    {
        if( !IsEnabled() ) return;
        RECT rcSeparator = GetThumbRect();
        if( ::PtInRect(&rcSeparator, event.ptMouse) ) {
            if( m_bDragable ) {
                m_uButtonState |= UISTATE_CAPTURED;
                ptLastMouse = event.ptMouse;
            }
        }
        else {
            m_uButtonState |= UISTATE_PUSHED;
            Invalidate();
        }
        return;
    }
    if( event.Type == UIEVENT_BUTTONUP )
    {
        if( (m_uButtonState & UISTATE_CAPTURED) != 0 ) {
            m_uButtonState &= ~UISTATE_CAPTURED;
//             if( GetParent() ) 
//                 GetParent()->NeedParentUpdate();
        }
        else if( (m_uButtonState & UISTATE_PUSHED) != 0 ) {
			if(m_pManager)m_pManager->SendNotify(this, _T("headerclick"));
            m_uButtonState &= ~UISTATE_PUSHED;	
            Invalidate();
        }
        return;
    }
    if( event.Type == UIEVENT_MOUSEMOVE )
    {
        if( (m_uButtonState & UISTATE_CAPTURED) != 0 ) {
            RECT rc = m_rcItem;
            if( m_iSepWidth >= 0 ) {
                rc.right -= ptLastMouse.x - event.ptMouse.x;
            }
            else {
                rc.left -= ptLastMouse.x - event.ptMouse.x;
            }
            
            if( rc.right - rc.left > GetMinWidth() ) {
                m_cxyFixed.cx = rc.right - rc.left;
                ptLastMouse = event.ptMouse;
                if( GetParent() ) 
                    GetParent()->NeedParentUpdate();
				//NeedParentUpdate是因为需要更新关联列
            }
        }
        return;
    }
    if( event.Type == UIEVENT_SETCURSOR )
    {
        RECT rcSeparator = GetThumbRect();
        if( m_bDragable && ::PtInRect(&rcSeparator, event.ptMouse) ) {//IsEnabled() && 
            ::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEWE)));
            return;
        }
    }
    if( event.Type == UIEVENT_MOUSEENTER )
    {
        if( IsEnabled() ) {
            m_uButtonState |= UISTATE_HOT;
            Invalidate();
        }
        return;
    }
    if( event.Type == UIEVENT_MOUSELEAVE )
    {
        if( IsEnabled() ) {
            m_uButtonState &= ~UISTATE_HOT;
            Invalidate();
        }
        return;
    }
    CControlUI::Event(event);
}

SIZE CListHeaderItemUI::EstimateSize(SIZE szAvailable)
{
    if( m_cxyFixed.cy == 0 ) return CSize(m_cxyFixed.cx, m_pManager->GetDefaultFontInfo().tmHeight + 14);
    return CControlUI::EstimateSize(szAvailable);
}

RECT CListHeaderItemUI::GetThumbRect() const
{
    if( m_iSepWidth >= 0 ) return CRect(m_rcItem.right - m_iSepWidth, m_rcItem.top, m_rcItem.right, m_rcItem.bottom);
    else return CRect(m_rcItem.left, m_rcItem.top, m_rcItem.left - m_iSepWidth, m_rcItem.bottom);
}

void CListHeaderItemUI::PaintStatusImage(GRAPHorHDC& gorh)
{
    if( IsFocused() ) m_uButtonState |= UISTATE_FOCUSED;
    else m_uButtonState &= ~ UISTATE_FOCUSED;


	if ( ( m_uButtonState & UISTATE_PUSHED ) != 0 ) {
		if ( !m_sPushedImage.IsEmpty() ) {
			if ( !DrawImage( gorh, ( LPCTSTR )m_sPushedImage ) ) m_sPushedImage.Empty();
			else return;
		}
	}
	else if ( ( m_uButtonState & UISTATE_HOT ) != 0 ) {
		if ( !m_sHotImage.IsEmpty() ) {
			if ( !DrawImage( gorh, ( LPCTSTR )m_sHotImage ) ) m_sHotImage.Empty();
			else return;
		}
	}
	else if ( ( m_uButtonState & UISTATE_FOCUSED ) != 0 ) {
		if ( !m_sFocusedImage.IsEmpty() ) {
			if ( !DrawImage( gorh, ( LPCTSTR )m_sFocusedImage ) ) m_sFocusedImage.Empty();
			else return;
		}
	}

    if( !m_sNormalImage.IsEmpty() ) {
         if( !DrawImage(gorh, (LPCTSTR)m_sNormalImage) ) m_sNormalImage.Empty();
    }

	//增加默认绘制
//     if( !m_sSepImage.IsEmpty() ) {
//         RECT rcThumb = GetThumbRect();
//         rcThumb.left -= m_rcItem.left;
//         rcThumb.top -= m_rcItem.top;
//         rcThumb.right -= m_rcItem.left;
//         rcThumb.bottom -= m_rcItem.top;
// 
//         //m_sSepImageModify.Empty();
//         m_sSepImageModify.FormatTinyBuf(_T("dest='%d,%d,%d,%d'"), rcThumb.left, rcThumb.top, rcThumb.right, rcThumb.bottom);
//         if( !DrawImage(hDC, (LPCTSTR)m_sSepImage, (LPCTSTR)m_sSepImageModify) ) m_sSepImage.Empty();
//     }
}

// void CListHeaderItemUI::PaintText(GRAPHorHDC& gorh)
// {
//     if( m_dwTextColor == 0 ) m_dwTextColor = m_pManager->GetDefaultFontColor();
// 
//     if( m_sText.IsEmpty() ) return;
// 
//     if( m_bShowHtml )
//         CRenderEngine::DrawHtmlText(gorh, m_pManager, m_rcItem, m_sText, m_dwTextColor, \
// 		DT_SINGLELINE | m_uTextStyle);
//     else
//         CRenderEngine::DrawText(gorh, m_pManager, m_rcItem, m_sText, m_dwTextColor, \
//         m_iFont, DT_SINGLELINE | m_uTextStyle);
// }

/////////////////////////////////////////////////////////////////////////////////////
//
//

CListElementUI::CListElementUI() : 
m_iIndex(-1),
m_pOwner(NULL), 
m_bSelected(false),
m_uButtonState(0)
{
}

LPCTSTR CListElementUI::GetClass() const
{
    return _T("ListElementUI");
}

UINT CListElementUI::GetControlFlags() const
{
    return UIFLAG_WANTRETURN;
}

LPVOID CListElementUI::GetInterface(LPCTSTR pstrName)
{
    if( _tcscmp(pstrName, _T("ListItem")) == 0 ) return static_cast<IListItemUI*>(this);
    return CControlUI::GetInterface(pstrName);
}

IListOwnerUI* CListElementUI::GetOwner()
{
    return m_pOwner;
}

void CListElementUI::SetOwner(CControlUI* pOwner)
{
    m_pOwner = static_cast<IListOwnerUI*>(pOwner->GetInterface(_T("ListOwner")));
}

void CListElementUI::SetVisible(bool bVisible)
{
    CControlUI::SetVisible(bVisible);
    if( !IsVisible() && m_bSelected)
    {
        m_bSelected = false;
        if( m_pOwner != NULL ) m_pOwner->SelectItem(-1);
    }
}

void CListElementUI::SetEnabled(bool bEnable)
{
    CControlUI::SetEnabled(bEnable);
    if( !IsEnabled() ) {
        m_uButtonState = 0;
    }
}

int CListElementUI::GetIndex() const
{
    return m_iIndex;
}

void CListElementUI::SetIndex(int iIndex)
{
    m_iIndex = iIndex;
}

// void CListElementUI::Invalidate()
// {
//     if( !IsVisible() ) return;
// 
//     if( GetParent() ) {
//         CContainerUI* pParentContainer = static_cast<CContainerUI*>(GetParent()->GetInterface(_T("Container")));
//         if( pParentContainer ) {
//             RECT rc = pParentContainer->GetPos();
//             RECT rcInset = pParentContainer->GetInset();
//             rc.left += rcInset.left;
//             rc.top += rcInset.top;
//             rc.right -= rcInset.right;
//             rc.bottom -= rcInset.bottom;
//             CScrollbarUI* pVerticalScrollbar = pParentContainer->GetVerticalScrollbar();
//             if( pVerticalScrollbar && pVerticalScrollbar->IsVisible() ) rc.right -= pVerticalScrollbar->GetFixedWidth();
//             CScrollbarUI* pHorizontalScrollbar = pParentContainer->GetHorizontalScrollbar();
//             if( pHorizontalScrollbar && pHorizontalScrollbar->IsVisible() ) rc.bottom -= pHorizontalScrollbar->GetFixedHeight();
// 
//             RECT invalidateRc = m_rcItem;
//             if( !::IntersectRect(&invalidateRc, &m_rcItem, &rc) ) 
//             {
//                 return;
//             }
// 
//             CControlUI* pParent = GetParent();
//             RECT rcTemp;
//             RECT rcParent;
//             while( pParent = pParent->GetParent() )
//             {
//                 rcTemp = invalidateRc;
//                 rcParent = pParent->GetPos();
//                 if( !::IntersectRect(&invalidateRc, &rcTemp, &rcParent) ) 
//                 {
//                     return;
//                 }
//             }
// 
//             if( m_pManager != NULL ) m_pManager->Invalidate(invalidateRc);
//         }
//         else {
//             CControlUI::Invalidate();
//         }
//     }
//     else {
//         CControlUI::Invalidate();
//     }
// }

bool CListElementUI::Activate()
{
    if( !CControlUI::Activate() ) return false;
    if( m_pManager != NULL ) m_pManager->SendNotify(this, _T("itemactivate"));
    return true;
}

bool CListElementUI::IsSelected() const
{
    return m_bSelected;
}

bool CListElementUI::Select(bool bSelect)
{
    if( !IsEnabled() ) return false;
    if( bSelect == m_bSelected ) return true;
    m_bSelected = bSelect;
    if( bSelect && m_pOwner != NULL ) m_pOwner->SelectItem(m_iIndex);
    Invalidate();

    return true;
}

bool CListElementUI::IsExpanded() const
{
    return false;
}

bool CListElementUI::Expand(bool /*bExpand = true*/)
{
    return false;
}

void CListElementUI::Event(TEventUI& event)
{
    if( !IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND ) {
        if( m_pOwner != NULL ) m_pOwner->Event(event);
        else CControlUI::Event(event);
        return;
    }

    if( event.Type == UIEVENT_DBLCLICK )
    {
        if( IsEnabled() ) {
            Activate();
            Invalidate();
        }
        return;
    }
    if( event.Type == UIEVENT_KEYDOWN && IsEnabled() )
    {
        if( event.chKey == VK_RETURN ) {
            Activate();
            Invalidate();
            return;
        }
    }
    // An important twist: The list-item will send the event not to its immediate
    // parent but to the "attached" list. A list may actually embed several components
    // in its path to the item, but key-presses etc. needs to go to the actual list.
    if( m_pOwner != NULL ) m_pOwner->Event(event); else CControlUI::Event(event);
}

void CListElementUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
    if( _tcscmp(pstrName, _T("selected")) == 0 ) Select(_tcscmp( pstrValue, _T( "true" ) ) == 0 );
    else CControlUI::SetAttribute(pstrName, pstrValue);
}
void CListElementUI::PaintBkColor( GRAPHorHDC& gorh )
{
	ASSERT(m_pOwner);
	//if( m_pOwner == NULL ) return;
	if ( !IsEnabled() ) m_uButtonState |= UISTATE_DISABLED;
	else m_uButtonState &= ~ UISTATE_DISABLED;
	if ( IsSelected() ) m_uButtonState |= UISTATE_SELECTED;
	else m_uButtonState &= ~ UISTATE_SELECTED;

	TListInfoUI* pInfo = m_pOwner->GetListInfo();
	DWORD iBackColor = pInfo->dwBkColor;
	if((m_uButtonState & UISTATE_DISABLED) != 0 ) {
		iBackColor = pInfo->dwDisabledBkColor;
	}
	else if( (m_uButtonState & UISTATE_SELECTED) != 0  ) {
		iBackColor = pInfo->dwSelectedBkColor;
	}
	else if( (m_uButtonState & UISTATE_HOT) != 0 ) {
		iBackColor = pInfo->dwHotBkColor;
	}

	if ( iBackColor != 0 ) {
		CRenderEngine::DrawColor(gorh, m_rcItem, iBackColor);
	}
	else
		CControlUI::PaintBkColor( gorh );
}
void CListElementUI::PaintBkImage( GRAPHorHDC& gorh )
{
	ASSERT(m_pOwner);
	//if( m_pOwner == NULL ) return;
	if ( !IsEnabled() ) m_uButtonState |= UISTATE_DISABLED;
	else m_uButtonState &= ~ UISTATE_DISABLED;
	if ( IsSelected() ) m_uButtonState |= UISTATE_SELECTED;
	else m_uButtonState &= ~ UISTATE_SELECTED;

	TListInfoUI* pInfo = m_pOwner->GetListInfo();

	bool bFlag=false;
	if( (m_uButtonState & UISTATE_DISABLED) != 0 ) {
		if( !pInfo->sDisabledImage.IsEmpty() ) {
			if( !DrawImage(gorh, (LPCTSTR)pInfo->sDisabledImage) ) pInfo->sDisabledImage.Empty();
			else bFlag=true;
			//else return;
		}
	}
	else if((m_uButtonState & UISTATE_SELECTED) != 0 ) {
		if( !pInfo->sSelectedImage.IsEmpty() ) {
			if( !DrawImage(gorh, (LPCTSTR)pInfo->sSelectedImage) ) pInfo->sSelectedImage.Empty();
			else bFlag=true;
			//else return;
		}
	}
	else if( (m_uButtonState & UISTATE_HOT) != 0 ) {
		if( !pInfo->sHotImage.IsEmpty() ) {
			if( !DrawImage(gorh, (LPCTSTR)pInfo->sHotImage) ) pInfo->sHotImage.Empty();
			else bFlag=true;
			//else return;
		}
	}

	if(!bFlag)
	{
		CControlUI::PaintBkImage(gorh);
	}
// 	if(!bFlag && !m_sBkImage.IsEmpty() ) {
// 		if( !DrawImage(gorh, (LPCTSTR)m_sBkImage) ) m_sBkImage.Empty();
// 	}
	if(!bFlag && m_sBkImage.IsEmpty() ) {
		if( !pInfo->sImage.IsEmpty() ) {
			if( !DrawImage(gorh, (LPCTSTR)pInfo->sImage) ) pInfo->sImage.Empty();
			//else return;
		}
	}

	if ( pInfo->dwLineColor != 0 ) {
		RECT rcLine = { m_rcItem.left, m_rcItem.bottom - 1, m_rcItem.right, m_rcItem.bottom - 1 };
		CRenderEngine::DrawLine(gorh, rcLine, 1, pInfo->dwLineColor);
	}
}

/////////////////////////////////////////////////////////////////////////////////////
//
//

CListLabelElementUI::CListLabelElementUI()
{
}

LPCTSTR CListLabelElementUI::GetClass() const
{
	return _T("ListLabelElementUI");
}

LPVOID CListLabelElementUI::GetInterface(LPCTSTR pstrName)
{
    if( _tcscmp(pstrName, _T("ListLabelElement")) == 0 ) return static_cast<CListLabelElementUI*>(this);
    return CListElementUI::GetInterface(pstrName);
}

void CListLabelElementUI::Event(TEventUI& event)
{
    if( !IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND ) {
        if( m_pOwner != NULL ) m_pOwner->Event(event);
        else CListElementUI::Event(event);
        return;
    }

    if( event.Type == UIEVENT_BUTTONDOWN )
    {
        if( IsEnabled() ) {
            m_pManager->SendNotify(this, _T("itemclick"));
            Select();
            Invalidate();
        }
        return;
    }
    if( event.Type == UIEVENT_MOUSEMOVE ) 
    {
        return;
    }
    if( event.Type == UIEVENT_BUTTONUP )
    {
        return;
    }
    if( event.Type == UIEVENT_MOUSEENTER )
    {
        if( IsEnabled() ) {
            m_uButtonState |= UISTATE_HOT;
            Invalidate();
        }
        return;
    }
    if( event.Type == UIEVENT_MOUSELEAVE )
    {
        if( (m_uButtonState & UISTATE_HOT) != 0 ) {
            m_uButtonState &= ~UISTATE_HOT;
            Invalidate();
        }
        return;
    }
    CListElementUI::Event(event);
}
//计算字的全部宽度
SIZE CListLabelElementUI::EstimateSize(SIZE szAvailable)
{
    if( m_pOwner == NULL ) return CSize(0, 0);

    TListInfoUI* pInfo = m_pOwner->GetListInfo();
    SIZE cXY = m_cxyFixed;
    if( cXY.cy == 0 && m_pManager != NULL ) {
        cXY.cy = m_pManager->GetDefaultFontInfo().tmHeight + 8;
        cXY.cy += pInfo->rcTextPadding.top + pInfo->rcTextPadding.bottom;
    }

    if( cXY.cx == 0 && m_pManager != NULL ) {
        RECT rcText = { 0, 0, 9999, cXY.cy };
        if( pInfo->bShowHtml ) {
            CRenderEngine::DrawHtmlText(m_pManager->GetPaintDC(), m_pManager, rcText, m_sText, 0, DT_SINGLELINE | DT_CALCRECT | pInfo->uTextStyle & ~DT_RIGHT & ~DT_CENTER);
        }
        else {
            CRenderEngine::DrawText(m_pManager->GetPaintDC(), m_pManager, rcText, m_sText, 0, pInfo->nFont, DT_SINGLELINE | DT_CALCRECT | pInfo->uTextStyle & ~DT_RIGHT & ~DT_CENTER);
        }
        cXY.cx = rcText.right - rcText.left + pInfo->rcTextPadding.left + pInfo->rcTextPadding.right;        
    }

    return cXY;
}

void CListLabelElementUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
    if( !::IntersectRect(&m_rcPaint, &rcPaint, &m_rcItem) ) return;
    DrawItemBk(hDC, m_rcItem);
    DrawItemText(hDC, m_rcItem);
}

void CListLabelElementUI::DrawItemText(HDC hDC, const RECT& rcItem)
{
    if( m_sText.IsEmpty() ) return;

    if( m_pOwner == NULL ) return;
    TListInfoUI* pInfo = m_pOwner->GetListInfo();
    DWORD iTextColor = pInfo->dwTextColor;
    if( (m_uButtonState & UISTATE_HOT) != 0 ) {
        iTextColor = pInfo->dwHotTextColor;
    }
    if( IsSelected() ) {
        iTextColor = pInfo->dwSelectedTextColor;
    }
    if( !IsEnabled() ) {
        iTextColor = pInfo->dwDisabledTextColor;
    }
    int nLinks = 0;
    RECT rcText = rcItem;
    rcText.left += pInfo->rcTextPadding.left;
    rcText.right -= pInfo->rcTextPadding.right;
    rcText.top += pInfo->rcTextPadding.top;
    rcText.bottom -= pInfo->rcTextPadding.bottom;

    if( pInfo->bShowHtml )
        CRenderEngine::DrawHtmlText(hDC, m_pManager, rcText, m_sText, iTextColor, \
        NULL, NULL, nLinks, DT_SINGLELINE | pInfo->uTextStyle);
    else
        CRenderEngine::DrawText(hDC, m_pManager, rcText, m_sText, iTextColor, \
        pInfo->nFont, DT_SINGLELINE | pInfo->uTextStyle);
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CListTextElementUI::CListTextElementUI() : m_nLinks(0), m_nHoverLink(-1), m_pOwner(NULL)
{
    ::ZeroMemory(&m_rcLinks, sizeof(m_rcLinks));
}

LPCTSTR CListTextElementUI::GetClass() const
{
    return _T("ListTextElementUI");
}

LPVOID CListTextElementUI::GetInterface(LPCTSTR pstrName)
{
    if( _tcscmp(pstrName, _T("ListTextElement")) == 0 ) return static_cast<CListTextElementUI*>(this);
    return CListLabelElementUI::GetInterface(pstrName);
}

UINT CListTextElementUI::GetControlFlags() const
{
    return UIFLAG_WANTRETURN | ( (IsEnabled() && m_nLinks > 0) ? UIFLAG_SETCURSOR : 0);
}

void CListTextElementUI::SetOwner(CControlUI* pOwner)
{
    CListElementUI::SetOwner(pOwner);
    m_pOwner = static_cast<IListUI*>(pOwner->GetInterface(_T("List")));
}

CStdString* CListTextElementUI::GetLinkContent(int iIndex)
{
    if( iIndex >= 0 && iIndex < m_nLinks ) return &m_sLinks[iIndex];
    return NULL;
}

void CListTextElementUI::Event(TEventUI& event)
{
    if( !IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND ) {
        if( m_pOwner != NULL ) m_pOwner->Event(event);
        else CListLabelElementUI::Event(event);
        return;
    }

    // When you hover over a link
    if( event.Type == UIEVENT_SETCURSOR ) {
        for( int i = 0; i < m_nLinks; i++ ) {
            if( ::PtInRect(&m_rcLinks[i], event.ptMouse) ) {
                ::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_HAND)));
                return;
            }
        }      
    }
    if( event.Type == UIEVENT_BUTTONUP && IsEnabled() ) {
        for( int i = 0; i < m_nLinks; i++ ) {
            if( ::PtInRect(&m_rcLinks[i], event.ptMouse) ) {
                m_pManager->SendNotify(this, _T("link"), i);
                return;
            }
        }
    }
    if( m_nLinks > 0 && event.Type == UIEVENT_MOUSEMOVE ) {
        int nHoverLink = -1;
        for( int i = 0; i < m_nLinks; i++ ) {
            if( ::PtInRect(&m_rcLinks[i], event.ptMouse) ) {
                nHoverLink = i;
                break;
            }
        }

        if(m_nHoverLink != nHoverLink) {
            Invalidate();
            m_nHoverLink = nHoverLink;
        }
    }
    if( m_nLinks > 0 && event.Type == UIEVENT_MOUSELEAVE ) {
        if(m_nHoverLink != -1) {
            Invalidate();
            m_nHoverLink = -1;
        }
    }
    CListLabelElementUI::Event(event);
}
//这里就没有计算字的全部宽度
SIZE CListTextElementUI::EstimateSize(SIZE szAvailable)
{
    TListInfoUI* pInfo = NULL;
    if( m_pOwner ) pInfo = m_pOwner->GetListInfo();

    SIZE cXY = m_cxyFixed;
    if( cXY.cy == 0 && m_pManager != NULL ) {
        cXY.cy = m_pManager->GetDefaultFontInfo().tmHeight + 8;
        if( pInfo ) cXY.cy += pInfo->rcTextPadding.top + pInfo->rcTextPadding.bottom;
    }

    return cXY;
}

void CListTextElementUI::DrawItemText(HDC hDC, const RECT& rcItem)
{
    if( m_pOwner == NULL ) return;
    TListInfoUI* pInfo = m_pOwner->GetListInfo();
    DWORD iTextColor = pInfo->dwTextColor;

    if( (m_uButtonState & UISTATE_HOT) != 0 ) {
        iTextColor = pInfo->dwHotTextColor;
    }
    if( IsSelected() ) {
        iTextColor = pInfo->dwSelectedTextColor;
    }
    if( !IsEnabled() ) {
        iTextColor = pInfo->dwDisabledTextColor;
    }
    IListCallbackUI* pCallback = m_pOwner->GetTextCallback();
    ASSERT(pCallback);
    if( pCallback == NULL ) return;
    m_nLinks = 0;
    int nLinks = lengthof(m_rcLinks);
    for( int i = 0; i < pInfo->nColumns; i++ )
    {
        RECT rcItem = { pInfo->rcColumn[i].left, m_rcItem.top, pInfo->rcColumn[i].right, m_rcItem.bottom };
        rcItem.left += pInfo->rcTextPadding.left;
        rcItem.right -= pInfo->rcTextPadding.right;
        rcItem.top += pInfo->rcTextPadding.top;
        rcItem.bottom -= pInfo->rcTextPadding.bottom;
        LPCTSTR pstrText = pCallback->GetItemText(this, m_iIndex, i);

        if( pInfo->bShowHtml )
            CRenderEngine::DrawHtmlText(hDC, m_pManager, rcItem, pstrText, iTextColor, \
            m_rcLinks, m_sLinks, nLinks, DT_SINGLELINE | pInfo->uTextStyle);
        else
            CRenderEngine::DrawText(hDC, m_pManager, rcItem, pstrText, iTextColor, \
            pInfo->nFont, DT_SINGLELINE | pInfo->uTextStyle);

        if( nLinks > 0 ) m_nLinks = nLinks, nLinks = 0; 
        else nLinks = lengthof(m_rcLinks);
    }
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CListExpandElementUI::CListExpandElementUI() : m_bExpanded(false), m_bHideSelf(false), m_pSubControl(NULL)
{
    ::ZeroMemory(&m_rcExpander, sizeof(m_rcExpander));
}

CListExpandElementUI::~CListExpandElementUI()
{
    if( m_pSubControl ) delete m_pSubControl;
}

LPCTSTR CListExpandElementUI::GetClass() const
{
    return _T("ListExpandElementUI");
}

LPVOID CListExpandElementUI::GetInterface(LPCTSTR pstrName)
{
    if( _tcscmp(pstrName, _T("ListExpandElement")) == 0 ) return static_cast<CListExpandElementUI*>(this);
    return CListLabelElementUI::GetInterface(pstrName);
}

bool CListExpandElementUI::IsExpanded() const
{
    return m_bExpanded;
}

bool CListExpandElementUI::Expand(bool bExpand)
{
    ASSERT(m_pOwner);
    if( m_pOwner == NULL ) return false;  
    if( bExpand == m_bExpanded ) return true;
    m_bExpanded = bExpand;
    if( !m_pOwner->ExpandItem(m_iIndex, bExpand) ) return false;
    // We need to manage the "expanding items", which are actually embedded controls
    // that we selectively display or not.
    if( bExpand ) 
    {
        if( m_pSubControl ) delete m_pSubControl;
        m_pSubControl = NULL;

        if( m_pManager != NULL ) m_pManager->SendNotify(this, _T("itemexpand"));
        if( m_pSubControl ) m_pManager->InitControls(m_pSubControl, this);
    }
    else
    {
        if( m_pManager != NULL ) m_pManager->SendNotify(this, _T("itemcollapse"));
    }
    return true;
}

bool CListExpandElementUI::GetExpandHideSelf() const
{
    return m_bHideSelf;
}

void CListExpandElementUI::SetExpandHideSelf(bool bHideSelf)
{
    m_bHideSelf = bHideSelf;
    NeedParentUpdate();
}

RECT CListExpandElementUI::GetExpanderRect() const
{
    return m_rcExpander;
}

void CListExpandElementUI::SetExpanderRect(RECT rc)
{
    m_rcExpander = rc;
}

void CListExpandElementUI::SetExpandItem(CControlUI* pControl)
{
    if (m_pSubControl ) delete m_pSubControl;
    m_pSubControl = pControl;
}

void CListExpandElementUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
    if( _tcscmp(pstrName, _T("expander")) == 0 ) {
        RECT rcExpander = { 0 };
        LPTSTR pstr = NULL;
        rcExpander.left = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);    
        rcExpander.top = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);    
        rcExpander.right = _tcstol(pstr + 1, &pstr, 10);  ASSERT(pstr);    
        rcExpander.bottom = _tcstol(pstr + 1, &pstr, 10); ASSERT(pstr);    
        SetExpanderRect(rcExpander);
    }
    else if( _tcscmp(pstrName, _T("hideself")) == 0 ) SetExpandHideSelf(_tcscmp(pstrValue, _T("true")) == 0);
    else CListTextElementUI::SetAttribute(pstrName, pstrValue);
}

void CListExpandElementUI::Event(TEventUI& event)
{
    if( !IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND ) {
        if( m_pOwner != NULL ) m_pOwner->Event(event);
        else CListTextElementUI::Event(event);
        return;
    }
    if( event.Type == UIEVENT_BUTTONDOWN )
    {
        if( IsEnabled() ) {
            m_pManager->SendNotify(this, _T("itemclick"));
            Select();
            Invalidate();
        }
        return;
    }
    if( event.Type == UIEVENT_MOUSEMOVE ) 
    {
        return;
    }
    if( event.Type == UIEVENT_BUTTONUP )
    {
        if( m_pOwner == NULL ) return;
        TListInfoUI* pInfo = m_pOwner->GetListInfo();
        RECT rcExpander = { m_rcItem.left + m_rcExpander.left, m_rcItem.top + m_rcExpander.top, 
            m_rcItem.left + m_rcExpander.right, m_rcItem.top + m_rcExpander.bottom };
        if( pInfo->bExpandable && ::PtInRect(&rcExpander, event.ptMouse) ) Expand(!m_bExpanded);
        return;
    }
    if( event.Type == UIEVENT_KEYDOWN )
    {
        switch( event.chKey ) {
      case VK_LEFT:
          Expand(false);
          return;
      case VK_RIGHT:
          Expand(true);
          return;
        }
    }
    if( event.Type == UIEVENT_MOUSEENTER )
    {
        if( (m_uButtonState & UISTATE_HOT) == 0  ) {
            m_uButtonState |= UISTATE_HOT;
            Invalidate();
        }
        return;
    }
    if( event.Type == UIEVENT_MOUSELEAVE )
    {
        if( (m_uButtonState & UISTATE_HOT) != 0 ) {
            m_uButtonState &= ~UISTATE_HOT;
            Invalidate();
        }
        return;
    }
    CListTextElementUI::Event(event);
}

SIZE CListExpandElementUI::EstimateSize(SIZE szAvailable)
{
    if( m_bExpanded && m_pSubControl != NULL ) {
        if( m_bHideSelf ) return m_pSubControl->EstimateSize(szAvailable);
        
        SIZE sz = m_pSubControl->EstimateSize(szAvailable);
        if( sz.cy < m_pSubControl->GetMinHeight() ) sz.cy = m_pSubControl->GetMinHeight();
        if( sz.cy > m_pSubControl->GetMaxHeight() ) sz.cy = m_pSubControl->GetMaxHeight();

        if( m_cxyFixed.cy == 0 ) sz.cy += CListTextElementUI::EstimateSize(szAvailable).cy;
        else sz.cy += m_cxyFixed.cy;
        return CSize(m_cxyFixed.cx, sz.cy);
    }
    else
    {
        return CListTextElementUI::EstimateSize(szAvailable);
    }   
}

void CListExpandElementUI::SetVisible(bool bVisible)
{
    if( m_bVisible == bVisible ) return;
    CControlUI::SetVisible(bVisible);

    if( m_bExpanded && m_pSubControl != NULL ) {
        m_pSubControl->SetInternVisible(bVisible);
    }
}

void CListExpandElementUI::SetInternVisible(bool bVisible)
{
    if( m_bExpanded && m_pSubControl != NULL ) {
        m_pSubControl->SetInternVisible(bVisible);
    }
    CControlUI::SetInternVisible(bVisible);
}

void CListExpandElementUI::SetMouseEnabled(bool bEnabled)
{
    m_bMouseEnabled = bEnabled;

    if( m_bExpanded && m_pSubControl != NULL ) {
        m_pSubControl->SetMouseEnabled(bEnabled);
    }
}

void CListExpandElementUI::SetPos(RECT rc)
{
    CListTextElementUI::SetPos(rc);
    if( m_pSubControl != NULL ) {
        if( m_bHideSelf ) {
            RECT rcPadding = m_pSubControl->GetPadding();
            RECT rcSubItem = { rc.left + rcPadding.left, rc.top + rcPadding.top, 
                rc.right - rcPadding.right, rc.bottom - rcPadding.bottom };
            m_pSubControl->SetPos(rcSubItem);
        }
        else {
            SIZE sz = m_pSubControl->EstimateSize(CSize(rc.right - rc.left, rc.bottom - rc.top));
            if( sz.cy < m_pSubControl->GetMinHeight() ) sz.cy = m_pSubControl->GetMinHeight();
            if( sz.cy > m_pSubControl->GetMaxHeight() ) sz.cy = m_pSubControl->GetMaxHeight();
            RECT rcPadding = m_pSubControl->GetPadding();

            if( sz.cy == 0 && m_cxyFixed.cy == 0 ) {
                RECT rcSubItem = { rc.left + rcPadding.left, (rc.bottom + rc.top) / 2 + rcPadding.top, 
                    rc.right - rcPadding.right, rc.bottom - rcPadding.bottom };
                m_pSubControl->SetPos(rcSubItem);
            }
            else if( sz.cy != 0 && m_cxyFixed.cy == 0 ) {
                RECT rcSubItem = { rc.left + rcPadding.left, rc.bottom - sz.cy - rcPadding.bottom, 
                    rc.right - rcPadding.right, rc.bottom - rcPadding.bottom };
                m_pSubControl->SetPos(rcSubItem);
            }
            else {
                RECT rcSubItem = { rc.left + rcPadding.left, rc.top + m_cxyFixed.cy + rcPadding.top, 
                    rc.right - rcPadding.right, rc.bottom - rcPadding.bottom };
                m_pSubControl->SetPos(rcSubItem);
            }
        }
    }
}

void CListExpandElementUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
    CListTextElementUI::DoPaint(hDC, rcPaint);

    if( m_bExpanded && m_pSubControl != NULL ) {
        m_pSubControl->DoPaint(hDC, rcPaint);
    }
}

void CListExpandElementUI::SetManager(CPaintManagerUI* pManager, CControlUI* pParent, bool bInit)
{
    if( m_bExpanded && m_pSubControl != NULL ) m_pSubControl->SetManager(pManager, this, bInit);
    CListTextElementUI::SetManager(pManager, pParent, bInit);
}

CControlUI* CListExpandElementUI::FindControl(FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags)
{
    CControlUI* pResult = NULL;
    if( m_bExpanded && m_pSubControl != NULL ) pResult = m_pSubControl->FindControl(Proc, pData, uFlags);
    if( pResult == NULL ) pResult = CListTextElementUI::FindControl(Proc, pData, uFlags);
    return pResult;
}

void CListExpandElementUI::DrawItemText(HDC hDC, const RECT& rcItem)
{
    DrawItemBk(hDC, rcItem);
    if( m_bExpanded && m_pSubControl != NULL && m_bHideSelf ) return;

    if( m_pOwner == NULL ) return;
    TListInfoUI* pInfo = m_pOwner->GetListInfo();
    DWORD iTextColor = pInfo->dwTextColor;
    if( (m_uButtonState & UISTATE_HOT) != 0 ) {
        iTextColor = pInfo->dwHotTextColor;
    }
    if( IsSelected() ) {
        iTextColor = pInfo->dwSelectedTextColor;
    }
    if( !IsEnabled() ) {
        iTextColor = pInfo->dwDisabledTextColor;
    }

    IListCallbackUI* pCallback = m_pOwner->GetTextCallback();
    ASSERT(pCallback);
    if( pCallback == NULL ) return;
    m_nLinks = 0;
    CStdString sColText;
    int nLinks = lengthof(m_rcLinks);
    for( int i = 0; i < pInfo->nColumns; i++ )
    {
        // Paint text
        RECT rcItem = { pInfo->rcColumn[i].left, m_rcItem.top, pInfo->rcColumn[i].right, m_rcItem.bottom };
        if( m_bExpanded && m_pSubControl != NULL ) rcItem.bottom -= m_pSubControl->GetHeight();
        rcItem.left += pInfo->rcTextPadding.left;
        rcItem.right -= pInfo->rcTextPadding.right;
        rcItem.top += pInfo->rcTextPadding.top;
        rcItem.bottom -= pInfo->rcTextPadding.bottom;

        LPCTSTR pstrText = pCallback->GetItemText(this, m_iIndex, i);
        if( pInfo->bShowHtml )
            CRenderEngine::DrawHtmlText(hDC, m_pManager, rcItem, pstrText, iTextColor, \
            m_rcLinks, m_sLinks, nLinks, DT_SINGLELINE | pInfo->uTextStyle);
        else
            CRenderEngine::DrawText(hDC, m_pManager, rcItem, pstrText, iTextColor, \
            pInfo->nFont, DT_SINGLELINE | pInfo->uTextStyle);

        if( nLinks > 0 ) m_nLinks = nLinks, nLinks = 0; 
        else nLinks = lengthof(m_rcLinks);
    }
}


/////////////////////////////////////////////////////////////////////////////////////
//
//

CListContainerElementUI::CListContainerElementUI() : 
m_iIndex(-1),
m_pOwner(NULL), 
m_bSelected(false),
m_uButtonState(0)
{
}

LPCTSTR CListContainerElementUI::GetClass() const
{
    return _T("ListContainerElement");
}

UINT CListContainerElementUI::GetControlFlags() const
{
    return UIFLAG_WANTRETURN;
}

LPVOID CListContainerElementUI::GetInterface(LPCTSTR pstrName)
{
    if( _tcscmp(pstrName, _T("ListItem")) == 0 ) return static_cast<IListItemUI*>(this);
    return CContainerUI::GetInterface(pstrName);
}

IListOwnerUI* CListContainerElementUI::GetOwner()
{
    return m_pOwner;
}

void CListContainerElementUI::SetOwner(CControlUI* pOwner)
{
    m_pOwner = static_cast<IListOwnerUI*>(pOwner->GetInterface(_T("ListOwner")));
}

void CListContainerElementUI::SetVisible(bool bVisible)
{
    CContainerUI::SetVisible(bVisible);
    if( !IsVisible() && m_bSelected)
    {
        m_bSelected = false;
        if( m_pOwner != NULL ) m_pOwner->SelectItem(-1);
    }
}

void CListContainerElementUI::SetEnabled(bool bEnable)
{
    CControlUI::SetEnabled(bEnable);
    if( !IsEnabled() ) {
        m_uButtonState = 0;
    }
}

int CListContainerElementUI::GetIndex() const
{
    return m_iIndex;
}

void CListContainerElementUI::SetIndex(int iIndex)
{
    m_iIndex = iIndex;
}

void CListContainerElementUI::Invalidate()
{
    if( !IsVisible() ) return;

    if( GetParent() ) {
        CContainerUI* pParentContainer = static_cast<CContainerUI*>(GetParent()->GetInterface(_T("Container")));
        if( pParentContainer ) {
            RECT rc = pParentContainer->GetPos();
            RECT rcInset = pParentContainer->GetInset();
            rc.left += rcInset.left;
            rc.top += rcInset.top;
            rc.right -= rcInset.right;
            rc.bottom -= rcInset.bottom;
            CScrollbarUI* pVerticalScrollbar = pParentContainer->GetVerticalScrollbar();
            if( pVerticalScrollbar && pVerticalScrollbar->IsVisible() ) rc.right -= pVerticalScrollbar->GetFixedWidth();
            CScrollbarUI* pHorizontalScrollbar = pParentContainer->GetHorizontalScrollbar();
            if( pHorizontalScrollbar && pHorizontalScrollbar->IsVisible() ) rc.bottom -= pHorizontalScrollbar->GetFixedHeight();

            RECT invalidateRc = m_rcItem;
            if( !::IntersectRect(&invalidateRc, &m_rcItem, &rc) ) 
            {
                return;
            }

            CControlUI* pParent = GetParent();
            RECT rcTemp;
            RECT rcParent;
            while( pParent = pParent->GetParent() )
            {
                rcTemp = invalidateRc;
                rcParent = pParent->GetPos();
                if( !::IntersectRect(&invalidateRc, &rcTemp, &rcParent) ) 
                {
                    return;
                }
            }

            if( m_pManager != NULL ) m_pManager->Invalidate(invalidateRc);
        }
        else {
            CContainerUI::Invalidate();
        }
    }
    else {
        CContainerUI::Invalidate();
    }
}

bool CListContainerElementUI::Activate()
{
    if( !CContainerUI::Activate() ) return false;
    if( m_pManager != NULL ) m_pManager->SendNotify(this, _T("itemactivate"));
    return true;
}

bool CListContainerElementUI::IsSelected() const
{
    return m_bSelected;
}

bool CListContainerElementUI::Select(bool bSelect)
{
    if( !IsEnabled() ) return false;
    if( bSelect == m_bSelected ) return true;
    m_bSelected = bSelect;
    if( bSelect && m_pOwner != NULL ) m_pOwner->SelectItem(m_iIndex);
    SetMouseChildEnabled(bSelect);
    Invalidate();

    return true;
}

bool CListContainerElementUI::IsExpanded() const
{
    return false;
}

bool CListContainerElementUI::Expand(bool /*bExpand = true*/)
{
    return false;
}

void CListContainerElementUI::Event(TEventUI& event)
{
    if( !IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND ) {
        if( m_pOwner != NULL ) m_pOwner->Event(event);
        else CContainerUI::Event(event);
        return;
    }

    if( event.Type == UIEVENT_DBLCLICK )
    {
        if( IsEnabled() ) {
            Activate();
            Invalidate();
        }
        return;
    }
    if( event.Type == UIEVENT_KEYDOWN && IsEnabled() )
    {
        if( event.chKey == VK_RETURN ) {
            Activate();
            Invalidate();
            return;
        }
    }
    if( event.Type == UIEVENT_BUTTONDOWN )
    {
        if( IsEnabled() ){
            m_pManager->SendNotify(this, _T("itemclick"));
            Select();
            Invalidate();
        }
        return;
    }
    if( event.Type == UIEVENT_BUTTONUP ) 
    {
        return;
    }
    if( event.Type == UIEVENT_MOUSEMOVE )
    {
        return;
    }
    if( event.Type == UIEVENT_MOUSEENTER )
    {
        if( IsEnabled() ) {
            m_uButtonState |= UISTATE_HOT;
            Invalidate();
        }
        return;
    }
    if( event.Type == UIEVENT_MOUSELEAVE )
    {
        if( (m_uButtonState & UISTATE_HOT) != 0 ) {
            m_uButtonState &= ~UISTATE_HOT;
            Invalidate();
        }
        return;
    }

    // An important twist: The list-item will send the event not to its immediate
    // parent but to the "attached" list. A list may actually embed several components
    // in its path to the item, but key-presses etc. needs to go to the actual list.
    if( m_pOwner != NULL ) m_pOwner->Event(event); else CControlUI::Event(event);
}

void CListContainerElementUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
    if( _tcscmp(pstrName, _T("selected")) == 0 ) Select();
    else CContainerUI::SetAttribute(pstrName, pstrValue);
}

void CListContainerElementUI::DoPaint(HDC hDC, const RECT& rcPaint)
{
    if( !::IntersectRect(&m_rcPaint, &rcPaint, &m_rcItem) ) return;
    DrawItemBk(hDC, m_rcItem);
    CContainerUI::DoPaint(hDC, rcPaint);
}

void CListContainerElementUI::DrawItemText(HDC hDC, const RECT& rcItem)
{
    return;
}

void CListContainerElementUI::DrawItemBk(HDC hDC, const RECT& rcItem)
{
    ASSERT(m_pOwner);
    if( m_pOwner == NULL ) return;
    TListInfoUI* pInfo = m_pOwner->GetListInfo();
    DWORD iBackColor = pInfo->dwBkColor;

    if( (m_uButtonState & UISTATE_HOT) != 0 ) {
        iBackColor = pInfo->dwHotBkColor;
    }
    if( IsSelected() ) {
        iBackColor = pInfo->dwSelectedBkColor;
    }
    if( !IsEnabled() ) {
        iBackColor = pInfo->dwDisabledBkColor;
    }
    if ( iBackColor != 0 ) {
        CRenderEngine::DrawColor(hDC, m_rcItem, iBackColor);
    }

    if( !IsEnabled() ) {
        if( !pInfo->sDisabledImage.IsEmpty() ) {
            if( !DrawImage(hDC, (LPCTSTR)pInfo->sDisabledImage) ) pInfo->sDisabledImage.Empty();
            else return;
        }
    }
    if( IsSelected() ) {
        if( !pInfo->sSelectedImage.IsEmpty() ) {
            if( !DrawImage(hDC, (LPCTSTR)pInfo->sSelectedImage) ) pInfo->sSelectedImage.Empty();
            else return;
        }
    }
    if( (m_uButtonState & UISTATE_HOT) != 0 ) {
        if( !pInfo->sHotImage.IsEmpty() ) {
            if( !DrawImage(hDC, (LPCTSTR)pInfo->sHotImage) ) pInfo->sHotImage.Empty();
            else return;
        }
    }
    if( !m_sBkImage.IsEmpty() ) {
        if( !DrawImage(hDC, (LPCTSTR)m_sBkImage) ) m_sBkImage.Empty();
    }

    if( m_sBkImage.IsEmpty() ) {
        if( !pInfo->sImage.IsEmpty() ) {
            if( !DrawImage(hDC, (LPCTSTR)pInfo->sImage) ) pInfo->sImage.Empty();
            else return;
        }
    }

    if ( pInfo->dwLineColor != 0 ) {
        RECT rcLine = { m_rcItem.left, m_rcItem.bottom - 1, m_rcItem.right, m_rcItem.bottom - 1 };
        CRenderEngine::DrawLine(hDC, rcLine, 1, pInfo->dwLineColor);
    }
}
