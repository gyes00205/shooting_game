#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsScene>
#include "character.h"

class enemy:public character
{
    Q_OBJECT
public:
    enemy();
//    int lifespan;
    int random_position;
    void show_picture();
public slots:
    void move();
};

#endif // ENEMY_H
