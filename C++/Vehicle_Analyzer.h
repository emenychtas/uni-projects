#ifndef VEHICLE_ANALYZER_H
#define VEHICLE_ANALYZER_H

#include "Vehicle.h"

class Vehicle_Analyzer : public Vehicle
{
public:
	Vehicle_Analyzer(int, int, int);
	void V_Work(vector<vector<Block>> &);

	int getPalladium();
	int getIridium();
	int getPlatinum();

	int getExtractedRes();

	static int extractedResTotal;

private:
	int maxLoad;
	int palladium;
	int iridium;
	int platinum;

	int extractedRes;
};

#endif