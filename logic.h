#ifndef LOGIC_H
#define LOGIC_H
#include "defs.h"
#include<algorithm>
struct Mouse
{
    int x,y;
    int dx=0,dy=0;
    int speed=0;
    int up_down=1;
    int wait=0;
    void move()
    {
        x+=dx;
        y+=dy;
        x=max(x,51);
        y=max(y,36);
        x=min(x,SCREEN_WIDTH-100);
        y=min(y,620);
    }
    void winding()
    {
        if(wait>=winding_cooldown)
        {
            y+=up_down*10;
            up_down*=-1;
            wait=0;
        }
        wait++;
    }
    void turnNorth()
    {
        dy=-speed;
        dx=0;
    }
    void turnSouth()
    {
        dy=speed;
        dx=0;
    }
    void turnWest()
    {
        dx=-speed;
        dy=0;
    }
    void turnEast()
    {
        dx=speed;
        dy=0;
    }
};
bool check_Collision_Pipe(Mouse bird_mouse)
{
    SDL_Rect bird_rect={bird_mouse.x,bird_mouse.y-36,51,36};
    for(int i=0;i<Pipes.size();i++)
    {
        Pipe pipe=Pipes[i];
        SDL_Rect pipe_bot_rect={pipe.x,170+pipe_gap-pipe.height,62,300+pipe.height};
        SDL_Rect pipe_top_rect={pipe.x,0,62,150-pipe.height};
        if(SDL_HasIntersection(&bird_rect,&pipe_bot_rect)||SDL_HasIntersection(&bird_rect,&pipe_top_rect)) return true;
    }
    return false;
}
bool check_Collision_Heart(Mouse bird_mouse)
{
    SDL_Rect bird_rect={bird_mouse.x,bird_mouse.y-36,51,36};
    for(int i=0;i<Hearts.size();i++)
    {
        Pipe heart=Hearts[i];
        SDL_Rect heart_rect={heart.x,heart.height,35,30};
        if(SDL_HasIntersection(&bird_rect,&heart_rect)) return true;
    }
    return false;
}
void check_pass_Pipe(Mouse bird_mouse,Graphics graphics)
{
    for(int i=0;i<Pipes.size();i++)
    {
        Pipe &pipe=Pipes[i];
        if(bird_mouse.x>pipe.x+31&&pipe.pass==false)
        {
            score++;
            pipe.pass=true;
            //sound
            graphics.playChunk(graphics.point);
            break;
        }
    }
}
char *convert_into_pointer(string score_string,char *score_text)
{
    score_text=new char [score_string.size()];
    for(int i=0;i<score_string.size();i++)
        score_text[i]=score_string[i];
    score_text[score_string.size()]='\0';
    return score_text;
}
bool check_Click(Mouse mouse,SDL_Rect rect)
{
    SDL_GetMouseState(&mouse.x,&mouse.y);
    if(mouse.x>rect.x&&mouse.x<rect.x+rect.w&&mouse.y>rect.y&&mouse.y<rect.y+rect.h) return true;
    return false;
}
void DestroyTexture(SDL_Texture* &texture)
{
    SDL_DestroyTexture(texture);
    texture=nullptr;
}
void CloseFont(TTF_Font* &font)
{
    TTF_CloseFont(font);
    font=nullptr;
}
void FreeChunk(Mix_Chunk* &chunk)
{
    Mix_FreeChunk(chunk);
    chunk=nullptr;
}
void FreeMusic(Mix_Music* &music)
{
    Mix_FreeMusic(music);
    music=nullptr;
}
#endif // LOGIC_H
