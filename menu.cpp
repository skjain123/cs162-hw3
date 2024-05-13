#include "menu.h"
#include <iostream>
#include <string>

using namespace std;


Coffee Menu::search_coffee_by_name(string name) { //input a name
	Coffee found("null", -1, -1,-1); //default coffee to return if not found
	
	for (int i = 0; i < this->num_coffee; i++) { //go through the menu
		if (this->coffee_arr[i].get_name() == name) { //if the coffee name matches, return that coffee
			return coffee_arr[i];
		}
	} 

	return found; //return default coffee if none are found with inputted name
}


Menu Menu::search_coffee_by_price(float budget){
	Menu temp; //temporary menu that holds coffees filtered by a budget.
	
	for (int i = 0; i < this->num_coffee; i++) {
		if (this->coffee_arr[i].get_large_cost() <= budget) { //if any of the 3 size prices are less than the budget add the coffee to temp
			temp.add_to_menu(this->coffee_arr[i]);
		} else if (this->coffee_arr[i].get_medium_cost() <= budget) {
			temp.add_to_menu(this->coffee_arr[i]);
		} else if (this->coffee_arr[i].get_small_cost() <= budget) {
			temp.add_to_menu(this->coffee_arr[i]);
		}
	}	

	return temp; //return filtered menu

}

void Menu::add_to_menu(Coffee& coffee_to_add) { //input a coffee constructed using user inputs
	this->num_coffee++;	//increase the amount of coffees

	Coffee* other_arr = inport_coffee_arr(num_coffee); //dynamically allocate memory in a temp array

	for (int i = 0; i < this->num_coffee; i++) { //go through new array and copy each original coffee along with the new coffee to temp array
		if (i == num_coffee - 1) {
			other_arr[i] = coffee_to_add;
		} else {
			other_arr[i] = coffee_arr[i];
		}
	}

	delete[] coffee_arr; //delete original array
	this->coffee_arr = other_arr; //make the temp array the original
}

void Menu::remove_from_menu(int index_of_coffee_on_menu){ //user input specified index
	this->num_coffee--; //decrease the number of coffees

	Coffee* other_arr = inport_coffee_arr(num_coffee); //create temp array
	
	for (int i = 0; i < num_coffee + 1; i++) {
		if (i < index_of_coffee_on_menu) { //copy every coffee except the one at the specified index
			other_arr[i] = this->coffee_arr[i];
		} else if (i > index_of_coffee_on_menu) {
			other_arr[i-1] = this->coffee_arr[i];
		}
	}

	delete[] this->coffee_arr; //delete original
	this->coffee_arr = other_arr; //make the copy the original
}

int Menu::get_num_coffee() {
	return this->num_coffee; //return the number of coffees in the array
}

Coffee* Menu::get_coffee_arr() {
	return this->coffee_arr; //return the array of coffees
}

void Menu::set_num_coffee(int num) {
	this->num_coffee = num; //set the number of coffees to user specified num
}

void Menu::load_menu(fstream& fin) { //from the file get the menu
	string name; //temp variables
	float small_cost;
	float medium_cost;
	float large_cost;

	for (int i = 0; i < this->num_coffee; i++) {
		fin >> name; //get these temp variables from file
		fin >> small_cost;
		fin >> medium_cost;
		fin >> large_cost;

		//construct coffee and add it using the temp file variables
		this->coffee_arr[i] = Coffee(name, small_cost, medium_cost, large_cost);
	}
}

void Menu::export_menu() {
	ofstream fout; //export menu to the file (not appending)
	fout.open("menu.txt");

	fout << this->num_coffee << endl; //output the number of cofffees

	for (int i = 0; i < this->num_coffee; i++) { //output each coffee and its info separated by spaces
		fout << this->coffee_arr[i].get_name() << " ";
		fout << this->coffee_arr[i].get_small_cost() << " ";
		fout << this->coffee_arr[i].get_medium_cost() << " ";
		fout << this->coffee_arr[i].get_large_cost() << " " << endl;
	}

	fout.close();
}

void Menu::print_menu() {
	cout << endl << "Menu: " << endl << endl;

	if (this->num_coffee == 0) { //if there are no coffees in the menu, print theres no coffees
		cout << "No Coffee that satisfies requirements in Menu!" << endl;
	}

	for (int i = 0; i < this->num_coffee; i++) { //if there are, print all the coffees and thier information out
		cout << "Coffee Name: " << this->coffee_arr[i].get_name() << endl;
		cout << "Small Cost: " << this->coffee_arr[i].get_small_cost() << endl;
		cout << "Medium Cost: " << this->coffee_arr[i].get_medium_cost() << endl;
		cout << "Large Cost: " << this->coffee_arr[i].get_large_cost() << endl << endl;
	}
	cout << endl;
}

Coffee* Menu::inport_coffee_arr(int num) { //dynamically allocate memory for a coffee array
	return new Coffee[num];
}

Menu::Menu() { //default constructor initializing values
	this->num_coffee = 0;
	this->coffee_arr = new Coffee[0];
}

Menu::Menu(int size) { //non default constructor initializing specialized values
	this->num_coffee = size;
	this->coffee_arr = new Coffee[size];
}

Menu::~Menu() { //deconstructor getting rid of the dynamically allocated memory
	delete[] this->coffee_arr;
}

Menu::Menu(const Menu&) { //copy constructor?
	this->num_coffee = 0;
	this->coffee_arr = new Coffee[0];
}

Menu& Menu::operator=(Menu const& m) { //AOO deleting original coffee array and then cloning it
	delete[] this->coffee_arr;
	this->coffee_arr = this->inport_coffee_arr(m.num_coffee);
	this->num_coffee = m.num_coffee;
	
	return *this;
}

