#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsView>
#include "bullet.h"
#include "enemy.h"
#include "plane.h"
#include "character.h"
#include "fireball.h"
#include "bomb.h"
#include <QKeyEvent>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QLabel *score, *health, *Skill, *hp_bar, *result, *hint;

public slots:
    virtual void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    void autofire();
    void move_up();
    void move_left();
    void move_down();
    void move_right();
    void set_score();
    void set_health();
    void set_skill();
    void set_hp();
    void set_result();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    character *player, *ghost;
//    plane *player;
//    enemy *ghost;
    QTimer *timer, *fire, *firetimer, *movetime;
    QGraphicsView *view;
    int skills;
    int move_w;
    int move_a;
    int move_s;
    int move_d;
};

#endif // MAINWINDOW_H














