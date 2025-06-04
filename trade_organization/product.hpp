#pragma once
#include <string>
#include "entity.hpp"

using namespace std;

struct product_st
{
    string product_name;
    string product_type;
};

class product : public entity
{
public:
    product(const string name, const string type);
    product(const unsigned int id, const string name, const string type);

    string get_name() const;
    string get_type() const;

private:
    string _name;
    string _type;

};
