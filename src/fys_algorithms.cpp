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
    numImages = this->ji.getNumImages(this->ji.doc);
}

FysAlgorithms::~FysAlgorithms() {}

vector<string>
FysAlgorithms::getFilenames(int groupType)
{
    vector<string> names;
    if (groupType == TRAIN_TYPE) {
        for (int i = 0; i < this->numImages.train; ++i) {
            names.push_back(this->ji.getFullName(this->ji.doc, groupType, i));
        }
    }
    else if (groupType == VALIDATE_TYPE) {
        for (int i = 0; i < this->numImages.validate; ++i) {
            names.push_back(this->ji.getFullName(this->ji.doc, groupType, i));
        }
    }
    else if (groupType == TEST_TYPE) {
        for (int i = 0; i < this->numImages.test; ++i) {
            names.push_back(this->ji.getFullName(this->ji.doc, groupType, i));
        }
    }
    return names;
}

void
FysAlgorithms::readImage(cv::Mat* images, unsigned int idx, const string& filename, int flags)
{
    images[idx] = imread(filename, flags); 
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

// -------- OpenCV Features2D Interface --------
void
FysAlgorithms::detect(cv::Mat* images, vector<KeyPoint> keys, unsigned int idx)
{
    d->detect(images[idx], keys);
}

void
FysAlgorithms::compute(cv::Mat* images, vector<KeyPoint> keys,
        cv::Mat* descriptions, unsigned int idx)
{
    e->compute(images[idx], keys, descriptions[idx]);
}

void
FysAlgorithms::match(cv::Mat* queryDescriptions, cv::Mat* testDescriptions,
        vector<DMatch> mapping, unsigned int idx)
{
    m->match(queryDescriptions[idx], testDescriptions[idx], mapping);
}

void
FysAlgorithms::draw(cv::Mat* querys, vector<KeyPoint> queryKeys, unsigned int queryIdx,
        cv::Mat* tests, vector<KeyPoint> testKeys, unsigned int testIdx,
        vector<DMatch> mapping, cv::Mat* outputs, unsigned int outputIdx)
{
    drawMatches(querys[queryIdx], queryKeys, tests[testIdx], testKeys,
            mapping, outputs[outputIdx]);
}

// -------- RUN ANALYSIS --------
void
FysAlgorithms::loadInfo(int groupType)
{
    vector<string> filenames;
    vector<cv::KeyPoint> points;
    if (groupType == TRAIN_TYPE) {
        filenames = this->getFilenames(groupType);
        readImages(queryMats, filenames, 1); // Load 3-channel color images
        
        this->queryKeys = vector<vector<cv::KeyPoint> >(); // clear
        int i = 0;
        while (i < this->numImages.train) {
            this->detect(queryMats, points, i);
            // Reduce the keypoints here
            this->queryKeys.push_back(points); 
            ++i;
        }

        i = 0;
        while (i < this->numImages.train) {
            this->compute(queryMats, queryKeys[i], queryDescriptions, i);
            ++i;
        }
    }

    else if (groupType == VALIDATE_TYPE || groupType == TEST_TYPE) {
        filenames = this->getFilenames(groupType);
        readImages(testMats, filenames, 1); // Load 3-channel color images

        this->testKeys = vector<vector<cv::KeyPoint> >(); // clear
        int i = 0;
        int numTestImages = 0;
        if (groupType == VALIDATE_TYPE) {
            numTestImages = this->numImages.validate;
        }
        else if (groupType == TEST_TYPE) {
            numTestImages = this->numImages.test;
        }

        while (i < numTestImages) {
            this->detect(testMats, points, i);
            // Reduce the keypoinst here
            this->queryKeys.push_back(points);
            ++i;
        }

        i = 0;
        while (i < numTestImages) {
            this->compute(testMats, testKeys[i], testDescriptions, i);
            ++i;
        }
    }

    else {
        std::cerr << "Invalid group type of images!" << std::endl;
    }

    return;
}

void
FysAlgorithms::runValidate()
{
    this->loadInfo(TRAIN_TYPE);
    this->loadInfo(VALIDATE_TYPE);
    this->runAlgorithm(VALIDATE_TYPE);
}

void
FysAlgorithms::runTest()
{
    this->loadInfo(TRAIN_TYPE);
    this->loadInfo(TEST_TYPE);
    this->runAlgorithm(TEST_TYPE);
}

void
FysAlgorithms::runAlgorithm(int runType)
{

}

} // namespace fys

