#include <gtest/gtest.h>

#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

struct Coordinate
{
    std::uint32_t x;
    std::uint32_t y;

    bool operator==(const Coordinate& rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }
};

enum class TileE
{
    Empty,
    Adventurer,
    Monster,
    Treasure,
    Trap
};

class Tile
{
public:
    void set(TileE type)
    {
        m_type = type;
    }

    std::string to_string() const
    {
        switch (m_type)
        {
            case TileE::Empty : return ". ";
            case TileE::Adventurer : return "o ";
            case TileE::Monster : return "@ ";
            case TileE::Treasure : return "* ";
            case TileE::Trap : return "# ";
        }
        std::terminate();
    }

    bool isTreasure() const
    {
        return m_type == TileE::Treasure;
    }

private:
    TileE m_type{TileE::Empty};
};

std::ostream& operator<<(std::ostream& out, const Tile& tile)
{
    out << tile.to_string();
    return out;
}

enum class FeelingE
{
    Shining,
    Smell,
    Wind,
    Bounce
};

enum class DirectionE : std::uint8_t
{
    North,
    East,
    South,
    West
};

constexpr std::string DIRECTION[]
{
    "North",
    "East",
    "South",
    "West"
};

class Dungeon
{
public:
    Dungeon(const Coordinate& dimensions,
            const Coordinate& startPosition,
            const Coordinate& monster,
            const Coordinate& treasure,
            const std::vector<Coordinate>& traps) : 
            m_adventurer(startPosition)
    {
        m_map.resize(dimensions.y, std::vector<Tile>(dimensions.x));
        
        m_map.at(startPosition.y).at(startPosition.x).set(TileE::Adventurer);
        m_map.at(monster.y).at(monster.x).set(TileE::Monster);
        m_map.at(treasure.y).at(treasure.x).set(TileE::Treasure);
        for(const auto& trap : traps)
        {
            m_map.at(trap.y).at(trap.x).set(TileE::Trap);
        }
    }

    std::set<FeelingE> takeStep(DirectionE step)
    {
        std::set<FeelingE> feelings;
        std::cout << "Taking step towards: " << DIRECTION[static_cast<std::uint8_t>(step)] << "\n";
        if(!updateTheAdventurer(step))
        {
            feelings.insert(FeelingE::Bounce);
        }
        if (isTreasure())
        {
            feelings.insert(FeelingE::Shining);
        }

        print();
        return feelings;
    }
    void print() const
    {
        std::cout << toString();
    }
    std::string toString() const
    {
        std::stringstream ss;
        for(const auto& row : m_map)
        {
            for(const auto& tile : row)
            {
                ss << tile;
            }
            ss << std::endl;
        }
        return ss.str();
    }
    
private:
    Tile& getTile(const Coordinate& xy)
    {
        return m_map[xy.y][xy.x];
    }

    const Tile& getTile(const Coordinate& xy) const
    {
        return m_map.at(xy.y).at(xy.x);
    }

    bool updateTheAdventurer(DirectionE step)
    {
        //TODO maybe the step cannot be made
        switch(step){
            case DirectionE::North:
            m_adventurer.y--;
            break;
            case DirectionE::South:
            m_adventurer.y++;
            break;
            case DirectionE::East:
            m_adventurer.x++;
            break;
            case DirectionE::West:
            if(m_adventurer.x != 0)
            {
                m_adventurer.x--;
            }
            else
            {
                return false;
            }
            break;
        }
        return true;
    }

    bool isTreasure() const
    {
        return getTile(m_adventurer).isTreasure();
    }

    Coordinate m_adventurer;
    std::vector<std::vector<Tile>> m_map;
};

class DungeonBuilder
{
public:
    Dungeon build() const
    {
        return Dungeon{m_dimensions, m_startPosition, m_monster, m_treasure, m_traps};
    }

    DungeonBuilder& setDimensions(std::uint32_t x, std::uint32_t y)
    {
        m_dimensions = {x, y};
        return *this;
    }

    DungeonBuilder& setStartPosition(std::uint32_t x, std::uint32_t y)
    {
        m_startPosition = {x, y};
        return *this;
    }

    DungeonBuilder& setMonster(std::uint32_t x, std::uint32_t y)
    {
        m_monster = {x, y};
        return *this;
    }

    DungeonBuilder& setTreasure(std::uint32_t x, std::uint32_t y)
    {
        m_treasure = {x, y};
        return *this;
    }

    DungeonBuilder& setTraps(const std::vector<Coordinate>& traps)
    {
        m_traps = traps;
        return *this;
    }
    
    Dungeon parseFromFile(const std::string& path)
    {
        std::ifstream reader(path);
        assert(reader.is_open());
        return buildFromStream(reader);
    }

    Dungeon parseFromString(const std::string& input)
    {
        std::stringstream ss(input);
        return buildFromStream(ss);
    }

private:
    template<typename Stream>
    Dungeon buildFromStream(Stream& reader)
    {
        m_dimensions = toCoordinate(reader).value();
        m_startPosition = toCoordinate(reader).value();
        m_treasure = toCoordinate(reader).value();
        m_monster = toCoordinate(reader).value();

        auto trap = toCoordinate(reader);
        while (trap.has_value())
        {
            m_traps.push_back(trap.value());
            trap = toCoordinate(reader);
        }
        return build();
    }

    template<typename Stream>
    std::optional<Coordinate> toCoordinate(Stream& ss) const
    {
        std::string line;
        if (std::getline(ss, line))
        {
            return toCoordinateStr(line); 
        }
        return std::nullopt;   
    }

    Coordinate toCoordinateStr(const std::string& line) const
    {
         std::stringstream subss(line);
            std::uint32_t readNumberX, readNumberY;
            subss >> readNumberX;
            subss >> readNumberY;
            return {readNumberX, readNumberY}; 
    }

    Coordinate m_dimensions{10u, 10u};
    Coordinate m_startPosition{0u, 0u};
    Coordinate m_monster{5u, 5u};
    Coordinate m_treasure{8u, 8u};
    std::vector<Coordinate> m_traps;
};

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

TEST(AdventureGameTest, printTheMap)
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


TEST(AdventureGameTest, printTheMapFromText)
{
    const auto map = DungeonBuilder().parseFromString("10 11\n0 3\n7 8\n5 5\n6 8\n7 9");
    map.print();
}

TEST(AdventureGameTest, printTheMapFromFile)
{
    const auto map = DungeonBuilder().parseFromFile("input.txt");
    std::string desiredMap = 
//   0 1 2 3 4 5 6 7 8 9
    ". . . . . . . . . . \n" // 0
    ". . . . . . . . . . \n" // 1
    ". . . . . . . . . . \n" // 2
    "o . . . . . . . . . \n" // 3
    ". . . . . . . . . . \n" // 4
    ". . . . . @ . . . . \n" // 5
    ". . . . . . . . . . \n" // 6
    ". . . . . . . . . . \n" // 7
    ". . . . . . # * . . \n" // 8
    ". . . . . . . # . . \n" // 9
    ". . . . . . . . . . \n";// 10

    EXPECT_EQ(desiredMap, map.toString());

    // TODO: compare print output to map
    std::cout << "---------- PrintMapFromFile ----------\n";
    std::cout << desiredMap << std::endl;
    std::cout << map.toString() << std::endl;
    //map.print();
}

TEST(AdventureGameTest, readInputToGameAndPrintIt)
{
    Game game;
    game.run("input.txt");
    /*
    std::string desiredMap = 
//   0 1 2 3 4 5 6 7 8 9
    ". . . . . . . . . . \n" // 0
    ". . . . . . . . . . \n" // 1
    ". . . . . . . . . . \n" // 2
    "o . . . . . . . . . \n" // 3
    ". . . . . . . . . . \n" // 4
    ". . . . . @ . . . . \n" // 5
    ". . . . . . . . . . \n" // 6
    ". . . . . . . . . . \n" // 7
    ". . . . . . # * . . \n" // 8
    ". . . . . . . # . . \n" // 9
    ". . . . . . . . . . \n";// 10

    EXPECT_EQ(desiredMap, game.toString());*/
}

TEST(AdventureGameTest, playerIsAbleToTakeAStepTowardsTreasure)
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

TEST(AdventureGameTest, playerIsAbleToTakeAStepTowardsNorthWhichIsNonTreasure)
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

TEST(AdventureGameTest, playerIsAbleToTakeAStepTowardsEastWhichIsNonTreasure)
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

TEST(AdventureGameTest, playerIsAbleToTakeAStepTowardsWestWhichIsNonTreasure)
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