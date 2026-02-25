#include "raylib.h"

#define HEIGHT 600
#define WIDTH 900

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Reel Fishin'");

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {

        BeginDrawing();
            DrawCircle(50,50,50,RED);
            
        EndDrawing();
    }

    CloseWindow();
}
