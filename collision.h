#ifndef MYLISTEN_H
#define MYLISTEN_H
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <iostream>
#include <QPushButton>
#include<QIcon>
#include<Box2D/Collision/b2Collision.h>
#include<Box2D/Dynamics/Contacts/b2Contact.h>
#include<Box2D/Dynamics/b2ContactManager.h>
#include<Box2D/Dynamics/Contacts/b2ContactSolver.h>
#include<gameitem.h>
#include<bird.h>
#include<obstacle.h>
#include<pig.h>

 class mylisten:public b2ContactListener
{
public:
     void BeginContact(b2Contact*contact); //detect collision
};

#endif // MYLISTEN_H
