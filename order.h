#ifndef ORDER_H
#define ORDER_H 

#include <string>

using namespace std;

class Order
{
private:
	int id;
	string coffee_name;
	char coffee_size;
	int quantity;

public:
	//getters
	int get_id();
	string get_coffee_name();
	char get_coffee_size();
	int get_quantity();

	//setters
	void set_ID(int);

	//default/nondefault constructors --- no dynamic memory allocated so deconstructors are unneccessary
	Order();
	Order(int, string, char, int);

};
#endif