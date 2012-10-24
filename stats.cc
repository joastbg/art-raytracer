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

#include "stats.h"

#include <iomanip>

std::ostream& operator<<(std::ostream& out, const Statistics& o) {
	out << std::endl;
	out << "-- Statistics" << std::endl;
	out << "Rendering time (s):\t" << std::setprecision(4) << o.renderTime << std::endl;
	out << "Total nr of rays:\t" << o.totalRays << std::endl;
	out << "Primary rays:\t\t" << o.primRays << std::endl;
	out << "Secondary rays:\t\t" << o.secRays << std::endl;
	out << "Triangles:\t\t" << o.nrTriangles;
	return out;
}
