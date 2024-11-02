#include <stdio.h>
#include <vector>
#include "objects.h"
#include <cstdint>
#if _WIN32
#   include <Windows.h>
#endif
#if __APPLE__
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#   include <GLUT/glut.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/glut.h>
#endif

#define WIDTH 1000
#define HEIGHT 800
#define BOX_SIZE 10


std::vector<Box> boxes;
int window;

void stopGame() {
    glutDestroyWindow(window);
}

Box createBox(uint32_t x, uint32_t y, uint32_t s, Color color = { .red = 1.f, .green = 1.f, .blue = 1.f}) {
    return {
        .x = x,
        .y = y,
        .s = s,
        .color = color
    };
}

void drawBox(Box box) {
    float bottomLeftX = box.x + box.s;
    float bottomLeftY = HEIGHT - (box.y + box.s);
    float topRightX = box.x;
    float topRightY = HEIGHT - box.y;

    glColor3f(box.color.red, box.color.green, box.color.blue);

    glBegin(GL_QUADS);
        glVertex2f(bottomLeftX, bottomLeftY);
        glVertex2f(topRightX, bottomLeftY);
        glVertex2f(topRightX, topRightY);
        glVertex2f(bottomLeftX, topRightY);
    glEnd();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawWindow() {
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    // START DRAW
    for (Box box : boxes) {
        drawBox(box);
    }
    // END DRAW

    glFlush();

    glutPostRedisplay();
}

void move(int x, int y) {
    if ((x != -1 && x != 1 && x != 0) || (y != -1 && y != 1 && y != 0)) {
        perror("Invalid movement\n");
        exit(1);
    }

    x *= BOX_SIZE;
    y *= BOX_SIZE;

    size_t boxes_size = boxes.size();

    for (size_t i = 0; i < boxes_size; i++)
    {
        if (i == boxes_size - 1)
        {
            boxes[i].x = boxes[i].x + x;
            boxes[i].y = boxes[i].y + y;
        }
        else
        {
            boxes[i].x = boxes[i + 1].x;
            boxes[i].y = boxes[i + 1].y;
        }
    }
}

void handleSpecialKey(int key, int, int) {
    switch (key) {
        case GLUT_KEY_UP:
            move(0, -1);
            break;
        case GLUT_KEY_DOWN:
            move(0, 1);
            break;
        case GLUT_KEY_LEFT:
            move(-1, 0);
            break;
        case GLUT_KEY_RIGHT:
            move(1, 0);
            break;
        default:
            break;
    }
}

void handleWasdKeys(unsigned char key, int, int) {
    switch (key) {
        case 'w':
            move(0, -1);
            break;
        case 's':
            move(0, 1);
            break;
        case 'a':
            move(-1, 0);
            break;
        case 'd':
            move(1, 0);
            break;
        case 'q':
            stopGame();
        default:
            break;
    }
}

void createInitialSnake(uint size) {
    int currentX = 0;

    for (size_t i = 0; i < size; i++) {
        Box box = createBox(currentX, 0, BOX_SIZE);

        boxes.push_back(box);

        currentX += BOX_SIZE;
    }
}

int main(int argc, char **argv) {
    createInitialSnake(3);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    window = glutCreateWindow("Hello");
    glutDisplayFunc(drawWindow);
    glutReshapeFunc(reshape);

    glutSpecialFunc(handleSpecialKey);
    glutKeyboardFunc(handleWasdKeys);

    glutMainLoop();

    return 0;
}