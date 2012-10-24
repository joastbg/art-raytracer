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

#ifndef TILE_H
#define TILE_H

class Tile {
public:
	Tile(int sx, int sy, int ex, int ey) : sx(sx), sy(sy), ex(ex), ey(ey) {}
	int sx; // start x
	int sy; // start y 
	int ex;	// end x
	int ey;	// end y
};

#endif
