#include <vector>
#include <cstdint>
#include "consts.h"
#include <unordered_set>

class Apples
{
private:
    int16_t m_size;
    int16_t m_length;
    std::unordered_set<Box> m_boxes;
    XY randomPos();
public:
    Apples(int16_t length, int16_t size);
    ~Apples();

    void spawn();
    void remove(Box box);
    void drawFunc(void (* callback)(Box));
};
