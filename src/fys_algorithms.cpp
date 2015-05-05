// Copyright (c) 2015, Ming Wen

#include "fys_algorithms.hpp"

using namespace std;
using namespace cv;

namespace fys {

// -------- FEATURE DETECTOR --------
FysFeatureDetector::FysFeatureDetector(string name)
{
    if (name == "SIFT") {
        this->detector = new SIFT();
    }
    else if (name == "SURF") {
        this->detector = new SURF();
    }
    else {
        this->detector = NULL;
    }
}

FysFeatureDetector::FysFeatureDetector(string name, vector<string> parameters)
{
    if (name == "SIFT") {
        int para1 = atoi(parameters[0].c_str());
        int para2 = atoi(parameters[1].c_str());
        double para3 = atof(parameters[2].c_str());
        double para4 = atof(parameters[2].c_str());
        double para5 = atof(parameters[2].c_str());
        this->detector = new SIFT(para1, para2, para3, para4, para5);
    }
    else {
        this->detector = NULL;
    }
}

FysFeatureDetector::~FysFeatureDetector() {}

cv::FeatureDetector*
FysFeatureDetector::getDetector()
{
    return this->detector;
}

// -------- DESCRIPTOR EXTRACTOR --------
FysDescriptorExtractor::FysDescriptorExtractor(string name)
{
    if (name == "SIFT") {
        this->extractor = new SIFT();
    }
    else if (name == "SURF") {
        this->extractor = new SURF();
    }
    else if (name == "FREAK") {
        this->extractor = new FREAK();
    }
    else {
        this->extractor = NULL;
    }
}

FysDescriptorExtractor::FysDescriptorExtractor(string name, vector<string> parameters)
{
    if (name == "SIFT") {
        int para1 = atoi(parameters[0].c_str());
        int para2 = atoi(parameters[1].c_str());
        double para3 = atof(parameters[2].c_str());
        double para4 = atof(parameters[2].c_str());
        double para5 = atof(parameters[2].c_str());
        this->extractor = new SIFT(para1, para2, para3, para4, para5);
    }
    else {
        this->extractor = NULL;
    }
}

FysDescriptorExtractor::~FysDescriptorExtractor() {}

cv::DescriptorExtractor*
FysDescriptorExtractor::getExtractor()
{
    return this->extractor;
}

// -------- DESCRIPTOR MATCHER --------
FysDescriptorMatcher::FysDescriptorMatcher(string name)
{
    if (name == "BFMatcher") {
        this->matcher = new BFMatcher();
    }
    else {
        this->matcher = NULL;
    }
}

FysDescriptorMatcher::FysDescriptorMatcher(string name, vector<string> parameters)
{
    if (name == "BFMatcher") {
        int para1 = atoi(parameters[0].c_str());
        bool para2 = atob(parameters[1].c_str());
        this->matcher = new BFMatcher(para1, para2);
    }
    else {
        this->matcher = NULL;
    }
}

FysDescriptorMatcher::~FysDescriptorMatcher() {}

cv::DescriptorMatcher*
FysDescriptorMatcher::getMatcher()
{
    return this->matcher;
}

// -------- ALGORITHMS --------
FysAlgorithms::FysAlgorithms(string featureJsonFile, string imageJsonFile)
    : jf(featureJsonFile), ji(imageJsonFile)
{
    fysDetector = new FysFeatureDetector(jf.getDetectorType(jf.doc),
            jf.getParameters("detector"));
    fysExtractor = new FysDescriptorExtractor(jf.getExtractorType(jf.doc),
            jf.getParameters("extractor"));
    fysMatcher = new FysDescriptorMatcher(jf.getMatcherType(jf.doc),
            jf.getParameters("matcher"));
    d = fysDetector->getDetector();
    e = fysExtractor->getExtractor();
    m = fysMatcher->getMatcher();
    queryMats = new cv::Mat[MAT_ARRAY_SIZE]; 
    testMats = new cv::Mat[MAT_ARRAY_SIZE];
}

void
FysAlgorithms::readImage(cv::Mat* image, unsigned int idx, const string& filename, int flags)
{
    image[idx] = imread(filename, flags); 
}

void
FysAlgorithms::readImages(cv::Mat* images, const vector<string>& filenames, int flags)
{
    for (unsigned int i = 0; i < filenames.size(); ++i) {
        images[i] = imread(filenames[i], flags);
    }
}

cv::Mat
FysAlgorithms::getImage(const string& type, unsigned int idx)
{
    if (type == "query") {
        return queryMats[idx];
    }
    else if (type == "test") {
        return testMats[idx];
    }

    // Should not reach here
    return cv::Mat();
}

FysAlgorithms::~FysAlgorithms() {}

} // namespace fys

