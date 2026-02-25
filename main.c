#include <stdlib.h>
#include <time.h>
#include "raylib.h"

#define HEIGHT 600
#define WIDTH 900
#define SLIDDER_HEIGHT 400
#define SLIDDER_WIDTH 20
#define SLIDDER_X 100
#define SLIDDER_Y 100
#define REEL_UPPERBOUND SLIDDER_Y
#define REEL_LOWERBOUND SLIDDER_Y + SLIDDER_HEIGHT
typedef enum {
    UP = -1,
    DOWN = 1
} dir_t;

typedef struct {
    int x, y, width, height, speed;
    Color color;
}reel_t;

typedef struct {
    int x, y, width, height, speed;
    Color color;
    dir_t direction;
    int random_number;
    int change_dir_chance;
} fish_t;

void moveReel(short direction, reel_t* reel);
void moveFish(fish_t* fish);

int main(void) {
    srand((unsigned)time(NULL));
    InitWindow(WIDTH, HEIGHT, "Reel Fishin'");

    SetTargetFPS(60);
    
    Rectangle slidder = {SLIDDER_X, SLIDDER_Y, SLIDDER_WIDTH, SLIDDER_HEIGHT};
    reel_t reel = {SLIDDER_X, 100, SLIDDER_WIDTH, 8, 5, WHITE};
    fish_t fish = {SLIDDER_X, 100, SLIDDER_WIDTH, 50, 3, GREEN, DOWN, 1, 8};
    dir_t direction = UP;

    while(!WindowShouldClose())
    {
        if(IsKeyDown(KEY_SPACE)) {
            direction = UP;
        } else {
            direction = DOWN;
        }
        BeginDrawing();
            ClearBackground(SKYBLUE);
            moveReel(direction, &reel);
            moveFish(&fish);
            DrawRectangle(fish.x, fish.y, fish.width, fish.height, fish.color);
            DrawRectangle(reel.x, reel.y, reel.width, reel.height, reel.color);
            
            DrawRectangleLinesEx(slidder, 2, BLACK);
        EndDrawing();
    }

    CloseWindow();
}

void moveReel(short direction, reel_t* reel) {
    if(reel->y + reel->speed * direction >= REEL_UPPERBOUND && reel->y + reel->speed * direction <= (REEL_LOWERBOUND - reel->height)) {
        reel->y += reel->speed * direction;
    }
}

void moveFish(fish_t* fish) {
    
    if(fish->y + fish->speed *fish->direction >= REEL_UPPERBOUND && fish->y + fish->speed *fish->direction <= (REEL_LOWERBOUND - fish->height)) {
        fish->y += fish->speed *fish->direction;
    }
    fish->random_number = rand() % 100;
    if(fish->random_number < fish->change_dir_chance) {
        fish->direction *= -1;
    }
}
