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

#include "consts.h"

const int FPS = 10;
const int FRAME_DURATION = 1000 / FPS;

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
    snake.animate();

    glFlush();

    glutSwapBuffers();
}

void handleSpecialKey(int key, int, int) {
    switch (key) {
        case GLUT_KEY_UP:
            snake.turnUp();
            break;
        case GLUT_KEY_DOWN:
            snake.turnDown();
            break;
        case GLUT_KEY_LEFT:
            snake.turnLeft();
            break;
        case GLUT_KEY_RIGHT:
            snake.turnRight();
            break;
        default:
            break;
    }
}

void handleWasdKeys(unsigned char key, int, int) {
    switch (key) {
        case 'w':
            snake.turnUp();
            break;
        case 's':
            snake.turnDown();
            break;
        case 'a':
            snake.turnLeft();
            break;
        case 'd':
            snake.turnRight();
            break;
        case 'q':
            stopGame();
        case 'n':
            snake.increaseSize();
            break;
        case 'p':
            snake.decreaseSize();
            break;
        default:
            break;
    }
}

void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(FRAME_DURATION, timer, 0);
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

    glutTimerFunc(0, timer, 0);

    glutMainLoop();

    return 0;
}