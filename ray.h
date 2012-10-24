/*
 * =====================================================================================
 *
 *       Filename:  aabb.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/05/2012 20:49:30
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Johan Astborg (ja), into@avantimedev.net
 *        Company:  avantimedev
 *
 * =====================================================================================
 */

#ifndef RAY_H
#define RAY_H

#include "vector3.h"

class Ray {
public:
    Ray(const Vector3& start, const Vector3& dir) : start(start), dir(dir) {}
    Vector3 pointAt(float l) {
        return start + (dir * l);
    }
    Ray reflectAt(Vector3& normal, Vector3& point) {
        //Vector3 tmp = normal * (2 * (normal * direction))
    }
    Vector3 start;
    Vector3 dir;

    friend std::ostream& operator<<(std::ostream& out, const Ray& r);
};

#endif
