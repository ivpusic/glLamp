/* 
 * File:   Bodies.h
 * Author: ivpusic
 *
 * Created on January 7, 2014, 8:47 PM
 */

#ifndef BODIES_H
#define	BODIES_H

#include <math.h>
#include <GL/freeglut.h>
#include "Vector.h"

class Bodies {
public:
    Bodies();
    void drawRectangle(double w, double h, double l);
    void drawCube(double a);
    void drawCicle(double r);
    void drawCoordinateSystem();
    void drawSphere(double r);
    void drawLetterO(double r);
    void drawCylinder(double r, double h, int m);
    void drawEllipticCylinder(double a, double b, double h, int m);
    void drawCone(double r, double h, int m);
    void drawTruncatedCone(double r1, double r2, double h, int m);

private:
    Vector vector;
    double v[3];
};

#endif	/* BODIES_H */

