#include "Unit.h"
#include "World.h"

Unit::Unit() {

}

void Unit::Step(World* world) {
	int8_t movX = rand() % 3 - 1;
	int8_t movY = rand() % 3 - 1;

	if (world->GetTile(posX + movX, posY + movY) == 1) {
		posX += movX;
		posY += movY;
	}
}
