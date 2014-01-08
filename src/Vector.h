/* 
 * File:   Vector.h
 * Author: ivpusic
 *
 * Created on January 7, 2014, 8:57 PM
 */

#ifndef VECTOR_H
#define	VECTOR_H

#include <math.h>

class Vector {
public:
    Vector();
    void normalize(double *v);
    void vproduct(double *v, double a0, double a1, double a2, double b0, double b1, double b2);
    Vector(const Vector& orig);
    virtual ~Vector();
private:

};

#endif	/* VECTOR_H */

