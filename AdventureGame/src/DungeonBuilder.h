#pragma once

#include "Dungeon.h"

#include <fstream>
#include <cassert>
#include <optional>

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
