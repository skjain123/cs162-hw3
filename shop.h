#ifndef SHOP_H
#define SHOP_H

#include <string>
#include <fstream>
#include <iostream>
#include "menu.h"
#include "order.h"

using namespace std;

class Shop {
  private:
    Menu m;
    string phone;
    string address; 
    float revenue;      //shop revenue
    Order *order_arr;   //order array
    int num_orders;     //number or orders
  public:
    //need to include accessor functions and mutator functions for private member when appropriate
    //need to include constructors and destructors where appropriate
    //need to use 'const' when appropriate

    //Suggested functions
    void load_data(); //reads from files to correctly populate coffee, menu, etc.
    void view_shop_detail(); //prints info, menu info, and order info
    void add_to_menu(); //adds a coffee to menu
    void remove_from_menu(); //removes a coffee from menu
    void search_by_name(); //search coffee from menu using a user inputted name
    void search_by_price(); //search coffee from menu using a user inputted budget
    void place_order(); //place an order based on the menu
    Shop clone_shop(); //clone shop testing
    
    //pull data from files
    void inport_shop_info(); //shop_info.txt

    void inport_menu_info(); //menu.txt
    
    void inport_order_info(); //orders.txt
    void load_orders(fstream& fin);

    //setters
    void set_num_order(int); //number of orders

    //dynamically allocate memory to order array
    Order* inport_order_arr(int);
    
    //adding an order -> checking valid inputs -> confirming orders -> updating the revenue -> exporting to file
    void add_order(Order o);
    bool check_print_coffee(Coffee); //check if user inputted coffee exists
    bool check_order_input(char);
    void confirm_order(Coffee c, string c_name, char c_size, int q);
    void update_revenue(char, Coffee, int);
    void export_orders();
    
    //constructors/copy/deconstructors
    Shop();
    Shop(const Shop&);
    Shop& operator=(Shop const& s);
    ~Shop();
    
};

#endif
