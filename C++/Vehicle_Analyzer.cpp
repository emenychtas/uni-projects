#include "Vehicle_Analyzer.h"

extern int baseX, baseY;

Vehicle_Analyzer::Vehicle_Analyzer(int x, int y, int i)
{
	speed = 1;
	index = i;
	symbol = 'A';
	setPosition(x, y);

	maxLoad = 50;
	palladium = 0;
	iridium = 0;
	platinum = 0;

	extractedRes = 0;
}

void Vehicle_Analyzer::V_Work(vector<vector<Block>> &grid)
{
	int palladiumRes = grid[positionX][positionY].getPalladium();
	int iridiumRes = grid[positionX][positionY].getIridium();
	int platinumRes = grid[positionX][positionY].getPlatinum();
	int Sum = palladiumRes + iridiumRes + platinumRes;

	if(Sum >= 10)
	{
		float break_probability = grid[positionX][positionY].getDifficulty() * (1 - durability);
		float lucky_roll = (float)rand() / RAND_MAX;
		if(lucky_roll < break_probability)
		{
			damaged = true;
			breakdowns++;
			breakdownsTotal++;
			damagedVehicles++;
		}

		if(damaged) { cout << symbol << index << ": got damaged trying to extract from [" << positionX << "," << positionY << "]" << endl; }
		else
		{
			int palladiumCount = 0;
			int iridiumCount = 0;
			int platinumCount = 0;
			int curLoad = palladium + iridium + platinum;

			if(Sum <= maxLoad - curLoad)
			{
				palladiumCount = palladiumRes;
				grid[positionX][positionY].setPalladium(0);

				iridiumCount = iridiumRes;
				grid[positionX][positionY].setIridium(0);

				platinumCount = platinumRes;
				grid[positionX][positionY].setPlatinum(0);
			}
			else
			{
				while(curLoad < maxLoad)
				{
					if(palladiumRes > 0)
					{
						curLoad++;
						palladiumCount++;
						palladiumRes--;
					}
					if((curLoad < maxLoad) && iridiumRes > 0)
					{
						curLoad++;
						iridiumCount++;
						iridiumRes--;
					}
					if((curLoad < maxLoad) && platinumRes > 0)
					{
						curLoad++;
						platinumCount++;
						platinumRes--;
					}
				}

				grid[positionX][positionY].setPalladium(palladiumRes);
				grid[positionX][positionY].setIridium(iridiumRes);
				grid[positionX][positionY].setPlatinum(platinumRes);
			}

			palladium += palladiumCount;
			iridium += iridiumCount;
			platinum += platinumCount;
			extractedRes += palladiumCount + iridiumCount + platinumCount;
			extractedResTotal += palladiumCount + iridiumCount + platinumCount;

			cout << symbol << index << ": extracted  " << palladiumCount << " PA,  " << iridiumCount << " IR,  " << platinumCount << " PL from [" << positionX << "," << positionY << "]" << endl;

			if(palladium + iridium + platinum == maxLoad)
			{
				grid[positionX][positionY].setCurVehicle(NULL);

				positionX = baseX;
				positionY = baseY;

				grid[baseX][baseY].setPalladium(grid[baseX][baseY].getPalladium() + palladium);
				grid[baseX][baseY].setIridium(grid[baseX][baseY].getIridium() + iridium);
				grid[baseX][baseY].setPlatinum(grid[baseX][baseY].getPlatinum() + platinum);

				cout << "    " << "unloaded  " << palladium << " PA, " << iridium << " IR, " << platinum << " PL at base" << endl;

				palladium = 0;
				iridium = 0;
				platinum = 0;
			}
		}
	}
}

int Vehicle_Analyzer::getPalladium() { return palladium; }
int Vehicle_Analyzer::getIridium() { return iridium; }
int Vehicle_Analyzer::getPlatinum() { return platinum; }

int Vehicle_Analyzer::getExtractedRes() { return extractedRes; }