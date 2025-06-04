#pragma once
#include <string>
#include <vector>
#include "entity.hpp"

using namespace std;

class customer : public entity
{
public:
    customer(const string name, const string phone_number);
    customer(const unsigned int id, const string name, const string phone_number, 
        vector<unsigned int>& sale_ids);

    string get_name() const;
    string get_phone_number() const;
    const vector<unsigned int>& get_sale_ids() const;

    void add_sale_id(const unsigned int id);

private:
    string _name;
    string _phone_number;
    vector<unsigned int> _sale_ids;

};
