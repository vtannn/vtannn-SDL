#ifndef DEFS_H
#define DEFS_H
#define INITIAL_SPEED 10
const int SCREEN_WIDTH=700;
const int SCREEN_HEIGHT=800;
const char* WINDOW_TITLE="Vtan";
bool quit=false;
bool flying=false;
bool game_over=false;
#define BOARD_X 0
#define BOARD_Y 0
#define CELLSIZE 30
const int BIRD_CLIPS[][4] = {
    {0,0,51,36},
    {0,0,51,36},
    {0,0,51,36}
};
#define BIRD_FRAMES 3
#endif // DEFS_H
