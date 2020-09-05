#include "bomb.h"
#include <QDebug>
#include "enemy.h"
bomb::bomb()
{

}

void bomb::bombfly()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0,n=colliding_items.size();i<n;i++)
        if(typeid(*(colliding_items[i]))==typeid(enemy))
        {
            enemy *ghost = static_cast<enemy *> (colliding_items[i]);
            if(ghost->lifespan)
                ghost->lifespan-=50;
            else
                ghost->lifespan=0;
            qDebug()<<ghost->lifespan;
            if(ghost->lifespan<=0)
            {
                scene()->removeItem(colliding_items[i]);
                //delete colliding_items[i];
            }

            scene()->removeItem(this);
            delete this;
            return;
        }

    this->setPos(x(), y() - 3);
    if(y()+this->pixmap().height() < 0) {
        this->scene()->removeItem(this);
        delete this;
    }
}
