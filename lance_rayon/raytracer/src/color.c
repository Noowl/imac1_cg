#include "../include/color.h" 

/* Fonction qui calcule la somme de deux couleurs */
Color3f addColors(Color3f c1, Color3f c2){
	c1.r = c1.r + c2.r;
	c1.g = c1.g + c2.g;
	c1.b = c1.b + c2.b;
	return c1;
}

/* L’équivalent pour la soustraction, la multiplication et la division. */
Color3f subColors(Color3f c1, Color3f c2){
	c1.r = c1.r - c2.r;
	c1.g = c1.g - c2.g;
	c1.b = c1.b - c2.b;
	return c1;
}
Color3f multColors(Color3f c1, Color3f c2){
	c1.r = c1.r * c2.r;
	c1.g = c1.g * c2.g;
	c1.b = c1.b * c2.b;
	return c1;
}
Color3f divColors (Color3f c1, Color3f c2){
	if (c2.r == 0 || c2.g == 0 || c2.b == 0)
		printf("Pas de division par zero stp\n");
	else {
		c1.r = c1.r / c2.r;
		c1.g = c1.g / c2.g;
		c1.b = c1.b / c2.b;
	}
	return c1;
}

/* fonctions de multiplication et division d’une couleur par un scalaire */
Color3f multColor(Color3f c, float a){
	c.r = a*c.r;
	c.g = a*c.g;
	c.b = a*c.b;
	return c;
}
Color3f divColor(Color3f c, float a){
	if (a != 0){
		c.r = a/c.r;
		c.g = a/c.g;
		c.b = a/c.b;
	} else 
		printf("Pas de division par zero stp\n");
	return c;
}