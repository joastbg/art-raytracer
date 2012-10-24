/*
 * =====================================================================================
 *
 *       Filename:  kdtree.h
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

#ifndef KDTREE_H
#define KDTREE_H

#ifdef ENABLE_KDTREE

#include "triangle.h"
#include "aabb.h"

class KdTreeNode {
public:
	KdTreeNode(int axis) : axis(axis) {}
	void add(Triangles& triangles, int currlevel, int maxlevel) {
		// Check stop criterion
		if (triangles.size() < 4 || currlev == maxlevel) {
			// Make leaf node
			for (int i=0;i<triangles.size();i++) {
				leafTriangles.push_back(triangles[i]);
			}			
			return;
		}
		
		// Calculate split position (median)
		
		// Split triangles into buffers
		Triangles leftBuffer;
		Triangles rightBuffer;
		for (int i=0;i<triangles.size();i++) {
			if (triangles[i]->v0[axis] <= splitval || triangles[i]->v0[axis] <= splitval || triangles[i]->v0[axis] <= splitval) {
				leftBuffer.push_back(triangles[i]);
			}
			if (triangles[i]->v0[axis] > splitval || triangles[i]->v0[axis] > splitval || triangles[i]->v0[axis] > splitval) {
				leftBuffer.push_back(triangles[i]);
			}
		}
		left = new KdTreeNode((axis+1)%3);
		left->add(leftBuffer, currlevel+1, maxlevel);
		right = new KdTreeNode((axis+1)%3);
		left->add(leftBuffer, currlevel+1, maxlevel);
	}
//private:
	int axis;
	Triangles leafTriangles;
	double splitval;
	const int axis;
	KdTreeNode* left;
	KdTreeNode* right;
};

class Tupple {
public:
	Tupple(KdTreeNode *node, double tmin, double tmax) : node(node), tmin(tmin), tmax(tmax) {}
	KdTreeNode *node;
	double tmin;
	double tmax;
};

// comparator
class AxisComparator {
public:
	AxisComparator(int axis) : axis(axis) {}
	bool operator() (Triangle& lhs, Triangle& rhs) {
		// compare lhs.v[axis] to rhs.v[axis]
		return true;
	}
	int axis;
};

class KdTree {
public:
	KdTree(Triangles& triangles) : maxlevel(16) {
		// Create box
		box = new BoundingBox();
		// Create root note
		root = new KdTreeNode();
		// Add triangles
		root->add(triangles, 0, maxlevel);
	}
	
	bool closest_intersection(Triangles* triangles) {
		// Return closest intersection from a list of triangle primitives
	}
	
	bool intersect(Ray& ray, double tmin, double tmax, double t) {
		// Check intersection with bounding box
		if (!box->intersect(ray)) return false;
		std::stack<Tupple> stack;
		stack.push(Tupple(root, tmin, tmax));
		while (!stack.empty()) {
			Tupple t = stack.top();
			stack.pop();
			KdTreeNode *node = t.node;
			while (node->leafTriangles() == 0) {
				double st = (node.splitval - ray.start[node.axis) / ray.dir[node.axis];
				KdTreeNode *near;
				KdTreeNode *far;
				if (ray.start[node.axis] < node.splitval) {
					near = node.left;
					far = node.rigth;
				} else {
					near = node.right;
					far = node.left;
				}
				
				if (t >= tmax || st < 0) {
					node = near;
				} else if (st <= tmin) {
					node = far;
				} else {
					stack.push(Tupple(far, t, tmax));
					node = near;
					tmax = st;
				}			
			}
		}
		
		if (node->leafTriangles() != 0) {
			// Intersect ray with each triangle
			return closest_intersection(node->leafTriangles);
		}
		return false;
	}
private:
	int maxlevel;
	KdTreeNode* root;
	BoundingBox* box;
};

#endif
#endif
