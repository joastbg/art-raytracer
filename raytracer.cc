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

#include "raytracer.h"

bool Raytracer::render(Camera* camera, Scene* scene, Image* image, Options* options) {
//bool Raytracer::render(Camera& camera, Scene& scene, Image& image, const Options& options) {

        // Test threads
	RenderConfig config;
	scene->preprocess();
        
	// Init camera view
	camera->initView(image->getWidth(), image->getHeight());
	config.camera = camera;
	config.scene = scene;
	config.image = image;
	config.options = options;
	config.raytracer = this;
	ARThreadPool threadPool(&config);
	threadPool.run();

    return true;
}

bool Raytracer::render_tiled(RenderWork* work) {
    const Tile *tile = work->tile;
    //printf("Render tile %d %d %d %d\n", tile->sx, tile->sy, tile->ex, tile->ey);
    
    Color c(0.0, 0.0, 0.0);	
    Color c2(0.0, 0.0, 0.0);
    Color bg(0.1,0.1,0.1);
    for (int y = tile->sy; y < tile->ey; ++y) {
	for (int x = tile->sx; x < tile->ex; ++x) {	
	    Ray ray = work->config->camera->rayAt(x,y);
	    if(trace(ray, c, 0, work)) {
		for (double i=0;i<2.0;i+=0.1) {
		    Ray ray = work->config->camera->rayAt(double(x)+i,double(y)+i);
		    trace(ray, c2, 0, work);
		    c += c2;
		}
		c*=0.05;
		work->config->image->setColor(x, y, c);
	    } else {
                work->config->image->setColor(x, y, bg);
	    }

	    //usleep(delay);
	}
    }	
}

bool Raytracer::trace(Ray& ray, Color& c, int depth, RenderWork* work) {  
    
    Triangle *triangle = NULL;
    double t = 0.0;
    Scene* scene = work->config->scene;
    double u, v;
    if (scene->intersect(ray, t, &triangle, u, v) == false) {
        return false;
    }
    
    Vector3 colPoint = ray.pointAt(t);
    Color testColor = Color(0.9, 0.9, 0.9);
    Lights::iterator iter;
    for (iter = scene->getLights().begin(); iter != scene->getLights().end(); ++iter) {
        Light *p = *iter;
        
        c = testColor * 0.15;
        
        PointLight *pl = dynamic_cast<PointLight*>(p);              
	if (pl == NULL)
                continue;
        
        // Calculate light component from point light
        Vector3 newStart = (ray.start + ray.dir * t);
	Vector3 dist = (pl->getPosition() - newStart).normalize();
	Vector3 n = triangle->normalAt(u, v);// newStart - surface->getPosition();
        
        // If normal points in wrong dir
        //if((n.dot(ray.dir)) > 0.0) n=-n;
        
        double tt = 0;		
        Ray toLight = Ray(colPoint, (pl->getPosition() - colPoint).normalize());
	//Surface *surface2 = NULL;
        double max = (pl->getPosition() - colPoint).length();        
	Triangle *triangle2 = NULL;
	if (scene->intersect(toLight, tt, &triangle2, u, v))
            if (tt < max)
		continue;
        
        if (n.dot(dist) > 0) {
            Vector3 arg = (dist * (1/t)).normalize();
            Ray lightRay(newStart, arg);

            float lambert = (lightRay.dir.dot(n));
            //if (dynamic_cast<Triangle*>(surface))
            //std::cout << "lambert: " << lambert << std::endl;
            Color cl = pl->getColor();
            c += testColor * lambert * 0.5;
           
            //c += testColor * lambert * 0.5;
            
            //c += cl * lambert * 0.5;
            //c += cl * lambert * 0.5;
       }
        
        Vector3 R = (n*n.dot(toLight.dir)*2-toLight.dir);//.normalize();
        R.normalize();
        double Is = 0;
        double dot = R.dot(ray.dir);
        if (dot < 0) {
                Is = 0.9 * pow( dot, 20 );//(R * ray.getDirection())*(R * ray.getDirection())*(R * ray.getDirection())*(R * ray.getDirection());
        }
        c += Is;
        
        //Vector3 normal = surface->normalAt(colPoint);
	
    }   
    return true;
}
