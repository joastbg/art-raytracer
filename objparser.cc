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

#include "objparser.h"

#include <iostream>
#include <fstream>
#include <sstream>

bool ObjParser::parseMaterial(std::string objline) {
	// Extract MTL-filename
	std::string filename;
	filename = objline.substr(7, objline.size() - 7);
	std::cout << "Parsing material file: " << filename << std::endl;
	
	// Open MTL-file	
	std::ifstream in(filename.c_str());

	if (!in.is_open()) {
		std::cerr << std::endl << "WARNING: Unable to open material file " << filename << std::endl;
		return false;
	}

	// Start parse MTL-file
	std::string line;
	while (in.good()) {
		// Look for "newmtl"
		getline (in, line);
		std::string matname = "Default";
		if (!line.compare(0, 6, "newmtl")) {
			// Extract material name
			if (line.size() > 7) matname = line.substr(7, line.size() - 7);
			getline (in, line);
			while (line.compare(0, 1, "") && in.good()) {
				std::cout << "Material [" << matname << "] - " << line << std::endl;
				getline (in, line);
			}	
		}
	}
	return true;
}

bool ObjParser::parse(Scene& scene) {

	// Open OBJ-file
	std::ifstream in(filename.c_str());

	if (!in.is_open()) {
		std::cerr << std::endl << "ERROR: Unable to open obj file " << filename << std::endl;
		return false;
	}

	// Start parse OBJ-file
	//scene.addTriangle(Triangle(Vector3(0,0,0), Vector3(0,0,0), Vector3(0,0,0)));
	//stats.nrTriangles++;

	std::vector<Vector3> vertices;
	std::vector<Vector3> faces;
        std::vector<Vector3> normals;
        std::vector<Vector3> facenormals;
        int count=0;
        int ncount=0;
	std::string line;
	while (in.good()) {
		getline (in, line);
		//std::cout << line << std::endl;

		if (!line.compare(0, 6, "mtllib")) parseMaterial(line);

		// Extract object name
		if (!line.compare(0, 2, "o ")) {
			std::string matname = line.substr(2, line.size() - 2);
			std::cout << "object name: " << matname << std::endl;
		}
                
		// Extract vertex list
		if (!line.compare(0, 2, "v ")) {
			std::stringstream ss(line.substr(2, line.size() - 2));
			double x, y, z;
			ss >> x;
			ss >> y;
			ss >> z;
                        //x -= 1;
                        //y -= 1;
                        //z += 15;
                        count++;
			//std::cout << count << ": vertex: " << x << " "<< y  << " " << z << std::endl;
			vertices.push_back(Vector3(x, y, z));
		}
                
                // Extract vertex normal list
		if (!line.compare(0, 3, "vn ")) {
			std::stringstream ss(line.substr(3, line.size() - 3));
			double x, y, z;
			ss >> x;
			ss >> y;
			ss >> z;
                        //x -= 1;
                        //y -= 1;
                        //z += 15;
                        ncount++;
			//std::cout << ncount << ": normal: " << x << " "<< y  << " " << z << std::endl;
			normals.push_back(Vector3(x, y, z));
		}

                
		// Extract group name
		if (!line.compare(0, 2, "g ")) {
			std::string smooth = line.substr(2, line.size() - 2);
			std::cout << "group: " << smooth << std::endl;
		}
                
		// Extract smooth parameter
		if (!line.compare(0, 2, "s ")) {
			std::string smooth = line.substr(2, line.size() - 2);
			std::cout << "smooth: " << smooth << std::endl;
		}

		// Extract faces
		if (!line.compare(0, 2, "f ")) {
			std::stringstream ss(line.substr(2, line.size() - 2));
			//double a, b, c, d = 0;
                        std::string sa, sb, sc, sd;
			ss >> sa;
			ss >> sb;
			ss >> sc;
			ss >> sd;
                        
                        double a, b, c, d = 0;
                        double x, y, z, w;
                        // include normals
                        if (sa.find("//") != std::string::npos) {
                            sscanf(sa.c_str(), "%lf//%lf", &a, &x);
                            sscanf(sb.c_str(), "%lf//%lf", &b, &y);
                            sscanf(sc.c_str(), "%lf//%lf", &c, &z);
                            sscanf(sd.c_str(), "%lf//%lf", &d, &w);
                            
                            facenormals.push_back(Vector3(x, y, z));
                            if (w != 0)
                            facenormals.push_back(Vector3(x, z, w));
                        }                          
                   
			//std::cout << "face: " << a << " / " << x << ", " << b  << " / " << y << ", " << c << " / " << z << ", " << d << " / " << w << std::endl;
			faces.push_back(Vector3(a, b, c));
			if (d != 0)
                        faces.push_back(Vector3(a, c, d));
                        
		}

		if (!line.compare(0, 6, "usemtl")) {
			std::string matname = line.substr(6, line.size() - 6);
			std::cout << "material name: " << matname << std::endl;		
		}
	}

	// Create triangles from vertices and faces
        int a=0;
	for (std::vector<Vector3>::iterator itr = faces.begin(); itr != faces.end(); ++itr) {
            if (normals.size() == 0) {
                scene.addTriangle(new Triangle(vertices[(*itr).x - 1], vertices[(*itr).y - 1], vertices[(*itr).z - 1]));
            }
            else {
                //std::cout << "NORMAL" << std::endl;
                scene.addTriangle(new Triangle(vertices[(*itr).x - 1], vertices[(*itr).y - 1], vertices[(*itr).z - 1], 
                        normals[facenormals[a].x-1], normals[facenormals[a].y-1], normals[facenormals[a].z-1]));
                //std::cout << normals[facenormals[a].x-1] << " " << normals[facenormals[a].y-1] << " " << normals[facenormals[a].z-1] << std::endl;
            }
            a++;
	}
        //scene.addTriangle(new Triangle(Vector3(0.0, 0.0, 16.0), Vector3(3.0, 0.0, 16.0), Vector3(0.0, 3.0, 16.0)));
        //scene.addTriangle(new Triangle(Vector3(0.0, 0.0, 18.0), Vector3(3.0, 0.0, 18.0), Vector3(0.0, 3.0, 18.0)));
        //scene.addTriangle(new Triangle(Vector3(0.0, 0.0, 16.0), Vector3(-3.0, 0.0, 18.0), Vector3(0.0, 3.0, 16.0)));

	return true;
}
