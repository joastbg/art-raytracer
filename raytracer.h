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

#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "camera.h"
#include "scene.h"
#include "options.h"
#include "image.h"
#include "ray.h"
#include "color.h"
#include "vector3.h"
#include "threadpool.h"
#include "tile.h"

#include <stdlib.h>
#include <string>
#include <sstream>
#include <list>
#include <iostream>
#include <assert.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <vector>

class Raytracer;
class RenderConfig {
public:
Camera* camera;
Scene* scene;
Image* image;
Options* options;
Raytracer* raytracer;
};

class RenderWork {
public:
RenderWork(RenderConfig* config, const Tile* tile) : config(config), tile(tile) {}
RenderConfig* config;
const Tile* tile;
};

class Raytracer {
public:
	Raytracer() {}
	bool render(Camera* camera, Scene* scene, Image* image, Options* options);
	bool render_tiled(RenderWork* work);
	bool trace(Ray& ray, Color& c, int depth, RenderWork* work);
private:
    //RenderConfig config;
};

#endif
