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
int lives=0,lives_cooldown=0,reset_frequency=0;
bool die=false,congratulation=false,hit=false,menu=true,lose=false;
bool acceleration=true;
bool pause_game=false,muted=false;
bool reset=false;
Uint32 pipe_frequency=3000;
Uint32 time_now;
Uint32 time_pause,time_resume;
Uint32 reset_time_pause;
SDL_Texture *pipe,*heart;
Mix_Chunk *life;
char *score_text;
#endif // DEFS_H
