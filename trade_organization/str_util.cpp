#include <sstream>
#include <string>
#include <vector>
#include "str_util.hpp"

string str_util::join(const vector<unsigned int>& vec, const char sep)
{
    if (vec.size() == 0)
        return "";

    string out = to_string(vec[0]);
    for (unsigned int i = 1; i < vec.size(); ++i)
        out += sep + to_string(vec[i]);

    return out;
}
vector<unsigned int> str_util::split(const string& str, const char sep)
{
    vector<unsigned int> out;
    stringstream ss(str);
    string item;

    while (getline(ss, item, sep))
        if (!item.empty())
            out.push_back(stoul(item));

    return out;
}
vector<string> str_util::split_str(const string& str, const char sep)
{
    vector<string> out;
    stringstream ss(str);
    string item;

    while (getline(ss, item, sep))
        out.push_back(item);

    return out;
}
