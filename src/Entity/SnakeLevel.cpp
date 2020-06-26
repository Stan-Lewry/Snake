#include "SnakeLevel.h"

Wall::Wall(int x, int y){
    world = GameEngine::createWorldComponent(x, y, 1, 1, 1);
    rend = GameEngine::createRenderableComponent("wall", true, world);
    phys = GameEngine::createPhysicsComponent({{0,0}, {1, 1}}, "snake_wall", world);
}

Ground::Ground(int x, int y){
    world = GameEngine::createWorldComponent(x, y, 1, 1, 1);
    rend = GameEngine::createRenderableComponent("ground", true, world);
}

SnakeLevel::SnakeLevel() {
    createLevel(40, 40);
}

void SnakeLevel::createLevel(int w, int h) {
    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            if (i == 0 || i == w - 1 || j == 0 || j == h - 1) {
                groundObjects.push_back(new Wall(j, i));
            } else {
                groundObjects.push_back(new Ground(j, i));
            }
        }
    }
}