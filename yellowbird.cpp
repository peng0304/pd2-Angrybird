#include <yellowbird.h>
#include<iostream>
yellowbird::yellowbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):Bird(x,y,radius,timer,pixmap,world,scene)
{

}
void yellowbird::ability()
{
    b2Vec2 a=g_body->GetLinearVelocity();
   g_body->SetLinearVelocity(b2Vec2(a.x*6,a.y*6));
}
