#include "Application.h"
#include <chrono>
#include <thread>

const char* worldPath = "C:\\Users\\Simply\\Desktop\\world.png";
const int FRAMEDURATION = 1000 / 600;

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

Uint32 Util::GetPixel(SDL_Surface* surface, int x, int y) {
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp)
	{
	case 1:
		return *p;
		break;

	case 2:
		return *(Uint16*)p;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
		break;

	case 4:
		return *(Uint32*)p;
		break;

	default:
		return 0;       /* shouldn't happen, but avoids warnings */
	}
}

Application::Application() {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	window = SDL_CreateWindow("World Automata", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINSIZEX, WINSIZEY, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	GenerateWorldFromImage();

	SDL_ShowWindow(window);
}

void Application::Boot() {
	for (int i = 0; i < 60; i++) {
		Unit u = Unit();
		u.team = i % 6;
		u.posX = 800;
		u.posY = 400;
		world.SpawnPerson(u);
	}

	while (true) {
		uint32_t frameStart = SDL_GetTicks();
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {
		
		}
		Run();
		Render();

		if (FRAMEDURATION > (SDL_GetTicks() - frameStart)) {
			SDL_Delay(FRAMEDURATION - (SDL_GetTicks() - frameStart));
		}
	}
}

void Application::Run() {
	world.Step();
}

void Application::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	for (int i = 0; i < world.population.size(); i++) {
		Unit* u = &world.population[i];
		SDL_SetRenderDrawColor(renderer, colors[u->team*3], colors[u->team *3+1], colors[u->team *3+2], 255);
		SDL_RenderDrawPoint(renderer, u->posX, u->posY);
	}
	SDL_RenderPresent(renderer);
}

void Application::GenerateWorldFromImage() {
	SDL_Surface* surface = IMG_Load(worldPath);
	int w = surface->w;
	int h = surface->h;
	world = World(w, h);

	for (int x = 0; x < w-1; x++)
		for (int y = 0; y < h-1; y++) {
			uint32_t pixel = ((uint8_t*)surface->pixels)[y*w + x];
			world.SetTiles(x, y, pixel == 0? 2: 1);
		}
}
