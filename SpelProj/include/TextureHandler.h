#ifndef __TEXTUREHANDLER_H__
#define __TEXTUREHANDLER_H__

#include "GameLoop.h"

// static class for loading textures
class TextureHandler
{
public:
    static SDL_Texture *LoadTexture(const char *fileName);
    static void Draw(SDL_Texture *texture, SDL_Rect source, SDL_Rect destination);
};

#endif // __TEXTUREHANDLER_H__