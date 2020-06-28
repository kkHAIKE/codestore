#ifndef __UIMANAGER_H__
#define __UIMANAGER_H__
#pragma once


/////////////////////////////////////////////////////////////////////////////////////
//

class CElementUI;
class GRAPHorHDC;

/////////////////////////////////////////////////////////////////////////////////////
//

enum EVENTTYPE_UI {
    UIEVENT__FIRST = 0,

    UIEVENT__KEYBEGIN,
    UIEVENT_KEYDOWN,
    UIEVENT_KEYUP,
    UIEVENT_CHAR,
    UIEVENT_SYSKEY,
    UIEVENT__KEYEND,

    UIEVENT__MOUSEBEGIN,
    UIEVENT_MOUSEMOVE,
    UIEVENT_MOUSELEAVE,
    UIEVENT_MOUSEENTER,
    UIEVENT_MOUSEHOVER,
    UIEVENT_BUTTONDOWN,
    UIEVENT_BUTTONUP,
    UIEVENT_DBLCLICK,
    UIEVENT_CONTEXTMENU,
    UIEVENT_SCROLLWHEEL,
    UIEVENT__MOUSEEND,

    UIEVENT_KILLFOCUS,
    UIEVENT_SETFOCUS,
    UIEVENT_WINDOWSIZE,
    UIEVENT_SETCURSOR,
    UIEVENT_TIMER,

    //UIEVENT_MEASUREITEM,
    //UIEVENT_DRAWITEM,
    //UIEVENT_NOTIFY,
    //UIEVENT_COMMAND,

    UIEVENT__LAST
};

/////////////////////////////////////////////////////////////////////////////////////
//
enum {
    UIALIGNMENT_LEFT_TOP = 0,
    UIALIGNMENT_CENTER,
    UIALIGNMENT_RIGHT_BOTTOM,
    UIALIGNMENT_STRETCH
};
enum {
	UIDOCK_LEFT=0,
	UIDOCK_TOP,
	UIDOCK_RIGHT,
	UIDOCK_BOTTOM
};

// Flags for CControlUI::GetControlFlags()
#define UIFLAG_TABSTOP       0x00000001
#define UIFLAG_SETCURSOR     0x00000002
#define UIFLAG_WANTRETURN    0x00000004  //���ջس�

// Flags for FindControl()
#define UIFIND_ALL           0x00000000
#define UIFIND_VISIBLE       0x00000001
#define UIFIND_ENABLED       0x00000002
#define UIFIND_HITTEST       0x00000004  //������ԣ����������������ҷ�Ӧ
#define UIFIND_TOP_FIRST     0x00000008
#define UIFIND_CAN_FOCUS     0x00000010
#define UIFIND_ME_FIRST      0x80000000

// Flags for the CDialogLayout stretching
#define UISTRETCH_NEWGROUP   0x00000001
#define UISTRETCH_NEWLINE    0x00000002
#define UISTRETCH_MOVE_X     0x00000004
#define UISTRETCH_MOVE_Y     0x00000008
#define UISTRETCH_SIZE_X     0x00000010
#define UISTRETCH_SIZE_Y     0x00000020

// Flags used for controlling the paint
#define UISTATE_FOCUSED      0x00000001
#define UISTATE_CHECKED      0x00000002
#define UISTATE_SELECTED     0x00000004
#define UISTATE_DISABLED     0x00000008
#define UISTATE_HOT          0x00000010  //������������
#define UISTATE_PUSHED       0x00000020
#define UISTATE_READONLY     0x00000040
#define UISTATE_CAPTURED     0x00000080

#define UIMES_DELAYCLEAR		WM_APP + 1
/////////////////////////////////////////////////////////////////////////////////////
//
class TFontInfo
{
public:
    TFontInfo( HFONT font ) {
        ASSERT( font );
        hFont = font;
    }
    ~TFontInfo() {
        ::DeleteObject( hFont );
    }

    HFONT hFont;
    TEXTMETRIC tm;
};

typedef struct tagFINDTABINFO {
    CElementUI* pFocus;
    CElementUI* pLast;
    bool bForward;
    bool bNextIsIt;
} FINDTABINFO;

typedef struct tagFINDSHORTCUT {
    TCHAR ch;
    bool bPickNext;
} FINDSHORTCUT;

typedef struct tagTIMERINFO {
    CElementUI* pSender;
    UINT nLocalID;
    HWND hWnd;
    UINT uWinTimer;
    bool bKilled;
} TIMERINFO;

// Structure for notifications from the system
// to the control implementation.
typedef struct tagTEventUI {
    int Type;
    CElementUI* pSender;
    DWORD dwTimestamp;

    POINT ptMouse;
    TCHAR chKey;
    WORD wKeyState;

    WPARAM wParam;
    LPARAM lParam;
} TEventUI;

// Structure for notifications to the outside world
typedef struct tagTNotifyUI {
    CStdString sType;
    CElementUI* pSender;
    DWORD dwTimestamp;

    POINT ptMouse;

    WPARAM wParam;
    LPARAM lParam;
} TNotifyUI;

// Listener interface
class INotifyUI
{
public:
    virtual void Notify( TNotifyUI& msg ) = 0;
};

// MessageFilter interface
class IMessageFilterUI
{
public:
    virtual LRESULT MessageHandler( UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled ) = 0;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CPaintManagerUI
{
public:
    CPaintManagerUI();
    ~CPaintManagerUI();

public:
    void Init( HWND hWnd );
    void NeedUpdate();
    void Invalidate( const RECT& rcItem );

    GRAPHorHDC* GetPaintDC() const;
    HWND GetPaintWindow() const;

    POINT GetMousePos() const;
    SIZE GetClientSize() const;
    SIZE GetInitSize() const;
    void SetInitSize( int cx, int cy );
    const RECT& GetSizeBox() const;
    void SetSizeBox( const RECT& rcSizeBox );
    const RECT& GetCaptionRect() const;
    void SetCaptionRect( const RECT& rcCaption );
    RECT GetRoundCorner() const;
    void SetRoundCorner( const RECT& rcRoundCorner );
    void SetMinMaxInfo( int cx, int cy );
    void SetShowUpdateRect( bool show );

    static HINSTANCE GetResourceInstance();
    static HINSTANCE GetLanguageInstance();
    static void SetResourceInstance( HINSTANCE hInst );
    static void SetLanguageInstance( HINSTANCE hInst );

    bool UseParentResource( CPaintManagerUI* pm );
    CPaintManagerUI* GetParentResource() const;

    DWORD GetDefaultDisabledColor() const;
    void SetDefaultDisabledColor( DWORD dwColor = 0xFFA7A6AA );

    HFONT GetDefaultFont() const;
    DWORD GetDefaultFontColor() const;
    const TEXTMETRIC& GetDefaultFontInfo();
    void SetDefaultFont( HFONT hFont, DWORD dwColor = 0xFF000000 );

    HFONT GetDefaultBoldFont() const;
    const TEXTMETRIC& GetDefaultBoldFontInfo();
    void SetDefaultBoldFont( HFONT hFont, DWORD dwColor = 0xFF000000 );

    HFONT GetDefaultLinkFont() const;
    DWORD GetDefaultLinkFontColor() const;
    DWORD GetDefaultLinkFontHoverColor() const;
    const TEXTMETRIC& GetDefaultLinkFontInfo();
    void SetDefaultLinkFont( HFONT hFont, DWORD dwColor = 0xFF0000FF, DWORD dwHoverColor = 0xFFD3215F );

    bool AddFont( HFONT hFont );
    HFONT AddFont( LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic );
    // 	bool AddFontAt( int index, HFONT hFont );
    // 	HFONT AddFontAt( int index, LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline );
    HFONT GetFont( int index ) const;
    void SetFont( int index, HFONT hFont );
    bool FindFont( HFONT hFont ) const;
    // 	bool RemoveFont( HFONT hFont );
    // 	bool RemoveFontAt( int index );
    void RemoveAllFonts();
    const TEXTMETRIC& GetFontInfo( int index );

    Bitmap* GetImage( LPCTSTR bitmap ) const;
    Bitmap* GetImageEx( LPCTSTR bitmap, LPCTSTR type = NULL );
    Bitmap* AddImage( LPCTSTR bitmap, LPCTSTR type = NULL );
    //bool RemoveImage( LPCTSTR bitmap );
    void RemoveAllImages();

    void AddDefaultAttributeList( LPCTSTR pStrControlName, LPCTSTR pStrControlAttrList );
    LPCTSTR GetDefaultAttributeList( LPCTSTR pStrControlName ) const;
    bool RemoveDefaultAttributeList( LPCTSTR pStrControlName );
    void RemoveAllDefaultAttributeList();

    bool AttachDialog( CElementUI* pControl );
    bool InitControls( CElementUI* pControl, CElementUI* pParent = NULL );
    //�Ƴ�һ���ؼ�
    void ReapObjects( CElementUI* pControl );

    CElementUI* GetFocus() const;
    void SetFocus( CElementUI* pControl );
    bool SetNextTabControl( bool bForward = true );

    bool SetTimer( CElementUI* pControl, UINT nTimerID, UINT uElapse );
    bool KillTimer( CElementUI* pControl, UINT nTimerID );

    void SetCapture();
    void ReleaseCapture();

    bool AddNotifier( INotifyUI* pControl );
    bool RemoveNotifier( INotifyUI* pControl );
    void SendNotify( TNotifyUI& Msg );
    void SendNotify( CElementUI* pControl, LPCTSTR pstrMessage, WPARAM wParam = 0, LPARAM lParam = 0 );

    bool AddMessageFilter( IMessageFilterUI* pFilter );
    bool RemoveMessageFilter( IMessageFilterUI* pFilter );

    int GetPostPaintCount() const;
    bool AddPostPaint( CElementUI* pControl );
    bool RemovePostPaint( CElementUI* pControl );
    //bool SetPostPaintIndex( CControlUI* pControl, int iIndex );

    CElementUI* GetRoot() const;
    CElementUI* FindControl( POINT pt ) const;
    CElementUI* FindControl( LPCTSTR pstrName );

    static void MessageLoop();
    static bool TranslateMessage( const LPMSG pMsg );

    bool MessageHandler( UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes );
    bool PreMessageHandler( UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes );

private:
    static CElementUI* CALLBACK __FindControlFromNameHash( CElementUI* pThis, LPVOID pData );
    static CElementUI* CALLBACK __FindControlFromCount( CElementUI* pThis, LPVOID pData );
    static CElementUI* CALLBACK __FindControlFromPoint( CElementUI* pThis, LPVOID pData );
    static CElementUI* CALLBACK __FindControlFromTab( CElementUI* pThis, LPVOID pData );
    static CElementUI* CALLBACK __FindControlFromShortcut( CElementUI* pThis, LPVOID pData );
    static CElementUI* CALLBACK __FindControlFromUpdate( CElementUI* pThis, LPVOID pData );

private:
    HWND m_hWndPaint;
    GRAPHorHDC* m_hDcPaint;
    //������ͼ
    GRAPHorHDC* m_hDcOffscreen;
    HBITMAP m_hbmpOffscreen;
    bool m_bOffscreenPaint;
    //��ʾ���
    HWND m_hwndTooltip;
    TOOLINFO m_ToolTip;
    //��ʾ�������򣬵�����
    bool m_bShowUpdateRect;
    //��ǰ�󶨵ĶԻ���
    CElementUI* m_pRoot;
    //��ǰ����ؼ�
    CElementUI* m_pFocus;
    CElementUI* m_pFocusBackup;
    //���漤������϶��¼��Ŀؼ�
    CElementUI* m_pEventHover;
    bool m_bMouseTracking;
    //���漤����갴���¼��Ŀؼ������ڼ�����������¼�
    CElementUI* m_pEventClick;
    //���漤�����̰����¼��Ŀؼ������ڼ������̵����¼�
    CElementUI* m_pEventKey;
    //�κ�����¼��������¼
    POINT m_ptLastMousePos;
    //��С���ڳߴ�
    SIZE m_szMinWindow;
    //��ʼ���ڳߴ�
    SIZE m_szInitWindowSize;
    //���ڿ�����
    RECT m_rcSizeBox;
    //Բ��
    RECT m_szRoundCorner;
    //������
    RECT m_rcCaption;
    //����TimerID
    UINT m_uTimerID;
    //���ڵ�һ�λ���
    bool m_bFirstLayout;
    //���ø��±�־
    bool m_bUpdateNeeded;
    //�л�����ʱ����
    bool m_bFocusNeeded;
    //������⶯��ʱ���ı����ͼ��
    bool m_bMouseCapture;

    CStdPtrArray<INotifyUI> m_aNotifiers;
    CStdPtrArray<TIMERINFO> m_aTimers;
    CStdPtrArray<IMessageFilterUI> m_aMessageFilters;
    //����PostPaint�Ŀؼ��б�
    CStdPtrArray<CElementUI> m_aPostPaintControls;
    CStdPtrArray<CElementUI> m_aDelayedCleanup;
    CStdStringPtrMap<CElementUI*> m_mNameHash;

    DWORD m_dwDefalutDisabledColor;
    /////////////////////////////////////
    HFONT m_hDefalutFont;
    TEXTMETRIC m_hDefalutFontTextMetric;
    DWORD m_dwDefalutFontColor;

    HFONT m_hDefalutBoldFont;
    TEXTMETRIC m_hDefaluttBoldFontTextMetric;

    HFONT m_hDefalutLinkFont;
    TEXTMETRIC m_hDefalutLinkFontTextMetric;
    DWORD m_dwDefalutLinkFontColor;
    DWORD m_dwDefalutLinkFontHoverColor;

    CStdPtrArray<TFontInfo> m_aCustomFonts;
    /////////////////////////////////////
    CStdStringPtrMap<Bitmap*> m_mImageHash;
    CStdStringPtrMap<CStdString*> m_DefaultAttrHash;
    //��PM�������������Դ
    CPaintManagerUI* m_pParentResourcePM;

    static HINSTANCE m_hInstance;
    //static HINSTANCE m_hLangInst;
    static CStdPtrArray<CPaintManagerUI> m_aPreMessages;
};

/////////////////////////////////////////////////////////////////////////////////////
//

typedef CElementUI* ( CALLBACK* FINDCONTROLPROC )( CElementUI*, LPVOID );


class UILIB_API CElementUI
{
public:
    CElementUI();
    virtual ~CElementUI();

public:
    virtual CStdString GetName() const;
    virtual void SetName( LPCTSTR pstrName );

    virtual LPCTSTR GetClass() const;
    virtual LPVOID GetInterface( LPCTSTR pstrName );
    virtual UINT GetControlFlags() const;

    virtual bool Activate();
    virtual CPaintManagerUI* GetManager() const;
    virtual void SetManager( CPaintManagerUI* pManager, CElementUI* pParent, bool bInit = true );
    virtual CElementUI* GetParent() const;

    bool DrawImage( GRAPHorHDC& gorh, LPCTSTR pStrImage, LPCTSTR pStrModify = NULL );

    // λ�����
    virtual SIZE GetDesiredSize() const;
    //�Ӹ�ǿ�вⶨ��Ĭ��Ϊ��
    void EstimateSize( const SIZE& szAvailable , bool bForce = false );
    virtual void EstimateSizeMain( const SIZE& szAvailable );
    virtual SIZE EstimateSizeOver( const SIZE& szAvailable );
    virtual RECT GetPos() const;		//һ�������2��
    void SetPos( const RECT& rc );
    virtual void SetPosMain( const RECT& rc );
    virtual RECT SetPosOver ( const RECT& rc );
    virtual int GetWidth() const;
    virtual int GetHeight() const;
    virtual int GetX() const;
    virtual int GetY() const;
    virtual RECT GetPadding() const;
    virtual void SetPadding( const RECT& rcPadding ); // ������߾࣬���ϲ㴰�ڻ���
    virtual SIZE GetFixedXY() const;         // ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ
    virtual void SetFixedXY( const SIZE& szXY );    // ��floatΪtrueʱ��Ч
    virtual int GetFixedWidth() const;       // ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ
    virtual void SetFixedWidth( int cx );    // Ԥ��Ĳο�ֵ
    virtual int GetFixedHeight() const;      // ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ
    virtual void SetFixedHeight( int cy );   // Ԥ��Ĳο�ֵ
    virtual int GetMinWidth() const;
    virtual void SetMinWidth( int cx );
    virtual int GetMaxWidth() const;
    virtual void SetMaxWidth( int cx );
    virtual int GetMinHeight() const;
    virtual void SetMinHeight( int cy );
    virtual int GetMaxHeight() const;
    virtual void SetMaxHeight( int cy );
    virtual int GetVerticalAlignment() const;
    virtual void SetVerticalAlignment( int alignment = UIALIGNMENT_STRETCH );
    virtual int GetHorizontalAlignment()const;
    virtual void SetHorizontalAlignment( int alignment = UIALIGNMENT_STRETCH );
	virtual int GetDockSide() const;
	virtual void SetDockSide(int side=UIDOCK_LEFT);
    // ��ݼ�
    virtual TCHAR GetShortcut() const;
    virtual void SetShortcut( TCHAR ch );

    // �����ʾ
    virtual LPCTSTR GetToolTip() const;
    virtual void SetToolTip( LPCTSTR pstrText );

    // �û�����
    virtual LPCTSTR GetUserData() const; // �������������û�ʹ��
    virtual void SetUserData( LPCTSTR pstrText ); // �������������û�ʹ��
    virtual UINT_PTR GetTag() const; // �������������û�ʹ��
    virtual void SetTag( UINT_PTR pTag ); // �������������û�ʹ��

    // һЩ��Ҫ������
    virtual bool IsVisible() const;
    virtual void SetVisible( bool bVisible = true );
    virtual void SetInternVisible( bool bVisible = true ); // �����ڲ����ã���ЩUIӵ�д��ھ������Ҫ��д�˺���
    virtual bool IsEnabled() const;
    virtual void SetEnabled( bool bEnabled = true );
    virtual void SetInternEnabled( bool bEnabled = true );
    virtual bool IsMouseEnabled() const;
    virtual void SetMouseEnabled( bool bEnabled = true );
    virtual void SetInternMouseEnabled( bool bEnabled = true );
    virtual bool IsFocused() const;
    virtual void SetFocus();
    virtual bool IsCanFocus() const;
    virtual void SetCanFocus( bool bCanFocus = true );

    virtual CElementUI* FindControl( FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags );

    virtual void Invalidate();
    void Invalidate( const RECT& rc );
    bool IsUpdateNeeded() const;
    void NeedUpdate( bool bUpdateLayout );
    void NeedParentUpdate( bool bUpdateLayout );

    virtual void Init();
    virtual void ResetState();
    virtual void Event( TEventUI& event );

    virtual void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );
    void ApplyAttributeList( LPCTSTR pstrList );

    void DoPaint( GRAPHorHDC& gorh, const RECT& rcPaint );
    virtual void DoPaintOver( GRAPHorHDC& gorh );
    virtual void DoPostPaint( GRAPHorHDC& gorh, const RECT& rcPaint );

protected:
    CPaintManagerUI* m_pManager;
    CElementUI* m_pParent;

    bool m_bUpdateNeeded;
    RECT m_rcPaint;

    //�ؼ���Χ
    RECT m_rcItem;
    //�������
    SIZE m_szItemDesired;
    //�ϴβ���������
    SIZE m_szEstimateRemind;
    //�ϴ�setpos������
    RECT m_rcSetposRemind;
    //��Ȧ�߾�
    RECT m_rcPadding;
    //��Ը����ڵ����꣬��Ϊnear����Ϊfar
    SIZE m_cXY;
    //�ؼ���С
    SIZE m_cxyFixed;
    SIZE m_cxyMin;
    SIZE m_cxyMax;

    bool m_bVisible;
    bool m_bInternVisible;
    bool m_bEnabled;
    bool m_bInternEnabled;
    bool m_bMouseEnabled;
    bool m_bInternMouseEnabled;
    bool m_bFocused;
    bool m_bCanFocus;

    CStdString m_sName;
    CStdString m_sToolTip;
    TCHAR m_chShortcut;
    CStdString m_sUserData;
    UINT_PTR m_pTag;

    int m_iVerticalAlignment;
    int m_iHorizontalAlignment;

	int m_iDockSide;
};


class UILIB_API CControlUI: public CElementUI
{
    DECLARE_DYNCREATE( CControlUI )
public:
    CControlUI();

public:

    LPCTSTR GetClass() const;
    LPVOID GetInterface( LPCTSTR pstrName );
    UINT GetControlFlags() const;

    // ͼ�����
    DWORD GetBkColor() const;
    void SetBkColor( DWORD dwBackColor );
    DWORD GetBkColor2() const;
    void SetBkColor2( DWORD dwBackColor );
    LPCTSTR GetBkImage() const;
    void SetBkImage( LPCTSTR pStrImage );
    DWORD GetBorderColor() const;
    void SetBorderColor( DWORD dwBorderColor );
    RECT GetBorderSize() const;
    void SetBorderSize( const RECT& nSize );

    // λ�����
    void EstimateSizeMain( const SIZE& szAvailable );
    void SetPosMain( const RECT& rc );
    virtual RECT GetInset() const;
    virtual void SetInset( const RECT& rcInset );
    virtual int GetVerticalContentAlignment() const;
    virtual void SetVerticalContentAlignment( int alignment = UIALIGNMENT_STRETCH );
    virtual int GetHorizontalContentAlignment()const;
    virtual void SetHorizontalContentAlignment( int alignment = UIALIGNMENT_STRETCH );

    virtual bool IsTabStop() const;
    virtual void SetTabStop( bool bTabStop = true );
    virtual bool IsNotUseDefSkin() const;
    virtual void SetNotUseDefSkin( bool bNotUseDefSkin = true );

    void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );

    void DoPaintOver( GRAPHorHDC& gorh );
    virtual void PaintBkColor( GRAPHorHDC& gorh );
    virtual void PaintBkImage( GRAPHorHDC& gorh );
    virtual void PaintStatusImage( GRAPHorHDC& gorh );
    virtual void PaintBorder( GRAPHorHDC& gorh );

protected:
    RECT m_rcInset;

    bool m_bTabStop;
    bool m_bNotUseDefSkin;

    DWORD m_dwBackColor;
    DWORD m_dwBackColor2;
    CStdString m_sBkImage;

    DWORD m_dwBorderColor;
    RECT m_nBorderSize;

    int m_iVerticalContentAlignment;
    int m_iHorizontalContentAlignment;

};

#endif // __UIMANAGER_H__