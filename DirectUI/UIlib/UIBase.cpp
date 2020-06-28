
#include "StdAfx.h"
#include "UIBase.h"
/////////////////////////////////////////////////////////////////////////////////////
//动态创建
CRuntimeClass* CRuntimeClass::firstclass;
void* CRuntimeClass::CreateObjectByName( const TCHAR* name )
{
    CRuntimeClass* now = firstclass;
    while ( now != NULL ) {
        //"C"+"name"+"UI"
        int namelen = _tcslen( name );
        if ( _tcsncmp( name, now->classname + 1, namelen ) == 0 && namelen == _tcslen( now->classname ) - 3 ) {
            return now->CreateObject();
        }
        now = now->nextclass;
    }
    return NULL;
}

CLASS_INIT::CLASS_INIT( CRuntimeClass* pNewClass )
{
    pNewClass->nextclass = CRuntimeClass::firstclass;
    CRuntimeClass::firstclass = pNewClass;
}

/////////////////////////////////////////////////////////////////////////////////////
//
//
CRgn::CRgn()
{
    m_hrgn =::CreateRectRgn( 0, 0, 0, 0 );
    ASSERT( m_hrgn );
    m_bIsEmpty = true;
}
CRgn::CRgn( HRGN hrgn )
{
    m_hrgn =::CreateRectRgn( 0, 0, 0, 0 );
    ASSERT( m_hrgn );
    int ret;
    ret =::CombineRgn( m_hrgn, hrgn, NULL, RGN_COPY );
    ASSERT( ret != ERROR );
    m_bIsEmpty = ( ret == NULLREGION );
}
CRgn::CRgn( const CRgn& rgn )
{
    m_hrgn =::CreateRectRgn( 0, 0, 0, 0 );
    ASSERT( m_hrgn );
    VERIFY( ::CombineRgn( m_hrgn, rgn.m_hrgn, NULL, RGN_COPY ) != ERROR );
    m_bIsEmpty = rgn.m_bIsEmpty;
}
CRgn::CRgn( int nLeftRect, int nTopRect, int nRightRect, int nBottomRect )
{
    m_hrgn =::CreateRectRgn( nLeftRect, nTopRect, nRightRect, nBottomRect );
    ASSERT( m_hrgn );
    RECT rc = {nLeftRect, nTopRect, nRightRect, nBottomRect};
    m_bIsEmpty = ( ::IsRectEmpty( &rc ) == TRUE );
}
CRgn::CRgn( const RECT* lprc )
{
    m_hrgn =::CreateRectRgnIndirect( lprc );
    ASSERT( m_hrgn );
    m_bIsEmpty = ( ::IsRectEmpty( lprc ) == TRUE );
}
// CRgn::CRgn( LPRGNDATA lpRgnData, DWORD size )
// {
//     m_hrgn =::ExtCreateRegion( NULL, size, lpRgnData );
//     ASSERT( m_hrgn );
// }
CRgn::~CRgn()
{
    ::DeleteObject( m_hrgn );
}
// DWORD CRgn::GetData( LPRGNDATA& lpRgnData )
// {
//     DWORD ret =::GetRegionData( m_hrgn, 0, NULL );
//     ASSERT( ret != 0 );
//     lpRgnData = reinterpret_cast<LPRGNDATA>( new BYTE[ret] );
//     ret =::GetRegionData( m_hrgn, ret, lpRgnData );
//     ASSERT( ret != 0 );
//     return ret;
// }
bool CRgn::IsEmpty() const
{
    return m_bIsEmpty;
}
void CRgn::Join( const CRgn& rgn )
{
    int ret =::CombineRgn( m_hrgn, m_hrgn, rgn.m_hrgn, RGN_OR );
    ASSERT( ret != ERROR );
    m_bIsEmpty = ( ret == NULLREGION );
}
void CRgn::Intersect( const CRgn& rgn )
{
    int ret =::CombineRgn( m_hrgn, m_hrgn, rgn.m_hrgn, RGN_AND );
    VERIFY( ret != ERROR );
    m_bIsEmpty = ( ret == NULLREGION );
}
bool CRgn::PtInRegion( POINT* p )
{
    return ::PtInRegion( m_hrgn, p->x, p->y ) == TRUE;
}
CRgn::operator Region() const
{
    return m_hrgn;
}
CRgn::operator HRGN() const
{
    return m_hrgn;
}
CRgn& CRgn::operator=( HRGN hrgn )
{
    ASSERT( hrgn );
    int ret;
    ret =::CombineRgn( m_hrgn, hrgn, NULL, RGN_COPY );
    ASSERT( ret != ERROR );
    m_bIsEmpty = ( ret == NULLREGION );
    return *this;
}
CRgn& CRgn::operator=( const CRgn& rgn )
{
    VERIFY( ::CombineRgn( m_hrgn, rgn.m_hrgn, NULL, RGN_COPY ) != ERROR );
    m_bIsEmpty = rgn.m_bIsEmpty;
    return *this;
}
CRgn& CRgn::operator=( const RECT& rect )
{
    VERIFY( ::SetRectRgn( m_hrgn, rect.left, rect.top, rect.right, rect.bottom ) );
    m_bIsEmpty = ( ::IsRectEmpty( &rect ) == TRUE );
    return *this;
}
/////////////////////////////////////////////////////////////////////////////////////
//
//

CPoint::CPoint()
{
    x = y = 0;
}

CPoint::CPoint( const POINT& src )
{
    x = src.x;
    y = src.y;
}

CPoint::CPoint( int _x, int _y )
{
    x = _x;
    y = _y;
}

CPoint::CPoint( LPARAM lParam )
{
    x = GET_X_LPARAM( lParam );
    y = GET_Y_LPARAM( lParam );
}

/////////////////////////////////////////////////////////////////////////////////////
//
//

CSize::CSize()
{
    cx = cy = 0;
}

CSize::CSize( const SIZE& src )
{
    cx = src.cx;
    cy = src.cy;
}

CSize::CSize( const RECT& rc )
{
    cx = rc.right - rc.left;
    cy = rc.bottom - rc.top;
}

CSize::CSize( int _cx, int _cy )
{
    cx = _cx;
    cy = _cy;
}

CSize::operator Size() const
{
    return Size( cx, cy );
}
/////////////////////////////////////////////////////////////////////////////////////
//
//

CRect::CRect()
{
    left = top = right = bottom = 0;
}

CRect::CRect( const RECT& src )
{
    left = src.left;
    top = src.top;
    right = src.right;
    bottom = src.bottom;
}

CRect::CRect( int iLeft, int iTop, int iRight, int iBottom )
{
    left = iLeft;
    top = iTop;
    right = iRight;
    bottom = iBottom;
}

int CRect::GetWidth() const
{
    return right - left;
}

int CRect::GetHeight() const
{
    return bottom - top;
}

void CRect::Empty()
{
    left = top = right = bottom = 0;
}

bool CRect::IsNull() const
{
    return ( left == 0 && right == 0 && top == 0 && bottom == 0 );
}

// void CRect::Join( const RECT& rc )
// {
//     if ( rc.left < left ) left = rc.left;
//     if ( rc.top < top ) top = rc.top;
//     if ( rc.right > right ) right = rc.right;
//     if ( rc.bottom > bottom ) bottom = rc.bottom;
// }

void CRect::ResetOffset()
{
    ::OffsetRect( this, -left, -top );
}

void CRect::Normalize()
{
    if ( left > right ) {int tmp = left; left = right; right = tmp;}
    if ( top > bottom ) {int tmp = top; top = bottom; bottom = tmp;}
}

void CRect::Offset( int cx, int cy )
{
    ::OffsetRect( this, cx, cy );
}

void CRect::Inflate( int cx, int cy )
{
    ::InflateRect( this, cx, cy );
}

void CRect::Deflate( int cx, int cy )
{
    ::InflateRect( this, -cx, -cy );
}

void CRect::Union( const RECT& rc )
{
    ::UnionRect( this, this, &rc );
}
CRect::operator Rect() const
{
    return Rect( left, top, right - left, bottom - top );
}

bool CRect::IsEmpty() const
{
    return ::IsRectEmpty( this ) == TRUE;
}

void CRect::Intersect( const RECT& rc )
{
    ::IntersectRect( this, this, &rc );
}

/////////////////////////////////////////////////////////////////////////////////////
//
//

CWindowWnd::CWindowWnd() : m_hWnd( NULL ), m_OldWndProc( ::DefWindowProc ), m_bSubclassed( false )
{
}

HWND CWindowWnd::GetHWND() const
{
    return m_hWnd;
}

UINT CWindowWnd::GetClassStyle() const
{
    return 0;
}

LPCTSTR CWindowWnd::GetSuperClassName() const
{
    return NULL;
}

CWindowWnd::operator HWND() const
{
    return m_hWnd;
}

HWND CWindowWnd::Create( HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, const RECT rc, HMENU hMenu )
{
    return Create( hwndParent, pstrName, dwStyle, dwExStyle, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, hMenu );
}

HWND CWindowWnd::Create( HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, int x, int y, int cx, int cy, HMENU hMenu )
{
    if ( GetSuperClassName() != NULL && !RegisterSuperclass() ) return NULL;
    if ( GetSuperClassName() == NULL && !RegisterWindowClass() ) return NULL;
    m_hWnd = ::CreateWindowEx( dwExStyle, GetWindowClassName(), pstrName, dwStyle, x, y, cx, cy, hwndParent, hMenu, CPaintManagerUI::GetResourceInstance(), this );
    ASSERT( m_hWnd != NULL );
    return m_hWnd;
}

HWND CWindowWnd::Subclass( HWND hWnd )
{
    ASSERT( ::IsWindow( hWnd ) );
    ASSERT( m_hWnd == NULL );
    m_OldWndProc = SubclassWindow( hWnd, __WndProc );
    if ( m_OldWndProc == NULL ) return NULL;
    m_bSubclassed = true;
    m_hWnd = hWnd;
    return m_hWnd;
}

void CWindowWnd::Unsubclass()
{
    ASSERT( ::IsWindow( m_hWnd ) );
    if ( !::IsWindow( m_hWnd ) ) return;
    if ( !m_bSubclassed ) return;
    SubclassWindow( m_hWnd, m_OldWndProc );
    m_OldWndProc = ::DefWindowProc;
    m_bSubclassed = false;
}

void CWindowWnd::ShowWindow( bool bShow /*= true*/, bool bTakeFocus /*= false*/ )
{
    ASSERT( ::IsWindow( m_hWnd ) );
    if ( !::IsWindow( m_hWnd ) ) return;
    ::ShowWindow( m_hWnd, bShow ? ( bTakeFocus ? SW_SHOWNORMAL : SW_SHOWNOACTIVATE ) : SW_HIDE );
}

bool CWindowWnd::ShowModal()
{
    ASSERT( ::IsWindow( m_hWnd ) );
    HWND hWndParent = GetWindowOwner( m_hWnd );
    MSG msg = { 0 };
    while ( ::IsWindow( m_hWnd ) && ::GetMessage( &msg, NULL, 0, 0 ) ) {
        //过滤掉给父窗口的响应消息
        if ( msg.hwnd == hWndParent ) {
            if ( ( msg.message >= WM_MOUSEFIRST && msg.message <= WM_MOUSELAST ) ) continue;
            if ( msg.message >= WM_KEYFIRST && msg.message <= WM_KEYLAST ) continue;
            if ( msg.message == WM_SETCURSOR ) continue;
        }

        if ( !CPaintManagerUI::TranslateMessage( &msg ) ) {
            ::TranslateMessage( &msg );
            ::DispatchMessage( &msg );
        }
        //得到退出消息时，先退出循环，再在后面发送
        if ( msg.message == WM_QUIT ) break;
    }
    if ( msg.message == WM_QUIT ) ::PostQuitMessage( msg.wParam );
    return true;
}

void CWindowWnd::Close()
{
    ASSERT( ::IsWindow( m_hWnd ) );
    if ( !::IsWindow( m_hWnd ) ) return;
    PostMessage( WM_CLOSE );
}

void CWindowWnd::CenterWindow()
{
    ASSERT( ::IsWindow( m_hWnd ) );
    //不是子窗口
    ASSERT( ( GetWindowStyle( m_hWnd )&WS_CHILD ) == 0 );
    RECT rcDlg = { 0 };
    ::GetWindowRect( m_hWnd, &rcDlg );
    RECT rcArea = { 0 };
    RECT rcCenter = { 0 };
    //HWND hWndParent = ::GetParent(m_hWnd);
    HWND hWndCenter = ::GetWindowOwner( m_hWnd );
    //得到屏幕区域
    ::SystemParametersInfo( SPI_GETWORKAREA, NULL, &rcArea, NULL );
    if ( hWndCenter == NULL ) rcCenter = rcArea; else ::GetWindowRect( hWndCenter, &rcCenter );

    int DlgWidth = rcDlg.right - rcDlg.left;
    int DlgHeight = rcDlg.bottom - rcDlg.top;

    // Find dialog's upper left based on rcCenter
    int xLeft = ( rcCenter.left + rcCenter.right ) / 2 - DlgWidth / 2;
    int yTop = ( rcCenter.top + rcCenter.bottom ) / 2 - DlgHeight / 2;

    // The dialog is outside the screen, move it inside
    if ( xLeft < rcArea.left ) xLeft = rcArea.left;
    else if ( xLeft + DlgWidth > rcArea.right ) xLeft = rcArea.right - DlgWidth;
    if ( yTop < rcArea.top ) yTop = rcArea.top;
    else if ( yTop + DlgHeight > rcArea.bottom ) yTop = rcArea.bottom - DlgHeight;
    ::SetWindowPos( m_hWnd, NULL, xLeft, yTop, -1, -1, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE );
}

void CWindowWnd::SetIcon( UINT nRes )
{
    HICON hIcon = ( HICON )::LoadImage( CPaintManagerUI::GetResourceInstance(), MAKEINTRESOURCE( nRes ), IMAGE_ICON, ::GetSystemMetrics( SM_CXICON ), ::GetSystemMetrics( SM_CYICON ), LR_DEFAULTCOLOR );
    ASSERT( hIcon );
    ::SendMessage( m_hWnd, WM_SETICON, ( WPARAM ) TRUE, ( LPARAM ) hIcon );
    hIcon = ( HICON )::LoadImage( CPaintManagerUI::GetResourceInstance(), MAKEINTRESOURCE( nRes ), IMAGE_ICON, ::GetSystemMetrics( SM_CXSMICON ), ::GetSystemMetrics( SM_CYSMICON ), LR_DEFAULTCOLOR );
    ASSERT( hIcon );
    ::SendMessage( m_hWnd, WM_SETICON, ( WPARAM ) FALSE, ( LPARAM ) hIcon );
}

bool CWindowWnd::RegisterWindowClass()
{
    WNDCLASS wc = { 0 };
    wc.style = GetClassStyle();
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hIcon = NULL;
    wc.lpfnWndProc = CWindowWnd::__WndProc;
    wc.hInstance = CPaintManagerUI::GetResourceInstance();
    wc.hCursor = ::LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground = NULL;
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = GetWindowClassName();
    ATOM ret = ::RegisterClass( &wc );
    ASSERT( ret != NULL || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS );
    return ret != NULL || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS;
}

bool CWindowWnd::RegisterSuperclass()
{
    // Get the class information from an existing
    // window so we can subclass it later on...
    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof( WNDCLASSEX );
    if ( !::GetClassInfoEx( NULL, GetSuperClassName(), &wc ) ) {
        //系统获取不到就获取程序注册的
        if ( !::GetClassInfoEx( CPaintManagerUI::GetResourceInstance(), GetSuperClassName(), &wc ) ) {
            ASSERT( !"Unable to locate window class" );
            return NULL;
        }
    }
    m_OldWndProc = wc.lpfnWndProc;
    wc.lpfnWndProc = CWindowWnd::__ControlProc;
    wc.hInstance = CPaintManagerUI::GetResourceInstance();
    wc.lpszClassName = GetWindowClassName();
    ATOM ret = ::RegisterClassEx( &wc );
    ASSERT( ret != NULL || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS );
    return ret != NULL || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS;
}

LRESULT CALLBACK CWindowWnd::__WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    CWindowWnd* pThis = NULL;
    if ( uMsg == WM_NCCREATE ) {
        LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>( lParam );
        pThis = static_cast<CWindowWnd*>( lpcs->lpCreateParams );
        pThis->m_hWnd = hWnd;
        ::SetWindowLongPtr( hWnd, GWLP_USERDATA, reinterpret_cast<LPARAM>( pThis ) );
    }
    else {
        pThis = reinterpret_cast<CWindowWnd*>( ::GetWindowLongPtr( hWnd, GWLP_USERDATA ) );
        if ( uMsg == WM_NCDESTROY && pThis != NULL ) {
            LRESULT lRes = ::CallWindowProc( pThis->m_OldWndProc, hWnd, uMsg, wParam, lParam );
            ::SetWindowLongPtr( pThis->m_hWnd, GWLP_USERDATA, 0L );
            if ( pThis->m_bSubclassed ) pThis->Unsubclass();
            pThis->m_hWnd = NULL;
            pThis->OnFinalMessage( hWnd );
            return lRes;
        }
    }
    if ( pThis != NULL ) {
        return pThis->HandleMessage( uMsg, wParam, lParam );
    }
    else {
        return ::DefWindowProc( hWnd, uMsg, wParam, lParam );
    }
}

LRESULT CALLBACK CWindowWnd::__ControlProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    CWindowWnd* pThis = NULL;
    if ( uMsg == WM_NCCREATE ) {
        LPCREATESTRUCT lpcs = reinterpret_cast<LPCREATESTRUCT>( lParam );
        pThis = static_cast<CWindowWnd*>( lpcs->lpCreateParams );
        ::SetProp( hWnd, _T( "WndX" ), ( HANDLE ) pThis );
        pThis->m_hWnd = hWnd;
    }
    else {
        pThis = reinterpret_cast<CWindowWnd*>( ::GetProp( hWnd, _T( "WndX" ) ) );
        if ( uMsg == WM_NCDESTROY && pThis != NULL ) {
            LRESULT lRes = ::CallWindowProc( pThis->m_OldWndProc, hWnd, uMsg, wParam, lParam );
            if ( pThis->m_bSubclassed ) pThis->Unsubclass();
            ::SetProp( hWnd, _T( "WndX" ), NULL );
            pThis->m_hWnd = NULL;
            pThis->OnFinalMessage( hWnd );
            return lRes;
        }
    }
    if ( pThis != NULL ) {
        return pThis->HandleMessage( uMsg, wParam, lParam );
    }
    else {
        return ::DefWindowProc( hWnd, uMsg, wParam, lParam );
    }

}

LRESULT CWindowWnd::SendMessage( UINT uMsg, WPARAM wParam /*= 0*/, LPARAM lParam /*= 0*/ )
{
    ASSERT( ::IsWindow( m_hWnd ) );
    return ::SendMessage( m_hWnd, uMsg, wParam, lParam );
}

LRESULT CWindowWnd::PostMessage( UINT uMsg, WPARAM wParam /*= 0*/, LPARAM lParam /*= 0*/ )
{
    ASSERT( ::IsWindow( m_hWnd ) );
    return ::PostMessage( m_hWnd, uMsg, wParam, lParam );
}

void CWindowWnd::ResizeClient( int cx /*= -1*/, int cy /*= -1*/ )
{
    ASSERT( ::IsWindow( m_hWnd ) );
    RECT rc = { 0 };
    if ( !::GetClientRect( m_hWnd, &rc ) ) return;
    if ( cx != -1 ) rc.right = cx;
    if ( cy != -1 ) rc.bottom = cy;
    if ( !::AdjustWindowRectEx( &rc, GetWindowStyle( m_hWnd ), ( !( GetWindowStyle( m_hWnd ) & WS_CHILD ) && ( ::GetMenu( m_hWnd ) != NULL ) ), GetWindowExStyle( m_hWnd ) ) ) return;
    UINT uFlags = SWP_NOZORDER | SWP_NOMOVE;
    ::SetWindowPos( m_hWnd, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top, uFlags );
}

LRESULT CWindowWnd::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    return ::CallWindowProc( m_OldWndProc, m_hWnd, uMsg, wParam, lParam );
}

void CWindowWnd::OnFinalMessage( HWND /*hWnd*/ )
{
}

