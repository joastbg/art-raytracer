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

#ifndef ARCORE_H
#define ARCORE_H

#include "options.h"

class ARCore {
public:
	ARCore(Options options) : options(options) {}
	void run();
private:
	const Options& options;
};

#endif
