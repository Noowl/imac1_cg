#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>
#include <assert.h>
#include "player.h"

/*
*   allocates memory to the player
*   parameters are : x : position y
*                    y : position y
*                    red : color rgb
*                    green : color rgb
*                    blue : color rgb
*   @return Player
*/
Player allocPlayer(int x, int y, int red, int green, int blue){
	Player p;
	p.Pmin.x = x;
	p.Pmin.y = y;
	p.Pmax.x = x + 1;
	p.Pmax.y = y + 1;
    
    p.c.red = red;
    p.c.green = green;
    p.c.blue = blue;
	return p;
}

Pshot allocPmissile(float x, float y, int red, int green, int blue){
    Pshot m;
    m = malloc(sizeof(Pmissile));
    if( m != NULL){
        m->Pmin.x = x;
        m->Pmin.y = y;
        m->Pmax.x = x + 1;
        m->Pmax.y = y + 1;

        m->c.red = red;
        m->c.green = green;
        m->c.blue = blue;
        m->next = NULL;
    }
    return m;
}

/*  
*   draw a square which represents the player
*/
void drawPlayer(Player p){
    glColor3ub(p.c.red, p.c.green, p.c.blue);
    glBegin(GL_QUADS);
		glVertex2f(p.Pmax.x-1, p.Pmax.y);
		glVertex2f(p.Pmax.x, p.Pmax.y);
        glVertex2f(p.Pmin.x+1, p.Pmin.y);
		glVertex2f(p.Pmin.x, p.Pmin.y);
	glEnd();
}

/*  
*   Takes in parameters the player and the action : 0 or 1
*   1 : player goes up
*   0 : player goes down
*/
void movePlayer(Player *p, int action){
    if (action == 1){
        if (p->Pmax.y < MAP_HEIGHT){
            p->Pmin.y++;
            p->Pmax.y++;
        }
    }
    else if (p->Pmin.y > 0){
        p->Pmin.y--;
        p->Pmax.y--;
    }
}

void staticPlayer(Player *p){
    p->Pmin.x = p->Pmin.x + 0.2;
    p->Pmax.x = p->Pmax.x + 0.2;
}

void addMissile(Pshot *s, Player p){
    if(*s == NULL){
        *s = allocPmissile(p.Pmin.x, p.Pmin.y, p.c.red, p.c.green, p.c.blue);
    }
    else{
        addMissile(&(*s)->next, p);
    }
}

void drawMissile(Pmissile pm){
    glColor3ub(pm.c.red, pm.c.green, pm.c.blue);
    glBegin(GL_QUADS);
        glVertex2f(pm.Pmax.x-1, pm.Pmax.y);
        glVertex2f(pm.Pmax.x, pm.Pmax.y);
        glVertex2f(pm.Pmin.x+1, pm.Pmin.y);
        glVertex2f(pm.Pmin.x, pm.Pmin.y);
    glEnd();
}

void drawShot(Pshot ps){
    if(ps != NULL){
        drawMissile(*ps);
        drawShot(ps->next);
    }
}

void moveShot(Pshot *ps){
    if(*ps != NULL){
        (*ps)->Pmin.x = (*ps)->Pmin.x + 0.4;
        (*ps)->Pmax.x = (*ps)->Pmax.x + 0.4;
        moveShot(&(*ps)->next);
    }
}
