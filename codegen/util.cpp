#include <cstring>
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

const char* lookupComment(int line)
{
    const char* comment = NULL;

    std::map<int, std::string>::iterator it = commentMap.find(line);
    if (it != commentMap.end())
    {
        // We need to duplicate the string since erase() removes the original copy of it
        //
        comment = duplicateString((*it).second.c_str(), strlen((*it).second.c_str()));

        // Remove the comment from the map so it can no longer be claimed
        // by a different token
        //
        commentMap.erase(it);
    }

    return comment;
}
