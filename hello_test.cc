#include <gtest/gtest.h>
#include <iostream>

// TEST(HelloTest, BasicAssertions) {
//   // Expect two strings not to be equal.
//     EXPECT_STRNE("hello", "world");
//   // Expect equality.
//     EXPECT_EQ(9 * 6, 42);
//     // TEST_COUT("hello world from test\n");

// }

TEST(testing, fail)
{
	EXPECT_EQ(false, true);
}

TEST(testing, succeed)
{
	EXPECT_EQ(true, true);
}

