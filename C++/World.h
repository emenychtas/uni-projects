#ifndef WORLD_H
#define WORLD_H

#include "Block.h"
#include "Vehicle.h"
#include "Vehicle_Explorer.h"
#include "Vehicle_Analyzer.h"
#include "Vehicle_Rescuer.h"
#include <vector>

using std::vector;

class World
{
public:
	World(int[]);
	void WorkVehicles();
	void MoveVehicles();
	void PrintState();
	void PrintBaseInfo();
	void PrintMapStats();
	void PrintBlockInfo(int, int);
	void EditBlock(int, int, int, int, int);
	void PrintVehicles();
	void PrintVehicleStats();
	void PrintVehicleInfo(int);
	void ToggleVehicleStatus(int);
	void AddNewVehicle(int, int, char);
	int GameState();

private:
	void InitializeGrid();
	void InitializeVehicles();

	vector<vector<Block>> grid;
	vector<Vehicle*> vehicles;

	int dimX, dimY, explorersCount, analyzersCount, rescuersCount,targetPalladium, targetIridium, targetPlatinum;
};

#endif