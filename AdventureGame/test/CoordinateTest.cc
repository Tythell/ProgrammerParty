#include <coordinate.h>

#include <gtest/gtest.h>

TEST(CoordinateTest, verifyCoordinatesCanBeEqual)
{
    Coordinate x{10, 10};
    ASSERT_TRUE(x == x);
}

TEST(CoordinateTest, verifyCoordinatesCanBeDifferent)
{
    Coordinate x{10, 10};
    Coordinate y(0, 10);
    ASSERT_FALSE(y == x);
}
