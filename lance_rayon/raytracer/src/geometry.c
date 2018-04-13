#include "color.h" 
#include "geometry.h" 
#include "shape.h" 
#include "raytracer.h"

/*Construit le point (x, y, z)*/
Point3D pointXYZ(float x, float y, float z){
	Point3D tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return tmp;
}

/*Construit le vecteur (x, y, z)*/
Vector3D vectorXYZ(float x, float y, float z){
	Vector3D tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return tmp;
}

/*Construit le vecteur AB = B − A*/
Vector3D vector(Point3D A, Point3D B){
	Vector3D tmp;
	tmp.x = B.x - A.x;
	tmp.y = B.y - A.y;
	tmp.z = B.z - A.z;
	return tmp;
}

/*Construit le point P + V*/
Point3D pointPlusVector(Point3D P, Vector3D V){
	Point3D tmp;
	tmp.x = P.x + V.x;
	tmp.y = P.y + V.y;
	tmp.z = P.z + V.z;
	return tmp;
}

/*fonctions d’addition et soustraction de vecteurs*/
Vector3D addVectors(Vector3D A, Vector3D B){
	Vector3D tmp;
	tmp.x = A.x + B.x;
	tmp.y = A.y + B.y;
	tmp.z = A.z + B.z;
	return tmp;
}
Vector3D subVectors(Vector3D A, Vector3D B){
	Vector3D tmp;
	tmp.x = A.x - B.x;
	tmp.y = A.y - B.y;
	tmp.z = A.z - B.z;
	return tmp;
}

/*fonctions de multiplication et division d’un vecteur par un scalaire*/
Vector3D multVector(Vector3D V, float a){
	Vector3D tmp;
	tmp.x = a * V.x;
	tmp.y = a * V.y;
	tmp.z = a * V.z;
	return tmp;
}
Vector3D divVector(Vector3D V, float a){
	if (a != 0){
		V.x = V.x / a;
		V.y = V.y / a;
		V.z = V.z / a;
	} else 
		printf("Pas de division par zero stp\n");
	return V;
}

/*Fonction calculant le produit scalaire de deux vecteurs : Cela représente la norme de la projection d'un vecteur sur l'autre * la norme de cet autre vecteur */
float dot(Vector3D A, Vector3D B){
	return A.x*B.x + A.y*B.y + A.z*B.z;
}

/*fonction calculant la norme d’un vecteur*/
float norm(Vector3D A){
	return sqrt(pow(A.x, 2) + pow(A.y, 2) + pow(A.z, 2));
}

/*fonction retournant le vecteur normalisé passé en paramètre*/
Vector3D normalize(Vector3D A){
	float norme = norm(A);
	if (norme != 0){
		A.x = A.x / norme;
		A.y = A.y / norme;
		A.z = A.z / norme;
	}
	else 
		printf("Pas de division par zero stp\n");
	return A;
}


/* Fonctions qui affichent les vectors et points passés en paramètre */
void printVector3D(Vector3D v){
	printf("Coordonnées du vecteur : \n");
	printf("x : %f\n", v.x);
	printf("y : %f\n", v.y);
	printf("z : %f\n", v.z);
}
void printPoint3D(Point3D p){
	printf("Coordonnées du point : \n");
	printf("x : %f\n", p.x);
	printf("y : %f\n", p.y);
	printf("z : %f\n", p.z);
}