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

#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>
#include <cmath>

class Vector3 {
public:
	Vector3() : x(0), y(0), z(0) {}
	Vector3(double x, double y, double z) : x(x), y(y), z(z) {}
	Vector3(double (&v)[3]) : x(v[0]), y(v[1]), z(v[2]) {}
	union {
		struct {
		double x;
		double y;
		double z;
		};
		double v[3];
	};
        
        // arithmetic operators with Vector3
	inline Vector3 operator+(const Vector3& b) const { return Vector3(x + b.x, y + b.y, z + b.z); }
	inline Vector3 operator-(const Vector3& b) const { return Vector3(x - b.x, y - b.y, z - b.z); }
	//inline Vector3 operator*(const Vector3& b) const { return Vector3(x + b.x); }
	//inline Vector3 operator/(const Vector3& b) const { return Vector3(x + b.x); }
        
        // unary minus
	inline Vector3 operator-() const { return Vector3(-x, -y, -z); }
	
	// op= operators
	inline Vector3& operator+=(const Vector3& b) { x += b.x; y += b.y; z += b.z; }
	inline Vector3& operator-=(const Vector3& b) { x -= b.x; y -= b.y; z -= b.z; }
	inline Vector3& operator*=(const Vector3& b) { x *= b.x; y *= b.y; z *= b.z; }
	inline Vector3& operator/=(const Vector3& b) { x /= b.x; y /= b.y; z /= b.z; }
	
	// arithmetic operators with double
	inline Vector3 operator+(double b) const { return Vector3(x + b, y + b, z + b); }
	inline Vector3 operator-(double b) const { return Vector3(x - b, y - b, z - b); }
	inline Vector3 operator*(double b) const { return Vector3(x * b, y * b, z * b); }
	inline Vector3 operator/(double b) const { return Vector3(x / b, y / b, z / b); }
	
	// op= operators with float
	inline Vector3& operator+=(double b) { x += b; y += b; z += b; *this; }
	inline Vector3& operator-=(double b) { x -= b; y -= b; z -= b; *this; }
	inline Vector3& operator*=(double b) { x *= b; y *= b; z *= b; *this; }
	inline Vector3& operator/=(double b) { x /= b; y /= b; z /= b; *this; }
        
        // cross product
	inline Vector3 cross(const Vector3& b) const
	{
                return Vector3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	}
	
	// dot product with another vector
	inline double dot(const Vector3& b) const { return x * b.x + y * b.y + z * b.z; }

	// length of the vector
	inline double length() const { return sqrt((x * x) + (y * y) + (z * z)); }

	// 1/length() of the vector
	inline double ilength() const { return 1.0 / sqrt((x * x) + (y * y) + (z * z)); }

	// returns the vector scaled to unit length
	inline Vector3 normalize() const { 
		double il = ilength();
		return Vector3(x * il, y * il, z * il); 
	}
        
	friend std::ostream& operator<<(std::ostream& out, const Vector3& v);
};

#endif
