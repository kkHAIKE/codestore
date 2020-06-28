#include "StdAfx.h"
#include "UIDefaultSkin.h"

#include <Uxtheme.h>
#include <vsstyle.h>
#pragma comment(lib,"uxtheme.lib")
void CDefaultSkinUI::DrawButton( GRAPHorHDC& gorh, HWND hWnd, const RECT& rcPaint, UINT btstate )
{
    int istateid = PBS_NORMAL;
    if ( ( btstate & UISTATE_PUSHED ) != 0 )
        istateid = PBS_PRESSED;
    else if ( ( btstate & UISTATE_HOT ) != 0 )
        istateid = PBS_HOT;
    else if ( ( btstate & UISTATE_DISABLED ) != 0 )
        istateid = PBS_DISABLED;

    bool bModesave = gorh.SetHDCmode();
    HTHEME hTheme =::OpenThemeData( hWnd, WC_BUTTON );
    ::DrawThemeBackground( hTheme, gorh, BP_PUSHBUTTON, istateid, &rcPaint, NULL );
    ::CloseThemeData( hTheme );

    gorh.SetGRAPHmode();
    Graphics& g = gorh;

    //     if ( ( btstate & UISTATE_PUSHED ) != 0 ) {
    //         g.DrawRectangle( &Pen( Color::Black ), rcPaint.left, rcPaint.top, rcPaint.right - rcPaint.left - 1, rcPaint.bottom - rcPaint.top - 1 );
    //         g.DrawRectangle( &Pen( COLOR_3D_SHADOW1 ), rcPaint.left + 1, rcPaint.top + 1, rcPaint.right - rcPaint.left - 3, rcPaint.bottom - rcPaint.top - 3 );
    //         g.FillRectangle( &SolidBrush( COLOR_3D_FOREGROUND ), rcPaint.left + 2, rcPaint.top + 2, rcPaint.right - rcPaint.left - 4, rcPaint.bottom - rcPaint.top - 4 );
    //     }
    //     else {
    //         Point p[3];
    //         p[0].X = rcPaint.left; p[0].Y = rcPaint.bottom - 2;
    //         p[1].X = rcPaint.left; p[1].Y = rcPaint.top;
    //         p[2].X = rcPaint.right - 2; p[2].Y = rcPaint.top;
    //         g.DrawLines( &Pen( Color::White ), p, 3 );
    //
    //         p[0].X = rcPaint.left; p[0].Y = rcPaint.bottom - 1;
    //         p[1].X = rcPaint.right - 1; p[1].Y = rcPaint.bottom - 1;
    //         p[2].X = rcPaint.right - 1; p[2].Y = rcPaint.top;
    //         g.DrawLines( &Pen( COLOR_3D_SHADOW2 ), p, 3 );
    //
    //         p[0].X = rcPaint.left + 1; p[0].Y = rcPaint.bottom - 2;
    //         p[1].X = rcPaint.right - 2; p[1].Y = rcPaint.bottom - 2;
    //         p[2].X = rcPaint.right - 2; p[2].Y = rcPaint.top + 1;
    //         g.DrawLines( &Pen( COLOR_3D_SHADOW1 ), p, 3 );
    //
    //         g.FillRectangle( &SolidBrush( COLOR_3D_FOREGROUND ), rcPaint.left + 1, rcPaint.top + 1, rcPaint.right - rcPaint.left - 3, rcPaint.bottom - rcPaint.top - 3 );
    //     }

    if ( ( btstate & UISTATE_FOCUSED ) != 0 ) {
        Pen p( Color::Black );
        p.SetDashStyle( DashStyleDot );
        g.DrawRectangle( &p, rcPaint.left + 4, rcPaint.top + 4, rcPaint.right - rcPaint.left - 9, rcPaint.bottom - rcPaint.top - 9 );
    }

    gorh.Setmode( bModesave );
}
void CDefaultSkinUI::DrawScrollbar( GRAPHorHDC& gorh, HWND hWnd, const RECT& rcPaint, UINT sbstate, UINT sbpart )
{
    int ipartid = 0;
    int istateid = SCRBS_NORMAL;

    if ( ( sbstate & UISTATE_PUSHED ) != 0 )
        istateid = SCRBS_PRESSED;
    else if ( ( sbstate & UISTATE_HOT ) != 0 )
        istateid = SCRBS_HOT;
    else if ( ( sbstate & UISTATE_DISABLED ) != 0 )
        istateid = SCRBS_DISABLED;

    switch ( sbpart ) {
    case PART_SCROLLBAR_BUTTON_UP:
    case PART_SCROLLBAR_BUTTON_DOWN:
    case PART_SCROLLBAR_BUTTON_LEFT:
    case PART_SCROLLBAR_BUTTON_RIGHT:
        ipartid = SBP_ARROWBTN;
        istateid += sbpart * 4;
        break;
    case PART_SCROLLBAR_LOWVERT:
        ipartid = SBP_LOWERTRACKVERT;
        break;
    case PART_SCROLLBAR_LOWHORZ:
        ipartid = SBP_LOWERTRACKHORZ;
        break;
    case PART_SCROLLBAR_UPVERT:
        ipartid = SBP_UPPERTRACKVERT;
        break;
    case PART_SCROLLBAR_UPHORZ:
        ipartid = SBP_UPPERTRACKHORZ;
        break;
    case PART_SCROLLBAR_THUMBVERT:
        ipartid = SBP_THUMBBTNVERT;
        break;
    case PART_SCROLLBAR_THUMBHORZ:
        ipartid = SBP_THUMBBTNHORZ;
        break;
    case PART_SCROLLBAR_RAILVERT:
        ipartid = SBP_GRIPPERVERT;
        break;
    case PART_SCROLLBAR_RAILHORZ:
        ipartid = SBP_GRIPPERHORZ;
    }

    bool bModesave = gorh.SetHDCmode();
    HTHEME hTheme =::OpenThemeData( hWnd, WC_SCROLLBAR );
    ::DrawThemeBackground( hTheme, gorh, ipartid, istateid, &rcPaint, NULL );
    ::CloseThemeData( hTheme );
    //     bool bModesave = gorh.SetGRAPHmode();
    //     Graphics& g = gorh;
    //
    //     switch ( sbpart ) {
    //     case PART_SCROLLBAR_BACKGROUND:
    //         g.FillRectangle( &HatchBrush( HatchStyle50Percent, COLOR_3D_FOREGROUND, Color::White ), rcPaint.left, rcPaint.top, rcPaint.right - rcPaint.left, rcPaint.bottom - rcPaint.top );
    //         break;
    //     case PART_SCROLLBAR_BUTTON_LEFT:
    //     case PART_SCROLLBAR_BUTTON_UP:
    //     case PART_SCROLLBAR_BUTTON_RIGHT:
    //     case PART_SCROLLBAR_BUTTON_DOWN:
    //     case PART_SCROLLBAR_THUMB:
    //         if ( sbpart != PART_SCROLLBAR_THUMB && ( sbstate & UISTATE_PUSHED ) != 0 ) {
    //             g.DrawRectangle( &Pen( COLOR_3D_SHADOW1 ), rcPaint.left, rcPaint.top, rcPaint.right - rcPaint.left - 1, rcPaint.bottom - rcPaint.top - 1 );
    //             g.FillRectangle( &SolidBrush( COLOR_3D_FOREGROUND ), rcPaint.left + 1, rcPaint.top + 1, rcPaint.right - rcPaint.left - 2, rcPaint.bottom - rcPaint.top - 2 );
    //         }
    //         else if ( sbpart != PART_SCROLLBAR_THUMB || ( sbstate & UISTATE_DISABLED ) == 0 ) {
    //             Point p[3];
    //             p[0].X = rcPaint.left; p[0].Y = rcPaint.bottom - 2;
    //             p[1].X = rcPaint.left; p[1].Y = rcPaint.top;
    //             p[2].X = rcPaint.right - 2; p[2].Y = rcPaint.top;
    //             g.DrawLines( &Pen( COLOR_3D_FOREGROUND ), p, 3 );
    //
    //             p[0].X = rcPaint.left; p[0].Y = rcPaint.bottom - 1;
    //             p[1].X = rcPaint.right - 1; p[1].Y = rcPaint.bottom - 1;
    //             p[2].X = rcPaint.right - 1; p[2].Y = rcPaint.top;
    //             g.DrawLines( &Pen( COLOR_3D_SHADOW2 ), p, 3 );
    //
    //             p[0].X = rcPaint.left + 1; p[0].Y = rcPaint.bottom - 2;
    //             p[1].X = rcPaint.right - 2; p[1].Y = rcPaint.bottom - 2;
    //             p[2].X = rcPaint.right - 2; p[2].Y = rcPaint.top + 1;
    //             g.DrawLines( &Pen( COLOR_3D_SHADOW1 ), p, 3 );
    //
    //             p[0].X = rcPaint.left + 1; p[0].Y = rcPaint.bottom - 3;
    //             p[1].X = rcPaint.left + 1; p[1].Y = rcPaint.top + 1;
    //             p[2].X = rcPaint.right - 3; p[2].Y = rcPaint.top + 1;
    //             g.DrawLines( &Pen( Color::White ), p, 3 );
    //
    //             g.FillRectangle( &SolidBrush( COLOR_3D_FOREGROUND ), rcPaint.left + 2, rcPaint.top + 2, rcPaint.right - rcPaint.left - 4, rcPaint.bottom - rcPaint.top - 4 );
    //         }
    //
    //         Point rcCenter( ( rcPaint.left +  rcPaint.right ) / 2, ( rcPaint.top +  rcPaint.bottom ) / 2 );
    //         if ( sbpart == PART_SCROLLBAR_BUTTON_LEFT ) {
    //             Point p[3];
    //             p[0].X = rcCenter.X - 3; p[0].Y = rcCenter.Y;
    //             p[1].X = rcCenter.X + 2; p[1].Y = rcCenter.Y - 4;
    //             p[2].X = rcCenter.X + 2; p[2].Y = rcCenter.Y + 4;
    //
    //             g.FillPolygon( &SolidBrush( ( ( sbstate & UISTATE_DISABLED ) != 0 ) ? pManager->GetDefaultDisabledColor() : Color::Black ), p, 3 );
    //         }
    //         else if ( sbpart == PART_SCROLLBAR_BUTTON_UP ) {
    //             Point p[3];
    //             p[0].X = rcCenter.X; p[0].Y = rcCenter.Y - 3;
    //             p[1].X = rcCenter.X - 4; p[1].Y = rcCenter.Y + 2;
    //             p[2].X = rcCenter.X + 4; p[2].Y = rcCenter.Y + 2;
    //
    //             g.FillPolygon( &SolidBrush( ( ( sbstate & UISTATE_DISABLED ) != 0 ) ? pManager->GetDefaultDisabledColor() : Color::Black ), p, 3 );
    //         }
    //         else if ( sbpart == PART_SCROLLBAR_BUTTON_RIGHT ) {
    //             Point p[3];
    //             p[0].X = rcCenter.X + 3; p[0].Y = rcCenter.Y;
    //             p[1].X = rcCenter.X - 2; p[1].Y = rcCenter.Y - 4;
    //             p[2].X = rcCenter.X - 2; p[2].Y = rcCenter.Y + 4;
    //
    //             g.FillPolygon( &SolidBrush( ( ( sbstate & UISTATE_DISABLED ) != 0 ) ? pManager->GetDefaultDisabledColor() : Color::Black ), p, 3 );
    //         }
    //         else if ( sbpart == PART_SCROLLBAR_BUTTON_DOWN ) {
    //             Point p[3];
    //             p[0].X = rcCenter.X; p[0].Y = rcCenter.Y + 3;
    //             p[1].X = rcCenter.X - 4; p[1].Y = rcCenter.Y - 2;
    //             p[2].X = rcCenter.X + 4; p[2].Y = rcCenter.Y - 2;
    //
    //             g.FillPolygon( &SolidBrush( ( ( sbstate & UISTATE_DISABLED ) != 0 ) ? pManager->GetDefaultDisabledColor() : Color::Black ), p, 3 );
    //         }
    //         break;
    //     }
    //
    gorh.Setmode( bModesave );
}
void CDefaultSkinUI::DrawOption( GRAPHorHDC& gorh, HWND hWnd, const RECT& rcPaint, UINT btstate, bool bGroup )
{
    int ipartid = 0;
    int istateid = CBS_UNCHECKEDNORMAL;
    if ( ( btstate & UISTATE_PUSHED ) != 0 )
        istateid = CBS_UNCHECKEDPRESSED;
    else if ( ( btstate & UISTATE_HOT ) != 0 )
        istateid = CBS_UNCHECKEDHOT;
    else if ( ( btstate & UISTATE_DISABLED ) != 0 )
        istateid = CBS_UNCHECKEDDISABLED;
    if ( ( btstate & UISTATE_CHECKED ) != 0 )
        istateid += 4;

    RECT rc = {rcPaint.left + 1, ( rcPaint.bottom + rcPaint.top ) / 2 - 6, 12, 12};
    rc.right += rc.left; rc.bottom += rc.top;

    bool bModesave = gorh.SetHDCmode();
    HTHEME hTheme =::OpenThemeData( hWnd, WC_BUTTON );
    ::DrawThemeBackground( hTheme, gorh, bGroup ? BP_RADIOBUTTON : BP_CHECKBOX, istateid, &rc, NULL );
    ::CloseThemeData( hTheme );

    gorh.SetGRAPHmode();
    Graphics& g = gorh;
    //
    //     //¹Ì¶¨12
    rc.right -= rc.left; rc.bottom -= rc.top;
    //
    //     if ( bGroup ) {
    //         //»­±³¾°ÏÈ
    //         g.FillEllipse( &SolidBrush( ( ( btstate & UISTATE_PUSHED ) != 0 || ( btstate & UISTATE_DISABLED ) != 0 ) ? \
    //                                     COLOR_3D_FOREGROUND : Color::White ), rc.left, rc.top, rc.right, rc.bottom );
    //
    //         //»­»·
    //         g.DrawArc( &Pen( COLOR_3D_SHADOW1 ), rc.left, rc.top, rc.right - 1, rc.bottom - 1, 135, 180 );
    //         g.DrawArc( &Pen( Color::White ), rc.left, rc.top, rc.right - 1, rc.bottom - 1, 315, 180 );
    //         g.DrawArc( &Pen( COLOR_3D_SHADOW2 ), rc.left + 1, rc.top + 1, rc.right - 3, rc.bottom - 3, 135, 180 );
    //         g.DrawArc( &Pen( COLOR_3D_FOREGROUND ), rc.left + 1, rc.top + 1, rc.right - 3, rc.bottom - 3, 315, 180 );
    //
    //         if ( ( btstate & UISTATE_SELECTED ) != 0 )
    //             g.FillEllipse( &SolidBrush( ( ( btstate & UISTATE_DISABLED ) != 0 ) ? pManager->GetDefaultDisabledColor() : Color::Black ),
    //                            rc.left + 4, rc.top + 4, 4, 4 );
    //     }
    //     else {
    //         g.FillRectangle( &SolidBrush( ( ( btstate & UISTATE_PUSHED ) != 0 || ( btstate & UISTATE_DISABLED ) != 0 ) ?  \
    //                                       COLOR_3D_FOREGROUND : Color::White ), rc.left, rc.top, rc.right, rc.bottom );
    //
    //         Point p[3];
    //         p[0].X = rc.left; p[0].Y = rc.top + rc.bottom - 2;
    //         p[1].X = rc.left; p[1].Y = rc.top;
    //         p[2].X = rc.left + rc.right - 2; p[2].Y = rc.top;
    //         g.DrawLines( &Pen( COLOR_3D_SHADOW2 ), p, 3 );
    //
    //         p[0].X = rc.left; p[0].Y = rc.top + rc.bottom - 1;
    //         p[1].X = rc.left + rc.right - 1; p[1].Y = rc.top + rc.bottom - 1;
    //         p[2].X = rc.left + rc.right - 1; p[2].Y = rc.top;
    //         g.DrawLines( &Pen( Color::White ), p, 3 );
    //
    //         p[0].X = rc.left + 1; p[0].Y = rc.top + rc.bottom - 2;
    //         p[1].X = rc.left + rc.right - 2; p[1].Y = rc.top + rc.bottom - 2;
    //         p[2].X = rc.left + rc.right - 2; p[2].Y = rc.top + 1;
    //         g.DrawLines( &Pen( COLOR_3D_FOREGROUND ), p, 3 );
    //
    //         p[0].X = rc.left + 1; p[0].Y = rc.top + rc.bottom - 3;
    //         p[1].X = rc.left + 1; p[1].Y = rc.top + 1;
    //         p[2].X = rc.left + rc.right - 3; p[2].Y = rc.top + 1;
    //         g.DrawLines( &Pen( Color::Black ), p, 3 );
    //
    //         if ( ( btstate & UISTATE_SELECTED ) != 0 ) {
    //             p[0].X = rc.left + 3; p[0].Y = rc.top + 6;
    //             p[1].X = rc.left + 5; p[1].Y = rc.top + rc.bottom - 4;
    //             p[2].X = rc.left + rc.right - 4; p[2].Y = rc.top + 3;
    //             g.DrawLines( &Pen( ( ( btstate & UISTATE_DISABLED ) != 0 ) ? pManager->GetDefaultDisabledColor() : Color::Black, 2 ), p, 3 );
    //         }
    //     }
    if ( ( btstate & UISTATE_FOCUSED ) != 0 ) {
        Pen p( Color::Black );
        p.SetDashStyle( DashStyleDot );
        g.DrawRectangle( &p, rc.left + rc.right + 4, rcPaint.top + 4, rcPaint.right - rcPaint.left - rc.right - 9, rcPaint.bottom - rcPaint.top - 9 );
    }
    gorh.Setmode( bModesave );
}
void CDefaultSkinUI::DrawProgress( GRAPHorHDC& gorh, HWND hWnd, const RECT& rcPaint, const RECT& rcFg, bool bVert )
{
    bool bModesave = gorh.SetHDCmode();
    HTHEME hTheme =::OpenThemeData( hWnd, _T( "Progress" ) );
    ::DrawThemeBackground( hTheme, gorh, bVert ? PP_BARVERT : PP_BAR, 0, &rcPaint, NULL );
    RECT rc = {rcFg.left + rcPaint.left, rcFg.top + rcPaint.top, rcFg.right + rcPaint.left, rcFg.bottom + rcPaint.top};
    ::DrawThemeBackground( hTheme, gorh, bVert ? PP_CHUNKVERT : PP_CHUNK, 0, &rc, NULL );
    ::CloseThemeData( hTheme );

    //»­³¬¼òµ¥µã
    //     bool bModesave = gorh.SetGRAPHmode();
    //     Graphics& g = gorh;
    //
    //     g.FillRectangle( &SolidBrush( COLOR_3D_FOREGROUND ), rcPaint.left, rcPaint.top, rcPaint.right - rcPaint.left, rcPaint.bottom - rcPaint.top );
    //     g.DrawRectangle( &Pen( COLOR_3D_SHADOW2 ), rcPaint.left, rcPaint.top, rcPaint.right - rcPaint.left - 1, rcPaint.bottom - rcPaint.top - 1 );
    //     g.FillRectangle( &SolidBrush( COLOR_FG_BLUE ), rcPaint.left + rcFg.left, rcPaint.top + rcFg.top, rcFg.right - rcFg.left, rcFg.bottom - rcFg.top );
    //
    gorh.Setmode( bModesave );
}
void CDefaultSkinUI::DrawEdit( GRAPHorHDC& gorh, HWND hWnd, const RECT& rcPaint, UINT btstate )
{
    int istateid = ETS_NORMAL;
    if ( ( btstate & UISTATE_FOCUSED ) != 0 )
        istateid = ETS_FOCUSED;
    else if ( ( btstate & UISTATE_HOT ) != 0 )
        istateid = ETS_HOT;
    else if ( ( btstate & UISTATE_DISABLED ) != 0 )
        istateid = ETS_DISABLED;
    else if ( ( btstate & UISTATE_READONLY ) != 0 )
        istateid = ETS_READONLY;

    bool bModesave = gorh.SetHDCmode();
    HTHEME hTheme =::OpenThemeData( hWnd, WC_EDIT );
    ::DrawThemeBackground( hTheme, gorh, EP_EDITTEXT, istateid, &rcPaint, NULL );
    ::CloseThemeData( hTheme );

    //     bool bModesave = gorh.SetGRAPHmode();
    //     Graphics& g = gorh;
    //
    //     g.FillRectangle( &SolidBrush( Color::White ), rcPaint.left, rcPaint.top, rcPaint.right - rcPaint.left, rcPaint.bottom - rcPaint.top );
    //
    //     Point p[3];
    //     p[0].X = rcPaint.left; p[0].Y = rcPaint.bottom - 2;
    //     p[1].X = rcPaint.left; p[1].Y = rcPaint.top;
    //     p[2].X = rcPaint.right - 2; p[2].Y = rcPaint.top;
    //     g.DrawLines( &Pen( COLOR_3D_SHADOW1 ), p, 3 );
    //
    //     p[0].X = rcPaint.left; p[0].Y = rcPaint.bottom - 1;
    //     p[1].X = rcPaint.right - 1; p[1].Y = rcPaint.bottom - 1;
    //     p[2].X = rcPaint.right - 1; p[2].Y = rcPaint.top;
    //     g.DrawLines( &Pen( Color::White ), p, 3 );
    //
    //     p[0].X = rcPaint.left + 1; p[0].Y = rcPaint.bottom - 2;
    //     p[1].X = rcPaint.right - 2; p[1].Y = rcPaint.bottom - 2;
    //     p[2].X = rcPaint.right - 2; p[2].Y = rcPaint.top + 1;
    //     g.DrawLines( &Pen( COLOR_3D_FOREGROUND ), p, 3 );
    //
    //     p[0].X = rcPaint.left + 1; p[0].Y = rcPaint.bottom - 3;
    //     p[1].X = rcPaint.left + 1; p[1].Y = rcPaint.top + 1;
    //     p[2].X = rcPaint.right - 3; p[2].Y = rcPaint.top + 1;
    //     g.DrawLines( &Pen( COLOR_3D_SHADOW2 ), p, 3 );

    gorh.Setmode( bModesave );
}
void CDefaultSkinUI::DrawWindow( GRAPHorHDC& gorh, HWND hWnd, const RECT& rcPaint, UINT sbstate, UINT sbpart )
{
    int ipartid = 0;
    int istateid = 0;
    switch ( sbpart ) {
    case PART_WINDOW_CAPTION:
        ipartid = WP_CAPTION;
        istateid = CS_ACTIVE;
        break;
    case PART_WINDOW_MINBUTTON:
        ipartid = WP_MINBUTTON;
        if ( ( sbstate & UISTATE_DISABLED ) != 0 )
            istateid = MINBS_DISABLED;
        else if ( ( sbstate & UISTATE_HOT ) != 0 )
            istateid = MINBS_HOT;
        else if ( ( sbstate & UISTATE_PUSHED ) != 0 )
            istateid = MINBS_PUSHED;
        else
            istateid = MINBS_NORMAL;
        break;
    case PART_WINDOW_MAXBUTTON:
        ipartid = WP_MAXBUTTON;
        if ( ( sbstate & UISTATE_DISABLED ) != 0 )
            istateid = MAXBS_DISABLED;
        else if ( ( sbstate & UISTATE_HOT ) != 0 )
            istateid = MAXBS_HOT;
        else if ( ( sbstate & UISTATE_PUSHED ) != 0 )
            istateid = MAXBS_PUSHED;
        else
            istateid = MAXBS_NORMAL;
        break;
    case PART_WINDOW_RESTOREBUTTON:
        ipartid = WP_RESTOREBUTTON;
        if ( ( sbstate & UISTATE_DISABLED ) != 0 )
            istateid = RBS_DISABLED;
        else if ( ( sbstate & UISTATE_HOT ) != 0 )
            istateid = RBS_HOT;
        else if ( ( sbstate & UISTATE_PUSHED ) != 0 )
            istateid = RBS_PUSHED;
        else
            istateid = RBS_NORMAL;
        break;
    case PART_WINDOW_CLOSEBUTTON:
        ipartid = WP_CLOSEBUTTON;
        if ( ( sbstate & UISTATE_DISABLED ) != 0 )
            istateid = CBS_DISABLED;
        else if ( ( sbstate & UISTATE_HOT ) != 0 )
            istateid = CBS_HOT;
        else if ( ( sbstate & UISTATE_PUSHED ) != 0 )
            istateid = CBS_PUSHED;
        else
            istateid = CBS_NORMAL;
        break;
    case PART_WINDOW_DIALOG:
        ipartid = WP_DIALOG;
    }

    bool bModesave = gorh.SetHDCmode();
    HTHEME hTheme =::OpenThemeData( hWnd, _T( "Window" ) );
    ::DrawThemeBackground( hTheme, gorh, ipartid, istateid, &rcPaint, NULL );
    ::CloseThemeData( hTheme );
    gorh.Setmode( bModesave );
}