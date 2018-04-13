#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <time.h>

/* Dimensions de la fenêtre */
static unsigned int WINDOW_WIDTH = 500;
static unsigned int WINDOW_HEIGHT = 500;

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 10000 / 60;

typedef struct Point{
	float x, y; // Position 2D du point
	unsigned char r, g, b; // Couleur du point
	struct Point* next; // Point suivant à dessiner
} Point, *PointList;

typedef struct Primitive{
	GLenum primitiveType;
	PointList points;
	struct Primitive* next;
} Primitive, *PrimitiveList;

void scene() {
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-5, 5, -5, 5);
}

Point* allocPoint(float x, float y, unsigned char r, unsigned char g, unsigned char b) {
    /*
    On alloue un espace mémoire suffisant pour pouvoir stocker un point
    Attention : la fonction malloc() renvoie un void* qu'il faut impérativement caster en Point*.
    */
    Point* point = (Point*) malloc(sizeof(Point));
    if (!point) {
    	return NULL;
    }
    point->x = x;
    point->y = y;
    point->r = r;
    point->g = g;
    point->b = b;
    point->next = NULL;
    return point;
}

void addPointToList(Point* point, PointList* list) {
	assert(point);
	assert(list);
	if (*list == NULL) {
        /* Si le pointeur sur la liste est vide, on le modifie pour le faire pointer sur le point donné en paramètre */
		*list = point;
	} else {
        /* Sinon, on réapplique la même fonction mais sur le point suivant */
		addPointToList(point, &(*list)->next);
	}
}

void drawPoints(PointList list) {
	while(list) {
		glColor3ub(list->r, list->g, list->b);
		glVertex2f(list->x, list->y);
		list = list->next;
	}
}

void deletePoints(PointList* list) {
	assert(list);
	while (*list) {
		Point* next = (*list)->next;
		free(*list);
		*list = next;
	}
}

Primitive* allocPrimitive(GLenum primitiveType) {
    /*
    On alloue un espace mémoire suffisant pour pouvoir stocker une primitive
    Attention : la fonction malloc() renvoie un void* qu'il faut impérativement caster en Primitive*.
    */
    Primitive* primitive = (Primitive*) malloc(sizeof(Primitive));
    if (!primitive) {
    	return NULL;
    }
    primitive->primitiveType = primitiveType;
    primitive->points = NULL;
    primitive->next = NULL;
    return primitive;
}

void addPrimitive(Primitive* primitive, PrimitiveList* list) {
	assert(primitive);
	assert(list);
	if (*list == NULL) {
        // Si le pointeur sur la liste est vide, on le modifie pour le faire pointer sur la primitive donnée en paramètre
		*list = primitive;
	} else {
        // Sinon, on réapplique la même fonction mais sur le point suivant
		addPrimitive(primitive, &(*list)->next);
	}
}

void drawPrimitives(PrimitiveList list) {
	while(list) {
		glBegin(list->primitiveType);
		drawPoints(list->points);
		glEnd();
		list = list->next;
	}
}

void deletePrimitive(PrimitiveList* list) {
	assert(list);
	while(*list) {
		Primitive* next = (*list)->next;
		deletePoints(&(*list)->points);
		free(*list);
		*list = next;
	}
}

void resizeViewport() {
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1., 1., -1., 1.);
	SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
}

static const unsigned char COLORS[] = {
	255, 255, 255,
	0, 0, 0,
	255, 0, 0,
	0, 255, 0,
	0, 0, 255,
	255, 255, 0,
	0, 255, 255,
	255, 0, 255
};

static const unsigned int NB_COLORS = sizeof(COLORS) / (3 * sizeof(unsigned char));

void drawColorPalette() {
	int i;
    float dx = 2.f / NB_COLORS; // dx = "delta x"
    glBegin(GL_QUADS);
    for(i = 0; i < NB_COLORS; ++i) {
    	glColor3ubv(COLORS + i * 3);
    	glVertex2f(-1 + i * dx, -1);
    	glVertex2f(-1 + (i + 1) * dx, -1);
    	glVertex2f(-1 + (i + 1) * dx, 1);
    	glVertex2f(-1 + i  * dx, 1);
    }
    glEnd();
}

void drawLandmark() {
	glBegin(GL_LINES);
	glColor3ub(255,0,0);
	glVertex2f(-10, 0);
	glVertex2f(10, 0);
	glColor3ub(0,255,0);
	glVertex2f(0, -10);
	glVertex2f(0, 10);
	glEnd();

	int i;
	glPointSize(4);
	for (i=-5; i<5;i++){
		glBegin(GL_POINTS);
		glColor3ub(255,0,0);
		glVertex2f(i,0);
		glEnd();
	}
	for (i=-5; i<5;i++){
		glBegin(GL_POINTS);
		glColor3ub(0,255,0);
		glVertex2f(0,i);
		glEnd();
	}
}

void drawSquare(){
	glBegin(GL_QUADS);
		glVertex2f(-0.5, 0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(0.5, -0.5);
		glVertex2f(-0.5, -0.5);
	glEnd();
}

void drawCircle() {
    float i, teta;
    teta = 0;
    glBegin(GL_POLYGON);
        for (i=0; i<1.0;i+=0.01){
            teta = i*2*M_PI;
            glVertex2f(0.5*cos(teta),0.5*sin(teta));
        }
    glEnd();
}

int rand_a_b(int a, int b){
    return rand()%(b-a) +a;
}

void drawRoundedSquare() {
    
    glColor3ub(255, 255, 0);
/* CARRES */

        glPushMatrix();
            glScalef(1.0, 0.5, 1);
                drawSquare();
        glPopMatrix();

        glPushMatrix();
            glScalef(0.5, 1.0, 1);
                drawSquare();
        glPopMatrix();

/* RONDS */
    glColor3ub(255, 255, 0);
    glPushMatrix();
        glTranslatef(-0.25, 0.25, 0.0);
        glScalef(0.5, 0.5, 1);
        drawCircle();
    glPopMatrix();

    glColor3ub(255, 255, 0);
    glPushMatrix();
        glTranslatef(0.25, 0.25, 0.0);
        glScalef(0.5, 0.5, 1);
        drawCircle();
    glPopMatrix();

    glColor3ub(255, 255, 0);
    glPushMatrix();
        glTranslatef(0.25, -0.25, 0.0);
        glScalef(0.5, 0.5, 0.5);
        drawCircle();
    glPopMatrix();

    glColor3ub(255, 255, 0);
    glPushMatrix();
        glTranslatef(-0.25, -0.25, 0.0);
        glScalef(0.5, 0.5, 0.5);
        drawCircle();
    glPopMatrix();

}

void drawFirstArm() {
    glColor3ub(0, 100, 0);

    glPushMatrix();
        glScalef(2, 2, 0);
        drawCircle();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(3, 0, 0);
        drawCircle();
    glPopMatrix();

    
    glBegin(GL_LINE_LOOP);
        glColor3ub(0, 100, 0);
        glVertex2f(0, 1);
        glVertex2f(3, 0.5);
        glVertex2f(3, -0.5);
        glVertex2f(0, -1);
    glEnd();
}

void drawSecondArm() {
    glColor3ub(255, 255, 0);

    glPushMatrix();
        glScalef(0.3, 0.3, 1);
        drawRoundedSquare();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(1, 0.0, 0.0);
        glPushMatrix();
            glScalef(2, 0.2, 1);
            drawSquare();
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(2, 0, 1);
        glScalef(0.3, 0.3, 1);
        drawRoundedSquare();
    glPopMatrix();
}

void drawThirdArm() {
    glColor3ub(100, 0, 0);
    glPushMatrix();
        glTranslatef(2, 0.0, 0.0);
            glPushMatrix();
            glScalef(0.3, 0.3, 1);
            drawSquare();
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(3, 0.0, 0.0);
            glPushMatrix();
                glScalef(2, 0.2, 1);
                drawSquare();
            glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(4, 0.0, 0.0);
            glPushMatrix();
                glScalef(0.5, 0.5, 1);
                drawCircle();
            glPopMatrix();
    glPopMatrix();
}

int main(int argc, char** argv) {
    int alpha, beta, gamma;
        alpha = 45;
        beta = -10;
        gamma = 35;
    //float x, y;
    float mode_rotation;
    //float rotation;
    //float randx, randy;
    //rotation = x = y = 0;
    mode_rotation =0;
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
	SDL_WM_SetCaption("Noowl powa", NULL);

	glClearColor(0.1, 0.1, 0.1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

    /* On créé une première primitive par défaut */
	PrimitiveList primitives = NULL;
	Primitive* prim = allocPrimitive(GL_POINTS);
	//PrimitiveList lastPrim = prim;
	addPrimitive(prim, &primitives);

	int loop = 1;
    int mode = 0; // le mode d'affichage. 0 = le dessin, 1 = la palette
    //unsigned int currentColor = 0; // l'index de la couleur courante dans le tableau COLORS
    GLenum currentPrimitiveType = GL_POINTS;

    /* Boucle d'affichage */
    while(loop) {

        /* Récupération du temps au début de la boucle */
    	Uint32 startTime = SDL_GetTicks();

        /* Code de dessin */

        glClear(GL_COLOR_BUFFER_BIT); // Toujours commencer par clear le buffer

        if (mode == 0) {
            drawPrimitives(primitives); // On dessine la liste de primitives
        }
        else if (mode == 1) {
        	drawColorPalette();
        }
        scene();

        // glTranslatef(x,y,0);
        // glRotatef(rotation, 0.0, 0.0, 1.0);
        // drawSquare();
        // glRotatef(-rotation, 0.0, 0.0, 1.0);
        // glTranslatef(-x,-y,0);

        // randx = rand_a_b(-4, 4);
        // randy = rand_a_b(-3, 3);
        // glTranslatef(randx,randy,0);
        // glColor3ub(0,0,255);
        // drawCircle();
        // glTranslatef(-randx,-randy,0);

        drawLandmark();

        glPushMatrix();
            glRotatef(alpha, 0, 0, 1);
            drawFirstArm();
                    
                    glTranslatef(3, 0, 0);
                    glRotatef(beta, 0, 0, 1);
                    drawSecondArm();
                        /*glPushMatrix();
                            glRotatef(gamma, 0, 0, 1);
                            drawThirdArm();
                        glPopMatrix();*/

        glPopMatrix();

        alpha += 1;
        beta += -1;
        gamma += 1;

        /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e)) {

            /* L'utilisateur ferme la fenêtre : */
        	if(e.type == SDL_QUIT) {
        		loop = 0;
        		break;
        	}

            /* Quelques exemples de traitement d'evenements : */
        	switch(e.type) {

                /* Clic souris */
        		case SDL_MOUSEBUTTONUP:
              //       if (mode == 1) {
              //           /* On retrouve automatiquement l'index de la couleur cliquée en connaissant la taille de notre tableau */
              //           currentColor = e.button.x * NB_COLORS / WINDOW_WIDTH;
              //       }
              //       else if (mode == 0) {
              //               /* Transformation des coordonnées du clic souris en coordonnées OpenGL */
            		// 	x = -4 + 8. * e.button.x / WINDOW_WIDTH;
            		// 	y = -(-3 + 6. * e.button.y / WINDOW_HEIGHT);
              //               /* On retrouve la couleur courante grace à son index */
            		// 	unsigned int r = COLORS[currentColor * 3];
            		// 	unsigned int g = COLORS[currentColor * 3 + 1];
            		// 	unsigned int b = COLORS[currentColor * 3 + 2];
              //               /* On ajoute un nouveau point à la liste de la primitive courante */
            		// 	addPointToList(allocPoint(x, y, r, g, b), &lastPrim->points);
            		// }
                    break;

                case SDL_MOUSEMOTION:
                    if (mode_rotation == 1){
                        //rotation = 360*e.button.x/WINDOW_WIDTH;
                    }
                    break;

                /* Touche clavier */
        		case SDL_KEYDOWN:
            		printf("touche pressée (code = %d)\n", e.key.keysym.sym);
            		if (e.key.keysym.sym == SDLK_SPACE) {
            			mode = 1;
            		}

            		int newPrimitivePressed = 0;
            		GLenum newPrimitiveType;
                    break;

        		switch(e.key.keysym.sym) {

        			case SDLK_q:
            			loop = 0;
                        break;

        			case SDLK_SPACE:
            			mode = 1;
            			break;

        			case SDLK_p:
            			newPrimitivePressed = 1;
            			newPrimitiveType = GL_POINTS;
            			break;

        			case SDLK_l:
                        newPrimitivePressed = 1;
                        newPrimitiveType = GL_LINES;
                        break;

        			case SDLK_t:
                        newPrimitivePressed = 1;
                        newPrimitiveType = GL_TRIANGLES;
                        break;

        			case SDLK_c:
                        /* Touche pour effacer le dessin */
                        deletePrimitive(&primitives); // on supprime les primitives actuelles
                        addPrimitive(allocPrimitive(currentPrimitiveType), &primitives); // on réinitialise à la primitive courante
                        break;

                    default:
                        break;
                }

                switch (e.button.button){
                    case SDL_BUTTON_RIGHT:
                        mode_rotation = 1;
                        break;
                }

                if (newPrimitivePressed && currentPrimitiveType != newPrimitiveType) {
                	prim = allocPrimitive(newPrimitiveType);
                	//lastPrim = prim;
                	addPrimitive(prim, &primitives);
                	currentPrimitiveType = newPrimitiveType;
                }

                case SDL_KEYUP:
                    if (e.key.keysym.sym == SDLK_SPACE) {
                    	mode = 0;
                    }
                    break;

                case SDL_VIDEORESIZE:
                    WINDOW_WIDTH = e.resize.w;
                    WINDOW_HEIGHT = e.resize.h;
                    resizeViewport();
                    break;

                default:
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

            deletePrimitive(&primitives);

    /* Liberation des ressources associées à la SDL */ 
            SDL_Quit();

            return EXIT_SUCCESS;
        }
