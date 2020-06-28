/********************************************************************  
    isee_thum.cpp   ISee图像浏览器—ISee内部图像格式缩放代码实现文件  
  
    版权所有(C) 2001 VCHelp-coPathway-ISee workgroup member's  
  
        这一程序是自由软件，你可以遵照自由软件基金会出版的GNU   
    通用公共许可证条款来修改和重新发布这一程序。或者用许可证的  
    第二版，或者（根据你的选择）用任何更新的版本。  
  
        发布这一程序的目的是希望它有用，但没有任何担保。甚至没  
    有适合特定目地的隐含的担保。更详细的情况请参阅GNU 通用公共  
    许可证。  
  
        你应该已经和程序一起收到一份GNU 通用公共许可证的副本。  
    如果还没有，写信给：  
        The Free Software Foundation, Inc.,   
        675  Mass Ave,  Cambridge,  MA02139,  USA  
  
        如果你在使用本软件时有什么问题或建议，用以下地址可以与  
    我们取得联系：  
        http://isee.126.com  
        http://www.vchelp.net  
    或：  
        iseesoft@china.com  
  
    编写：Analyst  
    电邮：analyst@citiz.net  
  
    版本：Build 10108  
          Date  2001-1-8  
*********************************************************************/   
   
#include "stdafx.h"   
   
#include "isee_thum.h"   
   
#ifdef _DEBUG   
#define new DEBUG_NEW   
#undef THIS_FILE   
static char THIS_FILE[] = __FILE__;   
#endif   
   
// Alpha表（内部使用）   
static QWORD s_AlphaTable[_IRWE_THUM_APLHATAB_SIZE];   
   
   
// 初始化Alpha表（此函数应该在主程序初始化时就调用）   
void _Thum_InitAlphaTable()   
{   
    QWORD temp;   
   
    for(int i=0;i<_IRWE_THUM_APLHATAB_SIZE;i++)   
    {   
        temp = (QWORD)i;   
        s_AlphaTable[i] = temp<<48 | temp<<32 | temp<<16 | temp;   
    }   
}   
   
   
// 图像缩放函数（这是该模块唯一的对外接口）   
// 注：本模块只适用于ISee内部图像格式，也就是32位DIB位格式。   
void _Thum_BlitStretch(   
    DWORD **lpDesLines,     // 目标图像缓冲区行地址数组（数组中每个元素的值都是对应图像扫描行的首地址）   
    int deswidth,           // 目标图像宽度（以象素为单位）   
    int desheight,          // 目标图像高度（以象素为单位）   
    DWORD **lpSrcLines,     // 源图像缓冲区行地址数组（数组中每个元素的值都是对应图像扫描行的首地址）   
    int srcwidth,           // 源图像宽度（以象素为单位）   
    int srcheight           // 源图像高度（以象素为单位）   
    )   
{   
    DWORD dU = (srcwidth < 16) / deswidth;   
    DWORD dV = (srcheight < 16) / desheight;   
    DWORD V1 = 0;   
   
    for(int i = 0; i  desheight-1; i++)   
    {   
        _Thum_DrawScanLine((DWORD*)(lpDesLines[i]), (DWORD *)(lpSrcLines[(V1>>16)]), deswidth, dU);   
        _Thum_DrawScanLineAlpha((DWORD*)(lpDesLines[i]), (DWORD *)(lpSrcLines[(V1>>16)+1]), deswidth, dU, (V1>>9)&0x7f);   
        V1 += dV;   
    }   
}   
           
   
// 行缩放函数（内部函数）   
void _Thum_DrawScanLine(DWORD* DestAddr, DWORD* SrcAddr, int Width, DWORD dU)   
{   
    __asm{   
        mov esi, SrcAddr;   
        mov edi, DestAddr;   
        mov ecx, Width;   
        xor edx, edx;  //edx = U1   
        mov ebx, dU;   
        pxor mm7, mm7;   
   
    LoopX:   
        mov eax, edx;   
        and eax, 0xffff;   
        shr eax, 9;   
        movq mm6, [s_AlphaTable + eax * 8]; //mm6 = a2   
        neg eax;   
        add eax, 128;   
        movq mm5, [s_AlphaTable + eax * 8]; //mm5 = a1   
   
        mov eax, edx;   
        shr eax, 16;   
        movq mm0, [esi + eax * 4];   
        movq mm1, mm0;   
        PUNPCKLBW mm0, mm7;  //mm0 = 0a10r10g10b1   
        PUNPCKHBW mm1, mm7;  //mm1 = 0a20r20g20b2   
   
        pmullw mm0, mm5;   
        pmullw mm1, mm6;   
        paddw  mm0, mm1;   
        psrlw  mm0, 7;   
        packuswb mm0, mm0;   
        movd eax, mm0;   
        add edx, ebx;   
        stosd;   
   
        dec ecx;   
        jnz LoopX;   
        emms;   
    }   
}   
   
void _Thum_DrawScanLineAlpha(DWORD* DestAddr, DWORD* SrcAddr, int Width, DWORD dU, DWORD Alpha)   
{   
    if(!Alpha)   
        return;   
   
    __asm{   
        mov esi, SrcAddr;   
        mov edi, DestAddr;   
        mov ecx, Width;   
        xor edx, edx;  //edx = U1   
        mov ebx, dU;   
        mov eax, Alpha;   
        pxor mm7, mm7;   
        movq mm4, [s_AlphaTable + eax * 8]; //mm4 = alpha   
   
        LoopX:   
        mov eax, edx;   
        and eax, 0xffff;   
        shr eax, 9;   
        movq mm6, [s_AlphaTable + eax * 8]; //mm6 = a2   
        neg eax;   
        add eax, 128;   
        movq mm5, [s_AlphaTable + eax * 8]; //mm5 = a1   
   
        mov eax, edx;   
        shr eax, 16;   
        movq mm0, [esi + eax * 4];   
        movq mm1, mm0;   
        PUNPCKLBW mm0, mm7;  //mm0 = 0a10r10g10b1   
        movd mm2, [edi];   
        PUNPCKHBW mm1, mm7;  //mm1 = 0a20r20g20b2   
   
        pmullw mm0, mm5;   
        punpcklbw mm2, mm7;   
        pmullw mm1, mm6;   
        paddw  mm0, mm1;   
        psrlw  mm0, 7;   
   
        psubw mm0, mm2;   
        pmullw mm0, mm4;   
        psraw  mm0, 7;   
        paddw  mm0, mm2;   
   
        packuswb mm0, mm0;   
        movd eax, mm0;   
        add edx, ebx;   
        stosd;   
   
        dec ecx;   
        jnz LoopX;   
        emms;   
    }   
} 
