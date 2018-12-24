#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>


struct Bullet{
    double x,y,move_x,move_y;
    int time;

}bullet[10000];


double tank_x=100;
double tank_y=100;
double tank_radius=30;
double tank_move_x=1;
double tank_move_y=0;
double tank_move_degree=0;
int number_of_bullets=0;
const int step = 20;
const int bullet_speed=20;
const int bullet_max_time=20;
const double PI=3.14159265359;

void turn_degree(double degree)
{
    tank_move_degree+=degree;
    tank_move_x=cos(tank_move_degree*PI/180);
    tank_move_y=sin(tank_move_degree*PI/180);
}

void moveTank(SDL_Keycode key) {
    switch (key) {
        case SDLK_UP:
            tank_x += tank_move_x*step;
            tank_y += tank_move_y*step;
            break;
        case SDLK_DOWN:
            tank_x -= tank_move_x*step;
            tank_y -= tank_move_y*step;
            break;
        case SDLK_RIGHT:
            turn_degree(15);
            break;
        case SDLK_LEFT:
            turn_degree(-15);
            break;
        case SDLK_SPACE:
            bullet[number_of_bullets].x=tank_x+1.5*tank_radius*tank_move_x;
            bullet[number_of_bullets].y=tank_y+1.5*tank_radius*tank_move_y;
            bullet[number_of_bullets].move_x=tank_move_x*bullet_speed;
            bullet[number_of_bullets].move_y=tank_move_y*bullet_speed;
            bullet[number_of_bullets].time=0;
            number_of_bullets++;
            break;
    }
}



#ifdef main
#undef main
#endif /* main */


int main(int argc , char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("workshop", 20, 20, 800, 600, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    while (1) {
        SDL_Event event;
        if(SDL_PollEvent(&event))
        {
            if(event.type==SDL_QUIT) {break;}
            if(event.type==SDL_KEYDOWN)
                moveTank(event.key.keysym.sym);
            SDL_SetRenderDrawColor(renderer,200,200,200,50);
            SDL_RenderClear(renderer);
            for(int i=0;i<number_of_bullets;i++)
                if(bullet[i].time<bullet_max_time)
                {
                    bullet[i].time++;
                    filledCircleRGBA(renderer,bullet[i].x,bullet[i].y,4,128,0,255,100);
                    bullet[i].x+=bullet[i].move_x;
                    bullet[i].y+=bullet[i].move_y;
                }
            filledCircleRGBA(renderer,tank_x,tank_y,tank_radius,0,150,255,100);
            thickLineRGBA(renderer,tank_x,tank_y,tank_x+1.5*tank_radius*tank_move_x,tank_y+1.5*tank_radius*tank_move_y,10,0,150,255,100);

            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
