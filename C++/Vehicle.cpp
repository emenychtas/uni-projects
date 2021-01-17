#include "Vehicle.h"
#include <cstdlib>

Vehicle::Vehicle()
{
	damaged = false;
	durability = ((rand() % 10) + 1) / 10.0; // Limit from 0.1 to 1.0.

	moves = 0;
	breakdowns = 0;
	roundsDamaged = 0;
}

void Vehicle::V_Move(vector<vector<Block>> &grid)
{
	int destX, destY, offsetX, offsetY;
	int origX = positionX;
	int origY = positionY;

	for(int i=0; i<speed; i++)
	{
		if(!damaged && !getBlocked(grid))
		{
			do{
				do{
					offsetX = (rand() % 3) - 1; // Limit from -1 to 1.
					destX = positionX + offsetX;
				}while(destX < 0 || destX >= grid.size());
	
				do{
					offsetY = (rand() % 3) - 1;
					destY = positionY + offsetY;
				}while((offsetX == 0 && offsetY == 0) || destY < 0 || destY >= grid[0].size());

			}while(grid[destX][destY].getOccupied() || grid[destX][destY].getAvoid());
			
			positionX = destX;
			positionY = destY;
			moves++;
			movesTotal++;

			float break_probability = grid[positionX][positionY].getDifficulty() * (1 - durability);
			float lucky_roll = (float)rand() / RAND_MAX;
			if(lucky_roll < break_probability)
			{
				damaged = true;
				breakdowns++;
				breakdownsTotal++;
				damagedVehicles++;
			}
		}
	}

	if(positionX != origX || positionY != origY)
	{
		grid[origX][origY].setCurVehicle(NULL);
		grid[positionX][positionY].setCurVehicle(this);

		cout << symbol << index << ": moved from [" << origX << "," << origY << "] to [" << positionX << "," << positionY << "]";
		if(damaged) { cout << " and got damaged"; }
		cout << endl;
	}
}

void Vehicle::V_Work(vector<vector<Block>> &grid)
{
	//Will be overriden.
}

bool Vehicle::getBlocked(vector<vector<Block>> &grid)
{
	int counter=0, blocked=0, offsetX=-1, offsetY=-1, maxX=1, maxY=1;

	if(positionX == 0) { offsetX = 0; }
	if(positionX == grid.size() - 1) { maxX = 0; }
	if(positionY == 0) { offsetY = 0; }
	if(positionY == grid[0].size() - 1) { maxY = 0; }

	for(int i=offsetX; i<=maxX; i++)
	{
		for(int j=offsetY; j<=maxY; j++)
		{
			if(i!=0 || j!=0)
			{
				counter++;
				if(grid[positionX+i][positionY+j].getOccupied() || grid[positionX+i][positionY+j].getAvoid()) { blocked++; }
			}
		}
	}

	if(counter == blocked) return true;
	else return false;
}

int Vehicle::getSpeed() { return speed; }
void Vehicle::setSpeed(int x) { speed = x; }

bool Vehicle::getDamaged() { return damaged; }
void Vehicle::setDamaged(bool x) { damaged = x; }

float Vehicle::getDurability() { return durability; }
void Vehicle::setDurability(float x) { durability = x; }

int Vehicle::getRoundsD() { return roundsDamaged; }
void Vehicle::setRoundsD(int x) { roundsDamaged = x; }

int Vehicle::getIndex() { return index; }
char Vehicle::getSymbol() { return symbol; }

int Vehicle::getPositionX() { return positionX; }
int Vehicle::getPositionY() { return positionY; }
void Vehicle::setPosition(int x, int y) { positionX = x; positionY = y; }

int Vehicle::getMoves() { return moves; }
int Vehicle::getBreakdowns() { return breakdowns; }