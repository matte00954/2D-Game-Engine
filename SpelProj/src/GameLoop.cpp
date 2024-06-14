#include "GameLoop.h"
#include "TextureHandler.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "GameSettings.h"

SDL_Renderer *GameLoop::pRenderer = nullptr;
SDL_Event GameLoop::event;

// all colliders end up here
std::vector<Collider *> GameLoop::pAllColliders;

// ECS manager object
EntitySystemManager manager;
// game title
const char *title = "Crab Catcher";

GameLoop::GameLoop()
{
}

GameLoop::~GameLoop()
{
}

// Set screen size, window type (fullscreen , windowed etc)
void GameLoop::initialise(float x, float y, int width, int height, bool isFullscreen)
{
    // flags = fullscreen / normal
    int flags = 0;

    if (isFullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    else
    {
        flags = SDL_WINDOW_SHOWN;
    }

    int initialiseStatus = SDL_Init(SDL_INIT_EVERYTHING);

    //std::cout << "SDL init = " << initialiseStatus << std::endl;

    if (initialiseStatus == 0)
    {
        //std::cout << "SDL initialised" << std::endl;
        pWindow = SDL_CreateWindow(title, x, y, width, height, flags);

        if (pWindow)
        {
            //std::cout << "Window created" << std::endl;
        }

        pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

        if (pRenderer)
        {
            SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
            //std::cout << "Renderer created" << std::endl;
        }

        isRunning = true;
    }
    else
    {
        isRunning = false;
    }
    createGame();
}

// add game objects here
auto &player(manager.createEntity());
Vector2D lastViablePosition;

auto &enemy1(manager.createEntity());
auto &enemy2(manager.createEntity());
auto &enemy3(manager.createEntity());
auto &wall1(manager.createEntity());
auto &wall2(manager.createEntity());
auto &wall3(manager.createEntity());

int victoryPoints = 0;

// make the game in this function
void GameLoop::createGame()
{
    player.addComponent<Transform>(2);
    player.addComponent<Sprite>("resources/images/water.png");
    player.addComponent<KeyboardController>();
    player.addComponent<Collider>("player");
    player.setName("player");

    enemy1.addComponent<Transform>(300.0f, 200.0f, 32, 32, 1, 4);
    enemy1.addComponent<Sprite>("resources/images/enemy.png");
    enemy1.addComponent<Collider>("enemy");
    enemy1.addComponent<EnemyBehavior>(900, 100, 1.0f, 0);
    enemy1.setName("enemy1");

    enemy2.addComponent<Transform>(800.0f, 300.0f, 32, 32, 1, 4);
    enemy2.addComponent<Sprite>("resources/images/enemy.png");
    enemy2.addComponent<Collider>("enemy");
    enemy2.addComponent<EnemyBehavior>(700, 350, 1.25f, 0);
    enemy2.setName("enemy2");

    enemy3.addComponent<Transform>(800.0f, 700.0f, 32, 32, 1, 4);
    enemy3.addComponent<Sprite>("resources/images/enemy.png");
    enemy3.addComponent<Collider>("enemy");
    enemy3.addComponent<EnemyBehavior>(900, 100, 1.5f, 0);
    enemy3.setName("enemy3");

    wall1.addComponent<Transform>(300.0f, 300.0f, 150, 20, 1, 0);
    wall1.addComponent<Sprite>("resources/images/dirt.png");
    wall1.addComponent<Collider>("wall");
    wall1.setName("wall1");

    wall2.addComponent<Transform>(600.0f, 100.0f, 30, 300, 1, 0);
    wall2.addComponent<Sprite>("resources/images/grass.png");
    wall2.addComponent<Collider>("wall");
    wall2.setName("wall2");

    wall3.addComponent<Transform>(900.0f, 400.0f, 200, 30, 1, 0);
    wall3.addComponent<Sprite>("resources/images/grass.png");
    wall3.addComponent<Collider>("wall");
    wall3.setName("wall3");
}

// the game loop
void GameLoop::update()
{
    // update all entities and their components
    manager.refresh();
    manager.update();

    if (victoryPoints >= 3)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Victory", "You won the game!", NULL);
        isRunning = false;
    }

    if (player.getComponent<Collider>().insideScreenCheck())
    {
        player.getComponent<Transform>().position = lastViablePosition;
    }

    for (size_t i = 0; i < pAllColliders.size(); i++)
    {
        SDL_Rect item = pAllColliders.at(i)->getRectangles();
        if (pAllColliders.at(i) != &player.getComponent<Collider>())
        {
            if (player.getComponent<Collider>().AABB(item))
            {
                if (pAllColliders.at(i)->getTag().compare("wall") == 0 && pAllColliders.at(i)->pEntity->isActive())
                {
                    // std::cout << "player collided with object" << std::endl;
                    player.getComponent<Transform>().position = lastViablePosition;
                }
                else if (pAllColliders.at(i)->getTag().compare("enemy") == 0 && pAllColliders.at(i)->pEntity->isActive())
                {
                    // std::cout << "player collided with enemy : " << colliders.at(i)->entity->getName() << " at " << colliders.at(i)->getListPosition() << std::endl;
                    pAllColliders.at(i)->pEntity->destroy();
                    // std::cout << "destroying enemy entity " << colliders.at(i)->entity->getName() << " : " << colliders.at(i)->getListPosition() << std::endl;
                    victoryPoints++;
                    manager.refresh();
                }
            }
        }
    }
    lastViablePosition = player.getComponent<Transform>().position;
}

void GameLoop::render()
{
    SDL_RenderClear(pRenderer);
    manager.draw();
    SDL_RenderPresent(pRenderer);
}

void GameLoop::clean()
{
    SDL_DestroyWindow(pWindow);
    SDL_DestroyRenderer(pRenderer);
    SDL_Quit();
    std::cout << "Game cleaned";
}

void GameLoop::handleEvents()
{
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }
}