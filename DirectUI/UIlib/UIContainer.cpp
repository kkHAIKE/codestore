#include "StdAfx.h"
#include "UIContainer.h"

//计划Wrap排版

/////////////////////////////////////////////////////////////////////////////////////
//
//
IMPLEMENT_DYNCREATE( CScrollViewerUI )
CScrollViewerUI::CScrollViewerUI():
    m_pVerticalScrollbar( NULL ),
    m_pHorizontalScrollbar( NULL ),
    m_iVerticalScrollbarStyle( UISCROLL_NONE ),
    m_iHorizontalScrollbarStyle( UISCROLL_NONE )
{
}

CScrollViewerUI::~CScrollViewerUI()
{
    if ( m_pVerticalScrollbar ) delete m_pVerticalScrollbar;
    if ( m_pHorizontalScrollbar ) delete m_pHorizontalScrollbar;
}
LPCTSTR CScrollViewerUI::GetClass() const
{
    return _T( "ScrollViewerUI" );
}

LPVOID CScrollViewerUI::GetInterface( LPCTSTR pstrName )
{
    if ( _tcscmp( pstrName, _T( "ScrollViewer" ) ) == 0 ) return static_cast<CScrollViewerUI*>( this );
    return CContentControlUI::GetInterface( pstrName );
}
void CScrollViewerUI::Event( TEventUI& event )
{
    if ( !IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND ) {
        if ( m_pParent != NULL ) m_pParent->Event( event );
        else CContentControlUI::Event( event );
        return;
    }

    if ( m_pVerticalScrollbar != NULL && m_pVerticalScrollbar->IsEnabled() ) {
        if ( event.Type == UIEVENT_KEYDOWN ) {
            switch ( event.chKey ) {
            case VK_DOWN:
                LineDown();
                return;
            case VK_UP:
                LineUp();
                return;
            case VK_NEXT:
                PageDown();
                return;
            case VK_PRIOR:
                PageUp();
                return;
            case VK_HOME:
                HomeUp();
                return;
            case VK_END:
                EndDown();
                return;
            }
        }
        else if ( event.Type == UIEVENT_SCROLLWHEEL ) {
            switch ( LOWORD( event.wParam ) ) {
            case SB_LINEUP:
                LineUp();
                return;
            case SB_LINEDOWN:
                LineDown();
                return;
            }
        }
    }
    else if ( m_pHorizontalScrollbar != NULL && m_pHorizontalScrollbar->IsEnabled() ) {
        if ( event.Type == UIEVENT_KEYDOWN ) {
            switch ( event.chKey ) {
            case VK_DOWN:
                LineRight();
                return;
            case VK_UP:
                LineLeft();
                return;
            case VK_NEXT:
                PageRight();
                return;
            case VK_PRIOR:
                PageLeft();
                return;
            case VK_HOME:
                HomeLeft();
                return;
            case VK_END:
                EndRight();
                return;
            }
        }
        else if ( event.Type == UIEVENT_SCROLLWHEEL ) {
            switch ( LOWORD( event.wParam ) ) {
            case SB_LINEUP:
                LineLeft();
                return;
            case SB_LINEDOWN:
                LineRight();
                return;
            }
        }
    }
    CContentControlUI::Event( event );
}
void CScrollViewerUI::SetVisible( bool bVisible )
{
    if ( m_bVisible == bVisible )return;

    if ( m_pVerticalScrollbar )
        m_pVerticalScrollbar->SetInternVisible( bVisible );
    if ( m_pHorizontalScrollbar )
        m_pHorizontalScrollbar->SetInternVisible( bVisible );

    CContentControlUI::SetVisible( bVisible );

}
void CScrollViewerUI::SetInternVisible( bool bVisible )
{
    if ( m_bInternVisible == bVisible )return;

    if ( m_pVerticalScrollbar )
        m_pVerticalScrollbar->SetInternVisible( bVisible );
    if ( m_pHorizontalScrollbar )
        m_pHorizontalScrollbar->SetInternVisible( bVisible );

    CContentControlUI::SetInternVisible( bVisible );
}
void CScrollViewerUI::SetEnabled( bool bEnabled )
{
    if ( m_bEnabled == bEnabled )return;

    if ( m_pVerticalScrollbar )
        m_pVerticalScrollbar->SetInternEnabled( bEnabled );
    if ( m_pHorizontalScrollbar )
        m_pHorizontalScrollbar->SetInternEnabled( bEnabled );

    CContentControlUI::SetEnabled( bEnabled );
}
void CScrollViewerUI::SetInternEnabled( bool bEnabled )
{
    if ( m_bInternEnabled == bEnabled )return;

    if ( m_pVerticalScrollbar )
        m_pVerticalScrollbar->SetInternEnabled( bEnabled );
    if ( m_pHorizontalScrollbar )
        m_pHorizontalScrollbar->SetInternEnabled( bEnabled );

    CContentControlUI::SetInternEnabled( bEnabled );
}
void CScrollViewerUI::SetMouseEnabled( bool bEnabled )
{
    if ( m_bMouseEnabled == bEnabled )return;

    if ( m_pVerticalScrollbar )
        m_pVerticalScrollbar->SetInternMouseEnabled( bEnabled );
    if ( m_pHorizontalScrollbar )
        m_pHorizontalScrollbar->SetInternMouseEnabled( bEnabled );

    CContentControlUI::SetMouseEnabled( bEnabled );
}
void CScrollViewerUI::SetInternMouseEnabled( bool bEnabled )
{
    if ( m_bInternMouseEnabled == bEnabled )return;

    if ( m_pVerticalScrollbar )
        m_pVerticalScrollbar->SetInternMouseEnabled( bEnabled );
    if ( m_pHorizontalScrollbar )
        m_pHorizontalScrollbar->SetInternMouseEnabled( bEnabled );

    CContentControlUI::SetInternMouseEnabled( bEnabled );
}

SIZE CScrollViewerUI::EstimateSizeOver( const SIZE& szAvailable )
{
    SIZE szSize = {0};
    if ( m_pContent && m_pContent->IsVisible() ) {
        //在这里应该要测出是否滚动条然后返回完美长度
        //内容应该保留正确测量值
        RECT rcPadding = m_pContent->GetPadding();
        SIZE szRemindAvailable = szAvailable;
        szRemindAvailable.cx -= rcPadding.left + rcPadding.right;
        szRemindAvailable.cy -= rcPadding.top + rcPadding.bottom;
        szRemindAvailable.cx = MAX( szRemindAvailable.cx, 0 );
        szRemindAvailable.cy = MAX( szRemindAvailable.cy, 0 );

        m_pContent->EstimateSize( szRemindAvailable );
        szSize = m_pContent->GetDesiredSize();
        SIZE szRemindSize = szSize;
        szSize.cx += rcPadding.left + rcPadding.right;
        szSize.cy += rcPadding.top + rcPadding.bottom;

        ProcessScrollbar( szRemindAvailable, szRemindSize );

        bool bflagSetV = false, bflagSetH = false;
        if ( m_pVerticalScrollbar && m_pVerticalScrollbar->IsVisible() )
            {szRemindAvailable.cx -= m_pVerticalScrollbar->GetFixedWidth(); bflagSetV = true;}
        if ( m_pHorizontalScrollbar && m_pHorizontalScrollbar->IsVisible() )
            {szRemindAvailable.cy -= m_pHorizontalScrollbar->GetFixedHeight(); bflagSetH = true;}
        szRemindAvailable.cx = MAX( szRemindAvailable.cx, 0 );
        szRemindAvailable.cy = MAX( szRemindAvailable.cy, 0 );

        if ( bflagSetV || bflagSetH ) {
            m_pContent->EstimateSize( szRemindAvailable );
            szRemindSize = m_pContent->GetDesiredSize();
            ProcessScrollbar( szRemindAvailable, szRemindSize );

            if ( !bflagSetV && m_pVerticalScrollbar && m_pVerticalScrollbar->IsVisible() )
                {szRemindAvailable.cx -= m_pVerticalScrollbar->GetFixedWidth(); bflagSetV = true;}
            else
                bflagSetV = false;
            if ( !bflagSetH && m_pHorizontalScrollbar && m_pHorizontalScrollbar->IsVisible() )
                {szRemindAvailable.cy -= m_pHorizontalScrollbar->GetFixedHeight(); bflagSetH = true;}
            else
                bflagSetH = false;
            szRemindAvailable.cx = MAX( szRemindAvailable.cx, 0 );
            szRemindAvailable.cy = MAX( szRemindAvailable.cy, 0 );

            if ( bflagSetV || bflagSetH ) {
                m_pContent->EstimateSize( szRemindAvailable );
                szRemindSize = m_pContent->GetDesiredSize();
                ProcessScrollbar( szRemindAvailable, szRemindSize );
            }
        }
    }
    else
        ProcessScrollbar( szAvailable, CSize() );
    return CSize( szSize.cx + ( ( m_pVerticalScrollbar && m_iVerticalScrollbarStyle == UISCROLL_SHOW ) ? m_pVerticalScrollbar->GetFixedWidth() : 0 )\
                  , szSize.cy + ( ( m_pHorizontalScrollbar && m_iHorizontalScrollbarStyle == UISCROLL_SHOW ) ? m_pHorizontalScrollbar->GetFixedHeight() : 0 ) );
}
void CScrollViewerUI::SetPosMain( const RECT& rc )
{
    RECT rcPos = {rc.left + m_rcInset.left, rc.top + m_rcInset.top, rc.right - m_rcInset.right - \
                  ( ( m_pVerticalScrollbar && m_pVerticalScrollbar->IsVisible() ) ? m_pVerticalScrollbar->GetFixedWidth() : 0 ), \
                  rc.bottom - m_rcInset.bottom - ( ( m_pHorizontalScrollbar && m_pHorizontalScrollbar->IsVisible() ) ? m_pHorizontalScrollbar->GetFixedHeight() : 0 )
                 };
    rcPos.right = MAX( rcPos.left, rcPos.right );
    rcPos.bottom = MAX( rcPos.top, rcPos.bottom );
    rcPos = SetPosOver( rcPos );
    if ( m_pVerticalScrollbar && m_pVerticalScrollbar->IsVisible() ) {
        RECT rcScrollbarPos = { rcPos.right + m_rcInset.right, rc.top, rc.right, rc.bottom };
        m_pVerticalScrollbar->SetPos( rcScrollbarPos );
        rcPos.right += m_pVerticalScrollbar->GetFixedWidth();
    }
    if ( m_pHorizontalScrollbar && m_pHorizontalScrollbar->IsVisible() ) {
        RECT rcScrollbarPos = { rc.left, rcPos.bottom + m_rcInset.bottom, rc.right , rc.bottom };
        m_pHorizontalScrollbar->SetPos( rcScrollbarPos );
        rcPos.bottom += m_pHorizontalScrollbar->GetFixedHeight();
    }
    ::SetRect( &m_rcItem, rcPos.left - m_rcInset.left, rcPos.top - m_rcInset.top, rcPos.right + m_rcInset.right, rcPos.bottom + m_rcInset.bottom );
}
RECT CScrollViewerUI::SetPosOver( const RECT& rc )
{
    if ( m_pContent && m_pContent->IsVisible() ) {
        //忽略内部对齐属性
        //当某滚动条禁用时采用内容那方向的对齐
        //拉伸原则：滚动条禁用时拉升至POS，启用时拉伸至测量值
        RECT rcPadding = m_pContent->GetPadding();
        RECT rcRemind = rc;
        rcRemind.left += rcPadding.left; rcRemind.right -= rcPadding.right;
        rcRemind.top += rcPadding.top; rcRemind.bottom -= rcPadding.bottom;
        rcRemind.right = MAX( rcRemind.left, rcRemind.right );
        rcRemind.bottom = MAX( rcRemind.top, rcRemind.bottom );

        int hAligenment = m_pContent->GetHorizontalAlignment();
        int vAligenment = m_pContent->GetVerticalAlignment();

        int cx = m_pContent->GetFixedWidth();
        int cy = m_pContent->GetFixedHeight();
        SIZE sz = m_pContent->GetDesiredSize();

        int retX = 0;
        int posX = 0;
        if ( m_pHorizontalScrollbar && m_pHorizontalScrollbar->IsEnabled() ) {
            //启用了横向
            posX = rcRemind.left - m_pHorizontalScrollbar->GetScrollPos();
            //肯定不是0，因为激活了横向
            retX = sz.cx;
        }
        else {
            //禁用了横向
            if ( hAligenment == UIALIGNMENT_STRETCH ) {
                retX = cx ? cx : ( rcRemind.right - rcRemind.left );
            }
            else {
                retX = sz.cx ? sz.cx : ( rcRemind.right - rcRemind.left );
            }
            retX = CLAMP( retX, m_pContent->GetMinWidth(), m_pContent->GetMaxWidth() );

            if ( hAligenment == UIALIGNMENT_LEFT_TOP )
                posX = rcRemind.left;
            else if ( hAligenment == UIALIGNMENT_RIGHT_BOTTOM )
                posX = rcRemind.right - retX;
            else
                posX = ( rcRemind.left + rcRemind.right - retX ) / 2;
        }

        int retY = 0;
        int posY = 0;
        if ( m_pVerticalScrollbar && m_pVerticalScrollbar->IsEnabled() ) {
            posY = rcRemind.top - m_pVerticalScrollbar->GetScrollPos();
            retY = sz.cy;
        }
        else {
            if ( vAligenment == UIALIGNMENT_STRETCH ) {
                retY = cy ? cy : ( rcRemind.bottom - rcRemind.top );
            }
            else {
                retY = sz.cy ? sz.cy : ( rcRemind.bottom - rcRemind.top );
            }
            retY = CLAMP( retY, m_pContent->GetMinHeight(), m_pContent->GetMaxWidth() );

            if ( vAligenment == UIALIGNMENT_LEFT_TOP )
                posY = rcRemind.top;
            else if ( vAligenment == UIALIGNMENT_RIGHT_BOTTOM )
                posY = rcRemind.bottom - rcRemind.top;
            else
                posY = ( rcRemind.bottom + rcRemind.top - retY ) / 2;
        }
        m_pContent->SetPos( CRect( posX, posY, posX + retX, posY + retY ) );
        ProcessScrollbar( CSize( rcRemind.right - rcRemind.left, rcRemind.bottom - rcRemind.top ), CSize( retX, retY ) );
        //RECT posRemind=m_pContent->GetPos();

        //ProcessScrollbar(CSize(rcRemind.right-rcRemind.left,rcRemind.bottom-rcRemind.top),\
        //	CSize(posRemind.right-posRemind.left,posRemind.bottom-posRemind.top));
    }
    return rc;
}
void CScrollViewerUI::PaintContent( GRAPHorHDC& gorh )
{
    if ( m_pVerticalScrollbar && m_pVerticalScrollbar->IsVisible() )
        m_pVerticalScrollbar->DoPaint( gorh, m_rcPaint );
    if ( m_pHorizontalScrollbar && m_pHorizontalScrollbar->IsVisible() )
        m_pHorizontalScrollbar->DoPaint( gorh, m_rcPaint );

    if ( m_pContent && m_pContent->IsVisible() ) {
        RECT rcPadding = m_pContent->GetPadding();
        RECT rcClip = {m_rcItem.left + m_rcInset.left + rcPadding.left, \
                       m_rcItem.top + m_rcInset.top + rcPadding.top, \
                       m_rcItem.right - m_rcInset.right - rcPadding.right - ( ( m_pVerticalScrollbar && m_pVerticalScrollbar->IsVisible() ) ? m_pVerticalScrollbar->GetFixedWidth() : 0 ), \
                       m_rcItem.bottom - m_rcInset.bottom - rcPadding.bottom - ( ( m_pHorizontalScrollbar && m_pHorizontalScrollbar->IsVisible() ) ? m_pHorizontalScrollbar->GetFixedHeight() : 0 )
                      };
        if ( ::IsRectEmpty( &rcClip ) )
            return;
        CRgn oldRegion = gorh.IntersectClip( rcClip );

        m_pContent->DoPaint( gorh, m_rcPaint );

        gorh.SetClip( oldRegion );
    }
}
void CScrollViewerUI::SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue )
{
    if ( _tcscmp( pstrName, _T( "vscrollbar" ) ) == 0 ) {
        int vstyle = UISCROLL_NONE;
        if ( _tcscmp( pstrValue, _T( "true" ) ) == 0 || _tcscmp( pstrValue, _T( "auto" ) ) == 0 )
            vstyle = UISCROLL_AUTO;
        else if ( _tcscmp( pstrValue, _T( "show" ) ) == 0 )
            vstyle = UISCROLL_SHOW;
        else if ( _tcscmp( pstrValue, _T( "hide" ) ) == 0 )
            vstyle = UISCROLL_HIDE;
        EnableScrollBar( vstyle, m_iHorizontalScrollbarStyle );
    }
    else if ( _tcscmp( pstrName, _T( "hscrollbar" ) ) == 0 ) {
        int vstyle = UISCROLL_NONE;
        if ( _tcscmp( pstrValue, _T( "true" ) ) == 0 || _tcscmp( pstrValue, _T( "auto" ) ) == 0 )
            vstyle = UISCROLL_AUTO;
        else if ( _tcscmp( pstrValue, _T( "show" ) ) == 0 )
            vstyle = UISCROLL_SHOW;
        else if ( _tcscmp( pstrValue, _T( "hide" ) ) == 0 )
            vstyle = UISCROLL_HIDE;
        EnableScrollBar( m_iVerticalScrollbarStyle, vstyle );
    }
    else CContentControlUI::SetAttribute( pstrName, pstrValue );
}
void CScrollViewerUI::SetManager( CPaintManagerUI* pManager, CElementUI* pParent, bool bInit )
{
    if ( m_pVerticalScrollbar != NULL ) m_pVerticalScrollbar->SetManager( pManager, this, bInit );
    if ( m_pHorizontalScrollbar != NULL ) m_pHorizontalScrollbar->SetManager( pManager, this, bInit );
    CContentControlUI::SetManager( pManager, pParent, bInit );
}
CElementUI* CScrollViewerUI::FindControl( FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags )
{
    if ( ( uFlags & UIFIND_VISIBLE ) != 0 && !IsVisible() ) return NULL;
    if ( ( uFlags & UIFIND_ENABLED ) != 0 && !IsEnabled() ) return NULL;
    if ( ( uFlags & UIFIND_HITTEST ) != 0 && ( !m_bMouseEnabled || !::PtInRect( &m_rcItem, * reinterpret_cast<LPPOINT>( pData ) ) ) ) return NULL;
    if ( ( uFlags & UIFIND_CAN_FOCUS ) != 0 && !IsCanFocus() ) return NULL;

    CElementUI* pThisResult = CElementUI::FindControl( Proc, pData, uFlags );

    if ( ( uFlags & UIFIND_ME_FIRST ) != 0 && pThisResult )return pThisResult;

    CElementUI* pContentResult = NULL;
    if ( m_pVerticalScrollbar ) pContentResult = m_pVerticalScrollbar->FindControl( Proc, pData, uFlags );
    if ( pContentResult == NULL && m_pHorizontalScrollbar ) pContentResult = m_pHorizontalScrollbar->FindControl( Proc, pData, uFlags );
    if ( pContentResult == NULL && m_pContent )pContentResult = m_pContent->FindControl( Proc, pData, uFlags );
    if ( pContentResult )
        return pContentResult;

    return pThisResult;
}
SIZE CScrollViewerUI::GetScrollPos() const
{
    SIZE sz = {0, 0};
    if ( m_pVerticalScrollbar ) sz.cy = m_pVerticalScrollbar->GetScrollPos();
    if ( m_pHorizontalScrollbar ) sz.cx = m_pHorizontalScrollbar->GetScrollPos();
    return sz;
}

SIZE CScrollViewerUI::GetScrollRange() const
{
    SIZE sz = {0, 0};
    if ( m_pVerticalScrollbar ) sz.cy = m_pVerticalScrollbar->GetScrollRange();
    if ( m_pHorizontalScrollbar ) sz.cx = m_pHorizontalScrollbar->GetScrollRange();
    return sz;
}

void CScrollViewerUI::SetScrollPos( const SIZE& szPos )
{
    int cx = 0;
    int cy = 0;
    if ( m_pVerticalScrollbar && m_pVerticalScrollbar->IsEnabled() ) {
        int iLastScrollPos = m_pVerticalScrollbar->GetScrollPos();
        m_pVerticalScrollbar->SetScrollPos( szPos.cy );
        cy = m_pVerticalScrollbar->GetScrollPos() - iLastScrollPos;
    }

    if ( m_pHorizontalScrollbar && m_pHorizontalScrollbar->IsEnabled() ) {
        int iLastScrollPos = m_pHorizontalScrollbar->GetScrollPos();
        m_pHorizontalScrollbar->SetScrollPos( szPos.cx );
        cx = m_pHorizontalScrollbar->GetScrollPos() - iLastScrollPos;
    }

    if ( cx == 0 && cy == 0 ) return;

    if ( m_pContent && m_pContent->IsVisible() ) {
        RECT rcPos = m_pContent->GetPos();
        rcPos.left -= cx;
        rcPos.right -= cx;
        rcPos.top -= cy;
        rcPos.bottom -= cy;
        m_pContent->SetPos( rcPos );
    }

    Invalidate();
}

void CScrollViewerUI::LineUp()
{
    int cyLine = m_pVerticalScrollbar->GetLineSize();
	if ( m_pManager ) cyLine = m_pManager->GetDefaultFontInfo().tmHeight + 8;

    SIZE sz = GetScrollPos();
    sz.cy -= cyLine;
    SetScrollPos( sz );
}

void CScrollViewerUI::LineDown()
{
    int cyLine = m_pVerticalScrollbar->GetLineSize();
    if ( m_pManager ) cyLine = m_pManager->GetDefaultFontInfo().tmHeight + 8;

    SIZE sz = GetScrollPos();
    sz.cy += cyLine;
    SetScrollPos( sz );
}

void CScrollViewerUI::PageUp()
{
    SIZE sz = GetScrollPos();
    int iOffset = m_rcItem.bottom - m_rcItem.top - m_rcInset.top - m_rcInset.bottom;
    if ( m_pHorizontalScrollbar && m_pHorizontalScrollbar->IsVisible() ) iOffset -= m_pHorizontalScrollbar->GetFixedHeight();
    sz.cy -= iOffset;
    SetScrollPos( sz );
}

void CScrollViewerUI::PageDown()
{
    SIZE sz = GetScrollPos();
    int iOffset = m_rcItem.bottom - m_rcItem.top - m_rcInset.top - m_rcInset.bottom;
    if ( m_pHorizontalScrollbar && m_pHorizontalScrollbar->IsVisible() ) iOffset -= m_pHorizontalScrollbar->GetFixedHeight();
    sz.cy += iOffset;
    SetScrollPos( sz );
}

void CScrollViewerUI::HomeUp()
{
    SIZE sz = GetScrollPos();
    sz.cy = 0;
    SetScrollPos( sz );
}

void CScrollViewerUI::EndDown()
{
    SIZE sz = GetScrollPos();
    sz.cy = GetScrollRange().cy;
    SetScrollPos( sz );
}

void CScrollViewerUI::LineLeft()
{
    SIZE sz = GetScrollPos();
    sz.cx -= m_pHorizontalScrollbar->GetLineSize();
    SetScrollPos( sz );
}

void CScrollViewerUI::LineRight()
{
    SIZE sz = GetScrollPos();
    sz.cx += m_pHorizontalScrollbar->GetLineSize();
    SetScrollPos( sz );
}

void CScrollViewerUI::PageLeft()
{
    SIZE sz = GetScrollPos();
    int iOffset = m_rcItem.right - m_rcItem.left - m_rcInset.left - m_rcInset.right;
    if ( m_pVerticalScrollbar && m_pVerticalScrollbar->IsVisible() ) iOffset -= m_pVerticalScrollbar->GetFixedWidth();
    sz.cx -= iOffset;
    SetScrollPos( sz );
}

void CScrollViewerUI::PageRight()
{
    SIZE sz = GetScrollPos();
    int iOffset = m_rcItem.right - m_rcItem.left - m_rcInset.left - m_rcInset.right;
    if ( m_pVerticalScrollbar && m_pVerticalScrollbar->IsVisible() ) iOffset -= m_pVerticalScrollbar->GetFixedWidth();
    sz.cx += iOffset;
    SetScrollPos( sz );
}

void CScrollViewerUI::HomeLeft()
{
    SIZE sz = GetScrollPos();
    sz.cx = 0;
    SetScrollPos( sz );
}

void CScrollViewerUI::EndRight()
{
    SIZE sz = GetScrollPos();
    sz.cx = GetScrollRange().cx;
    SetScrollPos( sz );
}

void CScrollViewerUI::EnableScrollBar( int iStyleVertical, int iStyleHorizontal )
{
    if ( iStyleVertical != UISCROLL_NONE && !m_pVerticalScrollbar ) {
        m_pVerticalScrollbar = new CScrollbarUI;
        m_pVerticalScrollbar->SetOwner( this );
        m_pVerticalScrollbar->SetManager( m_pManager, NULL, false );
        m_pVerticalScrollbar->SetEnabled( false );
        //m_iVerticalScrollbarStyle = iStyleVertical;
        if ( iStyleVertical == UISCROLL_SHOW )
            m_pVerticalScrollbar->SetVisible( true );
        else
            m_pVerticalScrollbar->SetVisible( false );
        if ( m_pManager ) {
            LPCTSTR pDefaultAttributes = m_pManager->GetDefaultAttributeList( _T( "VScrollBar" ) );
            if ( pDefaultAttributes ) {
                m_pVerticalScrollbar->ApplyAttributeList( pDefaultAttributes );
            }
        }
    }
    else if ( iStyleVertical == UISCROLL_NONE && m_pVerticalScrollbar ) {
        delete m_pVerticalScrollbar;
        m_pVerticalScrollbar = NULL;
        //m_iVerticalScrollbarStyle = UISCROLL_NONE;
    }

    if ( iStyleHorizontal != UISCROLL_NONE && !m_pHorizontalScrollbar ) {
        m_pHorizontalScrollbar = new CScrollbarUI;
        m_pHorizontalScrollbar->SetHorizontal( true );
        m_pHorizontalScrollbar->SetOwner( this );
        m_pHorizontalScrollbar->SetManager( m_pManager, NULL, false );
        m_pHorizontalScrollbar->SetEnabled( false );
        //m_iHorizontalScrollbarStyle = iStyleHorizontal;
        if ( iStyleHorizontal == UISCROLL_SHOW )
            m_pHorizontalScrollbar->SetVisible( true );
        else
            m_pHorizontalScrollbar->SetVisible( false );
        if ( m_pManager ) {
            LPCTSTR pDefaultAttributes = m_pManager->GetDefaultAttributeList( _T( "HScrollBar" ) );
            if ( pDefaultAttributes ) {
                m_pHorizontalScrollbar->ApplyAttributeList( pDefaultAttributes );
            }
        }
    }
    else if ( iStyleHorizontal == UISCROLL_NONE && m_pHorizontalScrollbar ) {
        delete m_pHorizontalScrollbar;
        m_pHorizontalScrollbar = NULL;
        //m_iHorizontalScrollbarStyle = UISCROLL_NONE;
    }
    if (  m_iVerticalScrollbarStyle != iStyleVertical ||
            m_iHorizontalScrollbarStyle != iStyleHorizontal ) {
        m_iVerticalScrollbarStyle = iStyleVertical;
        m_iHorizontalScrollbarStyle = iStyleHorizontal;
        //要强行更新布局
        NeedUpdate( true );
    }
}
CScrollbarUI* CScrollViewerUI::GetVerticalScrollbar() const
{
    return m_pVerticalScrollbar;
}

CScrollbarUI* CScrollViewerUI::GetHorizontalScrollbar() const
{
    return m_pHorizontalScrollbar;
}
void CScrollViewerUI::ProcessScrollbar( const SIZE& sz, const SIZE& szNeed )
{
    //传入的rc是客户区
    if ( m_pVerticalScrollbar != NULL ) {
        int cyScroll = szNeed.cy - sz.cy;
        //要求达到了，则启用滚动条，如果是auto则显示
        if ( cyScroll > 0 && !m_pVerticalScrollbar->IsEnabled() ) {
            m_pVerticalScrollbar->SetEnabled( true );
            m_pVerticalScrollbar->SetScrollRange( cyScroll );
            m_pVerticalScrollbar->SetScrollPos( 0 );
            if ( m_iVerticalScrollbarStyle == UISCROLL_AUTO )
                m_pVerticalScrollbar->SetVisible( true );
        }
        else if ( cyScroll <= 0 && m_pVerticalScrollbar->IsEnabled() ) {
            //要求达不到，则禁止滚动条，如果是auto则隐藏
            m_pVerticalScrollbar->SetScrollRange( 0 );
            m_pVerticalScrollbar->SetScrollPos( 0 );
            m_pVerticalScrollbar->SetEnabled( false );
            if ( m_iVerticalScrollbarStyle == UISCROLL_AUTO )
                m_pVerticalScrollbar->SetVisible( false );
        }
        else if ( m_pVerticalScrollbar->IsEnabled() )
            m_pVerticalScrollbar->SetScrollRange( cyScroll );
    }

    if ( m_pHorizontalScrollbar != NULL ) {
        int cxScroll = szNeed.cx - sz.cx;
        //要求达到了，则启用滚动条，如果是auto则显示
        if ( cxScroll > 0 && !m_pHorizontalScrollbar->IsEnabled() ) {
            m_pHorizontalScrollbar->SetEnabled( true );
            m_pHorizontalScrollbar->SetScrollRange( cxScroll );
            m_pHorizontalScrollbar->SetScrollPos( 0 );
            if ( m_iHorizontalScrollbarStyle == UISCROLL_AUTO )
                m_pHorizontalScrollbar->SetVisible( true );
        }
        else if ( cxScroll <= 0 && m_pHorizontalScrollbar->IsEnabled() ) {
            //要求达不到，则禁止滚动条，如果是auto则隐藏
            m_pHorizontalScrollbar->SetScrollRange( 0 );
            m_pHorizontalScrollbar->SetScrollPos( 0 );
            m_pHorizontalScrollbar->SetEnabled( false );
            if ( m_iHorizontalScrollbarStyle == UISCROLL_AUTO )
                m_pHorizontalScrollbar->SetVisible( false );
        }
        else if ( m_pHorizontalScrollbar->IsEnabled() )
            m_pHorizontalScrollbar->SetScrollRange( cxScroll );
    }
}
/////////////////////////////////////////////////////////////////////////////////////
//
//
IMPLEMENT_DYNCREATE( CContainerUI )
CContainerUI::CContainerUI() :
    m_iChildPadding( 0 ),
    m_bAutoDestroy( true )
{
    //可焦点
    m_bCanFocus = true;
    //默认拉伸
    m_iHorizontalAlignment = m_iVerticalAlignment = UIALIGNMENT_STRETCH;
}

CContainerUI::~CContainerUI()
{
    RemoveAll();
}

LPCTSTR CContainerUI::GetClass() const
{
    return _T( "ContainerUI" );
}

LPVOID CContainerUI::GetInterface( LPCTSTR pstrName )
{
    if ( _tcscmp( pstrName, _T( "IContainer" ) ) == 0 ) return static_cast<IContainerUI*>( this );
    else if ( _tcscmp( pstrName, _T( "Container" ) ) == 0 ) return static_cast<CContainerUI*>( this );
    return CElementUI::GetInterface( pstrName );
}

CElementUI* CContainerUI::GetItemAt( int iIndex ) const
{
    if ( iIndex < 0 || iIndex >= m_items.GetSize() ) return NULL;
    return m_items[iIndex];
}

int CContainerUI::GetItemIndex( CElementUI* pControl ) const
{
    return m_items.Find( pControl );
}

bool CContainerUI::SetItemIndex( CElementUI* pControl, int iIndex )
{
    int iFind = m_items.Find( pControl );
    if ( iFind != -1 ) {
        //不能简单的更新图像
        //因为造成了排版上的顺序原因·所以要更新排列
        //Invalidate();
        m_items.Remove( iFind );
        if ( m_items.InsertAt( iIndex, pControl ) ) {
            NeedUpdate( true );
            return true;
        }
        return false;
    }

    return false;
}

int CContainerUI::GetCount() const
{
    return m_items.GetSize();
}

bool CContainerUI::Add( CElementUI* pControl )
{
    if ( pControl == NULL ) return false;

    if ( m_pManager != NULL ) m_pManager->InitControls( pControl, this );
    NeedUpdate( true );
    return m_items.Add( pControl );
}

bool CContainerUI::AddAt( CElementUI* pControl, int iIndex )
{
    if ( pControl == NULL ) return false;

    if ( m_pManager != NULL ) m_pManager->InitControls( pControl, this );
    NeedUpdate( true );
    return m_items.InsertAt( iIndex, pControl );
}

bool CContainerUI::Remove( CElementUI* pControl )
{
    int iFind = m_items.Find( pControl );
    if ( iFind != -1 ) {
        NeedUpdate( true );
        if ( m_bAutoDestroy ) delete pControl;

        return m_items.Remove( iFind );
    }
    return false;
}

bool CContainerUI::RemoveAt( int iIndex )
{
    CElementUI* pControl = GetItemAt( iIndex );
    if ( pControl != NULL ) {
        return Remove( pControl );
    }

    return false;
}

void CContainerUI::RemoveAll()
{
    if ( GetCount() == 0 )return;

    if ( m_bAutoDestroy )
        m_items.Resize_Delete( 0 );
    else
        m_items.Empty();
    NeedUpdate( true );
}
void CContainerUI::SetVisible( bool bVisible )
{
    if ( m_bVisible == bVisible ) return;

    for ( int it = 0; it < m_items.GetSize(); ++it ) {
        m_items[it]->SetInternVisible( bVisible );
    }

    CElementUI::SetVisible( bVisible );
}

void CContainerUI::SetInternVisible( bool bVisible )
{
    if ( m_bInternVisible == bVisible ) return;

    for ( int it = 0; it < m_items.GetSize(); ++it ) {
        m_items[it]->SetInternVisible( bVisible );
    }

    CElementUI::SetInternVisible( bVisible );
}

void CContainerUI::SetEnabled( bool bEnabled )
{
    if ( m_bEnabled == bEnabled ) return;

    for ( int it = 0; it < m_items.GetSize(); ++it ) {
        m_items[it]->SetInternEnabled( bEnabled );
    }

    CElementUI::SetEnabled( bEnabled );
}
void CContainerUI::SetInternEnabled( bool bEnabled )
{
    if ( m_bInternEnabled == bEnabled )return;

    for ( int it = 0; it < m_items.GetSize(); ++it ) {
        m_items[it]->SetInternEnabled( bEnabled );
    }

    CElementUI::SetInternEnabled( bEnabled );
}
void CContainerUI::SetMouseEnabled( bool bEnabled )
{
    if ( m_bMouseEnabled == bEnabled )return;

    for ( int it = 0; it < m_items.GetSize(); ++it ) {
        m_items[it]->SetInternMouseEnabled( bEnabled );
    }

    CElementUI::SetMouseEnabled( bEnabled );
}
void CContainerUI::SetInternMouseEnabled( bool bEnabled )
{
    if ( m_bInternEnabled == bEnabled )return;

    for ( int it = 0; it < m_items.GetSize(); ++it ) {
        m_items[it]->SetInternMouseEnabled( bEnabled );
    }
    CElementUI::SetInternMouseEnabled( bEnabled );
}
int CContainerUI::GetChildPadding() const
{
    return m_iChildPadding;
}

void CContainerUI::SetChildPadding( int iPadding )
{
    if ( m_iChildPadding == iPadding )return;
    m_iChildPadding = iPadding;

    NeedUpdate( true );
}
bool CContainerUI::IsAutoDestroy() const
{
    return m_bAutoDestroy;
}

void CContainerUI::SetAutoDestroy( bool bAuto )
{
    m_bAutoDestroy = bAuto;
}

// int CContainerUI::FindSelectable( int iIndex, bool bForward /*= true*/ ) const
// {
//     // NOTE: This is actually a helper-function for the list/combo/ect controls
//     //       that allow them to find the next enabled/available selectable item
//     if ( GetCount() == 0 ) return -1;
//     iIndex = CLAMP( iIndex, 0, GetCount() - 1 );
//     if ( bForward ) {
//         for ( int i = iIndex; i < GetCount(); ++i ) {
//             if ( GetItemAt( i )->GetInterface( _T( "ListItem" ) ) != NULL
//                     && GetItemAt( i )->IsVisible()
//                     && GetItemAt( i )->IsEnabled() ) return i;
//         }
//         return -1;
//     }
//     else {
//         for ( int i = iIndex; i >= 0; --i ) {
//             if ( GetItemAt( i )->GetInterface( _T( "ListItem" ) ) != NULL
//                     && GetItemAt( i )->IsVisible()
//                     && GetItemAt( i )->IsEnabled() ) return i;
//         }
//         //找不到从头找一次
//         return FindSelectable( 0, true );
//     }
// }
SIZE CContainerUI::EstimateSizeOver( const SIZE& szAvailable )
{
    SIZE retSZ = {0};

    //简单的取所有元素最大测量
    for ( int it = 0; it < m_items.GetSize(); ++it ) {
        CElementUI* pControl = m_items[it];
        if ( !pControl->IsVisible() ) continue;

        RECT rcPadding = pControl->GetPadding();
        SIZE szRemind = szAvailable;
        szRemind.cx -= rcPadding.left + rcPadding.right;
        szRemind.cy -= rcPadding.top + rcPadding.bottom;
        szRemind.cx = MAX( szRemind.cx, 0 );
        szRemind.cy = MAX( szRemind.cy, 0 );

        pControl->EstimateSize( szRemind );
        szRemind = pControl->GetDesiredSize();

        retSZ.cx = MAX( retSZ.cx, szRemind.cx + rcPadding.left + rcPadding.right );
        retSZ.cy = MAX( retSZ.cy, szRemind.cy + rcPadding.top + rcPadding.bottom );
    }
    return retSZ;
}
RECT CContainerUI::SetPosOver( const RECT& rc )
{
    for ( int it = 0; it < m_items.GetSize(); ++it ) {
        CElementUI* pControl = m_items[it];
        if ( !pControl->IsVisible() ) continue;

        RECT rcPadding = pControl->GetPadding();
        RECT rcRemind = rc;
        rcRemind.left += rcPadding.left; rcRemind.right -= rcPadding.right;
        rcRemind.top += rcPadding.top; rcRemind.bottom -= rcPadding.bottom;
        rcRemind.right = MAX( rcRemind.left, rcRemind.right );
        rcRemind.bottom = MAX( rcRemind.top, rcRemind.bottom );

        pControl->SetPos( rcRemind );
    }
    return rc;
}
void CContainerUI::DoPaintOver( GRAPHorHDC& gorh )
{
    for ( int it = 0; it < m_items.GetSize(); ++it ) {
        CElementUI* pControl = m_items[it];
        if ( !pControl->IsVisible() ) continue;

        RECT rcPadding = pControl->GetPadding();
        RECT rcClip = {m_rcItem.left + rcPadding.left, \
                       m_rcItem.top + rcPadding.top, \
                       m_rcItem.right - rcPadding.right, \
                       m_rcItem.bottom - rcPadding.bottom
                      };
        if ( ::IsRectEmpty( &rcClip ) )
            continue;
        CRgn oldRegion = gorh.IntersectClip( rcClip );

        pControl->DoPaint( gorh, m_rcPaint );

        gorh.SetClip( oldRegion );
    }
}
void CContainerUI::SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue )
{
    if ( _tcscmp( pstrName, _T( "childpadding" ) ) == 0 ) SetChildPadding( _ttoi( pstrValue ) );
    else CElementUI::SetAttribute( pstrName, pstrValue );
}

void CContainerUI::SetManager( CPaintManagerUI* pManager, CElementUI* pParent, bool bInit )
{
    for ( int it = 0; it < m_items.GetSize(); ++it ) {
        m_items[it]->SetManager( pManager, this, bInit );
    }
    CElementUI::SetManager( pManager, pParent, bInit );
}

CElementUI* CContainerUI::FindControl( FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags )
{
    if ( ( uFlags & UIFIND_VISIBLE ) != 0 && !IsVisible() ) return NULL;
    if ( ( uFlags & UIFIND_ENABLED ) != 0 && !IsEnabled() ) return NULL;
    if ( ( uFlags & UIFIND_HITTEST ) != 0 && ( !m_bMouseEnabled || !::PtInRect( &m_rcItem, * reinterpret_cast<LPPOINT>( pData ) ) ) ) return NULL;
    if ( ( uFlags & UIFIND_CAN_FOCUS ) != 0 && !IsCanFocus() ) return NULL;

    CElementUI* pThisResult = CElementUI::FindControl( Proc, pData, uFlags );

    if ( ( uFlags & UIFIND_ME_FIRST ) != 0 && pThisResult )return pThisResult;

    if ( ( uFlags & UIFIND_TOP_FIRST ) != 0 ) {
        for ( int it = m_items.GetSize() - 1; it >= 0; --it ) {
            CElementUI* pControl = m_items[it]->FindControl( Proc, pData, uFlags );
            if ( pControl != NULL ) return pControl;
        }
    }
    else {
        for ( int it = 0; it < m_items.GetSize(); ++it ) {
            CElementUI* pControl = m_items[it]->FindControl( Proc, pData, uFlags );
            if ( pControl != NULL ) return pControl;
        }
    }

    return pThisResult;
}


/////////////////////////////////////////////////////////////////////////////////////
//
//
IMPLEMENT_DYNCREATE( CVerticalLayoutUI )

LPCTSTR CVerticalLayoutUI::GetClass() const
{
    return _T( "VertialLayoutUI" );
}
LPVOID CVerticalLayoutUI::GetInterface( LPCTSTR pstrName )
{
    if ( _tcscmp( pstrName, _T( "VerticalLayout" ) ) == 0 ) return static_cast<CVerticalLayoutUI*>( this );
    return CContainerUI::GetInterface( pstrName );
}
SIZE CVerticalLayoutUI::EstimateSizeOver( const SIZE& szAvailable )
{
    SIZE retSZ = {0};
    m_nAdjustables = 0;
    for ( int it = 0; it < m_items.GetSize(); ++it ) {
        CElementUI* pControl = m_items[it];
        if ( !pControl->IsVisible() ) continue;

        RECT rcPadding = pControl->GetPadding();
        SIZE szRemind = szAvailable;
        szRemind.cx -= rcPadding.left + rcPadding.right;
        szRemind.cy -= rcPadding.top + rcPadding.bottom;
        szRemind.cx = MAX( szRemind.cx, 0 );
        szRemind.cy = MAX( szRemind.cy, 0 );

        pControl->EstimateSize( szRemind );
        szRemind = pControl->GetDesiredSize();

        retSZ.cx = MAX( retSZ.cx, szRemind.cx + rcPadding.left + rcPadding.right );
        retSZ.cy += szRemind.cy + rcPadding.top + rcPadding.bottom + ( it ? m_iChildPadding : 0 );

        if ( szRemind.cy == 0 )
            ++m_nAdjustables;
    }
    return retSZ;
}
RECT CVerticalLayoutUI::SetPosOver( const RECT& rc )
{
    int cyExpand = 0;
    int cyLastExpand = 0;
    if ( m_nAdjustables > 0 ) {
        cyExpand = MAX( 0, ( rc.bottom - rc.top - m_szItemDesired.cy ) / m_nAdjustables );
        cyLastExpand = MAX( 0, rc.bottom - rc.top - m_szItemDesired.cy - ( m_nAdjustables - 1 ) * cyExpand );
    }

    int iAdjustables = 0;
    int posY = rc.top;
    for ( int it = 0; it < m_items.GetSize(); ++it ) {
        CElementUI* pControl = m_items[it];
        if ( !pControl->IsVisible() ) continue;

        RECT rcPadding = pControl->GetPadding();
        RECT rcRemind = rc;
        rcRemind.left += rcPadding.left; rcRemind.right -= rcPadding.right;
        rcRemind.right = MAX( rcRemind.left, rcRemind.right );

        int cx = pControl->GetFixedWidth();
        SIZE sz = pControl->GetDesiredSize();

        int hAligenment = UIALIGNMENT_LEFT_TOP;
		//sz.cx改成cx
        if ( cx < rcRemind.right - rcRemind.left || pControl->GetHorizontalAlignment() != UIALIGNMENT_STRETCH )
            hAligenment = pControl->GetHorizontalAlignment();

        int retX = 0;
        if ( hAligenment == UIALIGNMENT_STRETCH ) {
            retX = cx ? cx : ( rcRemind.right - rcRemind.left );
        }
        else {
            retX = sz.cx ? sz.cx : ( rcRemind.right - rcRemind.left );
        }
        retX = CLAMP( retX, pControl->GetMinWidth(), pControl->GetMaxWidth() );

        int retY = sz.cy;
        if ( sz.cy == 0 ) {
            ++iAdjustables;
            retY = ( iAdjustables == m_nAdjustables ) ? cyLastExpand : cyExpand;
			retY = CLAMP( retY, pControl->GetMinHeight(), pControl->GetMaxWidth() );
        }

        posY += rcPadding.top;
        int posX = 0;
        if ( hAligenment == UIALIGNMENT_LEFT_TOP )
            posX = rcRemind.left;
        else if ( hAligenment == UIALIGNMENT_RIGHT_BOTTOM )
            posX = rcRemind.right - retX;
        else
            posX = ( rcRemind.left + rcRemind.right - retX ) / 2;

        pControl->SetPos( CRect( posX, posY, posX + retX, posY + retY ) );
        posY += pControl->GetHeight() + rcPadding.bottom + m_iChildPadding;
    }
    return rc;
}
void CVerticalLayoutUI::DoPaintOver( GRAPHorHDC& gorh )
{
	for ( int it = 0; it < m_items.GetSize(); ++it ) {
		CElementUI* pControl = m_items[it];
		if ( !pControl->IsVisible() ) continue;

		RECT rcPadding = pControl->GetPadding();
		RECT rcClip = {m_rcItem.left + rcPadding.left, \
			m_rcItem.top, \
			m_rcItem.right - rcPadding.right, \
			m_rcItem.bottom
		};
		if ( ::IsRectEmpty( &rcClip ) )
			continue;
		CRgn oldRegion = gorh.IntersectClip( rcClip );

		pControl->DoPaint( gorh, m_rcPaint );

		gorh.SetClip( oldRegion );
	}
}
/////////////////////////////////////////////////////////////////////////////////////
//
//
IMPLEMENT_DYNCREATE( CHorizontalLayoutUI )

LPCTSTR CHorizontalLayoutUI::GetClass() const
{
    return _T( "HorizontalLayoutUI" );
}
LPVOID CHorizontalLayoutUI::GetInterface( LPCTSTR pstrName )
{
    if ( _tcscmp( pstrName, _T( "HorizontalLayout" ) ) == 0 ) return static_cast<CHorizontalLayoutUI*>( this );
    return CContainerUI::GetInterface( pstrName );
}
SIZE CHorizontalLayoutUI::EstimateSizeOver( const SIZE& szAvailable )
{
    SIZE retSZ = {0};
    m_nAdjustables = 0;
    for ( int it = 0; it < m_items.GetSize(); ++it ) {
        CElementUI* pControl = m_items[it];
        if ( !pControl->IsVisible() ) continue;

        RECT rcPadding = pControl->GetPadding();
        SIZE szRemind = szAvailable;
        szRemind.cx -= rcPadding.left + rcPadding.right;
        szRemind.cy -= rcPadding.top + rcPadding.bottom;
        szRemind.cx = MAX( szRemind.cx, 0 );
        szRemind.cy = MAX( szRemind.cy, 0 );

        pControl->EstimateSize( szRemind );
        szRemind = pControl->GetDesiredSize();

        retSZ.cx += szRemind.cx + rcPadding.left + rcPadding.right + ( it ? m_iChildPadding : 0 );
        retSZ.cy = MAX( retSZ.cy, szRemind.cy + rcPadding.top + rcPadding.bottom );

        if ( szRemind.cx == 0 )
            ++m_nAdjustables;
    }
    return retSZ;
}
RECT CHorizontalLayoutUI::SetPosOver( const RECT& rc )
{
    int cxExpand = 0;
    int cxLastExpand = 0;
    if ( m_nAdjustables > 0 ) {
        cxExpand = MAX( 0, ( rc.right - rc.left - m_szItemDesired.cx ) / m_nAdjustables );
        cxLastExpand = MAX( 0, rc.right - rc.left - m_szItemDesired.cx - ( m_nAdjustables - 1 ) * cxExpand );
    }
    int iAdjustables = 0;
    int posX = rc.left;
    for ( int it = 0; it < m_items.GetSize(); ++it ) {
        CElementUI* pControl = m_items[it];
        if ( !pControl->IsVisible() ) continue;

        RECT rcPadding = pControl->GetPadding();
        RECT rcRemind = rc;
        rcRemind.top += rcPadding.top; rcRemind.bottom -= rcPadding.bottom;
        rcRemind.bottom = MAX( rcRemind.top, rcRemind.bottom );

        int cy = pControl->GetFixedHeight();
        SIZE sz = pControl->GetDesiredSize();

        int vAligenment = UIALIGNMENT_LEFT_TOP;
        if ( cy < rcRemind.bottom - rcRemind.top || pControl->GetVerticalAlignment() != UIALIGNMENT_STRETCH )
            vAligenment = pControl->GetVerticalAlignment();

        int retY = 0;
        if ( vAligenment == UIALIGNMENT_STRETCH ) {
            retY = cy ? cy : ( rcRemind.bottom - rcRemind.top );
        }
        else {
            retY = sz.cy ? sz.cy : ( rcRemind.bottom - rcRemind.top );
        }
        retY = CLAMP( retY, pControl->GetMinHeight(), pControl->GetMaxWidth() );

        int retX = sz.cx;
        if ( sz.cx == 0 ) {
            ++iAdjustables;
            retX = ( iAdjustables == m_nAdjustables ) ? cxLastExpand : cxExpand;
			retX = CLAMP( retX, pControl->GetMinWidth(), pControl->GetMaxWidth() );
        }
  
        posX += rcPadding.left;
        int posY = 0;
        if ( vAligenment == UIALIGNMENT_LEFT_TOP )
            posY = rcRemind.top;
        else if ( vAligenment == UIALIGNMENT_RIGHT_BOTTOM )
            posY = rcRemind.bottom - rcRemind.top;
        else
            posY = ( rcRemind.bottom + rcRemind.top - retY ) / 2;

        pControl->SetPos( CRect( posX, posY, posX + retX, posY + retY ) );
        posX += pControl->GetWidth() + rcPadding.right + m_iChildPadding;
    }
    return rc;
}
void CHorizontalLayoutUI::DoPaintOver( GRAPHorHDC& gorh )
{
	for ( int it = 0; it < m_items.GetSize(); ++it ) {
		CElementUI* pControl = m_items[it];
		if ( !pControl->IsVisible() ) continue;

		RECT rcPadding = pControl->GetPadding();
		RECT rcClip = {m_rcItem.left, \
			m_rcItem.top + rcPadding.top, \
			m_rcItem.right, \
			m_rcItem.bottom - rcPadding.bottom
		};
		if ( ::IsRectEmpty( &rcClip ) )
			continue;
		CRgn oldRegion = gorh.IntersectClip( rcClip );

		pControl->DoPaint( gorh, m_rcPaint );

		gorh.SetClip( oldRegion );
	}
}
/////////////////////////////////////////////////////////////////////////////////////
//
//
IMPLEMENT_DYNCREATE( CDockLayoutUI )

CDockLayoutUI::CDockLayoutUI():m_bLastFill(false)
{

}
LPCTSTR CDockLayoutUI::GetClass() const
{
	return _T( "DockLayoutUI" );
}

LPVOID CDockLayoutUI::GetInterface( LPCTSTR pstrName )
{
	if ( _tcscmp( pstrName, _T( "DockLayout" ) ) == 0 ) return static_cast<CDockLayoutUI*>( this );
	return CContainerUI::GetInterface( pstrName );
}


bool CDockLayoutUI::IsLastFill() const
{
	return m_bLastFill;
}
void CDockLayoutUI::SetLastFill(bool lastFill)
{
	m_bLastFill=lastFill;
}

SIZE CDockLayoutUI::EstimateSizeOver( const SIZE& szAvailable )
{
	SIZE szAvailableRemind=szAvailable;

	for ( int it = 0; it < m_items.GetSize(); ++it ) {
		CElementUI* pControl = m_items[it];
		if ( !pControl->IsVisible() ) continue;

		RECT rcPadding = pControl->GetPadding();
		SIZE szRemind = szAvailableRemind;
		szRemind.cx -= rcPadding.left + rcPadding.right;
		szRemind.cy -= rcPadding.top + rcPadding.bottom;
		szRemind.cx = MAX( szRemind.cx, 0 );
		szRemind.cy = MAX( szRemind.cy, 0 );

		pControl->EstimateSize( szRemind );
		szRemind = pControl->GetDesiredSize();

		switch(pControl->GetDockSide())
		{
		case UIDOCK_LEFT:
		case UIDOCK_RIGHT:
			szAvailableRemind.cx-=szRemind.cx;
			break;
		case UIDOCK_TOP:
		case UIDOCK_BOTTOM:
			szAvailableRemind.cy-=szRemind.cy;
		}
		
		szAvailableRemind.cx=MAX(0,szAvailableRemind.cx);
		szAvailableRemind.cy=MAX(0,szAvailableRemind.cy);
	}
	return szAvailable;
}

RECT CDockLayoutUI::SetPosOver( const RECT& rc )
{
	RECT rcLast=rc;

	int iLastit=0;
	for ( int it = 0; it < m_items.GetSize(); ++it ) {
		CElementUI* pControl = m_items[it];
		if ( !pControl->IsVisible() ) continue;
		iLastit=it;
	}
	for ( int it = 0; it < m_items.GetSize(); ++it ) {
		CElementUI* pControl = m_items[it];
		if ( !pControl->IsVisible() ) continue;

		RECT rcPadding = pControl->GetPadding();
		RECT rcRemind = rcLast;
		rcRemind.left += rcPadding.left; rcRemind.right -= rcPadding.right;
		rcRemind.top += rcPadding.top; rcRemind.bottom -= rcPadding.bottom;
		rcRemind.right = MAX( rcRemind.left, rcRemind.right );
		rcRemind.bottom = MAX( rcRemind.top, rcRemind.bottom );

		int iDockSide=pControl->GetDockSide();
		int hAligenment = pControl->GetHorizontalAlignment();
		int vAligenment = pControl->GetVerticalAlignment();

		int cx = pControl->GetFixedWidth();
		int cy = pControl->GetFixedHeight();
		SIZE sz = pControl->GetDesiredSize();

		if(it==iLastit)
		{
			if(cx>=rcRemind.right - rcRemind.left  && hAligenment==UIALIGNMENT_STRETCH)
				hAligenment=UIALIGNMENT_LEFT_TOP;
			if(cy>=rcRemind.bottom - rcRemind.top  && vAligenment==UIALIGNMENT_STRETCH)
				vAligenment=UIALIGNMENT_LEFT_TOP;

			int retX = 0;
			if ( hAligenment == UIALIGNMENT_STRETCH ) {
				retX = cx ? cx : ( rcRemind.right - rcRemind.left );
			}
			else {
				retX = sz.cx ? sz.cx : ( rcRemind.right - rcRemind.left );
			}
			retX = CLAMP( retX, pControl->GetMinWidth(), pControl->GetMaxWidth() );
			int retY = 0;
			if ( vAligenment == UIALIGNMENT_STRETCH ) {
				retY = cy ? cy : ( rcRemind.bottom - rcRemind.top );
			}
			else {
				retY = sz.cy ? sz.cy : ( rcRemind.bottom - rcRemind.top );
			}
			retY = CLAMP( retY, pControl->GetMinHeight(), pControl->GetMaxWidth() );

			int posX = 0;
			if ( hAligenment == UIALIGNMENT_LEFT_TOP )
				posX = rcRemind.left;
			else if ( hAligenment == UIALIGNMENT_RIGHT_BOTTOM )
				posX = rcRemind.right - retX;
			else
				posX = ( rcRemind.left + rcRemind.right - retX ) / 2;

			int posY = 0;
			if ( vAligenment == UIALIGNMENT_LEFT_TOP )
				posY = rcRemind.top;
			else if ( vAligenment == UIALIGNMENT_RIGHT_BOTTOM )
				posY = rcRemind.bottom - rcRemind.top;
			else
				posY = ( rcRemind.bottom + rcRemind.top - retY ) / 2;

			pControl->SetPos( CRect( posX, posY, posX + retX, posY + retY ) );
			break;
		}

		int retX=0;
		int posX=0;
		if(iDockSide==UIDOCK_LEFT || iDockSide==UIDOCK_RIGHT)
		{
			retX=sz.cx;
			if(retX==0)
			{
				retX=rcRemind.right-rcRemind.left;
				 retX = CLAMP( retX, pControl->GetMinWidth(), pControl->GetMaxWidth() );
			}
			if(iDockSide==UIDOCK_LEFT)
				posX=rcRemind.left;
			else
				posX=rcRemind.right-retX;
		}
		else
		{
			if(cx>=rcRemind.right - rcRemind.left  && hAligenment==UIALIGNMENT_STRETCH)
				hAligenment=UIALIGNMENT_LEFT_TOP;

			if ( hAligenment == UIALIGNMENT_STRETCH ) {
				retX = cx ? cx : ( rcRemind.right - rcRemind.left );
			}
			else {
				retX = sz.cx ? sz.cx : ( rcRemind.right - rcRemind.left );
			}
			retX = CLAMP( retX, pControl->GetMinWidth(), pControl->GetMaxWidth() );
			
			if ( hAligenment == UIALIGNMENT_LEFT_TOP )
				posX = rcRemind.left;
			else if ( hAligenment == UIALIGNMENT_RIGHT_BOTTOM )
				posX = rcRemind.right - retX;
			else
				posX = ( rcRemind.left + rcRemind.right - retX ) / 2;
		}

		int retY=0;
		int posY=0;
		if(iDockSide==UIDOCK_TOP || iDockSide==UIDOCK_BOTTOM)
		{
			retY=sz.cy;
			if(retY==0)
			{
				retY=rcRemind.bottom-rcRemind.top;
				retY = CLAMP( retY, pControl->GetMinHeight(), pControl->GetMaxHeight() );
			}
			if(iDockSide==UIDOCK_TOP)
				posY=rcRemind.top;
			else
				posY=rcRemind.bottom-retY;
		}
		else
		{
			if(cy>=rcRemind.bottom - rcRemind.top  && vAligenment==UIALIGNMENT_STRETCH)
				vAligenment=UIALIGNMENT_LEFT_TOP;

			if ( vAligenment == UIALIGNMENT_STRETCH ) {
				retY = cy ? cy : ( rcRemind.bottom - rcRemind.top );
			}
			else {
				retY = sz.cy ? sz.cy : ( rcRemind.bottom - rcRemind.top );
			}
			retY = CLAMP( retY, pControl->GetMinHeight(), pControl->GetMaxHeight() );

			if ( vAligenment == UIALIGNMENT_LEFT_TOP )
				posY = rcRemind.top;
			else if ( vAligenment == UIALIGNMENT_RIGHT_BOTTOM )
				posY = rcRemind.bottom - retY;
			else
				posY = ( rcRemind.top + rcRemind.bottom - retY ) / 2;
		}
		pControl->SetPos( CRect( posX, posY, posX + retX, posY + retY ) );
		switch(iDockSide)
		{
		case UIDOCK_LEFT:
			rcLast.left+=pControl->GetWidth()+rcPadding.left+rcPadding.right;
			break;
		case UIDOCK_TOP:
			rcLast.top+=pControl->GetHeight()+rcPadding.top+rcPadding.bottom;
			break;
		case UIDOCK_RIGHT:
			rcLast.right-=pControl->GetWidth()+rcPadding.left+rcPadding.right;
			break;
		case UIDOCK_BOTTOM:
			rcLast.bottom-=pControl->GetHeight()+rcPadding.top+rcPadding.bottom;
		}
		rcLast.right=MAX(rcLast.left,rcLast.right);
		rcLast.bottom=MAX(rcLast.top,rcLast.bottom);
	}
	return rc;
}

void CDockLayoutUI::SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue )
{
	if(_tcscmp(pstrName,_T("lastfill"))==0)SetLastFill(_tcscmp(pstrValue,_T("true"))==0);
	else CContainerUI::SetAttribute(pstrName,pstrValue);
}
