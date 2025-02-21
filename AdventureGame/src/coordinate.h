#pragma once

#include <cstdint>

struct Coordinate
{
    std::uint32_t x;
    std::uint32_t y;

    bool operator==(const Coordinate& rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }
};