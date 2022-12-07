#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main() {
	string Legendary[3] = { "first legendary item", "second legendary item", "third legendary item" };
	string Epic[6] = { "first epic object","second epic object" ,"third epic object" ,"fourth epic object" ,"fifth epic object" ,"sixth epic object" };
	string Rare[5] = { "first rare object","second rare object" ,"third rare object" ,"fourth rare object" ,"fifth rare object" };
	srand(time(0));
	int pull;
	int rarity = rand() % 1000;
	if (0 <= rarity && rarity < 5) {
		rarity = 3; // Legendary
	} else if (5 <= rarity && rarity < 99) {
		rarity = 2; // Epic
	} else {
		rarity = 1; // Rare
	}
	cout << "Rarete : " << rarete_name << " | Numero tire : " << rarity << endl;

	switch (rarity) {
		case 1:
			pull = rand() % Rare->length();
			cout << "You pulled the " << Rare[pull];
			break;
		case 2:
			pull = rand() % Epic->length();
			cout << "You pulled the " << Epic[pull];
			break;
		case 3:
			pull = rand() % Legendary->length();
			cout << "You pulled the " << Legendary[pull];
			break;
		default:
			cout << "Error, please retry or contact an administrator";
			break;
	}
}