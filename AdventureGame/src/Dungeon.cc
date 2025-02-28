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
