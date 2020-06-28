#pragma once

/////////////////////////////////////////////////////////////////////////////////////
//
class UILIB_API CPopContentControlUI:public CContentControlUI
{
public:

};

/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CMenuButtonUI: public CButtonUI
{
    DECLARE_DYNCREATE( CMenuButtonUI )
public:
    CMenuButtonUI( void );

    LPCTSTR GetClass() const;
    LPVOID GetInterface( LPCTSTR pstrName );
    UINT GetControlFlags() const;

    bool Activate();
    void Event( TEventUI& event );

    HMENU GetMenu() const;
    void SetMenu( HMENU menu );

protected:
    bool m_bIsMenuPopped;
    HMENU m_hMenu;
};
