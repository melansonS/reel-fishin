#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
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
    Rectangle rec;
    int  speed;
    Color color;
}reel_t;

typedef struct {
    Rectangle rec;
    int speed;
    Color color;
    dir_t direction;
    int random_number;
    int change_dir_chance;
} fish_t;

void moveReel(short direction, reel_t* reel);
void moveFish(fish_t* fish);
bool checkRecCollision(Rectangle *rec1, Rectangle *rec2);

int main(void) {
    srand((unsigned)time(NULL));
    InitWindow(WIDTH, HEIGHT, "Reel Fishin'");

    SetTargetFPS(60);

    Rectangle slidder = {SLIDDER_X, SLIDDER_Y, SLIDDER_WIDTH, SLIDDER_HEIGHT};
    reel_t reel = {{SLIDDER_X, 100, SLIDDER_WIDTH, 20}, 1, WHITE};
    fish_t fish = {{SLIDDER_X, 100, SLIDDER_WIDTH, 50}, 1, GREEN, DOWN, 1, 8};
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
            DrawRectangleRec(fish.rec, fish.color);
            DrawRectangleRec(reel.rec, reel.color);
            if(checkRecCollision(&reel.rec, &fish.rec)){
                DrawText("Collision detected", 50, 50, 20, DARKGRAY);
            }

            DrawRectangleLinesEx(slidder, 2, BLACK);
        EndDrawing();
    }

    CloseWindow();
}

void moveReel(short direction, reel_t* reel) {
    if(reel->rec.y + reel->speed * direction >= REEL_UPPERBOUND && reel->rec.y + reel->speed * direction <= (REEL_LOWERBOUND - reel->rec.height)) {
        reel->rec.y += reel->speed * direction;
    }
}

void moveFish(fish_t* fish) {

    if(fish->rec.y + fish->speed *fish->direction >= REEL_UPPERBOUND && fish->rec.y + fish->speed *fish->direction <= (REEL_LOWERBOUND - fish->rec.height)) {
        fish->rec.y += fish->speed *fish->direction;
    }
    fish->random_number = rand() % 100;
    if(fish->random_number < fish->change_dir_chance) {
        fish->direction *= -1;
    }
}

bool checkRecCollision(Rectangle *rec1, Rectangle *rec2) {
    if(rec1->y >= rec2->y && rec1->y <= rec2->y + rec2->height) {
        return true;
    } else if(rec1->y + rec1->height  >= rec2->y && rec1->y + rec1->height <= rec2->y + rec2->height) {
        return true;
    } else {
        return false;
    }
}

