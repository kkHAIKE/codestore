/********************************************************************  
    isee_thum.cpp   ISeeͼ���������ISee�ڲ�ͼ���ʽ���Ŵ���ʵ���ļ�  
  
    ��Ȩ����(C) 2001 VCHelp-coPathway-ISee workgroup member's  
  
        ��һ����������������������������������������GNU   
    ͨ�ù������֤�������޸ĺ����·�����һ���򡣻��������֤��  
    �ڶ��棬���ߣ��������ѡ�����κθ��µİ汾��  
  
        ������һ�����Ŀ����ϣ�������ã���û���κε���������û  
    ���ʺ��ض�Ŀ�ص������ĵ���������ϸ����������GNU ͨ�ù���  
    ���֤��  
  
        ��Ӧ���Ѿ��ͳ���һ���յ�һ��GNU ͨ�ù������֤�ĸ�����  
    �����û�У�д�Ÿ���  
        The Free Software Foundation, Inc.,   
        675  Mass Ave,  Cambridge,  MA02139,  USA  
  
        �������ʹ�ñ����ʱ��ʲô������飬�����µ�ַ������  
    ����ȡ����ϵ��  
        http://isee.126.com  
        http://www.vchelp.net  
    ��  
        iseesoft@china.com  
  
    ��д��Analyst  
    ���ʣ�analyst@citiz.net  
  
    �汾��Build 10108  
          Date  2001-1-8  
*********************************************************************/   
   
#include "stdafx.h"   
   
#include "isee_thum.h"   
   
#ifdef _DEBUG   
#define new DEBUG_NEW   
#undef THIS_FILE   
static char THIS_FILE[] = __FILE__;   
#endif   
   
// Alpha���ڲ�ʹ�ã�   
static QWORD s_AlphaTable[_IRWE_THUM_APLHATAB_SIZE];   
   
   
// ��ʼ��Alpha���˺���Ӧ�����������ʼ��ʱ�͵��ã�   
void _Thum_InitAlphaTable()   
{   
    QWORD temp;   
   
    for(int i=0;i<_IRWE_THUM_APLHATAB_SIZE;i++)   
    {   
        temp = (QWORD)i;   
        s_AlphaTable[i] = temp<<48 | temp<<32 | temp<<16 | temp;   
    }   
}   
   
   
// ͼ�����ź��������Ǹ�ģ��Ψһ�Ķ���ӿڣ�   
// ע����ģ��ֻ������ISee�ڲ�ͼ���ʽ��Ҳ����32λDIBλ��ʽ��   
void _Thum_BlitStretch(   
    DWORD **lpDesLines,     // Ŀ��ͼ�񻺳����е�ַ���飨������ÿ��Ԫ�ص�ֵ���Ƕ�Ӧͼ��ɨ���е��׵�ַ��   
    int deswidth,           // Ŀ��ͼ���ȣ�������Ϊ��λ��   
    int desheight,          // Ŀ��ͼ��߶ȣ�������Ϊ��λ��   
    DWORD **lpSrcLines,     // Դͼ�񻺳����е�ַ���飨������ÿ��Ԫ�ص�ֵ���Ƕ�Ӧͼ��ɨ���е��׵�ַ��   
    int srcwidth,           // Դͼ���ȣ�������Ϊ��λ��   
    int srcheight           // Դͼ��߶ȣ�������Ϊ��λ��   
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
           
   
// �����ź������ڲ�������   
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
