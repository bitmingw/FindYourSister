// Copyright (c) 2015, Ming Wen

#ifndef _H_FYS
#define _H_FYS

#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>

#include <unistd.h>

#define MAX_LINE 256 // max characters in one line
#define INT_STR_LEN 12 // max number of characters in one integer

// type of sample images
#define TRAIN_TYPE 0
#define VALIDATE_TYPE 1
#define TEST_TYPE 2

using namespace std;

namespace fys {

// some utility functions
int checkDigit(string str);
string itoa(int idx);

} // namespce fys

#endif // _H_FYS

