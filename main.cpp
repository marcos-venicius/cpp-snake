#include <stdio.h>
#include <vector>
#include "snake.h"
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


int window;
Snake snake = Snake(3, BOX_SIZE);

void stopGame() {
    printf("stopping game\n");
    glutDestroyWindow(window);
    exit(0);
}

void drawBox(Box box) {
    float bottomLeftX = box.pos.x + box.size;
    float bottomLeftY = HEIGHT - (box.pos.y + box.size);
    float topRightX = box.pos.x;
    float topRightY = HEIGHT - box.pos.y;

    glColor3f(box.color.r, box.color.g, box.color.b);

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

    snake.drawFunc(drawBox);

    glFlush();

    glutPostRedisplay();
}

void move(int x, int y) {
    if ((x != -1 && x != 1 && x != 0) || (y != -1 && y != 1 && y != 0)) {
        perror("Invalid movement\n");
        exit(1);
    }

    // size_t boxes_size = snake.boxes.size();

    // for (size_t i = boxes_size - 1; i >= 0; i--)
    // {
        // if (i == boxes_size - 1)
        // {
        //     boxes[i].x = boxes[i].x + x;
        //     boxes[i].y = boxes[i].y + y;
        // }
        // else
        // {
        //     boxes[i].x = boxes[i + 1].x;
        //     boxes[i].y = boxes[i + 1].y;
        // }
    // }
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

int main(int argc, char **argv) {
    snake = Snake(3, BOX_SIZE);

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