#ifndef GREENBIRD_H
#define GREENBIRD_H
#include <bird.h>

class greenbird:public Bird
{
public:
    greenbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    ~greenbird();
    void ability();
private:
    QTimer  *time;
    QPixmap image;
    b2World* w;
    QGraphicsScene* s;
    Bird* divide[3];
};

#endif // GREENBIRD_H
