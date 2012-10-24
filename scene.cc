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

#include "scene.h"

#include <limits>

void Scene::addTriangle(Triangle* triangle) {
        triangles.push_back(triangle);
	stats.nrTriangles++;
}

void Scene::preprocess() {
    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double minZ = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::min();
    double maxY = std::numeric_limits<double>::min();
    double maxZ = std::numeric_limits<double>::min();

    std::vector<Vector3*> vertices;
    
    for (int i=0;i<triangles.size();i++) {
        vertices.push_back(&triangles[i]->v0);
        vertices.push_back(&triangles[i]->v1);
        vertices.push_back(&triangles[i]->v2);
    }
    
    for (int i=0;i<vertices.size();i++) {
        if (vertices[i]->x < minX) minX = vertices[i]->x;
        if (vertices[i]->x > maxX) maxX = vertices[i]->x;
        if (vertices[i]->y < minY) minY = vertices[i]->y;
        if (vertices[i]->y > maxY) maxY = vertices[i]->y;
        if (vertices[i]->z < minZ) minZ = vertices[i]->z;
        if (vertices[i]->z > maxZ) maxZ = vertices[i]->z;  
    }

    Vector3 min(minX, minY, minZ);
    Vector3 max(maxX, maxY, maxZ);

    //std::cout << "Min: " << min << std::endl;
    //std::cout << "Max: " << max << std::endl;

    box = new BoundingBox(min, max);
}

int Scene::intersect(Ray& ray, double &rayPos, Triangle** triangle, double& u, double& v) {
    
    // Check bounding box first
    if (box != NULL)
	if(box->intersect(ray) == false) return false;
    
    bool sceneCol = false;
    rayPos = std::numeric_limits<double>::infinity();	
    Triangles::iterator itr;
    
    for (itr = triangles.begin(); itr != triangles.end(); ++itr) {
	double t;
        bool objCol = false;
        objCol = (*itr)->intersect(ray, t, u, v);
        if (objCol == true && t < rayPos) {
                rayPos = t;
                *triangle = *itr;
                sceneCol = true;
        }
    }
    return sceneCol;
}