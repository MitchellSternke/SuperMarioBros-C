#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>

void mapComment(int line, const std::string& comment);
void mapNewline(int line);
const char* lookupComment(int line);

// We need to be able to duplicate yytext since it is volatile
//
inline char* duplicateString(const char* s, size_t n)
{
    char* d = new char[n + 1];
    memcpy(d, s, n);
    d[n] = '\0';
    return d;
}
#define DUP_YYTEXT (duplicateString(yytext, yyleng))

#endif // UTIL_HPP
