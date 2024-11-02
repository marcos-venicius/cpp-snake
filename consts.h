#ifndef BOX_H
#define BOX_H

#include <functional>
#include <cstdint>

#define WIDTH 1000
#define HEIGHT 800
#define BOX_SIZE 10

typedef struct
{
    float r;
    float g;
    float b;
} Color;

typedef struct
{
    int16_t x;
    int16_t y;
} XY;

struct Box
{
    XY pos;
    Color color;
    int16_t size;

    Box() : pos(), color(), size(0) {}
    Box(XY position, Color col, int16_t sz) : pos(position), color(col), size(sz) {}
};

bool operator==(const Box &lhs, const Box &rhs);
bool operator==(const Color &lhs, const Color &rhs);
bool operator==(const XY &lhs, const XY &rhs);

namespace std
{
    template <>
    struct hash<Box>
    {
        size_t operator()(const Box &box) const
        {
            return hash<int16_t>()(box.pos.x) ^
                   hash<int16_t>()(box.pos.y) ^
                   hash<float>()(box.color.r) ^
                   hash<float>()(box.color.g) ^
                   hash<float>()(box.color.b) ^
                   hash<int16_t>()(box.size);
        }
    };
}

#endif // BOX_H