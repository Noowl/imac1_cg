#ifndef PLAYER_H
#define PLAYER_H

extern int MAP_WIDTH;
extern int MAP_HEIGHT;

/*
*   defines a coordinate structure for the x and the y axes
*/
typedef struct coord {
    float x;
    float y;
} Coord;

/*
*   defines a color structure red, green, bleu
*/
typedef struct color {
    int red;
    int green;
    int blue;
} Color;

/*
*   defines a player structure with its Pmin and Pmax coordinates
*/
typedef struct player {
    Coord Pmin;
    Coord Pmax;
    Color c;
} Player;

typedef struct pMissile {
	Coord Pmin;
    Coord Pmax;
    Color c;
    struct pMissile *next;
} Pmissile, *Pshot;

/*
*   allocates memory to the player
*   parameters are : x : position y
*                    y : position y
*                    red : color rgb
*                    green : color rgb
*                    blue : color rgb
*   @return Player
*/
Player allocPlayer(int x, int y, int red, int green, int blue);
Pshot allocPmissile(float x, float y, int red, int green, int blue);
void addMissile(Pshot *s, Player p);
void drawShot(Pshot ps);
void moveShot(Pshot *ps);

/*  
*   draw a square which represents the player
*/
void drawPlayer(Player p);

/*  
*   Takes 0 or 1
*   1 : player goes up
*   0 : player goes down
*/
void movePlayer(Player *p, int action);
void staticPlayer(Player *p);




#endif