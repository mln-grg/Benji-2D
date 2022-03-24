#include "Game.h"
#include<iostream>
#include <SDL.h>
#include <SDL_image.h>

Game::Game() {
	isRunning = false;
}
Game::~Game() {
	
}
void Game::Initialize() {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
	{
		std::cerr << "Error Initializing SDL"<<std::endl;
		return;
	}
	else {
		SDL_DisplayMode displayMode;
		SDL_GetCurrentDisplayMode(0, &displayMode);
		windowWidth = displayMode.w;
		windowHeight = displayMode.h;
			window = SDL_CreateWindow(
			"Benji",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			windowWidth,
			windowHeight,
			SDL_WINDOW_BORDERLESS
		);
		if (!window) {
			std::cerr << "Error Creating SDL window" << std::endl;
			return;
		}
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (!renderer) {
			std::cerr << "Error creating SDL renderer." << std::endl;
			return;
		}
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
		isRunning = true;
	}

}
void Game::ProcessInput() {
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
				isRunning = false;
			}
			break;
		
		}
	}
}
void Game::Setup() {

}
void Game::Update() {

}
void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);
	
	//Drawing a test PNG texture
	SDL_Surface* surface=IMG_Load("./assets/images/tank-tiger-right.png");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	//dst rect in the renderer to place the texture we just created
	SDL_Rect dstRect = { windowWidth/2,windowHeight/2,64,64 };

	SDL_RenderCopy(renderer, texture, NULL, &dstRect);

	SDL_DestroyTexture(texture);

	SDL_RenderPresent(renderer);
}


void Game::Run() {
	//Game Loop
	Setup();
	while (isRunning) 
	{
		ProcessInput();
		Update();
		Render();
	}

}
void Game::Destroy() {

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

}