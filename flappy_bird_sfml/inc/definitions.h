#ifndef MY_DEFINITIONS_H
#define MY_DEFINITIONS_H

#define MW_WIDTH 768
#define MW_HEIGHT 1000

#define SPLASH_STATE_SHOW_TIME 0.5f

#define SPLASH_BG_FILE_PATH "../res/res/splash_bg.png"
#define MAIN_MENU_BG_FILE_PATH "../res/res/sky.png"
#define GAME_BG_FILE_PATH "../res/res/sky.png"
#define GAME_OVER_BG_FILE_PATH "../res/res/sky.png"

#define GAME_TITLE_FILE_PATH "../res/res/title.png"
#define PLAY_BUTTON_FILE_PATH "../res/res/play_button.png"

#define PIPE_UP_FILE_PATH "../res/res/pipe_up.png"
#define PIPE_DOWN_FILE_PATH "../res/res/pipe_down.png"
#define LAND_FILE_PATH "../res/res/land.png"

#define BIRD_FRAME_1_FILE_PATH "../res/res/bird_01.png"
#define BIRD_FRAME_2_FILE_PATH "../res/res/bird_02.png"
#define BIRD_FRAME_3_FILE_PATH "../res/res/bird_03.png"
#define BIRD_FRAME_4_FILE_PATH "../res/res/bird_04.png"

#define PIPE_MOVEMENT_SPEED 200.f
#define PIPE_SPAWN_FREQ 2.0f

#define BIRD_ANIMATION_DURATION 0.4f

enum BIRD_STATE {
	STILL = 1,
	FALLING = 2,
	FLYING = 3
};

#define GRAVITY 350.f
#define FLYING_SPEED 350.f
#define FLYING_DURATION 0.25f

typedef unsigned int uint32;

#endif
