#include "fireball.h"
#include "plane.h"
#include <QDebug>

fireball::fireball()
{

}

void fireball::leftfly()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0,n=colliding_items.size();i<n;i++)
        if(typeid(*(colliding_items[i]))==typeid(plane))
        {
            plane *player = static_cast<plane *> (colliding_items[i]);
            player->lifespan--;
            qDebug()<<player->lifespan;
            if(player->lifespan<=0)
            {
                scene()->removeItem(colliding_items[i]);
                //delete colliding_items[i];
            }

            scene()->removeItem(this);
            delete this;
            return;
        }

    this->setPos(x() - 3, y() + 3);
    if(y() > 801 || x() < 0) {
        this->scene()->removeItem(this);
        delete this;
    }
}

void fireball::midfly()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0,n=colliding_items.size();i<n;i++)
        if(typeid(*(colliding_items[i]))==typeid(plane))
        {
            plane *player = static_cast<plane *> (colliding_items[i]);
            player->lifespan--;
            qDebug()<<player->lifespan;
            if(player->lifespan<=0)
            {
                scene()->removeItem(colliding_items[i]);
                //delete colliding_items[i];
            }

            scene()->removeItem(this);
            delete this;
            return;
        }

    this->setPos(x(), y() + 3);
    if(y() > 801) {
        this->scene()->removeItem(this);
        delete this;
    }
}

void fireball::rightfly()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0,n=colliding_items.size();i<n;i++)
        if(typeid(*(colliding_items[i]))==typeid(plane))
        {
            plane *player = static_cast<plane *> (colliding_items[i]);
            player->lifespan--;
            qDebug()<<player->lifespan;
            if(player->lifespan<=0)
            {
                scene()->removeItem(colliding_items[i]);
                //delete colliding_items[i];
            }

            scene()->removeItem(this);
            delete this;
            return;
        }

    this->setPos(x() + 3, y() + 3);
    if(y() > 801|| x() > 620) {
        this->scene()->removeItem(this);
        delete this;
    }
}


