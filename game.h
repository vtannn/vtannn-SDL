#ifndef GAME_H
#define GAME_H
#include"graphics.h"
#include"logic.h"
struct Game
{
    Graphics graphics;

    SDL_Texture *background;

    ScrollingBackground bgr;

    ScrollingBackground ground;

    ScrollingBackground rain;

    Mouse bird_mouse={326,282};

    Sprite bird;

    SDL_Texture *pipe;
    Uint32 last_pipe=SDL_GetTicks()-pipe_frequency;

    SDL_Color color_white={255,255,255,0},color_pink={255,0,255,0},color_red={255,0,0,0};

    Mouse restart_mouse;
    SDL_Texture *restart_texture;
    SDL_Rect restart_rect={SCREEN_WIDTH/2-60,SCREEN_HEIGHT/2+20,120,42};

    Mouse menu_mouse;
    SDL_Rect menu_rect={265,497,200,112};

    Mouse flappybird_mouse={159,131},ready_mouse={275,310},tap_mouse={290,367};

    Mouse pause_mouse;
    SDL_Rect pause_rect={10,10,40,44};

    SDL_Event e;
    void CHECK_QUIT_GAME()
    {
        if(SDL_PollEvent(&e))
        {
            if(e.type==SDL_QUIT) quit=true;
        }
    }
    void INIT()
    {
        graphics.init();

        background=graphics.loadTexture("fbimg/bg.PNG");
        bgr.setTexture(background);
        ground.setTexture(graphics.loadTexture("fbimg/ground.PNG"));
        rain.setTexture(graphics.loadTexture("fbimg/rain.PNG"));
        pipe=graphics.loadTexture("fbimg/pipe.PNG");
        restart_texture=graphics.loadTexture("fbimg/restart.PNG");

        bird.clips.push_back(graphics.bird1);
        bird.clips.push_back(graphics.bird2);
        bird.clips.push_back(graphics.bird3);

    }

    void ACCELERATE()
    {
        if(score%3==0)
        {
            if(acceleration&&game_speed<10)
            {
                game_speed++;
                if(pipe_frequency>1500)
                pipe_frequency-=500;
                acceleration=false;
            }
        }
        else acceleration=true;
    }
    void CHECK_SCORE_AND_HIGHSCORE()
    {
        check_pass_Pipe(bird_mouse,graphics);
        high_score=max(high_score,score);
    }
    void CHECK_COLLISION()
    {
        if(check_Collision(bird_mouse))
        {
            game_over=true;
            //sound
            if(!die)
            {
                graphics.playChunk(graphics.die);
                die=true;
            }
        }
        if(bird_mouse.y==620)
        {
            game_over=true;
            //sound
            if(!hit)
            {
                graphics.playChunk(graphics.hit);
                hit=true;
            }
        }
    }
    void RENDER_BACKGROUND()
    {
        SDL_RenderClear(graphics.renderer);
        graphics.renderBackground(bgr,0);
        graphics.renderRain(rain,0);
        graphics.renderBackground(ground,620);
        rain.scroll_inverse();
    }
    void MENU()
    {
        //sound
        graphics.playMusic(graphics.music);
        ///render
        graphics.renderTexture(graphics.flappybird,flappybird_mouse.x,flappybird_mouse.y);
        graphics.renderTexture(graphics.ready,ready_mouse.x,ready_mouse.y);
        graphics.renderTexture(graphics.tap,tap_mouse.x,tap_mouse.y);
        graphics.renderTexture(graphics.playbutton,265,507);
        graphics.renderBIRD(bird_mouse.x,bird_mouse.y-36,bird,bird_mouse.speed);
        bird.tick();
        //winding
        flappybird_mouse.winding();
        ready_mouse.winding();
        tap_mouse.winding();
        bird_mouse.winding();
        //check click play button
        if(check_Click(menu_mouse,menu_rect))
        {
            if(e.type==SDL_MOUSEBUTTONDOWN)
            {
                if(e.button.button==SDL_BUTTON_LEFT)
                {
                    //delete menu
                    menu=false;
                    bird_mouse={100,SCREEN_HEIGHT/2-100};
                    Mix_HaltMusic();
                }
            }
        }
    }
    void RENDER_PIPE_AND_SCORE()
    {
        ///sound
        graphics.playMusic(graphics.background_music);
        ///render
        //pipe
        Pipes_draw(graphics);
        //score
        score_text=convert_into_pointer(to_string(score),score_text);
        graphics.renderText(score_text,SCREEN_WIDTH/2-10*(strlen(score_text)),10,color_white,graphics.font_score);
    }
    void CHECK_CLICKED_PAUSE_AND_RESUME_BUTTON()
    {
        if(check_Click(pause_mouse,pause_rect))
        {
            if(e.type==SDL_MOUSEBUTTONDOWN)
            {
                if(e.button.button==SDL_BUTTON_LEFT)
                {
                    if(pause_game)
                    {
                        time_resume=SDL_GetTicks();
                        last_pipe=time_resume-(time_pause-last_pipe);
                    }
                    else time_pause=SDL_GetTicks();
                    pause_game=1-pause_game;
                    //cout<<time_delay<<endl;
                }
            }
        }
    }
    void GRAVITY()
    {
        bird_mouse.speed+=4;
        bird_mouse.speed=min(bird_mouse.speed,20);
        bird_mouse.turnSouth();
        bird_mouse.move();
        bird_mouse.y=min(bird_mouse.y,620);
    }
    void SCROLL()
    {
        bgr.scroll();
        ground.scroll();
        bird.tick();
        if(flying) Pipes_update();
    }
    void JUMP()
    {
        if(e.type==SDL_KEYDOWN&&!menu)
        {
            if(!flying) flying=true;
            bird_mouse.speed=-25;
            //sound
            graphics.playChunk(graphics.flap);
        }
    }
    void RENDER_RESUME_BUTTON()
    {
        graphics.renderTexture(graphics.resume,10,10);
    }
    void CREATE_PIPE()
    {
        if(flying)
        {
            Pipes_delete();
            time_now=SDL_GetTicks();
            if(time_now-last_pipe>=pipe_frequency)
            {
                Pipe next_pipe;
                next_pipe={pipe,SCREEN_WIDTH,0,false};
                //random
                int a=-75,b=75;
                int random=rand()%(b-a+1)+a;
                next_pipe.height=random;
                Pipes.push_back(next_pipe);
                last_pipe=time_now;
            }
        }
    }
    void RENDER_PAUSE_BUTTON()
    {
        graphics.renderTexture(graphics.pause,10,10);
    }
    void RENDER_BIRD()
    {
        graphics.renderBIRD(bird_mouse.x,bird_mouse.y-36,bird,bird_mouse.speed);
//              SDL_SetRenderDrawColor(graphics.renderer,255,0,0,255);
//              SDL_Rect rect={bird_mouse.x,bird_mouse.y-36,51,36};
//              SDL_RenderDrawRect(graphics.renderer,&rect);
    }
    void RENDER_GAME_OVER()
    {
        ///render
        //bird
        graphics.renderBIRD(bird_mouse.x,bird_mouse.y-36,bird,90);
        //game over
        graphics.renderTexture(graphics.game_over,SCREEN_WIDTH/2-160,SCREEN_HEIGHT/2-300);
        //score board
        graphics.renderTexture(graphics.board,SCREEN_WIDTH/2-80,SCREEN_HEIGHT/2-215);
        //score
        char *score_board=convert_into_pointer("SCORE",score_board);
        graphics.renderText(score_board,SCREEN_WIDTH/2-55,SCREEN_HEIGHT/2-180,color_pink,graphics.font_board);

        score_board=convert_into_pointer(to_string(score),score_board);
        graphics.renderText(score_board,SCREEN_WIDTH/2-strlen(score_board)*8,SCREEN_HEIGHT/2-130,color_pink,graphics.font_board);
        //high score
        score_board=convert_into_pointer("BEST",score_board);
        graphics.renderText(score_board,SCREEN_WIDTH/2-44,SCREEN_HEIGHT/2-80,color_red,graphics.font_board);

        score_board=convert_into_pointer(to_string(high_score),score_board);
        graphics.renderText(score_board,SCREEN_WIDTH/2-strlen(score_board)*8,SCREEN_HEIGHT/2-30,color_red,graphics.font_board);
        //restart
        graphics.renderTexture(restart_texture,restart_rect.x,restart_rect.y);
        //sound
        if(score==high_score)
        {
            if(congratulation==false)
            {
                graphics.playChunk(graphics.highscore);
                congratulation=true;
            }
            //new record
            if(score>new_record)
            {
                if(strobe>=new_record_cooldown)
                {
                    graphics.renderTexture(graphics.new_record,SCREEN_WIDTH/2+43,SCREEN_HEIGHT/2-80);
                    strobe=0;
                }
                strobe++;
            }
        }
        else
        {
            if(lose==false)
            {
                graphics.playChunk(graphics.losing);
                lose=true;
            }
        }
    }
    void RESTART()
    {
        if(check_Click(restart_mouse,restart_rect))
        {
            if(e.type==SDL_MOUSEBUTTONDOWN)
            {
                if(e.button.button==SDL_BUTTON_LEFT)
                {
                    //reset game
                    game_over=false;
                    bird_mouse={100,SCREEN_HEIGHT/2-100};
                    Pipes.clear();
                    flying=false;
                    die=false;
                    congratulation=false;
                    hit=false;
                    new_record=max(new_record,high_score);
                    score=0;
                    game_speed=5;
                    pipe_frequency=3000;
                    Mix_Pause(-1);
                }
            }
        }
    }
    void PRESENT_RENDERER()
    {
        graphics.presentRenderer();
    }
};
#endif // GAME_H
