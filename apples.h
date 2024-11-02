#include <vector>
#include <cstdint>
#include "consts.h"
#include <unordered_map>

class Apples
{
private:
    int16_t m_size;
    std::unordered_map<std::pair<int, int>, Box> m_boxes;
    XY randomPos();
    void spawn();

public:
    Apples(int16_t length, int16_t size);
    ~Apples();

    void drawFunc(void (*callback)(Box));
    bool checkCollision(Box box);
};
