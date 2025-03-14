#pragma once

#include <string>
#include <exception>
#include <iostream>

enum class TileE
{
    Empty,
    Adventurer,
    Monster,
    Trap
};

class Tile
{
public:
    void set(TileE type)
    {
        m_type = type;
    }

    std::string toString() const
    {
        switch (m_type)
        {
            case TileE::Empty : return "." + getAdditonalInfo();
            case TileE::Adventurer : return "o" + getAdditonalInfo();
            case TileE::Monster : return "@" + getAdditonalInfo();
            case TileE::Trap : return "#" + getAdditonalInfo();
        }
        
        std::terminate();
    }

    void setTreasure(bool isIt = true) 
    {
        m_isTreasure = isIt;
    }

    bool isTreasure() const
    {
        return m_isTreasure;
    }

    bool isTrap() const
    {
        return m_type == TileE::Trap;
    }

    bool isMonster() const
    {
        return m_type == TileE::Monster;
    }

private:
    std::string getAdditonalInfo() const
    {
        return m_isTreasure ? "*" : " ";
    }

    TileE m_type{TileE::Empty};
    bool m_isTreasure{false};
};

std::ostream& operator<<(std::ostream& out, const Tile& tile);