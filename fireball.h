#ifndef FIREBALL_H
#define FIREBALL_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>

class fireball:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    fireball();

public slots:
    void leftfly();
    void midfly();
    void rightfly();
};

#endif // FIREBALL_H
