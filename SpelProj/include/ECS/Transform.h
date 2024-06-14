#ifndef __Transform_H__
#define __Transform_H__

#include "Components.h"
#include "GameSettings.h"
#include "../Vector2D.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

class Collider;

class Transform : public Component
{
private:
    int height = 32;
    int width = 32;
    int scale = 1;
    float speed = 4;

public:
    // objects are supposed to be public to allow easy access and avoid badly complex get/sets
    Vector2D position;
    Vector2D velocity;

    // default
    Transform()
    {
        position.zero();
    }

    Transform(int pScale)
    {
        position.x = 0.0f;
        position.y = 0.0f;
        scale = pScale;
    }

    Transform(float newX, float newY, int h, int w, int s)
    {
        position.x = newX;
        position.y = newY;
        height = h;
        width = w;
        scale = s;
    }

    Transform(float newX, float newY, int h, int w, int s, float sp)
    {
        position.x = newX;
        position.y = newY;
        height = h;
        width = w;
        scale = s;
        speed = sp;
    }

    // handle movement
    void update() override
    {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }

    // velocity set to zero at game start
    void start() override
    {
        velocity.zero();
    }

    // px, py = parameter x, y
    void setPosition(int px, int py)
    {
        // std::cout << "Transform of " << this->entity << "set to x :" << px << " y : " << py << std::endl;
        position.x = px;
        position.y = py;
    }

    int getHeight()
    {
        return height;
    }
    int getWidth()
    {
        return width;
    }
    int getScale()
    {
        return scale;
    }
    int getSpeed()
    {
        return speed;
    }
};

#endif // __Transform_H__