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

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "options.h"
#include "tile.h"
#include <iostream>
#include <vector>
#include <stdio.h>

class RenderConfig;
class RenderWork;

typedef std::vector<RenderWork*> ARWorkQueue;

class ARThread {
public:
	ARThread(ARWorkQueue& queue, int id, pthread_mutex_t* lock, RenderConfig* config);
	void join();
private:
	int id;
	pthread_t sthread;
	ARWorkQueue& queue;
	pthread_mutex_t* lock;
	//const Raytracer* raytracer;
	RenderConfig* config;

	void do_work();
	static void *start_thread(void *obj) {	
		reinterpret_cast<ARThread*>(obj)->do_work();
		return 0;
	}
};

class ARThreadPool {
public:
	ARThreadPool(RenderConfig* config) : config(config) {}
	void run();
private:
	RenderConfig* config;
	pthread_mutex_t* lock;
};

#endif
