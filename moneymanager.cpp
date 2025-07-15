// Text file for money management system
// This file contains the initial setup and instructions for the money management system.
// Money Management System
// Version: 1.0
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <utility>
using namespace std;

void ensiRuutu() {
	// Display the welcome message
	cout << "Tervetuloa Raha Hallinta Järjestelmään!" << endl;
	cout << "Tämä ohjelma auttaa sinua hallitsemaan tuloja ja kuluja." << endl;
	cout << "Haluatko ladata aiemmin tallennetut tiedot? (Kyllä/Ei): ";
	cout << "Edelliset tiedot voit poistaa poistamalla 'data.txt' tiedoston." << endl;
	string response;
	getline(cin, response);

	if (response == "Kyllä" || response == "kyllä") {
		cout << "Ladataan aiemmin tallennetut tiedot..." << endl;
	} else {
		cout << "Aloitetaan alusta ilman aiempia tietoja." << endl;
	}
}

// Function to display the menu
void näytäMenu() {
	// Display the menu options
	cout << "\nValitse toiminto:" << endl;
	cout << "1. Lisää tulo" << endl;
	cout << "2. Lisää kulu" << endl;
	cout << "3. Näytä yhteenveto" << endl;
	cout << "4. Tallenna ja poistu" << endl;
}

// Function to add income
void lisääTulo(vector<pair<string, double>>& incomes) {
	string description;
	double amount;

	// Get income description and amount from user
	cout << "Lisää tulo:" << endl;
	cout << "Kuvaus: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
	getline(cin, description);
	cout << "Määrä: ";
	cin >> amount;

	// Add the income to the vector
	incomes.push_back(make_pair(description, amount));
	cout << "Tulo lisätty onnistuneesti!" << endl;
}

// Function to add expense
void lisääKulu(vector<pair<string, double>>& expenses) {
	string description;
	double amount;

	// Get expense description and amount from user
	cout << "\nLisää kulu:" << endl;
	cout << "Kuvaus: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
	getline(cin, description);
	cout << "Määrä: ";
	cin >> amount;

	// Add the expense to the vector
	expenses.push_back(make_pair(description, amount));
	cout << "Kulu lisätty onnistuneesti!" << endl;
}

// Function to display summary of incomes and expenses
void näytäYhteenveto(const vector<pair<string, double>>& incomes, const vector<pair<string, double>>& expenses) {
	double totalIncome = 0.0;
	double totalExpense = 0.0;

	// Calculate total income
	cout << "\nTulot:" << endl;
	for (const auto& income : incomes) {
		cout << income.first << ": " << fixed << setprecision(2) << income.second << " €" << endl;
		totalIncome += income.second;
	}

	// Calculate total expenses
	cout << "\nKulut:" << endl;
	for (const auto& expense : expenses) {
		cout << expense.first << ": " << fixed << setprecision(2) << expense.second << " €" << endl;
		totalExpense += expense.second;
	}

	// Display totals
	cout << "\nYhteensä tulot: " << fixed << setprecision(2) << totalIncome << " €" << endl;
	cout << "Yhteensä kulut: " << fixed << setprecision(2) << totalExpense << " €" << endl;
	cout << "Saldo: " << fixed << setprecision(2) << (totalIncome - totalExpense) << " €" << endl;
}


// Main function
int main() {

	// Initialize the money management system
	ensiRuutu();

	// Vectors to store incomes and expenses
	vector<pair<string, double>> incomes;
	vector<pair<string, double>> expenses;

	// Load previously saved data if needed
	// Read from a file or database here if necessary
	// We'll start reading from a file
	ifstream infile("data.txt");
	if (infile.is_open()) {
		string line;
		while (getline(infile, line)) {
			istringstream iss(line);
			string type, description;
			double amount;
			iss >> type >> description >> amount;

			if (type == "Tulo") {
				incomes.push_back(make_pair(description, amount));
			} else if (type == "Kulu") {
				expenses.push_back(make_pair(description, amount));
			}
		}
		infile.close();
		cout << "Aiemmat tiedot ladattu onnistuneesti." << endl;
	} else {
		cout << "Ei aiempia tietoja ladattavaksi." << endl;
	}

	// Seed the random number generator for any future use
	srand(static_cast<unsigned int>(time(0)));

	// Display the initial summary if there are any incomes or expenses
	if (!incomes.empty() || !expenses.empty()) {
		näytäYhteenveto(incomes, expenses);
	} else {
		cout << "Ei aiempia tuloja tai kuluja." << endl;
		cout << "Aloita lisäämällä tuloja tai kuluja." << endl;
	}

	// Main loop for the money management system
	while (true) {
		// Display the menu
		näytäMenu();

		// Get user choice
		int choice;
		cout << "Valintasi: ";
		cin >> choice;

		switch (choice) {
			case 1:
				lisääTulo(incomes);
				break;
			case 2:
				lisääKulu(expenses);
				break;
			case 3:
				näytäYhteenveto(incomes, expenses);
				break;
			case 4: {
				// Save data to a file before exiting
				ofstream outfile("data.txt");
				if (outfile.is_open()) {
					for (const auto& income : incomes) {
						outfile << "Tulo " << income.first << " " << income.second << endl;
					}
					for (const auto& expense : expenses) {
						outfile << "Kulu " << expense.first << " " << expense.second << endl;
					}
					outfile.close();
					cout << "Tiedot tallennettu onnistuneesti." << endl;
				} else {
					cout << "Virhe tiedoston tallentamisessa." << endl;
				}
				return 0; // Exit the program
			}
			default:
				cout << "Virheellinen valinta, yritä uudelleen." << endl;
				break;
		}

	}

	// Clean up and exit
	return 0;
}

// End of the Money Management System code
// Generated by OpenAI's GPT-3, on 2025-07-15
