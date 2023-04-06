#define dt 0.01
#define G 0.66743
#define APPLICATION_WIDTH 800.0
#define APPLICATION_HEIGHT 800.0
#define MAX_CIRCLES 100

typedef struct Circle {
    double x;          // x position
    double y;          // y position
    double r;          // radius
    double mass;       // mass
    double vx;         // x velocity
    double vy;         // y velocity
    double ax;         // x acceleration
    double ay;         // y acceleration
} Circle;