#pragma once

#include <Debug.h>

template<class T>
class scoped_ptr
{
private:
	scoped_ptr(scoped_ptr const &);
	void operator=(scoped_ptr const &);

	T * px;
public:
	typedef scoped_ptr<T> this_type;
	typedef T element_type;

	explicit scoped_ptr( T * p = 0 ) : px( p )
	{
	}
	~scoped_ptr()
	{
		if(px!=0)
			delete px; 
	}
	void reset(T * p = 0)
	{
		ASSERT( p == 0 || p != px );
		this_type(p).swap(*this);
	}

	T & operator*() const
	{
		ASSERT( px != 0 );
		return *px;
	}

	T * operator->() const
	{
		ASSERT( px != 0 );
		return px;
	}

	T * get() const
	{
		return px;
	}

	void swap(scoped_ptr & b)
	{
		T * tmp = b.px;
		b.px = px;
		px = tmp;
	}

	operator bool () const
	{
		return px != 0;
	}
};
