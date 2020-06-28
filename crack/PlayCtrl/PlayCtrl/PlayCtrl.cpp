// PlayCtrl.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <thread/CriticalSection.h>

int g_lJpegQuality=80;
int g_nHighTimerNum=0;

CCriticalSection cs;

int parse_file_header(HIKVISION_MEDIA_FILE_HEADER* a1,MULTIMEDIA_INFO *a2)
{
	DWORD v2; // eax@7

	a2->part2 = 1;
	switch ( a1->magic )
	{
	case 0x484B4834: /*HKH4*/
		a2->type = 1;
		break;
	case 0x48534D32: /*HSM2*/
		a2->type = 2;
		break;
	case 0x48534D34: /*HSM4*/
		a2->type = 3;
		break;
	}

	v2 = a1->part11;

	if ( v2 == 0x7111 )
		a2->part5 = 0x7111;
	else if ( v2 == 0x7221 || (v2>=0x1011 && v2<=0x1013))
		a2->part5 = 0x7221;
	else if ( v2 == 0x7110 )
		a2->part5 = 0x7110;
	else if ( v2 == 0x1014 )
		a2->part5 = 0x2000u;
	
	a2->part6 = a1->part5;
	a2->part7 = a1->part7;
	a2->part8 = a1->part9;
	return 0;
}
int parse_media_info(HIKVISION_MEDIA_INFO* a1,MULTIMEDIA_INFO* a2)
{
	a2->part2 = a1->part2;
	a2->type = a1->type;
	a2->part5 = a1->part5;
	a2->part6 = a1->part6;
	a2->part7 = a1->part7;
	a2->part8 = a1->part8;
	a2->part9 = a1->part9;
	return 0;
}
DWORD search_start_code(BYTE *a1, DWORD a2)
{
	DWORD result=0; // eax@2

	if ( a2 < 4 || a2 == 3 )
	{
LABEL_5:
		result = -1;
	}
	else
	{
		while ( *(_DWORD *)&a1[result] != 1 )
		{
			++result;
			if ( result >= a2 - 3 )
				goto LABEL_5;
		}
	}
	return result;
}

int parse_stream(BYTE *a1, DWORD a2, MULTIMEDIA_INFO *a3)
{
	
}

int ParseStreamAsHIKSystem(BYTE* buf,DWORD a2,MULTIMEDIA_INFO *a3)
{
	int v4; // eax@3

	if ( a2 < 40 )
		return 1;
	
	DWORD v4=*(DWORD *)buf;

	if(v4==0x48534D32 /*HSM2*/ || v4==0x484B4834 /*HKH4*/ ||v4==0x48534D34 /*HSM4*/|| v4==0x484B4D34 /*HKM4*/)
		return parse_file_header((HIKVISION_MEDIA_FILE_HEADER *)buf, a3);
	if(v4==0x484B4D49 /*HKMI*/)
		return parse_media_info((HIKVISION_MEDIA_INFO *)buf, a3);
	return parse_stream(buf, a2,a3);
}

int ParseFileAsHIKSystem(HANDLE hFile, struct MULTIMEDIA_INFO *a3)
{
	DWORD v2; // ecx@0
	BYTE *v3; // esi@1
	signed int result; // eax@2
	DWORD a2; // [sp+0h] [bp-4h]@1

	v3 = new BYTE[0x10000];
	if ( v3 )
	{
		a2 = 0;
		if ( ReadFile(hFile, v3, 0x10000, &a2, 0) && a2 >= 0x800 )
		{
			if ( ParseStreamAsHIKSystem(v3, a2, a3) )
			{
				delete[] v3;
				result = 1;
			}
			else
			{
				delete[] v3;
				result = 0;
			}
		}
		else
		{
			delete[] v3;
			result = -2147483646;
		}
	}
	else
	{
		result = -2147483645;
	}
	return result;
}
int File_Inspect(LPCSTR lpFileName,MULTIMEDIA_INFO* a2)
{
	HANDLE v2; // eax@3
	int result; // eax@4

	if ( lpFileName && a2 )
	{
		memset(a2, 0, sizeof(MULTIMEDIA_INFO));
		v2 = CreateFileA(lpFileName, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	
		if ( v2 == INVALID_HANDLE_VALUE )
		{
			result = -2147483646;
		}
		else
		{
			SetFilePointer(v2, 0, 0, 0);
			if ( ParseFileAsHIKSystem( v2, a2) )
			{
				SetFilePointer(v2, 0, 0, 0);
				if ( ParseFileAsMPEG2System( v2, a2) )
				{
					SetFilePointer(v2, 0, 0, 0);
					if ( ParseFileAsMPEG4(v2, a2) )
					{
						CloseHandle(v2);
						result = 1;
					}
					else
					{
						CloseHandle(v2);
						result = 0;
					}
				}
				else
				{
					CloseHandle(v2);
					result = 0;
				}
			}
			else
			{
				CloseHandle(v2);
				result = 0;
			}
		}
	}
	else
	{
		result = -2147483647;
	}
	return result;
}

void _DebugInfo(char *pstrFormat, ...)
{
#ifdef _DEBUG
	char szBuffer[256] = { 0 };
	va_list args;
	va_start(args, pstrFormat);
	wvnsprintfA(szBuffer, 254, pstrFormat, args);
	strcat(szBuffer,256, "\n");
	va_end(args);
	OutputDebugStringA(szBuffer);
#endif
}

void _LOG_RECORD(char *str)
{
	//加上时间
#ifdef _DEBUG
	cs.lock();

	FILE* fplog=fopen("PlayCtrl.log","at");
	fprintf(fplog,str);
	fclose(fplog);

	cs.unlock();
#endif
}