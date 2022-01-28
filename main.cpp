#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int difficulty = 3, size, time, win_size = 800;
    float resize = 0.95;

    switch (difficulty)
    {
    case 1 :
        size = 14;
        time = 350;
        break;
    case 2 :
        size = 14;
        time = 250;
        break;
    case 3 :
        size = 10;
        time = 250;
        break;
    case 4 :
        size = 10;
        time = 150;
        break;
    case 5 :
        size = 6;
        time = 200;
        break;
    default :
        size = 10;
        time = 250;
        difficulty = 3;
        break;
    }

    game w(difficulty, win_size, size, time, resize);
    w.show();

    return a.exec();
}
