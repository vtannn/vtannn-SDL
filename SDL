#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
using namespace std;
int main(int argc,char* args[])
{
    srand(time(NULL));

    Game GAME;
    GAME.INIT();
    while(!quit)
    {
        ///quit game
        GAME.CHECK_QUIT_GAME();
        ///acceleration
        GAME.ACCELERATE();
        ///check score and high score
        GAME.CHECK_SCORE_AND_HIGHSCORE();
        //cerr<<score<<endl;
        ///check collision
        GAME.CHECK_COLLISION();
        ///render eternally
        GAME.RENDER_BACKGROUND();
        ///menu
        if(menu)
        {
            GAME.MENU();
        }
        else
        {
            GAME.RENDER_PIPE_AND_SCORE();
            ///check clicked pause and resume button
            GAME.CHECK_CLICKED_PAUSE_AND_RESUME_BUTTON();
            if(flying&&pause_game==false)
            {
                ///gravity
                GAME.GRAVITY();
            }
            if(!game_over)
            {
                //bird
                GAME.RENDER_BIRD();
                ///pause game
                if(pause_game==false)
                {
                    if(reset==false)
                    {
                        ///scroll
                        GAME.SCROLL();
                        //pipe
                        GAME.CREATE_PIPE_AND_HEART();
                    }
                    ///jump
                    GAME.JUMP();
                    //resume button
                    GAME.RENDER_RESUME_BUTTON();
                }
                else
                //pause button
                GAME.RENDER_PAUSE_BUTTON();
                ///mute
                GAME.CHECK_CLICKED_MUTE_AND_UNMUTE_BUTTON();
                if(muted==false)
                {
                    GAME.RENDER_UNMUTE_BUTTON();
                    Mix_ResumeMusic();
                }
                else
                {
                    GAME.RENDER_MUTE_BUTTON();
                    Mix_PauseMusic();
                    Mix_Pause(-1);
                }
            }
            else
            {
                ///render game over
                GAME.RENDER_GAME_OVER();
                ///restart
                GAME.RESTART();
            }
        }
        GAME.PRESENT_RENDERER();
        SDL_Delay(40);
    }
    GAME.DESTROY_AND_QUIT();
}
