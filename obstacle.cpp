#include <obstacle.h>
#include    <iostream>
Obstacle::Obstacle(float x, float y, float w,float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    life=2;
    role="obstacle";
    control=false;//set image

    g_pixmap.setPixmap(pixmap); //set pixmap
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSizeF(w,h);

    // create body
    bodydef.type=b2_dynamicBody;
    bodydef.bullet=true;
    bodydef.position.Set(x,y);  //position
    bodydef.userData=this;
    g_body=world->CreateBody(&bodydef);

    bodyobstacle.SetAsBox(w/2,h/2);

    fixturedef.shape=&bodyobstacle;
    fixturedef.density=obs_d;
    fixturedef.friction=obs_f;
    fixturedef.restitution=obs_r;
    g_body->CreateFixture(&fixturedef);

    connect(timer,SIGNAL(timeout()),this,SLOT(paint()));    // timer
    scene->addItem(&g_pixmap);
}

void Obstacle::setLinearVelocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);
}
