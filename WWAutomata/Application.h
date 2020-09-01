#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "World.h"

static class Util {
public:
	static Uint32 GetPixel(SDL_Surface* surface, int x, int y);
};

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
	void GenerateWorldFromImage();
};
