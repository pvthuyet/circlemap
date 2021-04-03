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
	using internal_data = std::pair<key_type, mapped_type>;

private:
	boost::circular_buffer<internal_data> mBuffer;

public:
	circle_map(size_type capacity):
		mBuffer(capacity)
	{
	}

	auto capacity() const
	{
		return mBuffer.capacity();
	}

	auto size() const
	{
		return mBuffer.size();
	}

	bool empty() const
	{
		return mBuffer.empty();
	}

	void push_back(key_type k, mapped_type v)
	{
		mBuffer.push_back(std::make_pair(std::move(k), std::move(v)));
	}

	auto pop_front()
	{
		BOOST_ASSERT(!mBuffer.empty());
		internal_data item = mBuffer.front();
		mBuffer.pop_front();
		return item;
	}
};