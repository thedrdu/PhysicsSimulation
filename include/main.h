#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"

#define dt 0.01
#define G 0.66743
#define MAX_CIRCLES 10
#define SIZE_INCREASE_RATE 0.2
#define CREATION_VELOCITY_MODIFIER 10 //higher = slower, this is used as a divisor
#define MAX_TRAIL_LENGTH 500

typedef struct {
    SDL_Point buffer[MAX_TRAIL_LENGTH];
    int size;
    int current_index;
} CircularBuffer;

typedef struct Circle {
    double x;          // x position
    double y;          // y position
    double r;          // radius
    double mass;       // mass
    double vx;         // x velocity
    double vy;         // y velocity
    double ax;         // x acceleration
    double ay;         // y acceleration
    SDL_Point trail[MAX_TRAIL_LENGTH];
    CircularBuffer cb;
    int trail_size;
} Circle;

extern int APPLICATION_WIDTH;
extern int APPLICATION_HEIGHT;

extern Circle circles[MAX_CIRCLES];
extern int num_circles;

void destroy_circle(Circle* circle);
Circle* create_circle(double x, double y, double r, double vx, double vy);
void update_simulation();
void draw_simulation(SDL_Renderer *renderer);
void draw_prediction(SDL_Renderer *renderer, double x1, double y1, double x2, double y2, double r);