#ifndef VEHICLE_RESCUER_H
#define VEHICLE_RESCUER_H

#include "Vehicle.h"

class Vehicle_Rescuer : public Vehicle
{
public:
	Vehicle_Rescuer(int, int, int);
	void V_Work(vector<vector<Block>> &);

	int getRescues();

	static int rescuesTotal;

private:
	int rescues;
};

#endif