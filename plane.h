#ifndef PLANE_H
#define PLANE_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsScene>
#include "character.h"

class plane: public character
{
    Q_OBJECT
public:
    plane();
//    int lifespan;
    void show_picture();
};

#endif // PLANE_H
