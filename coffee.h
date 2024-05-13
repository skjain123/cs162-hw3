#ifndef COFFEE_H
#define COFFEE_H

#include <string>
#include <fstream>

using namespace std;

class Coffee {
  private:
    string name;
    float small_cost;
    float medium_cost;
    float large_cost;
    
  public:
    //getters
    string get_name();
    float get_small_cost();
    float get_medium_cost();
    float get_large_cost();

    //setters
    void set_name(const string);
    void set_small_cost(const float);
    void set_medium_cost(const float);
    void set_large_cost(const float);

    //constructors/copying/destructors
    Coffee();
    Coffee(string name, float small_cost, float medium_cost, float large_cost);
    Coffee(const Coffee&);
    Coffee& operator=(const Coffee&);
    ~Coffee();
};

#endif