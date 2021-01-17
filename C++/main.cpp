#include "World.h"
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;

int baseX, baseY;

int	Vehicle::movesTotal = 0;
int	Vehicle::breakdownsTotal = 0;
int Vehicle::damagedVehicles = 0;
int	Vehicle_Explorer::flagsTotal = 0;
int	Vehicle_Analyzer::extractedResTotal = 0;
int	Vehicle_Rescuer::rescuesTotal = 0;

int main()
{
	srand((unsigned)time(NULL));

	string configLine, command;
	ifstream configFile;
	int config[10];

	configFile.open("config.txt");
	for(int i=0; i<10; i++)
	{
		std::getline(configFile, configLine);
		config[i] = std::stoi(configLine);
	}
	configFile.close();
	
	World my_World(config);
	
	int gameState = 0;

	while(gameState == 0)
	{
		cout << "> Command: ";
		cin >> command;
		cout << endl;

		if(command.compare("help") == 0)
		{
			cout << "Command List:" << endl << endl;
			cout << "exit" << endl;
			cout << "step" << endl;
			cout << "print" << endl;
			cout << "base_info" << endl;
			cout << "block_stats" << endl;
			cout << "block_info" << endl;
			cout << "block_edit" << endl;
			cout << "vehicle_list" << endl;
			cout << "vehicle_stats" << endl;
			cout << "vehicle_info" << endl;
			cout << "vehicle_toggle" << endl;
			cout << "vehicle_add" << endl << endl;
		}
		else if(command.compare("exit") == 0)
		{
			break;
		}
		else if(command.compare("step") == 0)
		{
			my_World.WorkVehicles();
			my_World.MoveVehicles();
		}
		else if(command.compare("print") == 0)
		{
			my_World.PrintState();
		}
		else if(command.compare("base_info") == 0)
		{
			my_World.PrintBaseInfo();
		}
		else if(command.compare("block_stats") == 0)
		{
			my_World.PrintMapStats();
		}
		else if(command.compare("block_info") == 0)
		{
			int x, y;
			string position;

			cout << "Position: ";
			cin >> position;
			cout << endl;
			unsigned index = position.find(",");
			x = stoi(position.substr(0, index));
			y = stoi(position.substr(index + 1, string::npos));
			
			my_World.PrintBlockInfo(x, y);
		}
		else if(command.compare("block_edit") == 0)
		{
			int x, y, pa, ir, pl;
			string position;

			cout << "Position: ";
			cin >> position;
			cout << endl;
			unsigned index = position.find(",");
			x = stoi(position.substr(0, index));
			y = stoi(position.substr(index + 1, string::npos));

			cout << "Palladium: ";
			cin >> pa;
			cout << "Iridium: ";
			cin >> ir;
			cout << "Platinum: ";
			cin >> pl;
			cout << endl;

			my_World.EditBlock(x, y, pa, ir, pl);
		}
		else if(command.compare("vehicle_list") == 0)
		{
			my_World.PrintVehicles();
		}
		else if(command.compare("vehicle_stats") == 0)
		{
			my_World.PrintVehicleStats();
		}
		else if(command.compare("vehicle_info") == 0)
		{
			int index;

			cout << "Index: ";
			cin >> index;
			cout << endl;

			my_World.PrintVehicleInfo(index);
		}
		else if(command.compare("vehicle_toggle") == 0)
		{
			int index;

			cout << "Index: ";
			cin >> index;
			cout << endl;
		
			my_World.ToggleVehicleStatus(index);
		}
		else if(command.compare("vehicle_add") == 0)
		{
			int x, y;
			char type;
			string position;

			cout << "Position: ";
			cin >> position;
			unsigned index = position.find(",");
			x = stoi(position.substr(0, index));
			y = stoi(position.substr(index + 1, string::npos));

			cout << "Type (E,A,R): ";
			cin >> type;
			cout << endl;

			my_World.AddNewVehicle(x, y, type);
		}

		gameState = my_World.GameState();
	}

	if(gameState != 0)
	{
		if(gameState == 1) { cout << "Game won!"; }
		else { cout << "Game lost.."; }
		cin >> command;
	}

	return 0;
}