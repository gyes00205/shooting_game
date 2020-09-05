#include "bullet.h"
#include <QDebug>
#include "enemy.h"
bullet::bullet()
{

}

void bullet::fly()
{

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0,n=colliding_items.size();i<n;i++)
        if(typeid(*(colliding_items[i]))==typeid(enemy))
        {
            enemy *ghost = static_cast<enemy *> (colliding_items[i]);
            ghost->lifespan--;
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
