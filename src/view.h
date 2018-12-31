//
// Created by Asus on 12/25/2018.
//

#ifndef PROJECT_VIEW_H
#define PROJECT_VIEW_H

#include "struct.h"

void init_window();
void render_clear();
void draw_bullet(struct Bullet bullet);
void draw_tank(struct Tank tank);
void draw_line(struct Tank tank);
void draw_walls(struct Wall walls[]);
void render_present();
void exit_window();

#endif //PROJECT_VIEW_H
