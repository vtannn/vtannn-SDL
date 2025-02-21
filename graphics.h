#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "logic.h"
#include "defs.h"
struct Graphics
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* cell_Empty,*cell_X,*cell_O,*winner1,*winner2;
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
    void init()
    {
        initSDL();
        cell_Empty=loadTexture("xo/cell_empty.png");
        cell_X=loadTexture("xo/cell_x.png");
        cell_O=loadTexture("xo/cell_o.png");
        winner1=loadTexture("xo/winner-1.png");
        winner2=loadTexture("xo/winner-2.png");
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
         dst.w=dst.w*30/100;
         dst.h=dst.h*30/100;
         SDL_RenderCopy(renderer,texture,NULL,&dst);
     }
     void QUIT()
     {
         SDL_DestroyWindow(window);
         SDL_DestroyRenderer(renderer);
         SDL_DestroyTexture(cell_Empty);
         SDL_DestroyTexture(cell_X);
         SDL_DestroyTexture(cell_O);
         IMG_Quit();
         SDL_Quit();
     }
     void prepareBackground(const Tictactoe &game)
     {
         for(int i=0;i<BOARDSIZE;i++)
         {
             for(int j=0;j<BOARDSIZE;j++)
             {
                 int x=BOARD_X + i*CELLSIZE;
                 int y=BOARD_Y + j*CELLSIZE;
                 renderTexture(cell_Empty,x,y);
            }
         }
         presentRenderer();
     }
     void render(const Tictactoe& game,int i,int j)
     {
             int x=BOARD_X + i*CELLSIZE;
             int y=BOARD_Y + j*CELLSIZE;
             switch(game.board[i][j])
             {
                 case EMPTY_CELL: renderTexture(cell_Empty,x,y);break;
                 case X_CELL: renderTexture(cell_X,x,y);break;
                 case O_CELL: renderTexture(cell_O,x,y);break;
             }
         presentRenderer();
     }
     void stopGame(Tictactoe &game,int row,int col)
     {
         bool kt=game.check();
         if(kt)
         {
             int x=BOARD_X + row*CELLSIZE;
             int y=BOARD_Y + col*CELLSIZE;
             if(kt==1) prepareScene(winner1);
             else prepareScene(winner2);
             presentRenderer();
             SDL_Delay(1000);
             quit=true;
         }
     }
};
#endif // GRAPHICS_H
