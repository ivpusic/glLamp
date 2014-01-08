/* 
 * File:   Bodies.cpp
 * Author: ivpusic
 * 
 * Created on January 7, 2014, 8:47 PM
 */

#include "Bodies.h"

Bodies::Bodies() {
}

void Bodies::drawSphere(double r) {

    glBegin(GL_QUADS);

    double phi;
    double rho;
    double v[] = {0.0, 0.0, 0.0};
    double deltaPhi;
    double deltaRho;
    deltaPhi = deltaRho = M_PI / 50;

    for (phi = 0; phi < M_PI; phi += deltaPhi) {
        for (rho = 0; rho < M_PI * 2; rho += deltaRho) {
            double x3 = r * sin(rho) * cos(phi);
            double y3 = r * sin(rho) * sin(phi);
            double z3 = r * cos(rho);

            double x4 = r * sin(rho + deltaRho) * cos(phi);
            double y4 = r * sin(rho + deltaRho) * sin(phi);
            double z4 = r * cos(rho + deltaRho);

            glVertex3f(x3, y3, z3);
            glVertex3f(x4, y4, z4);

            double x1 = r * sin(rho + deltaRho) * cos(phi + deltaPhi);
            double y1 = r * sin(rho + deltaRho) * sin(phi + deltaPhi);
            double z1 = r * cos(rho + deltaRho);

            double x2 = r * sin(rho) * cos(phi + deltaPhi);
            double y2 = r * sin(rho) * sin(phi + deltaPhi);
            double z2 = r * cos(rho);

            v[0] = x1;
            v[1] = y1;
            v[2] = z1;
            vector.normalize(v);
            glNormal3dv(v);

            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y2, z2);
        }
    }
    glEnd();
}

void Bodies::drawCube(double a) {
    drawRectangle(a, a, a);
}

void Bodies::drawRectangle(double w, double h, double l) {
    glBegin(GL_QUADS);

    glNormal3d(0, -1, 0);
    glVertex3d(0, 0, 0);
    glVertex3d(w, 0, 0);
    glVertex3d(w, 0, h);
    glVertex3d(0, 0, h);

    glNormal3d(0, 1, 0);
    glVertex3d(0, l, 0);
    glVertex3d(w, l, 0);
    glVertex3d(w, l, h);
    glVertex3d(0, l, h);

    glNormal3d(0, 0, -1);
    glVertex3d(0, 0, 0);
    glVertex3d(w, 0, 0);
    glVertex3d(w, l, 0);
    glVertex3d(0, l, 0);

    glNormal3d(0, 0, 1);
    glVertex3d(0, 0, h);
    glVertex3d(w, 0, h);
    glVertex3d(w, l, h);
    glVertex3d(0, l, h);

    glNormal3d(-1, 0, 0);
    glVertex3d(0, 0, 0);
    glVertex3d(0, l, 0);
    glVertex3d(0, l, h);
    glVertex3d(0, 0, h);

    glNormal3d(1, 0, 0);
    glVertex3d(w, 0, 0);
    glVertex3d(w, l, 0);
    glVertex3d(w, l, h);
    glVertex3d(w, 0, h);

    glEnd();
}

void Bodies::drawCoordinateSystem() {

    glDisable(GL_LIGHTING);

    glBegin(GL_LINES);
    glColor3d(1, 0, 0);
    glVertex3d(-10, 0, 0);
    glVertex3d(10, 0, 0);

    glColor3d(0, 1, 0);
    glVertex3d(0, -10, 0);
    glVertex3d(0, 10, 0);

    glColor3d(0, 0, 1);
    glVertex3d(0, 0, -10);
    glVertex3d(0, 0, 10);
    glEnd();

    glEnable(GL_LIGHTING);
}

void Bodies::drawLetterO(double r) {
    glBegin(GL_QUAD_STRIP);
    double increment = M_PI / 20;
    double i;

    glNormal3d(0, 0, -1);
    for (i = 0; i <= 2 * M_PI; i += increment) {
        glVertex3d(r * cos(i), r * sin(i), 0);
        glVertex3d((r + 1) * cos(i), (r + 1) * sin(i), 0);
    }

    glNormal3d(0, 0, 1);
    for (i = 0; i <= 2 * M_PI; i += increment) {
        glVertex3d(r * cos(i), r * sin(i), 1);
        glVertex3d((r + 1) * cos(i), (r + 1) * sin(i), 1);
    }

    for (i = 0; i <= 2 * M_PI; i += increment) {
        v[0] = -r * cos(i);
        v[1] = -r * sin(i);
        v[2] = 0;
        vector.normalize(v);
        glNormal3dv(v);
        glVertex3d(r * cos(i), r * sin(i), 0);
        glVertex3d((r) * cos(i), (r) * sin(i), 1);
    }

    glNormal3d(1, 1, 0);
    for (i = 0; i <= 2 * M_PI; i += increment) {
        v[0] = r * cos(i);
        v[1] = r * sin(i);
        v[2] = 0;
        vector.normalize(v);
        glNormal3dv(v);
        glVertex3d((r + 1) * cos(i), (r + 1) * sin(i), 0);
        glVertex3d((r + 1) * cos(i), (r + 1) * sin(i), 1);
    }
    glEnd();
}

void Bodies::drawCylinder(double r, double h, int m) {
    drawEllipticCylinder(r, r, h, m);
}

void Bodies::drawEllipticCylinder(double a, double b, double h, int m) {

    double i;
    double incr = M_PI / m;

    glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0, 0, -1.0);
    glVertex3d(0, 0, 0);
    for (i = 0; i <= 2 * M_PI; i += incr) {
        glVertex3d(a * cos(i), b * sin(i), 0);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0, 0, 1.0);
    glVertex3d(0, 0, h);
    for (i = 0; i <= 2 * M_PI; i += incr) {
        glVertex3d(a * cos(i), b * sin(i), h);
    }
    glEnd();


    glBegin(GL_TRIANGLE_STRIP);
    for (i = 0; i <= 2 * M_PI; i += incr) {
        v[0] = cos(i);
        v[1] = sin(i);
        v[2] = 0;
        vector.normalize(v);
        glNormal3dv(v);
        glVertex3d(a * cos(i), b * sin(i), 0);
        glVertex3d(a * cos(i), b * sin(i), h);
    }
    glEnd();
}

void Bodies::drawCone(double r, double h, int m) {
    double i;
    double incr = M_PI / m;

    glNormal3d(0, 0, -1.0);
    glVertex3d(0, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    for (i = 0; i <= 2 * M_PI; i += incr) {
        glVertex3d(r * cos(i), r * sin(i), 0);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0.0, 0.0, 1.0);
    glVertex3d(0.0, 0.0, h);
    for (i = 0; i <= 2 * M_PI; i += incr) {
        v[0] = cos(i);
        v[1] = sin(i);
        v[2] = 0;
        vector.normalize(v);
        glNormal3dv(v);
        glVertex3d(r * cos(i), r * sin(i), 0);
    }
    glEnd();
}

void Bodies::drawTruncatedCone(double r1, double r2, double h, int m) {

    double i;
    double incr = M_PI / m;

    glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0, 0, -1.0);
    glVertex3d(0, 0, 0);
    for (i = 0; i <= 2 * M_PI; i += incr) {
        glVertex3d(r1 * cos(i), r1 * sin(i), 0);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0, 0, 1.0);
    glVertex3d(0, 0, h);
    for (i = 0; i <= 2 * M_PI; i += incr) {
        glVertex3d(r2 * cos(i), r2 * sin(i), h);
    }
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    for (i = 0; i <= 2 * M_PI; i += incr) {
        vector.vproduct(v, r1 * cos(i - M_PI / 2), r1 * sin(i - M_PI / 2), 0, r2 * cos(i), r2 * sin(i), -h);
        vector.normalize(v);
        glNormal3dv(v);
        glVertex3d(r1 * cos(i), r1 * sin(i), 0);
        glVertex3d(r2 * cos(i), r2 * sin(i), h);
    }
    glEnd();
}