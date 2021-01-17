#ifndef VEHICLE_EXPLORER_H
#define VEHICLE_EXPLORER_H

#include "Vehicle.h"

class Vehicle_Explorer : public Vehicle
{
public:
	Vehicle_Explorer(int, int, int);
	void V_Work(vector<vector<Block>> &);

	int getFlags();

	static int flagsTotal;

private:
	int flags;
};

#endif