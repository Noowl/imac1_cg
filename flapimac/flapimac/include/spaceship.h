#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "player.h"

typedef struct spaceship {
    Coord Pmin;
    Coord Pmax;
    Color c;
    struct spaceship *next;
} Spaceship, *Enemies;

Enemies allocSpaceship(int x, int y, int red, int green, int blue);

void addSpaceship(Enemies *e, int x, int y, int red, int green, int blue);

void drawEnemies(Enemies e);

void drawSpaceship(Spaceship s);

int collisionEnemies(Player *p, Enemies e);

int collisionMissilesEnemies(Enemies e, Pshot s);

#endif