#include "Dungeon.h"

std::string toString(const DirectionE direction)
{
    switch (direction)
    {
        case DirectionE::North : return "North";
        case DirectionE::East : return "East";
        case DirectionE::South : return "South";
        case DirectionE::West : return "West";
    }
    return "Unknown direction";
}

std::set<FeelingE> Dungeon::takeStep(DirectionE step)
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
    if (isMonster())
    {
        feelings.insert(FeelingE::DeadSleepy);
    }

    print();
    return feelings;
}

std::string Dungeon::toString() const
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

bool Dungeon::pickTheTreasure() 
{
    if(isTreasure())
    {
       getTile(m_adventurer).remove(TileE::Treasure);
       return true;
    }
    return false;
}

bool Dungeon::shoot(DirectionE direction)
{
    if (m_numberOfShotsLeft > 0u)
    {
        --m_numberOfShotsLeft;

        auto target = m_adventurer;
        while (canAdventurerTakeStep(direction, target))
        {
            target = calculateStep(direction, target);
            if(getTile(target).is(TileE::Monster))
            {
                getTile(target).remove(TileE::Monster);
                return true;
            }
        }
    }
    return false;
}

Coordinate Dungeon::calculateStep(DirectionE direction, const Coordinate& position) const
{    
    assert(canAdventurerTakeStep(direction, position));
    Coordinate newCoordinate = position;

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

std::vector<Tile> Dungeon::getNeighbours() const
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

bool Dungeon::canAdventurerTakeStep(const DirectionE step, const Coordinate& position) const
{
    switch(step)
    {
        case DirectionE::North: return position.y > 0;
        case DirectionE::South: return position.y < m_map.size() - 1;
        case DirectionE::East: return position.x < m_map.at(position.y).size() - 1;
        case DirectionE::West: return position.x > 0;
    }
    return false;
}

bool Dungeon::updateTheAdventurer(DirectionE step)
{
    if (canAdventurerTakeStep(step))
    {
        getTile(m_adventurer).remove(TileE::Adventurer);
        m_adventurer = calculateStep(step);
        getTile(m_adventurer).set(TileE::Adventurer);

        return true;    
    }
    else
    {
        return false;
    }
}
