#pragma once

#include <Debug.h>

#include <smart_ptr\impl\shared_count.h>

template<typename T,typename D=deleter_array<T>>
class shared_array
{
public:
	typedef T value_type;
	typedef T* pointer;
	typedef const T const_value_type;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;

private:
	shared_count<T,D> pn;
	pointer px;

public:

	explicit shared_array(pointer p=0): px(p), pn(p)
	{
	}

	shared_array( const shared_array<T,D>& sp): px( sp.px ), pn( sp.pn )
	{
	}

	~shared_array()
	{
	}

	pointer get() const
	{
		return px;
	}

	reference operator[](int i) const
	{
		ASSERT(px!=0);
		ASSERT(i>=0);
		return *px;
	}

	operator bool() const
	{
		return px !=0;
	}

	void reset(pointer p=0)
	{
		ASSERT(p!=px);
		shared_array<T,D>(p).swap(*this);
	}
	void reset(const shared_array<T,D>& sp)
	{
		shared_array<T,D>(sp).swap(*this);
	}

	const shared_array<T,D>& operator=(const shared_array<T,D>& sp)
	{
		px = sp.px;
		pn = sp.pn;
		return *this;
	}

	void swap(shared_array<T,D>& sp)
	{
		T * tmp = sp.px;
		sp.px = px;
		px = tmp;

		pn.swap(sp.pn);
	}
	bool unique() const
	{
		return pn.unique();
	}

	long use_count() const
	{
		return pn.use_count();
	}
};

