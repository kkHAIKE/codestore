#pragma once
#include <Debug.h>

#if (_MSC_VER > 1400)
#define USE_SAFE
#endif

template<typename __char>
class CStdStringBasicFuc
{
public:
	CStdStringBasicFuc()
	{
		__nullstr[0]=__nullstr[1]='\0';
	}

	inline BOOL __IsBadStringPtr(LPCSTR lpsz,UINT_PTR ucchMax) const
	{
		return IsBadStringPtrA(lpsz,ucchMax);
	}
	inline BOOL __IsBadStringPtr(LPCWSTR lpsz,UINT_PTR ucchMax) const
	{
		return IsBadStringPtrW(lpsz,ucchMax);
	}
	
	inline int __strlen(LPCSTR string) const
	{
		return lstrlenA(string);
	}
	inline int __strlen(LPCWSTR string) const
	{
		return lstrlenW(string);
	}

	inline errno_t __strcpy( LPSTR strDestination, size_t _SizeInBytes,LPCSTR strSource)
	{
	#ifdef USE_SAFE
		return strcpy_s(strDestination,_SizeInBytes,strSource);
	#else
		return strcpy(strDestination,strSource)!=NULL;
	#endif
	}
	inline errno_t __strcpy( LPWSTR strDestination, size_t _SizeInBytes, LPCWSTR strSource)
	{
	#ifdef USE_SAFE
		return wcscpy_s(strDestination,_SizeInBytes,strSource);
	#else
		return wcscpy(strDestination,strSource)!=NULL;
	#endif
	}

	inline errno_t __strncpy( LPSTR strDest,size_t _SizeInBytes, LPCSTR strSource, size_t count )
	{
	#ifdef USE_SAFE
		return strncpy_s(strDest,_SizeInBytes,strSource,count);
	#else
		return strncpy(strDest,strSource,count)!=NULL;
	#endif
	}
	inline errno_t __strncpy( LPWSTR strDest,size_t _SizeInBytes, LPCWSTR strSource, size_t count )
	{
	#ifdef USE_SAFE
		return wcsncpy_s(strDest,_SizeInBytes,strSource,count);
	#else
		return wcsncpy(strDest,strSource,count)!=NULL;
	#endif
	}

	inline errno_t __strcat( LPSTR strDestination, size_t _SizeInBytes,LPCSTR strSource)
	{
	#ifdef USE_SAFE
		return strcat_s(strDestination,_SizeInBytes,strSource);
	#else
		return strcat(strDestination,strSource)!=NULL;
	#endif
	}
	inline errno_t __strcat( LPWSTR strDestination, size_t _SizeInBytes, LPCWSTR strSource)
	{
	#ifdef USE_SAFE
		return wcscat_s(strDestination,_SizeInBytes,strSource);
	#else
		return wcscat(strDestination,strSource)!=NULL;
	#endif
	}

	inline int __strcmp( LPCSTR string1, LPCSTR string2 ) const
	{
		return lstrcmpA(string1,string2);
	}
	inline int __strcmp( LPCWSTR string1, LPCWSTR string2 ) const
	{
		return lstrcmpW(string1,string2);
	}

	inline int __stricmp( LPCSTR string1, LPCSTR string2 ) const
	{
		return lstrcmpiA(string1,string2);
	}
	inline int __stricmp( LPCWSTR string1, LPCWSTR string2 ) const
	{
		return lstrcmpiW(string1,string2);
	}

	inline errno_t __strupr( LPSTR string ,size_t _SizeInBytes)
	{
	#ifdef USE_SAFE
		return _strupr_s(string,_SizeInBytes);
	#else
		return _strupr(string)!=NULL;
	#endif
	}	
	inline errno_t __strupr( LPWSTR string ,size_t _SizeInBytes)
	{
	#ifdef USE_SAFE
		return _wcsupr_s(string,_SizeInBytes);
	#else
		return _wcsupr(string)!=NULL;
	#endif
	}

	inline errno_t __strlwr( LPSTR string ,size_t _SizeInBytes)
	{
	#ifdef USE_SAFE
		return _strlwr_s(string,_SizeInBytes);
	#else
		return _strlwr(string)!=NULL;
	#endif
	}
	inline errno_t __strlwr( LPWSTR string ,size_t _SizeInBytes)
	{
	#ifdef USE_SAFE
		return _wcslwr_s(string,_SizeInBytes);
	#else
		return _wcslwr(string)!=NULL;
	#endif
	}

	inline LPSTR __strstr( LPSTR string, LPCSTR strCharSet ) const
	{
		return strstr(string,strCharSet);
	}
	inline LPWSTR __strstr( LPWSTR string, LPCWSTR strCharSet ) const
	{
		return wcsstr(string,strCharSet);
	}

	inline LPCSTR __strchr( LPCSTR string, int c ) const
	{
		return strchr(string,c);
	}
	inline LPCWSTR __strchr( LPCWSTR string, int c ) const
	{
		return wcschr(string,c);
	}

	inline LPSTR __strrchr( LPCSTR string, int c ) const
	{
		return strrchr(string,c);
	}
	inline LPWSTR __strrchr( LPCWSTR string, int c ) const
	{
		return wcsrchr(string,c);
	}
	
	inline int __wvnsprintf(LPSTR lpOut,int cchLimitIn,LPCSTR pszFmt,va_list arglist)
	{
		return wvnsprintfA(lpOut,cchLimitIn,pszFmt,arglist);
	}
	inline int __wvnsprintf(LPWSTR lpOut,int cchLimitIn,LPCWSTR pszFmt,va_list arglist)
	{
		return wvnsprintfW(lpOut,cchLimitIn,pszFmt,arglist);
	}

	inline errno_t __vsprintf(LPSTR lpOut,int cchLimitIn,LPCSTR pszFmt,va_list arglist)
	{
	#ifdef USE_SAFE
		return vsprintf_s(lpOut,cchLimitIn,pszFmt,arglist);
	#else
		return vsprintf(lpOut,pszFmt,arglist);
	#endif
	}
	inline errno_t __vsprintf(LPWSTR lpOut,int cchLimitIn,LPCWSTR pszFmt,va_list arglist)
	{
	#ifdef USE_SAFE
		return vswprintf_s(lpOut,cchLimitIn,pszFmt,arglist);
	#else
		return vswprintf(lpOut,pszFmt,arglist);
	#endif
	}

	inline size_t __strcspn( LPCSTR str, LPCSTR strCharSet ) const
	{
		return strcspn(str,strCharSet);
	}
	inline size_t __strcspn( LPCWSTR str, LPCWSTR strCharSet ) const
	{
		return wcscspn(str,strCharSet);
	}
	
	inline size_t __strspn( LPCSTR str,LPCSTR strCharSet ) const
	{
		return strspn(str,strCharSet);
	}
	inline size_t __strspn( LPCWSTR str,LPCWSTR strCharSet ) const
	{
		return wcsspn(str,strCharSet);
	}

	inline LPSTR __CharNext(LPCSTR lpsz) const
	{
		return CharNextA(lpsz);
	}
	inline LPWSTR __CharNext(LPCWSTR lpsz) const
	{
		return CharNextW(lpsz);
	}

	virtual void Assign(LPCSTR pstr, int cchMax = -1)
	{
	}
	virtual void Assign(LPCWSTR pstr, int cchMax = -1)
	{
	}

	__char __nullstr[2];

protected:

	inline void PreAssign(LPSTR dis,LPCSTR src,int cchMax = -1)
	{
		Assign(src,cchMax);
	}
	inline void PreAssign(LPSTR dis,LPCWSTR src,int cchMax = -1)
	{
		LPSTR pstr=NULL;
		if(src!=NULL)
		{
			int cchStr = ::WideCharToMultiByte(GetACP(),0, src, cchMax, NULL, 0,0,0);
			pstr = static_cast<LPSTR>(_alloca((cchStr+1)*sizeof(char)));
			if(pstr!=NULL)
			{
				::WideCharToMultiByte(GetACP(),0, src, cchMax, pstr, cchStr+1,0,0);
				pstr[cchStr]=0;
			}
		}
		Assign(pstr);
	}
	inline void PreAssign(LPWSTR dis,LPCSTR src,int cchMax = -1)
	{
		LPWSTR pstr=NULL;
		if(src!=NULL)
		{
			int cchStr = ::MultiByteToWideChar(GetACP(),0, src, cchMax, NULL, 0);
			pstr = static_cast<LPWSTR>(_alloca((cchStr+1)*sizeof(WCHAR)));
			if(pstr!=NULL)
			{
				::MultiByteToWideChar(GetACP(),0, src, cchMax, pstr, cchStr+1);
				pstr[cchStr]=0;
			}
		}
		Assign(pstr);
	}
	inline void PreAssign(LPWSTR dis,LPCWSTR src,int cchMax = -1)
	{
		Assign(src,cchMax);
	}

	inline void ConvUTF8(LPSTR dis,LPCSTR src,int cchMax = -1)
	{
		LPWSTR pstr=NULL;
		if(src!=NULL)
		{
			int cchStr = ::MultiByteToWideChar(CP_UTF8,0, src, cchMax, NULL, 0);
			pstr = static_cast<LPWSTR>(_alloca((cchStr+1)*sizeof(WCHAR)));
			if(pstr!=NULL)
			{
				::MultiByteToWideChar(CP_UTF8,0, src, cchMax, pstr, cchStr+1);
				pstr[cchStr]=0;
			}
		}
		PreAssign(dis,pstr);
	}
	inline void ConvUTF8(LPWSTR dis,LPCSTR src,int cchMax = -1)
	{
		LPWSTR pstr=NULL;
		if(src!=NULL)
		{
			int cchStr = ::MultiByteToWideChar(CP_UTF8,0, src, cchMax, NULL, 0);
			pstr = static_cast<LPWSTR>(_alloca((cchStr+1)*sizeof(WCHAR)));
			if(pstr!=NULL)
			{
				::MultiByteToWideChar(CP_UTF8,0, src, cchMax, pstr, cchStr+1);
				pstr[cchStr]=0;
			}
		}
		Assign(pstr);
	}
};

template<typename __char,int _buf=64>
class CStdStringBasic:public CStdStringBasicFuc<__char>
{
private:
	typedef CStdStringBasic<__char,_buf> this_type;

public:
	enum {MAX_LOCAL_STRING_LEN = _buf-1};

	CStdStringBasic():m_pstr(m_szBuffer),m_alloc(_buf)
	{
		m_szBuffer[0] = '\0';
	}
	CStdStringBasic( __char ch):m_pstr(m_szBuffer),m_alloc(_buf)
	{
		m_szBuffer[0] = ch;
		m_szBuffer[1] = '\0';
	}
	CStdStringBasic(const this_type & src):m_pstr(m_szBuffer),m_alloc(_buf)
	{
		m_szBuffer[0] = '\0';
		Assign(src.m_pstr);
	}

	CStdStringBasic(LPCSTR lpsz, int nLen = -1):m_pstr(m_szBuffer),m_alloc(_buf)
	{
		ASSERT(!::IsBadStringPtrA(lpsz,-1) || lpsz==NULL);
		m_szBuffer[0] = '\0';
		PreAssign(m_szBuffer,lpsz,nLen);
	}
	CStdStringBasic(LPCWSTR lpsz, int nLen = -1):m_pstr(m_szBuffer),m_alloc(_buf)
	{
		ASSERT(!::IsBadStringPtrW(lpsz,-1) || lpsz==NULL);
		m_szBuffer[0] = '\0';
		PreAssign(m_szBuffer,lpsz,nLen);
	}
	~CStdStringBasic()
	{
		if( m_pstr != m_szBuffer )
			free(m_pstr);
	}
	void ConvUTF8(LPCSTR src,int cchMax = -1)
	{
		CStdStringBasicFuc<__char>::ConvUTF8(m_pstr,src,cchMax);
	}
	void Empty()
	{
		if(m_pstr!=m_szBuffer)
		{
			free(m_pstr);
			m_pstr=m_szBuffer;
			m_alloc=_buf;
		}
		m_pstr[0]='\0';
	}
	int GetLength() const
	{
		return static_cast<int>(__strlen(m_pstr));
	}
	bool IsEmpty() const
	{
		return m_pstr[0] == '\0'; 
	}

	__char *GetBuffer(int nMinBufLength )
	{
		if(nMinBufLength<0)
			nMinBufLength=0;
		if(nMinBufLength<m_alloc)
			;
// 		if( nMinBufLength <= MAX_LOCAL_STRING_LEN ) 
// 		{
// 			if( m_pstr != m_szBuffer ) 
// 			{
// 				free(m_pstr);
// 				m_pstr = m_szBuffer;
// 			}
// 		}
		else
		{
			m_alloc=nMinBufLength + 1;
			if( m_pstr == m_szBuffer ) 
			{	
				m_pstr = static_cast<__char *>(malloc(m_alloc*sizeof(__char)));
				__strcpy(m_pstr,m_alloc, m_szBuffer);
			}
			else 
			{
				m_pstr = static_cast<__char *>(realloc(m_pstr,m_alloc*sizeof(__char)));
			}
		}

		return m_pstr;
	}
	void ReleaseBuffer( int nNewLength = -1)
	{
		ASSERT(nNewLength<0 || (nNewLength>=0 && nNewLength<m_alloc));
		m_pstr[m_alloc-1]='\0';
		if(nNewLength>=0 && nNewLength<m_alloc)
			m_pstr[nNewLength]='\0';

		int l_leng=GetLength();
		if(l_leng<=MAX_LOCAL_STRING_LEN)
		{
			if( m_pstr != m_szBuffer ) 
			{
				__strcpy(m_szBuffer,_buf,m_pstr);
				free(m_pstr);
				m_pstr = m_szBuffer;
				m_alloc=_buf;
			}
		}
		else if(l_leng!=m_alloc-1)
		{
			m_alloc=l_leng + 1;
			m_pstr=static_cast<__char *>(realloc(m_pstr, m_alloc * sizeof(__char)));
		}
	}
	void Append(const __char * pstr)
	{
		ASSERT(!__IsBadStringPtr(pstr,-1) || pstr==NULL);
		if(pstr==NULL || pstr[0]=='\0')
			return;

		GetBuffer(GetLength() + static_cast<int>(__strlen(pstr)));
		__strcat(m_pstr,m_alloc,pstr);
	}
	int Insert( int nIndex, const __char * pstr )
	{
		int l_leng=GetLength();
		ASSERT((!__IsBadStringPtr(pstr,-1) || pstr==NULL) && nIndex>=0 && nIndex<=l_leng);
		if(pstr==NULL || pstr[0]=='\0')
			return l_leng;

		int pstr_len=static_cast<int>(__strlen(pstr));
		GetBuffer(l_leng + pstr_len);
		if(nIndex<l_leng)
		{
			::MoveMemory(&m_pstr[nIndex+pstr_len],&m_pstr[nIndex],(l_leng-nIndex)*sizeof(__char));
		}
		//__strncpy(m_pstr+nIndex,GetAllocSize()-nIndex,pstr,pstr_len);
		::CopyMemory(m_pstr+nIndex,pstr,pstr_len*sizeof(__char));
		m_pstr[l_leng+pstr_len]='\0';
		return l_leng+pstr_len;
	}
	int Delete( int nIndex, int nCount = 1 )
	{
		int l_leng=GetLength();
		ASSERT(nCount>=1 && nIndex>=0 && nIndex<l_leng);
		if(nIndex+nCount>l_leng)
			nCount=l_leng-nIndex;
		if(nIndex+nCount<l_leng)
			::MoveMemory(&m_pstr[nIndex],&m_pstr[nIndex+nCount],(l_leng-nIndex-nCount+1)*sizeof(__char));
		else
			m_pstr[nIndex]='\0';
		ReleaseBuffer();
		return l_leng-nCount;
	}
	void Assign(const __char * pstr, int cchMax = -1)
	{
		if( pstr == NULL ) 
			pstr =__nullstr;
		cchMax = (cchMax<0 ? static_cast<int>(__strlen(pstr)) : cchMax);

		if( cchMax <= MAX_LOCAL_STRING_LEN ) 
		{
			if( m_pstr != m_szBuffer ) 
			{
				free(m_pstr);
				m_pstr = m_szBuffer;
				m_alloc=_buf;
			}
		}
		else if( cchMax >=m_alloc) 
		{
			if( m_pstr == m_szBuffer ) 
				m_pstr = NULL;
			m_alloc=cchMax + 1;
			m_pstr = static_cast<__char *>(realloc(m_pstr, m_alloc * sizeof(__char)));
		}
		//安全默认加结束符
		__strncpy(m_pstr,m_alloc,pstr, cchMax);
		//m_pstr[cchMax] = '\0';
	}
	const __char * GetData() const
	{
		return m_pstr;
	}

	void SetAt(int nIndex, __char ch)
	{
		ASSERT(nIndex>=0 && nIndex<GetLength());
		m_pstr[nIndex] = ch;
	}
	__char GetAt(int nIndex) const
	{
		ASSERT(nIndex>=0 && nIndex<GetLength());
		return m_pstr[nIndex];
	}
	__char& operator[] (int nIndex)
	{
		ASSERT(nIndex>=0 && nIndex<GetLength());
		return m_pstr[nIndex];
	}
	operator const __char *() const
	{
		return m_pstr; 
	}
	
	this_type& operator=(const this_type& src)
	{
		Assign(src.m_pstr);
		return *this;
	}
	this_type& operator=(__char ch)
	{
		m_szBuffer[0] = ch;
		m_szBuffer[1] = '\0';
		return *this;
	}
	this_type& operator=(const __char * pstr)
	{
		ASSERT(!__IsBadStringPtr(pstr,-1) || pstr==NULL);
		Assign(pstr);
		return *this;
	}

	friend this_type operator+(const this_type &a,const this_type &b)
	{
		this_type sTemp(a);
		sTemp.Append(b);
		return sTemp;
	}
	friend this_type operator+(const this_type &a,__char b)
	{
		this_type sTemp(a);
		sTemp.Append(b);
		return sTemp;
	}
	friend this_type operator+(const this_type &a,const __char* b)
	{
		this_type sTemp(a);
		sTemp.Append(b);
		return sTemp;
	}
	friend this_type operator+(__char a,const this_type &b)
	{
		this_type sTemp(a);
		sTemp.Append(b);
		return sTemp;
	}
	friend this_type operator+(const __char* a,const this_type &b)
	{
		this_type sTemp(a);
		sTemp.Append(b);
		return sTemp;
	}

	this_type& operator+=(const this_type& src)
	{
		Append(src.m_pstr);
		return *this;
	}
	this_type& operator+=(const __char * pstr)
	{
		ASSERT(!__IsBadStringPtr(pstr,-1) || pstr==NULL);
		Append(pstr);
		return *this;
	}
	this_type& operator+=(const __char ch)
	{
		__char str[] = { ch, '\0' };
		Append(str);
		return *this;
	}

	bool operator == (const __char * str) const{ return (Compare(str) == 0); }
	bool operator != (const __char * str) const{ return (Compare(str) != 0); }
	bool operator <= (const __char * str) const{ return (Compare(str) <= 0); }
	bool operator <  (const __char * str) const{ return (Compare(str) <  0); }
	bool operator >= (const __char * str) const{ return (Compare(str) >= 0); }
	bool operator >  (const __char * str) const{ return (Compare(str) >  0); }

	int Compare(const __char * pstr) const
	{
		 return __strcmp(m_pstr, pstr); 
	}
	int CompareNoCase(const __char * pstr) const
	{
		return __stricmp(m_pstr, pstr); 
	}

	void MakeUpper()
	{
		__strupr(m_pstr,m_alloc); 
	}
	void MakeLower()
	{
		__strlwr(m_pstr,m_alloc); 
	}

	this_type Left(int nLength) const
	{
		if(nLength<0)
			nLength=0;
		int l_leng=GetLength();
		if(nLength>l_leng)
			nLength = l_leng;
		return this_type(m_pstr, nLength);
	}
	this_type Mid(int iPos, int nLength = -1) const
	{
		int l_leng=GetLength();
		ASSERT(iPos>=0 && iPos<=l_leng);
		if(nLength<0 || iPos+nLength>l_leng)
			nLength=l_leng-iPos;
		if(nLength<=0) 
			return this_type();
		return this_type(m_pstr + iPos, nLength);
	}
	this_type Right(int nLength) const
	{
		int l_leng=GetLength();
		int iPos = l_leng - nLength;
		if( iPos < 0 ) 
		{
			iPos = 0;
			nLength = l_leng;
		}
		return this_type(m_pstr + iPos, nLength);
	}

	int Find(__char ch, int iPos = 0) const
	{
		if(iPos<0 || iPos>=GetLength()) 
			return -1;
		const __char * p = __strchr(m_pstr + iPos, ch);
		if(p==NULL) 
			return -1;
		return static_cast<int>(p - m_pstr);
	}
	int Find(const __char * pstr, int iPos = 0) const
	{
		ASSERT(!__IsBadStringPtr(pstr,-1));
		if(iPos<0 || iPos>=GetLength())
			return -1;
		const __char * p=__strstr(m_pstr + iPos, pstr);
		if(p==NULL)
			return -1;
		return static_cast<int>(p - m_pstr);
	}
	int ReverseFind(__char ch) const
	{
		const __char * p = __strrchr(m_pstr, ch);
		if(p==NULL)
			return -1;
		return static_cast<int>(p - m_pstr);
	}

	int Replace(const __char * pstrFrom, const __char * pstrTo)
	{
		ASSERT(!__IsBadStringPtr(pstrFrom,-1));
		ASSERT(!__IsBadStringPtr(pstrTo,-1) || pstrTo==NULL);
		if(pstrTo==NULL)
			pstrTo=__nullstr;
		this_type sTemp;
		int nCount = 0;
		int iPos = Find(pstrFrom);
		if(iPos<0)
			return 0;
		int cchFrom = static_cast<int>(__strlen(pstrFrom));
		int cchTo = static_cast<int>(__strlen(pstrTo));
		while( iPos >= 0 ) 
		{
			sTemp = Left(iPos);
			sTemp += pstrTo;
			sTemp += Mid(iPos + cchFrom);
			Assign(sTemp);
			iPos = Find(pstrFrom, iPos + cchTo);
			nCount++;
		}
		return nCount;
	}

	int __cdecl Format(const __char * pstrFormat, ...)
	{
		this_type sFormat = pstrFormat;
		__char szBuffer[1024] = { 0 };
		va_list argList;
		va_start(argList, pstrFormat);
		int iRet = __wvnsprintf(szBuffer,1024,sFormat, argList);
		va_end(argList);
		Assign(szBuffer);
		return iRet;
	}
	int __cdecl FormatTinyBuf(const __char * pstrFormat, ...)
	{
		this_type sFormat = pstrFormat;
		__char szBuffer[_buf] = { 0 };
		va_list argList;
		va_start(argList, pstrFormat);
		int iRet = __wvnsprintf(szBuffer,_buf,sFormat, argList);
		va_end(argList);
		Assign(szBuffer);
		return iRet;
	}

	int __cdecl FormatV(const __char * pstrFormat, ...)
	{
		this_type sFormat = pstrFormat;
		__char szBuffer[1024] = { 0 };
		va_list argList;
		va_start(argList, pstrFormat);
		int iRet = __vsprintf(szBuffer,1024,sFormat, argList);
		va_end(argList);
		Assign(szBuffer);
		return iRet;
	}

	int __cdecl FormatVTinyBuf(const __char * pstrFormat, ...)
	{
		this_type sFormat = pstrFormat;
		__char szBuffer[_buf] = { 0 };
		va_list argList;
		va_start(argList, pstrFormat);
		int iRet = __vsprintf(szBuffer,_buf,sFormat, argList);
		va_end(argList);
		Assign(szBuffer);
		return iRet;
	}

	int FindOneOf( LPCTSTR lpszCharSet ) const
	{
		if(lpszCharSet==NULL || *lpszCharSet==0)
			return -1;
		return __strcspn(m_pstr,lpszCharSet);
	}
	this_type& TrimRight( LPCTSTR pszTargets )
	{
		if(pszTargets==NULL || *pszTargets==0)
			return *this;

		__char* psz = m_pstr;
		__char* pszLast = NULL;

		while( *psz != 0 )
		{
			if( __strchr( pszTargets, *psz ) != NULL )
			{
				if( pszLast == NULL )
				{
					pszLast = psz;
				}
			}
			else
			{
				pszLast = NULL;
			}
			psz=__CharNext(psz);
		}

		if( pszLast != NULL )
		{
			// truncate at left-most matching character  
			ReleaseBuffer(pszLast-m_pstr);
		}

		return( *this );
	}
	this_type SpanIncluding( LPCTSTR lpszCharSet ) const
	{
		if(lpszCharSet==NULL || *lpszCharSet==0)
			return this_type();
		return Left(__strspn(m_pstr,lpszCharSet));
	}
protected:
	__char * m_pstr;
	__char m_szBuffer[_buf];

	int m_alloc;
};

typedef CStdStringBasic<char> CStdStringA;
typedef CStdStringBasic<WCHAR> CStdStringW;
typedef CStdStringBasic<TCHAR> CStdString;
