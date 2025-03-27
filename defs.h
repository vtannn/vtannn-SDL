#ifndef DEFS_H
#define DEFS_H
const int SCREEN_WIDTH=700;
const int SCREEN_HEIGHT=800;
const char* WINDOW_TITLE="Vtan";
bool quit=false;
bool flying=false;
bool game_over=false;
int pipe_gap=150;
int game_speed=5;
Uint32 pipe_frequency=3000;
SDL_Texture *pipe;
#endif // DEFS_H
