#pragma once

#include "coordinate.h"
#include "Tile.h"

#include <cstdint>
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <sstream>

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
        if (isTrapAround())
        {
            feelings.insert(FeelingE::Wind);
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
    std::vector<Coordinate> getNeighbours() const
    {
        return {};
    }

    bool isTrapAround() const
    {
        //TODO calculate the coordinates of the neighbors
        //return true if any one of them is trap
        const auto neighbours = getNeighbours();
        return false;
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
        auto oldPosition = m_adventurer;
        switch(step){
            case DirectionE::North:
            if(m_adventurer.y != 0)
            {
                m_adventurer.y--;
            } else {
                return false;
            }            
            break;
            case DirectionE::South:
            if(m_adventurer.y >= m_map.size() - 1){
                return false;
            }else {
                m_adventurer.y++;
            }
            break;
            case DirectionE::East:
            if (m_adventurer.x == m_map.at(m_adventurer.y).size() - 1)
            {
                return false;
            }
            else
            {
                m_adventurer.x++;
            }
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
        getTile(oldPosition).set(TileE::Empty);
        getTile(m_adventurer).set(TileE::Adventurer);
        return true;
    }

    bool isTreasure() const
    {
        return getTile(m_adventurer).isTreasure();
    }

    Coordinate m_adventurer;
    std::vector<std::vector<Tile>> m_map;
};
