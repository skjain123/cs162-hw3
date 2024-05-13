#ifndef MENU_H
#define MENU_H 

#include <string>
#include <fstream>
#include "coffee.h"

using namespace std;

class Menu {
  private:
    int num_coffee;
    Coffee* coffee_arr;
  public:
    // Suggested functions:
    Coffee search_coffee_by_name(string name); //search by name
    Menu search_coffee_by_price(float budget); //search by price
    void add_to_menu(Coffee& coffee_to_add); //add a coffee object into the Menu
    void remove_from_menu(int index_of_coffee_on_menu); //remove a coffee object from the Menu
    

    //getters
    int get_num_coffee();
    Coffee* get_coffee_arr();

    //setters
    void set_num_coffee(int);

    //import/export the menu from/to file
    void load_menu(fstream& fin);
    void export_menu();

    //print the menu
    void print_menu();

    //create dynamic array
    Coffee* inport_coffee_arr(int num);

    //constructor/copy/destructors
    Menu();
    Menu(int);
    Menu(const Menu&);
    Menu& operator=(const Menu&);
    ~Menu();

};

#endif