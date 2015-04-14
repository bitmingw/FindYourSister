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
    Features(JsonFeatures& jf);
    ~Features();

private:
    string detectorType;
    string descriptorType;
    string matcherType;
};

} // namespace fys

#endif // _H_FEATURES
