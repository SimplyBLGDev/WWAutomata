#pragma once
#include <SDL.h>
#include "World.h"

class Application {
public:
	Application();

	void Boot();

private:
	World world;
	SDL_Window* window;
	SDL_Renderer* renderer;

	void PollInputs();
	void Run();
	void Render();
};