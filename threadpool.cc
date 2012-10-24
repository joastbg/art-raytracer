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

#include "threadpool.h"
#include "raytracer.h"

ARThread::ARThread(ARWorkQueue& queue, int id, pthread_mutex_t* lock, RenderConfig* config ) : id(id), queue(queue), lock(lock), config(config) {
	pthread_create(&sthread, 0, &ARThread::start_thread, this);	
}

void ARThread::do_work() {
	
	for (;;) {
		pthread_mutex_lock(lock);
		if (queue.empty()) {
			pthread_mutex_unlock(lock);
			break;
		}
		RenderWork* work = queue.back();
		queue.pop_back();
		pthread_mutex_unlock(lock);
		//printf("Thread[%d]:\n", id);
		Tile tile(0,0,10,10);
		config->raytracer->render_tiled(work);
		//delete work;
	}
}

void ARThread::join() {
	pthread_join(sthread, NULL);
}

void ARThreadPool::run() {

	lock = new pthread_mutex_t;

	ARWorkQueue queue;
	
	int tileSize = config->options->tilesize;
	int nx = config->image->getWidth() / tileSize;
	int ny = config->image->getHeight() / tileSize;
	
	int rx = config->image->getWidth() % tileSize;
	int ry = config->image->getHeight() % tileSize;
	
	// Create render work and tiles
	for (int x=0;x<nx;x++) {
		for (int y=0;y<ny;y++) {
			queue.push_back(new RenderWork(config, new Tile(x*tileSize, y*tileSize, (x+1)*tileSize, (y+1)*tileSize)));
		}
	}
	
	for (int x=0;x<nx;x++) {
	    queue.push_back(new RenderWork(config, new Tile(x*tileSize, config->image->getHeight()-ry, (x+1)*tileSize, config->image->getHeight())));
	}
	
	for (int y=0;y<ny;y++) {
	    queue.push_back(new RenderWork(config, new Tile(config->image->getWidth()-rx, y*tileSize, config->image->getWidth(), (y+1)*tileSize)));
	}
	
	queue.push_back(new RenderWork(config, new Tile(config->image->getWidth()-rx, config->image->getHeight()-ry, config->image->getWidth(), config->image->getHeight())));
	
	std::cout << "rx: " << rx << std::endl;
	std::cout << "ry: " << ry << std::endl;

	// Create worker threads
	std::vector<ARThread*> threads;
	for (int i=0;i<config->options->threads;i++) {
		ARThread* thread = new ARThread(queue, i, lock, config);
		threads.push_back(thread);
	}	
	
	for (size_t i=0;i<threads.size();i++) {
		threads[i]->join();
	}

	for (size_t i=0;i<threads.size();i++) {
		delete threads[i];
	}
}
