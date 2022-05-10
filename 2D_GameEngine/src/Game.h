#pragma once
#include<SDL.h>
#include "ECS/ECS.h"
#include <SDL.h>
#include "AssetStore/AssetStore.h"
#include "EventBus/EventBus.h"

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class Game {
private:
    bool isRunning;
    bool isDebug;
    int millisecsPreviousFrame = 0;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Rect camera;

    std::unique_ptr<Registry> registry;
    std::unique_ptr<AssetStore> assetStore;
    std::unique_ptr<EventBus> eventBus;

public:
    Game();
    ~Game();
    void Initialize();
    void Run();
    void Setup();
    void LoadLevel(int level);
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();

    static int windowWidth;
    static int windowHeight;
    static int mapWidth;
    static int mapHeight;
};