#include "Block.h"
#include <cstdlib>

Block::Block()
{
	palladium = rand() % 10; // Limit from 0 to 9.
	iridium = rand() % 10;
	platinum = rand() % 10;
	difficulty = (rand() % 10) / 10.0; // Limit from 0.0 to 0.9.
	avoid = false;

	curVehicle = NULL;
}

int Block::getPalladium() { return palladium; }
void Block::setPalladium(int x) { palladium = x; }

int Block::getIridium() { return iridium; }
void Block::setIridium(int x) { iridium = x; }

int Block::getPlatinum() { return platinum; }
void Block::setPlatinum(int x) { platinum = x; }

float Block::getDifficulty() { return difficulty; }
void Block::setDifficulty(float x) { difficulty = x; }

bool Block::getAvoid() { return avoid; }
void Block::setAvoid(bool x) { avoid = x; }

Vehicle* Block::getCurVehicle() { return curVehicle; }
void Block::setCurVehicle(Vehicle* x) { curVehicle = x; }

bool Block::getOccupied()
{
	if(curVehicle != NULL) return true;
	else return false;
}