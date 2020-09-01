#include "World.h"

World::World() {}

World::World(uint32_t width, uint32_t height) {
	this->width = width;
	this->height = height;
	data = new uint8_t[width*height];
}

uint8_t World::GetTile(uint32_t x, uint32_t y) {
	return data[width * y + x];
}

void World::SpawnPerson(Unit unit) {
	population.push_back(unit);
}

void World::Step() {
	for (int i = 0; i < population.size(); i++) {
		population[i].Step();
	}
}
