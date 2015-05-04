// Copyright (c) 2015, Ming Wen

#include "fys_algorithms.hpp"

using namespace std;
using namespace cv;

namespace fys {

FysFeatureDetector::FysFeatureDetector(string name)
{
    if (name == "SIFT") {
        this->detector = new SIFT();
    }
}

FysFeatureDetector::FysFeatureDetector(string name, vector<string> paras)
{
    if (name == "SIFT") {
        int para1 = atoi(paras[0].c_str());
        int para2 = atoi(paras[1].c_str());
        double para3 = atof(paras[2].c_str());
        double para4 = atof(paras[2].c_str());
        double para5 = atof(paras[2].c_str());
        this->detector = new SIFT(para1, para2, para3, para4, para5);
    }
}

FysFeatureDetector::~FysFeatureDetector() {}

cv::FeatureDetector*
FysFeatureDetector::getDetector()
{
    return this->detector;
}

} // namespace fys
