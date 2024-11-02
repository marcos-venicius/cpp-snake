#include <vector>
#include <cstdint>
#include "consts.h"

class Snake
{
private:
    int16_t m_size;
    int16_t m_length;
    std::vector<Box> m_boxes;
    XY m_direction;

    void handleHorizontalOutBounds(XY *pos);
    void handleVerticalOutBounds(XY *pos);
    bool goingRight();
    bool goingLeft();
    bool goingDown();
    bool goingUp();
    void move(int16_t x, int16_t y);

public:

    Snake(int16_t length, int16_t size);
    ~Snake();
    void drawFunc(void (* callback)(Box));
    void animate();
    void turnUp();
    void turnDown();
    void turnLeft();
    void turnRight();
    void increaseSize();
    void decreaseSize();
};
