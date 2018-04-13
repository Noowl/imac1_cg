#include <stdlib.h>
#include <stdio.h>
#include "geometry.h" 
#include "color.h" 

int main(int argc, char** argv) {
	Point3D p1 = pointXYZ(0,0,0);
	Vector3D v1 = vectorXYZ(1,2,0);
	Vector3D v2 = vectorXYZ(0.5,1,-2.0);
	Vector3D v3 = vectorXYZ(0.2,-1,0);
	printPoint3D(pointPlusVector(p1,v1));
	printVector3D(addVectors(v2,v3));
	printVector3D(subVectors(v2,v3));
	printVector3D(multVector(v2,2));
	printVector3D(multVector(v2,0));
	printVector3D(divVector(v2,0));
	printf("%f\n", dot(vectorXYZ(1,0,0),vectorXYZ(2,0,0)));
	printf("%f\n", dot(vectorXYZ(1,0,0),vectorXYZ(0,1,0)));
	printf("%f\n", norm(vectorXYZ(2,0,0)));
	printf("%f\n", norm(vectorXYZ(1,1,1)));
	printf("%f\n", norm(vectorXYZ(0,0,0)));
	printVector3D(normalize(vectorXYZ(1,1,1)));
	printVector3D(normalize(vectorXYZ(0,0,0)));
	return EXIT_SUCCESS;
}