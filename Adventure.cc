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
        // for(const auto& row : m_map)
        // {
        //     for(const auto& tile : row)
        //     {
        //         std::cout << tile;
        //     }
        //     std::cout << std::endl;
        // }
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
