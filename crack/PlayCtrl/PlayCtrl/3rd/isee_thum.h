/******************************************************************** 
	isee_thum.h	ISeeͼ���������ISee�ڲ�ͼ���ʽ���Ŵ��붨���ļ� 
 
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
		675  Mass Ave,  Cambridge,	MA02139,  USA 
 
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
 
 
#ifndef __ISEE_THUM_INC__ 
#define __ISEE_THUM_INC__ 
 
// Alpha��ߴ� 
#define _IRWE_THUM_APLHATAB_SIZE	129 
// �������ͶԶ��� 
typedef __int64		QWORD; 
 
 
void _Thum_InitAlphaTable(); 
void _Thum_BlitStretch(DWORD **lpDesLines, int deswidth, int desheight,  
			DWORD **lpSrcLines, int srcwidth, int srcheight); 
void _Thum_DrawScanLine(DWORD* DestAddr, DWORD* SrcAddr, int Width, DWORD dU); 
void _Thum_DrawScanLineAlpha(DWORD* DestAddr, DWORD* SrcAddr,  
						int Width, DWORD dU, DWORD Alpha); 
 
#endif //__ISEE_THUM_INC__