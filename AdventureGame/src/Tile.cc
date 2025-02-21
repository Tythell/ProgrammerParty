#include "Tile.h"

std::ostream& operator<<(std::ostream& out, const Tile& tile)
{
    out << tile.toString();
    return out;
}