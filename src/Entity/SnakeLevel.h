#pragma once

#include "Entity.h"
#include "Snake.h"

#include "../GameEngine.h"

class Wall : public Entity {
public:
    Wall(int x, int y);
    virtual ~Wall(){}
protected:
    void doUpdate() override{}
private:
    WorldComponent* world;
    RenderableComponent* rend;
    PhysicsComponent* phys;
};

class Ground : public Entity {
public:
    Ground(int x, int y);
    virtual ~Ground(){}
protected:
    void doUpdate() override{}
private:
    WorldComponent* world;
    RenderableComponent* rend;
};

class Coin : public Entity {
public:
    Coin(int x, int y);
    virtual ~Coin(){}
protected:
    void doUpdate() override;
private:
    WorldComponent* world;
    RenderableComponent* rend;
    PhysicsComponent* phys;
};

class SnakeLevel {
public:
    SnakeLevel();
    virtual ~SnakeLevel(){}
private:
    void createLevel(int w, int h);

    std::vector<Entity*> level;

    Snake* snake;
    Coin* coin;


};