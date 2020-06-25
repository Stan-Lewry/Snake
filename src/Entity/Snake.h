#pragma once

#include "Entity.h"

#include "../GameEngine.h"

class Snake : public Entity {
public:
    Snake(int spawnX, int spawnY);
    virtual ~Snake(){}
protected:
    void doUpdate() override;

private:
    InputComponent* inputs;
    WorldComponent* world;
    RenderableComponent* rend;
    PhysicsComponent* phys;
};