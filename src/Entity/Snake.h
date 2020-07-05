#pragma once

#include "Entity.h"

#include "../GameEngine.h"

struct Segment {
    WorldComponent* world;
    RenderableComponent* rend;
    PhysicsComponent* phys;
};

class Snake : public Entity {
public:
    Snake(int spawnX, int spawnY);
    virtual ~Snake(){}
protected:
    void doUpdate() override;

private:
    void addSegment();

    std::vector<Segment> body;

    InputComponent* inputs;

    int lastX, lastY;

    bool alive;
};