#include "circle_map.hpp"
#include <gtest/gtest.h>
#include <cstdlib>

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(example, test_case1)
{
	ASSERT_EQ(0, 0);
}