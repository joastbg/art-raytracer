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

#ifndef CANVAS_H
#define CANVAS_H

class Canvas {
public:
	Canvas(unsigned int w, unsigned int h) : width(w), height(h) {}

	unsigned int getWidth() const { return width; }
	unsigned int getHeight() const { return height; }

protected:
	unsigned int width;
	unsigned int height;
};

#endif
