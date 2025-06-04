#include <stdexcept>
#include "exit_command.hpp"

using namespace std;

void exit_command::execute()
{
    throw runtime_error("Exit");
}
