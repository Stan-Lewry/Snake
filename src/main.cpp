#include "Utils/SDLUtils.h"
#include "Utils/Debug.h"
#include "GameEngine.h"

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

        ge->run();
    }
    else
    {
        SDEBUG("Failed to initialize SDL");
    }

    SDEBUG("Stopping");
    return 0;
}