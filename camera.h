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

#ifndef CAMERA_H
#define CAMERA_H


#include <iostream>
#include <cmath>

#include "ray.h"
#include "vector3.h"
#include "matrix.h"

const float PI = 3.1415926535897932384626433832795;

class Camera {
public:
        Camera(const Vector3& pos, const Vector3& dir, float fov = PI / 4.0) : pos(pos), dir(dir), fov(fov) { 
		// New camera code
		Vector3 lookFrom(0,0,0);
		Vector3 lookAt(0,0,0);
		Vector3 viewUp(0,1,0);
		fov = PI / 4.0;

		width = 800;
		height = 600;

		Vector3 diff = lookAt - lookFrom;
		N = (lookAt - lookFrom) / diff.length(); // Normalize
		Vector3 diff2 = N.cross(viewUp);
		Vector3 U = (N.cross(viewUp)) / diff2.length(); // Normalize
		Vector3 diff3 = U.cross(N);
		Vector3 V = (U.cross(N)) / diff3.length(); // Normalize

		xInc = U * (2*tan(fov/2.0))/width;
		yInc = V * (2*tan(fov/2.0))/width;

		/*
		// Image plane corners
		Vector p1 = Vector(-1,1,0); // Upper left
		Vector p2 = Vector(1,1,0); // Upper right
		Vector p3 = Vector(1,-1,0); // Lower right
		Vector p4 = Vector(-1,-1,0); // Lower left

		// Calc camera direction vector
		Vector zaxis = (lookAt - lookFrom).normalize();
		
		// Camera lookup (y-axis)
		Vector up = Vector(0,1,0)

		// Create camera view system basis
		Vector xaxis = up ^ zaxis;
		*/	
	}
	//~Camera();

	void initView(int width, int height) {
		this->width = width;
		this->height = height;
                
                lookFrom = Vector3(0,3,-1);
		Vector3 lookAt(0,0,10);

		f = (lookAt - lookFrom).length();

		//int width = 1024;
		//int height = 768;

		// Image plane corners
		Vector3 p1 = Vector3(-4, 3, 0); // Upper left
		Vector3 p2 = Vector3( 4, 3, 0); // Upper right
		Vector3 p3 = Vector3( 4,-3, 0); // Lower right
		Vector3 p4 = Vector3(-4,-3, 0); // Lower left

		// Calc camera direction vector
		zdir = (lookAt - lookFrom).normalize();

		// Camera lookup (y-axis)
		Vector3 up = Vector3(0,1,0);

		// Create camera view system basis
		Vector3 xaxis = up.cross(zdir); // (cross)
		Vector3 yaxis = xaxis.cross(-zdir); // (cross)
		Vector3 zaxis = (xaxis.cross(yaxis)).normalize(); // (cross)

		// Setup transformation matrix
		Matrix m;
		m.elems[0] = xaxis.x, m.elems[1] = xaxis.y, m.elems[2] = xaxis.z;
		m.elems[4] = yaxis.x, m.elems[5] = yaxis.y, m.elems[6] = yaxis.z;
		m.elems[8] = zaxis.x, m.elems[9] = zaxis.y, m.elems[10] = zaxis.z;
		m.invert();
		m.elems[3] = lookFrom.x, m.elems[7] = lookFrom.y, m.elems[11] = lookFrom.z;

		// Calculate interpolation vectors
		dx = ((p2 - p1) * (1.0 / width));
		dy = ((p1 - p4) * (1.0 / height));

                             
		// Move camera
		lookFrom = m.transform(lookFrom);
		p1 = m.transform(p1);
		p2 = m.transform(p2);
		p3 = m.transform(p3);
		p4 = m.transform(p4);
	}

	Ray rayAt(double u, double v);

	friend std::ostream& operator<<(std::ostream &out, const Camera &c);
private:
	Vector3 pos;
	Vector3 dir;
	Vector3 zdir;
	double fov; // Default 45 degrees
	Vector3 top;
	double tan_x;
	double tan_y;
	int height;
	int width;
	double f;
	Vector3 lookFrom;
	Vector3 N;
	Vector3 xInc;
	Vector3 yInc;
	Vector3 dx, dy;
};

#endif
