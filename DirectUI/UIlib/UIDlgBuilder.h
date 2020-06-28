#ifndef __UIDLGBUILDER_H__
#define __UIDLGBUILDER_H__

#pragma once

class UILIB_API CDialogBuilder
{
public:
    CElementUI* Create( STRINGorID xml, STRINGorID type = ( UINT ) 0, CPaintManagerUI* pManager = NULL );

    CStdString GetLastError() const;

private:
    CElementUI* _Parse( CElementUI* pParent = NULL, CPaintManagerUI* pManager = NULL );

    CMarkupMSXML m_xml;
};

#endif // __UIDLGBUILDER_H__