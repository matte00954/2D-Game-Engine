#include "../TextureHandler.h"
#include <SDL2/SDL.h>
#include "Components.h"

class Sprite : public Component
{
private:
    Transform *pTransform;
    SDL_Texture *pTexture;
    SDL_Rect sourceRect, destinationRect;

public:
    Sprite() = default;
    Sprite(const char *path)
    {
        // file path
        setTexture(path);
    }

    ~Sprite()
    {
        SDL_DestroyTexture(pTexture);
    }

    // change texture of sprite
    void setTexture(const char *path)
    {
        // file path
        pTexture = TextureHandler::LoadTexture(path);
    }

    void start() override
    {
        // ref of entity, get the transform component
        pTransform = &pEntity->getComponent<Transform>();

        sourceRect.x = sourceRect.y = 0;

        sourceRect.w = pTransform->getWidth();
        sourceRect.h = pTransform->getHeight();

        // texture is scaled by 2
        destinationRect.w = destinationRect.h = 64;
    }

    void update() override
    {
        destinationRect.x = static_cast<int>(pTransform->position.x);
        destinationRect.y = static_cast<int>(pTransform->position.y);

        destinationRect.w = pTransform->getWidth() * pTransform->getScale();
        destinationRect.h = pTransform->getHeight() * pTransform->getScale();
    }

    void draw() override
    {
        TextureHandler::Draw(pTexture, sourceRect, destinationRect);
    }
};