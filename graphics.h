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
    void update()
    {
        if(x>=-300) x-=game_speed;
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
    SDL_Texture* bird1,*bird2,*bird3;
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
     void init()
     {
        initSDL();
        bird1=loadTexture("fbimg/bird1.PNG");
        bird2=loadTexture("fbimg/bird2.PNG");
        bird3=loadTexture("fbimg/bird3.PNG");
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
     }
     void renderBIRD(int x,int y,Sprite &sprite,int angle)
     {
         renderTextureAngle(sprite.texture,x,y,angle);
     }
     void renderBackground(ScrollingBackground bgr,int x)
     {
         renderTexture(bgr.texture,bgr.scrollingOffset,x);
         renderTexture(bgr.texture,bgr.scrollingOffset-bgr.width,x);
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
