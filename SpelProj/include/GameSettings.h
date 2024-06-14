#ifndef __GAMESETTINGS_H__
#define __GAMESETTINGS_H__

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
// allows user to easily change game settings
// static, to access variables from anywhere
class GameSettings
{
public:
    const static int TARGET_FPS = 60;
    const static auto WINDOWPOS_X = SDL_WINDOWPOS_CENTERED;
    const static auto WINDOWSPOS_Y = SDL_WINDOWPOS_CENTERED;
    const static int WINDOW_WIDTH = 1200;
    const static int WINDOW_HEIGHT = 800;
    const static bool IS_FULLSCREEN = false;
};

#endif // __GAMESETTINGS_H__