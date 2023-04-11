/*
todo
----
circular buffer implementation
*/

#include <main.h>

int APPLICATION_WIDTH;
int APPLICATION_HEIGHT;
Circle circles[MAX_CIRCLES];
int num_circles;

int STEPS = 0;

int main(){
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);
    APPLICATION_WIDTH = dm.w;
    APPLICATION_HEIGHT = dm.h;
    window = SDL_CreateWindow("Circle Movement", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dm.w, dm.h, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int running = 1; //game state
    int paused = 0;

    int mouse_down = 0;
    int x1, y1 = 0; //initial position on mouse click
    int x2, y2 = 0; //position on mouse release

    //Used for circle creation upon mouse release
    double vx = 0;
    double vy = 0;
    double create_radius = 0;

    while(running){
        SDL_Event event;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //black
        SDL_RenderClear(renderer); //clear renderer for next iteration of game loop

        if(mouse_down){ //predictive
            SDL_GetMouseState(&x2, &y2);
            draw_prediction(renderer, x1, y1, x2, y2, create_radius);
            create_radius += SIZE_INCREASE_RATE;
        }

        while(SDL_PollEvent(&event)){ //check for inputs
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
                case SDL_MOUSEBUTTONDOWN:
                    if(!mouse_down){
                        create_radius = 0;
                        mouse_down = 1;
                        x1 = event.button.x;
                        y1 = event.button.y;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if(mouse_down){
                        mouse_down = 0;
                        vx = (double)((event.button.x-x1)/CREATION_VELOCITY_MODIFIER);
                        vy = (double)((event.button.y-y1)/CREATION_VELOCITY_MODIFIER);
                        create_circle(x1, y1, create_radius, vx, vy);
                    }
                    break;
                default:
                    break;
            }
        }
        
        if(!paused){
            for(int i = 0; i < 5; i++){
                STEPS++;
                update_simulation();
            }
        }
        
        draw_simulation(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(5); //milliseconds
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
