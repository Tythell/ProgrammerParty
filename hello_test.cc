#include <gtest/gtest.h>
#include <iostream>

// TEST(HelloTest, BasicAssertions) {
//   // Expect two strings not to be equal.
//     EXPECT_STRNE("hello", "world");
//   // Expect equality.
//     EXPECT_EQ(9 * 6, 42);
//     // TEST_COUT("hello world from test\n");

// }

TEST(testing, fail) {
  std::cout << "Hello test" << std::endl;
  EXPECT_EQ(false, true);
  EXPECT_THAT(false, Eq(true));
}

TEST(testing, succeed) { EXPECT_EQ(true, true); }
TEST(testing, 2Plus2Is4)
{
	EXPECT_EQ(4, 2 + 2);
}

