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
#endif // LOGIC_H
