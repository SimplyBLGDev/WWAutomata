#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>
#include "Unit.h"

// TILE TABLE:
// 0x00: null
// 0x01: Water
// 0x02: Ground
// ..
// 0xFF: null

class World {
public:
	std::vector<Unit> population;

	World();
	World(uint32_t width, uint32_t height);
	uint8_t GetTile(uint32_t x, uint32_t y);
	void SetTiles(uint32_t x, uint32_t y, uint8_t value);
	void SpawnPerson(Unit unit);
	void Step();
private:
	uint32_t width;
	uint32_t height;
	uint8_t* data;
};
