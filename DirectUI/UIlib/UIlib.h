#pragma once

#ifdef UILIB_EXPORTS
#define UILIB_API __declspec(dllexport)
#else
#define UILIB_API __declspec(dllimport)
#endif

#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <commctrl.h>
#include <olectl.h>
#include <Ole2.h>

#include <GdiPlus.h>
#pragma comment(lib,"gdiplus.lib")
using namespace Gdiplus;

#include "MarkupMSXML.h"

#include "UIBase.h"
#include "UIManager.h"
#include "UIRender.h"
#include "UIDlgBuilder.h"
#include "UIComonControls.h"
#include "UIContainer.h"
#include "UIExtraControls.h"
#include "UIDefaultSkin.h"
#include "UIEasyStart.h"
//#include "UIList.h"