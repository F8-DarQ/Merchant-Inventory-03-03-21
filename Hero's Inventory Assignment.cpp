// Hero's Inventory Assignment
// Created by Justin Richard on 03-03-2021

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::setw;
using std::distance;

int askNumber(string question, int high, int low);
void displayInventory(const vector<string>& inventory, const vector<int>& stock, const vector<int>& prices);


int main() {
	vector<string> merchantInventory;
	merchantInventory.push_back("Iron Sword");
	merchantInventory.push_back("Iron Shield");
	merchantInventory.push_back("Health Potion");
	merchantInventory.push_back("Mana Potion");

	vector<int> merchantStock;
	merchantStock.push_back(1);
	merchantStock.push_back(1);
	merchantStock.push_back(99);
	merchantStock.push_back(99);

	vector<int> merchantPrices;
	merchantPrices.push_back(100);
	merchantPrices.push_back(50);
	merchantPrices.push_back(20);
	merchantPrices.push_back(10);

	float merchantBuyBackRate = 0.5;

	vector<string> playerInventory;
	playerInventory.push_back("Wooden Sword");
	playerInventory.push_back("Wooden Shield");
	playerInventory.push_back("Empty Bottle");
	playerInventory.push_back("Hegemony Artifact");
	
	vector<int> playerStock;
	playerStock.push_back(1);
	playerStock.push_back(1);
	playerStock.push_back(50);
	playerStock.push_back(1);

	vector<int> playerPrices;
	playerPrices.push_back(20);
	playerPrices.push_back(20);
	playerPrices.push_back(1);
	playerPrices.push_back(500);

	int playerGold = 300;

	cout << "_______________________________" << endl;
	cout << "   _____ _    _  ____  _____  " << endl;
	cout << "  / ____| |  | |/ __ \\|  __ \\ " << endl;
	cout << " | (___ | |__| | |  | | |__) |" << endl;
	cout << "  \\___ \\|  __  | |  | |  ___/ " << endl;
	cout << "  ____) | |  | | |__| | |     " << endl;
	cout << " |_____/|_|  |_|\\____/|_|     " << endl;
	cout << "_______________________________" << endl << endl;
	cout << "Welcome Adventurer, what can I do for you?" << endl;

	int choice;

	do {
		cout << endl << "1. Buy from merchant" << endl;
		cout << "2. Sell to merchant" << endl;
		cout << "3. View inventory" << endl;
		cout << "4. View merchants inventory" << endl;
		cout << "0. Quit" << endl << endl;

		cout << "Gold: " << playerGold << endl;
		choice = askNumber("Your choice?", 4, 0);

			switch (choice) {
			case 1: { //buy from merchant
				cout << endl << "What do you need?" << endl;
				displayInventory(merchantInventory, merchantStock, merchantPrices);
				int choice2 = askNumber("Your Choice?", merchantInventory.size(), 0);

				if (!(merchantStock[choice2 - 1])) {
					cout << endl << "I'm sorry, but that item is out of stock." << endl;
					break;
				}
				if (!(playerGold > merchantPrices[choice2 - 1])) {
					cout << endl << "What are you trying to pull here? You don't have enough gold for that." << endl;
					break;
				}

				playerGold -= merchantPrices[choice2 - 1];
				merchantStock[choice2 - 1]--;
				vector<string>::iterator it;

				it = find(playerInventory.begin(), playerInventory.end(), merchantInventory[choice2 - 1]);
				if (it != playerInventory.end()) {
					int index = distance(playerInventory.begin(), it);
					playerStock[index]++;
				} else {
					playerInventory.push_back(merchantInventory[choice2 - 1]);
					playerStock.push_back(1);
					playerPrices.push_back(merchantPrices[choice2 - 1]);
				}
				break;
			}
			case 2: { //sell to merchant
				cout << endl << "What have you got to sell?" << endl;
				displayInventory(playerInventory, playerStock, playerPrices);
				int choice3 = askNumber("Your Choice? ", playerInventory.size(), 0);

				playerGold += (merchantBuyBackRate * playerPrices[choice3 - 1]);
				playerStock[choice3 - 1]--;
				vector<string>::iterator it;

				it = find(merchantInventory.begin(), merchantInventory.end(), playerInventory[choice3 - 1]);
				if (it != merchantInventory.end()) {
					int index = distance(merchantInventory.begin(), it);
					merchantStock[index]++;
				} else {
					merchantInventory.push_back(playerInventory[choice3 - 1]);
					merchantStock.push_back(1);
					merchantPrices.push_back(playerPrices[choice3 - 1]);
				}
				if (playerStock[choice3 - 1] == 0) {
					playerInventory.erase(playerInventory.begin() + choice3 - 1);
					playerStock.erase(playerStock.begin() + choice3 - 1);
					playerPrices.erase(playerPrices.begin() + choice3 - 1);
				}
				break;
			}
			case 3: { //view player inventory
				cout << endl << "Viewing Your Inventory" << endl;
				displayInventory(playerInventory, playerStock, playerPrices);
				break;
			}
			case 4: { //view merchant inventory
				cout << endl << "Viewing Merchants Inventory" << endl;
				displayInventory(merchantInventory, merchantStock, merchantPrices);
				break;
			}
			case 0: { //quit menu
				cout << endl << "Pleasure doing business, come back any time!" << endl;
				break;
			}
			default: {
				cout << endl <<"ERROR: Invalid choice... You shouldn't be able to see this." << endl;
				break;
			}
		}
	} while (choice != 0);
	return 0;
}

int askNumber(string question, int high, int low) {
	int number;
	do {
		cout << question << " (" << low << " - " << high << " ): ";
		cin >> number;
	} while (number > high || number < low);
	return number;
}

void displayInventory(const vector<string>& inventory, const vector<int>& stock, const vector<int>& prices) {

	cout << setw(3) << "#  " << setw(20) << "ITEM NAME" << setw(10) << "STOCK" << setw(10) << "PRICE" << endl;

	for (int i = 0; i < inventory.size(); i++) {
		cout << i + 1 << ". " << setw(20) << inventory[i];
		if (stock[i] != 0) {
			cout << setw(10) << stock[i] << setw(10) << prices[i] << endl;
		} else {
			cout << setw(10) << "SOLD OUT" << setw(10) << prices[i] << endl;
		}
	}
}

