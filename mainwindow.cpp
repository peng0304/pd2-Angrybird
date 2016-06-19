#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    r=5;                                                        // inital the value
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    // Create world
    b2Vec2 gravity(0.0f,-9.8);
    world = new b2World(gravity);
    GameItem::setGlobalSize(QSizeF(32,18),size());
    // Create bound (You can edit here)
    bound[0]=new Land(16,1,32,3,QPixmap(":/ground.png").scaled(width(),height()/6.0),world,scene);                      //buttom bound
    bound[1]=new Land(16,19.5,32,3,QPixmap(":/ground.png").scaled(width(),height()/6.0),world,scene);                      //upper bound
    bound[2]=new Land(-0.5,10,1,18,QPixmap(":/26_158.png").scaled(width()/32*1,height()/18*18),world,scene);  //left bound
    bound[3]=new Land(32,10,1,18,QPixmap(":/26_158.png").scaled(width()/32*1,height()/18*18),world,scene);  //right bound

    QPixmap background;
     background.load(":/ground2.jpg");
     background=background.scaled(754*1.4,628*1.4);
     gamebk=new  QGraphicsPixmapItem;
     gamebk->setPixmap(background);
     gamebk->setPos(-50,-280);
     scene->addItem(gamebk);

     restart=new QPushButton(this);
     restart->setGeometry(0,0,100,100);
     restart->setObjectName("restart");
     restart->setStyleSheet("#restart{border-image: url(:/restart.png)}");
     restart->show();

     quit=new QPushButton(this);
     quit->setGeometry(100,13,75,75);
     quit->setObjectName("quit");
     quit->setStyleSheet("#quit{border-image: url(:/quit.png)}");
     quit->show();

     QPixmap arrow;
     arrow.load(":/arrow.png");
      arrow=arrow.scaled(180,180);
      gamearrow=new  QGraphicsPixmapItem;
      gamearrow->setPixmap(arrow);
      gamearrow->setPos(110,280);
      scene->addItem(gamearrow);    // create basic world bird ,obstacle,pig
    basicgame();

    Score=new QLabel(this);
    yourscore=0;
    QString score="Score:";
    score=score+QString::number(yourscore);
    Score->setText(score);
    Score->setFont(QFont("Time",25,QFont::Bold));
    Score->setGeometry(780,10,150,100);
    Score->show();

    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(&timer,SIGNAL(timeout()),this,SLOT( checkgame()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));

    timer.start(100/6);
       world->SetContactListener(&mlisten);
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{

    // Hint: Notice the Number of every event!
    QMouseEvent *mouseplace=static_cast<QMouseEvent*>(event);
    QPointF place=mouseplace->pos();
    QString str;
    QMouseEvent *m=static_cast<QMouseEvent*>(event);    //press

    if(event->type() == QEvent::MouseButtonPress&&ongame==true)
    {
            if( (x>=3.7&&x<=5.4 ) &&(y>=15.5&&y<=17.0)    )
            {
               close();
               return true;
            }
            if(  (x>=1.0&&x<=2.5) && (y>=15.6&&y<=16.8)   )
            {
                freebasicgame();
                basicgame();
                yourscore=0;
                QString score="Score:";
                score=score+QString::number(yourscore);
                Score->setText(score);
                Score->setFont(QFont("Time",25,QFont::Bold));
                Score->setGeometry(780,10,150,100);
                Score->show();
                return true;
            }
             if(allbird[whichbird]->used==true&&m->button()==Qt::RightButton&&whichbird<3){                                                                                                       ///// if bird was used and x-axis not change
                   b2Vec2 a=allbird[whichbird]->g_body->GetLinearVelocity();
                   if(a.x<0.1&&a.y<0.1){
                        whichbird++;
                        if(whichbird==1){
                            allbird[whichbird]=new yellowbird(6.7f,8.0f,1,&timer,QPixmap(":/yellowbird2.png").scaled(width()/32*2,height()/18*2),world,scene);    //yellow bird
                        }
                        if(whichbird==2){
                            allbird[2] = new blackbird(6.7f,8.0f,1,&timer,QPixmap(":/blackbird.png").scaled(width()/32*2,height()/18*2),world,scene);    //black bird
                        }
                        if(whichbird==3){
                            allbird[3]=new greenbird(6.7f,8.0f,1,&timer,QPixmap(":/greenbird.png").scaled(width()/32*2,height()/18*2),world,scene);     //blue bird
                        }
                    }
                    return true;
             }
            if(allbird[whichbird]->used==true&&m->button()==Qt::LeftButton&&allbird[whichbird]->ability_use>0)    // click left mouse if bird is used you can use ability
            {
                    allbird[whichbird]->ability();
                    allbird[whichbird]->ability_use--;
                    return true;
            }
        // TODO : add your code here
                if(allbird[whichbird]->control==false&&r<0.5&&allbird[whichbird]->used==false&&m->button()==Qt::LeftButton){
                allbird[whichbird]->control=true;
                pressx=(place.x()*32)/960;
                pressy=(place.y()/540-1)*18*-1;
                allbird[whichbird]->used=true;
                return true;
                }
          return true;
    }
    if(event->type() == QEvent::MouseMove&&ongame==true)
    {
        // TODO : add your code here

        x=(place.x()*32)/960;           // mouse place
        y=(place.y()/540-1)*18*-1;  //  mouse place
        r=sqrt(   (x-allbird[whichbird]->firstx)*(x-allbird[whichbird]->firstx)+(y-allbird[whichbird]->firsty)*(y-allbird[whichbird]->firsty)   );

        if(allbird[whichbird]->control==true&&allbird[whichbird]->used==true){
        double bird_x=allbird[whichbird]->g_body->GetPosition().x;
        double bird_y=allbird[whichbird]->g_body->GetPosition().y;
        double x_diff=x-bird_x;
        double y_diff=y-bird_y;
        double boundx= (bird_x+x_diff-pressx);
        double  boundy=(bird_y+y_diff-pressy);
        double bound=sqrt(  boundx*boundx+boundy*boundy     );
                 if(bound<=5){
                    b2Vec2 sp(bird_x+x_diff ,bird_y+y_diff  );
                    allbird[whichbird]->g_body->SetTransform(sp,0);
                    return true;
                  }
            }
       return true;
    }

    if(event->type() == QEvent::MouseButtonRelease&&ongame==true)       //release
    {
        // TODO : add your code here
            if(allbird[whichbird]->control==true){
            allbird[whichbird]->g_body->SetActive(true);
            double x_diff=x-pressx;
            double y_diff=y-pressy;
            allbird[whichbird]->setLinearVelocity(b2Vec2(5*x_diff*-1,5*y_diff*-1));
            allbird[whichbird]->control=false;
            return true;
            }
        return true;
    }
        return false;
}


void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::QUITSLOT()
{
    // For debug
   cout << "Quit Game Signal receive !" << std::endl ;
}


void MainWindow::checkgame()
{
    if(yourscore>200){
        if(win==true){
            return;
        }
        win=true;
        QPixmap youwin;
         youwin.load(":/win.png");
         youwin=youwin.scaled(200.0,200.0);
         wingame=new  QGraphicsPixmapItem;
         wingame->setPixmap(youwin);
         wingame->setPos(100,100);
         scene->addItem(wingame);
        return;
    }
    ongame=false;
    for(int i=0;i<6;i++)
    {
        if(barrier[i]!=NULL)
        {
            if(barrier[i]->life==0)
            {
            delete barrier[i];
            barrier[i]=new Obstacle(1900.0f,5000.5f,1.5,5,&timer,QPixmap(":/26_158.png").scaled(width()/32*1.5,height()/18*5),world,scene);
            yourscore=yourscore+20;
            QString score="Score:";
            score=score+QString::number(yourscore);
            Score->setText(score);
            Score->setFont(QFont("Time",25,QFont::Bold));
            Score->setGeometry(780,10,150,100);
            Score->show();
            }
        }
    }

    for(int i=0;i<2;i++)
    {
        if(allpig[i]!=NULL)
        {
            if(allpig[i]->life==0)
            {
            delete allpig[i];
            allpig[i]=new pig(1900.0f,5000.5f,1.5,&timer,QPixmap(":/26_158.png").scaled(width()/32*1.5,height()/18*5),world,scene);
            yourscore=yourscore+100;
            QString score="Score:";
            score=score+QString::number(yourscore);
            Score->setText(score);
            Score->setFont(QFont("Time",25,QFont::Bold));
            Score->setGeometry(780,10,150,100);
            Score->show();
            }
        }
    }
    ongame=true;
}



void MainWindow::basicgame()                // create basic item
{
    // Create bird (You can edit here)
    whichbird=0;                                        //  choose use which bird
    win=false;
    allbird[0] = new Bird(6.7f,8.0f,1,&timer,QPixmap(":/bird.png").scaled(width()/32*2,height()/18*2),world,scene); //red bird

    allpig[0]=new pig(23.0f,10.0f,1,&timer,QPixmap(":/pig.png").scaled(width()/32*2,height()/18*2),world,scene);    //create pig
    allpig[0]->g_body->SetActive(true);
    allpig[1]=new pig(23.0f,5.0f,1.5,&timer,QPixmap(":/pig.png").scaled(width()/32*3,height()/18*3),world,scene);
    allpig[1]->g_body->SetActive(true);

    barrier[0]=new Obstacle(19.0f,5.5f,1.5,5,&timer,QPixmap(":/26_158.png").scaled(width()/32,height()/18*5),world,scene);  //obstacle
    barrier[1]=new Obstacle(27.0f,5.5f,1.5,5,&timer,QPixmap(":/26_158.png").scaled(width()/32,height()/18*5),world,scene);
    barrier[2]=new Obstacle(23.0f,8.8f,9.5,1,&timer,QPixmap(":/304_31.png").scaled(width()/32*9.5,height()/18*1),world,scene);

    barrier[3]=new Obstacle(20.0f,10.1f,1,3,&timer,QPixmap(":/26_158.png").scaled(width()/32,height()/18*3),world,scene);
    barrier[4]=new Obstacle(26.0f,10.1f,1,3,&timer,QPixmap(":/26_158.png").scaled(width()/32,height()/18*3),world,scene);
    barrier[5]=new Obstacle(23.0f,13.0f,9.5,1,&timer,QPixmap(":/304_31.png").scaled(width()/32*9.5,height()/18*1),world,scene);
    ongame=true;
}
void MainWindow::freebasicgame()        // delete item
{
    for(int i=0;i<whichbird+1;++i)
    {
        delete allbird[i];
    }

    for(int i=0;i<2;++i)
    {
        delete allpig[i];
    }

    for(int i=0;i<6;++i)
    {
        if(barrier[i]!=NULL)
        {
        delete barrier[i];
        }
    }
    if(win==true){
        delete wingame;
    }
    ongame=false;
}
