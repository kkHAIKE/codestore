#pragma once

/////////////////////////////////////////////////////////////////////////////////////
//
#define GdiplusStartup(gditoken)\
    GdiplusStartupInput gdiinput;\
    ::GdiplusStartup(&gditoken,&gdiinput,NULL)

/////////////////////////////////////////////////////////////////////////////////////
//

#define BEGIN_CONTROLS_BIND() \
    public:\
    void Bind(){

#define END_CONTROLS_BIND() \
    }

#define CONTROL_BIND(mem,cla,name) \
    mem=dynamic_cast<cla*>(m_pm.FindControl(name));

//消息默认是截取的
#define BEGIN_MSG_MAP() \
    public: \
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)\
    {	LRESULT lRes = 0;\
        BOOL bHandled = TRUE;\
        switch( uMsg ) {

#define MESSAGE_HANDLER(msg, func) \
    case msg:        lRes = func(uMsg, wParam, lParam, bHandled); break;

#define END_MSG_MAP()\
    default:\
    bHandled = FALSE;}\
    if( bHandled ) return lRes;\
                          return CWindowWndImpl::HandleMessage(uMsg, wParam, lParam);}

#define END_MSG_BASE_MAP() \
    default:\
    bHandled = FALSE;}\
    if( bHandled ) return lRes;\
                          if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;\
                                  return CWindowWnd::HandleMessage(uMsg, wParam, lParam);}

/////////////////////////////////////////////////////////////////////////////////////
//
class UILIB_API CWindowWndImpl: public CWindowWnd, public INotifyUI
{
public:
    CWindowWndImpl() {};
    virtual LPCTSTR GetXmlName() const = 0;
    virtual LPCTSTR GetXmlType() const {return ( UINT )0;}

    UINT GetClassStyle() const { return CS_DBLCLKS; };
    void OnFinalMessage( HWND /*hWnd*/ ) { PostQuitMessage( 0 ); delete this; }
    virtual void Bind() {};
    virtual void Init() {};
    virtual void OnPrepare() {};
    void Notify( TNotifyUI& msg );
    virtual LRESULT OnCreate( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
    virtual LRESULT OnNcActivate( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled ) {return ( wParam == 0 ) ? TRUE : FALSE;}
    virtual LRESULT OnNcCalcSize( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled ) {return 0;}
    virtual LRESULT OnNcPaint( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled ) {return 0;}
    virtual LRESULT OnNcHitTest( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
    virtual LRESULT OnSize( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
    virtual LRESULT OnGetMinMaxInfo( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
    virtual LRESULT OnSysCommand( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );

    BEGIN_MSG_MAP()
    MESSAGE_HANDLER( WM_CREATE, OnCreate )
    MESSAGE_HANDLER( WM_NCACTIVATE, OnNcActivate )
    MESSAGE_HANDLER( WM_NCCALCSIZE, OnNcCalcSize )
    MESSAGE_HANDLER( WM_NCPAINT, OnNcPaint )
    MESSAGE_HANDLER( WM_NCHITTEST, OnNcHitTest )
    MESSAGE_HANDLER( WM_SIZE, OnSize )
    MESSAGE_HANDLER( WM_GETMINMAXINFO, OnGetMinMaxInfo )
    MESSAGE_HANDLER( WM_SYSCOMMAND, OnSysCommand )
    END_MSG_BASE_MAP()
public:
    CPaintManagerUI m_pm;

};