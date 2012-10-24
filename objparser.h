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

#ifndef OBJPARSER_H
#define OPJPARSER_H

#include "scene.h"
#include "stats.h"

#include <string>

class ObjParser {
public:
	ObjParser(std::string filename) : filename(filename) {}
	bool parseMaterial(std::string objline);
	bool parse(Scene& scene);
private:
	std::string filename;
};

#endif
