/*
 * =====================================================================================
 *
 *       Filename:  matrix.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/11/2012 18:36:30
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Johan Astborg (ja), into@avantimedev.net
 *        Company:  avantimedev
 *
 * =====================================================================================
 */

#ifndef MATRIX_H
#define MATRIX_H

#include "vector3.h"

#include <iostream>

class Matrix {
public:
	Matrix(); // Empty constructor sets all elements to 0

	void identity(); // set elements to identity matrix
	bool invert();
	void transpose();
	void zero(); // zero out matrix
	double getXY(int x, int y);
	void setXY(int x, int y, double value);
	void set(int i, double value);
	void set(double (&arr)[16]);
	void set(const Matrix& matrix);
	// overloaded operators +, -, *, /, (x,y)
	// matrix * vector
	// matrix * scalar
	
	Vector3 transform(Vector3& v);

	friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);
	friend Matrix operator-(const Matrix& lhs, const Matrix& rhs);
	friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);
	friend Matrix operator*(const Matrix& lhs, const double scalar);
	
	double operator()(const int col, const int row);
	void operator()(); // zero out matrix
	void operator=(const Matrix& matrix);
	bool operator==(const Matrix& matrix);
	// determinant?

	friend std::ostream &operator<<(std::ostream& out, const Matrix& matrix);
double elems[16]; // or row major order
private:
	
};

#endif
