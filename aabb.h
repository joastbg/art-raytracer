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

#ifndef AABB_H
#define AABB_H

#include "vector3.h"
#include "ray.h"

class BoundingBox {
public:
    BoundingBox(Vector3 min, Vector3 max) : min(min), max(max) {}
    bool intersect(const Ray& r);
private:
    Vector3 min;
    Vector3 max;
};

#endif
