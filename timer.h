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

#ifndef TIMER_H
#define TIMER_H

#include <stdlib.h>
#include <sys/time.h>

class Timer {
public:
	Timer() : seconds(0) {}
	void start();
	double stop();
	struct timeval s;
	double seconds;
};

#endif
