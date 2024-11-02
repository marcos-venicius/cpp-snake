#include "consts.h"

bool operator==(const XY &lhs, const XY &rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator==(const Color &lhs, const Color &rhs)
{
    return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b;
}

bool operator==(const Box &lhs, const Box &rhs)
{
    return lhs.pos == rhs.pos && lhs.color == rhs.color && lhs.size == rhs.size;
}
