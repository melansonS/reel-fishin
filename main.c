#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "raylib.h"
#include "main.h"
#include "screenLayouts.h"

void moveReel(short direction, reel_t* pReel);
void moveFish(fish_t* pFish);
bool checkRecCollision(Rectangle *pRec1, Rectangle *pRec2);
void blendColors(Color col1, Color col2, float percent, Color *pBlended);
void initFish(fish_t *pFish);
void initSlider(success_slider_t *pSlider);
void initReel(reel_t *pReel);


Color fish_colors[NUM_FISH_COLORS] = {RED, ORANGE, YELLOW, BLUE, GREEN, PURPLE};
int fish_slider_heights[] = {30, 60, 90};
Texture2D fish_texture;
Texture2D boat_texture;

int main(void) {
    srand((unsigned)time(NULL));
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Reel Fishin'");

    Image image = LoadImage("resources/pixel_fish2_small.png");     // Loaded in CPU memory (RAM)
    fish_texture = LoadTextureFromImage(image);     // Image converted to texture, GPU memory (VRAM)
    image = LoadImage("resources/lil_boat.png");
    boat_texture = LoadTextureFromImage(image);     // Image converted to texture, GPU memory (VRAM)
    UnloadImage(image);

    SetTargetFPS(60);

    Rectangle fish_slider = {FISH_SLIDER_X, FISH_SLIDER_Y, FISH_SLIDER_WIDTH, FISH_SLIDER_HEIGHT};
    success_slider_t success_slider;
    initSlider(&success_slider);
    reel_t reel;
    initReel(&reel);
    fish_t current_fish;
    initFish(&current_fish);

    player_t player = {0};

    Vector2 boat_position = {60, 60};
    dir_t direction = UP;
    bool isReelOnFish = false;

    Color blendedslidderColor;
    float adjustedBlendPercent = 0.0;
    gameState_t state = LANDING_PAGE;

    while(!WindowShouldClose())
    {
        switch(state) {
            case(LANDING_PAGE):
                if(IsKeyDown(KEY_SPACE)) {
                    state = CATCHING_FISH;
                }
                break;
            case(CATCHING_FISH):
                if(IsKeyDown(KEY_SPACE)) {
                    direction = UP;
                } else {
                    direction = DOWN;
                }
                isReelOnFish = checkRecCollision(&reel.rec, &current_fish.rec);
                if(isReelOnFish && success_slider.completionVal < 1){
                    success_slider.completionVal += 0.003;
                    if(current_fish.rotation > -22) {
                        current_fish.rotation -= 0.3;
                    }
                    if(current_fish.texture_dest_rec.y > (WINDOW_HEIGHT/2) - 22) {
                        current_fish.texture_dest_rec.y -= 0.3;
                    }
                } else if(success_slider.completionVal > 0) {
                    success_slider.completionVal -= 0.002;
                    if(current_fish.scoreVal > current_fish.minScore) current_fish.scoreVal--;
                    if(current_fish.rotation < 22 ) {
                        current_fish.rotation += 0.3;
                    }
                    if(current_fish.texture_dest_rec.y < (WINDOW_HEIGHT/2) + 22) {
                        current_fish.texture_dest_rec.y += 0.3;
                    }
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
                moveReel(direction, &reel);
                moveFish(&current_fish);
                 
                if(IsKeyDown(KEY_P)) {
                    state = PAUSE;
                }

                if(success_slider.completionVal >= 1) {
                    current_fish.result = CAUGHT;
                    player.score += current_fish.scoreVal;
                    state = REEL_RESULTS;
                } else if (success_slider.completionVal <= 0) {
                    current_fish.result = ESCAPED;
                    state = REEL_RESULTS;
                }
                break;
            case(PAUSE):
                if(IsKeyDown(KEY_SPACE)) {
                    state = CATCHING_FISH;
                }
                break;
            case(REEL_RESULTS):
                if(IsKeyDown(KEY_ENTER)) {
                    state = CATCHING_FISH;
                    initFish(&current_fish);
                    initSlider(&success_slider);
                    initReel(&reel);
                }
                break;
            default:
                state = ERROR;
                break;
        }

        BeginDrawing();
            ClearBackground(SKYBLUE);
            switch(state) {
                case LANDING_PAGE:
                    displayLandingPage(&boat_texture, &boat_position);
                    break;
                case CATCHING_FISH:
                    displayCatchingScreen(&current_fish, &fish_slider, &reel, &success_slider, &player);
                    break;
                case PAUSE:
                    displayPauseScreen();
                    break;
                case REEL_RESULTS:
                    displayReelResults(&current_fish);
                default:
                    break;
            }
        EndDrawing();
    }

    CloseWindow();
}

void moveReel(short direction, reel_t* pReel) {
    if(pReel->rec.y + pReel->speed * direction >= REEL_UPPERBOUND && pReel->rec.y + pReel->speed * direction <= (REEL_LOWERBOUND - pReel->rec.height)) {
        pReel->rec.y += pReel->speed * direction;
    }
}

void moveFish(fish_t *pFish) {

    if(pFish->rec.y + pFish->speed * pFish->direction >= REEL_UPPERBOUND && pFish->rec.y + pFish->speed * pFish->direction <= (REEL_LOWERBOUND - pFish->rec.height)) {
        pFish->rec.y += pFish->speed * pFish->direction;
    }
    pFish->random_number = rand() % 100;
    if(pFish->random_number < pFish->change_dir_chance) {
        pFish->direction *= -1;
    }
}

bool checkRecCollision(Rectangle *pRec1, Rectangle *pRec2) {
    if(pRec1->y >= pRec2->y && pRec1->y <= pRec2->y + pRec2->height) {
        return true;
    } else if(pRec1->y + pRec1->height  >= pRec2->y && pRec1->y + pRec1->height <= pRec2->y + pRec2->height) {
        return true;
    } else {
        return false;
    }
}

void blendColors(Color col1, Color col2, float percent, Color *pBlended) {
    if(percent > 1) percent = 1;
    int maxR = col2.r - col1.r;
    int maxG = col2.g - col1.g;
    int maxB = col2.b - col1.b;
    pBlended->r = col1.r + maxR * percent;
    pBlended->g = col1.g + maxG * percent;
    pBlended->b = col1.b + maxB * percent;
    pBlended->a = col1.a;
}

void initFish(fish_t *pFish) {
    int minSpeed = 1;
    int maxSpeed = 3;
    int speed = (rand() % (maxSpeed - minSpeed + 1)) + minSpeed;

    fish_size_t size = (rand() % 3) + 1;

    int colorIndex = rand() % NUM_FISH_COLORS;
    Color fishColor = fish_colors[colorIndex];
    
    Rectangle fish_src_rec = {0, 0, FISH_TEXTURE_WIDTH, FISH_TEXTURE_HEIGHT};
    Rectangle fish_dest_rec = {WINDOW_WIDTH/2, WINDOW_HEIGHT/2, (FISH_TEXTURE_WIDTH/FISH_TEXTURE_SCALE) * size, (FISH_TEXTURE_HEIGHT/FISH_TEXTURE_SCALE) * size};
    Vector2 fish_origin = {(FISH_TEXTURE_WIDTH/(FISH_TEXTURE_SCALE * 2)) * size, (FISH_TEXTURE_HEIGHT/(FISH_TEXTURE_SCALE * 2)) * size};
    Vector2 fishPos = {300, 250};

    fishPos.y -= size * 70;
    float textureScale = 0.3 + (float) size / 5; // no longer needed when using DrawTexturePro
    float rotation = 1.0;
    int scoreVal = 1000;
    int minScore = 50;
    int changeDirectionChance = 8;

    fish_t fish =  {{FISH_SLIDER_X, 250, FISH_SLIDER_WIDTH, fish_slider_heights[size - 1]}, speed, fishColor, DOWN, scoreVal, minScore, 1, changeDirectionChance, fishPos, fish_texture, ESCAPED, size, rotation, textureScale, fish_src_rec, fish_dest_rec, fish_origin};
    *pFish = fish;
}

void initSlider(success_slider_t *pSlider) {
    success_slider_t slider = {{SUCCESS_SLIDER_X, SUCCESS_SLIDER_Y, SUCCESS_SLIDER_WIDTH, SUCCESS_SLIDER_HEIGHT}, 0.5, {SUCCESS_SLIDER_X, SUCCESS_SLIDER_Y, SUCCESS_SLIDER_WIDTH/2, SUCCESS_SLIDER_HEIGHT}, YELLOW};
    *pSlider = slider;
}

void initReel(reel_t *pReel) {
    reel_t reel = {{FISH_SLIDER_X, 250, FISH_SLIDER_WIDTH, 10}, 1, WHITE}; 
    *pReel = reel;
}
