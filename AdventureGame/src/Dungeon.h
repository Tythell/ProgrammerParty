#pragma once

#include "coordinate.h"
#include "Tile.h"

#include <cstdint>
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cassert>

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

std::string toString(const DirectionE direction);

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
        getTile(startPosition).set(TileE::Adventurer);
        getTile(monster).set(TileE::Monster);
        getTile(treasure).setTreasure() ;
        for(const auto& trap : traps)
        {
            getTile(trap).set(TileE::Trap);
        }
    }

    std::set<FeelingE> takeStep(DirectionE step)
    {
        std::cout << "Taking step towards: " << ::toString(step) << "\n";
        std::set<FeelingE> feelings;
        if(!updateTheAdventurer(step))
        {
            feelings.insert(FeelingE::Bounce);
        }
        if (isTreasure())
        {
            feelings.insert(FeelingE::Shining);
        }
        if (isTrapAround())
        {
            feelings.insert(FeelingE::Wind);
        }
        if(isMonsterAround())
        {
            feelings.insert(FeelingE::Smell);
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
    Coordinate calculateStep(DirectionE direction) const
    {    
        assert(canAdventurerTakeStep(direction));
        Coordinate newCoordinate = m_adventurer;
    
        switch(direction)
        {
            case DirectionE::North: 
                newCoordinate.y--;
                break;
            case DirectionE::South: 
                newCoordinate.y++; 
                break;
            case DirectionE::East: 
                newCoordinate.x++;
                break;
            case DirectionE::West: 
                newCoordinate.x--;
                break;
        }
        return newCoordinate;
    }

    std::vector<Tile> getNeighbours() const
    {
        std::vector<Tile> neighbours;
        constexpr auto NUMBER_OF_DIRECTIONS{4u};
        neighbours.reserve(NUMBER_OF_DIRECTIONS);
        for(auto direction : {DirectionE::North, DirectionE::East, DirectionE::South, DirectionE::West})
        {
            if (canAdventurerTakeStep(direction))
            {
                neighbours.push_back(getTile(calculateStep(direction)));
            }
        }
        return neighbours;
    }

    bool isMonsterAround() const
    {
        return std::ranges::any_of(getNeighbours(), std::mem_fn(&Tile::isMonster));
    }

    bool isTrapAround() const
    {
        return std::ranges::any_of(getNeighbours(), std::mem_fn(&Tile::isTrap));
    }

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
        if (canAdventurerTakeStep(step))
        {
            getTile(m_adventurer).set(TileE::Empty);
            m_adventurer = calculateStep(step);
            getTile(m_adventurer).set(TileE::Adventurer);

            return true;    
        }
        else
        {
            return false;
        }
    }

    bool canAdventurerTakeStep(const DirectionE step) const
    {
        switch(step)
        {
            case DirectionE::North: return m_adventurer.y > 0;
            case DirectionE::South: return m_adventurer.y < m_map.size() - 1;
            case DirectionE::East: return m_adventurer.x < m_map.at(m_adventurer.y).size() - 1;
            case DirectionE::West: return m_adventurer.x > 0;
        }
        return false;
    }

    bool isTreasure() const
    {
        return getTile(m_adventurer).isTreasure();
    }

    Coordinate m_adventurer;
    std::vector<std::vector<Tile>> m_map;
};
