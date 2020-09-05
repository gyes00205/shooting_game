#ifndef BOMB_H
#define BOMB_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>

class bomb : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    bomb();

public slots:
    void bombfly();
};

#endif // BOMB_H
