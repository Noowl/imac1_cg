#ifndef WORLD_H
#define WORLD_H
	
	#include "player.h"
	#include "spaceship.h"

extern int MAP_WIDTH;
extern int MAP_HEIGHT;

	typedef struct obstacle {
		Coord Pmin;
		Coord Pmax;
		Color c;
		struct obstacle *next;
	} Obstacle, *Walls;

	void initializeWorld(Player *p, Enemies *e, Walls *w);
	// Fonction qui récupère un fichier .ppm et dessine un monde.
	Walls allocObstacle(int x, int y, int red, int green, int blue);
	void addObstacle(Walls *w, int x, int y, int red, int green, int blue);
	void drawObstacle(Obstacle o);
	void drawWalls(Walls w);
    int collisionObstacles(Player *p, Walls w);
    int collisionMissilesObstacles(Walls w, Pshot s);

#endif