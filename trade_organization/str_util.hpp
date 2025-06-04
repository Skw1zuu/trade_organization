#include <string>
#include <vector>

using namespace std;

class str_util
{
public:
    static string join(const vector<unsigned int>& vec, const char sep = ' ');
    static vector<unsigned int> split(const string& str, const char sep = ' ');
    static vector<string> split_str(const string& str, const char sep = ' ');

};
