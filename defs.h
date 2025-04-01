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
int new_record=-1;
int new_record_cooldown=5;
int strobe=0;
int winding_cooldown=5;
bool die=false,congratulation=false,hit=false,menu=true;
bool acceleration=true;
bool pause_game=false;
Uint32 pipe_frequency=3000;
Uint32 time_now;
Uint32 time_pause,time_resume;
SDL_Texture *pipe;
char *score_text;
#endif // DEFS_H
