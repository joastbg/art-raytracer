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

#include "triangle.h"

Vector3 Triangle::normalAt(double u, double v) const {
    return (v2 - v0).cross(v2 - v1).normalize();
    //return n0.normalize();
    
    // Interpolate normal btw n0, n1, n2
    //Vector3 n = n0*(1 - u - v) + n1*u + n2*v;
    //return n0.normalize();
    //Vector3 n(n0*(1.0 - u - v) + n1*u + n2*v);
    //n.normalize();
    //return n.normalize();
}

bool Triangle::intersect(const Ray& ray, double& t, double& u, double& v) {
	// the moller-trumbore test
/*
	double det, inv_det;
	//double u, v;
	
	edge1 = v1 - v0;
	edge2 = v2 - v0;
	
	pvec = r.dir.cross(edge2); // cross
	
	det = edge1.dot(pvec); // dot
        
	if (det > -0.000001 && det < 0.000001)
		return false;
		
	inv_det = 1.0 / det;
	
	tvec = r.start - v0;
	
	u = tvec.dot(pvec) * inv_det;
	
	if (u < 0.0 || u > 1.0)
		return false;
	
	//Vector(, , );
	qvec = tvec.cross(edge1); // cross
	
	v = r.dir.dot(qvec) * inv_det;
	if (v < 0.0 || u + v > 1.0)
		return false;
		
	t = edge2.dot(qvec) * inv_det;
	if (t > 0.0)
	return true;
        */
        // barycentric coordinate
        double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.dir.x, d = v0.x - ray.start.x; 
	double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.dir.y, h = v0.y - ray.start.y;
	double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.dir.z, l = v0.z - ray.start.z;
		
	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k, s = e * j - f * i;
	
	double inv_denom  = 1.0 / (a * m + b * q + c * s);
	
	double e1 = d * m - b * n - c * p;
	double beta = e1 * inv_denom;
	
	if (beta < 0.00001)
	 	return false;
	
	double r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * inv_denom;
	
	if (gamma < 0.00001)
	 	return false;
	
	if (beta + gamma > 1.0)
		return false;
			
	double e3 = a * p - b * r + d * s;
	t = e3 * inv_denom;
	
	if (t < 0.000001)
		return false;
        u = beta;
        v = gamma;
	
	return true;
}
