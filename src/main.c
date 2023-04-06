/*
todo
----
segment off the various functions to the other c files for brevity and clarity
add mouse control(figure out how this would work)
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"
#include <main.h>

Circle circles[MAX_CIRCLES];
int num_circles = 0;

/* 
Creates a new circle, and returns it.
If the circle array is full, the earliest one gets deleted to make room.
*/
Circle* create_circle(double x, double y, double r, double vx, double vy){
    Circle* circle = (Circle*) malloc(sizeof(Circle));
    if(num_circles < MAX_CIRCLES){
        int index = num_circles;
        num_circles++;
        circle->x = x;
        circle->y = y;
        circle->r = r;
        circle->mass = (double)(M_PI * r * r);
        circle->vx = vx;
        circle->vy = vy;
        circle->ax = 0.0;
        circle->ay = 0.0;
        circles[index] = *circle;
    }
    else{ // shift all circles by one index, remove the earliest, not currently important
        for (int i = 0; i < MAX_CIRCLES - 1; i++){
            circles[i] = circles[i + 1];
        }
        circle->x = x;
        circle->y = y;
        circle->r = r;
        circle->mass = (double)(M_PI * r * r);
        circle->vx = vx;
        circle->vy = vy;
        circle->ax = 0.0;
        circle->ay = 0.0;
        circles[MAX_CIRCLES - 1] = *circle;
    }
    return circle;
}

void update_simulation(){
    for(int i = 0; i < num_circles; i++){
        Circle *circle = &circles[i];

        for(int j = 0; j < num_circles; j++){
            if(i == j){ //Circle can't affect itself
                continue;
            }
            Circle *other = &circles[j];
            double dx = other->x - circle->x;
            double dy = other->y - circle->y;
            double distance = sqrt(dx * dx + dy * dy);
            double min_distance = circle->r + other->r;
            if(distance < min_distance){ //Circles are too close
                continue;
            }
            double force_magnitude = G * circle->mass * other->mass / (distance * distance);
            double fx = force_magnitude * dx / distance;
            double fy = force_magnitude * dy / distance;
            circle->ax += fx / circle->mass;
            circle->ay += fy / circle->mass;
            printf("[%e, %e]\n", circle->ax, circle->ay);
        }
        // update velocity and position using Euler's method
        circle->vx += circle->ax * dt;
        circle->vy += circle->ay * dt;
        circle->x += circle->vx * dt;
        circle->y += circle->vy * dt;
    }
}

void draw_simulation(SDL_Renderer *renderer){
    for(int i = 0; i < num_circles; i++){
        Circle *circle = &circles[i];
        aaellipseRGBA(renderer, (int)circle->x, (int)circle->y, (int)circle->r, (int)circle->r, 255, 255, 255, 255);
    }
    SDL_RenderPresent(renderer);
}

int main(){
    srand(time(NULL));
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Circle Movement", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //Testing, add manual placement later
    create_circle(300, 300, 10, 5, -5);
    create_circle(400, 400, 10, -5, 5);

    int running = 1;
    int paused = 0;
    while(running){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE){
                        running = 0;
                    }
                    else if(event.key.keysym.sym == SDLK_p){
                        if(paused == 0){
                            paused = 1;
                        }
                        else if(paused == 1){
                            paused = 0;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        if(!paused){
            for(int i = 0; i < 10; i++){
                update_simulation();
            }
        }
        draw_simulation(renderer);
        SDL_Delay(10); //milliseconds
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}