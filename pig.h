#ifndef PIG_H
#define PIG_H
#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define PIG_DENSITY 11.0f
#define PIG_FRICTION 0.2f
#define PIG_RESTITUTION 0.5f

class pig : public GameItem
{
public:
    pig(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
    bool used;          /// to know if the bird was used
    float firstx,firsty;
    int life;
    b2BodyDef bodydef;
    b2CircleShape bodyshape;
    b2FixtureDef fixturedef;
};
#endif // PIG_H
