#include "TextureHandler.h"

//Get texture from a file path, create SDL objects to show on screen, then return SDL texture
SDL_Texture* TextureHandler::LoadTexture(const char* textureFileName)
{
    SDL_Surface* tempSurface = IMG_Load(textureFileName);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(GameLoop::pRenderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    
    return texture;
}

void TextureHandler::Draw(SDL_Texture* texture, SDL_Rect source, SDL_Rect destination)
{
    SDL_RenderCopy(GameLoop::pRenderer, texture, &source, &destination);
}