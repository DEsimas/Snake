#ifndef SCORE_H
#define SCORE_H

#include "headers.h"

class score
{
private:
    int points;
    bool added;

    QSqlQuery query;
    QSqlDatabase DataBase;
public:
    score();
    void zero();
    void reload();
    int get_score();
    void add_score();
    void add_record(QString name, int score, int dif);
    void create_score_table(QGridLayout* table, int dif);
};

#endif // SCORE_H
