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

#include "aabb.h"

bool BoundingBox::intersect(const Ray& r) {
    // Smits’ method
    double tmin, tmax, tymin, tymax, tzmin, tzmax;
    if (r.dir.x >= 0) {
	tmin = (min.x - r.start.x) / r.dir.x;
	tmax = (max.x - r.start.x) / r.dir.x;
    } else {
	tmin = (max.x - r.start.x) / r.dir.x;
	tmax = (min.x - r.start.x) / r.dir.x;
    }
    if (r.dir.y >= 0) {
	tymin = (min.y - r.start.y) / r.dir.y;
	tymax = (max.y - r.start.y) / r.dir.y;
    }
    else {
	tymin = (max.y - r.start.y) / r.dir.y;
	tymax = (min.y - r.start.y) / r.dir.y;
    }
    if ( (tmin > tymax) || (tymin > tmax) )
	return false;
    if (tymin > tmin)
	tmin = tymin;
    if (tymax < tmax)
	 tmax = tymax;
    if (r.dir.z >= 0) {
	tzmin = (min.z - r.start.z) / r.dir.z;
	tzmax = (max.z - r.start.z) / r.dir.z;
    } else {
	tzmin = (max.z - r.start.z) / r.dir.z;
	tzmax = (min.z - r.start.z) / r.dir.z;
    }
    if ( (tmin > tzmax) || (tzmin > tmax) )
	return false;
    if (tzmin > tmin)
	tmin = tzmin;
    if (tzmax < tmax)
	tmax = tzmax;
    return ((tmin < 3000) && (tmax > 0));
}
