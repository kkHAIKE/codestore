
#include "StdAfx.h"
#include "UIRender.h"

/////////////////////////////////////////////////////////////////////////////////////
//
//

GRAPHorHDC::GRAPHorHDC( HDC hdc ): m_rgn( 0, 0, 9999, 9999 ), m_hdc( hdc ), g( hdc ), is_graph( false ), bGraphSet( true ), bHDCSet( true )
{
    g.GetHDC();
}
GRAPHorHDC::~GRAPHorHDC()
{
    if ( !is_graph )
        SetGRAPHmode();
}
CRgn GRAPHorHDC::IntersectClip( const RECT& rc )
{
    CRgn oldrgn = m_rgn;
    m_rgn.Intersect( &rc );
    if ( is_graph ) {
        //if(!m_rgn.IsEmpty())
        g.SetClip( m_rgn );
        //else
        //	g.ResetClip();
        bGraphSet = true;
        bHDCSet = false;
    }
    else {
        //if(!m_rgn.IsEmpty())
        ::SelectClipRgn( m_hdc, m_rgn );
        //else
        //	::SelectClipRgn( m_hdc, NULL );
        bGraphSet = false;
        bHDCSet = true;
    }

    return oldrgn;
}
CRgn GRAPHorHDC::SetClip( const CRgn& rgn )
{
    CRgn oldrgn = m_rgn;
    m_rgn = rgn;
    if ( is_graph ) {
        //if(!m_rgn.IsEmpty())
        g.SetClip( m_rgn );
        //else
        //	g.ResetClip();
        bGraphSet = true;
        bHDCSet = false;
    }
    else {
        //if(!m_rgn.IsEmpty())
        ::SelectClipRgn( m_hdc, m_rgn );
        //else
        //	::SelectClipRgn( m_hdc, NULL );
        bGraphSet = false;
        bHDCSet = true;
    }

    return oldrgn;
}
bool GRAPHorHDC::SetGRAPHmode()
{
    if ( is_graph ) return true;
    is_graph = true;
    g.ReleaseHDC( m_hdc );
    if ( !bGraphSet ) {
        //if(!m_rgn.IsEmpty())
        g.SetClip( m_rgn );
        //else
        //	g.ResetClip();
        bGraphSet = true;
    }
    return false;
}
bool GRAPHorHDC::SetHDCmode()
{
    if ( !is_graph ) return false;
    is_graph = false;
    g.GetHDC();
    if ( !bHDCSet ) {
        //if(!m_rgn.IsEmpty())
        ::SelectClipRgn( m_hdc, m_rgn );
        //else
        //	::SelectClipRgn( m_hdc, NULL );
        bHDCSet = true;
    }
    return true;
}
bool GRAPHorHDC::Setmode( bool mode )
{
    if ( mode )
        return SetGRAPHmode();
    else
        return SetHDCmode();
}
GRAPHorHDC::operator HDC() const
{
    ASSERT( !is_graph );
    return m_hdc;
}
GRAPHorHDC::operator Graphics& ()
{
    ASSERT( is_graph );
    return g;
}

/////////////////////////////////////////////////////////////////////////////////////
//
//

Bitmap* CRenderEngine::LoadImage( STRINGorID bitmap, STRINGorID type )
{
    if ( bitmap == NULL )return NULL;

    Bitmap* b_ret = NULL;

    if ( type == NULL ) {
        b_ret = Bitmap::FromFile( bitmap );
        if ( b_ret->GetLastStatus() ) {
            delete b_ret;
            b_ret = NULL;
        }
    }
    else {
        HRSRC hResource = ::FindResource( CPaintManagerUI::GetResourceInstance(), bitmap, type );
        if ( hResource == NULL ) return NULL;
        HGLOBAL hGlobal = ::LoadResource( CPaintManagerUI::GetResourceInstance(), hResource );
        if ( hGlobal != NULL ) {
            DWORD dwSize = ::SizeofResource( CPaintManagerUI::GetResourceInstance(), hResource );
            if ( dwSize != 0 ) {
                HGLOBAL hGmem =::GlobalAlloc( GHND, dwSize );
                if ( hGmem != NULL ) {
                    ::CopyMemory( ::GlobalLock( hGmem ), ::LockResource( hGlobal ), dwSize );
                    ::GlobalUnlock( hGmem );

                    IStream* pStream = NULL;
                    if ( SUCCEEDED( CreateStreamOnHGlobal( hGmem, FALSE, &pStream ) ) ) {
                        b_ret = Bitmap::FromStream( pStream );
                        if ( b_ret->GetLastStatus() ) {
                            delete b_ret;
                            b_ret = NULL;
                        }
                        pStream->Release();
                    }
                    ::GlobalFree( hGmem );
                }
            }
            ::FreeResource( hGlobal );
        }
    }
    return b_ret;
}

ColorMatrix g_HotMat = {	1.05f, 0.00f, 0.00f, 0.00f, 0.00f,
                            0.00f, 1.05f, 0.00f, 0.00f, 0.00f,
                            0.00f, 0.00f, 1.05f, 0.00f, 0.00f,
                            0.00f, 0.00f, 0.00f, 1.00f, 0.00f,
                            0.05f, 0.05f, 0.05f, 0.00f, 1.00f
                       };
ColorMatrix g_GrayMat = {	0.30f, 0.30f, 0.30f, 0.00f, 0.00f,
                            0.59f, 0.59f, 0.59f, 0.00f, 0.00f,
                            0.11f, 0.11f, 0.11f, 0.00f, 0.00f,
                            0.00f, 0.00f, 0.00f, 1.00f, 0.00f,
                            0.00f, 0.00f, 0.00f, 0.00f, 1.00f
                        };

void CRenderEngine::DrawImage( GRAPHorHDC& gorh, Bitmap* hBitmap, const RECT& rc, const RECT& rcPaint, const RECT& rcBmpPart,
                               const RECT& rcCorners,  BYTE uFade, DWORD mask, DWORD style )
{
    bool bModesave = gorh.SetGRAPHmode();
    Graphics& g = gorh;

    ImageAttributes iAtt;

    ColorMatrix matrix = {
        1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
        0.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        0.0f,  0.0f,  0.0f,  0.0f,  1.0f
    };
    if ( ( style & UIDRAW_HIGHLIGHT ) != 0 ) {
        matrix = g_HotMat;
    }
    else if ( ( style & UIDRAW_GRAY ) != 0 ) {
        matrix = g_GrayMat;
    }
    if ( uFade != 255 ) {
        matrix.m[3][3] = static_cast<float>( uFade ) * 1.0f / 255.0f;
    }
    iAtt.SetColorMatrix( &matrix, ColorMatrixFlagsDefault, ColorAdjustTypeBitmap );

    if ( ( style & UIDRAW_USEMASK ) != 0 ) {
        iAtt.SetColorKey( mask, mask, ColorAdjustTypeBitmap );
    }
    if ( ( style & UIDRAW_TILE ) != 0 ) {
        iAtt.SetWrapMode( WrapModeTile );
    }

    RECT rcTemp = {0};
    RECT rcDest = {0};

    if ( ( style & UIDRAW_HOLE ) == 0 ) {
        rcDest.left = rc.left + rcCorners.left;
        rcDest.top = rc.top + rcCorners.top;
        rcDest.right = rc.right - rc.left - rcCorners.left - rcCorners.right;
        rcDest.bottom = rc.bottom - rc.top - rcCorners.top - rcCorners.bottom;
        rcDest.right += rcDest.left;
        rcDest.bottom += rcDest.top;
        if ( ::IntersectRect( &rcTemp, &rcPaint, &rcDest ) ) {
            rcDest.right -= rcDest.left;
            rcDest.bottom -= rcDest.top;
            g.DrawImage( hBitmap, Rect( rcDest.left, rcDest.top, rcDest.right, rcDest.bottom ),
                         rcBmpPart.left + rcCorners.left, rcBmpPart.top + rcCorners.top,
                         rcBmpPart.right - rcBmpPart.left - rcCorners.left - rcCorners.right,
                         rcBmpPart.bottom - rcBmpPart.top - rcCorners.top - rcCorners.bottom,
                         UnitPixel, &iAtt );
        }
    }

    // left-top
    if ( rcCorners.left > 0 && rcCorners.top > 0 ) {
        rcDest.left = rc.left;
        rcDest.top = rc.top;
        rcDest.right = rcCorners.left;
        rcDest.bottom = rcCorners.top;
        rcDest.right += rcDest.left;
        rcDest.bottom += rcDest.top;
        if ( ::IntersectRect( &rcTemp, &rcPaint, &rcDest ) ) {
            rcDest.right -= rcDest.left;
            rcDest.bottom -= rcDest.top;
            g.DrawImage( hBitmap, Rect( rcDest.left, rcDest.top, rcDest.right, rcDest.bottom ),
                         rcBmpPart.left, rcBmpPart.top, rcCorners.left, rcCorners.top,
                         UnitPixel, &iAtt );
        }
    }
    // top
    if ( rcCorners.top > 0 ) {
        rcDest.left = rc.left + rcCorners.left;
        rcDest.top = rc.top;
        rcDest.right = rc.right - rc.left - rcCorners.left - rcCorners.right;
        rcDest.bottom = rcCorners.top;
        rcDest.right += rcDest.left;
        rcDest.bottom += rcDest.top;
        if ( ::IntersectRect( &rcTemp, &rcPaint, &rcDest ) ) {
            rcDest.right -= rcDest.left;
            rcDest.bottom -= rcDest.top;
            g.DrawImage( hBitmap, Rect( rcDest.left, rcDest.top, rcDest.right, rcDest.bottom ),
                         rcBmpPart.left + rcCorners.left, rcBmpPart.top, rcBmpPart.right - rcBmpPart.left - \
                         rcCorners.left - rcCorners.right, rcCorners.top,
                         UnitPixel, &iAtt );
        }
    }
    // right-top
    if ( rcCorners.right > 0 && rcCorners.top > 0 ) {
        rcDest.left = rc.right - rcCorners.right;
        rcDest.top = rc.top;
        rcDest.right = rcCorners.right;
        rcDest.bottom = rcCorners.top;
        rcDest.right += rcDest.left;
        rcDest.bottom += rcDest.top;
        if ( ::IntersectRect( &rcTemp, &rcPaint, &rcDest ) ) {
            rcDest.right -= rcDest.left;
            rcDest.bottom -= rcDest.top;
            g.DrawImage( hBitmap, Rect( rcDest.left, rcDest.top, rcDest.right, rcDest.bottom ),
                         rcBmpPart.right - rcCorners.right, rcBmpPart.top, rcCorners.right, rcCorners.top,
                         UnitPixel, &iAtt );
        }
    }
    // left
    if ( rcCorners.left > 0 ) {
        rcDest.left = rc.left;
        rcDest.top = rc.top + rcCorners.top;
        rcDest.right = rcCorners.left;
        rcDest.bottom = rc.bottom - rc.top - rcCorners.top - rcCorners.bottom;
        rcDest.right += rcDest.left;
        rcDest.bottom += rcDest.top;
        if ( ::IntersectRect( &rcTemp, &rcPaint, &rcDest ) ) {
            rcDest.right -= rcDest.left;
            rcDest.bottom -= rcDest.top;
            g.DrawImage( hBitmap, Rect( rcDest.left, rcDest.top, rcDest.right, rcDest.bottom ),
                         rcBmpPart.left, rcBmpPart.top + rcCorners.top, rcCorners.left, rcBmpPart.bottom - \
                         rcBmpPart.top - rcCorners.top - rcCorners.bottom,
                         UnitPixel, &iAtt );
        }
    }
    // right
    if ( rcCorners.right > 0 ) {
        rcDest.left = rc.right - rcCorners.right;
        rcDest.top = rc.top + rcCorners.top;
        rcDest.right = rcCorners.right;
        rcDest.bottom = rc.bottom - rc.top - rcCorners.top - rcCorners.bottom;
        rcDest.right += rcDest.left;
        rcDest.bottom += rcDest.top;
        if ( ::IntersectRect( &rcTemp, &rcPaint, &rcDest ) ) {
            rcDest.right -= rcDest.left;
            rcDest.bottom -= rcDest.top;
            g.DrawImage( hBitmap, Rect( rcDest.left, rcDest.top, rcDest.right, rcDest.bottom ),
                         rcBmpPart.right - rcCorners.right, rcBmpPart.top + rcCorners.top, rcCorners.right,
                         rcBmpPart.bottom - rcBmpPart.top - rcCorners.top - rcCorners.bottom,
                         UnitPixel, &iAtt );
        }
    }
    // left-bottom
    if ( rcCorners.left > 0 && rcCorners.bottom > 0 ) {
        rcDest.left = rc.left;
        rcDest.top = rc.bottom - rcCorners.bottom;
        rcDest.right = rcCorners.left;
        rcDest.bottom = rcCorners.bottom;
        rcDest.right += rcDest.left;
        rcDest.bottom += rcDest.top;
        if ( ::IntersectRect( &rcTemp, &rcPaint, &rcDest ) ) {
            rcDest.right -= rcDest.left;
            rcDest.bottom -= rcDest.top;
            g.DrawImage( hBitmap, Rect( rcDest.left, rcDest.top, rcDest.right, rcDest.bottom ),
                         rcBmpPart.left, rcBmpPart.bottom - rcCorners.bottom, rcCorners.left, rcCorners.bottom,
                         UnitPixel, &iAtt );
        }
    }
    // bottom
    if ( rcCorners.bottom > 0 ) {
        rcDest.left = rc.left + rcCorners.left;
        rcDest.top = rc.bottom - rcCorners.bottom;
        rcDest.right = rc.right - rc.left - rcCorners.left - rcCorners.right;
        rcDest.bottom = rcCorners.bottom;
        rcDest.right += rcDest.left;
        rcDest.bottom += rcDest.top;
        if ( ::IntersectRect( &rcTemp, &rcPaint, &rcDest ) ) {
            rcDest.right -= rcDest.left;
            rcDest.bottom -= rcDest.top;
            g.DrawImage( hBitmap, Rect( rcDest.left, rcDest.top, rcDest.right, rcDest.bottom ),
                         rcBmpPart.left + rcCorners.left, rcBmpPart.bottom - rcCorners.bottom, \
                         rcBmpPart.right - rcBmpPart.left - rcCorners.left - rcCorners.right, rcCorners.bottom,
                         UnitPixel, &iAtt );
        }
    }
    // right-bottom
    if ( rcCorners.right > 0 && rcCorners.bottom > 0 ) {
        rcDest.left = rc.right - rcCorners.right;
        rcDest.top = rc.bottom - rcCorners.bottom;
        rcDest.right = rcCorners.right;
        rcDest.bottom = rcCorners.bottom;
        rcDest.right += rcDest.left;
        rcDest.bottom += rcDest.top;
        if ( ::IntersectRect( &rcTemp, &rcPaint, &rcDest ) ) {
            rcDest.right -= rcDest.left;
            rcDest.bottom -= rcDest.top;
            g.DrawImage( hBitmap, Rect( rcDest.left, rcDest.top, rcDest.right, rcDest.bottom ),
                         rcBmpPart.right - rcCorners.right, rcBmpPart.bottom - rcCorners.bottom, rcCorners.right, \
                         rcCorners.bottom,
                         UnitPixel, &iAtt );
        }
    }
    gorh.Setmode( bModesave );
}

bool CRenderEngine::DrawImageString( GRAPHorHDC& gorh, CPaintManagerUI* pManager, RECT& rc, const RECT& rcPaint,
                                     LPCTSTR pStrImage, LPCTSTR pStrModify, bool bMeasure )
{
    // 1、aaa.jpg
    // 2、file='aaa.jpg' res='' restype='0' dest='0,0,0,0' source='0,0,0,0' corner='0,0,0,0'
    // mask='#FF0000' fade='255' hole='false'
    // 字符格式必须紧凑，不能有多余空格或tab，图片本身是否带有alpha通道看图片类型

    if ( ::IsRectEmpty( &rc ) || ::IsRectEmpty( &rcPaint ) || pStrImage == NULL || *pStrImage == 0 ) return false;

    CStdString sImageName = pStrImage;
    CStdString sImageResType;
    RECT rcItem = rc;
    RECT rcBmpPart = {0};
    RECT rcCorner = {0};
    DWORD dwMask = 0;
    BYTE bFade = 255;
    DWORD dwStyle = 0;

    if ( sImageName.Find( _T( '=' ) ) != -1 ) {
        CStdString sParse;
        CStdString sValue;

        for ( int i = 0; i < 2; ++i ) {
            if ( i == 0 )
                sParse = _T( "<temp " ) + sImageName + _T( " />" );
            else if ( pStrModify != NULL && *pStrModify != 0 )
                sParse = _T( "<temp " ) + CStdString( pStrModify ) + _T( " />" );
            else continue;

            CMarkupMSXML xml;
            if ( !xml.SetDoc( sParse ) )
                return false;
            xml.FindElem();

            if ( sValue = xml.GetAttrib( _T( "file" ) ), !sValue.IsEmpty() ) {
                sImageName = sValue;
            }
            else if ( sValue = xml.GetAttrib( _T( "res" ) ), !sValue.IsEmpty() ) {
                sImageName = sValue;
            }

            if ( sValue = xml.GetAttrib( _T( "restype" ) ), !sValue.IsEmpty() ) {
                sImageResType = sValue;
            }

            if ( sValue = xml.GetAttrib( _T( "dest" ) ), !sValue.IsEmpty() ) {
                RECT t_rc = RectFromString( sValue );
                rcItem.left = rc.left + t_rc.left;
                rcItem.top = rc.top + t_rc.top;
                rcItem.right = rc.left + t_rc.right;
                rcItem.bottom = rc.top + t_rc.bottom;
            }

            if ( sValue = xml.GetAttrib( _T( "source" ) ), !sValue.IsEmpty() ) {
                rcBmpPart = RectFromString( sValue );
            }

            if ( sValue = xml.GetAttrib( _T( "corner" ) ), !sValue.IsEmpty() ) {
                rcCorner = RectFromString( sValue );
            }

            if ( sValue = xml.GetAttrib( _T( "mask" ) ), !sValue.IsEmpty() ) {
                if ( sValue[0] == _T( '#' ) ) dwMask = _tcstoul( sValue.GetData() + 1, NULL, 16 );
                else dwMask = _tcstoul( sValue, NULL, 16 );

                dwStyle |= UIDRAW_USEMASK;
            }

            if ( sValue = xml.GetAttrib( _T( "fade" ) ), !sValue.IsEmpty() ) {
                bFade = static_cast<BYTE>( _tcstoul( sValue, NULL, 10 ) );
            }

            if ( sValue = xml.GetAttrib( _T( "hole" ) ), !sValue.IsEmpty() ) {
                if ( sValue == _T( "true" ) )
                    dwStyle |= UIDRAW_HOLE;
            }

            if ( sValue = xml.GetAttrib( _T( "tile" ) ), !sValue.IsEmpty() ) {
                if ( sValue == _T( "true" ) )
                    dwStyle |= UIDRAW_TILE;
            }
            if ( sValue = xml.GetAttrib( _T( "highlight" ) ), !sValue.IsEmpty() ) {
                if ( sValue == _T( "true" ) )
                    dwStyle |= UIDRAW_HIGHLIGHT;
            }
            if ( sValue = xml.GetAttrib( _T( "gray" ) ), !sValue.IsEmpty() ) {
                if ( sValue == _T( "true" ) )
                    dwStyle |= UIDRAW_GRAY;
            }
        }
    }

    RECT rcTemp;
    if ( !::IntersectRect( &rcTemp, &rcItem, &rc ) ) return true;
    if ( !::IntersectRect( &rcTemp, &rcItem, &rcPaint ) ) return true;

    Bitmap* data = NULL;
    if ( sImageResType.IsEmpty() ) {
        data = pManager->GetImageEx( sImageName );
    }
    else {
        data = pManager->GetImageEx( sImageName, sImageResType );
    }
    if ( data == NULL ) return false;

    if ( rcBmpPart.left == 0 && rcBmpPart.right == 0 && rcBmpPart.top == 0 && rcBmpPart.bottom == 0 ) {
        rcBmpPart.right = data->GetWidth();
        rcBmpPart.bottom = data->GetHeight();
    }
    if ( bMeasure )
        rc = rcBmpPart;
    else
        DrawImage( gorh, data, rcItem, rcPaint, rcBmpPart, rcCorner, bFade, dwMask, dwStyle );
    return true;
}

void CRenderEngine::DrawColor( GRAPHorHDC& gorh, const RECT& rc, DWORD color )
{
    if ( ::IsRectEmpty( &rc ) || color <= 0x00FFFFFF )return;
    bool bModesave = gorh.SetGRAPHmode();
    Graphics& g = gorh;
    g.FillRectangle( &SolidBrush( color ), rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top );
    gorh.Setmode( bModesave );
}

void CRenderEngine::DrawGradient( GRAPHorHDC& gorh, const RECT& rc, DWORD dwFirst, DWORD dwSecond, bool bVertical )
{
    bool bModesave = gorh.SetGRAPHmode();
    Graphics& g = gorh;
    Rect rcTemp( rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top );
    g.FillRectangle( &LinearGradientBrush( rcTemp, dwFirst, dwSecond, bVertical ? LinearGradientModeVertical : LinearGradientModeHorizontal ), rcTemp );
    gorh.Setmode( bModesave );
}

void CRenderEngine::DrawLine( GRAPHorHDC& gorh, const RECT& rc, int nSize, DWORD dwPenColor )
{
    if ( ::IsRectEmpty( &rc ) || dwPenColor <= 0x00FFFFFF )return;
    if ( nSize < 1 )nSize = 1;

    bool bModesave = gorh.SetHDCmode();

    HPEN hPen = ::CreatePen( PS_SOLID, nSize, RGB( GetBValue( dwPenColor ), GetGValue( dwPenColor ), GetRValue( dwPenColor ) ) );
    HPEN hOldPen = ( HPEN )::SelectObject( gorh, hPen );

    ::MoveToEx( gorh, rc.left, rc.top, NULL );
    ::LineTo( gorh, rc.right, rc.bottom );

    ::SelectObject( gorh, hOldPen );
    ::DeleteObject( hPen );

    gorh.Setmode( bModesave );
}

void CRenderEngine::DrawRect( GRAPHorHDC& gorh, const RECT& rc, int nSize, DWORD dwPenColor )
{
    if ( ::IsRectEmpty( &rc ) || dwPenColor <= 0x00FFFFFF ) return;
    if ( nSize < 1 )nSize = 1;

    bool bModesave = gorh.SetHDCmode();

    HPEN hPen = ::CreatePen( PS_SOLID | PS_INSIDEFRAME, nSize, RGB( GetBValue( dwPenColor ), GetGValue( dwPenColor ), GetRValue( dwPenColor ) ) );
    HPEN hOldPen = ( HPEN )::SelectObject( gorh, hPen );
    HBRUSH hOldBrush = ( HBRUSH )::SelectObject( gorh, ::GetStockObject( HOLLOW_BRUSH ) );

    ::Rectangle( gorh, rc.left, rc.top, rc.right, rc.bottom );

    ::SelectObject( gorh, hOldBrush );
    ::SelectObject( gorh, hOldPen );
    ::DeleteObject( hPen );

    gorh.Setmode( bModesave );
}

void CRenderEngine::DrawText( GRAPHorHDC& gorh, CPaintManagerUI* pManager, RECT& rc, LPCTSTR pstrText, DWORD dwTextColor, int iFont, UINT uStyle )
{
    if ( ::IsRectEmpty( &rc ) || pstrText == NULL || *pstrText == 0 ) return;

    bool bModesave = gorh.SetHDCmode();

    int iOldBkMode =::SetBkMode( gorh, TRANSPARENT );
    DWORD dOldTextColor =::SetTextColor( gorh, RGB( GetBValue( dwTextColor ), GetGValue( dwTextColor ), GetRValue( dwTextColor ) ) );
    HFONT hOldFont = ( HFONT )::SelectObject( gorh, pManager->GetFont( iFont ) );

    ::DrawText( gorh, pstrText, -1, &rc, uStyle );

    ::SelectObject( gorh, hOldFont );
    ::SetTextColor( gorh, dOldTextColor );
    ::SetBkMode( gorh, iOldBkMode );

    gorh.Setmode( bModesave );
}

void CRenderEngine::DrawHtmlText( GRAPHorHDC& gorh, CPaintManagerUI* pManager, RECT& rc, LPCTSTR strText, DWORD dwTextColor, int iFont, UINT uStyle, CRgn** pLinks, CStdString** sLinks, int* pnLinkRects )
{
    // 考虑到在xml编辑器中使用<>符号不方便，可以使用{}符号代替
    // 输出{或<使用转义：<{> {<}，注意<在xml里要用用转义代替
    // 如果要改链接的字体和颜色把标志放在a后
    // The string formatter supports a kind of "mini-html" that consists of various short tags:
    //
    //   Link:             <a x>text</a>      where x(optional) = link content, normal like app:notepad or http:www.xxx.com
    //   Bold:             <b>text</b>
    //   Color:            <c #xxxxxx #xxxxxx>text</c>  where x = RGB in hex and y(optional) = RGB for hoverlink
    //   Change font:      <f x y>text</f>      where x = font id and y(optional)=font id for hoverlink
    //   Image:            <i x y>              where x = image name and y(optional) = imagelist id
    //   NewLine           <n>
    //   Paragraph:        <p i>
    //   X Indent:         <x i>                where i = hor indent in pixels
    //   Y Indent:         <y i>                where i = ver indent in pixels

    if ( ::IsRectEmpty( &rc ) || strText == NULL || *strText == 0 ) return;

    int nLinkRects = 0;
    LPTSTR pstrText = const_cast<LPTSTR>( strText );
    if ( pnLinkRects != NULL && pLinks != NULL && sLinks != NULL ) {
        nLinkRects = *pnLinkRects;
        if ( nLinkRects == 0 ) {
            while ( *pstrText != 0 ) {
                if ( ( *pstrText == _T( '<' ) || *pstrText == _T( '{' ) )
                        && pstrText[1] == _T( 'a' )
                        && ( pstrText[2] == _T( ' ' ) || pstrText[2] == _T( '>' ) || pstrText[2] == _T( '}' ) ) )
                    ++nLinkRects;
                pstrText =::CharNext( pstrText );
            }
            pstrText = const_cast<LPTSTR>( strText );
            *pnLinkRects = nLinkRects;
            if ( *pLinks ) delete[] *pLinks;
            if ( *sLinks ) delete[] *sLinks;
            *pLinks = new CRgn[nLinkRects];
            *sLinks = new CStdString[nLinkRects];
        }
    }

    bool bDraw = ( uStyle & DT_CALCRECT ) == 0;
    //CRgn oldRegion;
    bool bModesave = gorh.SetHDCmode();
    //if ( bDraw )
    //    oldRegion = gorh.IntersectClip( rc );

    HFONT hOldFont = ( HFONT ) ::SelectObject( gorh, pManager->GetFont( iFont ) );
    int iOldBkMode =::SetBkMode( gorh, TRANSPARENT );
    DWORD dOldTextColor =::SetTextColor( gorh, RGB( GetBValue( dwTextColor ), GetGValue( dwTextColor ), GetRValue( dwTextColor ) ) );
    // If the drawstyle include a alignment, we'll need to first determine the text-size so
    // we can draw it at the correct position...
    //     if ( ( uStyle & DT_SINGLELINE ) != 0 && ( ( uStyle & DT_VCENTER ) != 0 || ( uStyle & DT_CENTER ) != 0 ||
    //             ( uStyle & DT_RIGHT ) != 0 || ( uStyle & DT_BOTTOM ) != 0 ) && bDraw ) {
    //         RECT rcText = { 0, 0, 9999, 9999 };
    //         DrawHtmlText( gorh, pManager, rcText, pstrText, dwTextColor, uStyle | DT_CALCRECT );
    //         if ( ( uStyle & DT_VCENTER ) != 0 ) {
    //             rc.top = rc.top + ( ( rc.bottom - rc.top ) / 2 ) - ( ( rcText.bottom - rcText.top ) / 2 );
    //             rc.bottom = rc.top + ( rcText.bottom - rcText.top );
    //         }
    //         else if ( ( uStyle & DT_BOTTOM ) != 0 )
    //             rc.top = rc.bottom - ( rcText.bottom - rcText.top );
    //         if ( ( uStyle & DT_CENTER ) != 0 ) {
    //             rc.left = rc.left + ( ( rc.right - rc.left ) / 2 ) - ( ( rcText.right - rcText.left ) / 2 );
    //             rc.right = rc.left + ( rcText.right - rcText.left );
    //         }
    //         else if ( ( uStyle & DT_RIGHT ) != 0 )
    //             rc.left = rc.right - ( rcText.right - rcText.left );
    //     }

    // Determine if we're hovering over a link, because we would like to
    // indicate it by coloring the link text.
    // BUG: This assumes that the prcLink has already been filled once with
    //      link coordinates! That is usually not the case at first repaint. We'll clear
    //      the remanining entries at exit.
    int iHoverLink = -1;
    POINT ptMouse = pManager->GetMousePos();
    for ( int i = 0; i < nLinkRects; ++i ) {
        if ( ( *pLinks )[i].PtInRegion( &ptMouse ) ) {iHoverLink = i; break;}
    }

    TEXTMETRIC tm = pManager->GetFontInfo( iFont );
    POINT pt = { rc.left, rc.top };
    int iLinkIndex = 0;
    int cyLine = tm.tmHeight + tm.tmExternalLeading;
    int cyMinHeight = 0;
    int cxMaxWidth = 0;
    POINT ptLinkStart = { 0 };
    //是否在链接内
    bool bInLink = false;

    while ( *pstrText != _T( '\0' ) ) {
        if ( pt.x >= rc.right || *pstrText == _T( '\n' ) ) {
            // A new link was detected/requested. We'll adjust the line height
            // for the next line and expand the link hitbox (if any)
            if ( bInLink && iLinkIndex < nLinkRects )
                ( *pLinks )[iLinkIndex].Join( CRgn( ptLinkStart.x, ptLinkStart.y, MIN( pt.x, rc.right ), pt.y + tm.tmHeight ) );
            if ( ( uStyle & DT_SINGLELINE ) != 0 ) break;
            if ( *pstrText == _T( '\n' ) ) ++pstrText;
            pt.x = rc.left;
            pt.y += cyLine/* - tm.tmDescent*/;
            if ( pt.y > rc.bottom && bDraw ) break;
            ptLinkStart = pt;
            cyLine = tm.tmHeight + tm.tmExternalLeading;
            //if( pt.x >= rc.right ) break;
            //空格应该是要输出字符
            //while( *pstrText == _T(' ') ) pstrText++;
        }
        else if ( ( *pstrText == _T( '<' ) || *pstrText == _T( '{' ) )
                  && ( pstrText[1] >= _T( 'a' ) && pstrText[1] <= _T( 'z' ) )
                  && ( pstrText[2] == _T( ' ' ) || pstrText[2] == _T( '>' ) || pstrText[2] == _T( '}' ) ) ) {
            ++pstrText;
            switch ( *pstrText ) {
            case _T( 'a' ): { // Link
                    ++pstrText;
                    if ( *pstrText == _T( ' ' ) ) ++pstrText;;
                    if ( iLinkIndex < nLinkRects ) {
                        CStdString* pStr = *sLinks + iLinkIndex;
                        if ( pStr->IsEmpty() ) {
                            while ( *pstrText != _T( '\0' ) && *pstrText != _T( '>' ) && *pstrText != _T( '}' ) ) {
                                LPCTSTR pstrTemp = ::CharNext( pstrText );
                                while ( pstrText < pstrTemp ) {
                                    *pStr += *pstrText++;
                                }
                            }
                        }
                        else {
                            while ( *pstrText != _T( '\0' ) && *pstrText != _T( '>' ) && *pstrText != _T( '}' ) )++pstrText;
                        }
                    }
                    DWORD clrColor;
                    if ( iLinkIndex == iHoverLink ) {
                        clrColor = pManager->GetDefaultLinkFontHoverColor();
                        ::SelectObject( gorh, pManager->GetDefaultLinkFont() );
                        tm = pManager->GetDefaultLinkFontInfo();
                    }
                    else {
                        clrColor = pManager->GetDefaultLinkFontColor();
                        ::SelectObject( gorh, pManager->GetFont( iFont ) );
                        tm = pManager->GetFontInfo( iFont );
                    }
                    ::SetTextColor( gorh,  RGB( GetBValue( clrColor ), GetGValue( clrColor ), GetRValue( clrColor ) ) );

                    cyLine = MAX( cyLine, tm.tmHeight + tm.tmExternalLeading );
                    ptLinkStart = pt;
                    bInLink = true;
                }
                break;
            case _T( 'f' ): { // Font
                    ++pstrText;
                    int iFont = _tcstol( pstrText, &pstrText, 10 );
                    ::SelectObject( gorh, pManager->GetFont( iFont ) );
                    tm = pManager->GetFontInfo( iFont );

                    if ( *pstrText == _T( ' ' ) ) {
                        int iFontLink = _tcstol( pstrText, &pstrText, 10 );
                        if ( iLinkIndex == iHoverLink ) {
                            ::SelectObject( gorh, pManager->GetFont( iFontLink ) );
                            tm = pManager->GetFontInfo( iFontLink );
                        }
                    }
                    cyLine = MAX( cyLine, tm.tmHeight + tm.tmExternalLeading );
                }
                break;
            case _T( 'b' ): { // Bold text
                    ++pstrText;
                    ::SelectObject( gorh, pManager->GetDefaultBoldFont() );
                    tm = pManager->GetDefaultBoldFontInfo();
                    cyLine = MAX( cyLine, tm.tmHeight + tm.tmExternalLeading );
                }
                break;
            case _T( 'x' ): { // Indent
                    ++pstrText;
                    int iWidth = _tcstol( pstrText, &pstrText, 10 );
                    pt.x += iWidth;
                    cxMaxWidth = MAX( cxMaxWidth, pt.x );
                }
                break;
            case _T( 'n' ): { // Newline
                    ++pstrText;
                    if ( ( uStyle & DT_SINGLELINE ) != 0 ) break;
                    if ( bInLink && iLinkIndex < nLinkRects )
                        ( *pLinks )[iLinkIndex].Join( CRgn( ptLinkStart.x, ptLinkStart.y, MIN( pt.x, rc.right ), pt.y + tm.tmHeight ) );
                    pt.x = rc.left;
                    pt.y += cyLine/* - tm.tmDescent*/;
                    if ( pt.y > rc.bottom && bDraw ) break;
                    ptLinkStart = pt;
                    cyLine = tm.tmHeight + tm.tmExternalLeading;
                    //if( pt.x >= rc.right ) break;
                }
                break;
            case _T( 'p' ): { // Paragraph
                    ++pstrText;
                    pt.x = rc.right;
                    int pdis = 5;
                    if ( *pstrText == _T( ' ' ) )
                        pdis = _tcstol( pstrText, &pstrText, 10 );
                    cyLine = MAX( cyLine, tm.tmHeight + tm.tmExternalLeading ) + pdis;
                    ::SelectObject( gorh, pManager->GetFont( iFont ) );
                    // DWORD clrColor = pManager->GetDefaultFontColor();
                    ::SetTextColor( gorh, RGB( GetBValue( dwTextColor ), GetGValue( dwTextColor ), GetRValue( dwTextColor ) ) );
                    tm = pManager->GetFontInfo( iFont );
                }
                break;
            case _T( 'y' ): {
                    ++pstrText;
                    cyLine = _tcstol( pstrText, &pstrText, 10 );
                }
                break;
            case _T( 'i' ): { // Image
                    ++pstrText;
                    int iWidth = 0;
                    int iHeight = 0;
                    if ( *pstrText == _T( ' ' ) ) ++pstrText;
                    CStdString simage;

                    while ( *pstrText != _T( '\0' ) && *pstrText != _T( '>' ) && *pstrText != _T( '}' ) ) {
                        LPCTSTR pstrTemp = ::CharNext( pstrText );
                        while ( pstrText < pstrTemp ) {
                            simage += *pstrText++;
                        }
                    }
                    RECT rcBmpPart = {0, 0, 9999, 9999};
                    if ( DrawImageString( gorh, pManager, rcBmpPart, rcBmpPart, simage, NULL, true ) ) {
                        iWidth = rcBmpPart.right - rcBmpPart.left;
                        iHeight = rcBmpPart.bottom - rcBmpPart.top;
                        //需要换行，且图片快读比绘制区域小，且多行显示
                        if ( pt.x + iWidth >= rc.right && iWidth <= rc.right - rc.left && ( uStyle & DT_SINGLELINE ) == 0 ) {
                            if ( bInLink && iLinkIndex < nLinkRects )
                                ( *pLinks )[iLinkIndex].Join( CRgn( ptLinkStart.x, ptLinkStart.y, MIN( pt.x, rc.right ), pt.y + tm.tmHeight ) );
                            pt.x = rc.left;
                            pt.y += cyLine/* - tm.tmDescent*/;
                            if ( pt.y > rc.bottom && bDraw ) break;
                            ptLinkStart = pt;
                        }

                        if ( bDraw ) {
                            RECT rcImage = {pt.x, pt.y, pt.x + iWidth, pt.y + iHeight};
                            DrawImageString( gorh, pManager, rcImage, rcBmpPart, simage );
                        }

                        cyLine = MAX( iHeight, cyLine );
                        pt.x += iWidth;
                        cyMinHeight = pt.y + iHeight;
                        cxMaxWidth = MAX( cxMaxWidth, pt.x );
                    }
                }
                break;
            case _T( 'c' ): { // Color
                    ++pstrText;
                    if ( *pstrText == _T( ' ' ) ) ++pstrText;
                    if ( *pstrText == _T( '#' ) ) ++pstrText;
                    DWORD clrColor = _tcstoul( pstrText, &pstrText, 16 );

                    ::SetTextColor( gorh, RGB( GetBValue( clrColor ), GetGValue( clrColor ), GetRValue( clrColor ) ) );

                    if ( *pstrText == _T( ' ' ) ) {
                        ++pstrText;
                        if ( *pstrText == _T( '#' ) ) ++pstrText;
                        DWORD clrColorLink = _tcstoul( pstrText, &pstrText, 16 );

                        if ( iLinkIndex == iHoverLink )
                            ::SetTextColor( gorh, RGB( GetBValue( clrColorLink ), GetGValue( clrColorLink ), GetRValue( clrColorLink ) ) );
                    }
                }
                break;
            }
            while ( *pstrText != _T( '\0' ) && *pstrText != _T( '>' ) && *pstrText != _T( '}' ) ) pstrText = ::CharNext( pstrText );
            pstrText = ::CharNext( pstrText );
        }
        else if ( ( *pstrText == _T( '<' ) || *pstrText == _T( '{' ) ) && pstrText[1] == _T( '/' ) ) {
            ++pstrText;
            ++pstrText;
            switch ( *pstrText ) {
            case _T( 'a' ):
                ++pstrText;
                if ( bInLink && iLinkIndex < nLinkRects )
                    ( *pLinks )[iLinkIndex++].Join( CRgn( ptLinkStart.x, ptLinkStart.y, MIN( pt.x, rc.right ), pt.y + tm.tmHeight ) );
                ::SetTextColor( gorh, RGB( GetBValue( dwTextColor ), GetGValue( dwTextColor ), GetRValue( dwTextColor ) ) );
                ::SelectObject( gorh, pManager->GetFont( iFont ) );
                tm = pManager->GetFontInfo( iFont );
                bInLink = false;
                break;
            case _T( 'f' ):
            case _T( 'b' ):
                ++pstrText;
                ::SelectObject( gorh, pManager->GetFont( iFont ) );
                tm = pManager->GetFontInfo( iFont );
                break;
            case _T( 'c' ):
                ++pstrText;
                ::SetTextColor( gorh, RGB( GetBValue( dwTextColor ), GetGValue( dwTextColor ), GetRValue( dwTextColor ) ) );
                break;
            }
            while ( *pstrText != _T( '\0' ) && *pstrText != _T( '>' ) && *pstrText != _T( '}' ) ) pstrText = ::CharNext( pstrText );
            pstrText = ::CharNext( pstrText );
        }
        else if ( ( *pstrText == _T( '<' ) && pstrText[2] == _T( '>' ) && ( pstrText[1] == _T( '{' )  || pstrText[1] == _T( '}' ) ) ) ||
                  ( *pstrText == _T( '{' ) && pstrText[2] == _T( '}' ) && ( pstrText[1] == _T( '<' )  || pstrText[1] == _T( '>' ) ) ) ||
                  *pstrText == _T( ' ' ) ) {
            SIZE szSpace = { 0 };
            ::GetTextExtentPoint32( gorh, &pstrText[1], 1, &szSpace );
            if ( pt.x + szSpace.cx >= rc.right && ( uStyle & DT_SINGLELINE ) == 0 ) {
                if ( bInLink && iLinkIndex < nLinkRects )
                    ( *pLinks )[iLinkIndex].Join( CRgn( ptLinkStart.x, ptLinkStart.y, MIN( pt.x, rc.right ), pt.y + tm.tmHeight ) );
                pt.x = rc.left;
                pt.y += cyLine/* - tm.tmDescent*/;
                if ( pt.y > rc.bottom && bDraw ) break;
                ptLinkStart = pt;
                cyLine = tm.tmHeight + tm.tmExternalLeading;
            }

            if ( bDraw ) ::TextOut( gorh, pt.x, pt.y, &pstrText[1], 1 );
            pt.x += szSpace.cx;
            cxMaxWidth = MAX( cxMaxWidth, pt.x );
            if ( *pstrText != _T( ' ' ) )
                {++pstrText; ++pstrText;}
            ++pstrText;
        }
        else {
            POINT ptPos = pt;
            int cchChars = 0;
            int cchSize = 0;
            //int cchLastGoodWord = 0;
            //int cchLastGoodSize = 0;
            LPCTSTR p = pstrText;
            SIZE szText = { 0 };
            // if( *p == _T('<') || *p == _T('{') ) ++p, ++cchChars, ++cchSize;
            while ( *p != _T( '\0' ) && *p != _T( '<' ) && *p != _T( '{' ) && *p != _T( '\n' ) ) {
                // This part makes sure that we're word-wrapping if needed or providing support
                // for DT_END_ELLIPSIS. Unfortunately the GetTextExtentPoint32() call is pretty
                // slow when repeated so often.
                // TODO: Rewrite and use GetTextExtentExPoint() instead!

                LPCTSTR pstrTemp = ::CharNext( p );
                ++cchChars;
                cchSize += pstrTemp - p;

                //猜测后修正
                //因为比较难处理半字符的情况，所以暂时以宽字符作为标准，暂时取消DT_WORDBREAK和DT_END_ELLIPSIS支持
                szText.cx = cchChars * tm.tmMaxCharWidth;
                //int *asWidths=NULL;
                //int cchFit=0;
                if ( pt.x + szText.cx >= rc.right ) {
                    ::GetTextExtentPoint32( gorh, pstrText, cchSize, &szText );
                    //asWidths=new int[cchSize];
                    //::GetTextExtentExPoint(hDC,pstrText,cchSize,rc.right-pt.x,&cchFit,asWidths,&szText);
                }

                if ( pt.x + szText.cx > rc.right ) {
                    if ( pt.x + szText.cx > rc.right && pt.x + szText.cx != rc.left ) {
                        --cchChars;
                        cchSize -= pstrTemp - p;
                    }

                    //                     if( (uStyle & DT_WORDBREAK) != 0 && cchLastGoodWord > 0 ) {
                    //                         cchChars = cchLastGoodWord;
                    //                         cchSize = cchLastGoodSize;
                    //                     }
                    //
                    //                     if( (uStyle & DT_END_ELLIPSIS) != 0 && cchChars > 2 ) {
                    //                         cchChars = cchLastGoodWord;
                    //                         cchSize = cchLastGoodSize;
                    //                     }

                    pt.x = rc.right;
                    cxMaxWidth = MAX( cxMaxWidth, pt.x );
                    break;
                }
                //
                //                 if (!( ( p[0] >= _T('a') && p[0] <= _T('z') ) || ( p[0] >= _T('A') && p[0] <= _T('Z') ) ))
                //                 {
                //                     cchLastGoodWord = cchChars;
                //                     cchLastGoodSize = cchSize;
                //                 }
                //                 if( *p == _T(' ') )
                //                 {
                //                     cchLastGoodWord = cchChars;
                //                     cchLastGoodSize = cchSize;
                //                 }
                p = ::CharNext( p );
            }
            if ( cchChars > 0 ) {
                ::GetTextExtentPoint32( gorh, pstrText, cchSize, &szText );
                if ( bDraw ) {
                    ::TextOut( gorh, ptPos.x, ptPos.y, pstrText, cchSize );
                    //if( pt.x >= rc.right && (uStyle & DT_END_ELLIPSIS) != 0 ) ::TextOut(hDC, rc.right - 10, ptPos.y, _T("..."), 3);
                }
                pt.x += szText.cx;
                cxMaxWidth = MAX( cxMaxWidth, pt.x );
                pstrText += cchSize;
            }
        }
        ASSERT( iLinkIndex <= nLinkRects );
    }

    // Return size of text when requested
    if ( !bDraw ) {
        rc.bottom = MAX( cyMinHeight, ( pt.x == rc.left ) ? pt.y : ( pt.y + cyLine ) );
        rc.right = MIN( rc.right, cxMaxWidth );
    }

    //if ( bDraw )
    //    gorh.SetClip( oldRegion );

    ::SetTextColor( gorh, dOldTextColor );
    ::SetBkMode( gorh, iOldBkMode );
    ::SelectObject( gorh, hOldFont );

    gorh.Setmode( bModesave );
}
