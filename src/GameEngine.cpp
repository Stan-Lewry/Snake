#include "GameEngine.h"

#include "Component/WorldComponent.h"
#include "Component/RenderableComponent.h"
#include "Component/InputComponent.h"
#include "Component/PhysicsComponent.h"

#include "Entity/SimpleInputEntityTest.h"

GameEngine *GameEngine::instance = 0;

WorldComponent* GameEngine::createWorldComponent(float x, float y, float w, float h, float z) {
    WorldComponent* wc = new WorldComponent(x, y, w, h, z);
    return wc;
}

RenderableComponent* GameEngine::createRenderableComponent(std::string textureId, bool visible, WorldComponent* world) {
    RenderableComponent* rc = new RenderableComponent(textureId, visible);
    instance->renderer->registerRenderable(world, rc);
    return rc;
}

InputComponent* GameEngine::createInputComponent(std::list<Button> buttons) {
    InputComponent* ic = new InputComponent(buttons);
    instance->input->registerInputComponent(ic);
    return ic;
}

PhysicsComponent* GameEngine::createPhysicsComponent(vect<vect<float>> boundingBox, std::string name, WorldComponent* world) {
    PhysicsComponent* pc = new PhysicsComponent(boundingBox, name);
    instance->phys->registerPhysics(world, pc);
    return pc;
}

AnimationComponent* GameEngine::createAnimationComponent(std::vector<std::string> frames, double interval, bool loop, bool play, RenderableComponent* renderable) {
    AnimationComponent* ac = new AnimationComponent(frames, interval, loop, play);
    instance->anim->registerAnimationEntity(ac, renderable);
    return ac;
}
    


GameEngine::GameEngine() {
    SDEBUG("Constructing GameEngine");

    SDL_DisplayMode dm;
    SDL_GetDisplayMode(0, 0, &dm);

    cam = new Camera({20.0f, 20.0f}, 10.0f);

    input = new InputSubSystem();
    phys = new PhysicsSubSystem();
    TextureManager* tm  = new TextureManager();
    tm->initializeResource("assets/sheet.st");
    renderer = new Renderer2D(tm, 0, 0, 640, 640, cam);

    debugInfo = new DebugInfo();
    debugRenderer = new DebugRenderer(0, 0, 640, 640, cam, debugInfo);
    debugConsoleRenderer = new DebugConsoleRenderer(0, 0, 640, 640);

    anim = new AnimationSubSystem();
}

GameEngine::~GameEngine() {
    SDEBUG("Destructing GameEngine");
}

void GameEngine::run() {
    InputComponent* quitButton = new InputComponent({quit, f1, f2, leftSquareBracket, rightSquareBracket});
    input->registerInputComponent(quitButton);

    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 last = 0;
    double delta = 0;

    static double timer = 0;
    static int fCounter = 0;

    static bool showDebug = false;
    static bool showConsole = false;
    static bool lastF1 = false;
    static bool lastF2 = false;

    while (!quitButton->getButtonState(quit)) {
        lastF1 = quitButton->getButtonState(f1);
        lastF2 = quitButton->getButtonState(f2);

        last = now;
        now = SDL_GetPerformanceCounter();
        delta = (double)((now - last) * 1000 / (double)SDL_GetPerformanceFrequency());


        timer += delta;
        ++fCounter;
        if (timer >= 1000) {
            timer = 0;
            debugInfo->frameCount = fCounter;
            fCounter = 0;
        }

        cam->update(delta);
        phys->update(delta);      
        input->update(delta);
        anim->update(delta);
        
        if (quitButton->getButtonState(f1) && quitButton->getButtonState(f1) != lastF1) showDebug = !showDebug;
        if (quitButton->getButtonState(f2) && quitButton->getButtonState(f2) != lastF2) showConsole = !showConsole;
        if (quitButton->getButtonState(rightSquareBracket) && cam->getZoom() > 20.0f) cam->setZoom(cam->getZoom() - 1.0f);
        if (quitButton->getButtonState(leftSquareBracket) && cam->getZoom() < 600.0f) cam->setZoom(cam->getZoom() + 1.0f);


        SDL_RenderClear(rend);
        renderer->update(delta);
        if (showDebug) debugRenderer->update(delta);
        if (showConsole) debugConsoleRenderer->update(delta);
        SDL_RenderPresent(rend);
    }
}

