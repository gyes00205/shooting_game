#include "plane.h"

plane::plane()
{
    lifespan=10;
}

void plane::show_picture()
{
    this->setPixmap(QPixmap(":/res/cartoon-plane.png").scaled(50,50));
    this->setPos(260,700);
}
