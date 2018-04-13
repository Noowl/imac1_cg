#ifndef RAYTRACER_H
	#define RAYTRACER_H

#include "shape.h" 
#include "color.h" 
#include "geometry.h" 

//structure représentant un rayon
typedef struct Ray {
    Point3D origine;
    Vector3D direction;
}Ray;

//structure représentant une sphère
typedef struct Intersection {
    Point3D position;
    Color3f couleur;
}Intersection;

Ray createRay(Point3D origine, Vector3D direction);

int intersectsSphere(Ray r, Sphere s, Intersection* i);

int intersectsCube(Ray r, Cube s, Intersection* i);

#endif 