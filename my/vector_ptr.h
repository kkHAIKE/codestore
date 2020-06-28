#pragma once

#include <vector>

template<class T>
class vector_ptr:public std::vector<T*>
{
public:
	vector_ptr(bool outclear=true):std::vector<T*>(),m_outclear(outclear){}
	vector_ptr ( const vector_ptr<T>& x ):std::vector<T*>(x){}
	~vector_ptr()
	{
		if(m_outclear)
			clear_delete();
	}
	void clear_delete()
	{
		iterator it=begin();
		iterator End=end();
		for(;it!=End;++it)
		{
			delete *it;
		}
		clear();
	}
	iterator erase_delete ( iterator position )
	{
		delete *position;
		return erase(position);
	}
	iterator erase_delete ( iterator first, iterator last )
	{
		iterator it=first;
		for(;it!=last;++it)
		{
			delete *it;
		}
		return erase(first,last);
	}
protected:
	bool m_outclear;
};