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

#include "camera.h"

std::ostream& operator<<(std::ostream& out, const Camera& c) {
	return out << "Camera" << c.pos << " " << c.dir;
}

Ray Camera::rayAt(double u, double v) {
    Vector3 tdir = (zdir*f + dx*(2*u+1-width)*0.5 + dy*(2*v+1-height)*0.5).normalize();
    return Ray(lookFrom, tdir);
}