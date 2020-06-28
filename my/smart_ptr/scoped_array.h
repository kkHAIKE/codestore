#pragma once

#include <Debug.h>

template<class T>
class scoped_array
{
private:
	scoped_array(scoped_array const &);
	void operator=(scoped_array const &);

	T * px;
public:
	typedef scoped_array<T> this_type;
	typedef T element_type;

	explicit scoped_array( T * p = 0 ) : px( p )
	{
	}
	~scoped_array()
	{
		if(px!=0)
			delete[] px; 
	}
	void reset(T * p = 0)
	{
		ASSERT( p == 0 || p != px );
		this_type(p).swap(*this);
	}

	T & operator[](int i) const
	{
		ASSERT(px!=0);
		ASSERT(i>=0);
		return px[i];
	}

	T * get() const
	{
		return px;
	}

	void swap(scoped_array & b)
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
