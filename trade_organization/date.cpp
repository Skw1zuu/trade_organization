#include <sstream>
#include <stdexcept>
#include <regex>
#include "date.hpp"

date::date()
:
_day(0),
_month(0),
_year(0),
_str_date("00-00-0000")
{}
date::date(const string str_date)
:
_str_date(str_date)
{
    regex pattern(R"(\d{2}-\d{2}-\d{4})");
    
    if (!regex_match(str_date, pattern))
        throw runtime_error("Failed to parse date: invalid date(" + str_date + 
            ") format, available - DD-MM-YYYY");

    std::stringstream ss(str_date);
    char sep;
    ss >> _day >> sep >> _month >> sep >> _year;
}

bool date::operator>(const date &obj) const
{
    if (_year != obj._year)
        return _year > obj._year;
    if (_month != obj._month)
        return _month > obj._month;
    return _day > obj._day;
}
bool date::operator<(const date &obj) const
{
    return obj > *this;
}
float date::operator-(const date &obj) const
{
    return (_day - obj._day) + (_month - obj._month) * 30 + (_year - obj._year) * 365;
}

string date::to_string() const { return _str_date; }
