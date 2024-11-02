#include <vector>
#include <cstdint>

typedef struct {
    float r;
    float g;
    float b;
} Color;

typedef struct {
    int16_t x;
    int16_t y;
} XY;

typedef struct {
    XY pos;
    Color color;
    uint16_t size;
} Box;

class Snake
{
private:
    uint16_t m_size;
    uint16_t m_length;
    std::vector<Box> m_boxes;
    XY m_direction;

    void handleHorizontalOutBounds(XY *pos);
    void handleVerticalOutBounds(XY *pos);

public:

    Snake(uint16_t length, uint16_t size);
    ~Snake();
    void drawFunc(void (* callback)(Box));
    void move(int16_t x, int16_t y);
    void animate();
};
