#include "shop.h"

using namespace std;

//function defintions from shop.h goes here

void Shop::load_data(){
	//reads from files to correctly populate coffee, menu, etc.
	this->inport_shop_info();
	this->inport_menu_info();
	this->inport_order_info();

	return;
}

void Shop::view_shop_detail(){
	//handle "View shop detail" option
	//print shop address, phone number, revenue, menu, and order
	//Your code goes here: 
	cout << endl << "Shop Information: " << endl << endl;

	//print the shop information
	cout << "Phone Number: " << this->phone << endl;
	cout << "Address: " << this->address << endl;
	cout << "Revenue: " << this->revenue << endl << endl;

	this->m.print_menu(); //print the coffees available

	//print the order information
	cout << "Order Information: " << endl << endl;

	if (this->num_orders == 0) { //if there are none then say theres none
		cout << "No Orders in the Shop!" << endl << endl;
	}

	//print the orders 
	for (int i = 0; i < this->num_orders; i++) {
		cout << endl << "ID: " << this->order_arr[i].get_id() << endl;
		cout << "Coffee Name: " << this->order_arr[i].get_coffee_name() << endl;
		cout << "Coffee Size: " << this->order_arr[i].get_coffee_size() << endl;
		cout << "Quantity: " << this->order_arr[i].get_quantity() << endl << endl;
	}

	return;
}


void Shop::add_to_menu(){ //prompt for the new coffee's information and construct one and add it
	//prompting and getting information assuming that the user types in correct data type
	cout << "What is the name of the new coffee: ";
	string n;
	cin >> n;

	cout << "What is the price of the small size: ";
	float s_cost;
	cin >> s_cost;

	cout << "What is the price of the medium size: ";
	float m_cost;
	cin >> m_cost;

	cout << "What is the price of the large size: ";
	float l_cost;
	cin >> l_cost;


	//construct coffee using information
	Coffee new_c = Coffee(n, s_cost, m_cost, l_cost);

	//add the coffee to the program menu and export it to the actual file
	this->m.add_to_menu(new_c);
	this->m.export_menu();
}

void Shop::remove_from_menu(){ //remove a coffee from the menu by name
	
	//get the name of the coffee the user wants to delete
	string del_coffee; 
	cout << "Enter the name of the coffee to delete: ";
	cin >> del_coffee;

	bool found = false;

	for (int i = 0; i < this->m.get_num_coffee(); i++) { //go through the menu
		if (this->m.get_coffee_arr()[i].get_name() == del_coffee) { //compare the names 
			found = true; //if there are coffees by that name, remove it and set found to true.
			this->m.remove_from_menu(i);
			this->m.export_menu(); //remove from file
		}
	}
	if (!found) { //if the user inputs a name of a coffee that doesnt exist, say so.
		cout << endl << "No coffee on menu by that name to delete!" << endl;
	}
}

void Shop::search_by_name(){
	//handle "Search by coffee name" option
	//Hint: call Menu::search_coffee_by_name(string name);
	//Your code goes here: 

	string n; //get user input
	cout << "Input the name of the coffee you would like to search: ";
	cin >> n;

	//search menu for that name and get a coffee
	Coffee c = this->m.search_coffee_by_name(n);
	
	//if that coffee's name is not "null" or if it couldnt be found with the user input, then say so.
	this->check_print_coffee(c);
}

void Shop::search_by_price(){
	//handle "Search by coffee price" option
	//Hint: call Menu::search_coffee_by_price(float budget);
	//Your code goes here: 
	
	//get user input
	float budget;
	cout << "Please input your budget: ";
	cin >> budget;

	//using the budget, search for coffees that has a price less than the budget and print that menu of coffees
	Menu t = this->m.search_coffee_by_price(budget);
	t.print_menu(); //print
}

void Shop::place_order() {
	//handle "Place order" option
	//Your code goes here: 

	//temporary variables to construct the order from
	Coffee c;
	string c_name;
	char c_size;
	int q;
	
	//order a coffee by its name (reusing the search_coffee_by_name() function)

	cout << "Input the coffee name you would like to order: "; //user input for name
	cin >> c_name;
	c = this->m.search_coffee_by_name(c_name);
	c_name = c.get_name();
	if (check_print_coffee(c)) { //did the search_coffee_by_name() return a coffee whose name is not "null"?
		cout << "Input the size of the coffee you would like (S-Small, M-Large, L-Large): "; //user input for character size
		cin >> c_size;
		if(this->check_order_input(c_size)) { //is the character inputted either S, M, or L
			cout << "Input the amount of this you want to buy: ";
			cin >> q;

			this->confirm_order(c, c_name, c_size, q); //prompt the user if they want to buy the coffee after seeing price
		}
	}
}

Shop Shop::clone_shop() {
	//handle "Clone a shop" option
	//note: the purpose of this option is to test
	//your big three implementation
	Shop cloned_shop;

	cloned_shop = *this; // test AOO        

    Shop cloned_shop2 = *this; // test CC 

    cout << "Shop cloned successfully!" << endl; 

    return cloned_shop;
}

void Shop::inport_shop_info() { //pull info from "shop_info.txt"
	fstream fin;
	fin.open("shop_info.txt");
	getline(fin, this->phone);
	getline(fin, this->address);
	fin.close();
}

void Shop::inport_menu_info() { //pull info from "menu.txt"
	fstream fin;
	int coffee_num;
	fin.open("menu.txt");
	fin >> coffee_num;
	this->m = Menu(coffee_num);
	this->m.load_menu(fin);
	fin.close();
}

void Shop::inport_order_info() { //pull info from "orders.txt"
	fstream fin;
	fin.open("orders.txt");
	fin >> this->num_orders;
	
	this->order_arr = inport_order_arr(this->num_orders); //?
	this->load_orders(fin);
	fin.close();
}

void Shop::load_orders(fstream& fin) { //get orders from file
	int id;
	string coffee_name;
	char coffee_size;
	int quantity;

	for (int i = 0; i < this->num_orders; i++) {
		fin >> id;
		fin >> coffee_name;
		fin >> coffee_size;
		fin >> quantity;
	
		this->order_arr[i] = Order(id, coffee_name, coffee_size, quantity); //construct new order with pulled info

		//for that order, calculate the cost and add to the revenue
		update_revenue(this->order_arr[i].get_coffee_size(), this->m.search_coffee_by_name(this->order_arr[i].get_coffee_name()), this->order_arr[i].get_quantity());
	}
	
}

void Shop::set_num_order(int num) { //set the number of orders
	this->num_orders = num;
}

Order* Shop::inport_order_arr(int num) { //dynamically allocate order array
	return new Order[num];
}

void Shop::add_order(Order o) { //takes order, and adds it to the order array
	this->num_orders++; //increase the number of orders stored in the array
	
	Order* other_arr = new Order[this->num_orders]; //make temp array

	for (int i = 0; i < this->num_orders; i++) { //go through the original array and add it to the temp and add the new order to the last position
		if (i == num_orders - 1) {
			other_arr[i] = o;
		} else {
			other_arr[i] = order_arr[i];
		}
		other_arr[i].set_ID(i+1); //set the ID's of the orders using the for loop
	}

	delete[] order_arr; //delete original array
	//this->coffee_arr = inport_coffee_arr(this->num_coffee);
	this->order_arr = other_arr; //clone temp array to the original array
}

bool Shop::check_print_coffee(Coffee c) { //if the coffee's name is not "null" then print out the coffee info
	if (c.get_name() != "null") {
		cout << endl << "Coffee Name: " << c.get_name() << endl;
		cout << "Small Cost: " << c.get_small_cost() << endl;
		cout << "Medium Cost: " << c.get_medium_cost() << endl;
		cout << "Large Cost: " << c.get_large_cost() << endl << endl;
		return true;
	} else { //show the user that the user input did not match any coffee available
		cout << "No coffee by that name!" << endl;
		return false;
	}
}

bool Shop::check_order_input(char c_size) { //check if the user input for the order's size is correct 
	if (c_size == 'S' || c_size == 'M' || c_size == 'L') {
		return true;
	} else { //if incorrect input, please reprompt
		cout << "Invalid size input! Please input (S-Small, M-Large, L-Large)!" << endl;
		return false;
	}
}

void Shop::confirm_order(Coffee c, string c_name, char c_size, int q) { //tell user the price of their order and ask for confirmation
	float cost;
	bool confirm = false;

	//tell the user the price of the order
	if (c_size == 'S') cost = c.get_small_cost()*q;
	if (c_size == 'M') cost = c.get_medium_cost()*q;
	if (c_size == 'L') cost = c.get_large_cost()*q;
	cout << "Your total is: " << cost << "." << endl;
	
	//ask for confirmation
	cout << "Confirmed? 1-yes, 0-no: ";
	cin >> confirm;
	if (confirm) { //if yes, then add the order
		this->add_order(Order(this->num_orders, c_name, c_size, q));
		this->export_orders();
		this->update_revenue(c_size, c, q);
		cout << "Your order number is: " << this->num_orders << endl;
	}

}

//for each order, add its revenue to the shop
void Shop::update_revenue(char c_size, Coffee c, int q) { 
	if (c_size == 'S') {
		this->revenue += c.get_small_cost()*q;
	} else if (c_size == 'M') {
		this->revenue += c.get_medium_cost()*q;
	} else if (c_size == 'L') {
		this->revenue += c.get_large_cost()*q;
	}
}

void Shop::export_orders() { //export orders to the file
	ofstream fout;
	
	fout.open("orders.txt");

	fout << this->num_orders << endl; //export number of orders on first line
	for (int i = 0; i < this->num_orders; i++) { // export orders and info using space separation
		fout << this->order_arr[i].get_id() << " ";
		fout << this->order_arr[i].get_coffee_name() << " ";
		fout << this->order_arr[i].get_coffee_size() << " ";
		fout << this->order_arr[i].get_quantity() << " " << endl;
	}

	fout.close();
}

Shop::Shop() { //default constructor automatically loading in data from the files and initializing values
	this->num_orders = 0;
	this->load_data();
}

Shop& Shop::operator=(Shop const& s) { //AOO
	
	if (this != &s) {
		this->m = s.m;
		this->phone = s.phone;
		this->address = s.address;
		this->revenue = s.revenue;
		this->num_orders = s.num_orders;
	}

	if (s.order_arr == nullptr) {
		for (int i = 0; i < s.num_orders; i++) {
			this->order_arr[i] = s.order_arr[i];
		}
	} else {
		this->order_arr = nullptr;
	}

	return *this;
}

Shop::Shop(const Shop& s) { //CC

	this->m = s.m;
	this->phone = s.phone;
	this->address = s.address;
	this->revenue = s.revenue;
	this->num_orders = s.num_orders;

	if (s.order_arr == nullptr) {
		for (int i = 0; i < s.num_orders; i++) {
			this->order_arr[i] = s.order_arr[i];
		}
	} else {
		this->order_arr = nullptr;
	}
	
}

Shop::~Shop() { //deconstructor deleting dynamic order array
	delete[] this->order_arr;
}