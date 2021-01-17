#include "Vehicle_Explorer.h"

Vehicle_Explorer::Vehicle_Explorer(int x, int y, int i)
{
	speed = 3;
	index = i;
	symbol = 'E';
	setPosition(x, y);

	flags = 0;
}

void Vehicle_Explorer::V_Work(vector<vector<Block>> &grid)
{
	if(grid[positionX][positionY].getDifficulty() > 0.6)
	{
		grid[positionX][positionY].setAvoid(true);
		cout << symbol << index << ": placed danger flag at [" << positionX << "," << positionY << "]" << endl;
		flags++;
		flagsTotal++;
	}
}

int Vehicle_Explorer::getFlags() { return flags; }