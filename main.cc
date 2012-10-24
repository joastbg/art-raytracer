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

#include "options.h"
#include "arcore.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#define AR_VERSION "0.0.4"

void usage() {
	std::cout << "usage: ar [--threads n] [--outfile filename] [--width px] [--height px] [--infile filename] [--scene n] [--help]" << std::endl;
}

void banner() {
	std::cout << "ar (avantime raytracer) v" << AR_VERSION << std::endl;
	std::cout << "Copyright 2011-2012 Johan Astborg" << std::endl;
}

int main (int argc, char *argv[]) {

	Options options;
	if (argc == 1) usage();	
	for (int i = 1; i < argc; ++i) {
		if (!strncmp(argv[i], "--threads", 8)) options.threads = atoi(argv[++i]);
		if (!strncmp(argv[i], "--width", 8)) options.width = atoi(argv[++i]);
		if (!strncmp(argv[i], "--height", 8)) options.height = atoi(argv[++i]);
		if (!strncmp(argv[i], "--outfile", 9)) options.outfile = argv[++i];
		if (!strncmp(argv[i], "--infile", 8)) options.infile = argv[++i];
		if (!strncmp(argv[i], "--scene", 7)) options.scene = atoi(argv[++i]);
		if (!strncmp(argv[i], "--help", 6) || !strncmp(argv[i], "-h", 2)) usage();
	}

	banner();

	// Init avantime raytracer
	ARCore arcore(options);
	arcore.run();
	
	return 0;	
}
