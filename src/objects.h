#include <cstdint>

typedef struct {
    float red;
    float green;
    float blue;
} Color;

typedef struct {
    uint32_t x;
    uint32_t y;
    uint32_t s;
    Color color;
} Box;