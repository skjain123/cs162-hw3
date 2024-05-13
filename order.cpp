#include "order.h"

using namespace std;

int Order::get_id() { //ID
    return this->id;
}

string Order::get_coffee_name() { //name
    return this->coffee_name;
}

char Order::get_coffee_size() { //size
    return this->coffee_size;
}

int Order::get_quantity() { //quanitity
    return this->quantity;
}

void Order::set_ID(int num) { //set specialized ID
    this->id = num;
}

Order::Order() { //default constructor initializing values
    this->id = 0;
    this->coffee_name = " ";
    this->coffee_size = 'N';
    this->quantity = 0;
}

Order::Order(int ID, string c_name, char c_size, int q) { //non default constructor initializing specialized values
    this->id = ID;
    this->coffee_name = c_name;
    this->coffee_size = c_size;
    this->quantity = q;
}