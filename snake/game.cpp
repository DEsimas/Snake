#include "game.h"

void game::update()
{
    while(queue.size() != 0 ? queue.front() == direction[0] || queue.front() == opposite[direction[0]] : false)
        queue.erase(queue.begin());
    if(queue.size() != 0)
    {
        direction[0] = queue.front();
        queue.erase(queue.begin());
    }

    if((get_cords().x == get_snake()[0].x) && (get_cords().y == get_snake()[0].y))
    {
        spawn(get_snake());
        add_score();
        add_sigment();
    }

    snake::move();
    if(!is_end())
        draw();
    else
        end();
}

void game::save()
{
    add_record(name->text(), get_score(), difficulty);
    end();
}

void game::reload()
{
    queue.clear();
    score::reload();
    snake::reload();

    draw();
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(time);
    on_pause = false;
}

void game::change_difficulty()
{
    this->difficulty = new_dif->value();
    update_difficulty();
    set_size(this->size);
    spawn(get_snake());
    zero();
    end();
}

void game::end()
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(update()));
    on_pause = true;

    QGridLayout* fin = new QGridLayout;
    QLabel* fin_text = new QLabel("Ваша длина: " + QString::number(get_score()));
    QPushButton* cont = new QPushButton("Продолжить");
    connect(cont, SIGNAL(released()), this, SLOT(reload()));
    fin->addWidget(fin_text, 0, 0);
    fin->addWidget(cont, 0, 1);

    QGridLayout* dif = new QGridLayout;
    new_dif = new QSpinBox;
    new_dif->setMinimum(1);
    new_dif->setMaximum(5);
    new_dif->setValue(difficulty);
    QPushButton* change = new QPushButton("Изменить сложность");
    connect(change, SIGNAL(released()), this, SLOT(change_difficulty()));
    dif->addWidget(new_dif, 0, 0);
    dif->addWidget(change, 0, 1);

    QGridLayout* adding = new QGridLayout;
    name = new QLineEdit;
    QPushButton* add = new QPushButton("Сохранить");
    connect(add, SIGNAL(released()), this, SLOT(save()));
    adding->addWidget(name, 0, 0);
    adding->addWidget(add, 0, 1);

    QGridLayout* score_table = new QGridLayout;
    create_score_table(score_table, difficulty);

    QGridLayout* lay = new QGridLayout;
    lay->setVerticalSpacing(5);
    lay->addLayout(fin, 0, 0);
    lay->addLayout(dif, 1, 0);
    lay->addLayout(adding, 2, 0);
    lay->addLayout(score_table, 3, 0);

    qDeleteAll(findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
    delete this->layout();
    setLayout(lay);

}

void game::draw()
{
    QPixmap _food1(":/food/food1.png");
    QPixmap _food2(":/food/food2.png");
    QPixmap _food3(":/food/food3.png");
    QPixmap _food4(":/food/food4.png");

    QPixmap _snake_block1(":/parts/body/snake_body1.png");
    QPixmap _snake_block2(":/parts/body/snake_body2.png");
    QPixmap _snake_block3(":/parts/body/snake_body3.png");
    QPixmap _snake_block4(":/parts/body/snake_body4.png");

    QPixmap _snake_head1(":/parts/head/snake_head1.png");
    QPixmap _snake_head2(":/parts/head/snake_head2.png");
    QPixmap _snake_head3(":/parts/head/snake_head3.png");
    QPixmap _snake_head4(":/parts/head/snake_head4.png");

    QPixmap _snake_tail1(":/parts/tail/snake_tail1.png");
    QPixmap _snake_tail2(":/parts/tail/snake_tail2.png");
    QPixmap _snake_tail3(":/parts/tail/snake_tail3.png");
    QPixmap _snake_tail4(":/parts/tail/snake_tail4.png");

    QPixmap _snake_turn1(":/parts/turn/snake_turn1.png");
    QPixmap _snake_turn2(":/parts/turn/snake_turn2.png");
    QPixmap _snake_turn3(":/parts/turn/snake_turn3.png");
    QPixmap _snake_turn4(":/parts/turn/snake_turn4.png");

   QGridLayout* field = new QGridLayout;
   field->setSpacing(2);

   for(int i = 0; i < size; i++)
   {
       for(int j = 0; j < size; j++)
       {
           QLabel* lbl = new QLabel;
           lbl->setStyleSheet("background-color: #696969");

           if((get_cords().x == i) && (get_cords().y == j))
               setLabel(get_sprite(), lbl, _food1, _food2, _food3, _food4);

           int index = -1;
           for(unsigned int g = 0; g < direction.size(); g++)
               if((get_snake()[g].x == i) && (get_snake()[g].y == j))
                       index = g;

           if(index != -1)
           {
                if(index == 0)
                    setLabel(direction[index], lbl, _snake_head1, _snake_head2, _snake_head3, _snake_head4);
                else if(index == (int)direction.size() - 1)
                    setLabel(direction[index], lbl, _snake_tail1, _snake_tail2, _snake_tail3, _snake_tail4);
                else
                {
                    if((direction[index] == 1) && (direction[index+1] == 2))
                        lbl->setPixmap(_snake_turn3.scaled(win_size/size*resize, win_size/size*resize));
                    else if((direction[index] == 1) && (direction[index+1] == 4))
                        lbl->setPixmap(_snake_turn4.scaled(win_size/size*resize, win_size/size*resize));
                    else if((direction[index] == 2) && (direction[index+1] == 1))
                        lbl->setPixmap(_snake_turn1.scaled(win_size/size*resize, win_size/size*resize));
                    else if((direction[index] == 2) && (direction[index+1] == 3))
                        lbl->setPixmap(_snake_turn4.scaled(win_size/size*resize, win_size/size*resize));
                    else if((direction[index] == 3) && (direction[index+1] == 2))
                        lbl->setPixmap(_snake_turn2.scaled(win_size/size*resize, win_size/size*resize));
                    else if((direction[index]== 3) && (direction[index+1] == 4))
                        lbl->setPixmap(_snake_turn1.scaled(win_size/size*resize, win_size/size*resize));
                    else if((direction[index] == 4) && (direction[index+1] == 1))
                        lbl->setPixmap(_snake_turn2.scaled(win_size/size*resize, win_size/size*resize));
                    else if((direction[index] == 4) && (direction[index+1] == 3))
                        lbl->setPixmap(_snake_turn3.scaled(win_size/size*resize, win_size/size*resize));
                    else
                        setLabel(direction[index], lbl, _snake_block1, _snake_block2, _snake_block3, _snake_block4);
                }
           }

           field->addWidget(lbl, j, i);
       }
   }

   QFont font("Times", 15, QFont::Bold);
   QLabel* scr = new QLabel("Длина: " + QString::number(get_score()));
   scr->setFixedSize(win_size, 30);
   scr->setFont(font);

   QGridLayout* lay = new QGridLayout;
   lay->addLayout(field, 0, 0);
   lay->addWidget(scr, 1, 0);

   qDeleteAll(findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
   delete this->layout();
   setLayout(lay);
}

bool game::is_end()
{
    if((get_snake()[0].x == -1) || (get_snake()[0].x == size) || (get_snake()[0].y == -1) || (get_snake()[0].y == size))
        return true;
    for(unsigned int i = 1; i < direction.size(); i++)
        if((get_snake()[0].x == get_snake()[i].x) && (get_snake()[0].y == get_snake()[i].y))
            return true;
    return false;
}

void game::update_difficulty()
{
    switch (difficulty)
    {
    case 1 :
        size = 14;
        time = 300;
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
    }
}

void game::setLabel(int index, QLabel *label, QPixmap arg1, QPixmap arg2, QPixmap arg3, QPixmap arg4)
{
    switch(index)
    {
    case 1 :
        label->setPixmap(arg1.scaled(win_size/size*resize, win_size/size*resize));
        break;
    case 2 :
        label->setPixmap(arg2.scaled(win_size/size*resize, win_size/size*resize));
        break;
    case 3 :
        label->setPixmap(arg3.scaled(win_size/size*resize, win_size/size*resize));
        break;
    case 4 :
        label->setPixmap(arg4.scaled(win_size/size*resize, win_size/size*resize));
        break;
    }
}

void game::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_Up :
        queue.push_back(1);
        break;
    case Qt::Key_Right :
        queue.push_back(2);
        break;
    case Qt::Key_Down :
        queue.push_back(3);
        break;
    case Qt::Key_Left :
        queue.push_back(4);
        break;
    case Qt::Key_W :
        queue.push_back(1);
        break;
    case Qt::Key_D :
        queue.push_back(2);
        break;
    case Qt::Key_S :
        queue.push_back(3);
        break;
    case Qt::Key_A :
        queue.push_back(4);
        break;
    case Qt::Key_Return :
        if(on_pause)
        {
            if(name->hasFocus())
                save();
            else
                reload();
        }
        break;
    }
}

game::game(int difficulty, int win_size, int size, int time, float resize, QWidget *parrent) : QWidget(parrent), snake(), food(size, get_snake()), score(), resize(resize)
{
    opposite.insert(make_pair(1,3));
    opposite.insert(make_pair(2,4));
    opposite.insert(make_pair(3,1));
    opposite.insert(make_pair(4,2));

    this->size = size;
    this->time = time;
    this->difficulty = difficulty;
    this->win_size = win_size;

    on_pause = false;

    QIcon ico(":/other/snake.ico");

    setWindowIcon(ico);
    setWindowTitle("Змейка");
    setFixedSize(win_size + (size - 1) * 2, win_size + 50 + (size - 1) * 2);
    setStyleSheet("background-color: #C0C0C0");
    draw();

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(this->time);
}
