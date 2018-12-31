//
// Created by Asus on 12/25/2018.
//
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "view.h"
#include "struct.h"

SDL_Window *window;
SDL_Renderer *renderer;

void init_window() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("alter_tank", 20, 20, 600, 700, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void render_clear()
{
    SDL_SetRenderDrawColor(renderer,200,200,200,50);
    SDL_RenderClear(renderer);
}

void draw_bullet(struct Bullet bullet)
{
    filledCircleRGBA(renderer,bullet.x,bullet.y,4,128,0,255,100);
}

void draw_tank(struct Tank tank)
{
    filledCircleRGBA(renderer,tank.x,tank.y,tank.radius,0,150,255,100);
}

void draw_line(struct Tank tank)
{
    thickLineRGBA(renderer,tank.x,tank.y,tank.x+1.5*tank.radius*tank.move_x,tank.y+1.5*tank.radius*tank.move_y,10,0,150,255,100);
}

void draw_walls(struct Wall walls[])
{
    for(int i=0;i<22;i++)
    {
        lineRGBA(renderer,walls[i].x1,walls[i].y1,walls[i].x2,walls[i].y2,0,0,0,100);
    }
}

void render_present()
{
    SDL_RenderPresent(renderer);
}

void exit_window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
