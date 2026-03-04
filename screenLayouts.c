#include <string.h>
#include "screenLayouts.h"
#include "raylib.h"
#include "main.h"

void displayLandingPage(Texture2D *pBoat_texture, Vector2 *pBoat_position) {
    DrawText("Reel Fishin'", WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 - 100, 60, DARKGRAY);
    DrawText("WELCOME", WINDOW_WIDTH / 2 - 90, WINDOW_HEIGHT / 2 - 40, 40, DARKGRAY);
    DrawText("Press Space to continue", WINDOW_WIDTH / 2 - 230, WINDOW_HEIGHT / 2, 40, DARKGRAY);
    DrawTextureEx(*pBoat_texture, *pBoat_position, 1, 5, WHITE);
}

void displayCatchingScreen(fish_t *pCurrent_fish, Rectangle *pFish_slider, reel_t *pReel, success_slider_t *pSuccess_slider, player_t *pPlayer) {
    DrawRectangleRec(pCurrent_fish->rec, pCurrent_fish->color);
    DrawRectangleRec(pReel->rec, pReel->color);
    DrawTexturePro(pCurrent_fish->texture, pCurrent_fish->texture_src_rec, pCurrent_fish->texture_dest_rec, pCurrent_fish->texture_origin, pCurrent_fish->rotation, pCurrent_fish->color);

    DrawText(TextFormat("Fish score: %d", pCurrent_fish->scoreVal), 50, 50, 20, DARKGRAY);
    DrawRectangleLinesEx(*pFish_slider, 2, BLACK);
    DrawRectangleRec(pSuccess_slider->completionRec, pSuccess_slider->color);
    DrawRectangleLinesEx(pSuccess_slider->rec, 2, BLACK);

    DrawText(TextFormat("Score: %d", pPlayer->score), 750, 50, 20, DARKGRAY);
}

void displayPauseScreen(fish_t *pCurrent_fish) {
    DrawText("PAUSED", WINDOW_WIDTH / 2 - 90, WINDOW_HEIGHT / 2 + 90, 40, DARKGRAY);
    DrawText("Press Space to continue", WINDOW_WIDTH / 2 - 230, WINDOW_HEIGHT / 2 + 130, 40, DARKGRAY);
    drawFishCard(WINDOW_WIDTH / 2 - 125, 100, pCurrent_fish, SKYBLUE);
}

void displayReelResults(fish_t *pCurrent_fish) {
    char result[20];
    Color fish_card_background_color = DARKBLUE;
    if(pCurrent_fish->result == CAUGHT) {
        fish_card_background_color = BLUE;
        strcpy(result, "Caught   ");
        DrawText(TextFormat("you earned %d points!", pCurrent_fish->scoreVal), WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT/2 + 70, 25, DARKGRAY);
    } else {
       fish_card_background_color = MAROON;
       strcpy(result, "Got away");
    }
    DrawText(TextFormat("%s", result), WINDOW_WIDTH / 2 - 90, 40, 40, DARKGRAY);

    drawFishCard(WINDOW_WIDTH / 2 - 125, 100, pCurrent_fish, fish_card_background_color);

    DrawText("Press ENTER to continue", WINDOW_WIDTH / 2 - 240, WINDOW_HEIGHT / 2 + 150, 40, DARKGRAY);
}

void drawFishCard(int x, int y, fish_t *pCurrent_fish, Color cardBG) {
    Rectangle cardRec = {x, y, 250, 250};
    DrawRectangleRounded(cardRec, 0.2, 10, cardBG);
    DrawRectangleRoundedLinesEx(cardRec, 0.2, 10, 2, WHITE);
    DrawTextureEx(pCurrent_fish->texture, (Vector2){WINDOW_WIDTH / 2 - 30, 130}, 1, 0.3, pCurrent_fish->color);
    DrawText("Size:", WINDOW_WIDTH / 2 - 110, 240, 30, BLACK);
    for(int i = 0; i < 4; i++) {
        if(i < pCurrent_fish->size) {
            DrawRectangle(WINDOW_WIDTH/2 - 110 + 75 + (35 * i), 240, 25, 25, GREEN);
        }
    }
    DrawText("Speed:", WINDOW_WIDTH / 2 - 110, 290, 30, BLACK);
    for(int i = 0; i < 4; i++) {
        if(i < pCurrent_fish->speed) {
            DrawRectangle(WINDOW_WIDTH/2 - 110 + 110 + (35 * i), 290, 25, 25, GREEN);
        }
    }
}
