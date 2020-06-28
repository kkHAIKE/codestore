#ifndef __UICONTAINER_H__
#define __UICONTAINER_H__

#pragma once

// todo：布局应该有Dialog,Vertical,Horizontal,Stream,Tile,Grid,Tab,Proxy
// Grid布局要先完成，把垂直布局的分栏去掉，移植到Grid里
// 加上隐藏型滚动条
class CScrollbarUI;

enum {
    UISCROLL_NONE = 0,
    UISCROLL_AUTO,
    UISCROLL_SHOW,
    UISCROLL_HIDE
};

class UILIB_API CScrollViewerUI: public CContentControlUI
{
    DECLARE_DYNCREATE( CScrollViewerUI )
public:
    CScrollViewerUI();
    ~CScrollViewerUI();

    LPCTSTR GetClass() const;
    LPVOID GetInterface( LPCTSTR pstrName );

    void Event( TEventUI& event );
    void SetVisible( bool bVisible = true );
    void SetInternVisible( bool bVisible = true );
    void SetEnabled( bool bEnabled = true );
    void SetInternEnabled( bool bEnabled = true );
    void SetMouseEnabled( bool bEnabled = true );
    void SetInternMouseEnabled( bool bEnabled = true );

    SIZE EstimateSizeOver( const SIZE& szAvailable );
    void SetPosMain( const RECT& rc );
    RECT SetPosOver( const RECT& rc );
    void PaintContent( GRAPHorHDC& gorh );

    void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );

    void SetManager( CPaintManagerUI* pManager, CElementUI* pParent, bool bInit = true );
    CElementUI* FindControl( FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags );

    virtual SIZE GetScrollPos() const;
    virtual SIZE GetScrollRange() const;

    virtual void SetScrollPos( const SIZE& szPos );
    virtual void LineUp();
    virtual void LineDown();
    virtual void PageUp();
    virtual void PageDown();
    virtual void HomeUp();
    virtual void EndDown();
    virtual void LineLeft();
    virtual void LineRight();
    virtual void PageLeft();
    virtual void PageRight();
    virtual void HomeLeft();
    virtual void EndRight();

    virtual void EnableScrollBar( int iStyleVertical = UISCROLL_AUTO, int iStyleHorizontal = UISCROLL_NONE );
    virtual CScrollbarUI* GetVerticalScrollbar() const;
    virtual CScrollbarUI* GetHorizontalScrollbar() const;

protected:
    virtual void ProcessScrollbar( const SIZE& sz, const SIZE& szNeed );

protected:
    CScrollbarUI* m_pVerticalScrollbar;
    int m_iVerticalScrollbarStyle;
    CScrollbarUI* m_pHorizontalScrollbar;
    int m_iHorizontalScrollbarStyle;
};


/////////////////////////////////////////////////////////////////////////////////////
//

class IContainerUI
{
public:
    virtual CElementUI* GetItemAt( int iIndex ) const = 0;
    virtual int GetItemIndex( CElementUI* pControl ) const  = 0;
    virtual bool SetItemIndex( CElementUI* pControl, int iIndex )  = 0;
    virtual int GetCount() const = 0;
    virtual bool Add( CElementUI* pControl ) = 0;
    virtual bool AddAt( CElementUI* pControl, int iIndex )  = 0;
    virtual bool Remove( CElementUI* pControl ) = 0;
    virtual bool RemoveAt( int iIndex )  = 0;
    virtual void RemoveAll() = 0;
};

/////////////////////////////////////////////////////////////////////////////////////
//


class UILIB_API CContainerUI : public CElementUI, public IContainerUI
{
    DECLARE_DYNCREATE( CContainerUI )

public:
    CContainerUI();
    ~CContainerUI();

public:
    LPCTSTR GetClass() const;
    LPVOID GetInterface( LPCTSTR pstrName );

    CElementUI* GetItemAt( int iIndex ) const;
    int GetItemIndex( CElementUI* pControl ) const;
    bool SetItemIndex( CElementUI* pControl, int iIndex );
    int GetCount() const;
    bool Add( CElementUI* pControl );
    bool AddAt( CElementUI* pControl, int iIndex );
    bool Remove( CElementUI* pControl );
    bool RemoveAt( int iIndex );
    void RemoveAll();

    void SetVisible( bool bVisible = true );
    void SetInternVisible( bool bVisible = true );
    void SetEnabled( bool bEnabled = true );
    void SetInternEnabled( bool bEnabled = true );
    void SetMouseEnabled( bool bEnabled = true );
    void SetInternMouseEnabled( bool bEnabled = true );

    virtual int GetChildPadding() const;
    virtual void SetChildPadding( int iPadding );
    virtual bool IsAutoDestroy() const;
    virtual void SetAutoDestroy( bool bAuto = true );

    //virtual int FindSelectable( int iIndex, bool bForward = true ) const;
    SIZE EstimateSizeOver( const SIZE& szAvailable );
    RECT SetPosOver( const RECT& rc );
    void DoPaintOver( GRAPHorHDC& gorh );

    void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );

    void SetManager( CPaintManagerUI* pManager, CElementUI* pParent, bool bInit = true );
    CElementUI* FindControl( FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags );

protected:
    CStdPtrArray<CElementUI> m_items;
    //子控件的间隔
    int m_iChildPadding;
    bool m_bAutoDestroy;
};

/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CVerticalLayoutUI : public CContainerUI
{
    DECLARE_DYNCREATE( CVerticalLayoutUI )
public:

    LPCTSTR GetClass() const;
    LPVOID GetInterface( LPCTSTR pstrName );

    SIZE EstimateSizeOver( const SIZE& szAvailable );
    RECT SetPosOver( const RECT& rc );
	
	void DoPaintOver( GRAPHorHDC& gorh );

protected:
    int m_nAdjustables;
};

/////////////////////////////////////////////////////////////////////////////////////
//
class UILIB_API CHorizontalLayoutUI : public CContainerUI
{
    DECLARE_DYNCREATE( CHorizontalLayoutUI )
public:

    LPCTSTR GetClass() const;
    LPVOID GetInterface( LPCTSTR pstrName );

    SIZE EstimateSizeOver( const SIZE& szAvailable );
    RECT SetPosOver( const RECT& rc );

	void DoPaintOver( GRAPHorHDC& gorh );
protected:
    int m_nAdjustables;
};

class UILIB_API CDockLayoutUI:public CContainerUI
{
	DECLARE_DYNCREATE( CDockLayoutUI )
public:
	CDockLayoutUI();

	LPCTSTR GetClass() const;
	LPVOID GetInterface( LPCTSTR pstrName );

	bool IsLastFill() const;
	void SetLastFill(bool lastFill);

	SIZE EstimateSizeOver( const SIZE& szAvailable );
	RECT SetPosOver( const RECT& rc );

	void SetAttribute( LPCTSTR pstrName, LPCTSTR pstrValue );

protected:
	bool m_bLastFill;
};

#endif // __UICONTAINER_H__