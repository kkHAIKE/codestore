#include "StdAfx.h"
#include "UIExtraControls.h"




/////////////////////////////////////////////////////////////////////////////////////
//
//从这里开始增加弹出容器

class CPopWnd: public CWindowWnd
{
public:
	CPopWnd()
	{

	}
	void Init(CPopContentControlUI * pOwner)
	{
		WS_POPUP, WS_EX_TOOLWINDOW,
	}
};


/////////////////////////////////////////////////////////////////////////////////////
//
//
IMPLEMENT_DYNCREATE( CMenuButtonUI )
CMenuButtonUI::CMenuButtonUI( void ): m_bIsMenuPopped( false ), m_hMenu( NULL )
{
}

LPCTSTR CMenuButtonUI::GetClass() const
{
    return _T( "MenuButtonUI" );
}

LPVOID CMenuButtonUI::GetInterface( LPCTSTR pstrName )
{
    if ( _tcscmp( pstrName, _T( "MenuButton" ) ) == 0 ) return static_cast<CMenuButtonUI*>( this );
    return CButtonUI::GetInterface( pstrName );
}

UINT CMenuButtonUI::GetControlFlags() const
{
    return 0;
}

bool CMenuButtonUI::Activate()
{
    if ( !CControlUI::Activate() ) return false;
    m_bIsMenuPopped = !m_bIsMenuPopped;

    if ( m_bIsMenuPopped ) {
        m_uButtonState |= UISTATE_PUSHED;

        if ( m_hMenu ) {
            //要给父窗口发送MouseUp
            if ( m_pManager ) m_pManager->ReleaseCapture();
               // ::SendMessage( m_pManager->GetPaintWindow(), WM_LBUTTONUP, NULL, NULL );

            POINT p = {m_rcItem.left, m_rcItem.bottom};
            ::ClientToScreen( m_pManager->GetPaintWindow(), &p );
            ::TrackPopupMenuEx( m_hMenu, TPM_LEFTALIGN | TPM_TOPALIGN | TPM_LEFTBUTTON, p.x, p.y, m_pManager->GetPaintWindow(), NULL );
        }
        m_bIsMenuPopped = false;
    }

    m_uButtonState &= ~UISTATE_PUSHED;

    return true;
}
HMENU CMenuButtonUI::GetMenu() const
{
    return m_hMenu;
}

void CMenuButtonUI::SetMenu( HMENU menu )
{
    m_hMenu = menu;
}
void CMenuButtonUI::Event( TEventUI& event )
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
    if ( event.Type == UIEVENT_BUTTONDOWN || event.Type == UIEVENT_DBLCLICK ) {
        if ( ::PtInRect( &m_rcItem, event.ptMouse ) && IsEnabled() ) {
            Activate();
            Invalidate();
        }
        return;
    }
    if ( event.Type == UIEVENT_BUTTONUP ) {
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

    CContentControlUI::Event( event );
}