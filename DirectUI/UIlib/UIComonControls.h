#ifndef __UICOMMONCONTROLS_H__
#define __UICOMMONCONTROLS_H__

#pragma once

/////////////////////////////////////////////////////////////////////////////////////
//
class UILIB_API CTextBlockUI: public CElementUI
{
    DECLARE_DYNCREATE( CTextBlockUI )
public:
    CTextBlockUI();
    LPCTSTR GetClass() const;
    LPVOID GetInterface( LPCTSTR pstrName );

    void SetText( LPCTSTR text );
    LPCTSTR GetText() const;
    void SetTextColor( DWORD color );
    DWORD GetTextColor() const;
    void SetDisabledTextColor( DWORD color );
    DWORD GetDisabledTextColor() const;
    void SetFont( int font );
    int GetFont() const;
    void SetMultiLine( bool multiLine = true );
    bool GetMultiLine() const;
    void SetTextStyle( int style );
    int GetTextStyle() const;

    SIZE EstimateSizeOver( const SIZE& szAvailable );

    void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );
    void DoPaintOver( GRAPHorHDC& gorh );

protected:
    CStdString m_szText;
    DWORD m_dwTextColor;
    DWORD m_dwDisabledTextColor;
    int m_iFont;
    int m_iFontStyle;
    bool m_bMultiLine;
};
/////////////////////////////////////////////////////////////////////////////////////
//
class UILIB_API CHtmlBlockUI: public CTextBlockUI
{
    DECLARE_DYNCREATE( CHtmlBlockUI )
public:
    CHtmlBlockUI();
    ~CHtmlBlockUI();

    LPCTSTR GetClass() const;
    UINT GetControlFlags() const;
    LPVOID GetInterface( LPCTSTR pstrName );

    LPCTSTR GetLinkContent( int iIndex );
    void Event( TEventUI& event );
    SIZE EstimateSizeOver( const SIZE& szAvailable );
    void DoPaintOver( GRAPHorHDC& gorh );
    void Invalidate();

protected:
    int m_nLinks;
    CRgn* m_rcLinks;
    CStdString* m_sLinks;
    int m_nHoverLink;
    bool m_bMouseToCallInvalidate;
};
/////////////////////////////////////////////////////////////////////////////////////
//
class UILIB_API CContentControlUI: public CControlUI
{
    DECLARE_DYNCREATE( CContentControlUI )
public:
    CContentControlUI();
    ~CContentControlUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface( LPCTSTR pstrName );

    CElementUI* GetContent() const;
    virtual void SetContent( CElementUI* content );

    SIZE EstimateSizeOver( const SIZE& szAvailable );
    RECT SetPosOver( const RECT& rc );

    virtual bool IsAutoDestroy() const;
    virtual void SetAutoDestroy( bool bAuto = true );

    void SetVisible( bool bVisible = true );
    void SetInternVisible( bool bVisible = true );
    void SetEnabled( bool bEnabled = true );
    void SetInternEnabled( bool bEnabled = true );
    void SetMouseEnabled( bool bEnabled = true );
    void SetInternMouseEnabled( bool bEnabled = true );

    void SetManager( CPaintManagerUI* pManager, CElementUI* pParent, bool bInit = true );
    CElementUI* FindControl( FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags );
    void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );

    void DoPaintOver( GRAPHorHDC& gorh );
    void PaintBkColor( GRAPHorHDC& gorh );
    virtual void PaintContent( GRAPHorHDC& gorh );

protected:
    CElementUI* m_pContent;
    bool m_bAutoDestroy;
};
/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CLabelUI : public CContentControlUI
{
    DECLARE_DYNCREATE( CLabelUI )
public:
    CLabelUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface( LPCTSTR pstrName );

    void SetContent( CElementUI* content );
};

/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CButtonUI : public CContentControlUI
{
    DECLARE_DYNCREATE( CButtonUI )
public:
    CButtonUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface( LPCTSTR pstrName );
    UINT GetControlFlags() const;

    bool Activate();
    void ResetState();
    void Event( TEventUI& event );

    LPCTSTR GetNormalImage();
    void SetNormalImage( LPCTSTR pStrImage );
    LPCTSTR GetHotImage();
    void SetHotImage( LPCTSTR pStrImage );
    LPCTSTR GetPushedImage();
    void SetPushedImage( LPCTSTR pStrImage );
    LPCTSTR GetFocusedImage();
    void SetFocusedImage( LPCTSTR pStrImage );
    LPCTSTR GetDisabledImage();
    void SetDisabledImage( LPCTSTR pStrImage );
    void SetHandUse( bool handuse );
    bool IsHandUse() const;
    void SetWantReturn( bool wantreturn );
    bool IsWantReturn() const;
    void SetWantSpace( bool wantspace );
    bool IsWantSpace() const;

    void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );

    void PaintStatusImage( GRAPHorHDC& gorh );
    virtual void PaintDefault( GRAPHorHDC& gorh );

protected:
    UINT m_uButtonState;
    bool m_bHandUse;
    bool m_bIsWantReturn;
    bool m_bIsWantSpace;

    CStdString m_sNormalImage;
    CStdString m_sHotImage;
    CStdString m_sPushedImage;
    CStdString m_sFocusedImage;
    CStdString m_sDisabledImage;
};

/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API COptionUI : public CButtonUI
{
    DECLARE_DYNCREATE( COptionUI )
public:
    COptionUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface( LPCTSTR pstrName );
    UINT GetControlFlags() const;

    bool Activate();

    LPCTSTR GetSelectedImage();
    void SetSelectedImage( LPCTSTR pStrImage );
    LPCTSTR GetHotSelectedImage();
    void SetHotSelectedImage( LPCTSTR pStrImage );
    LPCTSTR GetPushedSelectedImage();
    void SetPushedSelectedImage( LPCTSTR pStrImage );
    LPCTSTR GetFocusedSelectedImage();
    void SetFocusedSelectedImage( LPCTSTR pStrImage );
    LPCTSTR GetDisabledSelectedImage();
    void SetDisabledSelectedImage( LPCTSTR pStrImage );

    bool IsGroup() const;
    void SetGroup( bool bGroup );
    bool IsChecked() const;
    void SetChecked( bool bSelected );

    SIZE EstimateSize( SIZE szAvailable );
    void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );

    void PaintStatusImage( GRAPHorHDC& gorh );
    void PaintDefault( GRAPHorHDC& gorh );

protected:
    bool m_bChecked;
    //这个为假则是checkbox
    bool m_bGroup;

    CStdString m_sSelectedImage;
    CStdString m_sHotSelectedImage;
    CStdString m_sPushedSelectedImage;
    CStdString m_sFocusedSelectedImage;
    CStdString m_sDisabledSelectedImage;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CProgressUI : public CContentControlUI
{
    DECLARE_DYNCREATE( CProgressUI )
public:
    CProgressUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface( LPCTSTR pstrName );

    bool IsHorizontal();
    void SetHorizontal( bool bHorizontal = true );
    int GetMinValue() const;
    void SetMinValue( int nMin );
    int GetMaxValue() const;
    void SetMaxValue( int nMax );
    int GetValue() const;
    void SetValue( int nValue );
    LPCTSTR GetFgImage() const;
    void SetFgImage( LPCTSTR pStrImage );

    void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );
    void PaintStatusImage( GRAPHorHDC& gorh );

protected:
    bool m_bHorizontal;
    int m_nMax;
    int m_nMin;
    int m_nValue;

    CStdString m_sFgImage;
    CStdString m_sFgImageModify;
};

/////////////////////////////////////////////////////////////////////////////////////
//

class CEditWnd;

class UILIB_API CEditUI : public CControlUI
{
    DECLARE_DYNCREATE( CEditUI )
    friend CEditWnd;
public:
    CEditUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface( LPCTSTR pstrName );
    UINT GetControlFlags() const;

    void Event( TEventUI& event );

    void ResetState();
    LPCTSTR GetText() const;
    void SetText( LPCTSTR pstrText );
    UINT GetMaxChar();
    void SetMaxChar( UINT uMax );
    bool IsReadOnly() const;
    void SetReadOnly( bool bReadOnly );
    bool IsPasswordMode() const;
    void SetPasswordMode( bool bPasswordMode );
    TCHAR GetPasswordChar() const;
    void SetPasswordChar( TCHAR cPasswordChar );

    void SetTextColor( DWORD color );
    DWORD GetTextColor() const;
    void SetDisabledTextColor( DWORD color );
    DWORD GetDisabledTextColor() const;
    void SetFont( int font );
    int GetFont() const;

    LPCTSTR GetNormalImage();
    void SetNormalImage( LPCTSTR pStrImage );
    LPCTSTR GetHotImage();
    void SetHotImage( LPCTSTR pStrImage );
    LPCTSTR GetFocusedImage();
    void SetFocusedImage( LPCTSTR pStrImage );
    LPCTSTR GetDisabledImage();
    void SetDisabledImage( LPCTSTR pStrImage );

    SIZE EstimateSizeOver( const SIZE& szAvailable );
    RECT SetPosOver( const RECT& rc );

    void SetVisible( bool bVisible = true );
    void SetInternVisible( bool bVisible = true );
    void SetEnabled( bool bEnabled = true );
    void SetInternEnabled( bool bEnabled = true );

    void SetManager( CPaintManagerUI* pManager, CElementUI* pParent, bool bInit = true );
    void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );

    void DoPaintOver( GRAPHorHDC& gorh );
    void PaintStatusImage( GRAPHorHDC& gorh );
    void PaintText( GRAPHorHDC& gorh );

protected:
    CEditWnd* m_pWindow;
    CTextBlockUI m_cTextBlock;

    CStdString m_szText;
    UINT m_uMaxChar;
    bool m_bReadOnly;
    bool m_bPasswordMode;
    TCHAR m_cPasswordChar;

    UINT m_uButtonState;

    CStdString m_sNormalImage;
    CStdString m_sHotImage;
    CStdString m_sFocusedImage;
    CStdString m_sDisabledImage;
};

/////////////////////////////////////////////////////////////////////////////////////
//
class CScrollViewerUI;

class UILIB_API CScrollbarUI : public CControlUI
{
    DECLARE_DYNCREATE( CScrollbarUI )
public:
    CScrollbarUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface( LPCTSTR pstrName );

    CScrollViewerUI* GetOwner() const;
    void SetOwner( CScrollViewerUI* pOwner );

    void ResetState();

    bool IsHorizontal() const;
    void SetHorizontal( bool bHorizontal = true );
    int GetScrollRange() const;
    void SetScrollRange( int nRange );
    int GetScrollPos() const;
    void SetScrollPos( int nPos );
    int GetLineSize() const;
    void SetLineSize( int nSize );

    LPCTSTR GetButton1NormalImage() const;
    void SetButton1NormalImage( LPCTSTR pStrImage );
    LPCTSTR GetButton1HotImage() const;
    void SetButton1HotImage( LPCTSTR pStrImage );
    LPCTSTR GetButton1PushedImage() const;
    void SetButton1PushedImage( LPCTSTR pStrImage );
    LPCTSTR GetButton1DisabledImage() const;
    void SetButton1DisabledImage( LPCTSTR pStrImage );

    LPCTSTR GetButton2NormalImage() const;
    void SetButton2NormalImage( LPCTSTR pStrImage );
    LPCTSTR GetButton2HotImage() const;
    void SetButton2HotImage( LPCTSTR pStrImage );
    LPCTSTR GetButton2PushedImage() const;
    void SetButton2PushedImage( LPCTSTR pStrImage );
    LPCTSTR GetButton2DisabledImage() const;
    void SetButton2DisabledImage( LPCTSTR pStrImage );

    LPCTSTR GetThumbNormalImage() const;
    void SetThumbNormalImage( LPCTSTR pStrImage );
    LPCTSTR GetThumbHotImage() const;
    void SetThumbHotImage( LPCTSTR pStrImage );
    LPCTSTR GetThumbPushedImage() const;
    void SetThumbPushedImage( LPCTSTR pStrImage );
    LPCTSTR GetThumbDisabledImage() const;
    void SetThumbDisabledImage( LPCTSTR pStrImage );

    LPCTSTR GetRailNormalImage() const;
    void SetRailNormalImage( LPCTSTR pStrImage );
    LPCTSTR GetRailHotImage() const;
    void SetRailHotImage( LPCTSTR pStrImage );
    LPCTSTR GetRailPushedImage() const;
    void SetRailPushedImage( LPCTSTR pStrImage );
    LPCTSTR GetRailDisabledImage() const;
    void SetRailDisabledImage( LPCTSTR pStrImage );

    LPCTSTR GetBkNormalImage() const;
    void SetBkNormalImage( LPCTSTR pStrImage );
    LPCTSTR GetBkHotImage() const;
    void SetBkHotImage( LPCTSTR pStrImage );
    LPCTSTR GetBkPushedImage() const;
    void SetBkPushedImage( LPCTSTR pStrImage );
    LPCTSTR GetBkDisabledImage() const;
    void SetBkDisabledImage( LPCTSTR pStrImage );
    //
    //     void SetBkMask( DWORD color );
    //     DWORD GetBkMask() const;

    RECT SetPosOver ( const RECT& rc );
    void Event( TEventUI& event );
    void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );

    void DoPaintOver( GRAPHorHDC& gorh );

    void PaintBk( GRAPHorHDC& gorh );
    void PaintButton1( GRAPHorHDC& gorh );
    void PaintButton2( GRAPHorHDC& gorh );
    void PaintThumb( GRAPHorHDC& gorh );
    void PaintRail( GRAPHorHDC& gorh );

protected:

    enum {
        DEFAULT_SCROLLBAR_SIZE = 16,
        DEFAULT_TIMERID = 10,
    };

    bool m_bHorizontal;
    int m_nRange;
    int m_nScrollPos;
    int m_nLineSize;
    CScrollViewerUI* m_pOwner;
    POINT ptLastMouse;
    int m_nLastScrollPos;
    int m_nLastScrollOffset;
    int m_nScrollRepeatDelay;

    UINT m_ubk1State;
    UINT m_ubk2State;
    RECT m_rcbk1;
    RECT m_rcbk2;
    CStdString m_sBkNormalImage;
    CStdString m_sBkHotImage;
    CStdString m_sBkPushedImage;
    CStdString m_sBkDisabledImage;

    RECT m_rcButton1;
    UINT m_uButton1State;
    CStdString m_sButton1NormalImage;
    CStdString m_sButton1HotImage;
    CStdString m_sButton1PushedImage;
    CStdString m_sButton1DisabledImage;

    RECT m_rcButton2;
    UINT m_uButton2State;
    CStdString m_sButton2NormalImage;
    CStdString m_sButton2HotImage;
    CStdString m_sButton2PushedImage;
    CStdString m_sButton2DisabledImage;

    RECT m_rcThumb;
    UINT m_uThumbState;
    CStdString m_sThumbNormalImage;
    CStdString m_sThumbHotImage;
    CStdString m_sThumbPushedImage;
    CStdString m_sThumbDisabledImage;

    CStdString m_sRailNormalImage;
    CStdString m_sRailHotImage;
    CStdString m_sRailPushedImage;
    CStdString m_sRailDisabledImage;

    CStdString m_sImageModify;
};

#endif // __UICOMMONCONTROLS_H__

