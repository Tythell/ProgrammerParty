#include <DungeonBuilder.h>

#include <gtest/gtest.h>

TEST(DunegonBuilderTest, printTheMap)
{
    const auto map = DungeonBuilder().
                        setDimensions(10u, 10u).
                        setStartPosition(0u, 3u).
                        setMonster(5u, 5u).
                        setTreasure(7u, 8u).
                        setTraps({{6u, 8u}, {7u, 9u}}).
                        build();
    map.print();
}


TEST(DunegonBuilderTest, printTheMapFromText)
{
    const auto map = DungeonBuilder().parseFromString("10 11\n0 3\n7 8\n5 5\n6 8\n7 9");
    map.print();
}

TEST(DunegonBuilderTest, printTheMapFromFile)
{
    const auto map = DungeonBuilder().parseFromFile("input.txt");
    const std::string desiredMap = 
//   0 1 2 3 4 5 6 7 8 9
    ". . . . . . . . . . \n" // 0
    ". . . . . . . . . . \n" // 1
    ". . . . . . . . . . \n" // 2
    "o . . . . . . . . . \n" // 3
    ". . . . . . . . . . \n" // 4
    ". . . . . @ . . . . \n" // 5
    ". . . . . . . . . . \n" // 6
    ". . . . . . . . . . \n" // 7
    ". . . . . . # .*. . \n" // 8
    ". . . . . . . # . . \n" // 9
    ". . . . . . . . . . \n";// 10

    EXPECT_EQ(desiredMap, map.toString());
}
