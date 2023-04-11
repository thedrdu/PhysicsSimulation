#include <main.h>

/*
Destroys the given circle by removing it from the circles array.
*/
void destroy_circle(Circle* circle){
    printf("destroyed: %p\n", (void*)circle);
    if(circle == NULL){
        return;
    }
    for(int i = 0; i < num_circles; i++){
        if(&circles[i] == circle){
            // Shift all subsequent circles over by one index.
            for(int j = i + 1; j < num_circles; j++){
                circles[j - 1] = circles[j];
            }
            num_circles--;
            break;
        }
    }
    circle = NULL;
}


/* 
Creates a new circle, and returns it.
Deletes the oldest circle if the maximum number of circles allowed is reached.
*/
Circle* create_circle(double x, double y, double r, double vx, double vy){
    Circle* circle = (Circle*) malloc(sizeof(Circle));
    SDL_Point current_point = {x, y};
    if(circle == NULL){
        return NULL;
    }
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
        circle->trail_size = 0; 
        circles[index] = *circle;
        circle->cb.size = MAX_TRAIL_LENGTH;
        circle->cb.current_index = 0;
        for(int i = 0; i < MAX_TRAIL_LENGTH; i++){
            circle->cb.buffer[i] = current_point;
        }
    }
    else{
        // Find the oldest circle and destroy it.
        Circle* oldest_circle = &circles[0];
        destroy_circle(oldest_circle);
        // Create the new circle.
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
        circle->trail_size = 0;
        circles[index] = *circle;
    }
    // printf("created: %p\n", (void*)circle);
    return circle;
}

/*
Updates the simulation by updating the attributes of all circles.
*/
void update_simulation(){
    for(int i = 0; i < num_circles; i++){
        Circle *circle = &circles[i];

        if(circle->x > (APPLICATION_WIDTH + circle->r) || circle->x < (0 - circle->r) || circle->y > (APPLICATION_HEIGHT + circle->r) || circle->y < (0 - circle->r)){
            destroy_circle(circle);
            continue;
        }

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
        }
        //update velocity and position using Euler's method
        circle->vx += circle->ax * dt;
        circle->vy += circle->ay * dt;
        circle->x += circle->vx * dt;
        circle->y += circle->vy * dt;

        //update trail
        SDL_Point current_point = {circle->x, circle->y};

        circle->cb.buffer[circle->cb.current_index] = current_point;
        circle->cb.current_index = (circle->cb.current_index + 1) % circle->cb.size;

        // if(circle->trail_size >= MAX_TRAIL_LENGTH){
        //     //remove oldest point by shifting all points to the left by one index
        //     for(int i = 1; i < MAX_TRAIL_LENGTH; i++){
        //         circle->trail[i-1] = circle->trail[i];
        //     }
        //     circle->trail[MAX_TRAIL_LENGTH-1] = current_point;
        // }
        // else{
        //     circle->trail[circle->trail_size] = current_point;
        //     circle->trail_size++;
        // }

        // printf("%d\n", circle->trail_size);
    }
}