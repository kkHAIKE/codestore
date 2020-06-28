/******************************************************************** 
	isee_thum.h	ISee图像浏览器—ISee内部图像格式缩放代码定义文件 
 
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
		675  Mass Ave,  Cambridge,	MA02139,  USA 
 
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
 
 
#ifndef __ISEE_THUM_INC__ 
#define __ISEE_THUM_INC__ 
 
// Alpha表尺寸 
#define _IRWE_THUM_APLHATAB_SIZE	129 
// 四字类型对定义 
typedef __int64		QWORD; 
 
 
void _Thum_InitAlphaTable(); 
void _Thum_BlitStretch(DWORD **lpDesLines, int deswidth, int desheight,  
			DWORD **lpSrcLines, int srcwidth, int srcheight); 
void _Thum_DrawScanLine(DWORD* DestAddr, DWORD* SrcAddr, int Width, DWORD dU); 
void _Thum_DrawScanLineAlpha(DWORD* DestAddr, DWORD* SrcAddr,  
						int Width, DWORD dU, DWORD Alpha); 
 
#endif //__ISEE_THUM_INC__