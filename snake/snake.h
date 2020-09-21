#ifndef SNAKE_H
#define SNAKE_H

#include "headers.h"

class snake
{
private:
    vector<cords> blocks;

public:
    vector<int> direction;

    snake();
    void move();
    void reload();
    void add_sigment();
    vector<cords> get_snake();
};

#endif // SNAKE_H
