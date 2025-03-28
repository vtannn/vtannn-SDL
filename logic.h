#ifndef LOGIC_H
#define LOGIC_H
#include "defs.h"
#include<algorithm>
struct Mouse
{
    int x=100,y=SCREEN_HEIGHT/2-100;
    int dx=0,dy=0;
    int speed=0;
    bool check=true;
    void move()
    {
        x+=dx;
        y+=dy;
        x=max(x,51);
        y=max(y,36);
        x=min(x,SCREEN_WIDTH-100);
        y=min(y,620);
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
