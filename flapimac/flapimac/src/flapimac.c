#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "world.h"
#include "player.h"
#include "spaceship.h"

int MAP_WIDTH = 24;
int MAP_HEIGHT = 16;

/* Dimensions de la fenêtre */
static unsigned int WINDOW_WIDTH = 1080;
static unsigned int WINDOW_HEIGHT = 720;

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000/20;

void resizeViewport() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0., MAP_WIDTH, 0., MAP_HEIGHT);
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
}


int main(int argc, char** argv) {
    Player player;
    //player = allocPlayer(1, 2, 248, 254, 14);

    Enemies enemies;
    enemies = NULL;
        
    Walls walls;
    walls = NULL;

    Pshot ps;
    ps = NULL;

    initializeWorld(&player, &enemies, &walls);
    /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    
    /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
    if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
        fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
        return EXIT_FAILURE;
    }
    SDL_WM_SetCaption("Flapimac", NULL);
    resizeViewport();
    
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    int loop = 1;
    
    int action;
    int mode = 0;
    int selection;

    /* Boucle d'affichage */
    while(loop) {

        /* Récupération du temps au début de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Code de dessin */

        glClear(GL_COLOR_BUFFER_BIT); // Toujours commencer par clear le buffer
        
        drawPlayer(player);
        staticPlayer(&player);
        
        collisionEnemies(&player, enemies);
        collisionObstacles(&player, walls);
        collisionMissilesEnemies(enemies, ps);
        collisionMissilesObstacles(walls, ps);
        
        drawShot(ps);
        moveShot(&ps);
        glTranslatef(-0.2,0,0);
        drawEnemies(enemies);
        drawWalls(walls);
        
       
        if (mode == 1){
            movePlayer(&player, action);
        }

        /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e)) {

            /* L'utilisateur ferme la fenêtre : */
            if(e.type == SDL_QUIT) {
                loop = 0;
                break;
            }
            
            /* Quelques exemples de traitement d'evenements : */
            
            switch(e.type){
                case SDL_KEYDOWN:
                    selection = e.key.keysym.sym;
                    
                    if (selection == SDLK_UP){
                        mode = 1;
                        action = 1;
                    }
                    if (selection == SDLK_DOWN){
                        mode = 1;
                        action = 0;
                    }
                    break;
                case SDL_KEYUP:
                    selection = e.key.keysym.sym;
                    mode = 0;
                    if (selection == SDLK_SPACE){
                        mode = 2;
                    }
                    if (mode == 2){
                        addMissile(&ps, player);
                    }

                break;
                
            }
        }

        /* Echange du front et du back buffer : mise à jour de la fenêtre */
        SDL_GL_SwapBuffers();

        /* Calcul du temps écoulé */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;

        /* Si trop peu de temps s'est écoulé, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }


    /* Liberation des ressources associées à la SDL */ 
    SDL_Quit();

    return EXIT_SUCCESS;
}
