#include "coordinate.h"
#include "Tile.h"
#include "Dungeon.h"
#include "DungeonBuilder.h"

#include <gtest/gtest.h>

#include <string>

using WayToTreasure = std::string;

class Game
{
public:
    WayToTreasure run(const std::string &file)
    {
        auto dungeon = DungeonBuilder().parseFromFile("input.txt");
        dungeon.print();
        return {};
    }
};

TEST(AdventureGameTest, readInputToGameAndPrintIt)
{
    Game game;
    game.run("input.txt");
}
