#include <gtest/gtest.h>

#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

struct Coordinate
{
    std::uint32_t x;
    std::uint32_t y;
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
            case TileE::Empty : return "..";
            case TileE::Adventurer : return "oo";
            case TileE::Monster : return "@@";
            case TileE::Treasure : return "**";
            case TileE::Trap : return "##";
        }
        std::terminate();
    }

private:
    TileE m_type{TileE::Empty};
};

std::ostream& operator<<(std::ostream& out, const Tile& tile)
{
    out << tile.to_string();
    return out;
}

class Dungeon
{
public:
    Dungeon(const Coordinate& dimensions,
            const Coordinate& startPosition,
            const Coordinate& monster,
            const Coordinate& treasure,
            const std::vector<Coordinate>& traps)
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

    void print() const
    {
        for(const auto& row : m_map)
        {
            for(const auto& tile : row)
            {
                std::cout << tile;
            }
            std::cout << std::endl;
        }
    }

private:
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

    Dungeon parseFromString(const std::string& input)
    {
        // dimension_x dimension_y
        // startPosition_x startPosition_y
        // treasure_x treasure_y
        // monsterPos_x monsterPos_y
        // trap_x trap_y ..........
        std::vector<Coordinate> readCoords;

        std::stringstream ss(input);
        m_dimensions = toCoordinate(ss);
        m_startPosition = toCoordinate(ss);
        m_treasure = toCoordinate(ss);
        m_monster = toCoordinate(ss);

        while (auto trap = toCoordinate(ss); trap.has_value())
        {
         
            m_traps.push_back(trap);
        }
        for (std::string line; std::getline(ss, line);)
        {
            readCoords.emplace_back(toCoordinate(line)); 
        }

        m_dimensions = readCoords.at(0);

        return Dungeon{m_dimensions, readCoords.at(1), readCoords.at(3), readCoords.at(2), {readCoords.begin() + 4, readCoords.end()}};
    }

private:
    Coordinate toCoordinate(const std::string& line) const
    {
         std::stringstream subss(line);
            std::uint32_t readNumberX, readNumberY;
            subss >> readNumberX;
            subss >> readNumberY;
            return {readNumberX, readNumberY}; 
    }
    Coordinate toCoordinate(std::stringstream& ss) const
    {
        std::uint32_t readNumberX, readNumberY;
        ss >> readNumberX;
        ss >> readNumberY;
        return {readNumberX, readNumberY}; 
    }

    Coordinate m_dimensions{10u, 10u};
    Coordinate m_startPosition{0u, 0u};
    Coordinate m_monster{5u, 5u};
    Coordinate m_treasure{8u, 8u};
    std::vector<Coordinate> m_traps;
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
/*                        setDimensions(10u, 10u).
                        setStartPosition(0u, 3u).
                        setMonster(5u, 5u).
                        setTreasure(7u, 8u).
                        setTraps({{6u, 8u}, {7u, 9u}}).
                        build();*/
    map.print();
}
// ....................
// ....................
// ..................@@
// ....................
// ....##..............
// ......##..##........
// ....................
// ..##..**..##........
// ....................
// oo....##............