#pragma once
#include <cstdint>
#include <stdlib.h>

class World;

class Unit {
public:
	uint32_t posX;
	uint32_t posY;

	uint16_t team;
	uint16_t age;
	uint16_t strength;

	Unit();
	void Step(World* world);
};
