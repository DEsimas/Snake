#include "snake.h"

snake::snake()
{
    blocks.push_back(cords(0,0));
    blocks.push_back(cords(0,1));

    direction.push_back(2);
    direction.push_back(1);
}

void snake::move()
{
    for(unsigned int i = 0; i < blocks.size(); i++)
    {
        switch (direction[i])
        {
        case 1 :
            blocks[i].y--;
            break;
        case 2 :
            blocks[i].x++;
            break;
        case 3 :
            blocks[i].y++;
            break;
        case 4 :
            blocks[i].x--;
            break;
        }
        if(i != 0)
        {
            if(blocks[i - 1].y == blocks[i].y - 1) direction[i] = 1;
            if(blocks[i - 1].x == blocks[i].x + 1) direction[i] = 2;
            if(blocks[i - 1].y == blocks[i].y + 1) direction[i] = 3;
            if(blocks[i - 1].x == blocks[i].x - 1) direction[i] = 4;
        }
    }
}

void snake::reload()
{
    blocks.clear();
    direction.clear();

    blocks.push_back(cords(0,0));
    blocks.push_back(cords(0,1));

    direction.push_back(2);
    direction.push_back(1);
}

void snake::add_sigment()
{
    blocks.push_back(cords(blocks[blocks.size() - 1].x, blocks[blocks.size() - 1].y));
    direction.push_back(-1);
}

vector<cords> snake::get_snake()
{
    return blocks;
}
