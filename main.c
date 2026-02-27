#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "raylib.h"
#include "main.h"

void moveReel(short direction, reel_t* reel);
void moveFish(fish_t* fish);
bool checkRecCollision(Rectangle *rec1, Rectangle *rec2);
void blendColors(Color col1, Color col2, float percent, Color *blended);

int main(void) {
    srand((unsigned)time(NULL));
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Reel Fishin'");

    Image image = LoadImage("resources/pixel_fish2.png");     // Loaded in CPU memory (RAM)
    Texture2D fish_texture = LoadTextureFromImage(image);     // Image converted to texture, GPU memory (VRAM)
    UnloadImage(image);

    SetTargetFPS(60);

    Rectangle fish_slider = {FISH_SLIDER_X, FISH_SLIDER_Y, FISH_SLIDER_WIDTH, FISH_SLIDER_HEIGHT};
    success_slider_t success_slider = {{SUCCESS_SLIDER_X, SUCCESS_SLIDER_Y, SUCCESS_SLIDER_WIDTH, SUCCESS_SLIDER_HEIGHT}, 0.5, {SUCCESS_SLIDER_X, SUCCESS_SLIDER_Y, SUCCESS_SLIDER_WIDTH/2, SUCCESS_SLIDER_HEIGHT}, YELLOW};
    reel_t reel = {{FISH_SLIDER_X, 100, FISH_SLIDER_WIDTH, 10}, 1, WHITE};
    fish_t fish = {{FISH_SLIDER_X, 100, FISH_SLIDER_WIDTH, 50}, 1, GREEN, DOWN, 1, 8,{300, 300}, fish_texture};
    dir_t direction = UP;
    bool reelOnFish = false;

    Color blendedslidderColor;
    float adjustedBlendPercent = 0.0;

    while(!WindowShouldClose())
    {
        blendColors(GREEN, RED, success_slider.completionVal, &blendedslidderColor);
        reelOnFish = checkRecCollision(&reel.rec, &fish.rec);
        if(IsKeyDown(KEY_SPACE)) {
            direction = UP;
        } else {
            direction = DOWN;
        }
        if(reelOnFish && success_slider.completionVal < 1){
            success_slider.completionVal += 0.003;
        } else if(success_slider.completionVal > 0) {
            success_slider.completionVal -= 0.002;
        }


        if(success_slider.completionVal < SUCCESS_SLIDER_DANGER_COLOR_TH) {
            adjustedBlendPercent = success_slider.completionVal / SUCCESS_SLIDER_DANGER_COLOR_TH;
            blendColors(RED, YELLOW, adjustedBlendPercent, &blendedslidderColor);
            success_slider.color = blendedslidderColor;
        }else if(success_slider.completionVal > SUCCESS_SLIDER_VICTORY_COLOR_TH ) {
            adjustedBlendPercent = (success_slider.completionVal - SUCCESS_SLIDER_VICTORY_COLOR_TH) / ( 1 - SUCCESS_SLIDER_VICTORY_COLOR_TH);
            blendColors(YELLOW, GREEN, adjustedBlendPercent , &blendedslidderColor);
            success_slider.color = blendedslidderColor;
        } else {
            success_slider.color = YELLOW;
        }
        success_slider.completionRec.width = SUCCESS_SLIDER_WIDTH * success_slider.completionVal;

        BeginDrawing();
            ClearBackground(SKYBLUE);
            moveReel(direction, &reel);
            moveFish(&fish);
            DrawRectangleRec(fish.rec, fish.color);
            DrawRectangleRec(reel.rec, reel.color);
            DrawTextureEx(fish.texture, fish.pos, 1, 0.3, WHITE);

            if(reelOnFish){
                DrawText("Collision detected", 50, 50, 20, DARKGRAY);
            }
            DrawRectangleLinesEx(fish_slider, 2, BLACK);
            DrawRectangleRec(success_slider.completionRec, success_slider.color);
            DrawRectangleLinesEx(success_slider.rec, 2, BLACK);

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

void blendColors(Color col1, Color col2, float percent, Color *blended) {
    if(percent > 1) percent = 1;
    int maxR = col2.r - col1.r;
    int maxG = col2.g - col1.g;
    int maxB = col2.b - col1.b;
    blended->r = col1.r + maxR * percent;
    blended->g = col1.g + maxG * percent;
    blended->b = col1.b + maxB * percent;
    blended->a = col1.a;
}
