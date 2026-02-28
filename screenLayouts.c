#include <string.h>
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
    DrawTextureEx(pCurrent_fish->texture, pCurrent_fish->pos, 1, pCurrent_fish->texture_scale, pCurrent_fish->color);

    DrawText(TextFormat("Fish score: %d", pCurrent_fish->scoreVal), 50, 50, 20, DARKGRAY);
    DrawRectangleLinesEx(*pFish_slider, 2, BLACK);
    DrawRectangleRec(pSuccess_slider->completionRec, pSuccess_slider->color);
    DrawRectangleLinesEx(pSuccess_slider->rec, 2, BLACK);

    DrawText(TextFormat("Score: %d", pPlayer->score), 750, 50, 20, DARKGRAY);
}

void displayPauseScreen() {
    DrawText("PAUSED", WINDOW_WIDTH / 2 - 90, WINDOW_HEIGHT / 2 - 40, 40, DARKGRAY);
    DrawText("Press Space to continue", WINDOW_WIDTH / 2 - 230, WINDOW_HEIGHT / 2, 40, DARKGRAY);
}

void displayReelResults(fish_t *pCurrent_fish) {
    char result[20];
    if(pCurrent_fish->result == CAUGHT) {
        strcpy(result, "Caught c:");
    } else {
       strcpy(result, "Escaped :c");
    }
    DrawText(TextFormat("RESULTS %s", result), WINDOW_WIDTH / 2 - 90, WINDOW_HEIGHT / 2 - 40, 40, DARKGRAY);
    DrawText("Press ENTER to continue", WINDOW_WIDTH / 2 - 230, WINDOW_HEIGHT / 2, 40, DARKGRAY);
}
