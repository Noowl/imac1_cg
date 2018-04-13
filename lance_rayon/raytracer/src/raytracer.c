#include "color.h" 
#include "geometry.h" 
#include "shape.h" 
#include "raytracer.h"


Ray createRay(Point3D origine, Vector3D direction){
    Ray tmp;
    tmp.origine = origine;
    tmp.direction = normalize(direction);
    return tmp;
}

float min(float  a, float b){
    if (a >= 0 && b >= 0){
        if (a < b){
            return a;
        }
        else 
            return b;
    }
    else if (a<= 0 && b >=0){
        return b;
    }
    else if (b<= 0 && a >=0){
        return a;
    }
    else 
        return 0;
}

int intersectsSphere(Ray r, Sphere s, Intersection* i){
    float a, b, c;
    a = pow(norm(r.direction),2);
    b = 2 * norm(vector(r.origine, r.direction));
    c = pow(norm(r.origine),2) - pow(s.rayon,2);
    float delta = pow(b,2)-4*a*c;
    
    if (delta > 0){
        float racine1 = (-b + sqrt(delta)) / (2*a);
        float racine2 = (-b - sqrt(delta)) / (2*a);
        float t = min(racine1, racine2);
        return t;
    }
    else if (delta == 0){
        float racine = -b / (2*a);
        return racine;
    }
    else 
        return 0;
}

int intersectsCube(Ray r, Cube s, Intersection* i){
    return 0;
}