#include "circle_map.hpp"
#include <gtest/gtest.h>
#include <cstdlib>
#include <string>

using key = std::string;
using value = int;

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(circle_map, constructor)
{
	circle_map<key, value> cm(2); 
	ASSERT_EQ(cm.capacity(), 2);
	ASSERT_EQ(cm.size(), 0);
	ASSERT_TRUE(cm.empty());
}

TEST(circle_map, contains)
{
	circle_map<key, value> cm(2);
	cm.push_back("a", 1);
	cm.push_back("b", 2);
	cm.push_back("c", 3);
	ASSERT_TRUE(cm.contains("c"));
}

TEST(circle_map, contains_reverse_find)
{
	circle_map<key, value> cm(2);
	cm.push_back("a", 1);
	cm.push_back("b", 2);
	cm.push_back("c", 3);
	ASSERT_TRUE(cm.contains("c", true));
}

TEST(circle_map, find)
{
	circle_map<key, value> cm(2);
	cm.push_back("a", 1);
	cm.push_back("b", 2);
	auto const& found = cm.find("a");
	ASSERT_EQ(found, 1);
}

TEST(circle_map, find_empty_map)
{
	circle_map<key, value> cm(2);
	auto const& found = cm.find("a");
	ASSERT_TRUE(!found);
}

TEST(circle_map, erase_empty_map)
{
	circle_map<key, value> cm(2);
	auto it = cm.erase("c");
	ASSERT_TRUE(!it.m_it);
}

TEST(circle_map, erase)
{
	circle_map<key, value> cm(2);
	cm.push_back("a", 1);
	cm.push_back("b", 2);
	cm.push_back("c", 3);
	cm.erase("c");
	ASSERT_FALSE(cm.contains("c"));
	ASSERT_EQ(cm.size(), 1);
}

TEST(circle_map, push_back_normal)
{
	circle_map<key, value> cm(2);
	cm.push_back("a", 1);
	ASSERT_TRUE(!cm.empty());
}

TEST(circle_map, push_back_duplicate)
{
	circle_map<key, value> cm(2);
	cm.push_back("a", 1);
	cm.push_back("a", 2);
	auto item = cm.get_and_pop_front();
	ASSERT_EQ(item->second, 2);
}

TEST(circle_map, pop_front_normal)
{
	circle_map<key, value> cm(2);
	cm.push_back("a", 1);
	cm.push_back("2", 2);
	auto item = cm.get_and_pop_front();
	ASSERT_EQ(item->first, "a");
	ASSERT_EQ(item->second, 1);
	ASSERT_EQ(1, cm.size());
}

TEST(circle_map, pop_front_empty_map)
{
	circle_map<key, value> cm(2);
	auto item = cm.get_and_pop_front();
	ASSERT_TRUE(!item);
}