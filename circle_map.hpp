#pragma once

#include <boost/circular_buffer.hpp>

template<class Key, class T>
class circle_map
{
public:
	using key_type = Key;
	using mapped_type = T;
	using size_type = unsigned int;
	using reference = mapped_type&;
	using const_reference = const mapped_type&;

private:
	boost::circular_buffer<T> mBuffer;

public:
	circle_map(size_type capacity):
		mBuffer(capacity)
	{
	}
};