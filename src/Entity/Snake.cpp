#include "Snake.h"

Snake::Snake(int spawnX, int spawnY) {    
    inputs = GameEngine::createInputComponent({w, a, s, d});
    world = GameEngine::createWorldComponent(spawnX, spawnY, 1, 1, 2);
    rend = GameEngine::createRenderableComponent("snake", true, world);
    phys = GameEngine::createPhysicsComponent({{0, 0}, {1, 1}}, "snake", world);
    GameEngine::registerEntity(this);

    alive = true;
    phys->setVelocity({0, -1});
}

void Snake::doUpdate() {
    if (phys->getCurrnentCollisionList().size() > 0) {
        alive = false;
    }

    if (alive) {
        if (inputs->getButtonState(w)) phys->setVelocity({0, -1});
        if (inputs->getButtonState(a)) phys->setVelocity({-1, 0});
        if (inputs->getButtonState(s)) phys->setVelocity({0, 1});
        if (inputs->getButtonState(d)) phys->setVelocity({1, 0});
    }
}