#pragma once

class CDefaultSkinUI
{
public:
    //     enum {
    //         COLOR_3D_FOREGROUND = 0xffd4d0c8,
    //         COLOR_3D_SHADOW1 = 0xff808080,
    //         COLOR_3D_SHADOW2 = 0xff404040,
    //         COLOR_FG_BLUE = 0xff0a246A
    //     };
    enum {
        PART_SCROLLBAR_BUTTON_UP = 0,
        PART_SCROLLBAR_BUTTON_DOWN,
        PART_SCROLLBAR_BUTTON_LEFT,
        PART_SCROLLBAR_BUTTON_RIGHT,
        PART_SCROLLBAR_LOWVERT,
        PART_SCROLLBAR_LOWHORZ,
        PART_SCROLLBAR_UPVERT,
        PART_SCROLLBAR_UPHORZ,
        PART_SCROLLBAR_THUMBVERT,
        PART_SCROLLBAR_THUMBHORZ,
        PART_SCROLLBAR_RAILVERT,
        PART_SCROLLBAR_RAILHORZ,
        PART_WINDOW_CAPTION,
        PART_WINDOW_MINBUTTON,
        PART_WINDOW_RESTOREBUTTON,
        PART_WINDOW_MAXBUTTON,
        PART_WINDOW_CLOSEBUTTON,
        PART_WINDOW_DIALOG
    };
public:

    static void DrawButton( GRAPHorHDC& gorh, HWND hWnd, const RECT& rcPaint, UINT btstate );
    static void DrawOption( GRAPHorHDC& gorh, HWND hWnd, const RECT& rcPaint, UINT btstate, bool bGroup );
    static void DrawProgress( GRAPHorHDC& gorh, HWND hWnd, const RECT& rcPaint, const RECT& rcFg , bool bVert );
    static void DrawEdit( GRAPHorHDC& gorh, HWND hWnd, const RECT& rcPaint, UINT btstate );
    static void DrawScrollbar( GRAPHorHDC& gorh, HWND hWnd, const RECT& rcPaint, UINT sbstate, UINT sbpart );
    static void DrawWindow( GRAPHorHDC& gorh, HWND hWnd, const RECT& rcPaint, UINT sbstate, UINT sbpart );
};
