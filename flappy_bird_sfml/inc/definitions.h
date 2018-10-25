#ifndef MY_DEFINITIONS_H
#define MY_DEFINITIONS_H

typedef unsigned char uint8;
typedef unsigned int  uint32;

inline constexpr int MW_WIDTH  = 768;
inline constexpr int MW_HEIGHT = 1000;

inline constexpr float SPLASH_STATE_SHOW_TIME = 0.5f;

#define _base_path "../res"

/* Backgrounds */
#define SPLASH_BG_FILE_PATH _base_path "/res/splash_bg.png"
#define SPLASH_BG_FILE_PATH _base_path "/res/splash_bg.png"
#define MAIN_MENU_BG_FILE_PATH _base_path "/res/sky.png"
#define GAME_BG_FILE_PATH _base_path "/res/sky.png"
#define GAME_OVER_BG_FILE_PATH _base_path "/res/sky.png"

#define GAME_TITLE_FILE_PATH _base_path "/res/title.png"
#define PLAY_BUTTON_FILE_PATH _base_path "/res/play_button.png"
#define GAME_OVER_TITLE_FILE_PATH _base_path "/res/game_over_title.png"
#define GAME_OVER_BODY_FILE_PATH _base_path "/res/game_over_body.png"

/* Text */
#define FLAPPY_FONT_FILE_PATH _base_path "/fonts/flappy_font.ttf"

/* Pipes and land */
#define PIPE_UP_FILE_PATH _base_path "/res/pipe_up.png"
#define PIPE_DOWN_FILE_PATH _base_path "/res/pipe_down.png"
#define LAND_FILE_PATH _base_path "/res/land.png"
#define INVISIBLE_PIPE_FILE_PATH _base_path "/res/pipe_score_test.png"

inline constexpr float PIPE_MOVEMENT_SPEED = 200.f;
inline constexpr float PIPE_SPAWN_FREQ     = 2.0f;

/* Bird */
#define BIRD_FRAME_1_FILE_PATH _base_path "/res/bird_01.png"
#define BIRD_FRAME_2_FILE_PATH _base_path "/res/bird_02.png"
#define BIRD_FRAME_3_FILE_PATH _base_path "/res/bird_03.png"
#define BIRD_FRAME_4_FILE_PATH _base_path "/res/bird_04.png"

inline constexpr float BIRD_ANIMATION_DURATION = 0.4f;

inline constexpr float BIRD_COLLISION_SCALE = 0.7f;

enum BIRD_STATE { STILL = 1, FALLING = 2, FLYING = 3 };

inline constexpr float GRAVITY         = 350.f;
inline constexpr float FLYING_SPEED    = 350.f;
inline constexpr float FLYING_DURATION = 0.25f;
inline constexpr float ROTATION_SPEED  = 100.f;

/* Game states */
enum eGAME_STATE { READY = 0, PLAYING = 1, GAMEOVER = 2 };

/* Flush */
inline constexpr float FLASH_SPEED = 1000.f;

/* Game Over */
inline constexpr float GAME_OVER_DELAY = .5f;

/* Best score */
#define BEST_SCORE_FILE_PATH "data/best_score.flappy"

#endif
