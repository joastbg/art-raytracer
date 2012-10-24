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

#include "timer.h"

void Timer::start() {
	gettimeofday(&s, NULL);
}

double Timer::stop() {
	struct timeval e;
	gettimeofday(&e, NULL);
	long seconds  = e.tv_sec  - s.tv_sec;
	long useconds = e.tv_usec - s.tv_usec;
	return (((seconds) * 1000 + useconds/1000.0) + 0.5) / 1000.0;
}
