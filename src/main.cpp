#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>

#include "Bodies.h"
#include "Vector.h"
#include "Color.h"

double fsAngle = 0;
double ssAngle = 0;
double tsAngle = -60;

Bodies bodies;
Vector vector;

double angle = 0.0;
double angle_up_down = 20.0;

void defaultLight() {
    float position[] = {0.0f, 0.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, WHITE);
    glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void lampLight() {
    float position[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float direction[] = {0.0, 0.0, -1.0};

    glLightfv(GL_LIGHT1, GL_DIFFUSE, RED_LOW);
    glLightfv(GL_LIGHT1, GL_POSITION, position);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
}

void turnOnDefaultLight() {
    glPushMatrix();
    glTranslated(10.0, 0, 10.0);
    defaultLight();
    glMaterialfv(GL_FRONT, GL_EMISSION, RED);
    bodies.drawCube(0.5);
    glMaterialfv(GL_FRONT, GL_EMISSION, BLACK);
    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    int camera_distance = 20;
    gluLookAt(camera_distance * cos(angle), camera_distance * sin(angle), angle_up_down, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

    double rStand = 2;
    double hStand = 5;

    double rJoint = 0.7;
    double hJoint = 5;

    int defaultRotation = 30;

    bodies.drawCylinder(6, 1, 10);
    glTranslated(0, 0, 1);
    bodies.drawCylinder(4, 1, 10);

    glPushMatrix();
    // main stand
    glRotated(fsAngle, 1, 0, 0);
    glTranslated(-2.5, 0, 0);
    glRotated(90, 0, 1, 0);
    bodies.drawCylinder(rStand, hStand, 10);

    // first - second stand
    glTranslated(0, 0, hStand / 4);
    glRotated(defaultRotation, 0, 0, 1);
    glRotated(-90, 0, 1, 0);
    glTranslated(0, 0, rStand);
    bodies.drawCylinder(0.4, 10, 5);

    // first - second stand
    glTranslated(rStand, 0, 0);
    bodies.drawCylinder(0.4, 10, 5);
    glPopMatrix();


    glPushMatrix();
    // second stand
    glRotated(defaultRotation + fsAngle, 1, 0, 0);
    glTranslated(-hStand / 2, 0, 0);
    glTranslated(0, 0, 12);
    glRotated(90, 0, 1, 0);
    glRotated(ssAngle, 0, 0, 1);
    bodies.drawCylinder(rJoint, hJoint, 10);

    // second - third stand
    glTranslated(0, 0, hStand / 4);
    glRotated(-90, 1, 0, 0);
    bodies.drawCylinder(0.4, 10, 5);

    // second - third stand
    glTranslated(0, -hStand / 2, 0);
    bodies.drawCylinder(0.4, 10, 5);


    // third stand
    glTranslated(0, -hStand / 4, 0);
    glTranslated(0, 0, 10);
    glRotated(-90, 1, 0, 0);

    glRotated(tsAngle, 0, 0, 1);
    bodies.drawCylinder(rJoint, hJoint, 10);

    glTranslated(0, 0, hStand / 2);
    glRotated(90, 0, 1, 0);
    bodies.drawCylinder(0.5, 1.5, 10);

    glTranslated(0, 1, 0);
    glTranslated(0, 0, 2.8);
    glRotated(90, 1, 0, 0);
    bodies.drawCylinder(1.5, 2, 10);

    glTranslated(0, 0, -3);
    bodies.drawTruncatedCone(3, 1.5, 3, 10);

    lampLight();
    glMaterialfv(GL_FRONT, GL_EMISSION, RED_LOW);
    bodies.drawSphere(1.5);
    glMaterialfv(GL_FRONT, GL_EMISSION, BLACK);
    glPopMatrix();
    glTranslated(0, 15, 0);
    bodies.drawSphere(3);

    glutSwapBuffers();
}

void scale(int w, int h) {
    double xmin = -15.0, xmax = 15.0;
    double xrange = xmax - xmin;
    double yrange = h * xrange / w;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(xmin, xmax, -yrange / 2.0, yrange / 2.0, 10.0, 100.0);
}

void on_arrow(int c, int x, int y) {
    if (c == GLUT_KEY_LEFT) {
        angle += 0.05;
    }
    if (c == GLUT_KEY_RIGHT) {
        angle -= 0.05;
    }
    if (c == GLUT_KEY_UP) {
        angle_up_down += 0.5;
    }
    if (c == GLUT_KEY_DOWN) {
        angle_up_down -= 0.5;
    }
}

void on_key(unsigned char c, int x, int y) {

    if (c == 'q') exit(0);
    if (c == 's') glShadeModel(GL_SMOOTH);
    if (c == 'f') glShadeModel(GL_FLAT);
    if (c == 'D') glEnable(GL_DEPTH_TEST);
    if (c == 'd') glDisable(GL_DEPTH_TEST);
    if (c == 'C') glEnable(GL_CULL_FACE);
    if (c == 'c') glDisable(GL_CULL_FACE);
    if (c == 'B') glCullFace(GL_BACK);
    if (c == 'b') glCullFace(GL_FRONT);
    if (c == '0') glEnable(GL_LIGHT0);
    if (c == '1') glEnable(GL_LIGHT1);
    if (c == '=') {
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
    }
    if (c == 'k') fsAngle += 1;
    if (c == 'l') fsAngle -= 1;

    if (c == 'h') ssAngle += 1;
    if (c == 'j') ssAngle -= 1;

    if (c == '[') tsAngle += 1;
    if (c == ']') tsAngle -= 1;
}

void rotate(int id) {
    glutPostRedisplay();
    // wait 50 milliseconds
    glutTimerFunc(50, rotate, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(1024, 768);
    glutCreateWindow("glLamp");

    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glShadeModel(GL_SMOOTH);

    glutDisplayFunc(display);
    glutReshapeFunc(scale);
    glutKeyboardFunc(on_key);
    glutSpecialFunc(on_arrow);
    glutTimerFunc(50, rotate, 0);

    glutMainLoop();
    return 0;
}