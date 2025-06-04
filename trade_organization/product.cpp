#include "product.hpp"

product::product(const string name, const string type)
:
_name(name),
_type(type)
{}
product::product(const unsigned int id, const string name, const string type)
:
entity(id),
_name(name),
_type(type)
{}

string product::get_name() const { return _name; } 
string product::get_type() const { return _type; }
