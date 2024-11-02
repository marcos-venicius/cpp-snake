#include "snake.h"
#include <stdlib.h>

Snake::Snake(uint16_t length, uint16_t size) {
    m_size = size;

    Pos pos = {
        .x = 0,
        .y = 0
    };

    Color color = {
        .r = 1,
        .g = 1,
        .b = 1
    };

    for (uint16_t i = 0; i < length; i++) {
        if (i == length - 1) {
            color.g = 0;
            color.b = 0;
        }

        Box box = {
            .pos = pos,
            .color = color,
            .size = size
        };

        m_boxes.push_back(box);

        pos.x += size;
    }
}

void Snake::drawFunc(void (* callback)(Box)) {
    for (Box box : m_boxes) {
        callback(box);
    }
}

Snake::~Snake() {
    // free
}