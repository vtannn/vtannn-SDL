#ifndef DEFS_H
#define DEFS_H
using namespace std;
const int SCREEN_WIDTH=700;
const int SCREEN_HEIGHT=800;
const char* WINDOW_TITLE="Vtan";
bool quit=false;
bool flying=false;
bool game_over=false;
int pipe_gap=150;
int game_speed=5;
int score=0;
int high_score=0;
int winding_cooldown=5;
bool die=false,congratulation=false,hit=false,menu=true;
Uint32 pipe_frequency=3000;
Uint32 time_now;
SDL_Texture *pipe;
char *score_text;
#endif // DEFS_H
