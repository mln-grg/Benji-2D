#pragma once
#include<SDL.h>

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class Game
{
private:
	bool isRunning;
	double millisecsPreviousFrame = 0;
	SDL_Window* window;
	SDL_Renderer* renderer;
	
public:
	Game();
	~Game();
	void Initialize();
	void Run();
	void Setup();
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();

	int windowWidth;
	int windowHeight;
};

