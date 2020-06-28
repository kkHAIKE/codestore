#pragma once

#include <Wininet.h>
#pragma comment(lib,"Wininet.lib")

#if !defined(__CSTRINGT_H__) && !defined(_WTL_USE_CSTRING)
#include <StdString.h>
#define CSTRING CStdString
#else
#define CSTRING CString
#endif

inline DWORD HttpGetBuffer(CSTRING& url,BYTE*& data)
{
	TCHAR headers[]=_T("Accept: */*\r\n");
	HINTERNET hNet=NULL;
	HINTERNET hUrlFile=NULL;
	data=NULL;
	DWORD retsize=0;
	try
	{
		hNet = InternetOpen(NULL,INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,0);
		if (hNet == NULL)
			throw 1;

		CSTRING strUrl=url;
		strUrl.TrimLeft();
		strUrl.TrimRight();
		if (strUrl.Find(_T("http:")) == -1)
		{
			if (strUrl[0] == _T('/'))
				strUrl.Insert(0,_T("http:"));
			else
				strUrl.Insert(0,_T("http://"));
		}

		hUrlFile = InternetOpenUrl(hNet,strUrl,headers,lstrlen(headers),INTERNET_FLAG_RELOAD|INTERNET_FLAG_DONT_CACHE
		                           | INTERNET_FLAG_TRANSFER_BINARY| INTERNET_FLAG_EXISTING_CONNECT,1);
		if (hUrlFile == NULL)
			throw 1;

		TCHAR szBuffer[80];
		DWORD dwLen = 80;
		if(!HttpQueryInfo(hUrlFile, HTTP_QUERY_STATUS_CODE, szBuffer, &dwLen, NULL))
			throw 1;
		if(_tcstol(szBuffer,NULL,10)!=200)
			throw 1;

		dwLen=0;
		if(HttpQueryInfo(hUrlFile, HTTP_QUERY_CONTENT_LENGTH,NULL, &dwLen, 0))
			throw 1;
		TCHAR* lpOutBuffer =  new TCHAR[dwLen];
		if(!HttpQueryInfo(hUrlFile, HTTP_QUERY_CONTENT_LENGTH,lpOutBuffer, &dwLen, 0))
		{
			delete[] lpOutBuffer;
			throw 1;
		}

		retsize=_tcstol(lpOutBuffer,NULL,10);
		delete[] lpOutBuffer;
		if(retsize==0)
			throw 1;

		BYTE* m_buffer = new BYTE[retsize+1];
		m_buffer[retsize] = 0;
		char* p=reinterpret_cast<char*>(m_buffer);
		DWORD nRead;
		dwLen=retsize;
		do
		{
			if(!InternetReadFile(hUrlFile,p,min(dwLen,1024),&nRead))
			{
				delete[] m_buffer;
				throw 1;
			}
			if (nRead != 0)
			{
				dwLen-=nRead;
				p+=nRead;
			}
		}
		while (dwLen!=0 && nRead!=0);
		data=m_buffer;
	}
	catch(int)
	{
	}
	if(hUrlFile)
		InternetCloseHandle(hUrlFile);
	if(hNet)
		InternetCloseHandle(hNet);
	return retsize;
}
