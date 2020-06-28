#pragma once

#include <smart_ptr\impl\ref_count_impl.h>

template<typename T>
struct deleter_ptr
{
	void operator()(T* a)
	{
		ASSERT(a!=NULL);
		delete a;
	}
};

template<typename T>
struct deleter_array
{
	void operator()(T* a)
	{
		ASSERT(a!=NULL);
		delete[] a;
	}
};

template <typename T,typename D>
class shared_count
{
 private:
  ref_count *pi;
  
  public:
  explicit shared_count(T* p): pi(0)
    {
		if(p!=0)
			pi=new ref_count_impl<T,D>(p);
    }
  
  explicit shared_count( const shared_count<T,D>& sc ): pi( sc.pi )
    {
      if(pi!=0)
      {
	      ++(*pi);
      }
    }
  
   ~shared_count( )
    {
      if(pi!=0 )
      {
	       pi->release();
      }
    }
  
  const shared_count<T,D>& operator=( const shared_count<T,D>& r)
    {
      ref_count *tmp = r.pi;
      
      if(tmp!=pi)
      {
		 if(tmp!=0)
			++(*tmp);
	     if(pi!=0)
	     {
	       pi->release();
	     }
		 pi = tmp;
      }
	  return *this;
    }

  void swap(shared_count<T,D>& r)
  {
	  ref_count * tmp = r.pi;
	  r.pi = pi;
	  pi = tmp;
  }

  bool unique() const
  {
		return use_count() == 1;
  }

  long use_count() const
  {
		return pi != 0? *pi: 0;
  }

};

