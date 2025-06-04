#pragma once
#include <string>
#include "entity.hpp"

using namespace std;

struct section_st
{
    string manager_first_name;
    string manager_middle_name;
    string manager_last_name;
    unsigned int floor_number;
};

class section : public entity
{
public:
    section(const string manager_first_name, const string manager_middle_name, 
        const string manager_last_name, const unsigned int floor_number);
    section(const unsigned int id, const string manager_first_name, 
        const string manager_middle_name, const string manager_last_name, 
        const unsigned int floor_number);

    string get_manager_first_name() const;
    string get_manager_middle_name() const;
    string get_manager_last_name() const;
    unsigned int get_floor_number() const;

private:
    string _manager_first_name;
    string _manager_middle_name;
    string _manager_last_name;
    unsigned int _floor_number;
    
};
