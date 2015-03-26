// Copyright (c) 2015, Ming Wen

#include "fys.hpp"

using namespace std;

namespace fys {

int checkDigit(string str)
{
    const char* c_str = str.c_str();
    if (isdigit(c_str[0])) {
        return atoi(c_str);
    }
    else {
        return -1;
    }
}

string itoa(int idx)
{
    char s[INT_STR_LEN];
    snprintf(s, INT_STR_LEN, "%d", idx);
    return string(s);
}

} // namespce fys
