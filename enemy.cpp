#include "enemy.h"
#include <QTimer>

enemy::enemy()
{
    lifespan=500;
    random_position=1;
    QTimer *timer=new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(50);
    //setPixmap(QPixmap(":/res/ghost.png").scaled(220,300));
}

void enemy::show_picture()
{
    this->setPixmap(QPixmap(":/res/ghost.png").scaled(220,300));
    this->setPos(195,0);
}

void enemy::move()
{
    if(random_position==1)
    {
        if(x()-10>=0)
            setPos(x()-10,y());
        else
        {
            setPos(x()+10,y());
            random_position=0;
        }

    }

    else
    {
        if(x()+this->pixmap().width()+10<=610)
            setPos(x()+10,y());
        else
        {
            setPos(x()-10,y());
            random_position=1;
        }

    }
}
