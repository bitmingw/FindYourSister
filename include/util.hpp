// Copyright (c) 2015, Ming Wen

#ifndef _H_UTIL
#define _H_UTIL

#include "fys.hpp"
#include "json_images.hpp"

using namespace std;
using namespace cv;

namespace fys {

// some utility functions
int checkDigit(string str);
string itoa(int idx);
vector<KeyPoint> pointsInRegion(vector<KeyPoint> allPoints, ImageRegion& region);
vector<KeyPoint> pointsInObject(vector<KeyPoint> allPoints, ImageObject& object);
vector<KeyPoint> matchedPoints(vector<KeyPoint> allPoints, vector<DMatch> matches, int type);

} // namespce fys

#endif // _H_UTIL

