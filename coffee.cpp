#include "coffee.h"
#include <iostream>

using namespace std;


string Coffee::get_name() {
    return this->name;
}
float Coffee::get_small_cost() {
    return this->small_cost;
}
float Coffee::get_medium_cost() {
    return this->medium_cost;
}
float Coffee::get_large_cost() {
    return this->large_cost;
}

void Coffee::set_name(const string s) {
    this->name = s;
}
void Coffee::set_small_cost(const float f) {
    this->small_cost = f;
}
void Coffee::set_medium_cost(const float f) {
    this->medium_cost = f;
}
void Coffee::set_large_cost(const float f) {
    this->large_cost = f;
}

Coffee::Coffee() { //initialize values
    this->set_name(" ");
    this->set_small_cost(0);
    this->set_medium_cost(0);
    this->set_large_cost(0);
}

Coffee::Coffee(string n, float small, float medium, float large) { //initialize specialized values
    this->set_name(n);
    this->set_small_cost(small);
    this->set_medium_cost(medium);
    this->set_large_cost(large);
}

Coffee::Coffee(const Coffee& c) { //CC
    this->name = c.name;
    this->small_cost = c.small_cost;
    this->medium_cost = c.medium_cost;
    this->large_cost = c.large_cost;
}

Coffee& Coffee::operator=(const Coffee& c) { //AOO
    this->name = c.name;
    this->small_cost = c.small_cost;
    this->medium_cost = c.medium_cost;
    this->large_cost = c.large_cost;
    return *this;
}

Coffee::~Coffee() { //deconstructor does nothing because no dynamic memory
    //comment
}