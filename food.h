#ifndef FOOD_H
#define FOOD_H

#include "snake.h"

class food
{
private:
    int size;
    int sprite;
    cords prise;
public:
    food(int size, vector<cords> avoid);
    int get_sprite();
    cords get_cords();
    void set_size(int size);
    void spawn(vector<cords> avoid);
};

#endif // FOOD_H
