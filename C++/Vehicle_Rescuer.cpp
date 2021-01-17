#include "Vehicle_Rescuer.h"

Vehicle_Rescuer::Vehicle_Rescuer(int x, int y, int i)
{
	speed = 2;
	index = i;
	symbol = 'R';
	setPosition(x, y);

	rescues = 0;
}

void Vehicle_Rescuer::V_Work(vector<vector<Block>> &grid)
{
	int count=0, offsetX=-1, offsetY=-1, maxX=1, maxY=1;

	if(positionX == 0) { offsetX = 0; }
	if(positionX == grid.size() - 1) { maxX = 0; }
	if(positionY == 0) { offsetY = 0; }
	if(positionY == grid[0].size() - 1) { maxY = 0; }

	for(int i=offsetX; i<=maxX; i++)
	{
		for(int j=offsetY; j<=maxY; j++)
		{
			if(grid[positionX+i][positionY+j].getCurVehicle() != NULL)
			{
				if(grid[positionX+i][positionY+j].getCurVehicle()->getDamaged())
				{
					grid[positionX+i][positionY+j].getCurVehicle()->setDamaged(false);
					grid[positionX+i][positionY+j].getCurVehicle()->setRoundsD(0);
					count++;
				}
			}
		}
	}

	if(count > 0)
	{
		cout << symbol << index << ": fixed " << count << " vehicle(s) around [" << positionX << "," << positionY << "]" << endl;
		rescues += count;
		rescuesTotal += count;
		damagedVehicles -= count;
	}
}

int Vehicle_Rescuer::getRescues() { return rescues; }