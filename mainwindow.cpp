#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(0, 0, 610, 790)),
    timer(new QTimer)
{

    move_a=0,move_d=0,move_s=0,move_w=0,skills=3;
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    hint = new QLabel(this);
    hint->setGeometry(620,340,300,300);
    hint->setText("WASD移動鍵\n空白鍵發射大砲");
    hint->setStyleSheet("font-size:40px;");

    //player->setPixmap(QPixmap(":/res/cartoon-plane.png").scaled(50,50));

    ghost = new enemy;
    player = new plane;
    ghost->show_picture();
    player->show_picture();
    //ghost->setPixmap(QPixmap(":/res/ghost.png").scaled(220,300));

    scene->addItem(player);
    scene->addItem(ghost);
    //ghost->setPos(195,0);
    //player->setPos(260, 600);

    hp_bar = new QLabel(this);
    hp_bar->setGeometry(0,0,620,10);
    hp_bar->setStyleSheet("background-color:red;");
    connect(timer,SIGNAL(timeout()),this,SLOT(set_hp()));

    score = new QLabel(this);
    score->setText("Score: ");
    score->setGeometry(620,10,200,100);
    score->setStyleSheet("font-size:40px;");
    connect(timer,SIGNAL(timeout()),this,SLOT(set_score()));

    health = new QLabel(this);
    health->setText("Health: ");
    health->setGeometry(620,120,200,100);
    health->setStyleSheet("font-size:40px;");
    connect(timer,SIGNAL(timeout()),this,SLOT(set_health()));

    Skill = new QLabel(this);
    Skill->setText("Skill: ");
    Skill->setGeometry(620,230,200,100);
    Skill->setStyleSheet("font-size:40px;");
    connect(timer,SIGNAL(timeout()),this,SLOT(set_skill()));

    timer->start(5);
    fire = new QTimer;
    firetimer = new QTimer;
    movetime = new QTimer;
    if(player->lifespan>0)
    {
        connect(movetime,SIGNAL(timeout()),this,SLOT(move_down()));
        connect(movetime,SIGNAL(timeout()),this,SLOT(move_right()));
        connect(movetime,SIGNAL(timeout()),this,SLOT(move_left()));
        connect(movetime,SIGNAL(timeout()),this,SLOT(move_up()));
    }
    if(ghost->lifespan>0)
    {
        connect(fire,SIGNAL(timeout()),this,SLOT(autofire()));
    }

    fire->start(600);
    firetimer->start(30);
    movetime->start(50);

    result = new QLabel(this);
    result->setGeometry(0,290,620,200);

    connect(timer,SIGNAL(timeout()),this,SLOT(set_result()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(player->lifespan>0)
    {
        switch(e->key()) {

        case Qt::Key_Up:
        case Qt::Key_W:
            move_w=1;
//            if(player->y()>=0)
//                player->setPos(player->x(), player->y() - 10);
            break;
        case Qt::Key_Down:
        case Qt::Key_S:
            move_s=1;
//            if(player->y()<=671)
//                player->setPos(player->x(), player->y() + 10);
            break;
        case Qt::Key_Left:
        case Qt::Key_A:
            move_a=1;
//            if(player->x()>=0)
//                player->setPos(player->x() - 10, player->y());
            break;
        case Qt::Key_Right:
        case Qt::Key_D:
            move_d=1;
//            if(player->x()<=510)
//                player->setPos(player->x() + 10, player->y());
            break;
        case Qt::Key_Space:
            if(skills>0)
            {
                QTimer *bombtimer = new QTimer;
                skills--;
                bomb *d = new bomb;
                d->setPixmap(QPixmap(":/res/bomb.png").scaled(25, 50));
                d->setPos(player->x() + player->pixmap().width() / 2 - d->pixmap().width() / 2, player->y() - d->pixmap().height());
                d->connect(bombtimer,SIGNAL(timeout()),d,SLOT(bombfly()));
                scene->addItem(static_cast<QGraphicsPixmapItem*>(d));
                bombtimer->start(5);
            }


            break;
        }
    }

}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    if(player->lifespan>0)
    {
        switch (e->key()) {
        case Qt::Key_W:
            move_w=0;
            break;
        case Qt::Key_A:
            move_a=0;
            break;
        case Qt::Key_S:
            move_s=0;
            break;
        case Qt::Key_D:
            move_d=0;
            break;
        }
    }

}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(player->lifespan>0)
    {
        bullet *b = new bullet;
        bullet *a = new bullet;
        bullet *c = new bullet;


        b->setPixmap(QPixmap(":/res/bullets1.png").scaled(5, 20));
        a->setPixmap(QPixmap(":/res/bullets1.png").scaled(5, 20));
        c->setPixmap(QPixmap(":/res/bullets1.png").scaled(5, 20));

        b->setPos(player->x() + player->pixmap().width() / 2 - b->pixmap().width() / 2, player->y() - b->pixmap().height());
        b->connect(timer, SIGNAL(timeout()), b, SLOT(fly()));
        a->setPos(player->x() + player->pixmap().width() / 2 - a->pixmap().width() / 2 - 15, player->y() - a->pixmap().height()+12.5);
        a->connect(timer, SIGNAL(timeout()), a, SLOT(fly()));
        c->setPos(player->x() + player->pixmap().width() / 2 - c->pixmap().width() / 2 + 15, player->y() - c->pixmap().height()+12.5);
        c->connect(timer, SIGNAL(timeout()), c, SLOT(fly()));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(b));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(a));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(c));
    }

}

void MainWindow::autofire()
{
    fireball *left = new fireball;
    fireball *mid = new fireball;
    fireball *right = new fireball;
    if(ghost->lifespan>0)
    {

        left->setPixmap(QPixmap(":/res/fireball.png").scaled(40,40));
        mid->setPixmap(QPixmap(":/res/fireball.png").scaled(40,40));
        right->setPixmap(QPixmap(":/res/fireball.png").scaled(40,40));



        mid->setPos(ghost->x() + ghost->pixmap().width() / 2 - mid->pixmap().width() / 2, ghost->y()+ghost->pixmap().height());


        left->setPos(ghost->x() + ghost->pixmap().width() / 2 - left->pixmap().width() / 2 - 30, ghost->y()+ghost->pixmap().height());


        right->setPos(ghost->x() + ghost->pixmap().width() / 2 - right->pixmap().width() / 2 + 30, ghost->y()+ghost->pixmap().height());

        mid->connect(firetimer, SIGNAL(timeout()), mid, SLOT(midfly()));
        left->connect(firetimer, SIGNAL(timeout()), left, SLOT(leftfly()));
        right->connect(firetimer, SIGNAL(timeout()), right, SLOT(rightfly()));


        scene->addItem(static_cast<QGraphicsPixmapItem*>(mid));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(left));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(right));
    }


}

void MainWindow::move_up()
{
    if(player->y()>=0&&move_w==1)
        player->setPos(player->x(), player->y() - 10);
}

void MainWindow::move_left()
{
    if(player->x()>=0&&move_a==1)
        player->setPos(player->x() - 10, player->y());
}

void MainWindow::move_down()
{
    if(player->y()<=721&&move_s==1)
        player->setPos(player->x(), player->y() + 10);
}

void MainWindow::move_right()
{
    if(player->x()<=560&&move_d==1)
        player->setPos(player->x() + 10, player->y());
}

void MainWindow::set_score()
{
    score->setText("Score: "+QString::number(500-ghost->lifespan-50*(10-player->lifespan)));
}

void MainWindow::set_health()
{
    health->setText("Health: "+QString::number(player->lifespan));
}

void MainWindow::set_skill()
{
    Skill->setText("Skill: "+QString::number(skills));
}

void MainWindow::set_hp()
{
    hp_bar->setGeometry(0,0,((float)ghost->lifespan/(float)500)*620,10);
    hp_bar->setStyleSheet("background-color:red;");
}

void MainWindow::set_result()
{
    if(ghost->lifespan==0)
    {
        //qDebug()<<"Win";
        result->setText("You Win");
        result->setStyleSheet("color:green;font-size:60px");
        result->setAlignment(Qt::AlignCenter);
        timer->stop();
        fire->stop();
        firetimer->stop();
        movetime->stop();
    }
    if(player->lifespan==0)
    {
        //qDebug()<<"Lose";
        result->setText("You Lose");
        result->setStyleSheet("color:red;font-size:60px");
        result->setAlignment(Qt::AlignCenter);
        timer->stop();
        fire->stop();
        firetimer->stop();
        movetime->stop();
    }
}
