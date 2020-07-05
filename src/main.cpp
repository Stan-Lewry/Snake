#include "Utils/SDLUtils.h"
#include "Utils/Debug.h"
#include "GameEngine.h"
#include "Entity/SnakeLevel.h"
#include "Entity/Snake.h"

int main (int argv, char* argc[])
{
    SDEBUG("Starting...");

    if (argv > 1)
    {
        SDEBUG("Argument %s", argc[0]);
    }

    if (initSDL())
    {
        GameEngine* ge = GameEngine::getInstance();

        SnakeLevel* sl = new SnakeLevel();
        ge->run();
    }
    else
    {
        SDEBUG("Failed to initialize SDL");
    }

    SDEBUG("Stopping");
    return 0;
}