#include "SnakeLevel.h"

#include <stdlib.h>
#include <time.h>

Wall::Wall(int x, int y){
    world = GameEngine::createWorldComponent(x, y, 1, 1, 1);
    rend = GameEngine::createRenderableComponent("wall", true, world);
    phys = GameEngine::createPhysicsComponent({{0,0}, {1, 1}}, "wall", true, world);
}

Ground::Ground(int x, int y){
    world = GameEngine::createWorldComponent(x, y, 1, 1, 1);
    rend = GameEngine::createRenderableComponent("ground", true, world);
}

Coin::Coin(int x, int y) {
    world = GameEngine::createWorldComponent(x, y, 1, 1, 1);
    rend = GameEngine::createRenderableComponent("coin", true, world);
    phys = GameEngine::createPhysicsComponent({{0, 0}, {1, 1}}, "coin", false, world);

    GameEngine::registerEntity(this);
}

void Coin::doUpdate() {
    if (phys->getCurrnentCollisionList().size() > 0) {
        world->setWorldX(rand() % (20 - 2) + 1);
        world->setWorldY(rand() % (20 - 2) + 1);
        phys->clearCollisions();
    }
}

SnakeLevel::SnakeLevel() {
    createLevel(20, 20);
}

void SnakeLevel::createLevel(int w, int h) {  
    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            if (i == 0 || i == w - 1 || j == 0 || j == h - 1) {
                level.push_back(new Wall(j, i));
            } else {
                level.push_back(new Ground(j, i));
            }
        }
    }

    srand(time(NULL));
    coin = new Coin(rand() % (w - 1) + 1, rand() % (h - 1) + 1);
    snake = new Snake(rand() % (w - 1) + 1, rand() % (h - 1) + 1);
}