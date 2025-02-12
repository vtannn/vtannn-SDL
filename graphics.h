#ifndef GRAPHICS_H
#define GRAPHICS_H
struct Graphics
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    void logErrorAndExit(const char* msg,const char* error)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR,"%s : %s",msg,error);
        SDL_Quit();
    }
    void init()
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
     void renderTexture(SDL_Texture* texture,int x,int y)
     {
         SDL_Rect dst;
         dst.x=x;
         dst.y=y;
         SDL_QueryTexture(texture,NULL,NULL,&dst.w,&dst.h);
         SDL_RenderCopy(renderer,texture,NULL,&dst);
     }
     void quit()
     {
         SDL_DestroyWindow(window);
         SDL_DestroyRenderer(renderer);
         IMG_Quit();
         SDL_Quit();
     }
};
#endif // GRAPHICS_H
