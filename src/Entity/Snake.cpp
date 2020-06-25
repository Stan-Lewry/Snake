#include "Snake.h"

Snake::Snake(int spawnX, int spawnY) {
    inputs = GameEngine::createInputComponent({upArrow});
    world = GameEngine::createWorldComponent(spawnX, spawnY, 1, 1, 2);
    rend = GameEngine::createRenderableComponent("snake", true, world);
    phys = GameEngine::createPhysicsComponent({{0, 0}, {1, 1}}, "snake", world);
}

void Snake::doUpdate() {
    
}