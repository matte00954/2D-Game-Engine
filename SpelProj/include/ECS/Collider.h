#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "../TextureHandler.h"
#include <SDL2/SDL.h>
#include "Components.h"

#include <string>
#include <algorithm>
#include <cctype>

class Transform;

class Collider : public Component
{
private:
    int listPosition;
    bool isColliding = false;
    SDL_Rect rectangles;
    std::string tag;
    Vector2D lastViablePos;

public:
    Transform *pTransform;
    // collider dimensions
    // to identify what type of collider it is such as wall, enemy etc
    // will be compared during collision detection

    Collider(std::string s)
    {
        std::string data = s;
        std::transform(data.begin(), data.end(), data.begin(), [](unsigned char c)
                       { return std::tolower(c); });
        tag = s;
    }

    void start() override
    {
        if (!pEntity->hasComponent<Transform>())
        {
            pEntity->addComponent<Transform>();
        }
        pTransform = &pEntity->getComponent<Transform>();

        GameLoop::pAllColliders.push_back(this);
        listPosition = GameLoop::pAllColliders.size();
    }

    void update() override
    {
        rectangles.x = static_cast<int>(pTransform->position.x);
        rectangles.y = static_cast<int>(pTransform->position.y);

        rectangles.w = pTransform->getWidth() * pTransform->getScale();
        rectangles.h = pTransform->getHeight() * pTransform->getScale();
    }

    int getListPosition()
    {
        return listPosition;
    }

    SDL_Rect getRectangles()
    {
        return rectangles;
    }

    bool insideScreenCheck()
    {
        if (rectangles.x < 0)
        {
            //std::cout << "Rectangle is colliding with border! x < 0 " << std::endl;
            return true;
        }
        else if (rectangles.x > GameSettings::WINDOW_WIDTH - 64)
        {
            //std::cout << "Rectangle is colliding with border! x > window width " << std::endl;
            return true;
        }
        else if (rectangles.y < 0)
        {
            //std::cout << "Rectangle is colliding with border! y < 0 " << std::endl;
            return true;
        }
        else if (rectangles.y > GameSettings::WINDOW_HEIGHT - 64)
        {
            //std::cout << "Rectangle is colliding with border! y > window width " << std::endl;
            return true;
        }
        return false;
    }

    std::string getTag()
    {
        return tag;
    }

    bool AABB(SDL_Rect b)
    {
        SDL_Rect a = this->rectangles;
        int leftA, leftB, rightA, rightB, topA, topB, bottomA, bottomB;

        leftA = a.x;
        rightA = a.x + a.w;
        topA = a.y;
        bottomA = a.y + a.h;

        leftB = b.x;
        rightB = b.x + b.w;
        topB = b.y;
        bottomB = b.y + b.h;

        if (bottomA <= topB)
        {
            return false;
        }
        if (topA >= bottomB)
        {
            return false;
        }
        if (rightA <= leftB)
        {
            return false;
        }
        if (leftA >= rightB)
        {
            return false;
        }
        // none of the sides of A are outside B
        return true;
    }
};

#endif // __COLLIDER_H__