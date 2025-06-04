#include "section.hpp"

section::section(const string manager_first_name, const string manager_middle_name, 
        const string manager_last_name, const unsigned int floor_number)
:
_manager_first_name(manager_first_name),
_manager_middle_name(manager_middle_name),
_manager_last_name(manager_last_name),
_floor_number(floor_number)
{}
section::section(const unsigned int id, const string manager_first_name, 
        const string manager_middle_name, const string manager_last_name, 
        const unsigned int floor_number)
:
entity(id),
_manager_first_name(manager_first_name),
_manager_middle_name(manager_middle_name),
_manager_last_name(manager_last_name),
_floor_number(floor_number)
{}

string section::get_manager_first_name() const { return _manager_first_name; }
string section::get_manager_middle_name() const { return _manager_middle_name; }
string section::get_manager_last_name() const { return _manager_last_name; }
unsigned int section::get_floor_number() const { return _floor_number; }
