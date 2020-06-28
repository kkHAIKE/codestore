
#include "StdAfx.h"
#include "UIManager.h"


/////////////////////////////////////////////////////////////////////////////////////
//
//

static UINT MapKeyState()
{
    UINT uState = 0;
    if ( ::GetKeyState( VK_CONTROL ) < 0 ) uState |= MK_CONTROL;
    if ( ::GetKeyState( VK_RBUTTON ) < 0 ) uState |= MK_LBUTTON;
    if ( ::GetKeyState( VK_LBUTTON ) < 0 ) uState |= MK_RBUTTON;
    if ( ::GetKeyState( VK_SHIFT ) < 0 ) uState |= MK_SHIFT;
    if ( ::GetKeyState( VK_MENU ) < 0 ) uState |= MK_ALT;
    return uState;
}

/////////////////////////////////////////////////////////////////////////////////////

HINSTANCE CPaintManagerUI::m_hInstance = NULL;
//HINSTANCE CPaintManagerUI::m_hLangInst = NULL;
CStdPtrArray<CPaintManagerUI> CPaintManagerUI::m_aPreMessages;


CPaintManagerUI::CPaintManagerUI() :
    m_hWndPaint( NULL ),
    m_hDcPaint( NULL ),
    m_hDcOffscreen( NULL ),
    m_hbmpOffscreen( NULL ),
    m_hwndTooltip( NULL ),
    m_bShowUpdateRect( false ),
    m_uTimerID( 0x1000 ),
    m_pRoot( NULL ),
    m_pFocus( NULL ),
    m_pEventHover( NULL ),
    m_pEventClick( NULL ),
    m_pEventKey( NULL ),
    m_bFirstLayout( true ),
    m_bFocusNeeded( false ),
    m_bUpdateNeeded( false ),
    m_bMouseTracking( false ),
    m_bMouseCapture( false ),
    m_bOffscreenPaint( true ),
    m_pParentResourcePM( NULL ),
    m_pFocusBackup( NULL )
{
    m_dwDefalutDisabledColor = 0xFFA7A6AA;
    LOGFONT lf = { 0 };
    ::GetObject( ::GetStockObject( DEFAULT_GUI_FONT ), sizeof( LOGFONT ), &lf );
    lf.lfHeight = -12;
    m_hDefalutFont = ::CreateFontIndirect( &lf );
    m_dwDefalutFontColor = 0xFF000000;
    ::ZeroMemory( &m_hDefalutFontTextMetric, sizeof( m_hDefalutFontTextMetric ) );

    lf.lfUnderline = TRUE;
    m_hDefalutLinkFont = ::CreateFontIndirect( &lf );
    m_dwDefalutLinkFontColor = 0xFF0000FF;
    m_dwDefalutLinkFontHoverColor = 0xFFD3215F;
    ::ZeroMemory( &m_hDefaluttBoldFontTextMetric, sizeof( m_hDefaluttBoldFontTextMetric ) );

    lf.lfUnderline = FALSE;
    lf.lfWeight += FW_BOLD;
    m_hDefalutBoldFont = ::CreateFontIndirect( &lf );
    ::ZeroMemory( &m_hDefalutLinkFontTextMetric, sizeof( m_hDefalutLinkFontTextMetric ) );

    // Boot Windows Common Controls (for the ToolTip control)
    //::InitCommonControls();

    m_szMinWindow.cx = m_szMinWindow.cy = 0;
    m_szInitWindowSize.cx = m_szInitWindowSize.cy = 0;
    m_ptLastMousePos.x = m_ptLastMousePos.y = -1;

    ::ZeroMemory( &m_rcSizeBox, sizeof( m_rcSizeBox ) );
    ::ZeroMemory( &m_rcCaption, sizeof( m_rcCaption ) );
    ::ZeroMemory( &m_ToolTip, sizeof( m_ToolTip ) );
    ::ZeroMemory( &m_szRoundCorner, sizeof( m_szRoundCorner ) );
}

CPaintManagerUI::~CPaintManagerUI()
{
    // Delete the control-tree structures
    m_aDelayedCleanup.Resize_Delete( 0 );

    for ( int i = 0; i < m_aTimers.GetSize(); ++i ) {
        TIMERINFO* pTimer = m_aTimers[i];
        if ( pTimer->bKilled == false ) {
            KillTimer( pTimer->pSender, pTimer->nLocalID );
        }

        delete pTimer;
    }

    delete m_pRoot;

    ::DeleteObject( m_hDefalutFont );
    ::DeleteObject( m_hDefalutBoldFont );
    ::DeleteObject( m_hDefalutLinkFont );

    RemoveAllFonts();
    RemoveAllImages();
    RemoveAllDefaultAttributeList();

    // Reset other parts...
    if ( m_hwndTooltip != NULL ) ::DestroyWindow( m_hwndTooltip );
    if ( m_hDcOffscreen != NULL ) {
        m_hDcOffscreen->SetHDCmode();
        HDC hDcOffscreen = *m_hDcOffscreen;
        delete m_hDcOffscreen;
        ::DeleteDC( hDcOffscreen );
    }
    if ( m_hbmpOffscreen != NULL ) ::DeleteObject( m_hbmpOffscreen );
    if ( m_hDcPaint != NULL ) {
        m_hDcPaint->SetHDCmode();
        HDC hDcPaint = *m_hDcPaint;
        delete m_hDcPaint;
        ::ReleaseDC( m_hWndPaint, hDcPaint );
    }

    m_aPreMessages.Remove( m_aPreMessages.Find( this ) );
}

void CPaintManagerUI::Init( HWND hWnd )
{
    ASSERT( ::IsWindow( hWnd ) );
    // Remember the window context we came from
    m_hWndPaint = hWnd;
    m_hDcPaint = new GRAPHorHDC( ::GetDC( hWnd ) );

    // We'll want to filter messages globally too
    m_aPreMessages.Add( this );
}
HINSTANCE CPaintManagerUI::GetResourceInstance()
{
    return m_hInstance;
}
//
// HINSTANCE CPaintManagerUI::GetLanguageInstance()
// {
//     return m_hLangInst;
// }

void CPaintManagerUI::SetResourceInstance( HINSTANCE hInst )
{
    m_hInstance = hInst;
    //   if ( m_hLangInst == NULL ) m_hLangInst = hInst;

    // 	INITCOMMONCONTROLSEX initex={sizeof(INITCOMMONCONTROLSEX),ICC_WIN95_CLASSES};
    // 	::InitCommonControlsEx(&initex);
    ::InitCommonControls();
}

// void CPaintManagerUI::SetLanguageInstance( HINSTANCE hInst )
// {
//     m_hLangInst = hInst;
// }

HWND CPaintManagerUI::GetPaintWindow() const
{
    return m_hWndPaint;
}
GRAPHorHDC* CPaintManagerUI::GetPaintDC() const
{
    return m_hDcPaint;
}
POINT CPaintManagerUI::GetMousePos() const
{
    return m_ptLastMousePos;
}

SIZE CPaintManagerUI::GetClientSize() const
{
    RECT rcClient = { 0 };
    ::GetClientRect( m_hWndPaint, &rcClient );
    return CSize( rcClient.right - rcClient.left, rcClient.bottom - rcClient.top );
}

SIZE CPaintManagerUI::GetInitSize() const
{
    return m_szInitWindowSize;
}

void CPaintManagerUI::SetInitSize( int cx, int cy )
{
    m_szInitWindowSize.cx = cx;
    m_szInitWindowSize.cy = cy;
}

const RECT& CPaintManagerUI::GetSizeBox() const
{
    return m_rcSizeBox;
}

void CPaintManagerUI::SetSizeBox( const RECT& rcSizeBox )
{
    m_rcSizeBox = rcSizeBox;
}

const RECT& CPaintManagerUI::GetCaptionRect() const
{
    return m_rcCaption;
}

void CPaintManagerUI::SetCaptionRect( const RECT& rcCaption )
{
    m_rcCaption = rcCaption;
}

RECT CPaintManagerUI::GetRoundCorner() const
{
    return m_szRoundCorner;
}

void CPaintManagerUI::SetRoundCorner( const RECT& rcRoundCorner )
{
    m_szRoundCorner = rcRoundCorner;
}

void CPaintManagerUI::SetMinMaxInfo( int cx, int cy )
{
    ASSERT( cx >= 0 && cy >= 0 );
    m_szMinWindow.cx = cx;
    m_szMinWindow.cy = cy;
}

void CPaintManagerUI::SetShowUpdateRect( bool show )
{
    m_bShowUpdateRect = show;
}

bool CPaintManagerUI::PreMessageHandler( UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& /*lRes*/ )
{
    switch ( uMsg ) {
    case WM_KEYDOWN: {
            // Tabbing between controls
            if ( wParam == VK_TAB ) {
                SetNextTabControl( ::GetKeyState( VK_SHIFT ) >= 0 );
                return true;
            }
            // Handle default dialog controls OK and CANCEL.
            // If there are controls named "ok" or "cancel" they
            // will be activated on keypress.
            if ( wParam == VK_RETURN ) {
                CElementUI* pControl = FindControl( _T( "ok" ) );
                if ( pControl != NULL && m_pFocus != pControl ) {
                    //如果当前控件不接受回车则激活默认ok
                    if ( m_pFocus == NULL || ( m_pFocus->GetControlFlags() & UIFLAG_WANTRETURN ) == 0 ) {
                        pControl->Activate();
                        return true;
                    }
                }
            }
            if ( wParam == VK_ESCAPE ) {
                CElementUI* pControl = FindControl( _T( "cancel" ) );
                if ( pControl != NULL ) {
                    pControl->Activate();
                    return true;
                }
            }
        }
        break;
    case WM_SYSCHAR: {
            // Handle ALT-shortcut key-combinations
            FINDSHORTCUT fs = { 0 };
            fs.ch = toupper( ( int )wParam );
            CElementUI* pControl = m_pRoot->FindControl( __FindControlFromShortcut, &fs, UIFIND_ENABLED | UIFIND_ME_FIRST | UIFIND_TOP_FIRST | UIFIND_CAN_FOCUS );
            if ( pControl != NULL ) {
                pControl->SetFocus();
                pControl->Activate();
                return true;
            }
        }
        break;
    case WM_SYSKEYDOWN: {
            if ( m_pFocus != NULL ) {
                TEventUI event = { 0 };
                event.Type = UIEVENT_SYSKEY;
                event.chKey = ( TCHAR )wParam;
                event.ptMouse = m_ptLastMousePos;
                event.wKeyState = MapKeyState();
                event.dwTimestamp = ::GetTickCount();
                m_pFocus->Event( event );
            }
        }
        break;
    }
    return false;
}

bool CPaintManagerUI::MessageHandler( UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes )
{
    // Not ready yet?
    if ( m_hWndPaint == NULL ) return false;
    // Cycle through listeners
    for ( int i = 0; i < m_aMessageFilters.GetSize(); ++i ) {
        bool bHandled = false;
        LRESULT lResult = m_aMessageFilters[i]->MessageHandler( uMsg, wParam, lParam, bHandled );
        if ( bHandled ) {
            lRes = lResult;
            return true;
        }
    }
    // Custom handling of events
    switch ( uMsg ) {
    case UIMES_DELAYCLEAR: {
            // Delayed control-tree cleanup. See AttachDialog() for details.
            m_aDelayedCleanup.Resize_Delete( 0 );
        }
        break;
    case WM_SETFOCUS: {
            //if(wParam==NULL)
            if ( m_pFocusBackup ) {
                SetFocus( m_pFocusBackup );
                m_pFocusBackup = NULL;
            }
        }
        break;
    case WM_KILLFOCUS: {
            if ( wParam == NULL ) {
                TEventUI event = { 0 };
                event.ptMouse = m_ptLastMousePos;
                event.dwTimestamp = ::GetTickCount();
                if ( m_pEventHover != NULL ) {
                    event.Type = UIEVENT_MOUSELEAVE;
                    event.pSender = m_pEventHover;
                    m_pEventHover->Event( event );
                }
                if ( m_pEventClick != NULL ) {
                    event.Type = UIEVENT_BUTTONUP;
                    event.pSender = m_pEventClick;
                    m_pEventClick->Event( event );
                }
                if ( m_pEventKey != NULL ) {
                    event.Type = UIEVENT_KEYUP;
                    event.pSender = m_pEventKey;
                    m_pEventKey->Event( event );
                }

                m_pFocusBackup = m_pFocus;
                SetFocus( NULL );
            }
        }
        break;
    case WM_CLOSE: {
            // Make sure all matching "closing" events are sent
            //在关闭前结束所有准备型事件
            TEventUI event = { 0 };
            event.ptMouse = m_ptLastMousePos;
            event.dwTimestamp = ::GetTickCount();
            if ( m_pEventHover != NULL ) {
                event.Type = UIEVENT_MOUSELEAVE;
                event.pSender = m_pEventHover;
                m_pEventHover->Event( event );
            }
            if ( m_pEventClick != NULL ) {
                event.Type = UIEVENT_BUTTONUP;
                event.pSender = m_pEventClick;
                m_pEventClick->Event( event );
            }
            if ( m_pEventKey != NULL ) {
                event.Type = UIEVENT_KEYUP;
                event.pSender = m_pEventKey;
                m_pEventKey->Event( event );
            }
            //取消焦点
            SetFocus( NULL );

            // Hmmph, the usual Windows tricks to avoid
            // focus loss...
            HWND hwndParent = GetWindowOwner( m_hWndPaint );
            if ( hwndParent != NULL ) ::SetFocus( hwndParent );
        }
        break;
    case WM_ERASEBKGND: {
            // We'll do the painting here...
            lRes = 1;
        }
        return true;
    case WM_PAINT: {
            // Should we paint?
            RECT rcPaint = { 0 };
            if ( !::GetUpdateRect( m_hWndPaint, &rcPaint, FALSE ) ) return true;
            // Do we need to resize anything?
            // This is the time where we layout the controls on the form.
            // We delay this even from the WM_SIZE messages since resizing can be
            // a very expensize operation.
            if ( m_bUpdateNeeded ) {
                m_bUpdateNeeded = false;
                RECT rcClient = { 0 };
                ::GetClientRect( m_hWndPaint, &rcClient );
                if ( !::IsRectEmpty( &rcClient ) ) {
                    if ( m_pRoot->IsUpdateNeeded() ) {
                        m_pRoot->SetPos( rcClient );
                        //重置离屏句柄
                        if ( m_hDcOffscreen != NULL ) {
                            m_hDcOffscreen->SetHDCmode();
                            HDC hDcOffscreen = *m_hDcOffscreen;
                            delete m_hDcOffscreen;
                            ::DeleteDC( hDcOffscreen );
                        }
                        if ( m_hbmpOffscreen != NULL ) ::DeleteObject( m_hbmpOffscreen );
                        m_hDcOffscreen = NULL;
                        m_hbmpOffscreen = NULL;
                    }
                    else {
                        CElementUI* pControl = NULL;
                        while ( pControl = m_pRoot->FindControl( __FindControlFromUpdate, NULL, UIFIND_VISIBLE | UIFIND_ME_FIRST ) ) {
                            pControl->SetPos( pControl->GetPos() );
                        }
                    }
                    // We'll want to notify the window when it is first initialized
                    // with the correct layout. The window form would take the time
                    // to submit swipes/animations.
                    if ( m_bFirstLayout ) {
                        m_bFirstLayout = false;
                        SendNotify( m_pRoot, _T( "windowinit" ) );
                    }
                }
            }
            // Set focus to first control?
            if ( m_bFocusNeeded ) {
                SetNextTabControl();
            }
            //
            // Render screen
            //
            // Prepare offscreen bitmap?
            //初始化离屏句柄
            if ( m_bOffscreenPaint && m_hbmpOffscreen == NULL ) {
                RECT rcClient = { 0 };
                ::GetClientRect( m_hWndPaint, &rcClient );
                HDC hDcOffscreen = ::CreateCompatibleDC( *m_hDcPaint );
                m_hbmpOffscreen = ::CreateCompatibleBitmap( *m_hDcPaint, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top );
                ASSERT( hDcOffscreen );
                ASSERT( m_hbmpOffscreen );
                ::SelectObject( hDcOffscreen, m_hbmpOffscreen );
                m_hDcOffscreen = new GRAPHorHDC( hDcOffscreen );
            }
            // Begin Windows paint
            PAINTSTRUCT ps = { 0 };
            ::BeginPaint( m_hWndPaint, &ps );
            if ( m_bOffscreenPaint ) {

                m_hDcOffscreen->SetHDCmode();
                // We have an offscreen device to paint on for flickerfree(无闪烁) display.
                //HBITMAP hOldBitmap = ( HBITMAP ) ::SelectObject( gorh, m_hbmpOffscreen );
                // Paint the image on the offscreen bitmap
                //int iSaveDC = ::SaveDC( gorh );
                m_pRoot->DoPaint( *m_hDcOffscreen, ps.rcPaint );
                //::RestoreDC( gorh, iSaveDC );

                //采用Post绘制的可以直接绘制在最高层
                for ( int i = 0; i < m_aPostPaintControls.GetSize(); ++i ) {
                    m_aPostPaintControls[i]->DoPostPaint( *m_hDcOffscreen, ps.rcPaint );
                }

                // Blit offscreen bitmap back to display
                ::BitBlt( ps.hdc,
                          ps.rcPaint.left,
                          ps.rcPaint.top,
                          ps.rcPaint.right - ps.rcPaint.left,
                          ps.rcPaint.bottom - ps.rcPaint.top,
                          *m_hDcOffscreen,
                          ps.rcPaint.left,
                          ps.rcPaint.top,
                          SRCCOPY );
                //::SelectObject( gorh, hOldBitmap );
            }
            else {
                // A standard paint job
                //int iSaveDC = ::SaveDC( ps.hdc );
                m_pRoot->DoPaint(  GRAPHorHDC( ps.hdc ), ps.rcPaint );
                //::RestoreDC( ps.hdc, iSaveDC );
            }
            //显示更新的框
            if ( m_bShowUpdateRect ) {
                CRenderEngine::DrawRect( GRAPHorHDC( ps.hdc ), rcPaint, 1, RGB( 220, 0, 0 ) );
            }
            // All Done!
            ::EndPaint( m_hWndPaint, &ps );
        }
        // If any of the painting requested a resize again, we'll need
        // to invalidate the entire window once more.
        if ( m_bUpdateNeeded ) {
            ::InvalidateRect( m_hWndPaint, NULL, FALSE );
        }
        return true;
    case WM_PRINTCLIENT: {
            RECT rcClient;
            ::GetClientRect( m_hWndPaint, &rcClient );
            HDC hDC = ( HDC ) wParam;
            //int save = ::SaveDC( hDC );
            m_pRoot->DoPaint( GRAPHorHDC ( hDC ), rcClient );
            // Check for traversing children. The crux(难题) is that WM_PRINT will assume
            // that the DC is positioned at frame coordinates(坐标) and will paint the child
            // control at the wrong position. We'll simulate the entire thing instead.
            if ( ( lParam & PRF_CHILDREN ) != 0 ) {
                HWND hWndChild = ::GetWindow( m_hWndPaint, GW_CHILD );
                while ( hWndChild != NULL ) {
                    RECT rcPos = { 0 };
                    ::GetWindowRect( hWndChild, &rcPos );
                    ::MapWindowPoints( HWND_DESKTOP, m_hWndPaint, reinterpret_cast<LPPOINT>( &rcPos ), 2 );
                    ::SetWindowOrgEx( hDC, -rcPos.left, -rcPos.top, NULL );
                    // NOTE: We use WM_PRINT here rather than the expected WM_PRINTCLIENT
                    //       since the latter will not print the nonclient correctly for
                    //       EDIT controls.
                    ::SendMessage( hWndChild, WM_PRINT, wParam, lParam | PRF_NONCLIENT );
                    hWndChild = ::GetWindow( hWndChild, GW_HWNDNEXT );
                }
            }
            //::RestoreDC( hDC, save );
        }
        break;
    case WM_GETMINMAXINFO: {
            LPMINMAXINFO lpMMI = ( LPMINMAXINFO ) lParam;
            lpMMI->ptMinTrackSize.x = m_szMinWindow.cx;
            lpMMI->ptMinTrackSize.y = m_szMinWindow.cy;
        }
        break;
    case WM_SIZE:
        //       if ( wParam != SIZE_MINIMIZED ) {
        if ( m_pFocus != NULL ) {
            TEventUI event = { 0 };
            event.Type = UIEVENT_WINDOWSIZE;
            event.dwTimestamp = ::GetTickCount();
            m_pFocus->Event( event );
        }

        m_pRoot->NeedUpdate( true );
        //         }
        //         else {
        //             TEventUI event = { 0 };
        //             event.ptMouse = m_ptLastMousePos;
        //             event.dwTimestamp = ::GetTickCount();
        //             if ( m_pEventHover != NULL ) {
        //                 event.Type = UIEVENT_MOUSELEAVE;
        //                 event.pSender = m_pEventHover;
        //                 m_pEventHover->Event( event );
        //             }
        //             if ( m_pEventClick != NULL ) {
        //                 event.Type = UIEVENT_BUTTONUP;
        //                 event.pSender = m_pEventClick;
        //                 m_pEventClick->Event( event );
        //             }
        //             if ( m_pEventKey != NULL ) {
        //                 event.Type = UIEVENT_KEYUP;
        //                 event.pSender = m_pEventKey;
        //                 m_pEventKey->Event( event );
        //             }
        //         }
        return true;
    case WM_TIMER: {
            for ( int i = 0; i < m_aTimers.GetSize(); ++i ) {
                const TIMERINFO* pTimer = m_aTimers[i];
                if ( pTimer->hWnd == m_hWndPaint && pTimer->uWinTimer == LOWORD( wParam ) && pTimer->bKilled == false ) {
                    TEventUI event = { 0 };
                    event.Type = UIEVENT_TIMER;
                    event.wParam = pTimer->nLocalID;
                    event.dwTimestamp = ::GetTickCount();
                    pTimer->pSender->Event( event );
                    break;
                }
            }
        }
        break;
    case WM_MOUSEHOVER: {
            m_bMouseTracking = false;
            POINT pt = { GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) };
            CElementUI* pHover = FindControl( pt );
            if ( pHover == NULL ) break;
            // Generate mouse hover event
            if ( m_pEventHover != NULL ) {
                TEventUI event = { 0 };
                event.ptMouse = pt;
                event.Type = UIEVENT_MOUSEHOVER;
                event.pSender = pHover;
                event.dwTimestamp = ::GetTickCount();
                m_pEventHover->Event( event );
            }
            // Create tooltip information
            CStdString sToolTip = pHover->GetToolTip();
            if ( sToolTip.IsEmpty() ) return true;
            ::ZeroMemory( &m_ToolTip, sizeof( TOOLINFO ) );
            m_ToolTip.cbSize = sizeof( TOOLINFO );
            m_ToolTip.uFlags = TTF_IDISHWND;
            m_ToolTip.hwnd = m_hWndPaint;
            m_ToolTip.uId = ( UINT_PTR ) m_hWndPaint;
            m_ToolTip.hinst = m_hInstance;
            m_ToolTip.lpszText = const_cast<LPTSTR>( ( LPCTSTR ) sToolTip );
            m_ToolTip.rect = pHover->GetPos();
            if ( m_hwndTooltip == NULL ) {
                m_hwndTooltip = ::CreateWindowEx( 0, TOOLTIPS_CLASS, NULL, WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, m_hWndPaint, NULL, m_hInstance, NULL );
                ::SendMessage( m_hwndTooltip, TTM_ADDTOOL, 0, ( LPARAM ) &m_ToolTip );
            }
            ::SendMessage( m_hwndTooltip, TTM_SETTOOLINFO, 0, ( LPARAM ) &m_ToolTip );
            ::SendMessage( m_hwndTooltip, TTM_TRACKACTIVATE, TRUE, ( LPARAM ) &m_ToolTip );
        }
        return true;
    case WM_MOUSELEAVE: {
            if ( m_hwndTooltip != NULL ) ::SendMessage( m_hwndTooltip, TTM_TRACKACTIVATE, FALSE, ( LPARAM ) &m_ToolTip );
            if ( m_bMouseTracking ) ::SendMessage( m_hWndPaint, WM_MOUSEMOVE, 0, ( LPARAM ) - 1 );
            m_bMouseTracking = false;
        }
        break;
    case WM_MOUSEMOVE: {
            // Start tracking this entire window again...
            if ( !m_bMouseTracking ) {
                TRACKMOUSEEVENT tme = { 0 };
                tme.cbSize = sizeof( TRACKMOUSEEVENT );
                tme.dwFlags = TME_HOVER | TME_LEAVE;
                tme.hwndTrack = m_hWndPaint;
                tme.dwHoverTime = m_hwndTooltip == NULL ? 1000UL : static_cast<DWORD>( ::SendMessage( m_hwndTooltip, TTM_GETDELAYTIME, TTDT_INITIAL, 0L ) );
                //调用这个函数开启离开悬停支持
                _TrackMouseEvent( &tme );
                m_bMouseTracking = true;
            }
            // Generate the appropriate mouse messages
            POINT pt = { GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) };
            m_ptLastMousePos = pt;
            CElementUI* pNewHover = FindControl( pt );
            if ( pNewHover != NULL && pNewHover->GetManager() != this ) break;
            TEventUI event = { 0 };
            event.ptMouse = pt;
            event.dwTimestamp = ::GetTickCount();
            if ( pNewHover != m_pEventHover && m_pEventHover != NULL ) {
                event.Type = UIEVENT_MOUSELEAVE;
                event.pSender = pNewHover;
                m_pEventHover->Event( event );
                m_pEventHover = NULL;
                if ( m_hwndTooltip != NULL ) ::SendMessage( m_hwndTooltip, TTM_TRACKACTIVATE, FALSE, ( LPARAM ) &m_ToolTip );
            }
            if ( pNewHover != m_pEventHover && pNewHover != NULL ) {
                event.Type = UIEVENT_MOUSEENTER;
                event.pSender = m_pEventHover;
                pNewHover->Event( event );
                m_pEventHover = pNewHover;
            }
            if ( m_pEventClick != NULL ) {
                event.Type = UIEVENT_MOUSEMOVE;
                event.pSender = NULL;
                m_pEventClick->Event( event );
            }
            else if ( pNewHover != NULL ) {
                event.Type = UIEVENT_MOUSEMOVE;
                event.pSender = NULL;
                pNewHover->Event( event );
            }
        }
        break;
    case WM_LBUTTONDOWN: {
            // We alway set focus back to our app (this helps
            // when Win32 child windows are placed on the dialog
            // and we need to remove them on focus change).
            //::SetFocus( m_hWndPaint );
            POINT pt = { GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) };
            m_ptLastMousePos = pt;
            CElementUI* pControl = FindControl( pt );
            if ( pControl == NULL || pControl->GetManager() != this ) break;
            m_pEventClick = pControl;
            pControl->SetFocus();
            SetCapture();
            // We always capture the mouse
            TEventUI event = { 0 };
            event.Type = UIEVENT_BUTTONDOWN;
            event.wParam = wParam;
            event.lParam = lParam;
            event.ptMouse = pt;
            event.wKeyState = ( WORD )wParam;
            event.dwTimestamp = ::GetTickCount();
            pControl->Event( event );
        }
        break;
    case WM_LBUTTONUP: {
            POINT pt = { GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) };
            m_ptLastMousePos = pt;
            if ( m_pEventClick == NULL ) break;
            ReleaseCapture();
            TEventUI event = { 0 };
            event.Type = UIEVENT_BUTTONUP;
            event.wParam = wParam;
            event.lParam = lParam;
            event.ptMouse = pt;
            event.wKeyState = ( WORD )wParam;
            event.dwTimestamp = ::GetTickCount();
            m_pEventClick->Event( event );
            m_pEventClick = NULL;
        }
        break;
    case WM_LBUTTONDBLCLK: {
            POINT pt = { GET_X_LPARAM( lParam ), GET_Y_LPARAM( lParam ) };
            m_ptLastMousePos = pt;
            CElementUI* pControl = FindControl( pt );
            if ( pControl == NULL || pControl->GetManager() != this ) break;
            // We always capture the mouse
            m_pEventClick = pControl;
            SetCapture();
            TEventUI event = { 0 };
            event.Type = UIEVENT_DBLCLICK;
            event.ptMouse = pt;
            event.wKeyState = ( WORD )wParam;
            event.dwTimestamp = ::GetTickCount();
            pControl->Event( event );
        }
        break;
    case WM_CHAR: {
            if ( m_pFocus == NULL ) break;
            TEventUI event = { 0 };
            event.Type = UIEVENT_CHAR;
            event.chKey = ( TCHAR )wParam;
            event.ptMouse = m_ptLastMousePos;
            event.wKeyState = MapKeyState();
            event.dwTimestamp = ::GetTickCount();
            m_pFocus->Event( event );
        }
        break;
    case WM_KEYDOWN: {
            if ( m_pFocus == NULL ) break;
            TEventUI event = { 0 };
            event.Type = UIEVENT_KEYDOWN;
            event.chKey = ( TCHAR )wParam;
            event.ptMouse = m_ptLastMousePos;
            event.wKeyState = MapKeyState();
            event.dwTimestamp = ::GetTickCount();
            m_pFocus->Event( event );
            m_pEventKey = m_pFocus;
        }
        break;
    case WM_KEYUP: {
            if ( m_pEventKey == NULL ) break;
            TEventUI event = { 0 };
            event.Type = UIEVENT_KEYUP;
            event.chKey = ( TCHAR )wParam;
            event.ptMouse = m_ptLastMousePos;
            event.wKeyState = MapKeyState();
            event.dwTimestamp = ::GetTickCount();
            m_pEventKey->Event( event );
            m_pEventKey = NULL;
        }
        break;
    case WM_SETCURSOR: {
            if ( LOWORD( lParam ) != HTCLIENT ) break;
            if ( m_bMouseCapture ) return true;

            POINT pt = { 0 };
            ::GetCursorPos( &pt );
            ::ScreenToClient( m_hWndPaint, &pt );
            CElementUI* pControl = FindControl( pt );
            if ( pControl == NULL ) break;
            if ( ( pControl->GetControlFlags() & UIFLAG_SETCURSOR ) == 0 ) break;
            TEventUI event = { 0 };
            event.Type = UIEVENT_SETCURSOR;
            event.wParam = wParam;
            event.lParam = lParam;
            event.ptMouse = pt;
            event.wKeyState = MapKeyState();
            event.dwTimestamp = ::GetTickCount();
            pControl->Event( event );
        }
        return true;
        //message is sent to the owner window of a combo box, list box, list view control,
        //or menu item when the control or menu is created.

    case WM_MEASUREITEM: {
            if ( wParam == 0 ) break;
            HWND hWndChild = ::GetDlgItem( m_hWndPaint, ( ( LPMEASUREITEMSTRUCT ) lParam )->CtlID );
            lRes = ::SendMessage( hWndChild, OCM__BASE + uMsg, wParam, lParam );
            return true;
        }
        break;
    case WM_DRAWITEM: {
            if ( wParam == 0 ) break;
            HWND hWndChild = ( ( LPDRAWITEMSTRUCT ) lParam )->hwndItem;
            lRes = ::SendMessage( hWndChild, OCM__BASE + uMsg, wParam, lParam );
            return true;
        }
        break;
    case WM_NOTIFY: {
            LPNMHDR lpNMHDR = ( LPNMHDR ) lParam;
            if ( lpNMHDR != NULL ) lRes = ::SendMessage( lpNMHDR->hwndFrom, OCM__BASE + uMsg, wParam, lParam );
            return true;
        }
        break;
    case WM_COMMAND:
    case WM_CTLCOLOREDIT: {
            if ( lParam == 0 ) break;
            HWND hWndChild = ( HWND ) lParam;
            lRes = ::SendMessage( hWndChild, OCM__BASE + uMsg, wParam, lParam );
            return true;
        }
        break;
    case WM_MOUSEWHEEL:
        if ( m_pFocus && m_pFocus->IsEnabled() ) {
            //尝试解除滚轮问题
            //             if ( _tcscmp( m_pFocus->GetClass(), _T( "ActiveXUI" ) ) == 0 )
            //                 break;

            int zDelta = ( int ) ( short ) HIWORD( wParam );
            TEventUI event = { 0 };
            event.Type = UIEVENT_SCROLLWHEEL;
            event.wParam = MAKEWPARAM( zDelta < 0 ? SB_LINEDOWN : SB_LINEUP, 0 );
            event.lParam = lParam;
            event.dwTimestamp = ::GetTickCount();
            m_pFocus->Event( event );

            // Let's make sure that the scroll item below the cursor is the same as before...
            //为什么要发个移动消息
            ::SendMessage( m_hWndPaint, WM_MOUSEMOVE, 0, ( LPARAM ) MAKELPARAM( m_ptLastMousePos.x, m_ptLastMousePos.y ) );
        }
        break;
        //     default:
        //         if ( uMsg == WM_MOUSEWHEEL && m_pFocus != NULL ) {
        //
        //         }
        //         break;
    }
    return false;
}

void CPaintManagerUI::NeedUpdate()
{
    m_bUpdateNeeded = true;
}

void CPaintManagerUI::Invalidate( const RECT& rcItem )
{
    ::InvalidateRect( m_hWndPaint, &rcItem, FALSE );
}

bool CPaintManagerUI::AttachDialog( CElementUI* pControl )
{
    ASSERT( ::IsWindow( m_hWndPaint ) );
    // Reset any previous attachment
    SetFocus( NULL );
    m_pEventKey = NULL;
    m_pEventHover = NULL;
    m_pEventClick = NULL;
    // Remove the existing control-tree. We might have gotten inside this function as
    // a result of an event fired or similar, so we cannot just delete the objects and
    // pull the internal memory of the calling code. We'll delay the cleanup.
    if ( m_pRoot != NULL ) {
        m_aPostPaintControls.Empty();
        m_aDelayedCleanup.Add( m_pRoot );
        ::PostMessage( m_hWndPaint, UIMES_DELAYCLEAR, 0L, 0L );
    }
    // Set the dialog root element
    m_pRoot = pControl;
    // Go ahead...
    m_bUpdateNeeded = true;
    m_bFirstLayout = true;
    m_bFocusNeeded = true;
    // Initiate all control
    return InitControls( pControl );
}

bool CPaintManagerUI::InitControls( CElementUI* pControl, CElementUI* pParent /*= NULL*/ )
{
    ASSERT( pControl );
    if ( pControl == NULL ) return false;
    pControl->SetManager( this, pParent != NULL ? pParent : pControl->GetParent(), true );
    pControl->FindControl( __FindControlFromNameHash, this, UIFIND_ALL );
    return true;
}

void CPaintManagerUI::ReapObjects( CElementUI* pControl )
{
    if ( pControl == m_pEventKey ) m_pEventKey = NULL;
    if ( pControl == m_pEventHover ) m_pEventHover = NULL;
    if ( pControl == m_pEventClick ) m_pEventClick = NULL;

    const CStdString& sName = pControl->GetName();
    if ( !sName.IsEmpty() ) m_mNameHash.Remove( sName );

    if ( m_pFocus == pControl )
        SetFocus( NULL );
}
void CPaintManagerUI::MessageLoop()
{
    MSG msg = { 0 };
    while ( ::GetMessage( &msg, NULL, 0, 0 ) ) {
        if ( !CPaintManagerUI::TranslateMessage( &msg ) ) {
            ::TranslateMessage( &msg );
            ::DispatchMessage( &msg );
        }
    }
}

bool CPaintManagerUI::TranslateMessage( const LPMSG pMsg )
{
    // Pretranslate Message takes care of system-wide messages, such as
    // tabbing and shortcut key-combos. We'll look for all messages for
    // each window and any child control attached.
    HWND hwndParent = ::GetParent( pMsg->hwnd );
    UINT uStyle = GetWindowStyle( pMsg->hwnd );
    LRESULT lRes = 0;
    for ( int i = 0; i < m_aPreMessages.GetSize(); ++i ) {
        CPaintManagerUI* pT = m_aPreMessages[i];
        if ( pMsg->hwnd == pT->GetPaintWindow()
                || ( hwndParent == pT->GetPaintWindow() && ( ( uStyle & WS_CHILD ) != 0 ) ) ) {
            if ( pT->PreMessageHandler( pMsg->message, pMsg->wParam, pMsg->lParam, lRes ) ) return true;
        }
    }
    return false;
}

CElementUI* CPaintManagerUI::GetFocus() const
{
    return m_pFocus;
}

void CPaintManagerUI::SetFocus( CElementUI* pControl )
{
    // Paint manager window has focus?
    //if ( ::GetFocus() != m_hWndPaint ) ::SetFocus( m_hWndPaint );
    // Already has focus?
    if ( pControl == m_pFocus ) return;
    // Remove focus from old control
    if ( m_pFocus != NULL ) {
        TEventUI event = { 0 };
        event.Type = UIEVENT_KILLFOCUS;
        event.pSender = pControl;
        event.dwTimestamp = ::GetTickCount();
        m_pFocus->Event( event );
        SendNotify( m_pFocus, _T( "killfocus" ) );
        m_pFocus = NULL;
    }
    // Set focus to new control
    if ( pControl != NULL
            && pControl->GetManager() == this
            && pControl->IsVisible()
            && pControl->IsEnabled() ) {
        m_pFocus = pControl;
        TEventUI event = { 0 };
        event.Type = UIEVENT_SETFOCUS;
        event.pSender = pControl;
        event.dwTimestamp = ::GetTickCount();
        m_pFocus->Event( event );
        SendNotify( m_pFocus, _T( "setfocus" ) );
    }
}

bool CPaintManagerUI::SetTimer( CElementUI* pControl, UINT nTimerID, UINT uElapse )
{
    ASSERT( pControl != NULL );
    ASSERT( uElapse > 0 );
    for ( int i = 0; i < m_aTimers.GetSize(); ++i ) {
        TIMERINFO* pTimer = m_aTimers[i];
        //原来有停用的则启用
        if ( pTimer->pSender == pControl
                && pTimer->hWnd == m_hWndPaint
                && pTimer->nLocalID == nTimerID ) {
            if ( pTimer->bKilled == true ) {
                if ( ::SetTimer( m_hWndPaint, pTimer->uWinTimer, uElapse, NULL ) ) {
                    pTimer->bKilled = false;
                    return true;
                }

                return false;
            }

            return false;
        }
    }

    m_uTimerID = ( ++m_uTimerID ) % 0xFF;
    if ( !::SetTimer( m_hWndPaint, m_uTimerID, uElapse, NULL ) ) return false;

    TIMERINFO* pTimer = new TIMERINFO;
    ASSERT( pTimer );
    pTimer->hWnd = m_hWndPaint;
    pTimer->pSender = pControl;
    pTimer->nLocalID = nTimerID;
    pTimer->uWinTimer = m_uTimerID;
    pTimer->bKilled = false;
    return m_aTimers.Add( pTimer );
}

bool CPaintManagerUI::KillTimer( CElementUI* pControl, UINT nTimerID )
{
    ASSERT( pControl != NULL );
    for ( int i = 0; i < m_aTimers.GetSize(); ++i ) {
        TIMERINFO* pTimer = m_aTimers[i];
        if ( pTimer->pSender == pControl
                && pTimer->hWnd == m_hWndPaint
                && pTimer->nLocalID == nTimerID ) {
            if ( pTimer->bKilled == false ) {
                ::KillTimer( pTimer->hWnd, pTimer->uWinTimer );
                pTimer->bKilled = true;
                return true;
            }
        }
    }
    return false;
}
void CPaintManagerUI::SetCapture()
{
    ::SetCapture( m_hWndPaint );
    m_bMouseCapture = true;
}
void CPaintManagerUI::ReleaseCapture()
{
    ::ReleaseCapture();
    m_bMouseCapture = false;
}
bool CPaintManagerUI::SetNextTabControl( bool bForward )
{
    // If we're in the process of restructuring the layout we can delay the
    // focus calulation until the next repaint.

    if ( m_bUpdateNeeded && bForward ) {
        m_bFocusNeeded = true;
        ::InvalidateRect( m_hWndPaint, NULL, FALSE );
        return true;
    }
    // Find next/previous tabbable control
    FINDTABINFO info1 = { 0 };
    info1.pFocus = m_pFocus;
    info1.bForward = bForward;
    CElementUI* pControl = m_pRoot->FindControl( __FindControlFromTab, &info1, UIFIND_VISIBLE | UIFIND_ENABLED | UIFIND_ME_FIRST );
    if ( pControl == NULL ) {
        if ( bForward ) {
            // Wrap around
            FINDTABINFO info2 = { 0 };
            info2.pFocus = NULL;
            info2.bForward = true;
            pControl = m_pRoot->FindControl( __FindControlFromTab, &info2, UIFIND_VISIBLE | UIFIND_ENABLED | UIFIND_ME_FIRST );
        }
        else {
            pControl = info1.pLast;
        }
    }
    if ( pControl != NULL ) SetFocus( pControl );
    m_bFocusNeeded = false;
    return true;
}

bool CPaintManagerUI::AddNotifier( INotifyUI* pNotifier )
{
    ASSERT( m_aNotifiers.Find( pNotifier ) < 0 );
    return m_aNotifiers.Add( pNotifier );
}

bool CPaintManagerUI::RemoveNotifier( INotifyUI* pNotifier )
{
    for ( int i = 0; i < m_aNotifiers.GetSize(); ++i ) {
        if ( m_aNotifiers[i] == pNotifier ) {
            return m_aNotifiers.Remove( i );
        }
    }
    return false;
}
bool CPaintManagerUI::AddMessageFilter( IMessageFilterUI* pFilter )
{
    ASSERT( m_aMessageFilters.Find( pFilter ) < 0 );
    return m_aMessageFilters.Add( pFilter );
}

bool CPaintManagerUI::RemoveMessageFilter( IMessageFilterUI* pFilter )
{
    for ( int i = 0; i < m_aMessageFilters.GetSize(); ++i ) {
        if ( m_aMessageFilters[i] == pFilter ) {
            return m_aMessageFilters.Remove( i );
        }
    }
    return false;
}

int CPaintManagerUI::GetPostPaintCount() const
{
    return m_aPostPaintControls.GetSize();
}

bool CPaintManagerUI::AddPostPaint( CElementUI* pControl )
{
    ASSERT( m_aPostPaintControls.Find( pControl ) < 0 );
    return m_aPostPaintControls.Add( pControl );
}

bool CPaintManagerUI::RemovePostPaint( CElementUI* pControl )
{
    for ( int i = 0; i < m_aPostPaintControls.GetSize(); ++i ) {
        if ( m_aPostPaintControls[i] == pControl ) {
            return m_aPostPaintControls.Remove( i );
        }
    }
    return false;
}

// bool CPaintManagerUI::SetPostPaintIndex( CControlUI* pControl, int iIndex )
// {
//     RemovePostPaint( pControl );
//     return m_aPostPaintControls.InsertAt( iIndex, pControl );
// }
void CPaintManagerUI::SendNotify( CElementUI* pControl, LPCTSTR pstrMessage, WPARAM wParam /*= 0*/, LPARAM lParam /*= 0*/ )
{
    TNotifyUI Msg;
    Msg.pSender = pControl;
    Msg.sType = pstrMessage;
    Msg.wParam = wParam;
    Msg.lParam = lParam;
    SendNotify( Msg );
}

void CPaintManagerUI::SendNotify( TNotifyUI& Msg )
{
    Msg.ptMouse = m_ptLastMousePos;
    Msg.dwTimestamp = ::GetTickCount();
    // Send to all listeners
    for ( int i = 0; i < m_aNotifiers.GetSize(); ++i ) {
        m_aNotifiers[i]->Notify( Msg );
    }
}
bool CPaintManagerUI::UseParentResource( CPaintManagerUI* pm )
{
    if ( pm == NULL ) {
        m_pParentResourcePM = NULL;
        return true;
    }

    if ( pm == this ) return false;

    CPaintManagerUI* pParentPM = pm->GetParentResource();
    while ( pParentPM ) {
        if ( pParentPM == this ) return false;
        pParentPM = pParentPM->GetParentResource();
    }

    m_pParentResourcePM = pm;
    return true;
}

CPaintManagerUI* CPaintManagerUI::GetParentResource() const
{
    return m_pParentResourcePM;
}


DWORD CPaintManagerUI::GetDefaultDisabledColor() const
{
    if ( m_pParentResourcePM ) return m_pParentResourcePM->GetDefaultDisabledColor();
    return m_dwDefalutDisabledColor;
}

void CPaintManagerUI::SetDefaultDisabledColor( DWORD dwColor )
{
    m_dwDefalutDisabledColor = dwColor;
}

HFONT CPaintManagerUI::GetDefaultFont() const
{
    if ( m_pParentResourcePM ) return m_pParentResourcePM->GetDefaultFont();
    return m_hDefalutFont;
}

DWORD CPaintManagerUI::GetDefaultFontColor() const
{
    if ( m_pParentResourcePM ) return m_pParentResourcePM->GetDefaultFontColor();
    return m_dwDefalutFontColor;
}
const TEXTMETRIC& CPaintManagerUI::GetDefaultFontInfo()
{
    if ( m_pParentResourcePM ) return m_pParentResourcePM->GetDefaultFontInfo();
    if ( m_hDefalutFontTextMetric.tmHeight == 0 && m_hDcPaint ) {
        HFONT hOldFont = ( HFONT ) ::SelectObject( *m_hDcPaint, m_hDefalutFont );
        ::GetTextMetrics( *m_hDcPaint, &m_hDefalutFontTextMetric );
        ::SelectObject( *m_hDcPaint, hOldFont );
    }

    return m_hDefalutFontTextMetric;
}

void CPaintManagerUI::SetDefaultFont( HFONT hFont, DWORD dwColor )
{
    if ( hFont == NULL ) return;

    if ( m_hDcPaint ) {
        HFONT hOldFont = ( HFONT ) ::SelectObject( *m_hDcPaint, hFont );
        ::GetTextMetrics( *m_hDcPaint, &m_hDefalutFontTextMetric );
        ::SelectObject( *m_hDcPaint, hOldFont );
    }
    else {
        ::ZeroMemory( &m_hDefalutFontTextMetric, sizeof( m_hDefalutFontTextMetric ) );
    }

    if ( m_hDefalutFont && !FindFont( m_hDefalutFont ) ) ::DeleteObject( m_hDefalutFont );
    m_hDefalutFont = hFont;
    m_dwDefalutFontColor = dwColor;
}

HFONT CPaintManagerUI::GetDefaultBoldFont() const
{
    if ( m_pParentResourcePM ) return m_pParentResourcePM->GetDefaultBoldFont();
    return m_hDefalutBoldFont;
}

// DWORD CPaintManagerUI::GetDefaultBoldFontColor()
// {
//     if ( m_pParentResourcePM ) return m_pParentResourcePM->GetDefaultBoldFontColor();
//     return m_dwDefalutBoldFontColor;
// }
const TEXTMETRIC& CPaintManagerUI::GetDefaultBoldFontInfo()
{
    if ( m_pParentResourcePM ) return m_pParentResourcePM->GetDefaultBoldFontInfo();
    if ( m_hDefaluttBoldFontTextMetric.tmHeight == 0 && m_hDcPaint ) {
        HFONT hOldFont = ( HFONT ) ::SelectObject( *m_hDcPaint, m_hDefalutBoldFont );
        ::GetTextMetrics( *m_hDcPaint, &m_hDefaluttBoldFontTextMetric );
        ::SelectObject( *m_hDcPaint, hOldFont );
    }

    return m_hDefaluttBoldFontTextMetric;
}
void CPaintManagerUI::SetDefaultBoldFont( HFONT hFont, DWORD dwColor )
{
    if ( hFont == NULL ) return;

    if ( m_hDcPaint ) {
        HFONT hOldFont = ( HFONT ) ::SelectObject( *m_hDcPaint, hFont );
        ::GetTextMetrics( *m_hDcPaint, &m_hDefaluttBoldFontTextMetric );
        ::SelectObject( *m_hDcPaint, hOldFont );
    }
    else {
        ::ZeroMemory( &m_hDefaluttBoldFontTextMetric, sizeof( m_hDefaluttBoldFontTextMetric ) );
    }

    if ( m_hDefalutBoldFont && !FindFont( m_hDefalutBoldFont ) ) ::DeleteObject( m_hDefalutBoldFont );
    m_hDefalutBoldFont = hFont;
    m_dwDefalutFontColor = dwColor;
}

HFONT CPaintManagerUI::GetDefaultLinkFont() const
{
    if ( m_pParentResourcePM ) return m_pParentResourcePM->GetDefaultLinkFont();
    return m_hDefalutLinkFont;
}
DWORD CPaintManagerUI::GetDefaultLinkFontColor() const
{
    if ( m_pParentResourcePM ) return m_pParentResourcePM->GetDefaultLinkFontColor();
    return m_dwDefalutLinkFontColor;
}

DWORD CPaintManagerUI::GetDefaultLinkFontHoverColor() const
{
    if ( m_pParentResourcePM ) return m_pParentResourcePM->GetDefaultLinkFontHoverColor();
    return m_dwDefalutLinkFontHoverColor;
}
const TEXTMETRIC& CPaintManagerUI::GetDefaultLinkFontInfo()
{
    if ( m_pParentResourcePM ) return m_pParentResourcePM->GetDefaultLinkFontInfo();

    if ( m_hDefalutLinkFontTextMetric.tmHeight == 0 && m_hDcPaint ) {
        HFONT hOldFont = ( HFONT )::SelectObject( *m_hDcPaint, m_hDefalutLinkFont );
        ::GetTextMetrics( *m_hDcPaint, &m_hDefalutLinkFontTextMetric );
        ::SelectObject( *m_hDcPaint, hOldFont );
    }

    return m_hDefalutLinkFontTextMetric;
}
void CPaintManagerUI::SetDefaultLinkFont( HFONT hFont, DWORD dwColor, DWORD dwHoverColor )
{
    if ( hFont == NULL ) return;

    if ( m_hDcPaint ) {
        HFONT hOldFont = ( HFONT ) ::SelectObject( *m_hDcPaint, hFont );
        ::GetTextMetrics( *m_hDcPaint, &m_hDefalutLinkFontTextMetric );
        ::SelectObject( *m_hDcPaint, hOldFont );
    }
    else {
        ::ZeroMemory( &m_hDefalutLinkFontTextMetric, sizeof( m_hDefalutLinkFontTextMetric ) );
    }

    if ( m_hDefalutLinkFont && !FindFont( m_hDefalutLinkFont ) ) ::DeleteObject( m_hDefalutLinkFont );
    m_hDefalutLinkFont = hFont;
    m_dwDefalutLinkFontColor = dwColor;
    m_dwDefalutLinkFontHoverColor = dwHoverColor;
}

bool CPaintManagerUI::AddFont( HFONT hFont )
{

    if ( hFont == NULL ) return false;

    TFontInfo* pFontInfo = new TFontInfo( hFont );
    ASSERT( pFontInfo );
    ::ZeroMemory( &pFontInfo->tm, sizeof( TEXTMETRIC ) );

    if ( m_hDcPaint ) {
        HFONT hOldFont = ( HFONT ) ::SelectObject( *m_hDcPaint, hFont );
        ::GetTextMetrics( *m_hDcPaint, &pFontInfo->tm );
        ::SelectObject( *m_hDcPaint, hOldFont );
    }

    if ( !m_aCustomFonts.Add( pFontInfo ) ) {
        delete pFontInfo;
        return false;
    }

    return true;
}

HFONT CPaintManagerUI::AddFont( LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic )
{
    LOGFONT lf = { 0 };
    ::GetObject( ::GetStockObject( DEFAULT_GUI_FONT ), sizeof( LOGFONT ), &lf );
    _tcscpy( lf.lfFaceName, pStrFontName );
    lf.lfHeight = -nSize;
    if ( bBold ) lf.lfWeight += FW_BOLD;
    if ( bUnderline ) lf.lfUnderline = TRUE;
    if ( bItalic ) lf.lfItalic = TRUE;
    HFONT hFont = ::CreateFontIndirect( &lf );
    ASSERT( hFont );
    if ( !AddFont( hFont ) ) {
        return NULL;
    }

    return hFont;
}
// bool CPaintManagerUI::AddFontAt( int index, HFONT hFont )
// {
// 	if ( hFont == NULL ) return false;
//
// 	TFontInfo* pFontInfo = new TFontInfo;
// 	if ( !pFontInfo ) return false;
// 	::ZeroMemory( pFontInfo, sizeof( TFontInfo ) );
// 	pFontInfo->hFont = hFont;
// 	if ( m_hDcPaint ) {
// 		HFONT hOldFont = ( HFONT ) ::SelectObject( m_hDcPaint, hFont );
// 		::GetTextMetrics( m_hDcPaint, &pFontInfo->tm );
// 		::SelectObject( m_hDcPaint, hOldFont );
// 	}
//
// 	if ( !m_aCustomFonts.InsertAt( index, pFontInfo ) ) {
// 		delete pFontInfo;
// 		return false;
// 	}
//
// 	return true;
// }
//
// HFONT CPaintManagerUI::AddFontAt( int index, LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline )
// {
// 	LOGFONT lf = { 0 };
// 	::GetObject( ::GetStockObject( DEFAULT_GUI_FONT ), sizeof( LOGFONT ), &lf );
// 	_tcscpy( lf.lfFaceName, pStrFontName );
// 	lf.lfHeight = -nSize;
// 	if ( bBold ) lf.lfWeight += FW_BOLD;
// 	if ( bUnderline ) lf.lfUnderline = TRUE;
// 	HFONT hFont = ::CreateFontIndirect( &lf );
// 	if ( hFont == NULL ) return NULL;
// 	if ( !AddFontAt( index, hFont ) ) {
// 		::DeleteObject( hFont );
// 		return NULL;
// 	}
//
// 	return hFont;
// }

HFONT CPaintManagerUI::GetFont( int index ) const
{
    if ( m_pParentResourcePM ) return m_pParentResourcePM->GetFont( index );

    if ( index < 0 || index >= m_aCustomFonts.GetSize() ) return GetDefaultFont();

    return m_aCustomFonts[index]->hFont;
}
void CPaintManagerUI::SetFont( int index, HFONT hFont )
{
    if ( index < 0 || index >= m_aCustomFonts.GetSize() ) return;
    HFONT oFont = m_aCustomFonts[index]->hFont;
    if ( m_hDefalutFont == oFont ) {
        m_hDefalutFont = hFont;
        ::ZeroMemory( &m_hDefalutFontTextMetric, sizeof( TEXTMETRIC ) );
    }
    if ( m_hDefalutBoldFont == oFont ) {
        m_hDefalutBoldFont = hFont;
        ::ZeroMemory( &m_hDefaluttBoldFontTextMetric, sizeof( TEXTMETRIC ) );
    }
    if ( m_hDefalutLinkFont == oFont ) {
        m_hDefalutLinkFont = hFont;
        ::ZeroMemory( &m_hDefalutLinkFontTextMetric, sizeof( TEXTMETRIC ) );
    }
    ::DeleteObject( oFont );
    m_aCustomFonts[index]->hFont = hFont;
    ::ZeroMemory( &m_aCustomFonts[index]->tm, sizeof( TEXTMETRIC ) );
}
bool CPaintManagerUI::FindFont( HFONT hFont ) const
{
    if ( m_pParentResourcePM ) return m_pParentResourcePM->FindFont( hFont );

    TFontInfo* pFontInfo = NULL;
    for ( int it = 0; it < m_aCustomFonts.GetSize(); ++it ) {
        if ( m_aCustomFonts[it]->hFont == hFont ) return true;
    }

    return false;
}
// bool CPaintManagerUI::RemoveFont( HFONT hFont )
// {
//     TFontInfo* pFontInfo = NULL;
//     for ( int it = 0; it < m_aCustomFonts.GetSize(); it++ ) {
//         pFontInfo = static_cast<TFontInfo*>( m_aCustomFonts[it] );
//         if ( pFontInfo->hFont == hFont ) {
//             ::DeleteObject( pFontInfo->hFont );
//             delete pFontInfo;
//             return m_aCustomFonts.Remove( it );
//         }
//     }
//
//     return false;
// }
//
// bool CPaintManagerUI::RemoveFontAt( int index )
// {
//     if ( index < 0 || index >= m_aCustomFonts.GetSize() ) return false;
//     TFontInfo* pFontInfo = static_cast<TFontInfo*>( m_aCustomFonts[index] );
//     ::DeleteObject( pFontInfo->hFont );
//     delete pFontInfo;
//     return m_aCustomFonts.Remove( index );
// }
void CPaintManagerUI::RemoveAllFonts()
{
    m_aCustomFonts.Resize_Delete( 0 );
}
const TEXTMETRIC& CPaintManagerUI::GetFontInfo( int index )
{
    if ( m_pParentResourcePM ) return m_pParentResourcePM->GetFontInfo( index );

    if ( index < 0 || index >= m_aCustomFonts.GetSize() ) return GetDefaultFontInfo();

    TFontInfo* pFontInfo = m_aCustomFonts[index];
    if ( pFontInfo->tm.tmHeight == 0 && m_hDcPaint ) {
        HFONT hOldFont = ( HFONT )::SelectObject( *m_hDcPaint, pFontInfo->hFont );
        ::GetTextMetrics( *m_hDcPaint, &pFontInfo->tm );
        ::SelectObject( *m_hDcPaint, hOldFont );
    }
    return pFontInfo->tm;
}
Bitmap* CPaintManagerUI::GetImage( LPCTSTR bitmap ) const
{
    CStdStringPtrMap<Bitmap*>::TITEM* item = m_mImageHash.Find( bitmap );

    if ( item )
        return item->Data;
    else if ( m_pParentResourcePM )
        return m_pParentResourcePM->GetImage( bitmap );
    else
        return NULL;
}

Bitmap* CPaintManagerUI::GetImageEx( LPCTSTR bitmap, LPCTSTR type )
{
    CStdStringPtrMap<Bitmap*>::TITEM* item = m_mImageHash.Find( bitmap );

    if ( !item ) {
        return AddImage( bitmap, type );
    }

    return item->Data;
}

Bitmap* CPaintManagerUI::AddImage( LPCTSTR bitmap, LPCTSTR type )
{
    Bitmap* data = NULL;
    if ( type != NULL && *type != 0 ) {
        int iIndex = -1, iType = -1;
        if ( isdigit( *bitmap ) ) {
            //LPTSTR pstr = NULL;
            iIndex = _tcstol( bitmap, NULL, 10 );
        }
        if ( isdigit( *type ) ) {
            iType = _tcstol( type, NULL, 10 );
        }
        data = CRenderEngine::LoadImage( ( iIndex == -1 ) ? STRINGorID( bitmap ) : STRINGorID( iIndex )  , ( iType == -1 ) ? STRINGorID( type ) : STRINGorID( iType )  );
    }
    else {
        data = CRenderEngine::LoadImage( bitmap, type );
    }

    if ( !data ) return NULL;

    m_mImageHash[bitmap] = data;

    return data;
}
// bool CPaintManagerUI::RemoveImage( LPCTSTR bitmap )
// {
//     TImageInfo* data = GetImage( bitmap );
//     if ( !data ) return false;
//
//     ::DeleteObject( data->hBitmap );
//     delete data;
//
//     return m_mImageHash.Remove( bitmap );
// }
void CPaintManagerUI::RemoveAllImages()
{
    for ( CStdStringPtrMap<Bitmap*>::Ite ite = m_mImageHash.Begin(); !ite.IsEnd(); ++ite ) {
        delete ( *ite )->Data;
    }

    m_mImageHash.Resize();
}

void CPaintManagerUI::AddDefaultAttributeList( LPCTSTR pStrControlName, LPCTSTR pStrControlAttrList )
{
    CStdString* pDefaultAttr = new CStdString( pStrControlAttrList );
    m_DefaultAttrHash[pStrControlName] = pDefaultAttr;
}

LPCTSTR CPaintManagerUI::GetDefaultAttributeList( LPCTSTR pStrControlName ) const
{
    CStdStringPtrMap<CStdString*>::TITEM* item = m_DefaultAttrHash.Find( pStrControlName );

    if ( item )
        return item->Data->GetData();
    else if ( m_pParentResourcePM )
        return m_pParentResourcePM->GetDefaultAttributeList( pStrControlName );
    else
        return NULL;
}

bool CPaintManagerUI::RemoveDefaultAttributeList( LPCTSTR pStrControlName )
{
    CStdStringPtrMap<CStdString*>::Ite ite;
    if ( !m_DefaultAttrHash.Find( pStrControlName, ite ) ) return false;

    delete ( *ite )->Data;
    return m_DefaultAttrHash.Remove( ite );
}

void CPaintManagerUI::RemoveAllDefaultAttributeList()
{
    for ( CStdStringPtrMap<CStdString*>::Ite ite = m_DefaultAttrHash.Begin(); !ite.IsEnd(); ++ite ) {
        delete ( *ite )->Data;
    }

    m_DefaultAttrHash.Resize();
}

CElementUI* CPaintManagerUI::GetRoot() const
{
    ASSERT( m_pRoot );
    return m_pRoot;
}

CElementUI* CPaintManagerUI::FindControl( LPCTSTR pstrName )
{
    ASSERT( m_pRoot );
    CStdStringPtrMap<CElementUI*>::TITEM* item = m_mNameHash.Find( pstrName );
    if ( item  )
        return item->Data;
    else
        return NULL;
}

CElementUI* CPaintManagerUI::FindControl( POINT pt ) const
{
    ASSERT( m_pRoot );
    return m_pRoot->FindControl( __FindControlFromPoint, &pt, UIFIND_VISIBLE | UIFIND_HITTEST | UIFIND_TOP_FIRST | UIFIND_CAN_FOCUS );
}


//计数器
CElementUI* CALLBACK CPaintManagerUI::__FindControlFromCount( CElementUI* /*pThis*/, LPVOID pData )
{
    int* pnCount = reinterpret_cast<int*>( pData );
    ++( *pnCount );
    return NULL;  // Count all controls
}

CElementUI* CALLBACK CPaintManagerUI::__FindControlFromTab( CElementUI* pThis, LPVOID pData )
{
    FINDTABINFO* pInfo = reinterpret_cast<FINDTABINFO*>( pData );
    if ( pInfo->pFocus == pThis ) {
        if ( pInfo->bForward ) pInfo->bNextIsIt = true;
        return pInfo->bForward ? NULL : pInfo->pLast;
    }
    if ( ( pThis->GetControlFlags() & UIFLAG_TABSTOP ) == 0 ) return NULL;
    pInfo->pLast = pThis;
    if ( pInfo->bNextIsIt ) return pThis;
    if ( pInfo->pFocus == NULL ) return pThis;
    return NULL;  // Examine all controls
}
//用来添加NameHash
CElementUI* CALLBACK CPaintManagerUI::__FindControlFromNameHash( CElementUI* pThis, LPVOID pData )
{
    CPaintManagerUI* pManager = static_cast<CPaintManagerUI*>( pData );
    const CStdString& sName = pThis->GetName();
    if ( sName.IsEmpty() ) return NULL;
    // Add this control to the hash list
    pManager->m_mNameHash[sName] = pThis;
    return NULL; // Attempt to add all controls
}

CElementUI* CALLBACK CPaintManagerUI::__FindControlFromShortcut( CElementUI* pThis, LPVOID pData )
{
    if ( !pThis->IsVisible() ) return NULL;
    FINDSHORTCUT* pFS = reinterpret_cast<FINDSHORTCUT*>( pData );
    //非常不理解这个PickNext是啥用途，我猜想可能是如果Label有快捷键则取下一个控件
    if ( pFS->ch == toupper( pThis->GetShortcut() ) ) pFS->bPickNext = true;
    if ( _tcsstr( pThis->GetClass(), _T( "LabelUI" ) ) != NULL ) return NULL; // Labels never get focus!
    return pFS->bPickNext ? pThis : NULL;
}

CElementUI* CALLBACK CPaintManagerUI::__FindControlFromPoint( CElementUI* pThis, LPVOID pData )
{
    LPPOINT pPoint = reinterpret_cast<LPPOINT>( pData );
    return ::PtInRect( &pThis->GetPos(), *pPoint ) ? pThis : NULL;
}

CElementUI* CALLBACK CPaintManagerUI::__FindControlFromUpdate( CElementUI* pThis, LPVOID pData )
{
    return pThis->IsUpdateNeeded() ? pThis : NULL;
}

/////////////////////////////////////////////////////////////////////////////////////
//
//
IMPLEMENT_DYNCREATE( CControlUI )

CControlUI::CControlUI() :
    m_dwBackColor( 0 ),
    m_dwBackColor2( 0 ),
    m_dwBorderColor( 0 ),
    m_bTabStop( false ),
    m_bNotUseDefSkin( false ),
    m_iVerticalContentAlignment( UIALIGNMENT_STRETCH ),
    m_iHorizontalContentAlignment( UIALIGNMENT_STRETCH )
{
    m_bCanFocus = true;

    //默认父拉伸
    m_iHorizontalAlignment = m_iVerticalAlignment = UIALIGNMENT_STRETCH;

    ::ZeroMemory( &m_rcInset, sizeof( m_rcInset ) );
    ::ZeroMemory( &m_nBorderSize, sizeof( m_nBorderSize ) );
}
LPCTSTR CControlUI::GetClass() const
{
    return _T( "ControlUI" );
}

LPVOID CControlUI::GetInterface( LPCTSTR pstrName )
{
    if ( _tcscmp( pstrName, _T( "Control" ) ) == 0 ) return static_cast<CControlUI*>( this );
    return CElementUI::GetInterface( pstrName );
}


UINT CControlUI::GetControlFlags() const
{
    return ( m_bTabStop  ) ? UIFLAG_TABSTOP : 0;//&& IsVisible() && IsEnabled()
}

DWORD CControlUI::GetBkColor() const
{
    return m_dwBackColor;
}
void CControlUI::SetBkColor( DWORD dwBackColor )
{
    if ( m_dwBackColor == dwBackColor ) return;

    m_dwBackColor = dwBackColor;
    Invalidate();
}

DWORD CControlUI::GetBkColor2() const
{
    return m_dwBackColor2;
}

void CControlUI::SetBkColor2( DWORD dwBackColor )
{
    if ( m_dwBackColor2 == dwBackColor ) return;

    m_dwBackColor2 = dwBackColor;
    Invalidate();
}

LPCTSTR CControlUI::GetBkImage() const
{
    return m_sBkImage;
}

void CControlUI::SetBkImage( LPCTSTR pStrImage )
{
    if ( m_sBkImage == pStrImage ) return;

    m_sBkImage = pStrImage;
    Invalidate();
}

DWORD CControlUI::GetBorderColor() const
{
    return m_dwBorderColor;
}

void CControlUI::SetBorderColor( DWORD dwBorderColor )
{
    if ( m_dwBorderColor == dwBorderColor ) return;

    m_dwBorderColor = dwBorderColor;
    Invalidate();
}

RECT CControlUI::GetBorderSize() const
{
    return m_nBorderSize;
}

void CControlUI::SetBorderSize( const RECT& nSize )
{
    if ( ::EqualRect( &m_nBorderSize, &nSize ) ) return;

    m_nBorderSize = nSize;
    Invalidate();
}
void CControlUI::EstimateSizeMain( const SIZE& szAvailable )
{
    SIZE sz = {szAvailable.cx - m_rcInset.left - m_rcInset.right, szAvailable.cy - m_rcInset.top - m_rcInset.bottom};
    sz.cx = MAX( sz.cx, 0 ); sz.cy = MAX( sz.cy, 0 );
    sz = EstimateSizeOver( sz );
    sz.cx += m_rcInset.left + m_rcInset.right;
    sz.cy += m_rcInset.top + m_rcInset.bottom;
    m_szItemDesired = sz;
}

void CControlUI::SetPosMain( const RECT& rc )
{
    RECT rcPos = {rc.left + m_rcInset.left, rc.top + m_rcInset.top, rc.right - m_rcInset.right, rc.bottom - m_rcInset.bottom};
    rcPos.right = MAX( rcPos.left, rcPos.right );
    rcPos.bottom = MAX( rcPos.top, rcPos.bottom );
    rcPos = SetPosOver( rcPos );
    ::SetRect( &m_rcItem, rcPos.left - m_rcInset.left, rcPos.top - m_rcInset.top, rcPos.right + m_rcInset.right, rcPos.bottom + m_rcInset.bottom );
}

RECT CControlUI::GetInset() const
{
    return m_rcInset;
}

void CControlUI::SetInset( const RECT& rcInset )
{
    if ( ::EqualRect( &m_rcInset, & rcInset ) )return;

    m_rcInset = rcInset;
    //需要强行计算布局
    NeedUpdate( true );
}
int CControlUI::GetVerticalContentAlignment() const
{
    return m_iVerticalContentAlignment;
}

void CControlUI::SetVerticalContentAlignment( int alignment/*=UIALIGNMENT_STRETCH*/ )
{
    if ( m_iVerticalContentAlignment == alignment )return;
    m_iVerticalContentAlignment = alignment;
    //不需要计算布局，这个元素只在setpos中起作用
    NeedUpdate( false );
}

int CControlUI::GetHorizontalContentAlignment() const
{
    return m_iHorizontalContentAlignment;
}

void CControlUI::SetHorizontalContentAlignment( int alignment/*=UIALIGNMENT_STRETCH*/ )
{
    if ( m_iHorizontalContentAlignment == alignment )return;
    m_iHorizontalContentAlignment = alignment;

    NeedUpdate( false );
}
void CControlUI::SetTabStop( bool bTabStop )
{
    m_bTabStop = bTabStop;
}
bool CControlUI::IsTabStop() const
{
    return m_bTabStop;
}
void CControlUI::SetNotUseDefSkin( bool bNotUseDefSkin  )
{
    m_bNotUseDefSkin = bNotUseDefSkin;
}
bool CControlUI::IsNotUseDefSkin() const
{
    return m_bNotUseDefSkin;
}

void CControlUI::SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue )
{
    if ( _tcscmp( pstrName, _T( "inset" ) ) == 0 ) {
        SetInset( RectFromString( pstrValue ) );
    }
    else if ( _tcscmp( pstrName, _T( "bkcolor" ) ) == 0 ) {
        if ( *pstrValue == _T( '#' ) ) pstrValue = ::CharNext( pstrValue );
        SetBkColor( _tcstoul( pstrValue, NULL, 16 ) );
    }
    else if ( _tcscmp( pstrName, _T( "bkcolor2" ) ) == 0 ) {
        if ( *pstrValue == _T( '#' ) ) pstrValue = ::CharNext( pstrValue );
        SetBkColor2( _tcstoul( pstrValue, NULL, 16 ) );
    }
    else if ( _tcscmp( pstrName, _T( "bordercolor" ) ) == 0 ) {
        if ( *pstrValue == _T( '#' ) ) pstrValue = ::CharNext( pstrValue );
        SetBorderColor( _tcstoul( pstrValue, NULL, 16 ) );
    }
    else if ( _tcscmp( pstrName, _T( "bordersize" ) ) == 0 ) SetBorderSize( RectFromString( pstrValue ) );
    else if ( _tcscmp( pstrName, _T( "bkimage" ) ) == 0 ) SetBkImage( pstrValue );
    else if ( _tcscmp( pstrName, _T( "tabstop" ) ) == 0 ) SetTabStop( _tcscmp( pstrValue, _T( "true" ) ) == 0 );
    else if ( _tcscmp( pstrName, _T( "notusedefskin" ) ) == 0 ) SetNotUseDefSkin( _tcscmp( pstrValue, _T( "true" ) ) == 0 );
    else if ( _tcscmp( pstrName, _T( "verticalcontentalignment" ) ) == 0 ) {
        if ( _tcscmp( pstrValue, _T( "top" ) ) == 0 )
            m_iVerticalContentAlignment = UIALIGNMENT_LEFT_TOP;
        else if ( _tcscmp( pstrValue, _T( "center" ) ) == 0 )
            m_iVerticalContentAlignment = UIALIGNMENT_CENTER;
        else if ( _tcscmp( pstrValue, _T( "bottom" ) ) == 0 )
            m_iVerticalContentAlignment = UIALIGNMENT_RIGHT_BOTTOM;
    }
    else if ( _tcscmp( pstrName, _T( "horizontalcontentalignment" ) ) == 0 ) {
        if ( _tcscmp( pstrValue, _T( "left" ) ) == 0 )
            m_iHorizontalContentAlignment = UIALIGNMENT_LEFT_TOP;
        else if ( _tcscmp( pstrValue, _T( "center" ) ) == 0 )
            m_iHorizontalContentAlignment = UIALIGNMENT_CENTER;
        else if ( _tcscmp( pstrValue, _T( "right" ) ) == 0 )
            m_iHorizontalContentAlignment = UIALIGNMENT_RIGHT_BOTTOM;
    }
    else CElementUI::SetAttribute( pstrName, pstrValue );
}

void CControlUI::DoPaintOver( GRAPHorHDC& gorh )
{
    // 绘制循序：背景颜色->背景图->状态图->文本
    PaintBkColor( gorh );
    PaintBkImage( gorh );
    PaintStatusImage( gorh );
    PaintBorder( gorh );
}

void CControlUI::PaintBkColor( GRAPHorHDC& gorh )
{
    if ( m_dwBackColor != 0 ) {
        if ( m_dwBackColor2 != 0 ) CRenderEngine::DrawGradient( gorh, m_rcItem, m_dwBackColor, m_dwBackColor2, true );
        else if ( m_dwBackColor >= 0xFF000000 ) CRenderEngine::DrawColor( gorh, m_rcPaint, m_dwBackColor );
        else CRenderEngine::DrawColor( gorh, m_rcItem, m_dwBackColor );
    }
}

void CControlUI::PaintBkImage( GRAPHorHDC& gorh )
{
    if ( m_sBkImage.IsEmpty() ) return;
    if ( !DrawImage( gorh, ( LPCTSTR )m_sBkImage ) ) m_sBkImage.Empty();
}

void CControlUI::PaintStatusImage( GRAPHorHDC& gorh )
{
}

void CControlUI::PaintBorder( GRAPHorHDC& gorh )
{
    bool bModesave = gorh.SetGRAPHmode();
    Graphics& g = gorh;
    if ( m_nBorderSize.left > 0 ) {
        g.FillRectangle( &SolidBrush( m_dwBorderColor ), \
                         m_rcItem.left, m_rcItem.top, m_nBorderSize.left, m_rcItem.bottom - m_rcItem.top );
    }
    if ( m_nBorderSize.top > 0 ) {
        g.FillRectangle( &SolidBrush( m_dwBorderColor ), \
                         m_rcItem.left, m_rcItem.top, m_rcItem.right - m_rcItem.left, m_nBorderSize.top );
    }
    if ( m_nBorderSize.right > 0 ) {
        g.FillRectangle( &SolidBrush( m_dwBorderColor ), \
                         m_rcItem.right - m_nBorderSize.right, m_rcItem.top, m_nBorderSize.right, m_rcItem.bottom - m_rcItem.top );
    }
    if ( m_nBorderSize.bottom > 0 ) {
        g.FillRectangle( &SolidBrush( m_dwBorderColor ), \
                         m_rcItem.left, m_rcItem.bottom - m_nBorderSize.bottom, m_rcItem.right - m_rcItem.left, m_rcItem.bottom );
    }
    gorh.Setmode( bModesave );
}

/////////////////////////////////////////////////////////////////////////////////////
//
//
CElementUI::CElementUI():
    m_pManager( NULL ),
    m_pParent( NULL ),
    m_bUpdateNeeded( true ),
    m_bVisible( true ),
    m_bInternVisible( true ),
    m_bEnabled( true ),
    m_bInternEnabled( true ),
    m_bMouseEnabled( true ),
    m_bInternMouseEnabled( true ),
    m_bFocused( false ),
    m_bCanFocus( false ),
    m_chShortcut( _T( '\0' ) ),
    m_pTag( NULL ),
    m_iVerticalAlignment( UIALIGNMENT_LEFT_TOP ),
    m_iHorizontalAlignment( UIALIGNMENT_LEFT_TOP ),
	m_iDockSide(UIDOCK_LEFT)
{
    m_cXY.cx = m_cXY.cy = 0;
    m_cxyFixed.cx = m_cxyFixed.cy = 0;
    m_cxyMin.cx = m_cxyMin.cy = 0;
    m_cxyMax.cx = m_cxyMax.cy = 9999;

    ::ZeroMemory( &m_rcPadding, sizeof( m_rcPadding ) );
    ::ZeroMemory( &m_rcItem, sizeof( m_rcItem ) );
    ::ZeroMemory( &m_rcPaint, sizeof( m_rcPaint ) );
    ::ZeroMemory( &m_szItemDesired, sizeof( m_szItemDesired ) );
    ::ZeroMemory( &m_szEstimateRemind, sizeof( m_szEstimateRemind ) );
    ::ZeroMemory( &m_rcSetposRemind, sizeof( m_rcSetposRemind ) );
}

CElementUI::~CElementUI()
{
    if ( m_pManager != NULL ) m_pManager->ReapObjects( this );
}

CStdString CElementUI::GetName() const
{
    return m_sName;
}

void CElementUI::SetName( LPCTSTR pstrName )
{
    m_sName = pstrName;
}

LPCTSTR CElementUI::GetClass() const
{
    return _T( "ElementUI" );
}

LPVOID CElementUI::GetInterface( LPCTSTR pstrName )
{
    if ( _tcscmp( pstrName, _T( "Element" ) ) == 0 ) return static_cast<CElementUI*>( this );
    return NULL;
}

UINT CElementUI::GetControlFlags() const
{
    return 0;
}

bool CElementUI::Activate()
{
    if ( !IsVisible() ) return false;
    if ( !IsEnabled() ) return false;
    return true;
}

CPaintManagerUI* CElementUI::GetManager() const
{
    return m_pManager;
}

void CElementUI::SetManager( CPaintManagerUI* pManager, CElementUI* pParent, bool bInit /*= true */ )
{
    m_pManager = pManager;
    m_pParent = pParent;
    if ( bInit && m_pParent ) Init();
}

CElementUI* CElementUI::GetParent() const
{
    return m_pParent;
}

bool CElementUI::DrawImage( GRAPHorHDC& gorh, LPCTSTR pStrImage, LPCTSTR pStrModify /*= NULL */ )
{
    if ( m_pManager != NULL )
        return CRenderEngine::DrawImageString( gorh, m_pManager, m_rcItem, m_rcPaint, pStrImage, pStrModify );
    else
        return false;
}
SIZE CElementUI::GetDesiredSize() const
{
    return m_szItemDesired;
}
void CElementUI::EstimateSize( const SIZE& szAvailable, bool bForce )
{
    //放在测量中
    //不是不等测量保存则不测量
    //这样就要求当NeedParent时自己也要置更新量
    if ( !bForce && szAvailable.cx == m_szEstimateRemind.cx && \
            szAvailable.cy == m_szEstimateRemind.cy )
        return;
    //保存这次测量值
    m_szEstimateRemind = szAvailable;

    EstimateSizeMain( szAvailable );
    if ( m_szItemDesired.cx == 0 || m_cxyFixed.cx != 0 )m_szItemDesired.cx = m_cxyFixed.cx;
    if ( m_szItemDesired.cy == 0 || m_cxyFixed.cy != 0 )m_szItemDesired.cy = m_cxyFixed.cy;
    m_szItemDesired.cx = CLAMP( m_szItemDesired.cx, m_cxyMin.cx, m_cxyMax.cx );
    m_szItemDesired.cy = CLAMP( m_szItemDesired.cy, m_cxyMin.cy, m_cxyMax.cy );
}
void CElementUI::EstimateSizeMain( const SIZE& szAvailable )
{
    m_szItemDesired = EstimateSizeOver( szAvailable );
}
SIZE CElementUI::EstimateSizeOver( const SIZE& szAvailable )
{
    return CSize();
}
RECT CElementUI::GetPos() const
{
    return m_rcItem;
}

void CElementUI::SetPos( const RECT& rc )
{
    if ( !m_bUpdateNeeded && ::EqualRect( &m_rcSetposRemind, &rc ) )
        return;
    m_rcSetposRemind = rc;

    CRect invalidateRc = m_rcItem;
    if ( invalidateRc.IsEmpty() )
        invalidateRc = rc;
    //更新或设定与测量保存不同则重新测量
    //这是一种做法，我现在去试试放在测量中
    SIZE szAvailable = {rc.right - rc.left, rc.bottom - rc.top};
    // 	if(m_bUpdateNeeded || szAvailable.cx==m_szEstimateRemind.cx &&\
    // 		szAvailable.cy==m_szEstimateRemind.cy)
    EstimateSize( szAvailable );

    SetPosMain( rc );

    m_bUpdateNeeded = false;

    invalidateRc.Union( m_rcItem );
    Invalidate( invalidateRc );
}
void CElementUI::SetPosMain( const RECT& rc )
{
    m_rcItem = SetPosOver( rc );
}
RECT CElementUI::SetPosOver( const RECT& rc )
{
    return rc;
}

int CElementUI::GetWidth() const
{
    return m_rcItem.right - m_rcItem.left;
}

int CElementUI::GetHeight() const
{
    return m_rcItem.bottom - m_rcItem.top;
}

int CElementUI::GetX() const
{
    return m_rcItem.left;
}

int CElementUI::GetY() const
{
    return m_rcItem.top;
}

RECT CElementUI::GetPadding() const
{
    return m_rcPadding;
}

void CElementUI::SetPadding( const RECT& rcPadding )
{
    if ( ::EqualRect( &m_rcPadding, &rcPadding ) ) return;
    m_rcPadding = rcPadding;
    //需要强行计算布局
    NeedParentUpdate( true );
}

SIZE CElementUI::GetFixedXY() const
{
    return m_cXY;
}
//设置相对坐标
void CElementUI::SetFixedXY( const SIZE& szXY )
{
    if ( m_cXY.cx == szXY.cx && m_cXY.cy == szXY.cy ) return;
    m_cXY = szXY;
    //不需要计算布局，只在setpos中用
    NeedParentUpdate( false );
}

int CElementUI::GetFixedWidth() const
{
    return m_cxyFixed.cx;
}

void CElementUI::SetFixedWidth( int cx )
{
    if ( cx < 0 ) return;
    if ( m_cxyFixed.cx == cx ) return;
    m_cxyFixed.cx = cx;

    NeedUpdate( true );
}

int CElementUI::GetFixedHeight() const
{
    return m_cxyFixed.cy;
}

void CElementUI::SetFixedHeight( int cy )
{
    if ( cy < 0 ) return;
    if ( m_cxyFixed.cy == cy ) return;
    m_cxyFixed.cy = cy;

    NeedUpdate( true );
}

int CElementUI::GetMinWidth() const
{
    return m_cxyMin.cx;
}

void CElementUI::SetMinWidth( int cx )
{
    if ( cx < 0 ) return;
    if ( m_cxyMin.cx == cx ) return;
    m_cxyMin.cx = cx;

    NeedUpdate( true );
}

int CElementUI::GetMaxWidth() const
{
    return m_cxyMax.cx;
}

void CElementUI::SetMaxWidth( int cx )
{
    if ( cx < 0 ) return;
    if ( m_cxyMax.cx == cx ) return;
    m_cxyMax.cx = cx;

    NeedUpdate( true );

}

int CElementUI::GetMinHeight() const
{
    return m_cxyMin.cy;
}

void CElementUI::SetMinHeight( int cy )
{
    if ( cy < 0 ) return;
    if ( m_cxyMin.cy == cy ) return;
    m_cxyMin.cy = cy;

    NeedUpdate( true );
}

int CElementUI::GetMaxHeight() const
{
    return m_cxyMax.cy;
}

void CElementUI::SetMaxHeight( int cy )
{
    if ( cy < 0 ) return;
    if ( m_cxyMax.cy == cy ) return;
    m_cxyMax.cy = cy;

    NeedUpdate( true );
}

int CElementUI::GetVerticalAlignment() const
{
    return m_iVerticalAlignment;
}

void CElementUI::SetVerticalAlignment( int alignment/*=UIALIGNMENT_STRETCH*/ )
{
    if ( m_iVerticalAlignment == alignment )return;
    m_iVerticalAlignment = alignment;

    NeedParentUpdate( false );
}

int CElementUI::GetHorizontalAlignment() const
{
    return m_iHorizontalAlignment;
}

void CElementUI::SetHorizontalAlignment( int alignment/*=UIALIGNMENT_STRETCH*/ )
{
    if ( m_iHorizontalAlignment == alignment )return;
    m_iHorizontalAlignment = alignment;

    NeedParentUpdate( false );
}
int CElementUI::GetDockSide() const
{
	return m_iDockSide;
}
void CElementUI::SetDockSide(int side)
{
	if(m_iDockSide==side)return;

	m_iDockSide=side;
	NeedParentUpdate(true);
}
TCHAR CElementUI::GetShortcut() const
{
    return m_chShortcut;
}

void CElementUI::SetShortcut( TCHAR ch )
{

    m_chShortcut = ch;
}

LPCTSTR CElementUI::GetToolTip() const
{
    return m_sToolTip;
}

void CElementUI::SetToolTip( LPCTSTR pstrText )
{
    m_sToolTip = pstrText;
}

LPCTSTR CElementUI::GetUserData() const
{
    return m_sUserData;
}

void CElementUI::SetUserData( LPCTSTR pstrText )
{
    m_sUserData = pstrText;
}

UINT_PTR CElementUI::GetTag() const
{
    return m_pTag;
}

void CElementUI::SetTag( UINT_PTR pTag )
{
    m_pTag = pTag;
}

bool CElementUI::IsVisible() const
{
    return m_bVisible && m_bInternVisible;
}

void CElementUI::SetVisible( bool bVisible /*= true */ )
{
    if ( m_bVisible == bVisible ) return;

    bool v = IsVisible();
    m_bVisible = bVisible;
    //取消焦点
    if ( m_bFocused && !IsVisible() ) {
        m_bFocused = false;

        if ( m_pManager && m_pManager->GetFocus() == this ) m_pManager->SetFocus( NULL );
    }
    //下面成立说明internVisible一定为真
    //既是已经子不可见则没必要上级更新
    if ( IsVisible() != v ) {
        //不显示了所以要更新
        NeedParentUpdate( true );
    }
}

void CElementUI::SetInternVisible( bool bVisible /*= true */ )
{
    m_bInternVisible = bVisible;

    if ( m_bFocused && !IsVisible() ) {
        m_bFocused = false;

        if ( m_pManager && m_pManager->GetFocus() == this ) m_pManager->SetFocus( NULL );
    }
}

bool CElementUI::IsEnabled() const
{
    return m_bEnabled && m_bInternEnabled;
}

void CElementUI::SetEnabled( bool bEnabled /*= true */ )
{
    if ( m_bEnabled == bEnabled ) return;
    m_bEnabled = bEnabled;

    if ( !m_bEnabled )
        ResetState();
    Invalidate();
}
void CElementUI::SetInternEnabled( bool bEnabled )
{
    m_bInternEnabled = bEnabled;
}
bool CElementUI::IsMouseEnabled() const
{
    return m_bMouseEnabled && m_bInternMouseEnabled;
}

void CElementUI::SetMouseEnabled( bool bEnabled /*= true */ )
{
    m_bMouseEnabled = bEnabled;
}
void CElementUI::SetInternMouseEnabled( bool bEnabled )
{
    m_bInternMouseEnabled = bEnabled;
}
bool CElementUI::IsFocused() const
{
    return m_bFocused;
}

void CElementUI::SetFocus()
{
    if ( m_pManager != NULL ) m_pManager->SetFocus( this );
}

bool CElementUI::IsCanFocus() const
{
    return m_bCanFocus;
}

void CElementUI::SetCanFocus( bool bCanFocus /*= true*/ )
{
    if ( m_bCanFocus == bCanFocus ) return;
    m_bCanFocus = bCanFocus;

    if ( m_bFocused ) {
        m_bFocused = false;

        if ( m_pManager && m_pManager->GetFocus() == this ) m_pManager->SetFocus( NULL );
    }
    Invalidate();
}

CElementUI* CElementUI::FindControl( FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags )
{
    if ( ( uFlags & UIFIND_VISIBLE ) != 0 && !IsVisible() ) return NULL;
    if ( ( uFlags & UIFIND_ENABLED ) != 0 && !IsEnabled() ) return NULL;
    //HITTEST设定时，禁止鼠标或者鼠标不在范围则过滤
    if ( ( uFlags & UIFIND_HITTEST ) != 0 && ( !m_bMouseEnabled || !::PtInRect( &m_rcItem, * reinterpret_cast<LPPOINT>( pData ) ) ) ) return NULL;
    if ( ( uFlags & UIFIND_CAN_FOCUS ) != 0 && !IsCanFocus() ) return NULL;
    return Proc( this, pData );
}

void CElementUI::Invalidate()
{
    if ( !IsVisible() ) return;

    Invalidate( m_rcItem );
}
void CElementUI::Invalidate( const RECT& rc )
{
    if ( !IsVisible() ) return;

    CRect invalidateRc = rc;
    CElementUI* pParent = this;

    RECT rcParent;
    while ( pParent = pParent->GetParent() ) {

        rcParent = pParent->GetPos();
        invalidateRc.Intersect( rcParent );
        if ( invalidateRc.IsEmpty() ) {
            return;
        }
    }
    if ( m_pManager != NULL )
        m_pManager->Invalidate( invalidateRc );
}
bool CElementUI::IsUpdateNeeded() const
{
    return m_bUpdateNeeded;
}

void CElementUI::NeedUpdate( bool bUpdateLayout )
{
    //测试做法,尝试性
    //如果未标志更新则
    if ( m_bUpdateNeeded != true && bUpdateLayout ) {
        m_bUpdateNeeded = true;
        SIZE szItemDesiredRemind = m_szItemDesired;
        EstimateSize( m_szEstimateRemind, true );
        if ( szItemDesiredRemind.cx != m_szItemDesired.cx ||
                szItemDesiredRemind.cy != m_szItemDesired.cy ) {
            if ( m_pParent )
                m_pParent->NeedUpdate( bUpdateLayout );
        }
    }
    Invalidate();

    if ( m_pManager != NULL ) m_pManager->NeedUpdate();
}

void CElementUI::NeedParentUpdate( bool bUpdateLayout )
{
    //测试
    //这样要保证，这个元素在Update查找树上比父系晚，应该要晚些
    //怎么查找都是先父元素后子元素


    if ( GetParent() ) {
        GetParent()->NeedUpdate( bUpdateLayout );
        //GetParent()->Invalidate();
    }
    else {
        NeedUpdate( bUpdateLayout );
    }

    if ( m_pManager != NULL ) m_pManager->NeedUpdate();
}

void CElementUI::Init()
{

}

void CElementUI::ResetState()
{

}

void CElementUI::Event( TEventUI& event )
{
    if ( event.Type == UIEVENT_SETCURSOR ) {
        ::SetCursor( ::LoadCursor( NULL, MAKEINTRESOURCE( IDC_ARROW ) ) );
        return;
    }
    if ( event.Type == UIEVENT_SETFOCUS ) {
        m_bFocused = true;
        return;
    }
    if ( event.Type == UIEVENT_KILLFOCUS ) {
        m_bFocused = false;
        return;
    }
    if ( event.Type == UIEVENT_TIMER ) {
        m_pManager->SendNotify( this, _T( "timer" ), event.wParam, event.lParam );
        return;
    }
    if ( m_pParent != NULL ) m_pParent->Event( event );
}

void CElementUI::SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue )
{
    if ( _tcscmp( pstrName, _T( "pos" ) ) == 0 ) {
        RECT rcPos = RectFromString( pstrValue );
        SIZE szXY = {rcPos.left >= 0 ? rcPos.left : rcPos.right, rcPos.top >= 0 ? rcPos.top : rcPos.bottom};
        SetFixedXY( szXY );
        SetFixedWidth( rcPos.right - rcPos.left );
        SetFixedHeight( rcPos.bottom - rcPos.top );
    }
    else if ( _tcscmp( pstrName, _T( "padding" ) ) == 0 ) {
        SetPadding( RectFromString( pstrValue ) );
    }
    else if ( _tcscmp( pstrName, _T( "width" ) ) == 0 ) SetFixedWidth( _ttoi( pstrValue ) );
    else if ( _tcscmp( pstrName, _T( "height" ) ) == 0 ) SetFixedHeight( _ttoi( pstrValue ) );
    else if ( _tcscmp( pstrName, _T( "minwidth" ) ) == 0 ) SetMinWidth( _ttoi( pstrValue ) );
    else if ( _tcscmp( pstrName, _T( "minheight" ) ) == 0 ) SetMinHeight( _ttoi( pstrValue ) );
    else if ( _tcscmp( pstrName, _T( "maxwidth" ) ) == 0 ) SetMaxWidth( _ttoi( pstrValue ) );
    else if ( _tcscmp( pstrName, _T( "maxheight" ) ) == 0 ) SetMaxHeight( _ttoi( pstrValue ) );
    else if ( _tcscmp( pstrName, _T( "name" ) ) == 0 ) SetName( pstrValue );
    else if ( _tcscmp( pstrName, _T( "tooltip" ) ) == 0 ) SetToolTip( pstrValue );
    else if ( _tcscmp( pstrName, _T( "userdata" ) ) == 0 ) SetUserData( pstrValue );
    else if ( _tcscmp( pstrName, _T( "enabled" ) ) == 0 ) SetEnabled( _tcscmp( pstrValue, _T( "true" ) ) == 0 );
    else if ( _tcscmp( pstrName, _T( "mouse" ) ) == 0 ) SetMouseEnabled( _tcscmp( pstrValue, _T( "true" ) ) == 0 );
    else if ( _tcscmp( pstrName, _T( "visible" ) ) == 0 ) SetVisible( _tcscmp( pstrValue, _T( "true" ) ) == 0 );
    else if ( _tcscmp( pstrName, _T( "shortcut" ) ) == 0 ) SetShortcut( pstrValue[0] );
    else if ( _tcscmp( pstrName, _T( "canfocus" ) ) == 0 ) SetCanFocus( _tcscmp( pstrValue, _T( "true" ) ) == 0 );
    else if ( _tcscmp( pstrName, _T( "verticalalignment" ) ) == 0 ) {
        if ( _tcscmp( pstrValue, _T( "top" ) ) == 0 )
            m_iVerticalAlignment = UIALIGNMENT_LEFT_TOP;
        else if ( _tcscmp( pstrValue, _T( "center" ) ) == 0 )
            m_iVerticalAlignment = UIALIGNMENT_CENTER;
        else if ( _tcscmp( pstrValue, _T( "bottom" ) ) == 0 )
            m_iVerticalAlignment = UIALIGNMENT_RIGHT_BOTTOM;
    }
    else if ( _tcscmp( pstrName, _T( "horizontalalignment" ) ) == 0 ) {
        if ( _tcscmp( pstrValue, _T( "left" ) ) == 0 )
            m_iHorizontalAlignment = UIALIGNMENT_LEFT_TOP;
        else if ( _tcscmp( pstrValue, _T( "center" ) ) == 0 )
            m_iHorizontalAlignment = UIALIGNMENT_CENTER;
        else if ( _tcscmp( pstrValue, _T( "right" ) ) == 0 )
            m_iHorizontalAlignment = UIALIGNMENT_RIGHT_BOTTOM;
    }
	else if(_tcscmp(pstrName,_T("dockside"))==0)
	{
		if(_tcscmp(pstrValue,_T("top"))==0)
			m_iDockSide=UIDOCK_TOP;
		else if(_tcscmp(pstrValue,_T("right"))==0)
			m_iDockSide=UIDOCK_RIGHT;
		else if(_tcscmp(pstrValue,_T("bottom"))==0)
			m_iDockSide=UIDOCK_BOTTOM;
	}
}

void CElementUI::ApplyAttributeList( LPCTSTR pstrList )
{
    CMarkupMSXML xml;
    CStdString sParse = _T( "<temp " ) + CStdString( pstrList ) + _T( " />" );
    if ( !xml.SetDoc( sParse ) )
        return;
    xml.FindElem();

    CStdString sItem;
    CStdString sValue;
    int it = 0;

    while ( sItem = xml.GetAttribName( it++ ), !sItem.IsEmpty() ) {
        sValue = xml.GetAttrib( sItem );
        SetAttribute( sItem, sValue );
    }
}

void CElementUI::DoPaint( GRAPHorHDC& gorh, const RECT& rcPaint )
{
    //这种模式是无法像绘制超出处理的
    if ( !::IntersectRect( &m_rcPaint, &rcPaint, &m_rcItem ) ) return;
    CRgn oldRegion = gorh.IntersectClip( m_rcPaint );

    DoPaintOver( gorh );

    gorh.SetClip( oldRegion );
}
void CElementUI::DoPaintOver( GRAPHorHDC& gorh )
{

}
void CElementUI::DoPostPaint( GRAPHorHDC& gorh, const RECT& rcPaint )
{
}
