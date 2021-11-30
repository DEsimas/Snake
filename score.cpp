#include "score.h"

score::score()
{
    added = false;
    points = 2;
}

void score::zero()
{
    points = 0;
}

void score::reload()
{
    added = false;
    points = 2;
}

int score::get_score()
{
    return points;
}

void score::add_score()
{
    points++;
}

void score::add_record(QString name, int score, int dif)
{
    if((!added) && (name!= ""))
    {
        added = true;
        QString table;
        switch (dif)
        {
        case 1 :
            table = "first";
            break;
        case 2 :
            table = "second";
            break;
        case 3 :
            table = "third";
            break;
        case 4 :
            table = "fourth";
            break;
        case 5 :
            table = "fifth";
            break;
        }

        query.exec("INSERT INTO " + table + " VALUES ('" + name + "', " + QString::number(score) + ")");
    }
}

void score::create_score_table(QGridLayout* table, int dif)
{
    DataBase = QSqlDatabase::addDatabase("QSQLITE");
    DataBase.setDatabaseName(QCoreApplication::applicationDirPath() + QDir::separator() + "score.db");


    if(DataBase.open())
    {
        query = QSqlQuery(DataBase);

        query.exec("CREATE TABLE IF NOT EXISTS first (name TEXT, score INTEGER)");
        query.exec("CREATE TABLE IF NOT EXISTS second (name TEXT, score INTEGER)");
        query.exec("CREATE TABLE IF NOT EXISTS third (name TEXT, score INTEGER)");
        query.exec("CREATE TABLE IF NOT EXISTS fourth (name TEXT, score INTEGER)");
        query.exec("CREATE TABLE IF NOT EXISTS fifth (name TEXT, score INTEGER)");

        switch (dif)
        {
        case 1 :
            query.exec("SELECT * FROM first ORDER BY score DESC");
            break;
        case 2 :
            query.exec("SELECT * FROM second ORDER BY score DESC");
            break;
        case 3 :
            query.exec("SELECT * FROM third ORDER BY score DESC");
            break;
        case 4 :
            query.exec("SELECT * FROM fourth ORDER BY score DESC");
            break;
        case 5 :
            query.exec("SELECT * FROM fifth ORDER BY score DESC");
            break;
        }

        for(int i = 0; i < 11; i++)
        {
            QLabel* place = new QLabel(QString::number(i));
            table->addWidget(place, i, 0);
            QLabel* name = new QLabel(query.value(0).toString());
            table->addWidget(name, i, 1);
            QLabel* score = new QLabel(query.value(1).toString());
            table->addWidget(score, i, 2);
            query.next();
        }

        QLabel* fields = new QLabel("#");
        table->addWidget(fields, 0, 0);
        QLabel* name = new QLabel("Имя");
        table->addWidget(name, 0, 1);
        QLabel* score = new QLabel("Длина");
        table->addWidget(score, 0, 2);

    }
    else
    {
        QLabel* lbl = new QLabel("База данных не  открыта! Ошибка: " + DataBase.lastError().text());
        table->addWidget(lbl);
    }

}
