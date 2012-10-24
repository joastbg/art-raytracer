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

#ifndef SCENE_H
#define SCENE_H

#include "triangle.h"
#include "stats.h"
#include "color.h"
#include "triangle.h"
#include "light.h"
#include "aabb.h"

#include <vector>

typedef std::vector<Triangle*> Triangles;
typedef std::vector<Light*> Lights;

class Scene {
public:
	Scene(Statistics& stats, Color& background) : stats(stats), background(background) {
                lights.push_back(new PointLight(Color(1.0, 1.0, 1.0), Vector3(4, 7, 5)));
        }
	void addTriangle(Triangle* triangle);
        
        void preprocess();
        
        int intersect(Ray& ray, double& rayPos, Triangle** triangle, double& u, double& v);
	int intersect_shadow(Ray& ray, double& rayPos, Triangle** triangle); // Optimized for shadows
        
        Lights& getLights() { return lights; }
	//Triangles& getTriangles() { return triangles; }
private:
	Triangles triangles;
        Lights lights;
        BoundingBox* box;
	Statistics& stats;
	Color& background;
};

#endif
