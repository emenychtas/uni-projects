#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct Employee
{
	char firstName[56];
	char lastName[56];
};

struct Company
{
	int id;
	char title[256];
	char summary[2048];
	int numberOfEmployees;
	Employee *employees;
};

struct Companies
{
	Company *arr;
	int numberOfCompanies;
};

void LoadFile(string);
void SaveFile();
void AddCompany();
void DeleteCompanyByID(int);
void DisplayCompanyByID(int);
void DisplayCompanies();
void DisplayCompaniesBySurname(string);
void SwapCompanies(int, int);
void SortCompanies();
int Search(int);
int LinearSearch(int);
int BinarySearch(int);
int BinaryInterpolationSearch(int);

Companies compDB;
string dbFilename;
bool dbLoaded = false;

void main(int argc, char *argv[])
{
	cout << "\n";

	if (argc == 1) LoadFile("data.csv");    // No argument: Load data.csv
	else if (argc == 2) LoadFile(argv[1]);  // 1  argument: Load specified file
	else
	{
		cout << "Too many arguments, terminating program.\n";
		return;
	}

	int menu_sel;
	string menu_input;
	
	cout << "\n";
	cout << "Company Data Manager:\n\n";
	cout << "1. Load Companies from File\n";
	cout << "2. Save Companies to File\n";
	cout << "3. Add a Company\n";
	cout << "4. Delete a Company by ID\n";
	cout << "5. Display a Company by ID\n";
	cout << "6. Display Companies\n";
	cout << "7. Display Companies by Surname\n";
	cout << "8. Exit\n\n";

	while (true)
	{
		cout << "Select: ";
		getline(cin, menu_input);
		menu_sel = menu_input[0] - 48;  // First character, convert to int.
		cout << "\n";

		switch (menu_sel)
		{
		case 1:
			cout << "Database Filename: ";
			getline(cin, menu_input);
			cout << "\n";
			LoadFile(menu_input);
			break;
		case 2:
			SaveFile();
			break;
		case 3:
			AddCompany();
			break;
		case 4:
			cout << "Company ID [Delete]: ";
			getline(cin, menu_input);
			cout << "\n";
			DeleteCompanyByID(stoi(menu_input));
			break;
		case 5:
			cout << "Company ID [Display]: ";
			getline(cin, menu_input);
			cout << "\n";
			DisplayCompanyByID(stoi(menu_input));
			break;
		case 6:
			DisplayCompanies();
			break;
		case 7:
			cout << "Employee Surname: ";
			getline(cin, menu_input);
			cout << "\n";
			DisplayCompaniesBySurname(menu_input);
			break;
		case 8:
			SaveFile();
			cout << "\nExiting...\n\n";
			system("PAUSE");
			return;
		default:
			cout << "Invalid Input\n";
		}

		cout << "\n";
	}
}

// Opens the specified database file loading any available content.
// In case the filename does not exist, this function creates the file.
void LoadFile(string filename)
{
	// If a database is already loaded, free the space and initialize.
	if (dbLoaded)
	{
		for (int i = 0; i < compDB.numberOfCompanies; i++)
		{
			free(compDB.arr[i].employees);
		}
		free(compDB.arr);

		compDB.numberOfCompanies = 0;
		dbLoaded = false;
	}

	ifstream datafile(filename);

	// If file exists, load any available content.
	if (datafile.is_open())
	{
		string buffer;

		// Read number of companies on file.
		getline(datafile, buffer);
		if (buffer.length() > 0) compDB.numberOfCompanies = stoi(buffer);
		else compDB.numberOfCompanies = 0;

		// Allocate needed memory for company array.
		compDB.arr = (Company*)malloc(compDB.numberOfCompanies * sizeof(Company));

		// For each company.
		for (int i = 0; i < compDB.numberOfCompanies; i++)
		{
			getline(datafile, buffer);

			// ID
			compDB.arr[i].id = stoi(buffer.substr(0, buffer.find(';')));
			// Title
			buffer = buffer.substr(buffer.find(';') + 1);
			buffer.substr(0, buffer.find(';')).copy(compDB.arr[i].title, 256);
			compDB.arr[i].title[buffer.substr(0, buffer.find(';')).length()] = '\0';
			// Summary
			buffer = buffer.substr(buffer.find(';') + 1);
			buffer.substr(0, buffer.find(';')).copy(compDB.arr[i].summary, 2048);
			compDB.arr[i].summary[buffer.substr(0, buffer.find(';')).length()] = '\0';
			// Number of Employees
			buffer = buffer.substr(buffer.find(';') + 1);
			compDB.arr[i].numberOfEmployees = stoi(buffer.substr(0, buffer.find(';')));
			// Employees
			compDB.arr[i].employees = (Employee*)malloc(compDB.arr[i].numberOfEmployees * sizeof(Employee));

			// For each employee.
			for (int j = 0; j < compDB.arr[i].numberOfEmployees; j++)
			{
				// First Name
				buffer = buffer.substr(buffer.find(';') + 1);
				buffer.substr(0, buffer.find(' ')).copy(compDB.arr[i].employees[j].firstName, 56);
				compDB.arr[i].employees[j].firstName[buffer.substr(0, buffer.find(' ')).length()] = '\0';
				// Last Name
				buffer = buffer.substr(buffer.find(' ') + 1);
				buffer.substr(0, buffer.find(';')).copy(compDB.arr[i].employees[j].lastName, 56);
				compDB.arr[i].employees[j].lastName[buffer.substr(0, buffer.find(';')).length()] = '\0';
			}
		}

		// Close file and mark database as loaded.
		datafile.close();
		dbLoaded = true;
		dbFilename = filename;

		// Sort database in case it's not sorted.
		SortCompanies();

		cout << "Database file \"" << filename << "\" loaded. Contains " << compDB.numberOfCompanies << " companies.\n";
	}
	// If file doesn't exist, create empty file.
	else
	{
		ofstream datafile(filename);

		if (datafile.is_open())
		{
			datafile.close();
			dbLoaded = true;
			dbFilename = filename;
			compDB.numberOfCompanies = 0;
			compDB.arr = (Company*)malloc(0);

			cout << "Database file \"" << filename << "\" created.\n";
		}
		else cout << "Filename \"" << filename << "\" not usable!\n";
	}
}

// Saves the database currently on RAM to the file it was loaded from.
void SaveFile()
{
	if (dbLoaded)
	{
		ofstream datafile(dbFilename);

		if (datafile.is_open())
		{
			// Write number of companies.
			datafile << compDB.numberOfCompanies << "\n";
			
			// For each company.
			for (int i = 0; i < compDB.numberOfCompanies; i++)
			{
				datafile << compDB.arr[i].id << ";" << compDB.arr[i].title << ";" << compDB.arr[i].summary << ";" << compDB.arr[i].numberOfEmployees;

				// For each employee.
				for (int j = 0; j < compDB.arr[i].numberOfEmployees; j++)
				{
					datafile << ";" << compDB.arr[i].employees[j].firstName << " " << compDB.arr[i].employees[j].lastName;
				}

				datafile << "\n";
			}

			datafile.close();

			cout << "Database saved successfully.\n";
		}
		else cout << "Failed to save database!\n";
	}
	else cout << "No loaded database to save.\n";
}

// Adds a new company to the database.
void AddCompany()
{
	// Increment number of companies and reallocate memory.
	compDB.numberOfCompanies++;
	compDB.arr = (Company*)realloc(compDB.arr, compDB.numberOfCompanies * sizeof(Company));

	string buffer;

	cout << "Adding new company to the database...\n\n";
	cout << "Company ID: ";
	getline(cin, buffer);
	compDB.arr[compDB.numberOfCompanies - 1].id = stoi(buffer);
	cout << "Company Title: ";
	getline(cin, buffer);
	buffer.copy(compDB.arr[compDB.numberOfCompanies - 1].title, 256);
	compDB.arr[compDB.numberOfCompanies - 1].title[buffer.length()] = '\0';
	cout << "Company Summary: ";
	getline(cin, buffer);
	buffer.copy(compDB.arr[compDB.numberOfCompanies - 1].summary, 2048);
	compDB.arr[compDB.numberOfCompanies - 1].summary[buffer.length()] = '\0';
	cout << "Number of Employees: ";
	getline(cin, buffer);
	compDB.arr[compDB.numberOfCompanies - 1].numberOfEmployees = stoi(buffer);

	// Allocate memory for the employees of the new company.
	compDB.arr[compDB.numberOfCompanies - 1].employees = (Employee*)malloc(compDB.arr[compDB.numberOfCompanies - 1].numberOfEmployees * sizeof(Employee));

	// For each employee.
	for (int i = 0; i < compDB.arr[compDB.numberOfCompanies - 1].numberOfEmployees; i++)
	{
		cout << "Employee #" << i + 1 << " First Name: ";
		getline(cin, buffer);
		buffer.copy(compDB.arr[compDB.numberOfCompanies - 1].employees[i].firstName, 56);
		compDB.arr[compDB.numberOfCompanies - 1].employees[i].firstName[buffer.length()] = '\0';
		cout << "Employee #" << i + 1 << " Last Name: ";
		getline(cin, buffer);
		buffer.copy(compDB.arr[compDB.numberOfCompanies - 1].employees[i].lastName, 56);
		compDB.arr[compDB.numberOfCompanies - 1].employees[i].lastName[buffer.length()] = '\0';
	}

	// Sort the database.
	SortCompanies();

	cout << "\nCompany record added to the database!\n";
}

// Deletes the company with the specified ID from the database.
void DeleteCompanyByID(int compID)
{
	// Check if the database is empty.
	if (compDB.numberOfCompanies == 0)
	{
		cout << "No companies exist in the database.\n";
		return;
	}

	// Search for the index of the specified company.
	int i = Search(compID);

	// If that company exists, delete it.
	if (i == -1) cout << "No company with matching ID was found.\n";
	else
	{
		// Swap that company with the last in the database.
		SwapCompanies(i, compDB.numberOfCompanies - 1);

		// Free the memory allocated for its employees.
		free(compDB.arr[compDB.numberOfCompanies - 1].employees);
		
		// Decrement number of companies and reallocate memory.
		compDB.numberOfCompanies--;
		compDB.arr = (Company*)realloc(compDB.arr, compDB.numberOfCompanies * sizeof(Company));

		// Sort the database.
		SortCompanies();

		cout << "Company with ID " << compID << " removed from the database!\n";
	}
}

// Displays the data of the company with the specified ID.
void DisplayCompanyByID(int compID)
{
	// Check if the database is empty.
	if (compDB.numberOfCompanies == 0)
	{
		cout << "No companies exist in the database.\n";
		return;
	}

	// Search for the index of the specified company.
	int i = Search(compID);

	// If the specified company exists, display its data.
	if (i == -1) cout << "No company with matching ID was found.\n";
	else
	{
		cout << "Company ID: " << compDB.arr[i].id << "\n";
		cout << "Company Title: " << compDB.arr[i].title << "\n";
		cout << "Company Summary: " << compDB.arr[i].summary << "\n";
		cout << "Number of Employees: " << compDB.arr[i].numberOfEmployees << "\n";

		// For each employee.
		for (int j = 0; j < compDB.arr[i].numberOfEmployees; j++)
		{
			cout << "Employee #" << j + 1 << ": " << compDB.arr[i].employees[j].firstName << " " << compDB.arr[i].employees[j].lastName << "\n";
		}
	}
}

// Displays the ID and Title of every company in the database.
void DisplayCompanies()
{
	// If database is not empty.
	if (compDB.numberOfCompanies > 0)
	{
		// For each company.
		for (int i = 0; i < compDB.numberOfCompanies; i++)
		{
			cout << "ID: " << compDB.arr[i].id << " Title: " << compDB.arr[i].title << "\n";
		}
		cout << "\n";
	}
	cout << "Number of Companies: " << compDB.numberOfCompanies << "\n";
}

// Displays the data of every company which has an employee with the specified surname.
void DisplayCompaniesBySurname(string surname)
{
	// Check if the database is empty.
	if (compDB.numberOfCompanies == 0)
	{
		cout << "No companies exist in the database.\n";
		return;
	}

	bool found = false;

	// For each company.
	for (int i = 0; i < compDB.numberOfCompanies; i++)
	{
		// For each employee.
		for (int j = 0; j < compDB.arr[i].numberOfEmployees; j++)
		{
			// If surname matches.
			if (compDB.arr[i].employees[j].lastName == surname)
			{
				found = true;
				
				// Display company ID and title.
				cout << "ID: " << compDB.arr[i].id << " Title: " << compDB.arr[i].title << "\n";

				// Go to the next company.
				break;
			}
		}
	}

	if (!found) cout << "No company with matching employee surname was found.\n";
}

// Swaps company records in database.
void SwapCompanies(int a, int b)
{
	Company temp;
	
	temp.id = compDB.arr[a].id;
	strcpy(temp.title, compDB.arr[a].title);
	strcpy(temp.summary, compDB.arr[a].summary);
	temp.numberOfEmployees = compDB.arr[a].numberOfEmployees;
	temp.employees = compDB.arr[a].employees;

	compDB.arr[a].id = compDB.arr[b].id;
	strcpy(compDB.arr[a].title, compDB.arr[b].title);
	strcpy(compDB.arr[a].summary, compDB.arr[b].summary);
	compDB.arr[a].numberOfEmployees = compDB.arr[b].numberOfEmployees;
	compDB.arr[a].employees = compDB.arr[b].employees;

	compDB.arr[b].id = temp.id;
	strcpy(compDB.arr[b].title, temp.title);
	strcpy(compDB.arr[b].summary, temp.summary);
	compDB.arr[b].numberOfEmployees = temp.numberOfEmployees;
	compDB.arr[b].employees = temp.employees;
}

// Sorts the database with ascending company IDs, using Insertion Sort.
void SortCompanies()
{
	int j;

	for (int i = 1; i < compDB.numberOfCompanies; i++)
	{
		j = i;

		while ((j > 0) && (compDB.arr[j - 1].id > compDB.arr[j].id))
		{
			SwapCompanies(j, j - 1);
			j--;
		}
	}
}

// Provides a menu for the user to select between search methods for ID search.
// Returns the index of the company with the specified ID.
int Search(int compID)
{
	int menu_sel;
	string menu_input;

	cout << "Search Method (1. Linear | 2. Binary | 3. BIS): ";

	getline(cin, menu_input);
	menu_sel = menu_input[0] - 48;   // First character, convert to int.

	cout << "\n";

	switch (menu_sel)
	{
	case 1:
		return LinearSearch(compID);
	case 2:
		return BinarySearch(compID);
	case 3:
		return BinaryInterpolationSearch(compID);
	default:
		return LinearSearch(compID);
	}
}

// Returns the index of the company with the specified ID, found with linear search.
int LinearSearch(int compID)
{
	cout << "[Using Linear Search]\n\n";

	for (int i = 0; i < compDB.numberOfCompanies; i++)
	{
		if (compDB.arr[i].id == compID) return i;
	}

	return -1;
}

// Returns the index of the company with the specified ID, found with binary search.
int BinarySearch(int compID)
{
	cout << "[Using Binary Search]\n\n";

	int mid;
	int left = 0;
	int right = compDB.numberOfCompanies - 1;

	if (compID > compDB.arr[right].id || compID < compDB.arr[left].id) return -1;

	while (left <= right)
	{
		mid = (left + right) / 2;

		if (compDB.arr[mid].id == compID) return mid;
		else if (compDB.arr[mid].id < compID) left = mid + 1;
		else right = mid - 1;
	}
	
	return -1;
}

// Returns the index of the company with the specified ID, found with binary interpolation search.
int BinaryInterpolationSearch(int compID)
{
	cout << "[Using Binary Interpolation Search]\n\n";

	int i, next, temp, size, left = 0, right = compDB.numberOfCompanies - 1;

	if (compID > compDB.arr[right].id || compID < compDB.arr[left].id) return -1;

	while (true)
	{
		size = right - left + 1;

		// If size is small, use linear search.
		if (size <= 5)
		{
			for (int j = 0; j < size; j++)
			{
				if (compID == compDB.arr[left + j].id) return (left + j);
				else if (j == size - 1) return -1;   // Not found.
			}
		}

		next = left + (int)ceil((size - 1) * (compID - compDB.arr[left].id) / (compDB.arr[right].id - compDB.arr[left].id));

		if (compID == compDB.arr[next].id) return next;

		i = 1;

		if (compID > compDB.arr[next].id)
		{
			while (true)
			{
				temp = next + (int)(i * sqrt(size));
				if (temp > compDB.numberOfCompanies - 1) temp = compDB.numberOfCompanies - 1;

				if (compID > compDB.arr[temp].id) i++;
				else break;
			}

			right = temp;
			left = next + (int)((i - 1) * sqrt(size)) + 1;
		}
		else if (compID < compDB.arr[next].id)
		{
			while (true)
			{
				temp = next - (int)(i * sqrt(size));
				if (temp < 0) temp = 0;

				if (compID < compDB.arr[temp].id) i++;
				else break;
			}

			right = next - (int)((i - 1) * sqrt(size)) - 1;
			left = temp;
		}
	}
}