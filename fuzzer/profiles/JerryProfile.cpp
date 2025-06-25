#include "JerryProfile.h"

#include <vector>

using std::string;
using std::vector;

namespace FuzzFlow {

vector<string> JerryProfile::get_process_arguments(bool randomizing_args)
{
    return {"--reprl-fuzzilli"};
}

} /// end of namespace FuzzFlow