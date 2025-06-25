#ifndef FUZZFLOW_SEEDCOMMENTS_H
#define FUZZFLOW_SEEDCOMMENTS_H

#include <string>
#include <map>

using std::string;
using std::map;

namespace FuzzFlow {

enum class CommentPosition {
    header,
    footer
};

class SeedComments {
public:
    static int header_index;
    static int footer_index;

    map<int, string> comments;

    string header_comments;
};

} /// end of namespace

#endif //FUZZFLOW_SEEDCOMMENTS_H
