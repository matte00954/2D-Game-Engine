#ifndef __GAMELOOP_H__
#define __GAMELOOP_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <vector>

class Collider;

class GameLoop
{
private:
    SDL_Window *pWindow;
    bool isRunning;
    int count;
    void createGame();

public:
    GameLoop();
    ~GameLoop();
    void initialise(float x, float y, int width, int height, bool isFullscreen);
    void update();
    void render();
    void clean();
    void handleEvents();
    bool gameStatus() { return isRunning; }

    static SDL_Renderer *pRenderer;
    static SDL_Event event;

    static std::vector <Collider*> pAllColliders;
};

#endif // __GAMELOOP_H__