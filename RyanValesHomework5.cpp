/*
Written by : Ryan Vales
Student ID : S00339723
Written on : 7/17/21
Assignment : RyanValesHomework5.cpp
*/

/*
	Wizard Inventory (with Exceptions) project
	Modification of Wizard Inventory project
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Filename constants
const string filename_items = "wizard_all_items.txt";
const string filename_inventory = "wizard_inventory.txt";

// Function declarations
void load_items(vector<string>& items, string filename);
void save_items(const vector<string>& inventory, string filename);
void process_commands(string command, vector<string>& items, vector<string>& inventory);

// Populate the specified vector from the specified file
void load_items(vector<string>& items, string filename) {
	ifstream input_file;
	input_file.open(filename);
	if (input_file) {
		string line;
		while (getline(input_file, line)) {
			items.push_back(line);
		}
		input_file.close();
	}
	else {
		throw runtime_error("Could not find file: " + filename); 
	}
}

// Write the data in the specified vector to the specified file
void save_items(const vector<string>& items, string filename) {
	ofstream output_file;
	output_file.open(filename);
	if (output_file) {
		string line;
		for (string item : items) {
			output_file << item << '\n';
		}
		output_file.close();
	}
}

//process the commands from the user
void process_commands(string command, vector<string>& items, vector<string>& inventory) {
	if (command == "walk") {
		int index = rand() % items.size() - 1;
		++index;
		string item = items[index];

		cout << "While walking down a path, you see " + item + ".\n";

		char choice;
		cout << "Do you want to grab it? (y/n): ";
		cin >> choice;

		if (choice == 'y') {
			if (inventory.size() >= 4) {
				cout << "You can't carry any more items.  Drop something first.\n";
			}
			else {
				inventory.push_back(item);
				cout << "You picked up " + item + ".\n";
			}
		}
	}
	else if (command == "show") {
		int num = 0;
		for (string item : inventory) {
			cout << ++num << ". " << item << endl;
		}
	}
	else if (command == "drop") {
		unsigned int number;
		cout << "Number: ";
		cin >> number;

		if (number < 1 || number > inventory.size()) {
			cout << "Invalid item number.\n";
		}
		else {
			int index = number - 1;
			string item = inventory[index];
			inventory.erase(inventory.begin() + index);
			cout << "You dropped " + item + ".\n";
		}
	}
	else if (command == "exit") {
		save_items(inventory, filename_inventory); // Save wizard's inventory to file
		cout << "Bye!\n\n";
	}
	else {
		cout << "Invalid command. Try again.\n";
	}
}

int main() {
	srand(time(nullptr));

	cout << "The Wizard Inventory program\n\n";

	cout << "COMMAND MENU\n"
		<< "walk - Walk down the path\n"
		<< "show - Show all items\n"
		<< "drop - Drop an item\n"
		<< "exit - Exit program\n";

	// Try to read all items from file
	vector<string> all_items;
	//TRY LOAD
	try {
		load_items(all_items, filename_items);
	} //END TRY
	catch (runtime_error e) { //CATCH FILENOTFOUNDEXCEPTION 
		cout << endl << e.what() << endl;
		cout << "Exiting program. Bye!" << endl;
		exit(1);
	} //END CATCH

	vector<string> inventory;
	//TRY LOAD
	try {
		load_items(inventory, filename_inventory);
	} //END TRY
	catch (runtime_error e) { //CATCH FILENOTFOUNDEXCEPTION 
		cout << endl << e.what() << endl;
		cout << "Wizard is starting with no inventory." << endl;
	} //END CATCH
	
	string command = "";
	while (command != "exit") {
		// get command from user
		cout << endl;
		cout << "Command: ";
		cin >> command;

		process_commands(command, all_items, inventory);
	}
	return 0;
}