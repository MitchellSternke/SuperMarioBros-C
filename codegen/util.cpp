#include <map>
#include <set>

#include "util.hpp"

std::map<int, std::string> commentMap;
std::set<int> newlineSet;

void mapComment(int line, const std::string& comment)
{
    commentMap[line] = comment;
}

void mapNewline(int line)
{
    newlineSet.insert(line);
}
