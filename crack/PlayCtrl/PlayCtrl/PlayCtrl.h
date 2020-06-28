#pragma once

typedef struct{
	long nFilePos;
	long nFrameNum;
	long nFrameTime;
	long nErrorFrameNum;
	SYSTEMTIME *pErrorTime;
	long nErrorLostFrameNum;
	long nErrorFrameSize;
}FRAME_POS,*PFRAME_POS;

typedef struct{
	long nWidth;
	long nHeight;
	long nStamp;
	long nType;
	long nFrameRate;
	DWORD dwFrameNum;
}FRAME_INFO;

typedef struct{
	char *pDataBuf;
	long  nSize;
	long  nFrameNum;
	BOOL  bRsaRight;
	long  nReserved;
}WATERMARK_INFO;

typedef struct
{
	long nPort;
	char * pBuf;
	long nBufLen;
	long nWidth;
	long nHeight;
	long nStamp;
	long nType;
	long nUser;
}DISPLAY_INFO;

typedef struct
{
	int part1;
	char* pBuf;
	long nSize;
	DWORD dwFrameNum;
	long nStamp;
	long nFrameRate;
	long nType;
	long nWidth;
	long nHeight;
	int part2;
	int part3;
	int part4;
	int part5;
	int part6;
	int part7;
	int part8;
	int part9;
	char* pWIDataBuf;
	int nWISize;
	int bWIRsaRight;
	int nWIReserved;
	int nWIFrameNum;
}IVSPLAY_DECDATA_INFO;

typedef struct
{
	char *pBuf;
	int nBufLen;
	ULONG part1;
	ULONG nStamp;
	ULONG part2;
	int nType;
	ULONG nWidth;
	ULONG nHeight;
	int part4;
	int part6[7];
}IVSPLAY_FRAME_INFO;

typedef struct
{
	int nType;
	ULONG nWidth;
	ULONG nHeight;
	ULONG part1;
	ULONG nStamp;
	ULONG part2;
	int part3;
	int part4;
	int part5;
	int part6[7];
}DISPLAY_PARA;

typedef struct
{
	DWORD magic;
	DWORD part1;
	DWORD part2;
	DWORD part3;
	DWORD part4;
	BYTE part5;
	BYTE part6;
	BYTE part7;
	BYTE part8;
	DWORD part9;
	DWORD part10;
	DWORD part11;
}HIKVISION_MEDIA_FILE_HEADER;

typedef struct
{
	WORD part1;
	WORD part2;
	WORD type;
	WORD part4;
	WORD part5;
	BYTE part6;
	BYTE part7;
	int part8;
	int part9;
	int part10;
}MULTIMEDIA_INFO;

typedef struct
{
	DWORD magic;
	DWORD part1;
	WORD part2;
	WORD type;
	WORD part5;
	BYTE part6;
	BYTE part7;
	int part8;
	int part9;
	int part10;
}HIKVISION_MEDIA_INFO;


typedef void (__stdcall *CB_DEC)(long nPort,char *pBuf,long nSize,FRAME_INFO *pFrameInfo,long nUser,long nReserved2);
typedef void (__stdcall *CB_CWM)(long nPort,WATERMARK_INFO* pWatermarkInfo,DWORD nUser);
typedef void (__stdcall *CB_Display)(long nPort,char * pBuf,long nSize,long nWidth,long nHeight,long nStamp,long nType,long nReserved);
typedef void (__stdcall *CB_DisplayEx)(DISPLAY_INFO *pstDisplayInfo);
typedef void (__stdcall *CB_DrawFun)(long nPort,HDC hDc,LONG nUser);
typedef void (__stdcall *CB_EncChange)(long nPort,long nUser);
typedef void (__stdcall *CB_FileDone)(DWORD nPort,DWORD nUser);

typedef void (__stdcall *CB_FPSChange)(ULONG,ULONG);
typedef void (__stdcall *CB_PlayEnd)(ULONG);
typedef void (__stdcall *CB_Display2)(ULONG,IVSPLAY_FRAME_INFO *,ULONG);
typedef void (__stdcall *CB_DimChange)(ULONG,ULONG,ULONG);
typedef void (__stdcall *CB_HDC)(ULONG,HDC,IVSPLAY_FRAME_INFO *,IVSPLAY_SYNCDATA_INFO *,ULONG);

typedef void (__stdcall *CB_Dec2)(IVSPLAY_DECDATA_INFO *,ULONG);
typedef void (__stdcall *CB_TargetFrame)(ULONG);

