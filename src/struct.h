//
// Created by Asus on 12/25/2018.
//

#ifndef PROJECT_STRUCT_H
#define PROJECT_STRUCT_H

struct Bullet{
    double x,y,move_x,move_y;
    int time;

};

struct Tank{
    double x,y,move_x,move_y;
    double radius,degree;
    struct Bullet bullets[1000];
    int bullets_size;
    int current_bullets_number;
};

struct Wall{
    double x1,y1,x2,y2;
};


#endif //PROJECT_STRUCT_H
