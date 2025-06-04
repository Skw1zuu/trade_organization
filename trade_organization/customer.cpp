#include "customer.hpp"

customer::customer(const string name, const string phone_number)
:
_name(name),
_phone_number(phone_number)
{}
customer::customer(const unsigned int id, const string name, const string phone_number, 
    vector<unsigned int>& sale_ids)
:
entity(id),
_name(name),
_phone_number(phone_number),
_sale_ids(sale_ids)
{}

string customer::get_name() const { return _name; }
string customer::get_phone_number() const { return _phone_number; }
const vector<unsigned int>& customer::get_sale_ids() const { return _sale_ids; }
void customer::add_sale_id(const unsigned int id)
{
    _sale_ids.push_back(id);
}
