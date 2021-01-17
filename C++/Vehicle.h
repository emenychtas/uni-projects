#ifndef VEHICLE_H
#define VEHICLE_H

#include "Block.h"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

class Vehicle
{
public:
	Vehicle();
	void V_Move(vector<vector<Block>> &);
	virtual void V_Work(vector<vector<Block>> &);
	bool getBlocked(vector<vector<Block>> &);

	int getSpeed();
	void setSpeed(int);

	bool getDamaged();
	void setDamaged(bool);

	float getDurability();
	void setDurability(float);

	int getRoundsD();
	void setRoundsD(int);

	int getIndex();
	char getSymbol();

	int getPositionX();
	int getPositionY();
	void setPosition(int, int);

	int getMoves();
	int getBreakdowns();

	static int movesTotal, breakdownsTotal, damagedVehicles;

protected:
	int speed;
	bool damaged;
	float durability;
	int roundsDamaged;

	int index;
	char symbol;
	int positionX;
	int positionY;

	int moves;
	int breakdowns;
};

#endif