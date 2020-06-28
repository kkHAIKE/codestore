#ifndef __UIRENDER_H__
#define __UIRENDER_H__
#pragma once

/////////////////////////////////////////////////////////////////////////////////////
//
#define UIDRAW_DEAFULT	0x00000000
#define UIDRAW_USEMASK	0x00000001
#define UIDRAW_HOLE		0x00000002
#define UIDRAW_TILE		0x00000004
#define UIDRAW_HIGHLIGHT 0x00000008
#define UIDRAW_GRAY 0x00000010
/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API GRAPHorHDC
{
public:
    GRAPHorHDC( HDC hdc );
    ~GRAPHorHDC();
    CRgn IntersectClip( const RECT& rc );
    CRgn SetClip( const CRgn& rgn );
    bool SetGRAPHmode();
    bool SetHDCmode();
    bool Setmode( bool mode );
    operator HDC() const;
    operator Graphics& ();

protected:
    HDC m_hdc;
    CRgn m_rgn;
    Graphics g;
    bool is_graph;
    bool bGraphSet;
    bool bHDCSet;

private:
    //GRAPHorHDC(const GRAPHorHDC& o){};
    GRAPHorHDC& operator=( const GRAPHorHDC& o ) {return *this;}
};
/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CRenderEngine
{
public:
    static Bitmap* LoadImage( STRINGorID bitmap, STRINGorID type = ( UINT ) 0 );
    static void DrawImage( GRAPHorHDC& gorh, Bitmap* hBitmap, const RECT& rc, const RECT& rcPaint, \
                           const RECT& rcBmpPart, const RECT& rcCorners, BYTE uFade = 255, DWORD mask = Color::Fuchsia, DWORD style = UIDRAW_DEAFULT );
    static bool DrawImageString( GRAPHorHDC& gorh, CPaintManagerUI* pManager, RECT& rcItem, const RECT& rcPaint,
                                 LPCTSTR pStrImage, LPCTSTR pStrModify = NULL, bool bMeasure = false );
    static void DrawColor( GRAPHorHDC& gorh, const RECT& rc, DWORD color );

    // 以下函数中的颜色参数alpha值无效
    static void DrawGradient( GRAPHorHDC& gorh, const RECT& rc, DWORD dwFirst, DWORD dwSecond, bool bVertical );
    static void DrawLine( GRAPHorHDC& gorh, const RECT& rc, int nSize, DWORD dwPenColor );
    static void DrawRect( GRAPHorHDC& gorh, const RECT& rc, int nSize, DWORD dwPenColor );
    static void DrawText( GRAPHorHDC& gorh, CPaintManagerUI* pManager, RECT& rc, LPCTSTR pstrText, \
                          DWORD dwTextColor, int iFont, UINT uStyle );
    static void DrawHtmlText( GRAPHorHDC& gorh, CPaintManagerUI* pManager, RECT& rc, LPCTSTR strText,
                              DWORD dwTextColor, int iFont, UINT uStyle, CRgn** pLinks = NULL, CStdString** sLinks = NULL, int* pnLinkRects = NULL );
};

#endif // __UIRENDER_H__