#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "view.h"
#include "struct.h"
#include "physics.h"

const int bullet_max_time=5000;

int move_mark[500];

struct Tank tank;

#ifdef main
#undef main
#endif /* main */


int main(int argc , char* argv[]) {

  /*  SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("workshop", 20, 20, 800, 600, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);*/
    init_window();
    tank.x=tank.y=50;
    tank.radius=30;
    tank.move_x=1;
    tank.move_y=0;
    tank.degree=0;
    tank.current_bullets_number=tank.bullets_size=0;

    struct Wall walls[22];
    int cords[22][4]={{0,0,0,7},{1,1,1,2},{1,3,1,4},{2,2,2,3},{2,4,2,6},{3,2,3,3},{4,2,4,3},{4,5,4,6},{5,4,5,6},
                      {0,0,6,0},{3,1,6,1},{0,2,1,2},{4,2,5,2},{1,3,4,3},{5,3,6,3},{2,4,3,4},{4,4,5,4},{1,5,2,5},
                      {3,5,4,5},{0,6,1,6},{6,0,6,7},{0,7,6,7}};
    for(int i=0;i<22;i++)
    {
        walls[i].x1=cords[i][0]*100;
        walls[i].y1=cords[i][1]*100;
        walls[i].x2=cords[i][2]*100;
        walls[i].y2=cords[i][3]*100;
    }


    while (1) {
        SDL_Event event;
        render_clear();
        if(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) { break; }
            if (event.type == SDL_KEYDOWN)
                move_mark[event.key.keysym.sym%500]=1;
            if (event.type == SDL_KEYUP)
                move_mark[event.key.keysym.sym%500]=0;
        }
        moveTank(move_mark,&tank,walls);
        tank.current_bullets_number=0;
        for(int i=0;i<tank.bullets_size;i++)
            if(tank.bullets[i].time<bullet_max_time)
            {
                tank.current_bullets_number++;
                tank.bullets[i].time++;
                draw_bullet(tank.bullets[i]);
                tank.bullets[i].x+=tank.bullets[i].move_x;
                tank.bullets[i].y+=tank.bullets[i].move_y;
            }
        draw_walls(walls);
        draw_tank(tank);
        draw_line(tank);
        render_present();
    }
    exit_window();
    return 0;
}
