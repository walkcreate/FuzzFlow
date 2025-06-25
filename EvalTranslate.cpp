#include <string_view>

#include "translator.h"

int main(int argc, char* argv[])
{
    std::string_view script_path;

    script_path = "WebKit_JSTests_es6_Map_Map.prototype.forEach.js";

    FuzzFlow::js2multiGraphs2js(script_path);

    return 0;
}
