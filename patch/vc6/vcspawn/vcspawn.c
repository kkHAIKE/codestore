//////////////////////////////////////////////////////////////////////////
//     �ļ���vcspawn���򹤳�Դ��
//     ���ߣ�AGanNo2
//     My blog��http://www.cppblog.com/aganno2  http://blog.csdn.net/aganno2 http://aganno2.ys168.com
//    Email��aganno2@163.com
//     ���ڣ�2006-12-09
// �������������ļ������������ȡ�ã�ֻ������ѧϰ�о�֮��;������
//           ������ʹ�ñ��ļ��еĴ���������ĺ���Ų�����
// ��������ɵ��޸���ݴ�������Ӧ�����Ҫ����������������ģ���Щ�������岻�Ǻ���ȷ��
// ����ʱѡ��/MD(���̶߳�̬����)����Ȼ�������⡣
// �������ļ�vcspawn.exe����ԭ�ļ����ɿ���Ч����������޸Ĵ����������Ҫ�ġ�
//////////////////////////////////////////////////////////////////////////


#include <mbstring.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdarg.h>
#include <windows.h>
#include "resource.h"

#pragma comment(linker,"/FILEALIGN:0x200")


//���ý������õĹ�����(�����������������)�Ĵ�С,windows98��û��SetProcessWorkingSetSize�������������Ҫ��̬�õ����ַ
typedef BOOL (__stdcall *SETPROCESSWORKINGSETSIZE)(
  HANDLE hProcess,                // handle to the process of interest
  DWORD dwMinimumWorkingSetSize,  // specifies minimum working set size
  DWORD dwMaximumWorkingSetSize   // specifies maximum working set size
);

LPSTR *app_argv;//����main�Ĳ���

HANDLE hGlobalProcess[2];//����ͬ���ľ��

HMODULE hKernel32 = 0;

//������ַ�����ƣ�����������GetProcessWorkingSetSize�ڳ�����û���õ�
char *FuncName[2] = {"SetProcessWorkingSetSize", "GetProcessWorkingSetSize"};
DWORD FuncAddr[2];

DWORD dword_403050 = 0;
char *default_path;

char flag[2] = ";";//��������path���������ķָ���
char *arr_ext[5] = {"\0", "exe", "com", "bat", "cmd"};//Ҫ�����Ľ����ļ��Ŀ��ܵ���չ��


char *ms_declare = "Microsoft (R) VcSpawn  Version %d.%02d\n"
                   "Copyright (C) Microsoft Corp 1993-1997. All rights reserved.\n\n"
                   "VcSpawn is a utility program required by Visual C++ Development Environment.\n";
char *my_declare = "Author: AGanNo2\n"
                   "Email��AGanNo2@163.com\n"
				   "Date: 2006/12/09\n"
				   "Disclaimer: This program is from reverse engineering,for research only!\n";

void exit_func();
int __stdcall only_begin(LPSTR lpCommandLine);
int __stdcall process_begin(LPSTR lpCommandLine);
void declare();
void my_printf(char *msg, ...);
int SetWorkingSetSize(DWORD dwMinimumWorkingSetSize, DWORD dwMaximumWorkingSetSize);
int get_func_addr();

//execute before main
_atexit(exit_func);

int main(int argc, char **argv)
{
	LPSTR lpCommandLine;
	LPSTR lpModuleName;//��·���Ŀ�ִ���ļ���
	LPSTR lpTemp;
	int ret_cmp;
	DWORD dwTickCount;
	DWORD dwTempTickCount;
	char *tok;

	puts(my_declare);
	fflush(stdout);

	lpCommandLine = GetCommandLine();
	app_argv = *argv;
	SetEnvironmentVariable("_MSDEV_BLD_ENV_", "1");
	if(lpCommandLine[0] == '"')
		lpCommandLine++;
 
	lpModuleName = __p__pgmptr();
	if(!_mbsnbicmp(lpCommandLine, lpModuleName, strlen(lpModuleName)))
	{
		lpTemp = __p__pgmptr();
	}
	else
	{
		if(!_mbsnbicmp(lpCommandLine, app_argv, strlen(app_argv)))
			lpTemp = app_argv;
		else
		{
			while(_ismbcspace(*lpCommandLine))
				lpCommandLine = _mbsinc(lpCommandLine);
			while(*lpCommandLine != '\0' && _ismbcspace(*lpCommandLine) == 0)
				lpCommandLine = _mbsinc(lpCommandLine);
			goto label;
		}
	}

	lpCommandLine+=strlen(lpTemp);
	if(*lpCommandLine == '"')
		lpCommandLine++;


label:	while(_ismbcspace(*lpCommandLine))
			lpCommandLine = _mbsinc(lpCommandLine);
	
	
	ret_cmp = _mbsnbcmp(lpCommandLine, "-t", 2);
	/*���������ԭ��Ļ�������Ū���ģ���ʵ�����벻����ô���ӣ�
	_mbsnbcmp�ķ���ֵ�д���0��С��0������0����������ڴ���0��С��0ʱ�������������
	��ret_cmp�������0�������൱���ж��ַ����Ƿ���ȣ���֪��M$Ϊʲô�����ô���ӣ�*/
	__asm
	{
		mov edi,ret_cmp
		neg edi
		sbb edi,edi
        inc edi
		mov ret_cmp,edi
	}

	if(_mbsnbcmp(lpCommandLine, "-e", 2) != 0)
	{
		if(ret_cmp == 0)
			declare();
	}
	
	lpCommandLine+=2;
	while(_ismbcspace(*lpCommandLine))
		lpCommandLine = _mbsinc(lpCommandLine);
	
	if(ret_cmp != 0)
		return process_begin(lpCommandLine);
	
	hGlobalProcess[0] = strtoul(lpCommandLine, &lpCommandLine,10);
	if(!_ismbcspace(*lpCommandLine))
		declare();
	
	while(_ismbcspace(*lpCommandLine))
		lpCommandLine = _mbsinc(lpCommandLine);

	if(*lpCommandLine == '\0')
		declare();//will exit
	
	if(!_mbsnbcmp(lpCommandLine, "-m", 2))
	{
		dwTickCount = GetTickCount();
		lpCommandLine+=2;
		while(_ismbcspace(*lpCommandLine))
			lpCommandLine = _mbsinc(lpCommandLine);
		
		tok = _mbstok(lpCommandLine, "\n");
		while(tok != NULL)
		{
			while(_ismbcspace(*tok))
				tok = _mbsinc(tok);
			if(!_mbsnbcmp(tok, "~vcecho!", 8))
			{
				tok+=8;
				while(_ismbcspace(*tok))
					tok = _mbsinc(tok);
				puts(tok);
				fflush(stdout);
			}
			else
			{
				if(!_mbsnbcmp(tok, "~vctime!", 8))
				{
					//��Ӧ�Ļ����븽�ں���
					__asm
					{
						call GetTickCount
							mov eax,ecx
							sub ecx,dwTickCount
							mov dwTickCount,eax
							mov dwTempTickCount,ecx
					}
					printf("Spawn Time %lu:%2.2lu.%lu\n",
						dwTempTickCount/60000, dwTempTickCount%60000/1000, 
						dwTempTickCount%1000/100);
					fflush(stdout);
				}
				else
				{
					if(!_mbsnbcmp(tok, "~vcsleep!", 9))
					{
						Sleep(3720);
					}
					else
					{
						if(0 !=only_begin(tok))
							break;
					}
				}
			}//else
			tok = _mbstok(NULL, "\n");
		}//while
	}
	else
		only_begin(lpCommandLine);
	CloseHandle(hGlobalProcess[0]);

	return 0;
}

int __stdcall only_begin(LPSTR lpCommandLine)
{
	int var_4;
	char var_10[12];
	int ExitCode;
	char path_buffer[_MAX_PATH];
	char DeviceBuf[4];
	PROCESS_INFORMATION pi = {0};
	int var_138;
	char lpTempPath[_MAX_PATH] = {0};
	char fname[_MAX_FNAME] = {0};
	char ext[_MAX_EXT] = {0};
	char dir[_MAX_DIR] = {0};
	char drive[_MAX_DRIVE] = {0};
    char *ApplicationName;
    STARTUPINFO StartupInfo = {0};
	LPTSTR lpFilePart;
	char *lpPath;
	char *envPATH;
	char workpath[_MAX_PATH];
	int extIndex = 0;
	char Extension[_MAX_EXT];
	int var_7a4;
	HANDLE hDevice;
	int var_7ac;
	int var_7b0;
	int var_7b4;
	char *var_7c0;

	int ret;
	LPSTR lpTemp;
	
	StartupInfo.cb = sizeof(StartupInfo);
	lpTemp = lpCommandLine;

	if(*lpCommandLine != '\0')
	{
		while(_ismbcspace(*lpTemp) == 0)
			lpTemp = _mbsinc(lpTemp);
	}
	if((lpTemp - lpCommandLine) > 259)
		declare();
    _mbsnbcpy(path_buffer, lpCommandLine, (lpTemp - lpCommandLine));

	
	path_buffer[lpTemp - lpCommandLine] = '\0';
	
	_splitpath(path_buffer, drive, dir, fname, ext);
	//lpTempPath = NULL;

	if(*drive != '\0')
		strcat(lpTempPath, drive);
	if(*dir != '\0')
		strcat(lpTempPath, dir);
	else if(*lpTempPath != '\0')
		strcat(lpTempPath, ".\\");

	extIndex = 0;
	_getcwd(workpath, _MAX_PATH);
	envPATH = getenv("PATH");
	if(envPATH == NULL)
		envPATH = default_path;

	if(*lpTempPath != '\0')
		lpPath = _strdup(lpTempPath);
	else	
	{
		lpPath = malloc(strlen(envPATH) + strlen(workpath) + 2);
		strcpy(lpPath, workpath);
		strcat(lpPath, flag);
		strcat(lpPath, envPATH);
	}

	if(*ext == '\0')
		extIndex = 1;
	
	if(extIndex <=5)
	{
		var_7c0 = arr_ext[extIndex];

		while(&var_7c0 < arr_ext + 5)
		{
			strcpy(Extension, ext);
			strcat(Extension, var_7c0);
			
			if(0 == SearchPath(lpPath, fname, Extension, _MAX_PATH, path_buffer, &lpFilePart))
			{
				var_7c0+=4;
				continue;
			}
			break;
		}
		ApplicationName = path_buffer;
	}

	free(lpPath);
	SetErrorMode(0);
	
	puts(lpCommandLine);//����ѽ�Ҫִ�еĽ���(���������)����ϸ��Ϣ�ض����������
	fflush(stdout);
	if(0 != CreateProcess(ApplicationName, lpCommandLine, NULL, NULL, TRUE,
		CREATE_NEW_PROCESS_GROUP, NULL, NULL, &StartupInfo, &pi))
	{
		
		hGlobalProcess[1] = pi.hProcess;
		SetWorkingSetSize(0xffffffff, 0xffffffff);

		ret = WaitForMultipleObjects(2, hGlobalProcess, FALSE, INFINITE);
		
		if(ret > 2)
			ExitCode = -1;
		else if(ret == 0)
		{
			if(-1 == (hDevice =CreateFile("\\\\.\\vwin32", GENERIC_READ, 0, NULL, OPEN_ALWAYS,
				FILE_ATTRIBUTE_NORMAL, 0)))
			{

			}
			signal(2, 1);
			var_7a4 = DeviceIoControl(hDevice, 5, DeviceBuf, 4, NULL, 0, NULL, NULL);
			signal(2, 0);
            
			while(var_7b0 < 1)
			{
				var_7b4 = GenerateConsoleCtrlEvent(CTRL_BREAK_EVENT, (DWORD)DeviceBuf);
				if(0 == var_7b4)
					var_7ac = 1;
				else
				{
					WaitForSingleObject(pi.hProcess, 47040);
					if(var_7b4 != 0x102)
						var_7ac = 1;
				}
				if(var_7ac != 0)
					break;
				var_7b0++;
			}
			TerminateProcess(pi.hProcess, -1);
		}
		else
		{
			if(0 == GetExitCodeProcess(pi.hProcess, &ExitCode))
				ExitCode = -1;
		}
		var_4 = ExitCode;
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		return ExitCode;
	}
	return -1;
}
int SetWorkingSetSize(DWORD dwMinimumWorkingSetSize, DWORD dwMaximumWorkingSetSize)
{
	
	if(dword_403050 == 0)
		if(get_func_addr() == 0)
			return 0;	
	if(FuncAddr[0] != 0)
			((SETPROCESSWORKINGSETSIZE)FuncAddr[0])(GetCurrentProcess(), dwMinimumWorkingSetSize,
			dwMaximumWorkingSetSize);
	return 1;
}
int get_func_addr()
{
	int i = 0;
	hKernel32 = LoadLibrary("kernel32.dll");
	if(hKernel32 == NULL)
		return 0;
	
	while(i < 2)
	{
		FuncAddr[i] = GetProcAddress(hKernel32, FuncName[i]);
		i++;
	}
	return 1;
}

//�����ǵ�����IDE�Ļ����°�"execute"ʱҪִ�еĲ���
int __stdcall process_begin(LPSTR lpCommandLine)
{
	STARTUPINFO StartupInfo = {0};
	int ExitCode = 0;
	int ret_cmp;
	ret_cmp = _mbsnbcmp(lpCommandLine, "-p", 2);
	/*���������ԭ��ķ���������Ū���ģ���ʵ�����벻����ô���ӣ�
	_mbsnbcmp�ķ���ֵ�д���0��С��0������0����������ڴ���0��С��0ʱ�������������
	��ret_cmp�������0�������൱���ж��ַ����Ƿ���ȣ���֪��M$Ϊʲô�����ô���ӣ�*/
	__asm
	{
		mov edi,ret_cmp
		neg edi
		sbb edi,edi
		inc edi
		mov ret_cmp,edi
	}
	StartupInfo.cb = sizeof(StartupInfo);
	if(ret_cmp != 0)
	{
		lpCommandLine+=2;
		while(_ismbcspace(*lpCommandLine))
			lpCommandLine = _mbsinc(lpCommandLine);
	}

	SetConsoleTitle(lpCommandLine);
	SetErrorMode(0);
	
	//���������Ҫִ�е�����
	puts(lpCommandLine);
	fflush(stdout);

	if(0 != CreateProcess(NULL, lpCommandLine, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS,
		NULL, NULL, &StartupInfo, &hGlobalProcess[0]))
	{
		if(0 != ret_cmp)
		{
			WaitForSingleObject(hGlobalProcess[0], INFINITE);
			GetExitCodeProcess(hGlobalProcess[0], &ExitCode);
			printf("Press any key to continue");
			_getch();
		}
		CloseHandle(hGlobalProcess[0]);
		return ExitCode;
	}
	return -1;
}

void declare()
{
	my_printf(ms_declare, 6, 0);
	fflush(stdout);
	exit(1);
}

void my_printf(char *msg, ...)
{
	va_list vl;
	va_start(vl, msg);
	vprintf(msg, vl);
	va_end(vl);
}

//�����˳�ʱҪִ�е��������
void exit_func()
{
	if(hKernel32 != 0)
	{
		FreeLibrary(hKernel32);
		hKernel32 = 0;
	}
}
