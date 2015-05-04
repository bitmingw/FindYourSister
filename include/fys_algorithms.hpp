// Copyright (c) 2015, Ming Wen

#ifndef _H_FYS_ALGORITHMS
#define _H_FYS_ALGORITHMS

#include "fys.hpp"
#include "util.hpp"
#include "json_features.hpp"

using namespace std;
using namespace cv;

namespace fys {

class FysFeatureDetector
{
public:
    FysFeatureDetector(string name);
    FysFeatureDetector(string name, vector<string> parameters);
    ~FysFeatureDetector();
    cv::FeatureDetector* getDetector();

private:
    cv::FeatureDetector* detector;
};

class FysDescriptorExtractor
{
public:
    FysDescriptorExtractor(string name);
    FysDescriptorExtractor(string name, vector<string> parameters);
    ~FysDescriptorExtractor();
    cv::DescriptorExtractor* getExtractor();

private:
    cv::DescriptorExtractor* extractor;
};

class FysDescriptorMatcher
{
public:
    FysDescriptorMatcher(string name);
    FysDescriptorMatcher(string name, vector<string> parameters);
    ~FysDescriptorMatcher();
    cv::DescriptorMatcher* getMatcher();

private:
    cv::DescriptorMatcher* matcher;
};

class FysAlgorithms
{
public:
    FysAlgorithms(string featureJsonFile, string imageJsonFile);
    ~FysAlgorithms();
    cv::FeatureDetector* d;
    cv::DescriptorExtractor* e;
    cv::DescriptorMatcher* m;

private:
    JsonFeatures jf;
    JsonImages ji;
    FysFeatureDetector* fysDetector;
    FysDescriptorExtractor* fysExtractor;
    FysDescriptorMatcher* fysMatcher;
};

} // namespace fys

#endif // _H_FYS_ALGORITHMS

