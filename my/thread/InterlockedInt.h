#pragma once

class CInterlockedInt
{
protected:
	volatile LONG m_int;
public:
	CInterlockedInt(LONG l_int=0):
		m_int(l_int){};
	
	inline
	LONG operator++()
	{
		return InterlockedIncrement(&m_int);
	}

	inline
 	LONG operator++(int)
 	{
 		return InterlockedExchangeAdd(&m_int,1);
 	}

	inline
	LONG Inc()
	{
		return InterlockedIncrement(&m_int);
	}

	inline
	LONG operator--()
	{
		return InterlockedDecrement(&m_int);
	}

	inline
 	LONG operator--(int)
 	{
 		return InterlockedExchangeAdd(&m_int,-1);
 	}

	inline
	LONG Dec()
	{
		return InterlockedDecrement(&m_int);
	}

	inline
	LONG operator+=(LONG c)
	{
		return InterlockedExchangeAdd(&m_int,c)+c;
	}

	inline
	LONG Add(LONG c)
	{
		return InterlockedExchangeAdd(&m_int,c)+c;
	}

	inline
	LONG operator-=(LONG c)
	{
		return InterlockedExchangeAdd(&m_int,-c)-c;
	}

	inline
	LONG Sub(LONG c)
	{
		return InterlockedExchangeAdd(&m_int,-c)-c;
	}

	inline
	operator LONG()
	{
		return InterlockedExchangeAdd(&m_int,0);
	}

	inline
	LONG operator=(LONG c)
	{
		InterlockedExchange(&m_int,c);
		return c;
	}

	inline
	LONG Equal(LONG c)
	{
		InterlockedExchange(&m_int,c);
		return c;
	}

};

//////////////////////////////////////////////////////////////////////////
#if defined(_M_IA64) && !defined(RC_INVOKED)
class CInterlockedInt64
{
protected:
	volatile LONG64 m_int;
public:
	CInterlockedInt64(LONG64 l_int=0):
	  m_int(l_int){};

	  LONG64 operator++()
	  {
		  return InterlockedIncrement64(&m_int);
	  }
	  LONG64 operator++(int)
	  {
		  return InterlockedExchangeAdd64(&m_int,1);
	  }
	  LONG64 Inc()
	  {
		  return InterlockedIncrement64(&m_int);
	  }

	  LONG64 operator--()
	  {
		  return InterlockedDecrement64(&m_int);
	  }
	  LONG64 operator--(int)
	  {
		  return InterlockedExchangeAdd64(&m_int,-1);
	  }
	  LONG64 Dec()
	  {
		  return InterlockedDecrement64(&m_int);
	  }

	  LONG64 operator+=(LONG64 c)
	  {
		  return InterlockedExchangeAdd64(&m_int,c)+c;
	  }
	  LONG64 Add(LONG64 c)
	  {
		  return InterlockedExchangeAdd64(&m_int,c)+c;
	  }

	  LONG64 operator-=(LONG64 c)
	  {
		  return InterlockedExchangeAdd64(&m_int,-c)-c;
	  }
	  LONG64 Sub(LONG64 c)
	  {
		  return InterlockedExchangeAdd64(&m_int,-c)-c;
	  }

	  operator LONG64()
	  {
		  return InterlockedExchangeAdd64(&m_int,0);
	  }

	  LONG64 operator=(LONG64 c)
	  {
		  InterlockedExchange64(&m_int,c);
		  return c;
	  }
	  LONG64 Equal(LONG64 c)
	  {
		  InterlockedExchange64(&m_int,c);
		  return c;
	  }

};
#endif
