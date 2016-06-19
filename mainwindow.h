#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include<QLabel>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>
#include <QPushButton>
#include<QIcon>
#include<Box2D/Collision/b2Collision.h>
#include<Box2D/Dynamics/Contacts/b2Contact.h>
#include<Box2D/Dynamics/b2ContactManager.h>
#include<Box2D/Dynamics/Contacts/b2ContactSolver.h>

#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include<pig.h>
#include<yellowbird.h>
#include<blackbird.h>
#include<bluebird.h>
#include<obstacle.h>
#include<collision.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
    void basicgame();
    void freebasicgame();
    int yourscore;
    QLabel *Score;
signals:
    // Signal
   void quitGame();

private slots:
    void tick();
    // For debug slot
    void QUITSLOT();
    void checkgame();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;
    QGraphicsPixmapItem *gamebk;
    QGraphicsPixmapItem *gamearrow;
     QGraphicsPixmapItem *wingame;
    Bird *allbird[9];
    Land* bound[4];
    Obstacle*barrier[6];
    pig*allpig[2];
    double x,pressx;       //// mouse x -axis
    double y,pressy;       //// mouse y -axis
    double r;     ///// bound r
    int whichbird;      //// to choose which bird in my control
    bool ongame;      ////to judge if the game is onplay
    QPushButton* restart;
    QPushButton* quit;
    mylisten mlisten;
    bool win;
};

#endif // MAINWINDOW_H
