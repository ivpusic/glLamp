/* 
 * File:   Vector.cpp
 * Author: ivpusic
 * 
 * Created on January 7, 2014, 8:57 PM
 */

#include "Vector.h"

Vector::Vector() {
}

void Vector::normalize(double *v) {
    double d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    v[0] /= d;
    v[1] /= d;
    v[2] /= d;
}

void Vector::vproduct(double *v, double a0, double a1, double a2, double b0, double b1, double b2) {
    v[0] = a1 * b2 - a2 * b1;
    v[1] = a2 * b0 - a0 * b2;
    v[2] = a0 * b1 - a1 * b0;
}

Vector::Vector(const Vector& orig) {
}

Vector::~Vector() {
}

