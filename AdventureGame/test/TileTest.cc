#include <Tile.h>

#include <gtest/gtest.h>

namespace {
struct TestData
{
    TileE type;
    std::string str;
};

class TileRepresentantionTest : public testing::TestWithParam<TestData>
{
public:
    TileE getType() const
    {
        return GetParam().type;
    }

    const std::string& getRepresentation() const
    {
        return GetParam().str;
    }
};
}

TEST_P(TileRepresentantionTest, verifyTilesCanBeRepresentedAsString)
{
    Tile tile;
    tile.set(getType());
    EXPECT_EQ(getRepresentation(), tile.toString());
}

TEST_P(TileRepresentantionTest, verifyTilesCanContainTreasure)
{
    Tile tile;
    tile.set(getType());
    tile.setTreasure();
    EXPECT_TRUE(tile.isTreasure());
    EXPECT_TRUE(tile.toString().find('*') != std::string::npos);
}

INSTANTIATE_TEST_SUITE_P(
    validTypes,
    TileRepresentantionTest,
    testing::Values(TestData{TileE::Empty, ". "},
                    TestData{TileE::Adventurer, "o "},
                    TestData{TileE::Monster, "@ "},
                    TestData{TileE::Trap, "# "})
);
