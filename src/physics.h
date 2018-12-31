//
// Created by Asus on 12/26/2018.
//

#ifndef PROJECT_PHYSICS_H
#define PROJECT_PHYSICS_H


void turn(struct Tank tank,double degree);
void moveTank(int move_mark[500],struct Tank *tank,struct Wall walls[]);
int barkhord(struct Tank tank,struct Wall wall,double last_x,double last_y);
double dis(int x1,int y1,int x2,int y2);




#endif //PROJECT_PHYSICS_H
