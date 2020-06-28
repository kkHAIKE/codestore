// UITest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "UIlib.h"
#include "resource.h"

#pragma comment(lib,"UIlib.lib")

class CTestWnd:public CWindowWndImpl
{
public:
	LPCTSTR GetWindowClassName() const{return _T("TestWndClass");}
	LPCTSTR GetXmlName() const{return _T("test.xml");}

	CTestWnd():m_testMenu(NULL)
	{
		//m_hMenu=::LoadMenu(CPaintManagerUI::GetResourceInstance(),MAKEINTRESOURCE(IDR_MENU1));
		//ASSERT(m_hMenu);
	}
	~CTestWnd()
	{
		//::DestroyMenu(m_hMenu);
	}
	void Init()
	{
		SetIcon(IDI_ICON1);
		CenterWindow();
		//m_testMenu->SetMenu(::GetSubMenu(m_hMenu,0));
	}

protected:
	CMenuButtonUI *m_testMenu;
// 	HMENU m_hMenu;
// 
// 	LRESULT OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
// 	{
// 		if((int)wParam==ID_40001)
// 			::MessageBox(m_hWnd,_T("²âÊÔ²Ëµ¥1"),NULL,MB_OK);
// 		bHandled=FALSE;
// 		return 0;
// 	}

// 	BEGIN_CONTROLS_BIND()
// 		CONTROL_BIND(m_testMenu,CMenuButtonUI,_T("testMenu"))
// 	END_CONTROLS_BIND()
// 
// 	BEGIN_MSG_MAP()
// 		MESSAGE_HANDLER(WM_COMMAND,OnCommand)
// 	END_MSG_MAP()
};

int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
	ULONG_PTR gditoken;
	GdiplusStartup(gditoken);
	::CoInitialize(NULL);

	CPaintManagerUI::SetResourceInstance(hInstance);

	CTestWnd *win=new CTestWnd();
	win->Create(NULL,_T("test"),UI_WNDSTYLE_FRAME,0);

	CPaintManagerUI::MessageLoop();

	::CoUninitialize();
	::GdiplusShutdown(gditoken);
}
