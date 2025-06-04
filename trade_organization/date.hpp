#pragma once
#include <string>

using namespace std;

class date
{
public:
    date();
    date(const string str_date); // DD-MM-YYYY

    bool operator>(const date& obj) const;
    bool operator<(const date& obj) const;
    float operator-(const date& obj) const; 

    string to_string() const;

private:
    unsigned int _day;
    unsigned int _month;
    unsigned int _year;
    string _str_date;

};
