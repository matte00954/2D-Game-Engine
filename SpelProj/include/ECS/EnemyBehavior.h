#ifndef __ENEMYBEHAVIOR_H__
#define __ENEMYBEHAVIOR_H__

#include "Components.h"
#include <iostream>

class EnemyBehavior : public Component
{
private:
    int pointA;
    int pointB;

    float xVelocity;
    float yVelocity;

    Transform* transform;

public:
    EnemyBehavior(int a, int b, int xVel, int yVel)
    {
        pointA = a;
        pointB = b;
        xVelocity = xVel;
        yVelocity = yVel;
    }

    void start() override
    {
        transform = &pEntity->getComponent<Transform>();
        transform->velocity.x = -xVelocity;
    }

    void update() override
    {
        if (transform->position.x >= pointA)
        {
            transform->velocity.x = -xVelocity;
        }
        else if (transform->position.x <= pointB)
        {
            transform->velocity.x = xVelocity;
        }
    }
};

#endif // __ENEMYBEHAVIOR_H__