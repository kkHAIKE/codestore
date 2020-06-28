#pragma once

#include <Debug.h>

#include <smart_ptr\impl\shared_count.h>

template<typename T,typename D=deleter_ptr<T>>
class shared_ptr
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
  
  explicit shared_ptr(pointer p=0): px(p), pn(p)
    {
    }

  shared_ptr( const shared_ptr<T,D>& sp): px( sp.px ), pn( sp.pn )
    {
    }
  
  ~shared_ptr()
    {
    }
  
  pointer get() const
    {
      return px;
    }

  reference operator*() const
    {
	 ASSERT(px!=0);
      return *px;
    }
  
  pointer operator->() const
    {
	 ASSERT(px!=0);
      return px;
    }
  
  operator bool() const
    {
      return px !=0;
    }

  void reset(pointer p=0)
  {
	  ASSERT(p!=px);
	  shared_ptr<T,D>(p).swap(*this);
  }
  void reset(const shared_ptr<T,D>& sp)
  {
	  shared_ptr<T,D>(sp).swap(*this);
  }

  const shared_ptr<T,D>& operator=(const shared_ptr<T,D>& sp)
    {
      px = sp.px;
      pn = sp.pn;
	  return *this;
    }

  void swap(shared_ptr<T,D>& sp)
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

