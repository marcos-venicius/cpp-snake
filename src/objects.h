#include <cstdint>

typedef struct {
    float red;
    float green;
    float blue;
} Color;

typedef struct {
    uint32_t x;
    uint32_t y;
    uint32_t w;
    uint32_t h;
    Color color;
} Box;