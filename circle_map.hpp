#pragma once

#include <boost/circular_buffer.hpp>
#include <boost/algorithm/find_backward.hpp>
#include <algorithm>
#include <optional>

template<class Key, class T>
class circle_map
{
public:
	using key_type = Key;
	using mapped_type = T;
	using size_type = unsigned int;
	using reference = mapped_type&;
	using const_reference = const mapped_type&;
	using opt_cref = std::optional<std::reference_wrapper<const mapped_type>>;
	using pair = std::pair<key_type, mapped_type>;

private:
	using buffer_type = boost::circular_buffer<pair>;
	buffer_type mBuffer;

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
		return reverseFind ? rfind_internal(k) != mBuffer.cend() : find_internal(k) != mBuffer.cend();
	}

	opt_cref find(key_type const& k) const
	{
		auto it = find_internal(k);
		if (mBuffer.cend() != it) {
			return opt_cref{it->second};
		}
		return std::nullopt;
	}

	auto erase(key_type const& k)
	{
		if (!mBuffer.empty()) {
			return mBuffer.erase(find_internal(k));
		}
		return mBuffer.end();
	}

	void push_back(key_type k, mapped_type v)
	{
		auto found = find_internal(k);
		if (found == std::end(mBuffer)) {
			mBuffer.push_back(std::make_pair(std::move(k), std::move(v)));
		}
		else {
			found->second = v;
		}
	}

	std::optional<pair> get_and_pop_front()
	{
		if (!mBuffer.empty()) {
			pair item = mBuffer.front();
			mBuffer.pop_front();
			return std::make_optional(std::move(item));
		}
		return std::nullopt;
	}

private:
	auto find_internal(key_type const& k) const
	{
		return std::ranges::find_if(mBuffer, [&k](auto const& item) {
			return k == item.first;
			});
	}

	auto find_internal(key_type const& k)
	{
		return std::ranges::find_if(mBuffer, [&k](auto const& item) {
			return k == item.first;
			});
	}

	auto rfind_internal(key_type const& k) const
	{
		return boost::algorithm::find_if_backward(mBuffer, [&k](auto const& item) {
			return k == item.first;
			});
	}

	auto rfind_internal(key_type const& k)
	{
		return boost::algorithm::find_if_backward(mBuffer, [&k](auto const& item) {
			return k == item.first;
			});
	}
};