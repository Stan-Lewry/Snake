#include "PhysicsSubSystem.h"

static const double tickSpeed = 1000 / 8;
static const float frictionConstant = 0.85f;
static const float frictionThreshold = 0.005f;

PhysicsSubSystem::PhysicsSubSystem()
    : SubSystem(tickSpeed)
    , physicsComponents() {}

PhysicsSubSystem::~PhysicsSubSystem() {}

void PhysicsSubSystem::registerPhysics(WorldComponent* worldCompo, PhysicsComponent* physicsCompo) {
    physicsComponents.push_back(std::make_pair(worldCompo, physicsCompo));
}

void PhysicsSubSystem::doUpdate(double dTime) {
    for (auto pair : physicsComponents) {

        pair.second->clearCollisions();

        resolveCollisionsAABB(pair);

        pair.first->setWorldX(pair.first->getWorldX() + pair.second->getVelocity().x);
        pair.first->setWorldY(pair.first->getWorldY() + pair.second->getVelocity().y);
    }
}

void PhysicsSubSystem::resolveCollisionsAABB(std::pair<WorldComponent*, PhysicsComponent*> entity) {
    SDL_Rect ra, rb, i;
    ra = {(entity.second->getBoundingBox().x + entity.first->getWorldX() + entity.second->getVelocity().x) * 10,
            (entity.second->getBoundingBox().y + entity.first->getWorldY() + entity.second->getVelocity().y) * 10,
            entity.second->getBoundingBox().w * 10,
            entity.second->getBoundingBox().h * 10};
    i = {0, 0, 0, 0};
    vect<float> vel = entity.second->getVelocity();

    for (auto entity2 : physicsComponents) {
        if (entity2.second != entity.second) {
            rb = {(entity2.second->getBoundingBox().x + entity2.first->getWorldX()) * 10,
                    (entity2.second->getBoundingBox().y + entity2.first->getWorldY()) * 10,
                    entity2.second->getBoundingBox().w * 10,
                    entity2.second->getBoundingBox().h * 10};

            if (SDL_IntersectRect(&rb, &ra, &i)) {
                bool collide = false;
                if (i.w <= i.h) {
                    if (entity2.second->isSolid()) vel.x = 0;
                    collide = true;
                }
                if (i.h <= i.w){
                     if (entity2.second->isSolid()) vel.y = 0;
                     collide = true;
                }
                if (collide){
                    entity.second->addCollision(entity2.second);
                    entity2.second->addCollision(entity.second);
                }
                entity.second->setVelocity(vel);
            }
        }
    }
}

void PhysicsSubSystem::resolveFriction(std::pair<WorldComponent*, PhysicsComponent*> entity) {
    vect<float> vel = entity.second->getVelocity();
    (vel.x > -frictionThreshold && vel.x < frictionThreshold) ? vel.x = 0 : vel.x *= frictionConstant;
    (vel.y > -frictionThreshold && vel.y < frictionThreshold) ? vel.y = 0 : vel.y *= frictionConstant;
    entity.second->setVelocity(vel);
}
