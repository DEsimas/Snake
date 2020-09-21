#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include "food.h"
#include "score.h"

class game : public QWidget, public snake, public food, public score
{
    Q_OBJECT
private slots:
    void update();
    void save();
    void reload();
    void change_difficulty();
private:
    int size;
    int time;
    int win_size;
    int difficulty;
    const float resize;

    bool on_pause;

    map<int, int> opposite;
    list<int> queue;

    QTimer* timer;
    QLineEdit* name;
    QSpinBox* new_dif;

    QSqlDatabase DB;
    QSqlQuery query;

    void end();
    void draw();
    bool is_end();
    void update_difficulty();
    void setLabel(int index, QLabel* label, QPixmap arg1, QPixmap arg2, QPixmap arg3, QPixmap arg4);
protected:
    void keyPressEvent(QKeyEvent* event);
public:
    game(int difficult, int win_size, int size, int time, float resize, QWidget* parrent = nullptr);
};

#endif // GAME_H
