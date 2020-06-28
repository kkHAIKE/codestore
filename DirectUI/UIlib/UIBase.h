#ifndef __UIBASE_H__
#define __UIBASE_H__
#pragma once

#include <Debug.h>
#include <StdString.h>
#include <StdStringPtrMap.h>
#include <StdArray.h>
#include <RuntimeClass.h>

/////////////////////////////////////////////////////////////////////////////////////
//

#define UI_WNDSTYLE_CONTAINER  (0)
#define UI_WNDSTYLE_FRAME      (WS_VISIBLE | WS_OVERLAPPEDWINDOW)
#define UI_WNDSTYLE_CHILD      (WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN)
#define UI_WNDSTYLE_DIALOG     (WS_VISIBLE | WS_POPUPWINDOW | WS_CAPTION | WS_DLGFRAME | WS_CLIPSIBLINGS | WS_CLIPCHILDREN)

#define UI_WNDSTYLE_EX_FRAME   (WS_EX_WINDOWEDGE)
#define UI_WNDSTYLE_EX_DIALOG  (WS_EX_TOOLWINDOW | WS_EX_DLGMODALFRAME)

#define UI_CLASSSTYLE_CONTAINER  (0)
#define UI_CLASSSTYLE_FRAME      (CS_VREDRAW | CS_HREDRAW)
#define UI_CLASSSTYLE_CHILD      (CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_SAVEBITS)
#define UI_CLASSSTYLE_DIALOG     (CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_SAVEBITS)


/////////////////////////////////////////////////////////////////////////////////////
//

inline RECT RectFromString( LPCTSTR pstrValue )
{
    RECT rc = { 0 };

    LPTSTR pstr = NULL;
    rc.left = _tcstol( pstrValue, &pstr, 10 );  ASSERT( pstr );
    rc.top = _tcstol( pstr + 1, &pstr, 10 );    ASSERT( pstr );
    rc.right = _tcstol( pstr + 1, &pstr, 10 );  ASSERT( pstr );
    rc.bottom = _tcstol( pstr + 1, &pstr, 10 );
    return rc;
}

inline SIZE SizeFromString( LPCTSTR pstrValue )
{
    SIZE sz = { 0 };

    LPTSTR pstr = NULL;
    sz.cx = _tcstol( pstrValue, &pstr, 10 );  ASSERT( pstr );
    sz.cy = _tcstol( pstr + 1, &pstr, 10 );
    return sz;
}

/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CRgn
{
public:
    CRgn();
    CRgn( HRGN hrgn );
    CRgn( const CRgn& rgn );
    CRgn( int nLeftRect, int nTopRect, int nRightRect, int nBottomRect );
    CRgn( const RECT* lprc );
    //  CRgn( LPRGNDATA lpRgnData, DWORD size );
    ~CRgn();

    //  DWORD GetData( LPRGNDATA& lpRgnData );
    bool IsEmpty() const;
    void Join( const CRgn& rgn );
    void Intersect( const CRgn& rgn );
    bool PtInRegion( POINT* p );
    operator Region() const;
    operator HRGN() const;
    CRgn& operator=( HRGN hrgn );
    CRgn& operator=( const RECT& hrgn );
    CRgn& operator=( const CRgn& rect );
protected:
    HRGN m_hrgn;
    bool m_bIsEmpty;
};


/////////////////////////////////////////////////////////////////////////////////////
//
/*存资源名称或ID*/
class UILIB_API STRINGorID
{
public:
    STRINGorID( LPCTSTR lpString ) {
        if ( lpString == NULL || *lpString == 0 )
            m_lpstr = NULL;
        m_lpstr = lpString;
    }
    STRINGorID( UINT nID ) : m_lpstr( MAKEINTRESOURCE( nID ) )
    { }
    operator LPCTSTR() const {
        return m_lpstr;
    }
protected:
    LPCTSTR m_lpstr;
};

/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CPoint : public tagPOINT
{
public:
    CPoint();
    CPoint( const POINT& src );
    CPoint( int x, int y );
    CPoint( LPARAM lParam );
};
/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CSize : public tagSIZE
{
public:
    CSize();
    CSize( const SIZE& src );
    CSize( const RECT& rc );
    CSize( int cx, int cy );

    operator Size() const;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CRect : public tagRECT
{
public:
    CRect();
    CRect( const RECT& src );
    CRect( int iLeft, int iTop, int iRight, int iBottom );

    int GetWidth() const;
    int GetHeight() const;
    void Empty();
    bool IsNull() const;
    bool IsEmpty() const;
    /*    void Join( const RECT& rc );*/
    //移动到0坐标
    void ResetOffset();
    //正常化
    void Normalize();
    void Offset( int cx, int cy );
    void Inflate( int cx, int cy );
    void Deflate( int cx, int cy );
    void Union( const RECT& rc );
    void Intersect( const RECT& rc );

    operator Rect() const;
};

/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CWindowWnd
{
public:
    CWindowWnd();

    HWND GetHWND() const;
    operator HWND() const;

    bool RegisterWindowClass();
    bool RegisterSuperclass();

    HWND Create( HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, const RECT rc, HMENU hMenu = NULL );
    HWND Create( HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT, HMENU hMenu = NULL );
    //窗口的子类化，即重设窗口函数
    HWND Subclass( HWND hWnd );
    void Unsubclass();

    void ShowWindow( bool bShow = true, bool bTakeFocus = true );
    bool ShowModal();
    void Close();
    void CenterWindow();
    void SetIcon( UINT nRes );

    LRESULT SendMessage( UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L );
    LRESULT PostMessage( UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L );
    void ResizeClient( int cx = -1, int cy = -1 );

protected:
    virtual LPCTSTR GetWindowClassName() const = 0;
    virtual LPCTSTR GetSuperClassName() const;
    virtual UINT GetClassStyle() const;

    virtual LRESULT HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam );
    virtual void OnFinalMessage( HWND hWnd );

    static LRESULT CALLBACK __WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
    static LRESULT CALLBACK __ControlProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

protected:
    HWND m_hWnd;
    WNDPROC m_OldWndProc;
    bool m_bSubclassed;

};

#endif // __UIBASE_H__