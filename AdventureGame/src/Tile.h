#pragma once

#include <string>
#include <exception>
#include <iostream>
#include <set>

enum class TileE
{
    Adventurer,
    Monster,
    Trap,
    Treasure
};

class Tile
{
public:
    void set(TileE type)
    {
        m_types.insert(type);
    }
    void remove(TileE type)
    {
        m_types.erase(type);
    }
    bool is(TileE type) const
    {
        return m_types.contains(type);
    }
    std::string toString() const
    {
        if (m_types.empty())
        {
            return ".   ";
        }

        std::string toStringTile = "";
        if (is(TileE::Treasure))
        {
            toStringTile.append("*");
        }
        if (is(TileE::Monster))
        {
            toStringTile.append("@");
        }
        if (is(TileE::Trap))
        {
            toStringTile.append("#");
        }
        if (is(TileE::Adventurer))
        {
            toStringTile.append("o");
        }

        toStringTile.append(std::string(4 - toStringTile.size(), ' '));

        return toStringTile;
    }

    // bool isTreasure() const
    // {
    //     return m_types.contains(TileE::Treasure);
    // }

    // bool isTrap() const
    // {
    //     return m_types.contains(TileE::Trap);
    // }

    // bool isMonster() const
    // {
    //     return m_types.contains(TileE::Monster);
    // }

    // bool isAdventurer() const
    // {
    //     return m_types.contains(TileE::Adventurer);
    // }

private:
    std::set<TileE> m_types{};
};

std::ostream& operator<<(std::ostream& out, const Tile& tile);