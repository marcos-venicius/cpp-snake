#include "snake.h"
#include <stdio.h>

Snake::Snake(int16_t length, int16_t size) {
    m_size = size;
    m_length = length;
    m_direction = {
        .x = 1,
        .y = 0
    };
    int16_t initialX = (length - 1) * size;

    XY pos = {
        .x = initialX,
        .y = 0
    };

    Color color = {
        .r = 1,
        .g = 0,
        .b = 0
    };

    for (int16_t i = 0; i < length; i++) {
        Box box(pos, color, size);

        m_boxes.push_back(box);

        pos.x -= size;

        if (i == 0) {
            color.g = 1;
            color.b = 1;
        }
    }
}

void Snake::drawFunc(void (* callback)(Box)) {
    for (Box box : m_boxes) {
        callback(box);
    }
}

void Snake::handleHorizontalOutBounds(XY *pos) {
    if (pos->x < 0) {
        pos->x = WIDTH - m_size;
    } else if (pos->x > WIDTH - m_size) {
        pos->x = 0;
    }
}

void Snake::handleVerticalOutBounds(XY *pos) {
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

    m_direction.x = x;
    m_direction.y = y;
}

void Snake::animate() {
    Box lastBox = m_boxes[0];

    XY lastPosition = lastBox.pos;
    XY tmp;

    lastPosition.x += m_direction.x * m_size;
    lastPosition.y += m_direction.y * m_size;

    for (int i = 0; i < m_length; i++) {
        handleHorizontalOutBounds(&lastPosition);
        handleVerticalOutBounds(&lastPosition);

        tmp = m_boxes[i].pos;

        m_boxes[i].pos = lastPosition;

        lastPosition = tmp;
    }
}

void Snake::increaseSize() {
    XY pos = m_boxes[m_boxes.size() - 1].pos;

    if (goingUp()) {
        pos.y = pos.y + m_size;
    } else if (goingDown()) {
        pos.y = pos.y - m_size;
    } else if (goingLeft()) {
        pos.x = pos.x + m_size;
    } else if (goingRight()) {
        pos.x = pos.x - m_size;
    }

    Color color = {
            .r = 1,
            .g = 1,
            .b = 1
    };

    Box box(pos, color, m_size);

    m_boxes.push_back(box);

    m_length++;
}

void Snake::decreaseSize() {
    m_boxes.pop_back();

    m_length--;
}

bool Snake::goingUp() {
    return m_direction.y == -1;
}

bool Snake::goingDown() {
    return m_direction.y == 1;
}

bool Snake::goingLeft() {
    return m_direction.x == -1;
}

bool Snake::goingRight() {
    return m_direction.x == 1;
}

void Snake::turnUp() {
    move(0, -1);
}

void Snake::turnDown() {
    move(0, 1);
}

void Snake::turnLeft() {
    move(-1, 0);
}

void Snake::turnRight() {
    move(1, 0);
}

Snake::~Snake() {
    // free
}