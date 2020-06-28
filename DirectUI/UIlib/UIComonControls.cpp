
#include "StdAfx.h"
#include "UIComonControls.h"

/////////////////////////////////////////////////////////////////////////////////////
//
//
IMPLEMENT_DYNCREATE( CTextBlockUI )
CTextBlockUI::CTextBlockUI(): m_bMultiLine( false ), m_iFont( -1 ), \
    m_dwTextColor( 0 ), m_dwDisabledTextColor( 0 ), m_iFontStyle( DT_NOPREFIX )
{
}
LPCTSTR CTextBlockUI::GetClass() const
{
    return _T( "TextBlockUI" );
}
LPVOID CTextBlockUI::GetInterface( LPCTSTR pstrName )
{
    if ( _tcscmp( pstrName, _T( "TextBlock" ) ) == 0 ) return static_cast<CTextBlockUI*>( this );
    return CElementUI::GetInterface( pstrName );
}

void CTextBlockUI::SetText( LPCTSTR text )
{
    if ( m_szText == text ) return;
    m_szText = text;
    NeedUpdate( true );
    // Invalidate();
}
LPCTSTR CTextBlockUI::GetText() const
{
    return m_szText;
}
void CTextBlockUI::SetTextColor( DWORD color )
{
    if ( m_dwTextColor == color )return;
    m_dwTextColor = color;

    if ( IsEnabled() )
        Invalidate();
}
DWORD CTextBlockUI::GetTextColor() const
{
    return m_dwTextColor;
}
void CTextBlockUI::SetDisabledTextColor( DWORD color )
{
    if ( m_dwDisabledTextColor == color )return;
    m_dwDisabledTextColor = color;

    if ( !IsEnabled() )
        Invalidate();
}
DWORD CTextBlockUI::GetDisabledTextColor() const
{
    return m_dwDisabledTextColor;
}
void CTextBlockUI::SetFont( int font )
{
    if ( m_iFont == font )return;
    m_iFont = font;
    NeedUpdate( true );
    //Invalidate();
}
int CTextBlockUI::GetFont() const
{
    return m_iFont;
}
void CTextBlockUI::SetMultiLine( bool multiLine )
{
    if ( m_bMultiLine == multiLine )return;
    m_bMultiLine = multiLine;
    NeedUpdate( true );
    //Invalidate();
}
bool CTextBlockUI::GetMultiLine() const
{
    return m_bMultiLine;
}
void CTextBlockUI::SetTextStyle( int style )
{
    if ( m_iFontStyle == style )return;
    m_iFontStyle = style;
    Invalidate();
}
int CTextBlockUI::GetTextStyle() const
{
    return m_iFontStyle;
}
SIZE CTextBlockUI::EstimateSizeOver( const SIZE& szAvailable )
{
    if ( !m_szText.IsEmpty() && m_pManager ) {
        RECT rc = {0, 0,  szAvailable.cx, szAvailable.cy};
        CRenderEngine::DrawText( *m_pManager->GetPaintDC(), m_pManager, rc, m_szText, m_pManager->GetDefaultFontColor(), \
                                 m_iFont, m_iFontStyle | DT_CALCRECT | ( m_bMultiLine ? 0 : DT_SINGLELINE ) );
        return CSize( rc.right - rc.left, rc.bottom - rc.top );
    }
    else if ( m_pManager )
        return CSize( 0, m_pManager->GetFontInfo( m_iFont ).tmHeight );

    return CSize();
}

void CTextBlockUI::SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue )
{
    if ( _tcscmp( pstrName, _T( "text" ) ) == 0 ) SetText( pstrValue );
    else if ( _tcscmp( pstrName, _T( "font" ) ) == 0 ) SetFont( _ttoi( pstrValue ) );
    else if ( _tcscmp( pstrName, _T( "textcolor" ) ) == 0 ) {
        if ( *pstrValue == _T( '#' ) ) pstrValue = ::CharNext( pstrValue );
        SetTextColor( _tcstoul( pstrValue, NULL, 16 ) );
    }
    else if ( _tcscmp( pstrName, _T( "disabledtextcolor" ) ) == 0 ) {
        if ( *pstrValue == _T( '#' ) ) pstrValue = ::CharNext( pstrValue );
        SetDisabledTextColor( _tcstoul( pstrValue, NULL, 16 ) );
    }
    else if ( _tcscmp( pstrName, _T( "multiline" ) ) == 0 ) SetMultiLine( _tcscmp( pstrValue, _T( "true" ) ) == 0 );
    else CElementUI::SetAttribute( pstrName, pstrValue );
}
void CTextBlockUI::DoPaintOver( GRAPHorHDC& gorh )
{
    if ( m_szText.IsEmpty() || m_pManager == NULL ) return;
    if ( m_dwTextColor == 0 )m_dwTextColor = m_pManager->GetDefaultFontColor();
    if ( m_dwDisabledTextColor == 0 )m_dwDisabledTextColor = m_pManager->GetDefaultDisabledColor();

    CRenderEngine::DrawText( gorh, m_pManager, m_rcItem, m_szText, ( IsEnabled() ? m_dwTextColor : m_dwDisabledTextColor ), \
                             m_iFont, m_iFontStyle | ( m_bMultiLine ? 0 : DT_SINGLELINE ) );
}
/////////////////////////////////////////////////////////////////////////////////////
//
//
IMPLEMENT_DYNCREATE( CHtmlBlockUI )
CHtmlBlockUI::CHtmlBlockUI(): m_nLinks( 0 ), m_nHoverLink( -1 ), m_rcLinks( NULL ), m_sLinks( NULL ), m_bMouseToCallInvalidate( false )
{
    //默认多行
    m_bMultiLine = true;
    //能接受鼠标点击
    m_bCanFocus = true;
}
CHtmlBlockUI::~CHtmlBlockUI()
{
    if ( m_rcLinks != NULL )
        delete[] m_rcLinks;
    if ( m_sLinks != NULL )
        delete[] m_sLinks;
}

LPCTSTR CHtmlBlockUI::GetClass() const
{
    return _T( "HtmlBlockUI" );
}
UINT CHtmlBlockUI::GetControlFlags() const
{
    if ( IsEnabled() && m_nLinks > 0 ) return UIFLAG_SETCURSOR;
    return 0;
}
LPVOID CHtmlBlockUI::GetInterface( LPCTSTR pstrName )
{
    if ( _tcscmp( pstrName, _T( "HtmlBlock" ) ) == 0 ) return static_cast<CHtmlBlockUI*>( this );
    return CTextBlockUI::GetInterface( pstrName );
}

LPCTSTR CHtmlBlockUI::GetLinkContent( int iIndex )
{
    if ( iIndex >= 0 && iIndex < m_nLinks ) return m_sLinks[iIndex];
    return NULL;
}
void CHtmlBlockUI::Event( TEventUI& event )
{
    if ( !IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND ) {
        if ( m_pParent != NULL ) m_pParent->Event( event );
        else CTextBlockUI::Event( event );
        return;
    }

    if ( event.Type == UIEVENT_SETCURSOR ) {
        for ( int i = 0; i < m_nLinks; ++i ) {
            if ( m_rcLinks[i].PtInRegion( &event.ptMouse ) ) {
                ::SetCursor( ::LoadCursor( NULL, MAKEINTRESOURCE( IDC_HAND ) ) );
                return;
            }
        }
    }
    if ( event.Type == UIEVENT_BUTTONDOWN || event.Type == UIEVENT_DBLCLICK && IsEnabled() ) {
        for ( int i = 0; i < m_nLinks; ++i ) {
            if ( m_rcLinks[i].PtInRegion( &event.ptMouse ) ) {
                return;
            }
        }
    }
    if ( event.Type == UIEVENT_BUTTONUP && IsEnabled() ) {
        for ( int i = 0; i < m_nLinks; ++i ) {
            if ( m_rcLinks[i].PtInRegion( &event.ptMouse ) ) {
                m_pManager->SendNotify( this, _T( "link" ), i );
                return;
            }
        }
    }

    if ( m_nLinks > 0 && event.Type == UIEVENT_MOUSEMOVE && IsEnabled() ) {
        int nHoverLink = -1;
        for ( int i = 0; i < m_nLinks; ++i ) {
            if ( m_rcLinks[i].PtInRegion( &event.ptMouse ) ) {
                nHoverLink = i;
                break;
            }
        }

        if ( m_nHoverLink != nHoverLink ) {
            m_nHoverLink = nHoverLink;
            m_bMouseToCallInvalidate = true;
            Invalidate();
            if ( m_nHoverLink != -1 )
                return;
        }
    }
    if ( event.Type == UIEVENT_MOUSELEAVE ) {
        if ( m_nLinks > 0 && IsEnabled() ) {
            if ( m_nHoverLink != -1 ) {
                m_nHoverLink = -1;
                m_bMouseToCallInvalidate = true;
                Invalidate();
                return;
            }
        }
    }
    CTextBlockUI::Event( event );
}
SIZE CHtmlBlockUI::EstimateSizeOver( const SIZE& szAvailable )
{
    if ( !m_szText.IsEmpty() && m_pManager ) {
        if ( m_bMultiLine ) {
            RECT rc = {0, 0, szAvailable.cx,  szAvailable.cy};
            CRenderEngine::DrawHtmlText( *m_pManager->GetPaintDC(), m_pManager, rc, m_szText, m_pManager->GetDefaultFontColor(), \
                                         m_iFont, m_iFontStyle | DT_CALCRECT );
            return CSize( rc.right - rc.left, rc.bottom - rc.top );
        }
        else {
            RECT rc = {0,0, MAX( szAvailable.cx, 9999 ),szAvailable.cy};
            CRenderEngine::DrawHtmlText( *m_pManager->GetPaintDC(), m_pManager, rc, m_szText, m_pManager->GetDefaultFontColor(), \
                                         m_iFont, m_iFontStyle | DT_CALCRECT | DT_SINGLELINE );
            return CSize( rc.right - rc.left, rc.bottom - rc.top );
        }
    }
    else if ( m_pManager )
        return CSize( 0, m_pManager->GetFontInfo( m_iFont ).tmHeight );
    return CSize();
}
void CHtmlBlockUI::DoPaintOver( GRAPHorHDC& gorh )
{
    if ( m_szText.IsEmpty() || m_pManager == NULL ) return;
    if ( m_dwTextColor == 0 )m_dwTextColor = m_pManager->GetDefaultFontColor();
    if ( m_dwDisabledTextColor == 0 )m_dwDisabledTextColor = m_pManager->GetDefaultDisabledColor();

    CRenderEngine::DrawHtmlText( gorh, m_pManager, m_rcItem, m_szText, ( IsEnabled() ? m_dwTextColor : m_dwDisabledTextColor ), \
                                 m_iFont, m_iFontStyle | ( m_bMultiLine ? 0 : DT_SINGLELINE ), &m_rcLinks, &m_sLinks, &m_nLinks );
}
void CHtmlBlockUI::Invalidate()
{
    if ( !m_bMouseToCallInvalidate )
        m_nLinks = 0;
    else
        m_bMouseToCallInvalidate = false;
    CTextBlockUI::Invalidate();
}
/////////////////////////////////////////////////////////////////////////////////////
//
//
IMPLEMENT_DYNCREATE( CContentControlUI )
CContentControlUI::CContentControlUI(): m_pContent( NULL ), m_bAutoDestroy( true )
{
}
CContentControlUI::~CContentControlUI()
{
    if ( m_bAutoDestroy && m_pContent )
        delete m_pContent;
}

LPCTSTR CContentControlUI::GetClass() const
{
    return _T( "ContentControlUI" );
}
LPVOID CContentControlUI::GetInterface( LPCTSTR pstrName )
{
    if ( _tcscmp( pstrName, _T( "ContentControl" ) ) == 0 )return static_cast<CContentControlUI*>( this );
    return CControlUI::GetInterface( pstrName );
}

CElementUI* CContentControlUI::GetContent() const
{
    return m_pContent;
}
void CContentControlUI::SetContent( CElementUI* content )
{
    if ( m_pContent == content )return;

    if ( m_bAutoDestroy && m_pContent != NULL )
        delete m_pContent;
    m_pContent = content;

    if ( m_pManager != NULL && m_pContent ) m_pManager->InitControls( m_pContent, this );

    NeedUpdate( true );
}

SIZE CContentControlUI::EstimateSizeOver( const SIZE& szAvailable )
{
    if ( m_pContent && m_pContent->IsVisible() ) {
        RECT rcPadding = m_pContent->GetPadding();
        SIZE szRemind = szAvailable;
        szRemind.cx -= rcPadding.left + rcPadding.right;
        szRemind.cy -= rcPadding.top + rcPadding.bottom;
        szRemind.cx = MAX( szRemind.cx, 0 );
        szRemind.cy = MAX( szRemind.cy, 0 );

        m_pContent->EstimateSize( szRemind );
        szRemind = m_pContent->GetDesiredSize();

        return CSize( szRemind.cx + rcPadding.left + rcPadding.right, \
                      szRemind.cy + rcPadding.top + rcPadding.bottom );
    }

    return CSize();
}
RECT CContentControlUI::SetPosOver( const RECT& rc )
{
    if ( m_pContent && m_pContent->IsVisible() ) {
        RECT rcPadding = m_pContent->GetPadding();
        RECT rcRemind = rc;
        rcRemind.left += rcPadding.left; rcRemind.right -= rcPadding.right;
        rcRemind.top += rcPadding.top; rcRemind.bottom -= rcPadding.bottom;
        rcRemind.right = MAX( rcRemind.left, rcRemind.right );
        rcRemind.bottom = MAX( rcRemind.top, rcRemind.bottom );

        int cx = m_pContent->GetFixedWidth();
        int cy = m_pContent->GetFixedHeight();
        SIZE sz = m_pContent->GetDesiredSize();

        //如果容器对齐不是stretch则优先容器
        int hAligenment = 0;
        int vAligenment = 0;
		//把sz.cx改成cx试试
        if ( cx >= rcRemind.right - rcRemind.left )
            hAligenment = ( m_pContent->GetHorizontalAlignment() == UIALIGNMENT_STRETCH ) ? UIALIGNMENT_LEFT_TOP :
                          m_pContent->GetHorizontalAlignment();
        else
            hAligenment = ( m_iHorizontalContentAlignment == UIALIGNMENT_STRETCH ) ? \
                          m_pContent->GetHorizontalAlignment() : m_iHorizontalContentAlignment;
        if ( cy >= rcRemind.bottom - rcRemind.top )
            vAligenment = ( m_pContent->GetVerticalAlignment() == UIALIGNMENT_STRETCH ) ? UIALIGNMENT_LEFT_TOP :
                          m_pContent->GetVerticalAlignment();
        else
            vAligenment = ( m_iVerticalContentAlignment == UIALIGNMENT_STRETCH ) ? \
                          m_pContent->GetVerticalAlignment() : m_iVerticalContentAlignment;

        int retX = 0;
        if ( hAligenment == UIALIGNMENT_STRETCH ) {
            retX = cx ? cx : ( rcRemind.right - rcRemind.left );
        }
        else {
            retX = sz.cx ? sz.cx : ( rcRemind.right - rcRemind.left );
        }
        retX = CLAMP( retX, m_pContent->GetMinWidth(), m_pContent->GetMaxWidth() );
        int retY = 0;
        if ( vAligenment == UIALIGNMENT_STRETCH ) {
            retY = cy ? cy : ( rcRemind.bottom - rcRemind.top );
        }
        else {
            retY = sz.cy ? sz.cy : ( rcRemind.bottom - rcRemind.top );
        }
        retY = CLAMP( retY, m_pContent->GetMinHeight(), m_pContent->GetMaxWidth() );

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

        m_pContent->SetPos( CRect( posX, posY, posX + retX, posY + retY ) );
    }
    return rc;
}

bool CContentControlUI::IsAutoDestroy() const
{
    return m_bAutoDestroy;
}
void CContentControlUI::SetAutoDestroy( bool bAuto )
{
    m_bAutoDestroy = bAuto;
}

void CContentControlUI::SetVisible( bool bVisible )
{
    if ( m_bVisible == bVisible ) return;

    if ( m_pContent )
        m_pContent->SetInternVisible( bVisible );

    CControlUI::SetVisible( bVisible );
}
void CContentControlUI::SetInternVisible( bool bVisible  )
{
    if ( m_bInternVisible == bVisible )return;

    if ( m_pContent )
        m_pContent->SetInternVisible( bVisible );

    CControlUI::SetInternVisible( bVisible );
}
void CContentControlUI::SetEnabled( bool bEnabled )
{
    if ( m_bEnabled == bEnabled )return;

    if ( m_pContent )
        m_pContent->SetInternEnabled( bEnabled );

    CControlUI::SetEnabled( bEnabled );
}
void CContentControlUI::SetInternEnabled( bool bEnabled )
{
    if ( m_bInternEnabled == bEnabled )return;

    if ( m_pContent )
        m_pContent->SetInternEnabled( bEnabled );

    CControlUI::SetInternEnabled( bEnabled );
}
void CContentControlUI::SetMouseEnabled( bool bEnabled )
{
    if ( m_bMouseEnabled == bEnabled )return;

    if ( m_pContent )
        m_pContent->SetInternMouseEnabled( bEnabled );

    CControlUI::SetMouseEnabled( bEnabled );
}
void CContentControlUI::SetInternMouseEnabled( bool bEnabled )
{
    if ( m_bInternMouseEnabled == bEnabled )return;

    if ( m_pContent )
        m_pContent->SetInternMouseEnabled( bEnabled );

    CControlUI::SetInternMouseEnabled( bEnabled );
}
void CContentControlUI::SetManager( CPaintManagerUI* pManager, CElementUI* pParent, bool bInit )
{
    if ( m_pContent )
        m_pContent->SetManager( pManager, this, bInit );
    CControlUI::SetManager( pManager, pParent, bInit );
}
CElementUI* CContentControlUI::FindControl( FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags )
{
    if ( ( uFlags & UIFIND_VISIBLE ) != 0 && !IsVisible() ) return NULL;
    if ( ( uFlags & UIFIND_ENABLED ) != 0 && !IsEnabled() ) return NULL;
    if ( ( uFlags & UIFIND_HITTEST ) != 0 && ( !m_bMouseEnabled || !::PtInRect( &m_rcItem, * reinterpret_cast<LPPOINT>( pData ) ) ) ) return NULL;
    if ( ( uFlags & UIFIND_CAN_FOCUS ) != 0 && !IsCanFocus() ) return NULL;

    CElementUI* pThisResult = CElementUI::FindControl( Proc, pData, uFlags );

    if ( ( uFlags & UIFIND_ME_FIRST ) != 0 && pThisResult )return pThisResult;

    CElementUI* pContentResult = NULL;
    if ( m_pContent )
        pContentResult = m_pContent->FindControl( Proc, pData, uFlags );
    if ( pContentResult )
        return pContentResult;

    return pThisResult;
}
void CContentControlUI::SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue )
{
    if ( _tcscmp( pstrName, _T( "text" ) ) == 0 ) {
        if ( _tcsstr( pstrValue, _T( "{html}" ) ) != NULL ) {
            CHtmlBlockUI* phtmlblock = new CHtmlBlockUI();
            phtmlblock->SetText( pstrValue + 6 );
            SetContent( phtmlblock );
        }
        else {
            CTextBlockUI* ptextblock = new CTextBlockUI();
            ptextblock->SetText( pstrValue );
            SetContent( ptextblock );
        }
    }
    else CControlUI::SetAttribute( pstrName, pstrValue );
}
void CContentControlUI::DoPaintOver( GRAPHorHDC& gorh )
{
    PaintBkColor( gorh );
    PaintBkImage( gorh );
    PaintStatusImage( gorh );
    PaintContent( gorh );
    PaintBorder( gorh );
}
void CContentControlUI::PaintBkColor( GRAPHorHDC& gorh )
{
    if ( !m_bNotUseDefSkin && m_pManager && !m_sName.IsEmpty() ) {
        if ( m_sName == _T( "tilebar" ) )
            return CDefaultSkinUI::DrawWindow( gorh, m_pManager->GetPaintWindow(), m_rcItem, 0, CDefaultSkinUI::PART_WINDOW_CAPTION );
        else if ( m_sName == _T( "dialog" ) )
            return CDefaultSkinUI::DrawWindow( gorh, m_pManager->GetPaintWindow(), m_rcItem, 0, CDefaultSkinUI::PART_WINDOW_DIALOG );
    }
    CControlUI::PaintBkColor( gorh );
}
void CContentControlUI::PaintContent( GRAPHorHDC& gorh )
{
    if ( m_pContent && m_pContent->IsVisible() ) {
        RECT rcPadding = m_pContent->GetPadding();
        RECT rcClip = {m_rcItem.left + m_rcInset.left + rcPadding.left, \
                       m_rcItem.top + m_rcInset.top + rcPadding.top, \
                       m_rcItem.right - m_rcInset.right - rcPadding.right, \
                       m_rcItem.bottom - m_rcInset.bottom - rcPadding.bottom
                      };
        if ( ::IsRectEmpty( &rcClip ) )
            return;
        CRgn oldRegion = gorh.IntersectClip( rcClip );

        m_pContent->DoPaint( gorh, m_rcPaint );

        gorh.SetClip( oldRegion );
    }
}
/////////////////////////////////////////////////////////////////////////////////////
//
//
IMPLEMENT_DYNCREATE( CLabelUI )
CLabelUI::CLabelUI()
{
    m_iHorizontalContentAlignment = m_iVerticalContentAlignment = UIALIGNMENT_LEFT_TOP;

    ::SetRect( &m_rcInset, 2, 2, 2, 2 );
}

LPCTSTR CLabelUI::GetClass() const
{
    return _T( "LabelUI" );
}

LPVOID CLabelUI::GetInterface( LPCTSTR pstrName )
{
    if ( _tcscmp( pstrName, _T( "Label" ) ) == 0 ) return static_cast<CLabelUI*>( this );
    return CContentControlUI::GetInterface( pstrName );
}
void CLabelUI::SetContent( CElementUI* content )
{
    CContentControlUI::SetContent( content );
    if ( content ) {
        CTextBlockUI* text = static_cast<CTextBlockUI*>( content->GetInterface( _T( "TextBlock" ) ) );
        if ( text )
            text->SetTextStyle( text->GetTextStyle()&~DT_NOPREFIX );
    }
}
/////////////////////////////////////////////////////////////////////////////////////
//
//
IMPLEMENT_DYNCREATE( CButtonUI )
CButtonUI::CButtonUI() : m_uButtonState( 0 ), m_bHandUse( false ), m_bIsWantReturn( false ), m_bIsWantSpace( false )
{
    m_iHorizontalContentAlignment = m_iVerticalContentAlignment = UIALIGNMENT_CENTER;
    ::SetRect( &m_rcInset, 4, 4, 4, 4 );
}

LPCTSTR CButtonUI::GetClass() const
{
    return _T( "ButtonUI" );
}

LPVOID CButtonUI::GetInterface( LPCTSTR pstrName )
{
    if ( _tcscmp( pstrName, _T( "Button" ) ) == 0 ) return static_cast<CButtonUI*>( this );
    return CContentControlUI::GetInterface( pstrName );
}

UINT CButtonUI::GetControlFlags() const
{
    return CContentControlUI::GetControlFlags() | ( IsEnabled() ? ( ( m_bHandUse ? UIFLAG_SETCURSOR : 0 ) | ( m_bIsWantReturn ? UIFLAG_WANTRETURN : 0 ) ) : 0 );
}
bool CButtonUI::Activate()
{
    if ( !CControlUI::Activate() ) return false;
    if ( m_pManager != NULL ) m_pManager->SendNotify( this, _T( "click" ) );
    return true;
}
void CButtonUI::ResetState()
{
    m_uButtonState = 0;
}
void CButtonUI::Event( TEventUI& event )
{
    if ( !IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND ) {
        if ( m_pParent != NULL ) m_pParent->Event( event );
        else CContentControlUI::Event( event );
        return;
    }
    //在Label基础上增加刷新
    if ( event.Type == UIEVENT_SETFOCUS ) {
        Invalidate();
    }
    if ( event.Type == UIEVENT_KILLFOCUS ) {
        Invalidate();
    }
    if ( m_bIsWantSpace && IsEnabled() ) {
        if ( event.Type == UIEVENT_KEYDOWN && event.chKey == VK_SPACE ) {
            m_uButtonState |= UISTATE_PUSHED;
            Invalidate();
            return;
        }
        else if ( event.Type == UIEVENT_KEYUP && event.chKey == VK_SPACE ) {
            Activate();
            m_uButtonState &= ~UISTATE_PUSHED;
            Invalidate();
            return;
        }
    }

    if ( event.Type == UIEVENT_BUTTONDOWN || event.Type == UIEVENT_DBLCLICK ) {
        if ( ::PtInRect( &m_rcItem, event.ptMouse ) && IsEnabled() ) {
            m_uButtonState |= UISTATE_PUSHED | UISTATE_CAPTURED;
            Invalidate();
        }
        return;
    }
    if ( event.Type == UIEVENT_MOUSEMOVE ) {
        if ( ( m_uButtonState & UISTATE_CAPTURED ) != 0 ) {
            if ( ::PtInRect( &m_rcItem, event.ptMouse ) ) m_uButtonState |= UISTATE_PUSHED;
            else m_uButtonState &= ~UISTATE_PUSHED;
            Invalidate();
        }
        return;
    }
    if ( event.Type == UIEVENT_BUTTONUP ) {
        if ( ( m_uButtonState & UISTATE_CAPTURED ) != 0 ) {
            if ( ::PtInRect( &m_rcItem, event.ptMouse ) ) Activate();
            m_uButtonState &= ~( UISTATE_PUSHED | UISTATE_CAPTURED );
            Invalidate();
        }
        return;
    }
    if ( event.Type == UIEVENT_MOUSEENTER ) {
        if ( IsEnabled() ) {
            m_uButtonState |= UISTATE_HOT;
            Invalidate();
        }
        return;
    }
    if ( event.Type == UIEVENT_MOUSELEAVE ) {
        if ( IsEnabled() ) {
            m_uButtonState &= ~UISTATE_HOT;
            Invalidate();
        }
        return;
    }
    if ( event.Type == UIEVENT_SETCURSOR ) {
        ::SetCursor( ::LoadCursor( NULL, MAKEINTRESOURCE( IDC_HAND ) ) );
        return;
    }
    CContentControlUI::Event( event );
}

LPCTSTR CButtonUI::GetNormalImage()
{
    return m_sNormalImage;
}

void CButtonUI::SetNormalImage( LPCTSTR pStrImage )
{
    if ( m_sNormalImage == pStrImage )return;

    m_sNormalImage = pStrImage;
    Invalidate();
}

LPCTSTR CButtonUI::GetHotImage()
{
    return m_sHotImage;
}

void CButtonUI::SetHotImage( LPCTSTR pStrImage )
{
    if ( m_sHotImage == pStrImage )return;

    m_sHotImage = pStrImage;
    Invalidate();
}

LPCTSTR CButtonUI::GetPushedImage()
{
    return m_sPushedImage;
}

void CButtonUI::SetPushedImage( LPCTSTR pStrImage )
{
    if ( m_sPushedImage == pStrImage )return;

    m_sPushedImage = pStrImage;
    Invalidate();
}

LPCTSTR CButtonUI::GetFocusedImage()
{
    return m_sFocusedImage;
}

void CButtonUI::SetFocusedImage( LPCTSTR pStrImage )
{
    if ( m_sFocusedImage == pStrImage )return;

    m_sFocusedImage = pStrImage;
    Invalidate();
}

LPCTSTR CButtonUI::GetDisabledImage()
{
    return m_sDisabledImage;
}

void CButtonUI::SetDisabledImage( LPCTSTR pStrImage )
{
    if ( m_sDisabledImage == pStrImage )return;

    m_sDisabledImage = pStrImage;
    Invalidate();
}

void CButtonUI::SetHandUse( bool handuse )
{
    m_bHandUse = handuse;
}
bool CButtonUI::IsHandUse() const
{
    return m_bHandUse;
}
void CButtonUI::SetWantReturn( bool wantreturn )
{
    m_bIsWantReturn = wantreturn;
}
bool CButtonUI::IsWantReturn() const
{
    return m_bIsWantReturn;
}
void CButtonUI::SetWantSpace( bool wantspace )
{
    m_bIsWantSpace = wantspace;
}
bool CButtonUI::IsWantSpace() const
{
    return m_bIsWantSpace;
}
void CButtonUI::SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue )
{
    if ( _tcscmp( pstrName, _T( "normalimage" ) ) == 0 ) SetNormalImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "hotimage" ) ) == 0 ) SetHotImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "pushedimage" ) ) == 0 ) SetPushedImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "focusedimage" ) ) == 0 ) SetFocusedImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "disabledimage" ) ) == 0 ) SetDisabledImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "handuse" ) ) == 0 ) SetHandUse( _tcscmp( pstrValue, _T( "true" ) ) == 0  );
    else if ( _tcscmp( pstrName, _T( "wantreturn" ) ) == 0 ) SetWantReturn( _tcscmp( pstrValue, _T( "true" ) ) == 0  );
    else if ( _tcscmp( pstrName, _T( "wantspace" ) ) == 0 ) SetWantSpace( _tcscmp( pstrValue, _T( "true" ) ) == 0  );
    else CContentControlUI::SetAttribute( pstrName, pstrValue );
}

void CButtonUI::PaintStatusImage( GRAPHorHDC& gorh )
{
    if ( IsFocused() ) m_uButtonState |= UISTATE_FOCUSED;
    else m_uButtonState &= ~ UISTATE_FOCUSED;
    if ( !IsEnabled() ) m_uButtonState |= UISTATE_DISABLED;
    else m_uButtonState &= ~ UISTATE_DISABLED;

    if ( ( m_uButtonState & UISTATE_DISABLED ) != 0 ) {
        if ( !m_sDisabledImage.IsEmpty() ) {
            if ( !DrawImage( gorh, ( LPCTSTR )m_sDisabledImage ) ) m_sDisabledImage.Empty();
            else return;
        }
    }
    else if ( ( m_uButtonState & UISTATE_PUSHED ) != 0 ) {
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

    if ( !m_sNormalImage.IsEmpty() ) {
        if ( !DrawImage( gorh, ( LPCTSTR )m_sNormalImage ) ) m_sNormalImage.Empty();
        else return;
    }

    if ( !m_bNotUseDefSkin )
        PaintDefault( gorh );
}

void CButtonUI::PaintDefault( GRAPHorHDC& gorh )
{
    if ( m_pManager ) {
        if ( !m_sName.IsEmpty() ) {
            if ( m_sName == _T( "mixbtn" ) )
                return CDefaultSkinUI::DrawWindow( gorh, m_pManager->GetPaintWindow(), m_rcItem, m_uButtonState, CDefaultSkinUI::PART_WINDOW_MINBUTTON );
            else if ( m_sName == _T( "restorebtn" ) )
                return CDefaultSkinUI::DrawWindow( gorh, m_pManager->GetPaintWindow(), m_rcItem, m_uButtonState, CDefaultSkinUI::PART_WINDOW_RESTOREBUTTON );
            else if ( m_sName == _T( "maxbtn" ) )
                return CDefaultSkinUI::DrawWindow( gorh, m_pManager->GetPaintWindow(), m_rcItem, m_uButtonState, CDefaultSkinUI::PART_WINDOW_MAXBUTTON );
            else if ( m_sName == _T( "closebtn" ) )
                return CDefaultSkinUI::DrawWindow( gorh, m_pManager->GetPaintWindow(), m_rcItem, m_uButtonState, CDefaultSkinUI::PART_WINDOW_CLOSEBUTTON );
        }
        CDefaultSkinUI::DrawButton( gorh, m_pManager->GetPaintWindow(), m_rcItem, m_uButtonState );
    }
}

/////////////////////////////////////////////////////////////////////////////////////
//
//
IMPLEMENT_DYNCREATE( COptionUI )
COptionUI::COptionUI() : m_bGroup( false ), m_bChecked( false )
{
    m_iHorizontalContentAlignment = m_iVerticalContentAlignment = UIALIGNMENT_LEFT_TOP;
    ::SetRect( &m_rcInset, 18, 4, 0, 4 );
}

LPCTSTR COptionUI::GetClass() const
{
    return _T( "OptionUI" );
}

LPVOID COptionUI::GetInterface( LPCTSTR pstrName )
{
    if ( _tcscmp( pstrName, _T( "Option" ) ) == 0 ) return static_cast<COptionUI*>( this );
    return CButtonUI::GetInterface( pstrName );
}

UINT COptionUI::GetControlFlags() const
{
    return CButtonUI::GetControlFlags() | ( ( m_bGroup && m_bChecked ) ? UIFLAG_TABSTOP : 0 ); //IsVisible() && IsEnabled() &&
}
bool COptionUI::IsGroup() const
{
    return m_bGroup;
}

void COptionUI::SetGroup( bool bGroup )
{
    if ( m_bGroup == bGroup )return;
    m_bGroup = bGroup;
    Invalidate();
    //   if ( m_bGroup && m_bSelected ) {
    //设组后清除状态,不可控最好去掉
    //         m_bSelected = false;
    //         Invalidate();
    //     }
}

bool COptionUI::IsChecked() const
{
    return m_bChecked;
}

void COptionUI::SetChecked( bool bSelected )
{
    if ( m_bChecked == bSelected ) return;
    m_bChecked = bSelected;
    if ( m_bChecked ) m_uButtonState |= UISTATE_CHECKED;
    else m_uButtonState &= ~UISTATE_CHECKED;

    if ( m_bGroup ) {
        if ( m_bChecked )  {
            if ( GetParent() ) {
                IContainerUI* pParent = ( IContainerUI* )( GetParent()->GetInterface( _T( "IContainer" ) ) );
                if ( pParent ) {
                    for ( int it = 0; it < pParent->GetCount(); ++it ) {
                        COptionUI* pControl = static_cast<COptionUI*>( pParent->GetItemAt( it )->GetInterface( _T( "Option" ) ) );
                        if ( pControl && pControl != this && pControl->IsGroup() && pControl->IsVisible() && pControl->IsEnabled() ) {
                            pControl->SetChecked( false );
                        }
                    }
                }
            }
            //放在这里，一个组只发一个消息
            if ( m_pManager != NULL ) m_pManager->SendNotify( this, _T( "selectchanged" ) );
        }
    }
    else {
        if ( m_pManager != NULL ) m_pManager->SendNotify( this, _T( "selectchanged" ) );
    }

    Invalidate();
}

bool COptionUI::Activate()
{
    if ( !CControlUI::Activate() ) return false;
    if ( m_bGroup ) SetChecked( true );
    else SetChecked( !m_bChecked );

    return true;
}

LPCTSTR COptionUI::GetSelectedImage()
{
    return m_sSelectedImage;
}

void COptionUI::SetSelectedImage( LPCTSTR pStrImage )
{
    if ( m_sSelectedImage == pStrImage )return;

    m_sSelectedImage = pStrImage;
    Invalidate();
}

LPCTSTR COptionUI::GetHotSelectedImage()
{
    return m_sHotSelectedImage;
}

void COptionUI::SetHotSelectedImage( LPCTSTR pStrImage )
{
    if ( m_sHotSelectedImage == pStrImage )return;

    m_sHotSelectedImage = pStrImage;
    Invalidate();
}

LPCTSTR COptionUI::GetPushedSelectedImage()
{
    return m_sPushedSelectedImage;
}

void COptionUI::SetPushedSelectedImage( LPCTSTR pStrImage )
{
    if ( m_sPushedSelectedImage == pStrImage )return;

    m_sPushedSelectedImage = pStrImage;
    Invalidate();
}

LPCTSTR COptionUI::GetFocusedSelectedImage()
{
    return m_sFocusedSelectedImage;
}

void COptionUI::SetFocusedSelectedImage( LPCTSTR pStrImage )
{
    if ( m_sFocusedSelectedImage == pStrImage )return;

    m_sFocusedSelectedImage = pStrImage;
    Invalidate();
}

LPCTSTR COptionUI::GetDisabledSelectedImage()
{
    return m_sDisabledSelectedImage;
}

void COptionUI::SetDisabledSelectedImage( LPCTSTR pStrImage )
{
    if ( m_sDisabledSelectedImage == pStrImage )return;

    m_sDisabledSelectedImage = pStrImage;
    Invalidate();
}

void COptionUI::SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue )
{
    if ( _tcscmp( pstrName, _T( "group" ) ) == 0 ) SetGroup( _tcscmp( pstrValue, _T( "true" ) ) == 0 );
    else if ( _tcscmp( pstrName, _T( "selected" ) ) == 0 ) SetChecked( _tcscmp( pstrValue, _T( "true" ) ) == 0 );
    else if ( _tcscmp( pstrName, _T( "selectedimage" ) ) == 0 ) SetSelectedImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "hotselectedimage" ) ) == 0 ) SetHotSelectedImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "pushedselectedimage" ) ) == 0 ) SetPushedSelectedImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "focusedselectedimage" ) ) == 0 ) SetFocusedSelectedImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "disabledselectedimage" ) ) == 0 ) SetDisabledSelectedImage( pstrValue );
    else CButtonUI::SetAttribute( pstrName, pstrValue );
}

void COptionUI::PaintStatusImage( GRAPHorHDC& gorh )
{
    if ( IsFocused() ) m_uButtonState |= UISTATE_FOCUSED;
    else m_uButtonState &= ~ UISTATE_FOCUSED;
    if ( !IsEnabled() ) m_uButtonState |= UISTATE_DISABLED;
    else m_uButtonState &= ~ UISTATE_DISABLED;

    if ( ( m_uButtonState & UISTATE_CHECKED ) != 0 && ( m_uButtonState & UISTATE_DISABLED ) != 0 ) {
        if ( !m_sDisabledSelectedImage.IsEmpty() ) {
            if ( !DrawImage( gorh, ( LPCTSTR )m_sDisabledSelectedImage ) ) m_sDisabledSelectedImage.Empty();
            else return;
        }
    }
    else if ( ( m_uButtonState & UISTATE_CHECKED ) != 0 && ( m_uButtonState & UISTATE_PUSHED ) != 0 ) {
        if ( !m_sPushedSelectedImage.IsEmpty() ) {
            if ( !DrawImage( gorh, ( LPCTSTR )m_sPushedSelectedImage ) ) m_sPushedSelectedImage.Empty();
            else return;
        }
    }
    else if ( ( m_uButtonState & UISTATE_CHECKED ) != 0 && ( m_uButtonState & UISTATE_HOT ) != 0 ) {
        if ( !m_sHotSelectedImage.IsEmpty() ) {
            if ( !DrawImage( gorh, ( LPCTSTR )m_sHotSelectedImage ) ) m_sHotSelectedImage.Empty();
            else return;
        }
    }
    else if ( ( m_uButtonState & UISTATE_CHECKED ) != 0  && ( m_uButtonState & UISTATE_FOCUSED ) != 0 ) {
        if ( !m_sFocusedSelectedImage.IsEmpty() ) {
            if ( !DrawImage( gorh, ( LPCTSTR )m_sFocusedSelectedImage ) ) m_sFocusedSelectedImage.Empty();
            else return;
        }
    }
    else if ( ( m_uButtonState & UISTATE_CHECKED ) != 0 ) {
        if ( !m_sSelectedImage.IsEmpty() ) {
            if ( !DrawImage( gorh, ( LPCTSTR )m_sSelectedImage ) ) m_sSelectedImage.Empty();
            else return;
        }
    }

    CButtonUI::PaintStatusImage( gorh );
}

void COptionUI::PaintDefault( GRAPHorHDC& gorh )
{
    if ( m_pManager )
        CDefaultSkinUI::DrawOption( gorh, m_pManager->GetPaintWindow(), m_rcItem, m_uButtonState, m_bGroup );
}

/////////////////////////////////////////////////////////////////////////////////////
//
//
IMPLEMENT_DYNCREATE( CProgressUI )
CProgressUI::CProgressUI() : m_bHorizontal( true ), m_nMin( 0 ), m_nMax( 100 ), m_nValue( 0 )
{

}

LPCTSTR CProgressUI::GetClass() const
{
    return _T( "ProgressUI" );
}

LPVOID CProgressUI::GetInterface( LPCTSTR pstrName )
{
    if ( _tcscmp( pstrName, _T( "Progress" ) ) == 0 ) return static_cast<CProgressUI*>( this );
    return CContentControlUI::GetInterface( pstrName );
}

bool CProgressUI::IsHorizontal()
{
    return m_bHorizontal;
}

void CProgressUI::SetHorizontal( bool bHorizontal )
{
    if ( m_bHorizontal == bHorizontal ) return;

    m_bHorizontal = bHorizontal;
    Invalidate();
}

int CProgressUI::GetMinValue() const
{
    return m_nMin;
}

void CProgressUI::SetMinValue( int nMin )
{
    if ( m_nMin == nMin )return;
    m_nMin = nMin;
    Invalidate();
}

int CProgressUI::GetMaxValue() const
{
    return m_nMax;
}

void CProgressUI::SetMaxValue( int nMax )
{
    if ( m_nMax == nMax )return;
    m_nMax = nMax;
    Invalidate();
}

int CProgressUI::GetValue() const
{
    return m_nValue;
}

void CProgressUI::SetValue( int nValue )
{
    if ( m_nValue == nValue )return;
    m_nValue = nValue;
    Invalidate();
}

LPCTSTR CProgressUI::GetFgImage() const
{
    return m_sFgImage;
}

void CProgressUI::SetFgImage( LPCTSTR pStrImage )
{
    if ( m_sFgImage == pStrImage ) return;

    m_sFgImage = pStrImage;
    Invalidate();
}

void CProgressUI::SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue )
{
    if ( _tcscmp( pstrName, _T( "fgimage" ) ) == 0 ) SetFgImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "hor" ) ) == 0 ) SetHorizontal( _tcscmp( pstrValue, _T( "true" ) ) == 0 );
    else if ( _tcscmp( pstrName, _T( "min" ) ) == 0 ) SetMinValue( _ttoi( pstrValue ) );
    else if ( _tcscmp( pstrName, _T( "max" ) ) == 0 ) SetMaxValue( _ttoi( pstrValue ) );
    else if ( _tcscmp( pstrName, _T( "value" ) ) == 0 ) SetValue( _ttoi( pstrValue ) );
    else CContentControlUI::SetAttribute( pstrName, pstrValue );
}

void CProgressUI::PaintStatusImage( GRAPHorHDC& gorh )
{
    if ( m_nMax <= m_nMin ) m_nMax = m_nMin + 1;
    if ( m_nValue > m_nMax ) m_nValue = m_nMax;
    if ( m_nValue < m_nMin ) m_nValue = m_nMin;

    RECT rc = {0};
    if ( m_bHorizontal ) {
        //right是进度的cx
        rc.right = ( m_rcItem.right - m_rcItem.left ) * ( m_nValue - m_nMin )  / ( m_nMax - m_nMin );
        //bottom是cy
        rc.bottom = m_rcItem.bottom - m_rcItem.top;
    }
    else {
        //top是空进度的cy
        rc.top = ( m_rcItem.bottom - m_rcItem.top ) * ( m_nMax - m_nValue ) / ( m_nMax - m_nMin );
        //cx
        rc.right = m_rcItem.right - m_rcItem.left;
        //全体的cy
        rc.bottom = m_rcItem.bottom - m_rcItem.top;
    }

    if ( !m_sFgImage.IsEmpty() ) {
        //m_sFgImageModify.Empty();
        m_sFgImageModify.FormatTinyBuf( _T( "dest='%d,%d,%d,%d'" ), rc.left, rc.top, rc.right, rc.bottom );

        if ( !DrawImage( gorh, ( LPCTSTR )m_sFgImage, ( LPCTSTR )m_sFgImageModify ) ) m_sFgImage.Empty();
        else return;
    }

    if ( !m_bNotUseDefSkin && m_pManager )
        CDefaultSkinUI::DrawProgress( gorh, m_pManager->GetPaintWindow(), m_rcItem, rc, !m_bHorizontal );
}

/////////////////////////////////////////////////////////////////////////////////////
//
//
//这个窗口伴随焦点而产生，失去焦点则关闭
//记住Manager判定要不不产生
class CEditWnd : public CWindowWnd
{
public:
    CEditWnd(): m_pOwner( NULL ), m_hBrush( NULL ), m_bkBmp( NULL ) {}
    ~CEditWnd() {
        if ( m_hBrush )
            ::DeleteObject( m_hBrush );
        if ( m_bkBmp )
            ::DeleteObject( m_bkBmp );
    }
    void Init( CEditUI* pOwner ) {
        CRect rcPos = pOwner->GetPos();
        RECT rcInset = pOwner->GetInset();
        rcPos.left += rcInset.left;
        rcPos.top += rcInset.top;
        rcPos.right -= rcInset.right;
        rcPos.bottom -= rcInset.bottom;
        rcPos.right = MAX( rcPos.left, rcPos.right );
        rcPos.bottom = MAX( rcPos.top, rcPos.bottom );

        UINT uStyle = WS_CHILD | ES_AUTOHSCROLL;
        if ( pOwner->IsPasswordMode() ) uStyle |= ES_PASSWORD;
        if ( pOwner->GetHorizontalContentAlignment() == UIALIGNMENT_CENTER )
            uStyle |= ES_CENTER;
        else if ( pOwner->GetHorizontalContentAlignment() == UIALIGNMENT_RIGHT_BOTTOM )
            uStyle |= ES_RIGHT;

        Create( pOwner->GetManager()->GetPaintWindow(), NULL, uStyle, 0, rcPos );

        Edit_Enable( m_hWnd, pOwner->IsEnabled() == true );
        Edit_SetText( m_hWnd, pOwner->GetText() );
        Edit_LimitText( m_hWnd, pOwner->GetMaxChar() );
        Edit_SetReadOnly( m_hWnd, pOwner->IsReadOnly() == true );
        if ( pOwner->IsPasswordMode() ) Edit_SetPasswordChar( m_hWnd, pOwner->GetPasswordChar() );

        SetWindowFont( m_hWnd, pOwner->GetManager()->GetFont( pOwner->GetFont() ), TRUE );

        Edit_SetModify( m_hWnd, FALSE );
        SendMessage( EM_SETMARGINS, EC_LEFTMARGIN | EC_RIGHTMARGIN, MAKELPARAM( 0, 0 ) );

        ::ShowWindow( m_hWnd, SW_SHOWNOACTIVATE );
        ::SetFocus( m_hWnd );

        Edit_SetSel( m_hWnd, 0, -1 );

        m_pOwner = pOwner;
    }
    void PrepareBackground( GRAPHorHDC& gorh ) {
        bool bModesave = gorh.SetHDCmode();

        CRect rcPos = m_pOwner->GetPos();
        RECT rcInset = m_pOwner->GetInset();
        rcPos.left += rcInset.left;
        rcPos.top += rcInset.top;
        rcPos.right -= rcInset.right;
        rcPos.bottom -= rcInset.bottom;
        rcPos.right = MAX( rcPos.left, rcPos.right );
        rcPos.bottom = MAX( rcPos.top, rcPos.bottom );

        if ( m_hBrush )
            ::DeleteObject( m_hBrush );
        if ( m_bkBmp )
            ::DeleteObject( m_bkBmp );

        HDC memdc =::CreateCompatibleDC( gorh );
        ASSERT( memdc );
        m_bkBmp =::CreateCompatibleBitmap( gorh, rcPos.right - rcPos.left, rcPos.bottom - rcPos.top );
        ASSERT( m_bkBmp );
        ::SelectObject( memdc, m_bkBmp );
        ::BitBlt( memdc, 0, 0, rcPos.right - rcPos.left, rcPos.bottom - rcPos.top, gorh, rcPos.left, rcPos.top, SRCCOPY );

        ::DeleteDC( memdc );
        m_hBrush =::CreatePatternBrush( m_bkBmp );
        ASSERT( m_hBrush );

        gorh.Setmode( bModesave );
    }

    LPCTSTR GetWindowClassName() const {
        return _T( "EditWnd" );
    }
    LPCTSTR GetSuperClassName() const {
        return WC_EDIT;
    }
    void OnFinalMessage( HWND hWnd ) {
        // Clear reference and die
        m_pOwner->m_pWindow = NULL;
        delete this;
    }

    LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam ) {
        LRESULT lRes = 0;
        BOOL bHandled = TRUE;
        if ( uMsg == WM_KILLFOCUS ) lRes = OnKillFocus( uMsg, wParam, lParam, bHandled );
        else if ( uMsg == OCM_COMMAND && GET_WM_COMMAND_CMD( wParam, lParam ) == EN_CHANGE ) lRes = OnEditChanged( uMsg, wParam, lParam, bHandled );
        else if ( uMsg == OCM_CTLCOLOREDIT ) lRes = OnCtlColor ( uMsg, wParam, lParam, bHandled );
        else bHandled = FALSE;
        if ( !bHandled ) return CWindowWnd::HandleMessage( uMsg, wParam, lParam );
        return lRes;
    }
    LRESULT OnKillFocus( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled ) {
        //LRESULT lRes = ::DefWindowProc( m_hWnd, uMsg, wParam, lParam );
        LRESULT lRes = CWindowWnd::HandleMessage( uMsg, wParam, lParam );
        PostMessage( WM_CLOSE );
        if ( m_pOwner && m_pOwner->m_pManager && wParam == NULL )
            ::PostMessage( m_pOwner->m_pManager->GetPaintWindow(), WM_KILLFOCUS, NULL, NULL );
        return lRes;
    }
    LRESULT OnEditChanged( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled ) {
        if ( m_pOwner == NULL ) return 0;
        // Copy text back
        int cchLen = ::GetWindowTextLength( m_hWnd ) + 1;
        if ( cchLen == 1 )return 0;
        LPTSTR pstr = static_cast<LPTSTR>( _alloca( cchLen * sizeof( TCHAR ) ) );
        ASSERT( pstr );
        //if ( pstr == NULL ) return 0;
        ::GetWindowText( m_hWnd, pstr, cchLen );
        m_pOwner->SetText( pstr );
        return 0;
    }

    LRESULT OnCtlColor( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled ) {
        HDC hdc = ( HDC )wParam;
        if ( m_pOwner == NULL || m_pOwner->m_pManager == NULL || m_hBrush == NULL ) return CWindowWnd::HandleMessage( uMsg, wParam, lParam );

        if ( m_pOwner->IsEnabled() ) {
            if ( m_pOwner->GetTextColor() == 0 )
                ::SetTextColor( hdc, m_pOwner->m_pManager->GetDefaultFontColor() );
            else
                ::SetTextColor( hdc, m_pOwner->GetTextColor() );
        }
        else {
            if ( m_pOwner->GetDisabledTextColor() == 0 )
                ::SetTextColor( hdc, m_pOwner->m_pManager->GetDefaultDisabledColor() );
            else
                ::SetTextColor( hdc, m_pOwner->GetDisabledTextColor() );
        }

        ::SetBkMode( hdc, TRANSPARENT );

        return ( LPARAM )m_hBrush;
    }
protected:
    CEditUI* m_pOwner;
    HBRUSH m_hBrush;
    HBITMAP m_bkBmp;
};

/////////////////////////////////////////////////////////////////////////////////////
//
//
IMPLEMENT_DYNCREATE( CEditUI )
CEditUI::CEditUI() : m_pWindow( NULL ), m_uMaxChar( 255 ), m_bReadOnly( false ),
    m_bPasswordMode( false ), m_cPasswordChar( _T( '*' ) ), m_uButtonState( 0 )
{
    m_iHorizontalContentAlignment = m_iVerticalContentAlignment = UIALIGNMENT_LEFT_TOP;

    ::SetRect( &m_rcInset, 4, 4, 4, 4 );
}

LPCTSTR CEditUI::GetClass() const
{
    return _T( "EditUI" );
}

LPVOID CEditUI::GetInterface( LPCTSTR pstrName )
{
    if ( _tcscmp( pstrName, _T( "Edit" ) ) == 0 ) return static_cast<CEditUI*>( this );
    return CControlUI::GetInterface( pstrName );
}

UINT CEditUI::GetControlFlags() const
{
    //if ( !IsEnabled() ) return CControlUI::GetControlFlags();

    return ( IsEnabled() ? UIFLAG_SETCURSOR : 0 ) | UIFLAG_TABSTOP;
}

void CEditUI::Event( TEventUI& event )
{
    if ( !IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND ) {
        if ( m_pParent != NULL ) m_pParent->Event( event );
        else CControlUI::Event( event );
        return;
    }

    if ( event.Type == UIEVENT_SETCURSOR ) {
        ::SetCursor( ::LoadCursor( NULL, MAKEINTRESOURCE( IDC_IBEAM ) ) );
        return;
    }

    if ( event.Type == UIEVENT_WINDOWSIZE ) {
        if ( m_pWindow != NULL ) m_pManager->SetFocus( NULL );
    }
    //禁止滚轮
    if ( event.Type == UIEVENT_SCROLLWHEEL ) {
        //if ( m_pWindow != NULL ) m_pManager->SetFocus( NULL );
        return;
    }
    if ( event.Type == UIEVENT_SETFOCUS  ) {//&& IsEnabled()
        if ( m_pWindow && m_pManager ) return;
        m_pWindow = new CEditWnd();
        ASSERT( m_pWindow );
        m_pWindow->Init( this );
        Invalidate();
    }
    if ( event.Type == UIEVENT_KILLFOCUS  ) {//&& IsEnabled()
        if ( m_pWindow )
            ::SendMessage( m_pWindow->GetHWND(), WM_CLOSE, NULL, NULL );
        Invalidate();
    }
    if ( event.Type == UIEVENT_BUTTONDOWN || event.Type == UIEVENT_DBLCLICK ) {
        if ( IsEnabled() && m_pManager ) {
            if ( IsFocused() ) {
                if ( m_pWindow == NULL ) {
                    m_pWindow = new CEditWnd();
                    ASSERT( m_pWindow );
                    m_pWindow->Init( this );
                }
                //                 else {
                //                     POINT pt = event.ptMouse;
                //                     pt.x -= m_rcItem.left + m_rcTextPadding.left;
                //                     pt.y -= m_rcItem.top + m_rcTextPadding.top;
                //                     ::SendMessage( *m_pWindow, WM_LBUTTONDOWN, event.wParam, MAKELPARAM( pt.x, pt.y ) );
                //                 }
            }
            m_pManager->ReleaseCapture();
        }
        return;
    }

    if ( event.Type == UIEVENT_BUTTONUP ) {
        return;
    }
    if ( event.Type == UIEVENT_MOUSEMOVE ) {
        return;
    }
    if ( event.Type == UIEVENT_MOUSEENTER ) {
        if ( IsEnabled() ) {
            m_uButtonState |= UISTATE_HOT;
            Invalidate();
        }
        return;
    }
    if ( event.Type == UIEVENT_MOUSELEAVE ) {
        if ( IsEnabled() ) {
            m_uButtonState &= ~UISTATE_HOT;
            Invalidate();
        }
        return;
    }
    CControlUI::Event( event );
}

void CEditUI::ResetState()
{
    m_uButtonState = 0;
}

void CEditUI::SetTextColor( DWORD color )
{
    m_cTextBlock.SetTextColor( color );
}
DWORD CEditUI::GetTextColor() const
{
    return m_cTextBlock.GetTextColor();
}
void CEditUI::SetDisabledTextColor( DWORD color )
{
    m_cTextBlock.SetDisabledTextColor( color );
}
DWORD CEditUI::GetDisabledTextColor() const
{
    return m_cTextBlock.GetDisabledTextColor();
}
void CEditUI::SetFont( int font )
{
    m_cTextBlock.SetFont( font );
}
int CEditUI::GetFont() const
{
    return m_cTextBlock.GetFont();
}
LPCTSTR CEditUI::GetText() const
{
    return m_szText;
}
void CEditUI::SetText( LPCTSTR pstrText )
{
    m_szText = pstrText;

    if ( m_pManager != NULL ) m_pManager->SendNotify( this, _T( "textchanged" ) );
    Invalidate();
}
UINT CEditUI::GetMaxChar()
{
    return m_uMaxChar;
}

void CEditUI::SetMaxChar( UINT uMax )
{
    if ( m_uMaxChar == uMax )return;

    m_uMaxChar = uMax;
    if ( m_pWindow != NULL ) Edit_LimitText( *m_pWindow, m_uMaxChar );
}


bool CEditUI::IsReadOnly() const
{
    return m_bReadOnly;
}
void CEditUI::SetReadOnly( bool bReadOnly )
{
    if ( m_bReadOnly == bReadOnly ) return;

    m_bReadOnly = bReadOnly;
    if ( m_pWindow != NULL ) Edit_SetReadOnly( *m_pWindow, m_bReadOnly );
    Invalidate();
}



bool CEditUI::IsPasswordMode() const
{
    return m_bPasswordMode;
}
void CEditUI::SetPasswordMode( bool bPasswordMode )
{
    if ( m_bPasswordMode == bPasswordMode ) return;
    m_bPasswordMode = bPasswordMode;

    Invalidate();
}

TCHAR CEditUI::GetPasswordChar() const
{
    return m_cPasswordChar;
}

void CEditUI::SetPasswordChar( TCHAR cPasswordChar )
{
    if ( m_cPasswordChar == cPasswordChar ) return;
    m_cPasswordChar = cPasswordChar;
    if ( m_pWindow != NULL ) Edit_SetPasswordChar( *m_pWindow, m_cPasswordChar );
    Invalidate();
}



LPCTSTR CEditUI::GetNormalImage()
{
    return m_sNormalImage;
}

void CEditUI::SetNormalImage( LPCTSTR pStrImage )
{
    if ( m_sNormalImage == pStrImage )return;

    m_sNormalImage = pStrImage;
    Invalidate();
}

LPCTSTR CEditUI::GetHotImage()
{
    return m_sHotImage;
}

void CEditUI::SetHotImage( LPCTSTR pStrImage )
{
    if ( m_sHotImage == pStrImage )return;

    m_sHotImage = pStrImage;
    Invalidate();
}

LPCTSTR CEditUI::GetFocusedImage()
{
    return m_sFocusedImage;
}

void CEditUI::SetFocusedImage( LPCTSTR pStrImage )
{
    if ( m_sFocusedImage == pStrImage )return;

    m_sFocusedImage = pStrImage;
    Invalidate();
}

LPCTSTR CEditUI::GetDisabledImage()
{
    return m_sDisabledImage;
}

void CEditUI::SetDisabledImage( LPCTSTR pStrImage )
{
    if ( m_sDisabledImage == pStrImage )return;

    m_sDisabledImage = pStrImage;
    Invalidate();
}

SIZE CEditUI::EstimateSizeOver( const SIZE& szAvailable )
{
    CStdString sText = m_szText;
    if ( m_bPasswordMode ) {
        sText.Empty();
        LPCTSTR p = m_szText.GetData();
        while ( *p != _T( '\0' ) ) {
            sText += m_cPasswordChar;
            p = ::CharNext( p );
        }
    }
    m_cTextBlock.SetText( sText );

    m_cTextBlock.EstimateSize( szAvailable );

    //return CSize(0,m_cTextBlock.GetDesiredSize().cy);
    return m_cTextBlock.GetDesiredSize();
}
RECT CEditUI::SetPosOver( const RECT& rc )
{
    if ( m_szText.IsEmpty() )return rc;

    SIZE sz = m_cTextBlock.GetDesiredSize();

    int posY = 0;
    if ( m_iVerticalContentAlignment == UIALIGNMENT_RIGHT_BOTTOM )
        posY = rc.bottom - sz.cy;
    else if ( m_iVerticalContentAlignment == UIALIGNMENT_CENTER )
        posY = ( rc.top + rc.bottom - sz.cy ) / 2;
    else
        posY = rc.top;

    m_cTextBlock.SetPos( CRect( rc.left, posY, rc.left + sz.cx, posY + sz.cy ) );
    return rc;
}
void CEditUI::SetVisible( bool bVisible )
{
    if ( m_bVisible == bVisible ) return;

    m_cTextBlock.SetInternVisible( bVisible );

    CControlUI::SetVisible( bVisible );
}
void CEditUI::SetInternVisible( bool bVisible  )
{
    if ( m_bInternVisible == bVisible )return;

    m_cTextBlock.SetInternVisible( bVisible );

    CControlUI::SetInternVisible( bVisible );
}
void CEditUI::SetEnabled( bool bEnabled )
{
    if ( m_bEnabled == bEnabled )return;

    m_cTextBlock.SetInternEnabled( bEnabled );

    CControlUI::SetEnabled( bEnabled );
}
void CEditUI::SetInternEnabled( bool bEnabled )
{
    if ( m_bInternEnabled == bEnabled )return;

    m_cTextBlock.SetInternEnabled( bEnabled );

    CControlUI::SetInternEnabled( bEnabled );
}
void CEditUI::SetManager( CPaintManagerUI* pManager, CElementUI* pParent, bool bInit  )
{
    m_cTextBlock.SetManager( pManager, this, bInit );

    CControlUI::SetManager( pManager, pParent, bInit );
}

void CEditUI::SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue )
{
    if ( _tcscmp( pstrName, _T( "text" ) ) == 0 ) SetText( pstrValue );
    else if ( _tcscmp( pstrName, _T( "font" ) ) == 0 ) SetFont( _ttoi( pstrValue ) );
    else if ( _tcscmp( pstrName, _T( "textcolor" ) ) == 0 ) {
        if ( *pstrValue == _T( '#' ) ) pstrValue = ::CharNext( pstrValue );
        SetTextColor( _tcstoul( pstrValue, NULL, 16 ) );
    }
    else if ( _tcscmp( pstrName, _T( "disabledtextcolor" ) ) == 0 ) {
        if ( *pstrValue == _T( '#' ) ) pstrValue = ::CharNext( pstrValue );
        SetDisabledTextColor( _tcstoul( pstrValue, NULL, 16 ) );
    }
    else if ( _tcscmp( pstrName, _T( "maxchar" ) ) == 0 ) SetMaxChar( _tcstol( pstrValue, NULL, 10 ) );
    else if ( _tcscmp( pstrName, _T( "readonly" ) ) == 0 ) SetReadOnly( _tcscmp( pstrValue, _T( "true" ) ) == 0 );
    else if ( _tcscmp( pstrName, _T( "password" ) ) == 0 ) SetPasswordMode( _tcscmp( pstrValue, _T( "true" ) ) == 0 );
    else if ( _tcscmp( pstrName, _T( "passwordchar" ) ) == 0 ) SetPasswordChar( pstrValue[0]  );
    else if ( _tcscmp( pstrName, _T( "normalimage" ) ) == 0 ) SetNormalImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "hotimage" ) ) == 0 ) SetHotImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "focusedimage" ) ) == 0 ) SetFocusedImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "disabledimage" ) ) == 0 ) SetDisabledImage( pstrValue );
    else CControlUI::SetAttribute( pstrName, pstrValue );
}
void CEditUI::DoPaintOver( GRAPHorHDC& gorh )
{
    PaintBkColor( gorh );
    PaintBkImage( gorh );
    PaintStatusImage( gorh );
    PaintText( gorh );
    PaintBorder( gorh );
}
void CEditUI::PaintStatusImage( GRAPHorHDC& gorh )
{
    if ( IsFocused() ) m_uButtonState |= UISTATE_FOCUSED;
    else m_uButtonState &= ~ UISTATE_FOCUSED;
    if ( !IsEnabled() ) m_uButtonState |= UISTATE_DISABLED;
    else m_uButtonState &= ~ UISTATE_DISABLED;
    if ( IsReadOnly() )m_uButtonState |= UISTATE_READONLY;
    else m_uButtonState &= ~ UISTATE_READONLY;

    bool bFlag = false;
    if ( ( m_uButtonState & UISTATE_DISABLED ) != 0 ) {
        if ( !m_sDisabledImage.IsEmpty() ) {
            if ( !DrawImage( gorh, ( LPCTSTR )m_sDisabledImage ) ) m_sDisabledImage.Empty();
            else bFlag = true;
            //else return;
        }
    }
    else if ( ( m_uButtonState & UISTATE_FOCUSED ) != 0 ) {
        if ( !m_sFocusedImage.IsEmpty() ) {
            if ( !DrawImage( gorh, ( LPCTSTR )m_sFocusedImage ) ) m_sFocusedImage.Empty();
            else bFlag = true;
            //else return;
        }
    }
    else if ( ( m_uButtonState & UISTATE_HOT ) != 0 ) {
        if ( !m_sHotImage.IsEmpty() ) {
            if ( !DrawImage( gorh, ( LPCTSTR )m_sHotImage ) ) m_sHotImage.Empty();
            else bFlag = true;
            //else return;
        }
    }

    if ( !bFlag && !m_sNormalImage.IsEmpty() ) {
        if ( !DrawImage( gorh, ( LPCTSTR )m_sNormalImage ) ) m_sNormalImage.Empty();
    }
    if ( !bFlag && m_sNormalImage.IsEmpty() && !m_bNotUseDefSkin && m_pManager )
        CDefaultSkinUI::DrawEdit( gorh, m_pManager->GetPaintWindow(), m_rcItem, m_uButtonState );

    if ( m_pWindow )
        m_pWindow->PrepareBackground( gorh );
}

void CEditUI::PaintText( GRAPHorHDC& gorh )
{
    if ( m_szText.IsEmpty() ) return;

    CStdString sText = m_szText;
    if ( m_bPasswordMode ) {
        sText.Empty();
        LPCTSTR p = m_szText.GetData();
        while ( *p != _T( '\0' ) ) {
            sText += m_cPasswordChar;
            p = ::CharNext( p );
        }
    }
    m_cTextBlock.SetText( sText );

    RECT rcClip = {m_rcItem.left + m_rcInset.left, \
                   m_rcItem.top + m_rcInset.top, \
                   m_rcItem.right - m_rcInset.right, \
                   m_rcItem.bottom - m_rcInset.bottom
                  };
    if ( ::IsRectEmpty( &rcClip ) )
        return;
    CRgn oldRegion = gorh.IntersectClip( rcClip );

    m_cTextBlock.DoPaint( gorh, m_rcPaint );

    gorh.SetClip( oldRegion );
}

/////////////////////////////////////////////////////////////////////////////////////
//
//
IMPLEMENT_DYNCREATE( CScrollbarUI )
CScrollbarUI::CScrollbarUI() : m_bHorizontal( false ), m_nRange( 100 ), m_nScrollPos( 0 ), m_nLineSize( 8 ),
    m_pOwner( NULL ), m_nLastScrollPos( 0 ), m_nLastScrollOffset( 0 ), m_nScrollRepeatDelay( 0 ), m_uButton1State( 0 ), \
    m_uButton2State( 0 ), m_uThumbState( 0 ), m_ubk1State( 0 ), m_ubk2State( 0 )
{

    m_cxyFixed.cx = DEFAULT_SCROLLBAR_SIZE;
    ptLastMouse.x = ptLastMouse.y = 0;
    ::ZeroMemory( &m_rcThumb, sizeof( m_rcThumb ) );
    ::ZeroMemory( &m_rcButton1, sizeof( m_rcButton1 ) );
    ::ZeroMemory( &m_rcButton2, sizeof( m_rcButton2 ) );
    ::ZeroMemory( &m_rcbk1, sizeof( m_rcbk1 ) );
    ::ZeroMemory( &m_rcbk2, sizeof( m_rcbk2 ) );
}

LPCTSTR CScrollbarUI::GetClass() const
{
    return _T( "ScrollbarUI" );
}

LPVOID CScrollbarUI::GetInterface( LPCTSTR pstrName )
{
    if ( _tcscmp( pstrName, _T( "Scrollbar" ) ) == 0 ) return static_cast<CScrollbarUI*>( this );
    return CControlUI::GetInterface( pstrName );
}

CScrollViewerUI* CScrollbarUI::GetOwner() const
{
    return m_pOwner;
}

void CScrollbarUI::SetOwner( CScrollViewerUI* pOwner )
{
    m_pOwner = pOwner;
}

void CScrollbarUI::ResetState( )
{
    //普通状态
    m_uButton1State = 0;
    m_uButton2State = 0;
    m_uThumbState = 0;
    m_ubk1State = 0;
    m_ubk2State = 0;
}

bool CScrollbarUI::IsHorizontal() const
{
    return m_bHorizontal;
}

void CScrollbarUI::SetHorizontal( bool bHorizontal )
{
    if ( m_bHorizontal == bHorizontal ) return;

    m_bHorizontal = bHorizontal;
    int t = m_cxyFixed.cx; m_cxyFixed.cx = m_cxyFixed.cy; m_cxyFixed.cy = t;

    NeedUpdate( true );
}

int CScrollbarUI::GetScrollRange() const
{
    return m_nRange;
}

void CScrollbarUI::SetScrollRange( int nRange )
{
    if ( m_nRange == nRange ) return;

    m_nRange = nRange;
    if ( m_nRange < 0 ) m_nRange = 0;
    if ( m_nScrollPos > m_nRange ) m_nScrollPos = m_nRange;
    //SetPos( m_rcItem );
	NeedUpdate( true );
}

int CScrollbarUI::GetScrollPos() const
{
    return m_nScrollPos;
}

void CScrollbarUI::SetScrollPos( int nPos )
{
    if ( m_nScrollPos == nPos ) return;

    m_nScrollPos = nPos;
    if ( m_nScrollPos < 0 ) m_nScrollPos = 0;
    if ( m_nScrollPos > m_nRange ) m_nScrollPos = m_nRange;
    //SetPos( m_rcItem );
	NeedUpdate( true );
}

int CScrollbarUI::GetLineSize() const
{
    return m_nLineSize;
}

void CScrollbarUI::SetLineSize( int nSize )
{
    m_nLineSize = nSize;
}

LPCTSTR CScrollbarUI::GetButton1NormalImage() const
{
    return m_sButton1NormalImage;
}

void CScrollbarUI::SetButton1NormalImage( LPCTSTR pStrImage )
{
    if ( m_sButton1NormalImage == pStrImage )return;
    m_sButton1NormalImage = pStrImage;
    Invalidate();
}

LPCTSTR CScrollbarUI::GetButton1HotImage() const
{
    return m_sButton1HotImage;
}

void CScrollbarUI::SetButton1HotImage( LPCTSTR pStrImage )
{
    if ( m_sButton1HotImage == pStrImage )return;
    m_sButton1HotImage = pStrImage;
    Invalidate();
}

LPCTSTR CScrollbarUI::GetButton1PushedImage()const
{
    return m_sButton1PushedImage;
}

void CScrollbarUI::SetButton1PushedImage( LPCTSTR pStrImage )
{
    if ( m_sButton1PushedImage == pStrImage )return;
    m_sButton1PushedImage = pStrImage;
    Invalidate();
}

LPCTSTR CScrollbarUI::GetButton1DisabledImage() const
{
    return m_sButton1DisabledImage;
}

void CScrollbarUI::SetButton1DisabledImage( LPCTSTR pStrImage )
{
    if ( m_sButton1DisabledImage == pStrImage )return;
    m_sButton1DisabledImage = pStrImage;
    Invalidate();
}

LPCTSTR CScrollbarUI::GetButton2NormalImage()const
{
    return m_sButton2NormalImage;
}

void CScrollbarUI::SetButton2NormalImage( LPCTSTR pStrImage )
{
    if ( m_sButton2NormalImage == pStrImage )return;
    m_sButton2NormalImage = pStrImage;
    Invalidate();
}

LPCTSTR CScrollbarUI::GetButton2HotImage()const
{
    return m_sButton2HotImage;
}

void CScrollbarUI::SetButton2HotImage( LPCTSTR pStrImage )
{
    if ( m_sButton2HotImage == pStrImage )return;
    m_sButton2HotImage = pStrImage;
    Invalidate();
}

LPCTSTR CScrollbarUI::GetButton2PushedImage()const
{
    return m_sButton2PushedImage;
}

void CScrollbarUI::SetButton2PushedImage( LPCTSTR pStrImage )
{
    if ( m_sButton2PushedImage == pStrImage )return;
    m_sButton2PushedImage = pStrImage;
    Invalidate();
}

LPCTSTR CScrollbarUI::GetButton2DisabledImage()const
{
    return m_sButton2DisabledImage;
}

void CScrollbarUI::SetButton2DisabledImage( LPCTSTR pStrImage )
{
    if ( m_sButton2DisabledImage == pStrImage )return;
    m_sButton2DisabledImage = pStrImage;
    Invalidate();
}

LPCTSTR CScrollbarUI::GetThumbNormalImage()const
{
    return m_sThumbNormalImage;
}

void CScrollbarUI::SetThumbNormalImage( LPCTSTR pStrImage )
{
    if ( m_sThumbNormalImage == pStrImage )return;
    m_sThumbNormalImage = pStrImage;
    Invalidate();
}

LPCTSTR CScrollbarUI::GetThumbHotImage()const
{
    return m_sThumbHotImage;
}

void CScrollbarUI::SetThumbHotImage( LPCTSTR pStrImage )
{
    if ( m_sThumbHotImage == pStrImage )return;
    m_sThumbHotImage = pStrImage;
    Invalidate();
}

LPCTSTR CScrollbarUI::GetThumbPushedImage()const
{
    return m_sThumbPushedImage;
}

void CScrollbarUI::SetThumbPushedImage( LPCTSTR pStrImage )
{
    if ( m_sThumbPushedImage == pStrImage )return;
    m_sThumbPushedImage = pStrImage;
    Invalidate();
}

LPCTSTR CScrollbarUI::GetThumbDisabledImage()const
{
    return m_sThumbDisabledImage;
}

void CScrollbarUI::SetThumbDisabledImage( LPCTSTR pStrImage )
{
    if ( m_sThumbDisabledImage == pStrImage )return;
    m_sThumbDisabledImage = pStrImage;
    Invalidate();
}

LPCTSTR CScrollbarUI::GetRailNormalImage()const
{
    return m_sRailNormalImage;
}

void CScrollbarUI::SetRailNormalImage( LPCTSTR pStrImage )
{
    if ( m_sRailNormalImage == pStrImage )return;
    m_sRailNormalImage = pStrImage;
    Invalidate();
}

LPCTSTR CScrollbarUI::GetRailHotImage()const
{
    return m_sRailHotImage;
}

void CScrollbarUI::SetRailHotImage( LPCTSTR pStrImage )
{
    if ( m_sRailHotImage == pStrImage )return;
    m_sRailHotImage = pStrImage;
    Invalidate();
}

LPCTSTR CScrollbarUI::GetRailPushedImage()const
{
    return m_sRailPushedImage;
}

void CScrollbarUI::SetRailPushedImage( LPCTSTR pStrImage )
{
    if ( m_sRailPushedImage == pStrImage )return;
    m_sRailPushedImage = pStrImage;
    Invalidate();
}

LPCTSTR CScrollbarUI::GetRailDisabledImage()const
{
    return m_sRailDisabledImage;
}

void CScrollbarUI::SetRailDisabledImage( LPCTSTR pStrImage )
{
    if ( m_sRailDisabledImage == pStrImage )return;
    m_sRailDisabledImage = pStrImage;
    Invalidate();
}

LPCTSTR CScrollbarUI::GetBkNormalImage()const
{
    return m_sBkNormalImage;
}

void CScrollbarUI::SetBkNormalImage( LPCTSTR pStrImage )
{
    if ( m_sBkNormalImage == pStrImage )return;
    m_sBkNormalImage = pStrImage;
    Invalidate();
}

LPCTSTR CScrollbarUI::GetBkHotImage()const
{
    return m_sBkHotImage;
}

void CScrollbarUI::SetBkHotImage( LPCTSTR pStrImage )
{
    if ( m_sBkHotImage == pStrImage )return;
    m_sBkHotImage = pStrImage;
    Invalidate();
}

LPCTSTR CScrollbarUI::GetBkPushedImage()const
{
    return m_sBkPushedImage;
}

void CScrollbarUI::SetBkPushedImage( LPCTSTR pStrImage )
{
    if ( m_sBkPushedImage == pStrImage )return;
    m_sBkPushedImage = pStrImage;
    Invalidate();
}

LPCTSTR CScrollbarUI::GetBkDisabledImage()const
{
    return m_sBkDisabledImage;
}

void CScrollbarUI::SetBkDisabledImage( LPCTSTR pStrImage )
{
    if ( m_sBkDisabledImage == pStrImage )return;
    m_sBkDisabledImage = pStrImage;
    Invalidate();
}
RECT CScrollbarUI::SetPosOver ( const RECT& rc )
{
    if ( m_bHorizontal ) {
        int cx = rc.right - rc.left - 2 * m_cxyFixed.cy;
        if ( cx > m_cxyFixed.cy ) {
            m_rcButton1.left = rc.left;
            m_rcButton1.top = rc.top;
            m_rcButton1.right = rc.left + m_cxyFixed.cy;
            m_rcButton1.bottom = rc.top + m_cxyFixed.cy;

            m_rcButton2.left = rc.right - m_cxyFixed.cy;
            m_rcButton2.top = rc.top;
            m_rcButton2.right = rc.right;
            m_rcButton2.bottom = rc.top + m_cxyFixed.cy;

            m_rcThumb.top = rc.top;
            m_rcThumb.bottom = rc.top + m_cxyFixed.cy;
            if ( m_nRange > 0 ) {
                int cxThumb = cx * ( rc.right - rc.left ) / ( m_nRange + rc.right - rc.left );
                if ( cxThumb < m_cxyFixed.cy ) cxThumb = m_cxyFixed.cy;

                m_rcThumb.left = m_nScrollPos * ( cx - cxThumb ) / m_nRange + m_rcButton1.right;
                m_rcThumb.right = m_rcThumb.left + cxThumb;
                if ( m_rcThumb.right > m_rcButton2.left ) {
                    m_rcThumb.left = m_rcButton2.left - cxThumb;
                    m_rcThumb.right = m_rcButton2.left;
                }
                m_rcbk1.left = m_rcButton1.right; m_rcbk1.top = rc.top; m_rcbk1.right = m_rcThumb.left; m_rcbk1.bottom = rc.bottom;
                m_rcbk2.left = m_rcThumb.right; m_rcbk2.top = rc.top; m_rcbk2.right = m_rcButton2.left; m_rcbk2.bottom = rc.bottom;
            }
            else {
                //m_rcThumb.left = m_rcButton1.right;
                //m_rcThumb.right = m_rcButton2.left;
                ::ZeroMemory( &m_rcThumb, sizeof( m_rcThumb ) );
                ::ZeroMemory( &m_rcbk1, sizeof( m_rcbk1 ) );
                ::ZeroMemory( &m_rcbk2, sizeof( m_rcbk2 ) );
            }
        }
        else {
            int cxButton = ( rc.right - rc.left ) / 2;
            if ( cxButton > m_cxyFixed.cy ) cxButton = m_cxyFixed.cy;
            m_rcButton1.left = rc.left;
            m_rcButton1.top = rc.top;
            m_rcButton1.right = rc.left + cxButton;
            m_rcButton1.bottom = rc.top + m_cxyFixed.cy;

            m_rcButton2.left = rc.right - cxButton;
            m_rcButton2.top = rc.top;
            m_rcButton2.right = rc.right;
            m_rcButton2.bottom = rc.top + m_cxyFixed.cy;

            ::ZeroMemory( &m_rcThumb, sizeof( m_rcThumb ) );
            ::ZeroMemory( &m_rcbk1, sizeof( m_rcbk1 ) );
            ::ZeroMemory( &m_rcbk2, sizeof( m_rcbk2 ) );
        }
    }
    else {
        int cy = rc.bottom - rc.top - 2 * m_cxyFixed.cx;
        if ( cy > m_cxyFixed.cx ) {
            m_rcButton1.left = rc.left;
            m_rcButton1.top = rc.top;
            m_rcButton1.right = rc.left + m_cxyFixed.cx;
            m_rcButton1.bottom = rc.top + m_cxyFixed.cx;

            m_rcButton2.left = rc.left;
            m_rcButton2.top = rc.bottom - m_cxyFixed.cx;
            m_rcButton2.right = rc.left + m_cxyFixed.cx;
            m_rcButton2.bottom = rc.bottom;

            m_rcThumb.left = rc.left;
            m_rcThumb.right = rc.left + m_cxyFixed.cx;
            if ( m_nRange > 0 ) {
                int cyThumb = cy * ( rc.bottom - rc.top ) / ( m_nRange + rc.bottom - rc.top );
                if ( cyThumb < m_cxyFixed.cx ) cyThumb = m_cxyFixed.cx;

                m_rcThumb.top = m_nScrollPos * ( cy - cyThumb ) / m_nRange + m_rcButton1.bottom;
                m_rcThumb.bottom = m_rcThumb.top + cyThumb;
                if ( m_rcThumb.bottom > m_rcButton2.top ) {
                    m_rcThumb.top = m_rcButton2.top - cyThumb;
                    m_rcThumb.bottom = m_rcButton2.top;
                }
                m_rcbk1.left = rc.left; m_rcbk1.top = m_rcButton1.bottom; m_rcbk1.right = rc.right; m_rcbk1.bottom = m_rcThumb.top;
                m_rcbk2.left = rc.left; m_rcbk2.top = m_rcThumb.bottom; m_rcbk2.right = rc.right; m_rcbk2.bottom = m_rcButton2.top;
            }
            else {
                //m_rcThumb.top = m_rcButton1.bottom;
                // m_rcThumb.bottom = m_rcButton2.top;
                ::ZeroMemory( &m_rcThumb, sizeof( m_rcThumb ) );
                ::ZeroMemory( &m_rcbk1, sizeof( m_rcbk1 ) );
                ::ZeroMemory( &m_rcbk2, sizeof( m_rcbk2 ) );
            }
        }
        else {
            int cyButton = ( rc.bottom - rc.top ) / 2;
            if ( cyButton > m_cxyFixed.cx ) cyButton = m_cxyFixed.cx;
            m_rcButton1.left = rc.left;
            m_rcButton1.top = rc.top;
            m_rcButton1.right = rc.left + m_cxyFixed.cx;
            m_rcButton1.bottom = rc.top + cyButton;

            m_rcButton2.left = rc.left;
            m_rcButton2.top = rc.bottom - cyButton;
            m_rcButton2.right = rc.left + m_cxyFixed.cx;
            m_rcButton2.bottom = rc.bottom;

            ::ZeroMemory( &m_rcThumb, sizeof( m_rcThumb ) );
            ::ZeroMemory( &m_rcbk1, sizeof( m_rcbk1 ) );
            ::ZeroMemory( &m_rcbk2, sizeof( m_rcbk2 ) );
        }
    }
    return rc;
}

void CScrollbarUI::Event( TEventUI& event )
{
    if ( !IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND ) {
        if ( m_pOwner != NULL ) m_pOwner->Event( event );
        else CControlUI::Event( event );
        return;
    }

    if ( event.Type == UIEVENT_BUTTONDOWN || event.Type == UIEVENT_DBLCLICK ) {
        if ( !IsEnabled() ) return;

        m_nLastScrollOffset = 0;
        m_nScrollRepeatDelay = 0;
        m_pManager->SetTimer( this, DEFAULT_TIMERID, 50U );

        if ( ::PtInRect( &m_rcButton1, event.ptMouse ) ) {
            m_uButton1State |= UISTATE_CAPTURED | UISTATE_PUSHED;
            if ( !m_bHorizontal ) {
                if ( m_pOwner != NULL ) m_pOwner->LineUp();
                else SetScrollPos( m_nScrollPos - m_nLineSize );
            }
            else {
                if ( m_pOwner != NULL ) m_pOwner->LineLeft();
                else SetScrollPos( m_nScrollPos - m_nLineSize );
            }
        }
        else if ( ::PtInRect( &m_rcButton2, event.ptMouse ) ) {
            m_uButton2State |= UISTATE_CAPTURED | UISTATE_PUSHED;
            if ( !m_bHorizontal ) {
                if ( m_pOwner != NULL ) m_pOwner->LineDown();
                else SetScrollPos( m_nScrollPos + m_nLineSize );
            }
            else {
                if ( m_pOwner != NULL ) m_pOwner->LineRight();
                else SetScrollPos( m_nScrollPos + m_nLineSize );
            }
        }
        else if ( ::PtInRect( &m_rcThumb, event.ptMouse ) ) {
            m_uThumbState |= UISTATE_CAPTURED | UISTATE_PUSHED;
            ptLastMouse = event.ptMouse;
            m_nLastScrollPos = m_nScrollPos;
        }
        else {
            if ( !m_bHorizontal ) {
                if ( ::PtInRect( &m_rcbk1, event.ptMouse ) ) {
                    //if ( event.ptMouse.y < m_rcThumb.top ) {
                    m_ubk1State |= UISTATE_CAPTURED | UISTATE_PUSHED;
                    if ( m_pOwner != NULL ) m_pOwner->PageUp();
                    else SetScrollPos( m_nScrollPos + m_rcItem.top - m_rcItem.bottom );
                }
                else if ( ::PtInRect( &m_rcbk2, event.ptMouse ) ) {
                    //else if ( event.ptMouse.y > m_rcThumb.bottom ) {
                    m_ubk2State |= UISTATE_CAPTURED | UISTATE_PUSHED;
                    if ( m_pOwner != NULL ) m_pOwner->PageDown();
                    else SetScrollPos( m_nScrollPos - m_rcItem.top + m_rcItem.bottom );
                }
            }
            else {
                if ( ::PtInRect( &m_rcbk1, event.ptMouse ) ) {
                    //if ( event.ptMouse.x < m_rcThumb.left ) {
                    m_ubk1State |= UISTATE_CAPTURED | UISTATE_PUSHED;
                    if ( m_pOwner != NULL ) m_pOwner->PageLeft();
                    else SetScrollPos( m_nScrollPos + m_rcItem.left - m_rcItem.right );
                }
                else if ( ::PtInRect( &m_rcbk2, event.ptMouse ) ) {
                    //else if ( event.ptMouse.x > m_rcThumb.right ) {
                    m_ubk2State |= UISTATE_CAPTURED | UISTATE_PUSHED;
                    if ( m_pOwner != NULL ) m_pOwner->PageRight();
                    else SetScrollPos( m_nScrollPos - m_rcItem.left + m_rcItem.right );
                }
            }
        }
        return;
    }
    if ( event.Type == UIEVENT_BUTTONUP ) {
        m_nScrollRepeatDelay = 0;
        m_nLastScrollOffset = 0;
        m_pManager->KillTimer( this, DEFAULT_TIMERID );

        if ( ( m_uThumbState & UISTATE_CAPTURED ) != 0 ) {
            m_uThumbState &= ~( UISTATE_CAPTURED | UISTATE_PUSHED );
            Invalidate();
        }
        else if ( ( m_uButton1State & UISTATE_CAPTURED ) != 0 ) {
            m_uButton1State &= ~( UISTATE_CAPTURED | UISTATE_PUSHED );
            Invalidate();
        }
        else if ( ( m_uButton2State & UISTATE_CAPTURED ) != 0 ) {
            m_uButton2State &= ~( UISTATE_CAPTURED | UISTATE_PUSHED );
            Invalidate();
        }
        else if ( ( m_ubk1State & UISTATE_CAPTURED ) != 0 ) {
            m_ubk1State &= ~( UISTATE_CAPTURED | UISTATE_PUSHED );
            Invalidate();
        }
        else if ( ( m_ubk2State & UISTATE_CAPTURED ) != 0 ) {
            m_ubk2State &= ~( UISTATE_CAPTURED | UISTATE_PUSHED );
            Invalidate();
        }
        return;
    }
    if ( event.Type == UIEVENT_MOUSEMOVE ) {
        if ( ( m_uThumbState & UISTATE_CAPTURED ) != 0 ) {
            if ( !m_bHorizontal ) {
                m_nLastScrollOffset = ( event.ptMouse.y - ptLastMouse.y ) * m_nRange / \
                                      ( m_rcItem.bottom - m_rcItem.top - m_rcThumb.bottom + m_rcThumb.top - 2 * m_cxyFixed.cx );
            }
            else {
                m_nLastScrollOffset = ( event.ptMouse.x - ptLastMouse.x ) * m_nRange / \
                                      ( m_rcItem.right - m_rcItem.left - m_rcThumb.right + m_rcThumb.left - 2 * m_cxyFixed.cy );
            }
        }
        else {
            if ( ( m_uThumbState & UISTATE_HOT ) != 0 ) {
                if ( !::PtInRect( &m_rcThumb, event.ptMouse ) ) {
                    m_uThumbState &= ~UISTATE_HOT;
                    Invalidate();
                }
            }
            else {
                if ( !IsEnabled() ) return;
                if ( ::PtInRect( &m_rcThumb, event.ptMouse ) ) {
                    m_uThumbState |= UISTATE_HOT;
                    Invalidate();
                }
            }
        }
        if ( ( m_uButton1State & UISTATE_CAPTURED ) != 0 ) {
            if ( ::PtInRect( &m_rcButton1, event.ptMouse ) ) m_uButton1State |= UISTATE_PUSHED;
            else m_uButton1State &= ~UISTATE_PUSHED;
            Invalidate();
        }
        else {
            if ( ( m_uButton1State & UISTATE_HOT ) != 0 ) {
                if ( !::PtInRect( &m_rcButton1, event.ptMouse ) ) {
                    m_uButton1State &= ~UISTATE_HOT;
                    Invalidate();
                }
            }
            else {
                if ( !IsEnabled() ) return;
                if ( ::PtInRect( &m_rcButton1, event.ptMouse ) ) {
                    m_uButton1State |= UISTATE_HOT;
                    Invalidate();
                }
            }
        }
        if ( ( m_uButton2State & UISTATE_CAPTURED ) != 0 ) {
            if ( ::PtInRect( &m_rcButton2, event.ptMouse ) ) m_uButton2State |= UISTATE_PUSHED;
            else m_uButton2State &= ~UISTATE_PUSHED;
            Invalidate();
        }
        else {
            if ( ( m_uButton2State & UISTATE_HOT ) != 0 ) {
                if ( !::PtInRect( &m_rcButton2, event.ptMouse ) ) {
                    m_uButton2State &= ~UISTATE_HOT;
                    Invalidate();
                }
            }
            else {
                if ( !IsEnabled() ) return;
                if ( ::PtInRect( &m_rcButton2, event.ptMouse ) ) {
                    m_uButton2State |= UISTATE_HOT;
                    Invalidate();
                }
            }
        }
        if ( ( m_ubk1State & UISTATE_CAPTURED ) != 0 ) {
            if ( ::PtInRect( &m_rcbk1, event.ptMouse ) ) m_ubk1State |= UISTATE_PUSHED;
            else m_ubk1State &= ~UISTATE_PUSHED;
            Invalidate();
        }
        else {
            if ( ( m_ubk1State & UISTATE_HOT ) != 0 ) {
                if ( !::PtInRect( &m_rcbk1, event.ptMouse ) ) {
                    m_ubk1State &= ~UISTATE_HOT;
                    Invalidate();
                }
            }
            else {
                if ( !IsEnabled() ) return;
                if ( ::PtInRect( &m_rcbk1, event.ptMouse ) ) {
                    m_ubk1State |= UISTATE_HOT;
                    Invalidate();
                }
            }
        }
        if ( ( m_ubk2State & UISTATE_CAPTURED ) != 0 ) {
            if ( ::PtInRect( &m_rcbk2, event.ptMouse ) ) m_ubk2State |= UISTATE_PUSHED;
            else m_ubk2State &= ~UISTATE_PUSHED;
            Invalidate();
        }
        else {
            if ( ( m_ubk2State & UISTATE_HOT ) != 0 ) {
                if ( !::PtInRect( &m_rcbk2, event.ptMouse ) ) {
                    m_ubk2State &= ~UISTATE_HOT;
                    Invalidate();
                }
            }
            else {
                if ( !IsEnabled() ) return;
                if ( ::PtInRect( &m_rcbk2, event.ptMouse ) ) {
                    m_ubk2State |= UISTATE_HOT;
                    Invalidate();
                }
            }
        }
        return;
    }
    if ( event.Type == UIEVENT_TIMER && event.wParam == DEFAULT_TIMERID ) {
        if ( !IsEnabled() ) {
            m_pManager->KillTimer( this, DEFAULT_TIMERID );
            return;
        }
        ++m_nScrollRepeatDelay;
        if ( ( m_uThumbState & UISTATE_CAPTURED ) != 0 ) {
            if ( !m_bHorizontal ) {
                if ( m_pOwner != NULL ) m_pOwner->SetScrollPos( CSize( m_pOwner->GetScrollPos().cx, \
                            m_nLastScrollPos + m_nLastScrollOffset ) );
                else SetScrollPos( m_nLastScrollPos + m_nLastScrollOffset );
            }
            else {
                if ( m_pOwner != NULL ) m_pOwner->SetScrollPos( CSize( m_nLastScrollPos + m_nLastScrollOffset, \
                            m_pOwner->GetScrollPos().cy ) );
                else SetScrollPos( m_nLastScrollPos + m_nLastScrollOffset );
            }
            Invalidate();
        }
        else if ( ( m_uButton1State & UISTATE_PUSHED ) != 0 ) {
            if ( m_nScrollRepeatDelay <= 5 ) return;
            if ( !m_bHorizontal ) {
                if ( m_pOwner != NULL ) m_pOwner->LineUp();
                else SetScrollPos( m_nScrollPos - m_nLineSize );
            }
            else {
                if ( m_pOwner != NULL ) m_pOwner->LineLeft();
                else SetScrollPos( m_nScrollPos - m_nLineSize );
            }
        }
        else if ( ( m_uButton2State & UISTATE_PUSHED ) != 0 ) {
            if ( m_nScrollRepeatDelay <= 5 ) return;
            if ( !m_bHorizontal ) {
                if ( m_pOwner != NULL ) m_pOwner->LineDown();
                else SetScrollPos( m_nScrollPos + m_nLineSize );
            }
            else {
                if ( m_pOwner != NULL ) m_pOwner->LineRight();
                else SetScrollPos( m_nScrollPos + m_nLineSize );
            }
        }
        else if ( ( m_ubk1State & UISTATE_PUSHED ) != 0 ) {
            if ( m_nScrollRepeatDelay <= 5 ) return;
            if ( !m_bHorizontal ) {
                if ( m_pOwner != NULL ) m_pOwner->PageUp();
                else SetScrollPos( m_nScrollPos + m_rcItem.top - m_rcItem.bottom );
            }
            else {
                if ( m_pOwner != NULL ) m_pOwner->PageDown();
                else SetScrollPos(  m_nScrollPos - m_rcItem.top + m_rcItem.bottom );
            }
        }
        else if ( ( m_ubk2State & UISTATE_PUSHED ) != 0 ) {
            if ( m_nScrollRepeatDelay <= 5 ) return;
            if ( !m_bHorizontal ) {
                if ( m_pOwner != NULL ) m_pOwner->PageLeft();
                else SetScrollPos(  m_nScrollPos + m_rcItem.left - m_rcItem.right );
            }
            else {
                if ( m_pOwner != NULL ) m_pOwner->PageRight();
                else SetScrollPos(  m_nScrollPos - m_rcItem.left + m_rcItem.right );
            }
        }
        //         else
        // 		{
        //             if ( m_nScrollRepeatDelay <= 5 ) return;
        //             POINT pt = { 0 };
        //             ::GetCursorPos( &pt );
        //             ::ScreenToClient( m_pManager->GetPaintWindow(), &pt );
        //             if ( !m_bHorizontal ) {
        //                 if ( pt.y < m_rcThumb.top ) {
        //                     if ( m_pOwner != NULL ) m_pOwner->PageUp();
        //                     else SetScrollPos( m_nScrollPos + m_rcItem.top - m_rcItem.bottom );
        //                 }
        //                 else if ( pt.y > m_rcThumb.bottom ) {
        //                     if ( m_pOwner != NULL ) m_pOwner->PageDown();
        //                     else SetScrollPos( m_nScrollPos - m_rcItem.top + m_rcItem.bottom );
        //                 }
        //             }
        //             else {
        //                 if ( pt.x < m_rcThumb.left ) {
        //                     if ( m_pOwner != NULL ) m_pOwner->PageLeft();
        //                     else SetScrollPos( m_nScrollPos + m_rcItem.left - m_rcItem.right );
        //                 }
        //                 else if ( pt.x > m_rcThumb.right ) {
        //                     if ( m_pOwner != NULL ) m_pOwner->PageRight();
        //                     else SetScrollPos( m_nScrollPos - m_rcItem.left + m_rcItem.right );
        //                 }
        //             }
        //         }
        return;
    }
    if ( event.Type == UIEVENT_MOUSEENTER ) {
        // if ( IsEnabled() ) {
        //	m_ubk1State|=UISTATE_HOT;
        //m_ubk2State|=UISTATE_HOT;
        //m_uButton1State |= UISTATE_HOT;
        //m_uButton2State |= UISTATE_HOT;
        //if ( ::PtInRect( &m_rcThumb, event.ptMouse ) ) m_uThumbState |= UISTATE_HOT;
        //  Invalidate();
        // }
        return;
    }
    if ( event.Type == UIEVENT_MOUSELEAVE ) {
        if ( IsEnabled() ) {
            m_ubk1State &= ~UISTATE_HOT;
            m_ubk2State &= ~UISTATE_HOT;
            m_uButton1State &= ~UISTATE_HOT;
            m_uButton2State &= ~UISTATE_HOT;
            m_uThumbState &= ~UISTATE_HOT;
            Invalidate();
        }
        return;
    }

    if ( m_pOwner != NULL ) m_pOwner->Event( event ); else CControlUI::Event( event );
}

void CScrollbarUI::SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue )
{
    if ( _tcscmp( pstrName, _T( "button1normalimage" ) ) == 0 ) SetButton1NormalImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "button1hotimage" ) ) == 0 ) SetButton1HotImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "button1pushedimage" ) ) == 0 ) SetButton1PushedImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "button1disabledimage" ) ) == 0 ) SetButton1DisabledImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "button2normalimage" ) ) == 0 ) SetButton2NormalImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "button2hotimage" ) ) == 0 ) SetButton2HotImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "button2pushedimage" ) ) == 0 ) SetButton2PushedImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "button2disabledimage" ) ) == 0 ) SetButton2DisabledImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "thumbnormalimage" ) ) == 0 ) SetThumbNormalImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "thumbhotimage" ) ) == 0 ) SetThumbHotImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "thumbpushedimage" ) ) == 0 ) SetThumbPushedImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "thumbdisabledimage" ) ) == 0 ) SetThumbDisabledImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "railnormalimage" ) ) == 0 ) SetRailNormalImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "railhotimage" ) ) == 0 ) SetRailHotImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "railpushedimage" ) ) == 0 ) SetRailPushedImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "raildisabledimage" ) ) == 0 ) SetRailDisabledImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "bknormalimage" ) ) == 0 ) SetBkNormalImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "bkhotimage" ) ) == 0 ) SetBkHotImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "bkpushedimage" ) ) == 0 ) SetBkPushedImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "bkdisabledimage" ) ) == 0 ) SetBkDisabledImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "hor" ) ) == 0 ) SetHorizontal( _tcscmp( pstrValue, _T( "true" ) ) == 0 );
    else if ( _tcscmp( pstrName, _T( "linesize" ) ) == 0 ) SetLineSize( _ttoi( pstrValue ) );
    else if ( _tcscmp( pstrName, _T( "range" ) ) == 0 ) SetScrollRange( _ttoi( pstrValue ) );
    else if ( _tcscmp( pstrName, _T( "value" ) ) == 0 ) SetScrollPos( _ttoi( pstrValue ) );
    else CControlUI::SetAttribute( pstrName, pstrValue );
}

void CScrollbarUI::DoPaintOver( GRAPHorHDC& gorh )
{
    PaintBk( gorh );
    PaintButton1( gorh );
    PaintButton2( gorh );
    PaintThumb( gorh );
    PaintRail( gorh );
}

void CScrollbarUI::PaintBk( GRAPHorHDC& gorh )
{
    if ( !IsEnabled() ) {m_ubk1State |= UISTATE_DISABLED; m_ubk2State |= UISTATE_DISABLED;}
    else {m_ubk1State &= ~ UISTATE_DISABLED; m_ubk2State &= ~ UISTATE_DISABLED;}

    RECT rc_bk1 = m_rcItem, rc_bk2 = m_rcItem;
    if ( m_rcbk1.top != 0 && m_rcbk2.bottom != 0 ) {
        if ( !m_bHorizontal ) {
            rc_bk1.bottom = m_rcbk1.bottom;
            rc_bk2.top = m_rcbk2.top;
        }
        else {
            rc_bk1.right = m_rcbk1.right;
            rc_bk2.left = m_rcbk2.left;
        }
    }

    if ( ( m_ubk1State & UISTATE_DISABLED ) != 0 ) {
        if ( !m_sBkDisabledImage.IsEmpty() ) {
            if ( !DrawImage( gorh, ( LPCTSTR )m_sBkDisabledImage ) ) m_sBkDisabledImage.Empty();
            else return;
        }
    }
    else if ( ( m_ubk1State & UISTATE_PUSHED ) != 0 ) {
        if ( !m_sBkPushedImage.IsEmpty() ) {
            m_sImageModify.FormatTinyBuf( _T( "dest='%d,%d,%d,%d'" ), rc_bk1.left - m_rcItem.left, rc_bk1.top - m_rcItem.top, \
                                          rc_bk1.right - m_rcItem.left, rc_bk1.bottom - m_rcItem.top );
            if ( !DrawImage( gorh, ( LPCTSTR )m_sBkPushedImage  , ( LPCTSTR )m_sImageModify ) ) m_sBkPushedImage.Empty();
            else return;
        }
    }
    else if ( ( m_ubk2State & UISTATE_PUSHED ) != 0 ) {
        if ( !m_sBkPushedImage.IsEmpty() ) {
            m_sImageModify.FormatTinyBuf( _T( "dest='%d,%d,%d,%d'" ), rc_bk2.left - m_rcItem.left, rc_bk2.top - m_rcItem.top, \
                                          rc_bk2.right - m_rcItem.left, rc_bk2.bottom - m_rcItem.top );
            if ( !DrawImage( gorh, ( LPCTSTR )m_sBkPushedImage  , ( LPCTSTR )m_sImageModify ) ) m_sBkPushedImage.Empty();
            else return;
        }
    }
    else if ( ( m_ubk1State & UISTATE_HOT ) != 0 ) {
        if ( !m_sBkHotImage.IsEmpty() ) {
            m_sImageModify.FormatTinyBuf( _T( "dest='%d,%d,%d,%d'" ), rc_bk1.left - m_rcItem.left, rc_bk1.top - m_rcItem.top, \
                                          rc_bk1.right - m_rcItem.left, rc_bk1.bottom - m_rcItem.top );
            if ( !DrawImage( gorh, ( LPCTSTR )m_sBkHotImage, ( LPCTSTR )m_sImageModify  ) ) m_sBkHotImage.Empty();
            else return;
        }
    }
    else if ( ( m_ubk2State & UISTATE_HOT ) != 0 ) {
        if ( !m_sBkHotImage.IsEmpty() ) {
            m_sImageModify.FormatTinyBuf( _T( "dest='%d,%d,%d,%d'" ), rc_bk2.left - m_rcItem.left, rc_bk2.top - m_rcItem.top, \
                                          rc_bk2.right - m_rcItem.left, rc_bk2.bottom - m_rcItem.top );
            if ( !DrawImage( gorh, ( LPCTSTR )m_sBkHotImage, ( LPCTSTR )m_sImageModify  ) ) m_sBkHotImage.Empty();
            else return;
        }
    }

    if ( !m_sBkNormalImage.IsEmpty() ) {
        if ( !DrawImage( gorh, ( LPCTSTR )m_sBkNormalImage ) ) m_sBkNormalImage.Empty();
        else return;
    }

    if ( !m_bNotUseDefSkin && m_pManager ) {
        CDefaultSkinUI::DrawScrollbar( gorh, m_pManager->GetPaintWindow(), rc_bk2, m_ubk2State, m_bHorizontal ? CDefaultSkinUI::PART_SCROLLBAR_UPHORZ : CDefaultSkinUI::PART_SCROLLBAR_UPVERT );
        CDefaultSkinUI::DrawScrollbar( gorh, m_pManager->GetPaintWindow(), rc_bk1, m_ubk1State, m_bHorizontal ? CDefaultSkinUI::PART_SCROLLBAR_LOWHORZ : CDefaultSkinUI::PART_SCROLLBAR_LOWVERT );
    }
}

void CScrollbarUI::PaintButton1( GRAPHorHDC& gorh )
{
    if ( !IsEnabled() ) m_uButton1State |= UISTATE_DISABLED;
    else m_uButton1State &= ~ UISTATE_DISABLED;

    //m_sImageModify.Empty();
    m_sImageModify.FormatTinyBuf( _T( "dest='%d,%d,%d,%d'" ), m_rcButton1.left - m_rcItem.left, \
                                  m_rcButton1.top - m_rcItem.top, m_rcButton1.right - m_rcItem.left, m_rcButton1.bottom - m_rcItem.top );

    if ( ( m_uButton1State & UISTATE_DISABLED ) != 0 ) {
        if ( !m_sButton1DisabledImage.IsEmpty() ) {
            if ( !DrawImage( gorh, ( LPCTSTR )m_sButton1DisabledImage, ( LPCTSTR )m_sImageModify ) ) m_sButton1DisabledImage.Empty();
            else return;
        }
    }
    else if ( ( m_uButton1State & UISTATE_PUSHED ) != 0 ) {
        if ( !m_sButton1PushedImage.IsEmpty() ) {
            if ( !DrawImage( gorh, ( LPCTSTR )m_sButton1PushedImage, ( LPCTSTR )m_sImageModify ) ) m_sButton1PushedImage.Empty();
            else return;
        }
    }
    else if ( ( m_uButton1State & UISTATE_HOT ) != 0 ) {
        if ( !m_sButton1HotImage.IsEmpty() ) {
            if ( !DrawImage( gorh, ( LPCTSTR )m_sButton1HotImage, ( LPCTSTR )m_sImageModify ) ) m_sButton1HotImage.Empty();
            else return;
        }
    }

    if ( !m_sButton1NormalImage.IsEmpty() ) {
        if ( !DrawImage( gorh, ( LPCTSTR )m_sButton1NormalImage, ( LPCTSTR )m_sImageModify ) ) m_sButton1NormalImage.Empty();
        else return;
    }
    if ( !m_bNotUseDefSkin && m_pManager )
        CDefaultSkinUI::DrawScrollbar( gorh, m_pManager->GetPaintWindow(), m_rcButton1, m_uButton1State, m_bHorizontal ? CDefaultSkinUI::PART_SCROLLBAR_BUTTON_LEFT : CDefaultSkinUI::PART_SCROLLBAR_BUTTON_UP );
}

void CScrollbarUI::PaintButton2( GRAPHorHDC& gorh )
{
    if ( !IsEnabled() ) m_uButton2State |= UISTATE_DISABLED;
    else m_uButton2State &= ~ UISTATE_DISABLED;

    //m_sImageModify.Empty();
    m_sImageModify.FormatTinyBuf( _T( "dest='%d,%d,%d,%d'" ), m_rcButton2.left - m_rcItem.left, \
                                  m_rcButton2.top - m_rcItem.top, m_rcButton2.right - m_rcItem.left, m_rcButton2.bottom - m_rcItem.top );

    if ( ( m_uButton2State & UISTATE_DISABLED ) != 0 ) {
        if ( !m_sButton2DisabledImage.IsEmpty() ) {
            if ( !DrawImage( gorh, ( LPCTSTR )m_sButton2DisabledImage, ( LPCTSTR )m_sImageModify ) ) m_sButton2DisabledImage.Empty();
            else return;
        }
    }
    else if ( ( m_uButton2State & UISTATE_PUSHED ) != 0 ) {
        if ( !m_sButton2PushedImage.IsEmpty() ) {
            if ( !DrawImage( gorh, ( LPCTSTR )m_sButton2PushedImage, ( LPCTSTR )m_sImageModify ) ) m_sButton2PushedImage.Empty();
            else return;
        }
    }
    else if ( ( m_uButton2State & UISTATE_HOT ) != 0 ) {
        if ( !m_sButton2HotImage.IsEmpty() ) {
            if ( !DrawImage( gorh, ( LPCTSTR )m_sButton2HotImage, ( LPCTSTR )m_sImageModify ) ) m_sButton2HotImage.Empty();
            else return;
        }
    }

    if ( !m_sButton2NormalImage.IsEmpty() ) {
        if ( !DrawImage( gorh, ( LPCTSTR )m_sButton2NormalImage, ( LPCTSTR )m_sImageModify ) ) m_sButton2NormalImage.Empty();
        else return;
    }
    if ( !m_bNotUseDefSkin && m_pManager )
        CDefaultSkinUI::DrawScrollbar( gorh, m_pManager->GetPaintWindow(), m_rcButton2, m_uButton2State, m_bHorizontal  ? CDefaultSkinUI::PART_SCROLLBAR_BUTTON_RIGHT : CDefaultSkinUI:: PART_SCROLLBAR_BUTTON_DOWN );
}

void CScrollbarUI::PaintThumb( GRAPHorHDC& gorh )
{
    if ( m_rcThumb.left == 0 && m_rcThumb.top == 0 && m_rcThumb.right == 0 && m_rcThumb.bottom == 0 ) return;
    if ( !IsEnabled() ) m_uThumbState |= UISTATE_DISABLED;
    else m_uThumbState &= ~ UISTATE_DISABLED;

    //m_sImageModify.Empty();
    m_sImageModify.FormatTinyBuf( _T( "dest='%d,%d,%d,%d'" ), m_rcThumb.left - m_rcItem.left, \
                                  m_rcThumb.top - m_rcItem.top, m_rcThumb.right - m_rcItem.left, m_rcThumb.bottom - m_rcItem.top );

    if ( ( m_uThumbState & UISTATE_DISABLED ) != 0 ) {
        if ( !m_sThumbDisabledImage.IsEmpty() ) {
            if ( !DrawImage( gorh, ( LPCTSTR )m_sThumbDisabledImage, ( LPCTSTR )m_sImageModify ) ) m_sThumbDisabledImage.Empty();
            else return;
        }
    }
    else if ( ( m_uThumbState & UISTATE_PUSHED ) != 0 ) {
        if ( !m_sThumbPushedImage.IsEmpty() ) {
            if ( !DrawImage( gorh, ( LPCTSTR )m_sThumbPushedImage, ( LPCTSTR )m_sImageModify ) ) m_sThumbPushedImage.Empty();
            else return;
        }
    }
    else if ( ( m_uThumbState & UISTATE_HOT ) != 0 ) {
        if ( !m_sThumbHotImage.IsEmpty() ) {
            if ( !DrawImage( gorh, ( LPCTSTR )m_sThumbHotImage, ( LPCTSTR )m_sImageModify ) ) m_sThumbHotImage.Empty();
            else return;
        }
    }

    if ( !m_sThumbNormalImage.IsEmpty() ) {
        if ( !DrawImage( gorh, ( LPCTSTR )m_sThumbNormalImage, ( LPCTSTR )m_sImageModify ) ) m_sThumbNormalImage.Empty();
        else return;
    }

    if ( !m_bNotUseDefSkin && m_pManager )
        CDefaultSkinUI::DrawScrollbar( gorh, m_pManager->GetPaintWindow(), m_rcThumb, m_uThumbState, m_bHorizontal ? CDefaultSkinUI::PART_SCROLLBAR_THUMBHORZ : CDefaultSkinUI::PART_SCROLLBAR_THUMBVERT );
}

void CScrollbarUI::PaintRail( GRAPHorHDC& gorh )
{
    if ( m_rcThumb.left == 0 && m_rcThumb.top == 0 && m_rcThumb.right == 0 && m_rcThumb.bottom == 0 ) return;
    if ( !IsEnabled() ) m_uThumbState |= UISTATE_DISABLED;
    else m_uThumbState &= ~ UISTATE_DISABLED;

    //m_sImageModify.Empty();
    RECT rc_rail;
    if ( !m_bHorizontal ) {
        rc_rail.left = m_rcThumb.left; rc_rail.top = ( m_rcThumb.top + m_rcThumb.bottom ) / 2 - m_cxyFixed.cx / 2;
        rc_rail.right = m_rcThumb.right; rc_rail.bottom = ( m_rcThumb.top + m_rcThumb.bottom ) / 2 + m_cxyFixed.cx - m_cxyFixed.cx / 2;
    }
    else {
        rc_rail.left = ( m_rcThumb.left + m_rcThumb.right ) / 2 - m_cxyFixed.cy / 2;	rc_rail.top = m_rcThumb.top;
        rc_rail.right = ( m_rcThumb.left + m_rcThumb.right ) / 2 + m_cxyFixed.cy - m_cxyFixed.cy / 2; rc_rail.bottom = m_rcThumb.bottom ;
    }

    m_sImageModify.FormatTinyBuf( _T( "dest='%d,%d,%d,%d'" ), rc_rail.left - m_rcItem.left, \
                                  rc_rail.top - m_rcItem.top, rc_rail.right - m_rcItem.left, rc_rail.bottom - m_rcItem.top );

    if ( ( m_uThumbState & UISTATE_DISABLED ) != 0 ) {
        if ( !m_sRailDisabledImage.IsEmpty() ) {
            if ( !DrawImage( gorh, ( LPCTSTR )m_sRailDisabledImage, ( LPCTSTR )m_sImageModify ) ) m_sRailDisabledImage.Empty();
            else return;
        }
    }
    else if ( ( m_uThumbState & UISTATE_PUSHED ) != 0 ) {
        if ( !m_sRailPushedImage.IsEmpty() ) {
            if ( !DrawImage( gorh, ( LPCTSTR )m_sRailPushedImage, ( LPCTSTR )m_sImageModify ) ) m_sRailPushedImage.Empty();
            else return;
        }
    }
    else if ( ( m_uThumbState & UISTATE_HOT ) != 0 ) {
        if ( !m_sRailHotImage.IsEmpty() ) {
            if ( !DrawImage( gorh, ( LPCTSTR )m_sRailHotImage, ( LPCTSTR )m_sImageModify ) ) m_sRailHotImage.Empty();
            else return;
        }
    }

    if ( !m_sRailNormalImage.IsEmpty() ) {
        if ( !DrawImage( gorh, ( LPCTSTR )m_sRailNormalImage, ( LPCTSTR )m_sImageModify ) ) m_sRailNormalImage.Empty();
        else return;
    }
    if ( !m_bNotUseDefSkin && m_pManager )
        CDefaultSkinUI::DrawScrollbar( gorh, m_pManager->GetPaintWindow(), rc_rail, 0, m_bHorizontal ? CDefaultSkinUI::PART_SCROLLBAR_RAILHORZ : CDefaultSkinUI::PART_SCROLLBAR_RAILVERT );
}
