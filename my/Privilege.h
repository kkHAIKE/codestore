//#include <Debug.h>
#pragma once

inline BOOL Privilege(TCHAR* pszPrivilege, BOOL bEnable)
{
	HANDLE           hToken;
	TOKEN_PRIVILEGES tp;
	BOOL             status;
	DWORD            error;

	// open process token
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return FALSE;
		//TRACE(_T("OpenProcessToken"));

	// get the luid
	if (!LookupPrivilegeValue(NULL, pszPrivilege, &tp.Privileges[0].Luid))
		return FALSE;
		//TRACE(_T("LookupPrivilegeValue"));

	tp.PrivilegeCount = 1;

	// enable or disable privilege
	if (bEnable)
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	else
		tp.Privileges[0].Attributes = 0;

	// enable or disable privilege
	status = AdjustTokenPrivileges(hToken, FALSE, &tp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

	// It is possible for AdjustTokenPrivileges to return TRUE and still not succeed.  
	// So always check for the last error value.
	error = GetLastError();
	CloseHandle(hToken);
	if (!status || (error != ERROR_SUCCESS))
		return FALSE;
		//TRACE(_T("AdjustTokenPrivileges"));

	return TRUE;
	// close the handle
	//if (!CloseHandle(hToken))
		//TRACE(_T("CloseHandle"));
}
