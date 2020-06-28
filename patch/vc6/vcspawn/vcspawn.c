//////////////////////////////////////////////////////////////////////////
//     文件：vcspawn逆向工程源码
//     作者：AGanNo2
//     My blog：http://www.cppblog.com/aganno2  http://blog.csdn.net/aganno2 http://aganno2.ys168.com
//    Email：aganno2@163.com
//     日期：2006-12-09
// 免责声明：此文件是由逆向分析取得，只可用于学习研究之用途。本人
//           对他人使用本文件中的代码所引起的后果概不负责。
// 你可以自由的修改这份代码以适应你的需要，由于是逆向得来的，有些变量意义不是很明确。
// 编译时选者/MD(多线程动态链接)，不然会有问题。
// 编译后的文件vcspawn.exe覆盖原文件即可看到效果，你可以修改代码输出你想要的。
//////////////////////////////////////////////////////////////////////////


#include <mbstring.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdarg.h>
#include <windows.h>
#include "resource.h"

#pragma comment(linker,"/FILEALIGN:0x200")


//设置进程所用的工作集(类似于所用物理类村)的大小,windows98下没有SetProcessWorkingSetSize这个函数，所以要动态得到其地址
typedef BOOL (__stdcall *SETPROCESSWORKINGSETSIZE)(
  HANDLE hProcess,                // handle to the process of interest
  DWORD dwMinimumWorkingSetSize,  // specifies minimum working set size
  DWORD dwMaximumWorkingSetSize   // specifies maximum working set size
);

LPSTR *app_argv;//传入main的参数

HANDLE hGlobalProcess[2];//用于同步的句柄

HMODULE hKernel32 = 0;

//函数地址和名称，不过看起来GetProcessWorkingSetSize在程序中没有用到
char *FuncName[2] = {"SetProcessWorkingSetSize", "GetProcessWorkingSetSize"};
DWORD FuncAddr[2];

DWORD dword_403050 = 0;
char *default_path;

char flag[2] = ";";//连续几个path环境变量的分隔符
char *arr_ext[5] = {"\0", "exe", "com", "bat", "cmd"};//要创建的进程文件的可能的扩展名


char *ms_declare = "Microsoft (R) VcSpawn  Version %d.%02d\n"
                   "Copyright (C) Microsoft Corp 1993-1997. All rights reserved.\n\n"
                   "VcSpawn is a utility program required by Visual C++ Development Environment.\n";
char *my_declare = "Author: AGanNo2\n"
                   "Email：AGanNo2@163.com\n"
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
	LPSTR lpModuleName;//带路径的可执行文件名
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
	/*下面这段是原版的汇编代码中弄来的，其实就我想不用这么复杂，
	_mbsnbcmp的返回值有大于0、小于0、等于0三种情况，在大于0、小于0时经过下面的运算
	后ret_cmp都会等于0，就是相当于判断字符串是否相等，不知道M$为什么搞得这么复杂？*/
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
					//对应的汇编代码附在后面
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
	
	puts(lpCommandLine);//这儿把将要执行的进程(编译或链接)的详细信息重定向到输出窗口
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

//这里是当你在IDE的环境下按"execute"时要执行的部分
int __stdcall process_begin(LPSTR lpCommandLine)
{
	STARTUPINFO StartupInfo = {0};
	int ExitCode = 0;
	int ret_cmp;
	ret_cmp = _mbsnbcmp(lpCommandLine, "-p", 2);
	/*下面这段是原版的反汇编代码中弄来的，其实就我想不用这么复杂，
	_mbsnbcmp的返回值有大于0、小于0、等于0三种情况，在大于0、小于0时经过下面的运算
	后ret_cmp都会等于0，就是相当于判断字符串是否相等，不知道M$为什么搞得这么复杂？*/
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
	
	//下面输出将要执行的命令
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

//程序退出时要执行的清理操作
void exit_func()
{
	if(hKernel32 != 0)
	{
		FreeLibrary(hKernel32);
		hKernel32 = 0;
	}
}
