# Define the compiler options
CXXFLAGS  = -pipe -O2 -Wall -W -ansi #-pedantic-errors
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast -pthread -msse4.1 

# Define what to do when make is executed without arguments.
all: ar
	g++ -o ar -pthread main.o options.o arcore.o timer.o stats.o image.o color.o tga.o objparser.o scene.o raytracer.o triangle.o vector3.o kdtree.o threadpool.o camera.o matrix.o light.o aabb.o
ar: main.o arcore.o options.o timer.o stats.o image.o color.o tga.o objparser.o scene.o raytracer.o triangle.o vector3.o kdtree.o threadpool.o camera.o matrix.o light.o aabb.o

# Define the rules for the object files.
main.o: main.cc
		g++ -c $(CXXFLAGS) main.cc
arcore.o: arcore.cc arcore.h
		g++ -c $(CXXFLAGS) arcore.cc
options.o: options.cc options.h
		g++ -c $(CXXFLAGS) options.cc
timer.o: timer.cc timer.h
		g++ -c $(CXXFLAGS) timer.cc
stats.o: stats.cc stats.h
		g++ -c $(CXXFLAGS) stats.cc
image.o: image.cc image.h
		g++ -c $(CXXFLAGS) image.cc
color.o: color.cc color.h
		g++ -c $(CXXFLAGS) color.cc
tga.o: tga.cc tga.h
		g++ -c $(CXXFLAGS) tga.cc
objparser.o: objparser.cc objparser.h
		g++ -c $(CXXFLAGS) objparser.cc
scene.o: scene.cc scene.h
		g++ -c $(CXXFLAGS) scene.cc
raytracer.o: raytracer.cc raytracer.h
		g++ -c $(CXXFLAGS) raytracer.cc
triangle.o: triangle.cc triangle.h
		g++ -c $(CXXFLAGS) triangle.cc
vector3.o: vector3.cc vector3.h
		g++ -c $(CXXFLAGS) vector3.cc
kdtree.o: kdtree.cc kdtree.h
		g++ -c $(CXXFLAGS) kdtree.cc
threadpool.o: threadpool.cc threadpool.h
		g++ -c $(CXXFLAGS) threadpool.cc
camera.o: camera.cc camera.h
		g++ -c $(CXXFLAGS) camera.cc
matrix.o: matrix.cc matrix.h
		g++ -c $(CXXFLAGS) matrix.cc
light.o: light.cc light.h
		g++ -c $(CXXFLAGS) light.cc
aabb.o: aabb.cc aabb.h
		g++ -c $(CXXFLAGS) aabb.cc
clean:
		rm -rf *o ar
		
run:
		./ar
		
runa:
		./ar --threads 8 --outfile out.tga --width 800 --height 600 --infile test.obj
