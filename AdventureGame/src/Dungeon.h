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
    Bounce,
    DeadSleepy
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
        getTile(treasure).set(TileE::Treasure);
        for(const auto& trap : traps)
        {
            getTile(trap).set(TileE::Trap);
        }
        print();
    }

    std::set<FeelingE> takeStep(DirectionE step);

    void print() const
    {
        std::cout << toString();
    }

    std::string toString() const;
    
    bool pickTheTreasure();

    bool shoot(DirectionE direction);
    
private:
    Coordinate calculateStep(DirectionE direction) const
    {
        return calculateStep(direction, m_adventurer);
    }

    Coordinate calculateStep(DirectionE direction, const Coordinate& position) const;

    std::vector<Tile> getNeighbours() const;

    bool isTypeAround(TileE type) const
    {
        // TODO: Refactor this with std::any_of
        // I couldn't get std::ranges::any_of to work with is(TypeE) function
        bool isAround = false;
        for (auto& neighbour : getNeighbours())
        {
            isAround |= neighbour.is(type);
        }
        return isAround;
    }

    bool isMonsterAround() const
    {
        return isTypeAround(TileE::Monster);
        // return std::ranges::any_of(getNeighbours(), std::mem_fn(&Tile::isMonster()));
    }

    bool isTrapAround() const
    {
        return isTypeAround(TileE::Trap);
        // return std::ranges::any_of(getNeighbours(), std::mem_fn(&Tile::isTrap()));
    }

    Tile& getTile(const Coordinate& xy)
    {
        return m_map[xy.y][xy.x];
    }

    const Tile& getTile(const Coordinate& xy) const
    {
        return m_map.at(xy.y).at(xy.x);
    }

    bool updateTheAdventurer(DirectionE step);

    bool canAdventurerTakeStep(const DirectionE step) const
    {
        return canAdventurerTakeStep(step, m_adventurer);
    }

    bool canAdventurerTakeStep(const DirectionE step, const Coordinate& position) const;

    bool isTreasure() const
    {
        return getTile(m_adventurer).is(TileE::Treasure);
    }
    
    bool isMonster() const
    {
        return getTile(m_adventurer).is(TileE::Monster);
    }

    bool m_isAdventurerAlive = true;
    Coordinate m_adventurer;
    std::uint32_t m_numberOfShotsLeft{1u};
    std::vector<std::vector<Tile>> m_map;
};
