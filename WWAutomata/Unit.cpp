#include "Unit.h"

Unit::Unit() {

}

void Unit::Step() {
	posX += rand() % 3 - 1;
	posY += rand() % 3 - 1;
}
