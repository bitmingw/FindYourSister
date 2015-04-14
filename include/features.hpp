// Copyright (c) 2015, Ming Wen

#ifndef _H_FEATURES
#define _H_FEATURES

using namespace std;
using namespace cv;

#include "json_features.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>

namespace fys {

class Features
{

public:
    Features(JsonFeatures config);
    ~Features();

private:
    JsonFeatures config;
    //cv::FeatureDetector& detector;
    //cv::DescriptorExtractor& extractor;
    //cv::DescriptorMatcher& matcher;
};

} // namespace fys

#endif // _H_FEATURES
