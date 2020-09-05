#ifndef CHARACTER_H
#define CHARACTER_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsScene>

class character:public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    character();
    virtual void show_picture()=0;
    int lifespan;
};

#endif // CHARACTER_H
