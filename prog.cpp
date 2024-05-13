#include <iostream>
#include "display.h"

using namespace std;

int main()
{
	cout << "Welcome to Coffee++" << endl;
	int choice = -1;
	Shop s;

	while (choice != QUIT){
		choice = get_choice();
		perform_action(s, choice);
	}

	cout << "Bye!" << endl;

	return 0;
}
