// Copyright (c) 2015, Ming Wen

#ifndef _H_FYS
#define _H_FYS

#include <algorithm>
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
#define DOUBLE_STR_LEN 80 // max number of characters in one double
#define BOOL_STR_LEN 6 // max number of characters in one boolean

// type of sample images
#define TRAIN_TYPE 0
#define VALIDATE_TYPE 1
#define TEST_TYPE 2

// type of match
#define QUERY_PART_TYPE 0
#define TRAIN_PART_TYPE 1

#endif // _H_FYS

