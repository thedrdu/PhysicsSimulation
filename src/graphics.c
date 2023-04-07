#include <main.h>

/*
Draws each circle in the circles array.
*/
void draw_simulation(SDL_Renderer *renderer){
    for(int i = 0; i < num_circles; i++){
        Circle *circle = &circles[i];
        aaellipseRGBA(renderer, (int)circle->x, (int)circle->y, (int)circle->r, (int)circle->r, 255, 255, 255, 255);
    }
}

/*
Draws the predictive line and the static circle when holding down the mouse button.
*/
void draw_prediction(SDL_Renderer *renderer, double x1, double y1, double x2, double y2, double r){
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

    aaellipseRGBA(renderer, x1, y1, r, r, 255, 255, 255, 255);
}