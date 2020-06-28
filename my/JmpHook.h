// HookApi_JMP.h:使用JMP法写的一个HOOK API的类.
//
#pragma once

class CJmpHook  
{

public:
	CJmpHook()
	{
		m_NewFunc[0]=0xe9;
		m_hProc=GetCurrentProcess();
	}
	~CJmpHook()
	{
		CloseHandle(m_hProc);
	}
	template<typename _T1,typename _T2>
	void HookCALL(_T1 lpOldFunc, _T2 lpNewFunc)
	{
		typedef union
		{
			_T1 a;
			BYTE* b;
		}T1Helper;
		
		typedef union
		{
			_T2 a;
			BYTE* b;
		}T2Helper;
		
		T1Helper t1;T2Helper t2;
		t1.b=NULL;t2.b=NULL;
		t1.a=lpOldFunc;t2.a=lpNewFunc;

		m_lpHookFunc=t1.b;
		CopyMemory(m_OldFunc,m_lpHookFunc,5);
     
		*reinterpret_cast<DWORD*>(m_NewFunc+1)=reinterpret_cast<DWORD>(t2.b)-reinterpret_cast<DWORD>(m_lpHookFunc)-5; 
	}
	void HookAPI(LPCTSTR ModuleName, LPCSTR ApiName, FARPROC lpNewFunc)
	{
		HookCALL(GetProcAddress(GetModuleHandle(ModuleName),ApiName),lpNewFunc);
		// 复制m_lpHookFunc前5个字节代码到m_OldFunc.
	}
	void SetHookOn()
	{
		//CopyMemory(m_lpHookFunc,m_NewFunc,5);
 		DWORD dwOldFlag; 
 		WriteProcessMemory(m_hProc, m_lpHookFunc, 
 			m_NewFunc, 5, &dwOldFlag);
	}
	void SetHookOff()
	{
		//CopyMemory(m_lpHookFunc,m_OldFunc,5);
 		DWORD dwOldFlag; 
 		WriteProcessMemory(m_hProc, m_lpHookFunc, 
 			m_OldFunc, 5, &dwOldFlag);
	}
	

protected: 

	HANDLE m_hProc; 
	BYTE m_OldFunc[8]; 
	BYTE m_NewFunc[8]; 
	BYTE* m_lpHookFunc; 
};

