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