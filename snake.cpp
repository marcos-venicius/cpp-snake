#include "snake.h"
#include <stdio.h>
#include "consts.h"

Snake::Snake(uint16_t length, uint16_t size) {
    m_size = size;
    m_length = length;

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

void Snake::handleHorizontalOutBounds(Pos *pos) {
    if (pos->x < 0) {
        pos->x = WIDTH - m_size;
    } else if (pos->x > WIDTH - m_size) {
        pos->x = 0;
    }
}

void Snake::handleVerticalOutBounds(Pos *pos) {
    if (pos->y < 0) {
        pos->y = HEIGHT - m_size;
    } else if (pos->y > HEIGHT - m_size) {
        pos->y = 0;
    }
}

void Snake::move(int16_t x, int16_t y) {
    if ((x != -1 && x != 1 && x != 0) || (y != -1 && y != 1 && y != 0)) {
        perror("Invalid movement\n");
        return;
    }

    Box lastBox = m_boxes[m_boxes.size() - 1];


    Pos lastPosition = lastBox.pos;
    Pos tmp;

    lastPosition.x += x * m_size;
    lastPosition.y += y * m_size;

    for (int i = m_length - 1; i >= 0; i--) {
        handleHorizontalOutBounds(&lastPosition);
        handleVerticalOutBounds(&lastPosition);

        tmp = m_boxes[i].pos;

        m_boxes[i].pos = lastPosition;

        lastPosition = tmp;
    }
}

Snake::~Snake() {
    // free
}