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

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector3.h"
#include "ray.h"

class Triangle {
public:
	Triangle(const Vector3& v0, const Vector3& v1, const Vector3& v2) : v0(v0), v1(v1), v2(v2) {}
        Triangle(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Vector3& n0, const Vector3& n1, const Vector3& n2) : v0(v0), v1(v1), v2(v2), n0(n0), n1(n1), n2(n2) {}
	bool intersect(const Ray& r, double& t, double& u, double& v);
        Vector3 normalAt(double u, double v) const;
        
	Vector3 v0;
	Vector3 v1;
	Vector3 v2;
        
        Vector3 n0;
        Vector3 n1;
        Vector3 n2;
        
        // Intersection test vectors
        Vector3 edge1; 
        Vector3 edge2; 
        Vector3 tvec;
        Vector3 pvec;
        Vector3 qvec;
};

#endif
