// rc.cpp : Defines the entry point for the console application.
//
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>

int __stdcall sub_10010F0(int a1, int a2, char *Format)
{
  char *v3; // eax@1
  int v4; // edi@1
  char *v5; // esi@1
  char v6; // dl@2
  char *v7; // ecx@2
  char v8; // al@9
  int v9; // edx@9
  char *v10; // edi@9
  char *v11; // eax@13
  char *v12; // ecx@14
  char *v14; // [sp-4h] [bp-10h]@19

  v5 = Format;
  v4 = strlen(Format) - 1;
  v3 = strchr(Format, '%');
  if (v4 >= 2 )
  {
    v6 = Format[v4 - 1];
    v7 = Format+v4;
    if ( v6 == '\n' && *(v7 - 2) == '\r' || v6 == '\r' && *(v7 - 2) == '\n' )
      *(v7 - 2) = 0;
  }
  if ( *Format )
  {
    if ( v3 )
    {
      v10 = Format;
      v9 = 0;
      v8 = *Format;
      do
      {
        if ( v8 == '%' )
          ++v9;
        v8 = (v10++)[1];
      }
      while ( v8 );
      v11 = (char*)malloc(strlen(Format) - 1 + v9 + 1);
      if ( v11 )
      {
        v12 = v11;
        while ( *v5 )
        {
          if ( *v5 == '%' )
          {
            *v12 = '%';
            ++v12;
          }
          *v12 = *v5;
          ++v12;
          ++v5;
        }
        *v12 = 0;
        v14 = v11;
        goto LABEL_23;
      }
      while ( strchr(Format, '%') )
        *strchr(Format, '%') = ' ';
    }
    v14 = Format;
LABEL_23:
    printf(v14);
  }
  printf("\n");
  return 0;
}

typedef int (_stdcall *RCCALL)(int,int,void*,int,int,char*[]);

int main(int argc, char* argv[])
{
	HMODULE hModule=LoadLibrary("RCDLL.DLL");
	PHANDLER_ROUTINE Handler=(PHANDLER_ROUTINE)GetProcAddress(hModule,"Handler");
	SetConsoleCtrlHandler(Handler,TRUE);
	RCCALL RC=(RCCALL)GetProcAddress(hModule,"RC");
	int Code=RC(0,0,sub_10010F0,0,argc,argv);
	SetConsoleCtrlHandler(Handler,FALSE);
	return Code;
}
