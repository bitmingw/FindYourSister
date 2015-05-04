// Copyright (c) 2015, Ming Wen

#ifndef _H_UTIL
#define _H_UTIL

#include "fys.hpp"
#include "json_images.hpp"

using namespace std;
using namespace cv;

namespace fys {

int checkDigit(string str);
string itoa(int idx);
string ftoa(double num);
string btoa(bool var);

bool pointsCompXAscend(KeyPoint i, KeyPoint j);
bool pointsCompXDescend(KeyPoint i, KeyPoint j);
bool pointsCompYAscend(KeyPoint i, KeyPoint j);
bool pointsCompYDescend(KeyPoint i, KeyPoint j);

vector<KeyPoint> pointsInRegion(vector<KeyPoint> allPoints, ImageRegion& region);
vector<KeyPoint> pointsInObject(vector<KeyPoint> allPoints, ImageObject& object);
vector<KeyPoint> matchedPoints(vector<KeyPoint> allPoints, vector<DMatch> matches, int type);
ImageRegion locateDenseRegion(vector<KeyPoint> points, double featherRate);

} // namespce fys

#endif // _H_UTIL

