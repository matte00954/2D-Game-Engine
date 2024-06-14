#include "GameLoop.h"
#include "GameSettings.h"

GameLoop *pGameLoop = nullptr;

int main(int argv, char **args)
{ 
    pGameLoop = new GameLoop();

    const int FPS = GameSettings::TARGET_FPS;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    //window name, x , y , width, height, fullscreen on/off
    pGameLoop->initialise(GameSettings::WINDOWPOS_X, GameSettings::WINDOWSPOS_Y,
     GameSettings::WINDOW_WIDTH, GameSettings::WINDOW_HEIGHT, GameSettings::IS_FULLSCREEN);

    while (pGameLoop->gameStatus())
    {
        frameStart = SDL_GetTicks();

        //SDL events
        pGameLoop->handleEvents();
        //updates every frame
        pGameLoop->update();
        //graphics
        pGameLoop->render();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    pGameLoop->clean();

    return 0;
}