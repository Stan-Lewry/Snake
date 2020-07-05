#include "Snake.h"

Snake::Snake(int spawnX, int spawnY) {    
    inputs = GameEngine::createInputComponent({w, a, s, d, space});

    Segment head;
    head.world = GameEngine::createWorldComponent(spawnX, spawnY, 1, 1, 2);
    head.rend = GameEngine::createRenderableComponent("snake", true, head.world);
    head.phys = GameEngine::createPhysicsComponent({{0, 0}, {1, 1}}, "snake", true, head.world);

    body.push_back(head);

    GameEngine::registerEntity(this);

    alive = true;
    body[0].phys->setVelocity({0, -1});

    lastX = body[0].world->getWorldX();
    lastY = body[0].world->getWorldY();
}

void Snake::doUpdate() {

    static bool gotCoin  = false;

    if (body[0].phys->getCurrnentCollisionList().size() > 0) {
        std::string colId = body[0].phys->getCurrnentCollisionList()[0]->getName();
        if (colId == "wall" || colId == "snake"){
            alive = false;
        }
        else if (colId == "coin") {
            gotCoin = true;
        }
        body[0].phys->clearCollisions();
    }

    if (alive) {

        if (lastX != body[0].world->getWorldX() || lastY != body[0].world->getWorldY()) {

            if (gotCoin) {
                addSegment();
                gotCoin = false;
            }

            for (int i = body.size() - 1; i > 0; --i) {
                body[i].world->setWorldX(body[i-1].world->getWorldX());
                body[i].world->setWorldY(body[i-1].world->getWorldY());
            }

            lastX = body[0].world->getWorldX();
            lastY = body[0].world->getWorldY();
        }

        if (inputs->getButtonState(w)) body[0].phys->setVelocity({0, -1});
        if (inputs->getButtonState(a)) body[0].phys->setVelocity({-1, 0});
        if (inputs->getButtonState(s)) body[0].phys->setVelocity({0, 1});
        if (inputs->getButtonState(d)) body[0].phys->setVelocity({1, 0});

    }
}

void Snake::addSegment() {
    Segment seg;
    seg.world = GameEngine::createWorldComponent(body[body.size() -1].world->getWorldX(),
                                                    body[body.size() -1].world->getWorldY(), 1, 1, 2);
    seg.rend = GameEngine::createRenderableComponent("snake", true, seg.world);
    seg.phys = GameEngine::createPhysicsComponent({{0, 0}, {1, 1}}, "snake", true, seg.world);

    body.push_back(seg);
}