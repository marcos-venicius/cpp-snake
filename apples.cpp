#include "apples.h"
#include <random>

Apples::Apples(int16_t length, int16_t size)
{
    m_size = size;

    Color color = {
        .r = .5,
        .g = 1,
        .b = .5};

    for (int16_t i = 0; i < length; i++)
    {
        XY pos = randomPos();
        std::pair<int, int> key(pos.x, pos.y);
        Box box(pos, color, size);

        m_boxes.insert({key, box});
    }
}

XY Apples::randomPos()
{
    std::random_device rd;
    std::mt19937 generator(rd());

    std::uniform_int_distribution<int16_t> distributionX(0, WIDTH - m_size);
    std::uniform_int_distribution<int16_t> distributionY(0, HEIGHT - m_size);

    int16_t x = distributionX(generator);
    int16_t y = distributionY(generator);

    return XY{
        .x = (int16_t)(x - x % m_size),
        .y = (int16_t)(y - y % m_size)};
}

void Apples::spawn()
{
    Color color = {
        .r = .5,
        .g = 1,
        .b = .5};
    XY pos = randomPos();
    Box box(pos, color, m_size);

    m_boxes.insert({box.key(), box});
}

void Apples::drawFunc(void (*callback)(Box))
{
    for (const auto &pair : m_boxes)
    {
        callback(pair.second);
    }
}

bool Apples::checkCollision(Box box) {
    std::pair<int, int> key = box.key();

    auto it = m_boxes.find(key);

    if (it != m_boxes.end()) {
        m_boxes.erase(key);

        spawn();

        return true;
    }

    return false;
}

Apples::~Apples()
{
    // free
}