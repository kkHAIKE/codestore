
#include "StdAfx.h"
#include "UIDlgBuilder.h"


CElementUI* CDialogBuilder::Create( STRINGorID xml, STRINGorID type, CPaintManagerUI* pManager )
{
    if ( type == NULL ) {
        if ( _tcschr( xml, _T( '<' ) ) == NULL ) {
            m_xml.Load( xml );
        }
        else {
            m_xml.SetDoc( xml );
        }
    }
    else {
        HRSRC hResource = ::FindResource( CPaintManagerUI::GetResourceInstance(), xml, type );
        if ( hResource == NULL ) return NULL;
        HGLOBAL hGlobal = ::LoadResource( CPaintManagerUI::GetResourceInstance(), hResource );
        if ( hGlobal != NULL ) {
            DWORD dwSize = ::SizeofResource( CPaintManagerUI::GetResourceInstance(), hResource );
            if ( dwSize != 0 ) {
                CStdString xmldoc;
                BYTE* pXmlData = reinterpret_cast<BYTE*>( ::LockResource( hGlobal ) );
                if ( pXmlData[0] == 0xef && pXmlData[0] == 0xee && pXmlData[0] == 0xbf ) {
                    xmldoc.ConvUTF8( reinterpret_cast<LPCSTR>( pXmlData + 3 ), dwSize - 3 );
                }
                else if ( pXmlData[0] == 0xff && pXmlData[0] == 0xfe ) {
                    xmldoc.Assign( reinterpret_cast<LPCWSTR>( pXmlData + 2 ), ( dwSize - 2 ) / 2 );
                }
                else {
                    xmldoc = CStdString( reinterpret_cast<LPCSTR>( pXmlData ), dwSize );
                }
                m_xml.SetDoc( xmldoc );
            }
            ::FreeResource( hGlobal );
        }
    }

    if ( pManager ) {
        if ( m_xml.FindElem( _T( "Window" ) ) ) {
            if ( pManager->GetPaintWindow() ) {
                CStdString strValue;
                if ( strValue = m_xml.GetAttrib( _T( "size" ) ), !strValue.IsEmpty() ) {
                    SIZE cXY = SizeFromString( strValue );
                    pManager->SetInitSize( cXY.cx, cXY.cy );
                }
                if ( strValue = m_xml.GetAttrib( _T( "sizebox" ) ), !strValue.IsEmpty() ) {
                    RECT rcSizeBox = RectFromString( strValue );
                    pManager->SetSizeBox( rcSizeBox );
                }
                if ( strValue = m_xml.GetAttrib( _T( "caption" ) ), !strValue.IsEmpty() ) {
                    RECT rcCaption = RectFromString( strValue );
                    pManager->SetCaptionRect( rcCaption );
                }
                if ( strValue = m_xml.GetAttrib( _T( "roundcorner" ) ), !strValue.IsEmpty() ) {
                    pManager->SetRoundCorner( RectFromString( strValue ) );
                }
                if ( strValue = m_xml.GetAttrib( _T( "mininfo" ) ), !strValue.IsEmpty() ) {
                    SIZE mininfo = SizeFromString( strValue );
                    pManager->SetMinMaxInfo( mininfo.cx, mininfo.cy );
                }
                if ( strValue = m_xml.GetAttrib( _T( "showdirty" ) ), !strValue.IsEmpty() ) {
                    pManager->SetShowUpdateRect( strValue == _T( "true" ) );
                }
            }
            m_xml.IntoElem();
            while ( m_xml.FindElem() ) {
                CStdString strClass = m_xml.GetTagName();
                if ( strClass == _T( "Image" ) ) {
                    CStdString imageName = m_xml.GetAttrib( _T( "name" ) );
                    CStdString imageResType = m_xml.GetAttrib( _T( "restype" ) );
                    pManager->GetImageEx( imageName, imageResType );
                }
                else if ( strClass == _T( "Font" ) ) {
                    CStdString fontName = m_xml.GetAttrib( _T( "name" ) );
                    int size = 12;
                    bool bold = false;
                    bool underline = false;
                    bool italic = false;
                    bool defaultfont = false;
                    bool defaultboldfont = false;
                    bool defaultlinkfont = false;

                    CStdString szSize;
                    if ( szSize = m_xml.GetAttrib( _T( "size" ) ), !szSize.IsEmpty() )
                        size = _tcstol( szSize, NULL, 10 );
                    if ( m_xml.GetAttrib( _T( "bold" ) ) == _T( "true" ) )
                        bold = true;
                    if ( m_xml.GetAttrib( _T( "underline" ) ) == _T( "true" ) )
                        underline = true;
                    if ( m_xml.GetAttrib( _T( "italic" ) ) == _T( "true" ) )
                        italic = true;
                    if ( m_xml.GetAttrib( _T( "default" ) ) == _T( "true" ) )
                        defaultfont = true;
                    if ( m_xml.GetAttrib( _T( "defaultbold" ) ) == _T( "true" ) )
                        defaultboldfont = true;
                    if ( m_xml.GetAttrib( _T( "defaultlink" ) ) == _T( "true" ) )
                        defaultlinkfont = true;
                    HFONT hFont = pManager->AddFont( fontName, size, bold, underline, italic );
                    if ( hFont != NULL ) {
                        if ( defaultfont ) pManager->SetDefaultFont( hFont );
                        if ( defaultboldfont ) pManager->SetDefaultBoldFont( hFont );
                        if ( defaultlinkfont ) pManager->SetDefaultLinkFont( hFont );
                    }
                }
                else if ( strClass == _T( "Default" ) ) {
                    CStdString controlName = m_xml.GetAttrib( _T( "name" ) );
                    CStdString controlValue = m_xml.GetAttrib( _T( "value" ) );

                    pManager->AddDefaultAttributeList( controlName, controlValue );
                }
            }
            m_xml.OutOfElem();
            m_xml.ResetChildPos();
            m_xml.IntoElem();
        }
    }
    return _Parse( NULL, pManager );
}

CStdString CDialogBuilder::GetLastError() const
{
    return m_xml.GetError();
}

CElementUI* CDialogBuilder::_Parse( CElementUI* pParent, CPaintManagerUI* pManager )
{
    CElementUI* pReturn = NULL;

    while ( m_xml.FindElem() ) {
        CStdString strClass = m_xml.GetTagName();
        if ( strClass == _T( "Image" ) || strClass == _T( "Font" ) || strClass == _T( "Default" ) )
            continue;

        CElementUI* pControl = static_cast<CElementUI*>( CRuntimeClass::CreateObjectByName( strClass ) );
        ASSERT( pControl );
        if ( pControl == NULL ) continue;

        // Add children
        if ( m_xml.IntoElem() ) {
            _Parse( pControl, pManager );
            m_xml.OutOfElem();
        }

        // Attach to parent
        // 因为某些属性和父窗口相关，比如selected，必须先Add到父窗口
        if ( pParent != NULL ) {

            IContainerUI* pContainer = static_cast<IContainerUI*>( pParent->GetInterface( _T( "IContainer" ) ) );
            if ( pContainer == NULL ) {
                CContentControlUI* pContentControl = static_cast<CContentControlUI*>( pParent->GetInterface( _T( "ContentControl" ) ) );
                ASSERT( pContentControl );
                pContentControl->SetContent( pControl );
            }
            else if ( !pContainer->Add( pControl ) ) {
                delete pControl;
                continue;
            }
        }

        // Init default attributes
        if ( pManager ) {
            pControl->SetManager( pManager, NULL, false );
            LPCTSTR pDefaultAttributes = pManager->GetDefaultAttributeList( strClass );
            if ( pDefaultAttributes ) {
                pControl->ApplyAttributeList( pDefaultAttributes );
            }
            CStdString sShareName = m_xml.GetAttrib( _T( "sharename" ) );
            if ( !sShareName.IsEmpty() ) {
                pDefaultAttributes = pManager->GetDefaultAttributeList( sShareName );
                if ( pDefaultAttributes ) {
                    pControl->ApplyAttributeList( pDefaultAttributes );
                }
            }
        }

        CStdString sItem;
        CStdString sValue;
        int it = 0;

        while ( sItem = m_xml.GetAttribName( it++ ), !sItem.IsEmpty() ) {
            sValue = m_xml.GetAttrib( sItem );
            pControl->SetAttribute( sItem, sValue );
        }

        if ( pManager ) pControl->SetManager( NULL, NULL, false );
        // Return first item
        if ( pReturn == NULL ) pReturn = pControl;
    }

    return pReturn;
}

