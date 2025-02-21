#include <Dungeon.h>
#include <DungeonBuilder.h>

#include <gtest/gtest.h>

TEST(DungeonTest, playerIsNotAbleToTakeAStepTowardsWestBecauseOfTheWall)
{
    auto map = DungeonBuilder().
                        setDimensions(10u, 10u).
                        setStartPosition(0u, 3u).
                        setMonster(5u, 5u).
                        setTreasure(0u, 4u).
                        setTraps({{6u, 8u}, {7u, 9u}}).
                        build();
    map.print();
    EXPECT_EQ(std::set<FeelingE>({FeelingE::Bounce}), map.takeStep(DirectionE::West));
}

TEST(DungeonTest, playerIsNotAbleToTakeAStepTowardsSouthBecauseOfTheWall)
{
    auto map = DungeonBuilder().
                        setDimensions(10u, 10u).
                        setStartPosition(0u, 9u).
                        setMonster(5u, 5u).
                        setTreasure(0u, 4u).
                        setTraps({{6u, 8u}, {7u, 9u}}).
                        build();
    map.print();
    EXPECT_EQ(std::set<FeelingE>({FeelingE::Bounce}), map.takeStep(DirectionE::South));
}

TEST(DungeonTest, playerIsNotAbleToTakeAStepTowardsNorthBecauseOfTheWall)
{
    auto map = DungeonBuilder().
                        setDimensions(10u, 10u).
                        setStartPosition(0u, 0u).
                        setMonster(5u, 5u).
                        setTreasure(0u, 4u).
                        setTraps({{6u, 8u}, {7u, 9u}}).
                        build();
    map.print();
    EXPECT_EQ(std::set<FeelingE>({FeelingE::Bounce}), map.takeStep(DirectionE::North));
}

TEST(DungeonTest, playerIsNotAbleToTakeAStepTowardsEastBecauseOfTheWall)
{
    auto map = DungeonBuilder().
                        setDimensions(10u, 10u).
                        setStartPosition(9u, 0u).
                        setMonster(5u, 5u).
                        setTreasure(0u, 4u).
                        setTraps({{6u, 8u}, {7u, 9u}}).
                        build();
    map.print();
    EXPECT_EQ(std::set<FeelingE>({FeelingE::Bounce}), map.takeStep(DirectionE::East));
}

TEST(DungeonTest, playerIsAbleToTakeAStepTowardsNorthWhichIsNonTreasure)
{ 
    auto map = DungeonBuilder().
                        setDimensions(10u, 10u).
                        setStartPosition(0u, 3u).
                        setMonster(5u, 5u).
                        setTreasure(0u, 4u).
                        setTraps({{6u, 8u}, {7u, 9u}}).
                        build();
    map.print();

    EXPECT_EQ(std::set<FeelingE>({}), map.takeStep(DirectionE::North));
}

TEST(DungeonTest, playerIsAbleToTakeAStepTowardsSouthWhichIsNonTreasure)
{ 
    auto map = DungeonBuilder().
                        setDimensions(10u, 10u).
                        setStartPosition(1u, 3u).
                        setMonster(5u, 5u).
                        setTreasure(0u, 4u).
                        setTraps({{6u, 8u}, {7u, 9u}}).
                        build();
    map.print();

    EXPECT_EQ(std::set<FeelingE>({}), map.takeStep(DirectionE::South));
}

TEST(DungeonTest, playerIsAbleToTakeAStepTowardsEastWhichIsNonTreasure)
{ 
    auto map = DungeonBuilder().
                        setDimensions(10u, 10u).
                        setStartPosition(0u, 3u).
                        setMonster(5u, 5u).
                        setTreasure(0u, 4u).
                        setTraps({{6u, 8u}, {7u, 9u}}).
                        build();
    map.print();

    EXPECT_EQ(std::set<FeelingE>({}), map.takeStep(DirectionE::East));
}

TEST(DungeonTest, playerIsAbleToTakeAStepTowardsWestWhichIsNonTreasure)
{ 
    auto map = DungeonBuilder().
                        setDimensions(10u, 10u).
                        setStartPosition(1u, 3u).
                        setMonster(5u, 5u).
                        setTreasure(0u, 4u).
                        setTraps({{6u, 8u}, {7u, 9u}}).
                        build();
    map.print();

    EXPECT_EQ(std::set<FeelingE>({}), map.takeStep(DirectionE::West));
}

TEST(DungeonTest, playerIsAbleToTakeAStepSouthTowardsTreasure)
{ 
    auto map = DungeonBuilder().
                        setDimensions(10u, 10u).
                        setStartPosition(0u, 3u).
                        setMonster(5u, 5u).
                        setTreasure(0u, 4u).
                        setTraps({{6u, 8u}, {7u, 9u}}).
                        build();
    map.print();
    EXPECT_EQ(std::set<FeelingE>({FeelingE::Shining}), map.takeStep(DirectionE::South));
}

TEST(DungeonTest, playerIsAbleToTakeAStepNorthTowardsTreasure)
{ 
    auto map = DungeonBuilder().
                        setDimensions(10u, 10u).
                        setStartPosition(0u, 3u).
                        setMonster(5u, 5u).
                        setTreasure(0u, 2u).
                        setTraps({{6u, 8u}, {7u, 9u}}).
                        build();
    map.print();
    EXPECT_EQ(std::set<FeelingE>({FeelingE::Shining}), map.takeStep(DirectionE::North));
}

TEST(DungeonTest, playerIsAbleToTakeAStepWestTowardsTreasure)
{ 
    auto map = DungeonBuilder().
                        setDimensions(10u, 10u).
                        setStartPosition(1u, 3u).
                        setMonster(5u, 5u).
                        setTreasure(0u, 3u).
                        setTraps({{6u, 8u}, {7u, 9u}}).
                        build();
    map.print();
    EXPECT_EQ(std::set<FeelingE>({FeelingE::Shining}), map.takeStep(DirectionE::West));
}

TEST(DungeonTest, playerIsAbleToTakeAStepEastTowardsTreasure)
{ 
    auto map = DungeonBuilder().
                        setDimensions(10u, 10u).
                        setStartPosition(1u, 3u).
                        setMonster(5u, 5u).
                        setTreasure(2u, 3u).
                        setTraps({{6u, 8u}, {7u, 9u}}).
                        build();
    map.print();
    EXPECT_EQ(std::set<FeelingE>({FeelingE::Shining}), map.takeStep(DirectionE::East));
}

TEST(DungeonTest, playerCanSenseWindyTrap)
{ 
    auto map = DungeonBuilder().
                        setDimensions(10u, 10u).
                        setStartPosition(0u, 0u).
                        setMonster(5u, 5u).
                        setTreasure(2u, 3u).
                        setTraps({{2u, 0u}, {7u, 9u}}).
                        build();
    map.print();
    EXPECT_EQ(std::set<FeelingE>({FeelingE::Wind}), map.takeStep(DirectionE::East));
}