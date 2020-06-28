#pragma once

#include <thread\InterlockedInt.h>

class ref_count:public CInterlockedInt
{
public:
	ref_count(LONG l_int=0):CInterlockedInt(l_int){}
	virtual ~ref_count(){}

	virtual void dispose() = 0;
	void destroy()
	{
		delete this;
	}
	void release()
	{
		ASSERT(*this>0);
		if(--(*this) == 0)
		{
			dispose();
			destroy();
		}
	}
};

template <typename T,typename D>
class ref_count_impl : public ref_count
{
public:
	typedef T* pointer;
  
private:
	pointer px;

public:
	explicit ref_count_impl( pointer p) : 
		px(p)
,		ref_count(1)
	{
	}

    ~ref_count_impl()
	{
	}

	inline void dispose()
    {
		if(px!=0)
			D()(px);
    }
};




