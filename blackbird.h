#ifndef BLACKBIRD_H
#define BLACKBIRD_H
#include <bird.h>

class blackbird:public Bird
{
public:
    blackbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void ability();
};

#endif // BLACKBIRD_H
