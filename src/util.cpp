// Copyright (c) 2015, Ming Wen

#include "../include/fys.hpp"

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

} // namespce fys
