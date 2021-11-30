#include "food.h"

food::food(int size, vector<cords> avoid)
{
    this->size = size;
    spawn(avoid);
}

int food::get_sprite()
{
    return sprite;
}

cords food::get_cords()
{
    return prise;
}

void food::set_size(int size)
{
    this->size = size;
}

void food::spawn(vector<cords> avoid)
{
    if((int)avoid.size() != size*size)
    {
        bool ch;
        sprite = rand() % 4 + 1;
        do
        {
            ch = false;
            prise.x = rand() % size;
            prise.y = rand() % size;

            for(auto i : avoid)
                if((i.x == prise.x) && (i.y == prise.y))
                    ch = true;
        } while(ch);
    }
}
