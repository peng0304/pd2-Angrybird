#include <bluebird.h>
#include<iostream>
greenbird::greenbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):Bird(x,y,radius,timer,pixmap,world,scene)
{
    time=timer;
    image=pixmap;
    w=world;
    s=scene;
}
greenbird::~greenbird(){
    if(ability_use==0)
    {
        for(int i=0;i<3;i++)
        {
            delete divide[i];
        }
    }
}

void greenbird::ability()
{
    b2Vec2 a=g_body->GetLinearVelocity();
    float x=g_body->GetPosition().x;
    float y=g_body->GetPosition().y;
    divide[0]=new greenbird(x+1,y+1,0.5,time,QPixmap(":/greenbird.png").scaled(30*1,30*1),w,s);               //blue bird
    divide[0]->g_body->SetActive(true);
    divide[0]->setLinearVelocity(b2Vec2(a.x*4,a.y*2));

    divide[1]=new greenbird(x+1,y,0.5,time,QPixmap(":/greenbird.png").scaled(30*1,30*1),w,s);               //blue bird
    divide[1]->g_body->SetActive(true);
    divide[1]->setLinearVelocity(b2Vec2(a.x*4,a.y));

    divide[2]=new greenbird(x+1,y-1,0.5,time,QPixmap(":/greenbird.png").scaled(30*1,30*1),w,s);               //blue bird
    divide[2]->g_body->SetActive(true);
    divide[2]->setLinearVelocity(b2Vec2(a.x*2,a.y*4));
}

