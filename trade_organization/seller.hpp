#pragma once
#include <string>
#include "entity.hpp"

using namespace std;

class seller : public entity
{
public:
    seller(const string first_name, const string middle_name, const string last_name,
        const string phone_number, const float salary);
    seller(const unsigned int id, const string first_name, const string middle_name, 
        const string last_name, const string phone_number, const float salary);
    
    string get_first_name() const;
    string get_middle_name() const;
    string get_last_name() const;
    string get_phone_number() const;
    float get_salary() const;

private:
    string _first_name;
    string _middle_name;
    string _last_name;
    string _phone_number;
    float _salary;
    
};