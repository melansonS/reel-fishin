#ifndef MAIN_H
#define MAIN_H

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 900
#define FISH_SLIDER_HEIGHT 400
#define FISH_SLIDER_WIDTH 20
#define FISH_SLIDER_X 100
#define FISH_SLIDER_Y 100
#define REEL_UPPERBOUND FISH_SLIDER_Y
#define REEL_LOWERBOUND FISH_SLIDER_Y + FISH_SLIDER_HEIGHT
#define SUCCESS_SLIDER_X 150
#define SUCCESS_SLIDER_Y 500
#define SUCCESS_SLIDER_HEIGHT 40
#define SUCCESS_SLIDER_WIDTH 600
#define SUCCESS_SLIDER_VICTORY_COLOR_TH 0.77
#define SUCCESS_SLIDER_DANGER_COLOR_TH 0.33

typedef enum {
    LANDING_PAGE,
    CATCHING_FISH,
    REEL_RESULTS,
    PAUSE,
    ERROR
} gameState_t;

typedef enum {
    UP = -1,
    DOWN = 1
} dir_t;

typedef enum {
    ESCAPED,
    CAUGHT
} fish_result_t;

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
    int scoreVal;
    int random_number;
    int change_dir_chance;
    Vector2 pos;
    Texture2D texture;
    fish_result_t result;
} fish_t;

typedef struct {
    Rectangle rec;
    float completionVal;
    Rectangle completionRec;
    Color color;
} success_slider_t;

typedef struct {
    int score;
} player_t;

#endif
