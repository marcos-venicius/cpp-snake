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
    std::pair<int, int> key() { return std::make_pair(pos.x, pos.y); }
};

namespace std
{
    template <>
    struct hash<std::pair<int, int>>
    {
        size_t operator()(const std::pair<int, int>& p) const {
            return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
        }
    };
}

#endif // BOX_H