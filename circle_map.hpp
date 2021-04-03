#pragma once

#include <boost/circular_buffer.hpp>
#include <boost/algorithm/find_backward.hpp>
#include <algorithm>

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
	using reference_internal_data = std::pair<key_type, mapped_type>&;
	using const_reference_internal_data = const std::pair<key_type, mapped_type>&;

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

	bool contains(key_type const& k, bool reverseFind = false) const
	{
		return reverseFind ? rfind(k) != mBuffer.cend() : find(k) != mBuffer.cend();
	}

	void push_back(key_type k, mapped_type v)
	{
		auto found = find(k);
		if (found == std::end(mBuffer)) {
			mBuffer.push_back(std::make_pair(std::move(k), std::move(v)));
		}
		else {
			found->second = v;
		}
	}

	auto get_and_pop_front()
	{
		BOOST_ASSERT(!mBuffer.empty());
		internal_data item = mBuffer.front();
		mBuffer.pop_front();
		return item;
	}

private:
	auto find(key_type const& k) const
	{
		return std::ranges::find_if(mBuffer, [&k](auto const& item) {
			return k == item.first;
			});
	}

	auto find(key_type const& k)
	{
		return std::ranges::find_if(mBuffer, [&k](auto const& item) {
			return k == item.first;
			});
	}

	auto rfind(key_type const& k) const
	{
		return boost::algorithm::find_if_backward(mBuffer, [&k](auto const& item) {
			return k == item.first;
			});
	}

	auto rfind(key_type const& k)
	{
		return boost::algorithm::find_if_backward(mBuffer, [&k](auto const& item) {
			return k == item.first;
			});
	}
};