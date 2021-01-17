#include "World.h"
#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;

extern int baseX, baseY;

World::World(int config[])
{
	dimX = config[0];
	dimY = config[1];
	baseX = config[2];
	baseY = config[3];
	explorersCount = config[4];
	analyzersCount = config[5];
	rescuersCount = config[6];
	targetPalladium = config[7];
	targetIridium = config[8];
	targetPlatinum = config[9];

	InitializeGrid();
	InitializeVehicles();
}

void World::WorkVehicles()
{
	for(int i=0; i<vehicles.size(); i++)
	{
		if(vehicles[i] != NULL && !vehicles[i]->getDamaged())
		{
			vehicles[i]->V_Work(grid);
		}
	}

	cout << endl;
}

void World::MoveVehicles()
{
	for(int i=0; i<vehicles.size(); i++)
	{
		if(vehicles[i] != NULL)
		{
			if(!vehicles[i]->getDamaged())
			{
				vehicles[i]->V_Move(grid);
			}
			else
			{
				if(vehicles[i]->getRoundsD() < 10)
				{
					vehicles[i]->setRoundsD(vehicles[i]->getRoundsD() + 1);
				}
				else
				{
					cout << vehicles[i]->getSymbol() << vehicles[i]->getIndex() << ": removed from the simulation" << endl;
					grid[vehicles[i]->getPositionX()][vehicles[i]->getPositionY()].setCurVehicle(NULL);
					vehicles[i] = NULL;
				}
			}
		}
	}

	cout << endl;
}

void World::PrintState()
{
	cout << "    ";
	for(int j=0; j<grid[0].size(); j++)
	{
		j<10 ? (cout << "0" << j) : (cout << j);
		cout << " ";
	}
	cout << endl << endl;

	for(int i=0; i<grid.size(); i++)
	{
		i<10 ? (cout << "0" << i) : (cout << i);
		cout << "  ";

		for(int j=0; j<grid[0].size(); j++)
		{
			if(i==baseX && j==baseY) { cout << 'X'; }
			else if(!grid[i][j].getOccupied()) { cout << '-'; }
			else { cout << grid[i][j].getCurVehicle()->getSymbol(); }
			cout << "  ";
		}
		cout << endl << endl;
	}
}

void World::PrintBaseInfo()
{
	cout << "Base Info:" << endl << endl;
	cout << "Palladium Resources:        " << grid[baseX][baseY].getPalladium() << "/" << targetPalladium << endl;
	cout << "Iridium Resources:          " << grid[baseX][baseY].getIridium() << "/" << targetIridium << endl;
	cout << "Platinum Resources:         " << grid[baseX][baseY].getPlatinum() << "/" << targetPlatinum << endl << endl;
}

void World::PrintMapStats()
{ 
	int pallTotal = 0, iridTotal = 0, platTotal = 0;

	int accessibleCount = 0;
	float diffSum = 0.0;

	for(int i=0; i<grid.size(); i++)
	{
		for(int j=0; j<grid[0].size(); j++)
		{
			pallTotal += grid[i][j].getPalladium();
			iridTotal += grid[i][j].getIridium();
			platTotal += grid[i][j].getPlatinum();

			if(!grid[i][j].getAvoid())
			{
				diffSum += grid[i][j].getDifficulty();
				accessibleCount++;
			}
		}
	}

	pallTotal -= grid[baseX][baseY].getPalladium();
	iridTotal -= grid[baseX][baseY].getIridium();
	platTotal -= grid[baseX][baseY].getPlatinum();

	float meanDiff = diffSum/accessibleCount;

	cout << "Mean Difficulty:      " << meanDiff << endl;
	cout << "Total Palladium:      " << pallTotal << endl;
	cout << "Total Iridium:        " << iridTotal << endl;
	cout << "Total Platinum:       " << platTotal << endl << endl;
}

void World::PrintBlockInfo(int x, int y)
{
	cout << "Block [" << x << "," << y << "] Info:" << endl << endl;
	cout << "Palladium Resources:        " << grid[x][y].getPalladium() << endl;
	cout << "Iridium Resources:          " << grid[x][y].getIridium() << endl;
	cout << "Platinum Resources:         " << grid[x][y].getPlatinum() << endl;
	cout << "Difficulty:                 " << grid[x][y].getDifficulty() << endl;
	cout << "Flagged:                    " << grid[x][y].getAvoid() << endl;
	cout << "Occupied by:                ";
	if(!grid[x][y].getOccupied()) { cout << "N/A" << endl << endl; }
	else { cout << grid[x][y].getCurVehicle()->getSymbol() << grid[x][y].getCurVehicle()->getIndex() << endl << endl; }
}

void World::EditBlock(int x, int y, int pa, int ir, int pl)
{
	grid[x][y].setPalladium(pa);
	grid[x][y].setIridium(ir);
	grid[x][y].setPlatinum(pl);

	cout << "Block [" << x << "," << y << "] resources edited." << endl << endl;
}

void World::PrintVehicles()
{
	cout << "Vehicle Indices: " << endl << endl;
	for(int i=0; i<vehicles.size(); i++)
	{
		if(vehicles[i] != NULL)
		{
			cout << i << ". " << vehicles[i]->getSymbol() << vehicles[i]->getIndex() << endl;
		}
	}
	cout << endl;
}

void World::PrintVehicleStats()
{
	cout << "Total Moves:                " << Vehicle::movesTotal << endl;
	cout << "Total Breakdowns:           " << Vehicle::breakdownsTotal << endl;
	cout << "Total Flags Placed:         " << Vehicle_Explorer::flagsTotal << endl;
	cout << "Total Resources Extracted:  " << Vehicle_Analyzer::extractedResTotal << endl;
	cout << "Total vehicles Fixed:       " << Vehicle_Rescuer::rescuesTotal << endl;
	cout << "Currently Damaged vehicles: " << Vehicle::damagedVehicles << endl << endl;
}

void World::PrintVehicleInfo(int i)
{
	cout << vehicles[i]->getSymbol() << vehicles[i]->getIndex() << " Info:" << endl << endl;
	cout << "Position:            " << vehicles[i]->getPositionX() << "," << vehicles[i]->getPositionY() << endl;
	cout << "Moves:               " << vehicles[i]->getMoves() << endl;
	cout << "Breakdowns:          " << vehicles[i]->getBreakdowns() << endl;
	cout << "Durability:          " << vehicles[i]->getDurability() << endl;
	cout << "Damaged:             " << vehicles[i]->getDamaged() << endl;
	cout << "Rounds Damaged:      " << vehicles[i]->getRoundsD() << endl;
	if(vehicles[i]->getSymbol() == 'E')
	{
		cout << "Flags Placed:        " << ((Vehicle_Explorer*)vehicles[i])->getFlags() << endl;
	}
	else if(vehicles[i]->getSymbol() == 'A')
	{
		cout << "Resources Extracted: " << ((Vehicle_Analyzer*)vehicles[i])->getExtractedRes() << endl;
		cout << "Palladium Load:      " << ((Vehicle_Analyzer*)vehicles[i])->getPalladium() << endl;
		cout << "Iridium Load:        " << ((Vehicle_Analyzer*)vehicles[i])->getIridium() << endl;
		cout << "Platinum Load:       " << ((Vehicle_Analyzer*)vehicles[i])->getPlatinum() << endl;
	}
	else if(vehicles[i]->getSymbol() == 'R')
	{
		cout << "vehicles Fixed:      " << ((Vehicle_Rescuer*)vehicles[i])->getRescues() << endl;
	}
	cout << endl;
}

void World::ToggleVehicleStatus(int i)
{
	if(vehicles[i]->getDamaged())
	{
		vehicles[i]->setDamaged(false);
		Vehicle::damagedVehicles--;
	}
	else
	{
		vehicles[i]->setDamaged(true);
		Vehicle::damagedVehicles++;
	}

	cout << vehicles[i]->getSymbol() << vehicles[i]->getIndex() << " status toggled." << endl << endl;
}

void World::AddNewVehicle(int x, int y, char type)
{
	if(grid[x][y].getOccupied())
	{
		cout << "The specified block is currently occupied." << endl << endl;
	}
	else
	{
		Vehicle* newVehicle = NULL;

		if(type == 'E' || type == 'e')
		{
			newVehicle = new Vehicle_Explorer(x, y, explorersCount);
			explorersCount++;
		}
		else if(type == 'A' || type == 'a')
		{
			newVehicle = new Vehicle_Analyzer(x, y, analyzersCount);
			analyzersCount++;
		}
		else if(type == 'R' || type == 'r')
		{
			newVehicle = new Vehicle_Rescuer(x, y, rescuersCount);
			rescuersCount++;
		}

		if(newVehicle != NULL)
		{
			grid[x][y].setCurVehicle(newVehicle);
			vehicles.push_back(newVehicle);
			cout << "New vehicle added at block [" << x << "," << y << "]." << endl << endl;
		}
		else
		{
			cout << "Invalid vehicle type." << endl << endl;
		}
	}
}

int World::GameState()
{
	int state = 0;

	if(grid[baseX][baseY].getPalladium() >= targetPalladium)
	{
		if(grid[baseX][baseY].getIridium() >= targetIridium)
		{
			if(grid[baseX][baseY].getPlatinum() >= targetPlatinum)
			{
				state = 1;
			}
		}
	}
	
	if(state == 0 && Vehicle::damagedVehicles >= vehicles.size())
	{
		state = -1;
	}
	
	return state;
}

void World::InitializeGrid()
{
	for(int i=0; i<dimX; i++)
	{
		vector<Block> Row;
		for(int j=0; j<dimY; j++)
		{
			Row.push_back(Block());
		}
		grid.push_back(Row);
	}

	grid[baseX][baseY].setPalladium(0);
	grid[baseX][baseY].setIridium(0);
	grid[baseX][baseY].setPlatinum(0);
	grid[baseX][baseY].setDifficulty(0.0);
	grid[baseX][baseY].setAvoid(true);
	grid[baseX][baseY].setCurVehicle(NULL);
}

void World::InitializeVehicles()
{
	for(int i=0; i<(explorersCount + analyzersCount + rescuersCount); i++)
	{
		int tempX, tempY;

		do{
			tempX = rand() % dimX;
			tempY = rand() % dimY;
		}while((tempX==baseX && tempY==baseY) || grid[tempX][tempY].getOccupied());
		
		Vehicle* newVehicle;

		if(i < explorersCount)
		{
			newVehicle = new Vehicle_Explorer(tempX, tempY, i);
		}
		else if(i < (explorersCount + analyzersCount))
		{
			newVehicle = new Vehicle_Analyzer(tempX, tempY, i-explorersCount);
		}
		else
		{
			newVehicle = new Vehicle_Rescuer(tempX, tempY, i-explorersCount-analyzersCount);
		}

		grid[tempX][tempY].setCurVehicle(newVehicle);
		vehicles.push_back(newVehicle);
	}
}