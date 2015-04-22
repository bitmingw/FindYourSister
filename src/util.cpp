// Copyright (c) 2015, Ming Wen

#include "util.hpp"

using namespace std;
using namespace cv;

namespace fys {

int
checkDigit(string str)
{
    const char* c_str = str.c_str();
    if (isdigit(c_str[0])) {
        return atoi(c_str);
    }
    else {
        return -1;
    }
}

string
itoa(int idx)
{
    char s[INT_STR_LEN];
    snprintf(s, INT_STR_LEN, "%d", idx);
    return string(s);
}

bool
pointsCompXAscend(KeyPoint i, KeyPoint j)
{
    return i.pt.x < j.pt.x;
}

bool
pointsCompXDescend(KeyPoint i, KeyPoint j)
{
    return i.pt.x > j.pt.x;
}

bool
pointsCompYAscend(KeyPoint i, KeyPoint j)
{
    return i.pt.y < j.pt.y;
}

bool
pointsCompYDescend(KeyPoint i, KeyPoint j)
{
    return i.pt.y > j.pt.y;
}


vector<KeyPoint>
pointsInRegion(vector<KeyPoint> allPoints, ImageRegion& region)
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

vector<KeyPoint>
pointsInObject(vector<KeyPoint> allPoints, ImageObject& object)
{
    return pointsInRegion(allPoints, object.region);
}

vector<KeyPoint>
matchedPoints(vector<KeyPoint> allPoints, vector<DMatch> matches, int type)
{
    vector<KeyPoint> matched;
    if (type != QUERY_PART_TYPE && type != TRAIN_PART_TYPE) {
        std::cerr << "Invalid parameter: point type should be Query or Train." << std::endl;
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

ImageRegion
locateDenseRegion(vector<KeyPoint> points, double featherRate)
{
    ImageRegion region;
    if (featherRate < 0 || featherRate > 1) {
        std::cerr << "Invalid parameter: featherRate should >= 0 and <= 1." << std::endl;
    }
    else {
        size_t totalPoints = points.size();
        size_t edgeIdxLow = static_cast<size_t>((totalPoints - 1) * featherRate * 0.5);
        size_t edgeIdxHigh = totalPoints - edgeIdxLow - 1;
        sort(points.begin(), points.end(), pointsCompXAscend);
        region.xmin = points[edgeIdxLow].pt.x;
        region.xmax = points[edgeIdxHigh].pt.x;
        sort(points.begin(), points.end(), pointsCompYAscend);
        region.ymin = points[edgeIdxLow].pt.y;
        region.ymax = points[edgeIdxHigh].pt.y;
    }
    return region;
}

} // namespce fys
