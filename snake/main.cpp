#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int difficult = 3, size, time, win_size = 900;
    float resize = 0.97;

    ifstream cfg("settings.cfg");

    if(cfg.is_open())
    {
        string s;
        cfg >> s;
        difficult = stoi(s);
        cfg >> s;
        win_size = stoi(s) - 100;
    }

    switch (difficult)
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
        difficult = 3;
        break;
    }

    if(win_size < 250)
    {
        win_size = 250;
        resize = 0.91;
    }
    else if(win_size < 500)
        resize = 0.92;
    else
        resize = 0.97;

    game w(difficult, win_size, size, time, resize);
    w.show();

    return a.exec();
}
