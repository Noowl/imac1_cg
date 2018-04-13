#ifndef SHAPE_H
	#define SHAPE_H

typedef struct Sphere {
    Point3D centre;
    float rayon;
    Color3f couleur;
}Sphere;

typedef struct Cube {
    Point3D min;
    Point3D max;
    Color3f couleur;
}Cube;

Cube createCube(Point3D pMin, Point3D pMax, Color3f couleur);

Sphere createSphere(Point3D centre, float rayon, Color3f couleur);

#endif 