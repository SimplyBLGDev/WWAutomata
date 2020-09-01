#include "Application.h"
#include <chrono>
#include <thread>

const int WINSIZEX = 1800;
const int WINSIZEY = 900;
const int colors[] {
	255, 0, 0,
	0, 255, 0,
	0, 0, 255,
	0, 255, 255,
	255, 0, 255,
	255, 255, 0
};

Application::Application() {
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("World Automata", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINSIZEX, WINSIZEY, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	world = World(WINSIZEX, WINSIZEY);

	SDL_ShowWindow(window);
}

void Application::Boot() {
	for (int i = 0; i < 60; i++) {
		Unit u = Unit();
		u.team = i % 6;
		u.posX = 800;
		u.posY = 500;
		world.SpawnPerson(u);
	}

	while (true) {
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {
		
		}
		Run();
		Render();
	}
}

void Application::Run() {
	world.Step();
}

void Application::Render() {
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	for (int i = 0; i < world.population.size(); i++) {
		Unit* u = &world.population[i];
		SDL_SetRenderDrawColor(renderer, colors[u->team*3], colors[u->team *3+1], colors[u->team *3+2], 32);
		SDL_RenderDrawPoint(renderer, u->posX, u->posY);
	}
	SDL_RenderPresent(renderer);
}
