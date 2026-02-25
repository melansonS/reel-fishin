#include "raylib.h"

#define HEIGHT 600
#define WIDTH 900

typedef struct {
    int x, y, width, height, speed;
    Color color;
}reel_t;

typedef enum {
    UP = -1,
    DOWN = 1
} dir_t;

void moveReel(short direction, reel_t* reel);

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Reel Fishin'");

    SetTargetFPS(60);

    reel_t reel = {100, 100, 20, 8, 5, WHITE};
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
            DrawRectangle(reel.x, reel.y, reel.width, reel.height, reel.color);
            
        EndDrawing();
    }

    CloseWindow();
}

void moveReel(short direction, reel_t* reel) {
    if(reel->y + reel->speed * direction > 0 && reel->y + reel->speed * direction < (HEIGHT - reel->height)) {
        reel->y += reel->speed * direction;
    }
}
