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

#include "arcore.h"
#include "timer.h"
#include "stats.h"
#include "tga.h"
#include "image.h"
#include "scene.h"
#include "objparser.h"
#include "camera.h"
#include "raytracer.h"
#include "threadpool.h"

#include <iostream>

void ARCore::run() {

	Statistics statistics;	

	std::cout << std::endl << "-- avantime raytracer started" << std::endl << std::endl;

	// Check options
	if (!options.validate()) return;
	std::cout << options << std::endl;

	// Create scene
	Color background(0, 0, 0);
	Scene scene(statistics, background);

	// Create camera
	Camera camera(Vector3(0,0,0), Vector3(0,0,0), PI / 5.0);

	// Parse OBJ-file
	ObjParser parser(options.infile);
	if(!parser.parse(scene)) return;

	// Create render device / Image
	Image image(options.width, options.height);	

	// Meassure time start	
	Timer timer;
	timer.start();
	
	// Start rendering
	Raytracer raytracer;
	raytracer.render(&camera, &scene, &image, const_cast<Options*>(&options));
	
	// Meassure time end
	statistics.renderTime = timer.stop();
	
	// Display statistics
	std::cout << statistics << std::endl;

	// Save image to disk
	TGA tga(options.outfile);
	tga.output(image);
}
