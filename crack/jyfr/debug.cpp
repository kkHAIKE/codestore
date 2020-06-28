// debug.cpp : Defines the entry point for the console application.
//

#include "StdAfx.h"

extern BYTE g_JyDump[];

int some_const[3]={60,80,110};

int dword_10553074=3120;
int dword_10553068=400;
int dword_1055306C=700;

  int * dword_10063664;
  int * dword_1006366C;

	int *dword_1052B3A8;
	int *dword_1052B3AC;
	int *dword_1052B3E4;
	int *dword_1052E36C;
	int *dword_105312F4;
	int *dword_10537204;
	int *dword_1053427C;
	float *flt_1053A18C;
	unsigned __int8 *byte_1053D114;
	float *flt_1053DCF8;
	float *flt_10540C84;
	int *dword_10540D8C;
	int *dword_10540D90;
	int *dword_10540DA4;
	float *flt_10540DB4;
	int *dword_10540DC8;
	int *dword_10540E5C;
	int *dword_10542368;
	int *dword_10543874;
	int *dword_10544D80;
	int *dword_1054628C;
	float *flt_10547798;
	unsigned __int8 *byte_10548CA4;
	float *flt_105491E8;
	float *flt_1054A6F4;
	int *dword_1054A754;
	int *dword_1054A758;
	int *dword_1054A774;
	int *dword_1054A778;
	int *dword_1054A78c;
	float *flt_1054A794;
	int *dword_1054A7A8;
	int *dword_1054A7E8;
	int *dword_1054AEA8;
	int *dword_1054B568;
	int *dword_1054BC28;
	int *dword_1054C2E8;
	float *flt_1054C9A8;
	unsigned __int8 *byte_1054D068;
	float *flt_1054D218;
	float *flt_1054D8D8;
	int *dword_1054D8F4;
	int *dword_1054DFB4;
	int *dword_1054E674;
	int *dword_1054ED34;
	int *dword_1054F3F4;
	float *flt_1054FAB4;
	unsigned __int8 *byte_10550174;
	float *flt_10550324;
	float *flt_105509E4;

//#pragma comment(lib,"Junyufr.lib")

int __stdcall junyufr_JY_ExtractFaceFeatureAuto(unsigned __int8 *pImage, int imgWidth, int imgHeight, FaceInfo_t ***pFaceInfoList, int *pFaceCount);

void MY_JY_InitModule()
{
// 	FILE *fp=fopen("jydump","rb");
// 	g_JyDump=new BYTE[153188];
// 	fread(g_JyDump,153188,1,fp);
// 	fclose(fp);

// 	fopen("jydump02","rb");
// 	g_JyDump02=new BYTE[26940];
// 	fread(g_JyDump02,26940,1,fp);
// 	fclose(fp);

	dword_10063664=some_const;
	dword_1006366C=some_const+2;

	dword_1052B3A8=(int *)(g_JyDump);
	dword_1052B3AC=(int *)(g_JyDump+4);
	dword_1052B3E4=(int *)(g_JyDump+0x3c);
	dword_1052E36C=(int *)(g_JyDump+0x2fc4);
	dword_105312F4=(int *)(g_JyDump+0x5F4C);
	dword_10537204=(int *)(g_JyDump+0xBE5C);
	dword_1053427C=(int *)(g_JyDump+0x8ED4);
	flt_1053A18C=(float *)(g_JyDump+0xEDE4);
	byte_1053D114=(unsigned __int8 *)(g_JyDump+0x11D6C);
	flt_1053DCF8=(float *)(g_JyDump+0x12950);
	flt_10540C84=(float *)(g_JyDump+0x158DC);
	dword_10540D8C=(int *)(g_JyDump+0x159E4);
	dword_10540D90=(int *)(g_JyDump+0x159E8);
	dword_10540DA4=(int *)(g_JyDump+0x159FC);
	flt_10540DB4=(float *)(g_JyDump+0x15A0C);
	dword_10540DC8=(int *)(g_JyDump+0x15A20);
	dword_10540E5C=(int *)(g_JyDump+0x15AB4);
	dword_10542368=(int *)(g_JyDump+0x16FC0);
	dword_10543874=(int *)(g_JyDump+0x184CC);
	dword_10544D80=(int *)(g_JyDump+0x199D8);
	dword_1054628C=(int *)(g_JyDump+0x1AEE4);
	flt_10547798=(float *)(g_JyDump+0x1C3F0);
	byte_10548CA4=(unsigned __int8 *)(g_JyDump+0x1D8FC);
	flt_105491E8=(float *)(g_JyDump+0x1DE40);
	flt_1054A6F4=(float *)(g_JyDump+0x1F34C);
	dword_1054A754=(int *)(g_JyDump+0x1F3AC);
	dword_1054A758=(int *)(g_JyDump+0x1F3B0);
	dword_1054A774=(int *)(g_JyDump+0x1F3CC);
	dword_1054A778=(int *)(g_JyDump+0x1F3D0);
	dword_1054A78c=(int *)(g_JyDump+0x1F3E4);
	flt_1054A794=(float *)(g_JyDump+0x1F3EC);
	dword_1054A7A8=(int *)(g_JyDump+0x1F400);
	dword_1054A7E8=(int *)(g_JyDump+0x1F440);
	dword_1054AEA8=(int *)(g_JyDump+0x1FB00);
	dword_1054B568=(int *)(g_JyDump+0x201C0);
	dword_1054BC28=(int *)(g_JyDump+0x20880);
	dword_1054C2E8=(int *)(g_JyDump+0x20F40);
	flt_1054C9A8=(float *)(g_JyDump+0x21600);
	byte_1054D068=(unsigned __int8 *)(g_JyDump+0x21CC0);
	flt_1054D218=(float *)(g_JyDump+0x21E70);
	flt_1054D8D8=(float *)(g_JyDump+0x22530);
	dword_1054D8F4=(int *)(g_JyDump+0x2254C);
	dword_1054DFB4=(int *)(g_JyDump+0x22C0C);
	dword_1054E674=(int *)(g_JyDump+0x232CC);
	dword_1054ED34=(int *)(g_JyDump+0x2398C);
	dword_1054F3F4=(int *)(g_JyDump+0x2404C);
	flt_1054FAB4=(float *)(g_JyDump+0x2470C);
	byte_10550174=(unsigned __int8 *)(g_JyDump+0x24DCC);
	flt_10550324=(float *)(g_JyDump+0x24F7C);
	flt_105509E4=(float *)(g_JyDump+0x2563C);
}

void MY_JY_FreeModule()
{
	//delete[] g_JyDump;
}
int main(int argc, char* argv[])
{
	unsigned __int8 bmp[358*441];
	FILE *fp=fopen("testbmp","rb");
	fread(bmp,358*441,1,fp);
	fclose(fp);

	MY_JY_InitModule();

	pFaceInfo_t *faceinfo=NULL;
	int face=0;
	junyufr_JY_ExtractFaceFeatureAuto(bmp,358,441,&faceinfo,&face);
	
	MY_JY_FreeModule();
}

