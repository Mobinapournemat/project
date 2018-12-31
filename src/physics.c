#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "view.h"
#include "struct.h"
#include <math.h>

const double step = 0.3;
const double turn_degree=0.2;
const int bullet_max_number=4;
const double bullet_speed=0.3;
const double time_between_bullets=100;

void turn(struct Tank *tank,double degree)
{
    tank->degree+=degree;
    tank->move_x=cos(tank->degree*M_PI/180);
    tank->move_y=sin(tank->degree*M_PI/180);
}

double dis(int x1,int y1,int x2,int y2)
{
    return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}

int barkhord(struct Tank tank,struct Wall wall,double last_x,double last_y)
{
    if(dis(wall.x1,wall.y1,tank.x,tank.y)<=tank.radius*tank.radius)
    {
        if(dis(wall.x1,wall.y1,last_x,last_y)<dis(wall.x1,wall.y1,tank.x,tank.y))return 0;
        return 3;
    }
    if(dis(wall.x2,wall.y2,tank.x,tank.y)<=tank.radius*tank.radius)
    {
        if(dis(wall.x2,wall.y2,last_x,last_y)<dis(wall.x2,wall.y2,tank.x,tank.y))return 0;
        return 3;
    }


    if(wall.x1==wall.x2)
    {
        if(wall.x1<=tank.x-tank.radius || wall.x1>=tank.x+tank.radius)return 0;
        if((wall.y1>=tank.y && wall.y2>=tank.y) || (wall.y1<=tank.y && wall.y2<=tank.y))return 0;
        return 1;
    }
    else
    {
        if(wall.y1<=tank.y-tank.radius || wall.y1>=tank.y+tank.radius)return 0;
        if((wall.x1>=tank.x && wall.x2>=tank.x) || (wall.x1<=tank.x && wall.x2<=tank.x))return 0;
        return 2;
    }
}

void moveTank(int move_mark[500],struct Tank *tank,struct Wall walls[])
{
    if (move_mark[SDLK_UP % 500]) {
        int last_x=tank->x;
        int last_y=tank->y;
        tank->x += tank->move_x * step;
        tank->y += tank->move_y * step;
        for(int i=0;i<22;i++)
        {
            int tmp = barkhord(*tank, walls[i], last_x, last_y);
            if((tmp&1))tank->x=last_x;
            if((tmp&2))tank->y=last_y;
        }
    }

    if(move_mark[SDLK_DOWN%500]) {int last_x=tank->x;
        int last_y=tank->y;
        tank->x -= tank->move_x * step/2;
        tank->y -= tank->move_y * step/2;
        for(int i=0;i<22;i++)
        {
            int tmp = barkhord(*tank, walls[i], last_x, last_y);
            if((tmp&1))tank->x=last_x;
            if((tmp&2))tank->y=last_y;
        }
    }
    if(move_mark[SDLK_RIGHT%500]) {
        turn(tank,turn_degree);
    }
    if(move_mark[SDLK_LEFT%500]) {
        turn(tank,-turn_degree);
    }
    if(move_mark[SDLK_SPACE%500]) {
        if(tank->current_bullets_number>=bullet_max_number)return ;
        int min_time=9999999;
        for(int i=0;i<tank->bullets_size;i++)
            if(min_time>tank->bullets[i].time)
                min_time=tank->bullets[i].time;
        if(min_time<time_between_bullets)return ;
        tank->bullets[tank->bullets_size].x=tank->x+1.5*tank->radius*tank->move_x;
        tank->bullets[tank->bullets_size].y=tank->y+1.5*tank->radius*tank->move_y;
        tank->bullets[tank->bullets_size].move_x=tank->move_x*bullet_speed;
        tank->bullets[tank->bullets_size].move_y=tank->move_y*bullet_speed;
        tank->bullets[tank->bullets_size].time=0;
        tank->bullets_size++;
    }
}



