#include "circle_map2.hpp"
#include <gtest/gtest.h>
#include <cstdlib>
#include <string>
#include <array>

using key = std::string;
using value = int;
using test_map = circle_map2<key, value>;

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(circle_map, constructor)
{
	test_map cm(2); 
	ASSERT_EQ(cm.capacity(), 2);
	ASSERT_EQ(cm.size(), 0);
	ASSERT_TRUE(cm.empty());
}

TEST(circle_map, push_back_normal)
{
	test_map cm(2);
	cm.push_back("a", 1);
	ASSERT_TRUE(!cm.empty());
}

TEST(circle_map, push_back_duplicate)
{
	test_map cm(2);
	cm.push_back("a", 1);
	cm.push_back("a", 2);
	auto item = cm.get_and_pop_front();
	ASSERT_EQ(item->second, 2);
}

TEST(circle_map, pop_front_normal)
{
	test_map cm(2);
	cm.push_back("a", 1);
	cm.push_back("2", 2);
	auto item = cm.get_and_pop_front();
	ASSERT_EQ(item->first, "a");
	ASSERT_EQ(item->second, 1);
	ASSERT_EQ(1, cm.size());
}

TEST(circle_map, pop_front_empty_map)
{
	test_map cm(2);
	auto item = cm.get_and_pop_front();
	ASSERT_TRUE(!item);
}

TEST(circle_map, contains)
{
	test_map cm(2);
	cm.push_back("a", 1);
	cm.push_back("b", 2);
	cm.push_back("c", 3);
	ASSERT_TRUE(cm.contains("c"));
}

TEST(circle_map, contains_reverse_find)
{
	test_map cm(2);
	cm.push_back("a", 1);
	cm.push_back("b", 2);
	cm.push_back("c", 3);
	ASSERT_TRUE(cm.contains("c"));
}

TEST(circle_map, contains_empty_map)
{
	test_map cm(2);
	ASSERT_TRUE(!cm.contains("c"));
}

TEST(circle_map, contains_reverse_empty_map)
{
	test_map cm(2);
	ASSERT_TRUE(!cm.contains("c", true));
}

TEST(circle_map, erase_empty_map)
{
	test_map cm(2);
	auto it = cm.erase("c");
	ASSERT_TRUE(!it.m_it);
}

TEST(circle_map, erase)
{
	test_map cm(2);
	cm.push_back("a", 1);
	cm.push_back("b", 2);
	cm.push_back("c", 3);
	cm.erase("c");
	ASSERT_FALSE(cm.contains("c"));
	ASSERT_EQ(cm.size(), 1);
}

TEST(circle_map, find)
{
	test_map cm(2);
	cm.push_back("a", 1);
	cm.push_back("b", 2);
	auto const& found = cm.find("a");
	ASSERT_EQ(*found, 1);
}

TEST(circle_map, find_empty_map)
{
	test_map cm(2);
	auto const& found = cm.find("a");
	ASSERT_TRUE(!found);
}

TEST(circle_map, find_if)
{
	test_map cm(2);
	cm.push_back("a", 1);
	cm.push_back("b", 2);
	auto const& found = cm.find_if([](auto const& item) {
		return item.second == 1;
		});
	ASSERT_EQ(*found, 1);
}

TEST(circle_map, find_if_empty_map)
{
	test_map cm(2);
	auto const& found = cm.find_if([](auto const& item) {
		return item.second == 1;
		});
	ASSERT_TRUE(!found);
}

TEST(circle_map, rfind_if)
{
	test_map cm(2);
	cm.push_back("a", 1);
	cm.push_back("b", 2);
	auto const& found = cm.rfind_if([](auto const& item) {
		return item.second == 1;
		});
	ASSERT_EQ(*found, 1);
}

TEST(circle_map, rfind_if_empty_map)
{
	test_map cm(2);
	auto const& found = cm.rfind_if([](auto const& item) {
		return item.second == 1;
		});
	ASSERT_TRUE(!found);
}

TEST(circle_map, traversal)
{
	std::array<int, 2> expected{ 1,2 };
	test_map cm(2);
	cm.push_back("a", 1);
	cm.push_back("b", 2);
	cm.traversal([& expected](auto const& item) {
		static int i = 0;
		ASSERT_EQ(expected[i++], item.second);
		});
}

TEST(circle_map, traversal_empty_map)
{
	std::array<int, 2> expected{ 1,2 };
	test_map cm(2);
	cm.traversal([&expected](auto const& item) {
		ASSERT_TRUE(false);
		});
	ASSERT_TRUE(true);
}

TEST(circle_map, rtraversal)
{
	std::array<int, 2> expected{ 2, 1 };
	test_map cm(2);
	cm.push_back("a", 1);
	cm.push_back("b", 2);
	cm.rtraversal([&expected](auto const& item) {
		static int i = 0;
		ASSERT_EQ(expected[i++], item.second);
		});
}
