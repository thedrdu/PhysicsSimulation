#include <main.h>

/*
Draws each circle in the circles array.
*/
void draw_simulation(SDL_Renderer *renderer){
    for(int i = 0; i < num_circles; i++){
        Circle *circle = &circles[i];
        aaellipseRGBA(renderer, (int)circle->x, (int)circle->y, (int)circle->r, (int)circle->r, 255, 255, 255, 255);
        
        //trail
        // for(int j = 1; j < circle->trail_size; j++){
        //     SDL_Point pos1 = circle->trail[j-1];
        //     SDL_Point pos2 = circle->trail[j];
        //     double alpha = (double)(j)/(double)circle->trail_size;
        //     SDL_SetRenderDrawColor(renderer, 255, 255, 255, alpha*255); // White with fading opacity
        //     SDL_RenderDrawLine(renderer, pos1.x, pos1.y, pos2.x, pos2.y);
        // }
        // int j = (circle->cb.current_index + 1) % circle->cb.size;
        // for(int i = 0; i < circle->cb.size; i++){
        //     SDL_Point pos1 = circle->cb.buffer[j];
        //     j = (j + 1) % circle->cb.size;
        //     SDL_Point pos2 = circle->cb.buffer[j];
        //     double alpha = (double)(i)/(double)circle->cb.size;
        //     SDL_SetRenderDrawColor(renderer, 255, 255, 255, alpha*255); // White with fading opacity
        //     SDL_RenderDrawLine(renderer, pos1.x, pos1.y, pos2.x, pos2.y);
        // }
        for(int j = 1; j < circle->trail_size; j++){
            int idx1 = (circle->cb.current_index + j - 1) % MAX_TRAIL_LENGTH;
            int idx2 = (circle->cb.current_index + j) % MAX_TRAIL_LENGTH;
            SDL_Point pos1 = circle->trail[idx1];
            SDL_Point pos2 = circle->trail[idx2];
            double alpha = (double)(j)/(double)circle->trail_size;
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, alpha*255); // White with fading opacity
            SDL_RenderDrawLine(renderer, pos1.x, pos1.y, pos2.x, pos2.y);
        }


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