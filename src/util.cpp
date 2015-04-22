// Copyright (c) 2015, Ming Wen

#include "util.hpp"

using namespace std;
using namespace cv;

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

vector<KeyPoint> pointsInRegion(vector<KeyPoint> allPoints, ImageRegion& region)
{
    vector<KeyPoint> selectedPoints;
    float x, y;
    for (vector<KeyPoint>::iterator it = allPoints.begin(); it != allPoints.end(); ++it) {
        x = it->pt.x;
        y = it->pt.y;
        if (x >= region.xmin && x <= region.xmax && y >= region.ymin && y <= region.ymax) {
            selectedPoints.push_back(*it);
        }
    }
    return selectedPoints;
}

vector<KeyPoint> pointsInObject(vector<KeyPoint> allPoints, ImageObject& object)
{
    return pointsInRegion(allPoints, object.region);
}

vector<KeyPoint> matchedPoints(vector<KeyPoint> allPoints, vector<DMatch> matches, int type)
{
    vector<KeyPoint> matched;
    if (type != QUERY_PART_TYPE && type != TRAIN_PART_TYPE) {
        std::cerr << "Invalid parameter: \"part of matches\"." << std::endl;
    }
    else if (type == QUERY_PART_TYPE) {
        int idx;
        for (vector<DMatch>::iterator it = matches.begin(); it != matches.end(); ++it) {
            idx = it->queryIdx;
            matched.push_back(allPoints[idx]);
        }
    }
    else {
        int idx;
        for (vector<DMatch>::iterator it = matches.begin(); it != matches.end(); ++it) {
            idx = it->trainIdx;
            matched.push_back(allPoints[idx]);
        }
    }
    return matched;
}

} // namespce fys
