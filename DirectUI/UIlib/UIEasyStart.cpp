#include "StdAfx.h"
#include "UIEasyStart.h"

void CWindowWndImpl::Notify( TNotifyUI& msg )
{
    if ( msg.sType == _T( "windowinit" ) ) OnPrepare();
    else if ( msg.sType == _T( "click" ) ) {
        const CStdString& sName = msg.pSender->GetName();
        if ( sName == _T( "mixbtn" ) )
            SendMessage( WM_SYSCOMMAND, SC_MINIMIZE );
        else if ( sName == _T( "maxbtn" ) )
            SendMessage( WM_SYSCOMMAND, SC_MAXIMIZE );
        else if ( sName == _T( "restorebtn" ) )
            SendMessage( WM_SYSCOMMAND, SC_RESTORE );
        else if ( sName == _T( "closebtn" ) )
            Close();
    }
}

LRESULT CWindowWndImpl::OnCreate( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
    LONG styleValue = ::GetWindowLong( *this, GWL_STYLE );
    styleValue &= ~WS_CAPTION;
    ::SetWindowLong( *this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN );
    RECT rcClient;
    ::GetClientRect( *this, &rcClient );
    ::SetWindowPos( *this, NULL, rcClient.left, rcClient.top, rcClient.right - rcClient.left, \
                    rcClient.bottom - rcClient.top, SWP_FRAMECHANGED );

    m_pm.Init( m_hWnd );
    CDialogBuilder builder;
    CElementUI* pRoot = builder.Create( GetXmlName(), GetXmlType(), &m_pm );
    ASSERT( pRoot && "Failed to parse XML" );
    m_pm.AttachDialog( pRoot );
    m_pm.AddNotifier( this );

    SIZE szInitWindowSize = m_pm.GetInitSize();
    if ( szInitWindowSize.cx != 0 ) {
        ::SetWindowPos( *this, NULL, 0, 0, szInitWindowSize.cx, szInitWindowSize.cy, SWP_NOZORDER | SWP_NOMOVE );
    }

    Bind();
    Init();
    return 0;
}

LRESULT CWindowWndImpl::OnNcHitTest( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
    POINT pt; pt.x = GET_X_LPARAM( lParam ); pt.y = GET_Y_LPARAM( lParam );
    ::ScreenToClient( *this, &pt );

    RECT rcClient;
    ::GetClientRect( *this, &rcClient );

    if ( !::IsZoomed( *this ) ) {
        RECT rcSizeBox = m_pm.GetSizeBox();
        if ( pt.y < rcClient.top + rcSizeBox.top ) {
            if ( pt.x < rcClient.left + rcSizeBox.left ) return HTTOPLEFT;
            if ( pt.x > rcClient.right - rcSizeBox.right ) return HTTOPRIGHT;
            return HTTOP;
        }
        else if ( pt.y > rcClient.bottom - rcSizeBox.bottom ) {
            if ( pt.x < rcClient.left + rcSizeBox.left ) return HTBOTTOMLEFT;
            if ( pt.x > rcClient.right - rcSizeBox.right ) return HTBOTTOMRIGHT;
            return HTBOTTOM;
        }
        if ( pt.x < rcClient.left + rcSizeBox.left ) return HTLEFT;
        if ( pt.x > rcClient.right - rcSizeBox.right ) return HTRIGHT;
    }

    RECT rcCaption = m_pm.GetCaptionRect();
    if ( pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
            && pt.y >= rcCaption.top && pt.y < rcCaption.bottom ) {
        CElementUI* pControl = m_pm.FindControl( pt );
        if ( pControl && ( _tcscmp( pControl->GetClass(), _T( "LabelUI" ) ) == 0 || _tcscmp( pControl->GetClass(), _T( "ControlUI" ) ) == 0
                           || pControl->GetInterface( _T( "IContainer" ) ) != NULL ) )
            return HTCAPTION;
    }

    return HTCLIENT;
}
LRESULT CWindowWndImpl::OnSize( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
    //设定圆角，默认4个角
    RECT szRoundCorner = m_pm.GetRoundCorner();
    //     if ( !::IsIconic( *this ) && ( szRoundCorner.cx != 0 || szRoundCorner.cy != 0 ) ) {
    //         RECT rcClient;
    //         ::GetClientRect( *this, &rcClient );
    //         HRGN hRgn =::CreateRoundRectRgn( rcClient.left, rcClient.top, rcClient.right + 1 , rcClient.bottom + 1 , szRoundCorner.cx, szRoundCorner.cy );
    //         ::SetWindowRgn( *this, hRgn, TRUE );
    //         ::DeleteObject( hRgn );
    //     }

    bHandled = FALSE;
    return 0;
}
LRESULT CWindowWndImpl::OnGetMinMaxInfo( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
    //设定最大化
    MONITORINFO oMonitor = {0};
    oMonitor.cbSize = sizeof( oMonitor );
    ::GetMonitorInfo( ::MonitorFromWindow( *this, MONITOR_DEFAULTTOPRIMARY ), &oMonitor );
    CRect rcWork = oMonitor.rcWork;
    rcWork.Offset( -rcWork.left, -rcWork.top );

    LPMINMAXINFO lpMMI = ( LPMINMAXINFO ) lParam;
    lpMMI->ptMaxPosition.x	= rcWork.left;
    lpMMI->ptMaxPosition.y	= rcWork.top;
    lpMMI->ptMaxSize.x		= rcWork.right;
    lpMMI->ptMaxSize.y		= rcWork.bottom;

    bHandled = FALSE;
    return 0;
}
LRESULT CWindowWndImpl::OnSysCommand( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
    //交换最大化和还原
    BOOL bZoomed = ::IsZoomed( *this );
    LRESULT lRes = CWindowWnd::HandleMessage( uMsg, wParam, lParam );
    if ( ::IsZoomed( *this ) != bZoomed ) {
        if ( !bZoomed ) {
            CElementUI* pControl = m_pm.FindControl( _T( "maxbtn" ) );
            if ( pControl ) pControl->SetVisible( false );
            pControl = m_pm.FindControl( _T( "restorebtn" ) );
            if ( pControl ) pControl->SetVisible( true );
        }
        else {
            CElementUI* pControl = m_pm.FindControl( _T( "maxbtn" ) );
            if ( pControl ) pControl->SetVisible( true );
            pControl = m_pm.FindControl( _T( "restorebtn" ) );
            if ( pControl ) pControl->SetVisible( false );
        }
    }
    return lRes;
}
