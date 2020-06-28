// linkfix.cpp : Defines the entry point for the console application.
//

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

void utf8_ascii(LPCSTR src,char *&to)
{
	int szWC=MultiByteToWideChar(CP_UTF8,0,src,-1,NULL,NULL);
	WCHAR *wc=new WCHAR[szWC];
	MultiByteToWideChar(CP_UTF8,0,src,-1,wc,szWC);

	int szAC=WideCharToMultiByte(CP_ACP,0,wc,-1,NULL,NULL,0,0);
	to=new char[szAC];
	WideCharToMultiByte(CP_ACP,0,wc,-1,to,szAC,0,0);
}

void run(TCHAR *para)
{
	STARTUPINFO si={0};
	PROCESS_INFORMATION pi={0};
	si.cb=sizeof(STARTUPINFO);

	TCHAR line[256]={_T("LINKfix.EXE")};
	_tcscat(line,para);
	//_stprintf(line,_T("linkfix.exe %s"),para);
	if(CreateProcess(NULL,line,NULL,NULL,FALSE,NULL,NULL,NULL,&si,&pi)==0)
	{
		printf("link:error %x\n",GetLastError());
		return ;
	}
	WaitForSingleObject(pi.hProcess,INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}

int _tmain(int argc, _TCHAR* argv[])
{
	if(argc>1)
	{
		TCHAR *p=GetCommandLine();
		_tprintf(_T("link:%s\n"),p);

		for(int i=1;i<argc;++i)
		{
			if(argv[i][0]==_T('@'))
			{
				HANDLE fp=CreateFile(argv[i]+1,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
				DWORD size=GetFileSize(fp,NULL),t;
				char *data=new char[size+1];
				ReadFile(fp,data,size,&t,NULL);
				data[size]=0;
				CloseHandle(fp);

				if(*(WORD*)data==0xbbef)
				{
					fp=CreateFile(argv[i]+1,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
					char* newdata=NULL;
					utf8_ascii(data+3,newdata);
					WriteFile(fp,newdata,strlen(newdata),&t,NULL);
					CloseHandle(fp);
					delete[] newdata;

				}

				delete[] data;

				//CopyFile(argv[i]+1,_T("tt.txt"),FALSE);
			}
		}
		run(p+_tcslen(argv[0])+(p[0]==_T('\"')?2:0));
	}
	else
		run(_T(""));

	return 0;
}

