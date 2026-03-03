#ifndef SCREEN_LAYOUTS_H
#define SCREEN_LAYOUTS_H

void displayLandingPage(Texture2D *pPoat_texture, Vector2 *pBoat_position);
void displayCatchingScreen(fish_t *pCurrent_fish, Rectangle *pFish_slider, reel_t *pReel, success_slider_t *pSuccess_slider, player_t *pPlayer);
void displayPauseScreen(fish_t *pCurrent_fish);
void displayReelResults(fish_t *pCurrent_fish);

#endif

