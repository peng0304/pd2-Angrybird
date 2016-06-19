#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define obs_d 20.0f
#define obs_f 0.9f
#define obs_r 0.6f

class Obstacle:public GameItem
{
    public:
        Obstacle(float x, float y, float w,float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
        void setLinearVelocity(b2Vec2 velocity);
        int life;
        b2CircleShape bodyshape;
        b2PolygonShape bodyobstacle;
        b2FixtureDef fixturedef;
        b2BodyDef bodydef;
};

#endif // OBSTACLE_H
