#pragma once

#include <boost/circular_buffer.hpp>
#include <boost/algorithm/find_backward.hpp>
#include <algorithm>
#include <optional>
#include <shared_mutex>

template<class Key, class T>
class circle_map
{
public:
	using key_type = Key;
	using mapped_type = T;
	using opt_mapped_type = std::optional<mapped_type>;
	using size_type = unsigned int;
	using reference = mapped_type&;
	using const_reference = const mapped_type&;
	using pair = std::pair<key_type, mapped_type>;
	using opt_pair = std::optional<pair>;

private:
	using buffer_type = boost::circular_buffer<pair>;
	buffer_type mBuffer;
	mutable std::shared_mutex mMutex;

public:
	circle_map(size_type capacity):
		mBuffer(capacity)
	{
	}

	auto capacity() const
	{
		std::shared_lock slock(mMutex);
		return mBuffer.capacity();
	}

	auto size() const
	{
		std::shared_lock slock(mMutex);
		return mBuffer.size();
	}

	bool empty() const
	{
		std::shared_lock slock(mMutex);
		return mBuffer.empty();
	}

	void push_back(key_type k, mapped_type v)
	{
		std::lock_guard lock(mMutex);
		auto found = find_internal(k);
		if (found == std::end(mBuffer)) {
			mBuffer.push_back(std::make_pair(std::move(k), std::move(v)));
		}
		else {
			found->second = v;
		}
	}

	opt_pair get_and_pop_front()
	{
		std::lock_guard lock(mMutex);
		if (!mBuffer.empty()) {
			pair item = mBuffer.front();
			mBuffer.pop_front();
			return std::make_optional(std::move(item));
		}
		return std::nullopt;
	}

	bool contains(key_type const& k, bool reverseFind = false) const
	{
		std::shared_lock slock(mMutex);
		return reverseFind ? rfind_internal(k) != mBuffer.cend() : find_internal(k) != mBuffer.cend();
	}

	auto erase(key_type const& k)
	{
		std::lock_guard lock(mMutex);
		if (!mBuffer.empty()) {
			return mBuffer.erase(find_internal(k));
		}
		return mBuffer.end();
	}

	opt_mapped_type find(key_type const& k) const
	{
		std::shared_lock slock(mMutex);
		auto it = find_internal(k);
		if (mBuffer.cend() != it) {
			return std::make_optional(it->second);
		}
		return std::nullopt;
	}

	template<class Predicate>
	opt_mapped_type find_if(Predicate pre) const
	{
		std::shared_lock slock(mMutex);
		auto it = std::ranges::find_if(mBuffer, pre);
		if (mBuffer.cend() != it) {
			return std::make_optional(it->second);
		}
		return std::nullopt;
	}

	template<class Predicate>
	opt_mapped_type rfind_if(Predicate pre) const
	{
		std::shared_lock slock(mMutex);
		auto it = boost::algorithm::find_if_backward(mBuffer, pre);
		if (mBuffer.cend() != it) {
			return std::make_optional(it->second);
		}
		return std::nullopt;
	}

	template<class Function>
	void traversal(Function func) const
	{
		std::shared_lock slock(mMutex);
		std::ranges::for_each(mBuffer, func);
	}

	template<class Function>
	void rtraversal(Function func) const
	{
		std::shared_lock slock(mMutex);
		std::ranges::for_each(std::crbegin(mBuffer), std::crend(mBuffer), func);
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