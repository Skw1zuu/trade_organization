#include "seller.hpp"

seller::seller(const string first_name, const string middle_name,
       const string last_name, const string phone_number, const float salary)
:
_first_name(first_name),
_middle_name(middle_name),
_last_name(last_name),
_phone_number(phone_number),
_salary(salary)
{}
seller::seller(const unsigned int id, const string first_name, const string middle_name, 
       const string last_name, const string phone_number, const float salary)
:
entity(id),
_first_name(first_name),
_middle_name(middle_name),
_last_name(last_name),
_phone_number(phone_number),
_salary(salary)
{}

string seller::get_first_name() const { return _first_name; }
string seller::get_middle_name() const { return _middle_name; }
string seller::get_last_name() const { return _last_name; }
string seller::get_phone_number() const { return _phone_number; }
float seller::get_salary() const { return _salary; }
