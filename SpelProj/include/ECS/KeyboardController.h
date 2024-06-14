#ifndef __KEYBOARDCONTROLLER_H__
#define __KEYBOARDCONTROLLER_H__

#include "EntityComponentSystem.h"
#include "../GameLoop.h"
#include "Components.h"

// Player controller
class KeyboardController : public Component
{
private:
    Transform *pTransform;

public:
    void start() override
    {
        pTransform = &pEntity->getComponent<Transform>();
    }

    void update() override
    {
        // player presses key
        if (GameLoop::event.type == SDL_KEYDOWN)
        {
            if (GameLoop::event.key.keysym.sym == SDLK_w)
            {
                pTransform->velocity.y = -1;
            }

            if (GameLoop::event.key.keysym.sym == SDLK_s)
            {
                pTransform->velocity.y = 1;
            }

            if (GameLoop::event.key.keysym.sym == SDLK_a)
            {
                pTransform->velocity.x = -1;
            }

            if (GameLoop::event.key.keysym.sym == SDLK_d)
            {
                pTransform->velocity.x = 1;
            }
        }
        else if (GameLoop::event.type == SDL_KEYUP)
        {
            //player releases key
            if (GameLoop::event.type == SDL_KEYUP)
            {
                if (GameLoop::event.key.keysym.sym == SDLK_w)
                {
                    pTransform->velocity.y = 0;
                }
                else if (GameLoop::event.key.keysym.sym == SDLK_s)
                {
                    pTransform->velocity.y = 0;
                }
                else if (GameLoop::event.key.keysym.sym == SDLK_a)
                {
                    pTransform->velocity.x = 0;
                }
                else if (GameLoop::event.key.keysym.sym == SDLK_d)
                {
                    pTransform->velocity.x = 0;
                }
            }
        }
    }
};

#endif // __KEYBOARDCONTROLLER_H__