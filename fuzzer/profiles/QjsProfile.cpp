#include "QjsProfile.h"

#include <vector>

using std::string;
using std::vector;

namespace FuzzFlow {

vector<string> QjsProfile::get_process_arguments(bool randomizing_args)
{
    return {"--reprl"};
}

} /// end of namespace FuzzFlow