#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "defs.h"
#include<algorithm>
#include<vector>
using namespace std;
struct Pipe
{
    SDL_Texture* texture;
    int x=SCREEN_WIDTH;
    int height;
    bool pass;
    int up_down=1;
    int wait=0;
    int acceleration=5;
    void update()
    {
        x-=game_speed;
    }
    void winding()
    {
        if(wait>=winding_cooldown)
        {
            height+=up_down*acceleration;
            if(acceleration>15)
            {
                acceleration=3;
                up_down*=-1;
            }
            else acceleration+=3;
            wait=0;
        }
        wait++;
    }
};
struct ScrollingBackground
{
    SDL_Texture *texture;
    int scrollingOffset=0;
    int width,height;

    void setTexture(SDL_Texture* _texture)
    {
        texture=_texture;
        SDL_QueryTexture(texture,NULL,NULL,&width,&height);
    }

    void scroll()
    {
        scrollingOffset-=game_speed;
        if(scrollingOffset<0) scrollingOffset=width;
    }
    void scroll_inverse()
    {
        scrollingOffset+=game_speed+5;
        if(scrollingOffset>height) scrollingOffset=0;
    }
};
struct Sprite
{
    SDL_Texture *texture;
    vector<SDL_Texture*>clips;
    int currentframes=0;
    void tick()
    {
        currentframes=(currentframes+1)%clips.size();
        texture=clips[currentframes];
    }
};
struct Graphics
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* bird1,*bird2,*bird3,*game_over,*board,*flappybird,*tap,*playbutton,*ready,*new_record,*resume,*pause;
    TTF_Font *font_score,*font_board;
    Mix_Chunk *point,*flap,*die,*highscore,*hit;
    Mix_Music *music,*background_music;
    void logErrorAndExit(const char* msg,const char* error)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR,"%s : %s",msg,error);
        SDL_Quit();
    }
    void initSDL()
    {
        if(SDL_Init(SDL_INIT_EVERYTHING)!=0)
        {
            logErrorAndExit("SDL_INIT",SDL_GetError());
        }
        window=SDL_CreateWindow(WINDOW_TITLE,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if(window==nullptr) logErrorAndExit("CreateWindow",SDL_GetError());
        renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if(renderer==nullptr) logErrorAndExit("CreateRenderer",SDL_GetError());
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"linear");
        SDL_RenderSetLogicalSize(renderer,SCREEN_WIDTH,SCREEN_HEIGHT);
        if (TTF_Init()==-1)
        {
            logErrorAndExit("SDL_ttf could not initialize! SDL_ttf Error: ",TTF_GetError());
        }
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            logErrorAndExit("SDL_mixer could not initialize! SDL_mixer Error: %s\n",Mix_GetError());
        }
    }
    void prepareScene(SDL_Texture* background)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,background,NULL,NULL);
    }
    void presentRenderer()
    {
        SDL_RenderPresent(renderer);
    }
    SDL_Texture* loadTexture(const char* filename)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"Loading %s",filename);
        SDL_Texture* texture=IMG_LoadTexture(renderer,filename);
        if(texture==nullptr) logErrorAndExit("CreateTexture",IMG_GetError());
        return texture;
     }
     TTF_Font* loadFont(const char* path,int size)
     {
         TTF_Font* font=TTF_OpenFont(path,size);
         if(font==nullptr)
         {
             logErrorAndExit("Load font : %s",TTF_GetError());
         }
         SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"Loading Font %s",path);
         return font;
     }
     Mix_Chunk* loadSound(const char* path)
     {
        Mix_Chunk* chunk = Mix_LoadWAV(path);
        if (chunk == nullptr)
        {
            logErrorAndExit("Could not load sound! SDL_mixer Error: %s", Mix_GetError());
        }
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"Loading %s",path);
        return chunk;
    }
    Mix_Music *loadMusic(const char* path)
    {
        Mix_Music *music = Mix_LoadMUS(path);
        if (music == nullptr)
        {
            logErrorAndExit("Could not load music! SDL_mixer Error: %s", Mix_GetError());
        }
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_INFO,"Loading %s",path);
        return music;
    }
     void init()
     {
        initSDL();
        bird1=loadTexture("fbimg/bird1.PNG");
        bird2=loadTexture("fbimg/bird2.PNG");
        bird3=loadTexture("fbimg/bird3.PNG");

        board=loadTexture("fbimg/scoreboard.PNG");
        game_over=loadTexture("fbimg/gameover1.PNG");

        flappybird=loadTexture("fbimg/flappybird.PNG");
        tap=loadTexture("fbimg/tap.PNG");
        playbutton=loadTexture("fbimg/playbutton.PNG");
        ready=loadTexture("fbimg/ready.PNG");
        new_record=loadTexture("fbimg/new.PNG");

        resume=loadTexture("fbimg/resume.PNG");
        pause=loadTexture("fbimg/pause.PNG");

        font_score=loadFont("font/fBirdFont.TTF",60);
        font_board=loadFont("font/fBirdFont.TTF",40);

        point=loadSound("sound/point.WAV");
        flap=loadSound("sound/flap.WAV");
        die=loadSound("sound/die.WAV");
        highscore=loadSound("sound/highscore.WAV");
        hit=loadSound("sound/hit.WAV");

        music=loadMusic("sound/Beanie.MP3");
        background_music=loadMusic("sound/Bleach.MP3");
     }
     void renderTexture(SDL_Texture* texture,int x,int y)
     {
         SDL_Rect dst;
         dst.x=x;
         dst.y=y;
         SDL_QueryTexture(texture,NULL,NULL,&dst.w,&dst.h);
         SDL_RenderCopy(renderer,texture,NULL,&dst);
     }
     void renderPipe(Pipe pipe,int y,int position)
     {
         SDL_Rect dst;
         dst.x=pipe.x;
         dst.y=y+pipe_gap*position-(position==1 ? pipe.height : 0 );
         SDL_QueryTexture(pipe.texture,NULL,NULL,&dst.w,&dst.h);
         dst.h+=pipe.height*position-pipe_gap;
         if(position==1) SDL_RenderCopy(renderer,pipe.texture,NULL,&dst);
         else
         {
             SDL_RenderCopyEx(renderer,pipe.texture,NULL,&dst,0,NULL,SDL_FLIP_VERTICAL);
         }
     }
     void renderTextureAngle(SDL_Texture* texture,int x,int y,int angle)
     {
         SDL_Rect dst;
         dst.x=x;
         dst.y=y;
         SDL_QueryTexture(texture,NULL,NULL,&dst.w,&dst.h);
         SDL_RenderCopyEx(renderer,texture,NULL,&dst,angle,NULL,SDL_FLIP_NONE);
     }
     void QUIT()
     {
         SDL_DestroyWindow(window);
         SDL_DestroyRenderer(renderer);
         IMG_Quit();
         SDL_Quit();
         TTF_Quit();
         Mix_Quit();
     }
     void renderBIRD(int x,int y,Sprite &sprite,int angle)
     {
         renderTextureAngle(sprite.texture,x,y,angle);
     }
     void renderBackground(ScrollingBackground bgr,int y)
     {
         renderTexture(bgr.texture,bgr.scrollingOffset,y);
         renderTexture(bgr.texture,bgr.scrollingOffset-bgr.width,y);
     }
     void renderRain(ScrollingBackground bgr,int x)
     {
         renderTexture(bgr.texture,x,bgr.scrollingOffset);
         renderTexture(bgr.texture,x,bgr.scrollingOffset-bgr.height);
     }
     void renderText(const char* text,int x,int y,SDL_Color textColor,TTF_Font *font)
     {
        SDL_Surface *surface=TTF_RenderText_Solid(font,text,textColor);
        if(surface==nullptr)
        {
            logErrorAndExit("Render text surface %s",TTF_GetError());
        }
        SDL_Texture* text_texture=SDL_CreateTextureFromSurface(renderer,surface);
        if(text_texture==nullptr)
        {
            logErrorAndExit("Create texture from surface %s",SDL_GetError());
        }
        renderTexture(text_texture,x,y);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(text_texture);
     }
     void playChunk(Mix_Chunk* chunk)
     {
        if(chunk!=nullptr)
        {
            Mix_PlayChannel(-1,chunk,0);
        }
     }
     void playMusic(Mix_Music *music)
    {
        if(Mix_PlayingMusic()== 0)
        {
            Mix_PlayMusic(music,-1);
        }
    }
};
vector<Pipe>Pipes;
bool ss(Pipe x,Pipe y)
{
    return x.x>y.x;
}
void Pipes_delete()
{
    sort(Pipes.begin(),Pipes.end(),ss);
    while(!Pipes.empty()&&Pipes[Pipes.size()-1].x<-100)
    {
        Pipes.pop_back();
    }
}
void Pipes_update()
{
    for(int i=0;i<Pipes.size();i++)
    {
        Pipes[i].update();
        Pipes[i].winding();
    }
}
void Pipes_draw(Graphics graphics)
{
    for(int i=0;i<Pipes.size();i++)
    {
        Pipe pipe=Pipes[i];
        graphics.renderPipe(pipe,170,1);
        graphics.renderPipe(pipe,0,-1);
//        SDL_SetRenderDrawColor(graphics.renderer,255,0,0,255);
//        SDL_Rect rect={pipe.x,170+pipe_gap-pipe.height,62,300+pipe.height};
//        SDL_RenderDrawRect(graphics.renderer,&rect);
//        SDL_Rect rect2={pipe.x,0,62,150-pipe.height};
//        SDL_RenderDrawRect(graphics.renderer,&rect2);
    }
}
#endif // GRAPHICS_H
