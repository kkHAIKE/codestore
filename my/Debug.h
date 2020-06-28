#pragma once
#include <crtdbg.h>
#include <Shlwapi.h>
#pragma comment(lib,"Shlwapi.lib")

inline void __cdecl __Trace(LPCTSTR pstrFormat, ...)
{
#ifdef _DEBUG
	TCHAR szBuffer[256] = { 0 };
	va_list args;
	va_start(args, pstrFormat);
	::wvnsprintf(szBuffer, 254, pstrFormat, args);
	_tcscat_s(szBuffer,256, _T("\n"));
	va_end(args);
	::OutputDebugString(szBuffer);
#endif
}

#ifndef TRACE
#ifdef _DEBUG
#define TRACE __Trace
#else
#define TRACE
#endif
#endif

#ifndef ASSERT
#define ASSERT(x)  _ASSERTE(x)
#endif

#ifndef VERIFY
#ifdef _DEBUG
#define VERIFY(x) _ASSERTE(x)
#else
#define VERIFY(x) ((void)(x))
#endif
#endif
