#ifndef LOGIC_H
#define LOGIC_H
#include "defs.h"
#include<algorithm>
using namespace std;
struct Mouse
{
    int x=100,y=SCREEN_HEIGHT/2-50;
    int dx=0,dy=0;
    int speed=0;
    bool check=true;
    void move()
    {
        x+=dx;
        y+=dy;
        x=max(x,0);
        y=max(y,0);
        x=min(x,SCREEN_WIDTH-100);
        y=min(y,SCREEN_HEIGHT-100);
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
