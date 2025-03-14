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

TEST(DungeonTest, playerCanSenseMonster)
{ 
    auto map = DungeonBuilder().
                        setDimensions(10u, 10u).
                        setStartPosition(0u, 0u).
                        setMonster(2u, 0u).
                        setTreasure(2u, 3u).
                        setTraps({{2u, 5u}, {7u, 9u}}).
                        build();
    map.print();
    EXPECT_EQ(std::set<FeelingE>({FeelingE::Smell}), map.takeStep(DirectionE::East));
}

TEST(DungeonTest, playerCanSenseMonsterTrapAndTreasure)
{ 
    auto map = DungeonBuilder().
                        setDimensions(10u, 10u).
                        setStartPosition(0u, 0u).
                        setMonster(2u, 0u).
                        setTreasure(1u, 0u).
                        setTraps({{1u, 1u}, {7u, 9u}}).
                        build();
    map.print();
    EXPECT_EQ(std::set<FeelingE>({FeelingE::Smell, FeelingE::Shining, FeelingE::Wind}), map.takeStep(DirectionE::East));
}

TEST(DungeonTest, playerCanSenseNothingButNeighbourHasTreasure)
{ 
    auto map = DungeonBuilder().
                        setDimensions(10u, 10u).
                        setStartPosition(0u, 0u).
                        setMonster(3u, 3u).
                        setTreasure(1u, 1u).
                        setTraps({{2u, 5u}, {7u, 9u}}).
                        build();
    map.print();
    EXPECT_TRUE(map.takeStep(DirectionE::East).empty());
}

TEST(DungeonTest, playerCanSenseMonsterTrapAndTreasureAfterHittingTheWall)
{ 
    auto map = DungeonBuilder().
                        setDimensions(10u, 10u).
                        setStartPosition(1u, 0u).
                        setMonster(2u, 0u).
                        setTreasure(1u, 0u).
                        setTraps({{1u, 1u}, {7u, 9u}}).
                        build();
    map.print();
    EXPECT_EQ(std::set<FeelingE>({FeelingE::Smell, FeelingE::Shining, FeelingE::Wind, FeelingE::Bounce}), map.takeStep(DirectionE::North));
}

TEST(DungeonTest, verifyPlayerCantMoveOutOfBounds)
{ 
    auto map = DungeonBuilder().
                        setDimensions(10u, 10u).
                        setStartPosition(4u, 3u).
                        setMonster(2u, 0u).
                        setTreasure(1u, 0u).
                        setTraps({{1u, 1u}, {7u, 9u}}).
                        build();
    
    map.print();
    map.takeStep(DirectionE::North);
    map.takeStep(DirectionE::North);
    map.takeStep(DirectionE::North);
    EXPECT_EQ(std::set<FeelingE>({FeelingE::Bounce}), map.takeStep(DirectionE::North));
}

TEST(DungeonTest, playerCanBounceBackAndStepToSenseMonsterTrapAndTreasure)
{ 
    auto map = DungeonBuilder().
                        setDimensions(10u, 10u).
                        setStartPosition(0u, 0u).
                        setMonster(2u, 0u).
                        setTreasure(1u, 0u).
                        setTraps({{1u, 1u}, {7u, 9u}}).
                        build();
    map.print();
    EXPECT_EQ(std::set<FeelingE>({FeelingE::Bounce}), map.takeStep(DirectionE::North));
    EXPECT_EQ(std::set<FeelingE>({FeelingE::Smell, FeelingE::Shining, FeelingE::Wind}), map.takeStep(DirectionE::East));
}

TEST(DungeonTest, playerCanPickTheTreasureUp)
{ 
    auto map = DungeonBuilder().
                        setDimensions(10u, 10u).
                        setStartPosition(0u, 0u).
                        setMonster(2u, 0u).
                        setTreasure(0u, 0u).
                        setTraps({{1u, 1u}, {7u, 9u}}).
                        build();
    map.print();
    EXPECT_TRUE(map.pickTheTreasure());
    EXPECT_FALSE(map.pickTheTreasure());
}

TEST(DungeonTest, playerCanShoot)
{ 
    auto map = DungeonBuilder().
                        setDimensions(10u, 10u).
                        setStartPosition(0u, 0u).
                        setMonster(2u, 0u).
                        setTreasure(4u, 0u).
                        setTraps({{1u, 1u}, {7u, 9u}}).
                        build();
    map.print();
    EXPECT_TRUE(map.shoot(DirectionE::East));
    EXPECT_EQ(std::set<FeelingE>({FeelingE::Wind}), map.takeStep(DirectionE::East));
}

TEST(DungeonTest, playerCanShootAndMiss)
{ 
    auto map = DungeonBuilder().
                        setDimensions(10u, 10u).
                        setStartPosition(0u, 0u).
                        setMonster(2u, 0u).
                        setTreasure(4u, 0u).
                        setTraps({{1u, 1u}, {7u, 9u}}).
                        build();
    map.print();
    EXPECT_FALSE(map.shoot(DirectionE::South));
}

TEST(DungeonTest, playerCanShootTwice)
{ 
    auto map = DungeonBuilder().
                        setDimensions(10u, 10u).
                        setStartPosition(0u, 0u).
                        setMonster(2u, 0u).
                        setTreasure(4u, 0u).
                        setTraps({{1u, 1u}, {7u, 9u}}).
                        build();
    map.print();
    EXPECT_FALSE(map.shoot(DirectionE::South));
    EXPECT_FALSE(map.shoot(DirectionE::East));
    EXPECT_EQ(std::set<FeelingE>({FeelingE::Wind, FeelingE::Smell}), map.takeStep(DirectionE::East));
}