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

#ifndef STATS_H
#define STATS_H

#include "triangle.h"

#include <iostream>

class Statistics {
public:
	Statistics() : renderTime(0), totalRays(0), primRays(0), secRays(0), nrTriangles(0) {}
	double renderTime;
	int totalRays;
	int primRays;
	int secRays;
	int nrTriangles;
	friend std::ostream& operator<<(std::ostream& out, const Statistics& o);
};

#endif
