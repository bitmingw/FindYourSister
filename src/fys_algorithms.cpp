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
    else if (name == "BRISK") {
        this->detector = new BRISK();
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
        double para4 = atof(parameters[3].c_str());
        double para5 = atof(parameters[4].c_str());
        this->detector = new SIFT(para1, para2, para3, para4, para5);
    }
    else if (name == "SURF") {
        double para1 = atof(parameters[0].c_str());
        int para2 = atoi(parameters[1].c_str());
        int para3 = atoi(parameters[2].c_str());
        bool para4 = atob(parameters[3].c_str());
        bool para5 = atob(parameters[4].c_str());
        this->detector = new SURF(para1, para2, para3, para4, para5);
    }
    else if (name == "BRISK") {
        int para1 = atoi(parameters[0].c_str());
        int para2 = atoi(parameters[1].c_str());
        double para3 = atof(parameters[2].c_str());
        this->detector = new BRISK(para1, para2, para3);
    }
    else {
        this->detector = NULL;
    }
}

FysFeatureDetector::~FysFeatureDetector()
{
    if (this->detector != NULL) {
        delete detector;
        detector = NULL;
    }
}

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
    else if (name == "BRISK") {
        this->extractor = new BRISK();
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
        double para4 = atof(parameters[3].c_str());
        double para5 = atof(parameters[4].c_str());
        this->extractor = new SIFT(para1, para2, para3, para4, para5);
    }
    else if (name == "SURF") {
        double para1 = atof(parameters[0].c_str());
        int para2 = atoi(parameters[1].c_str());
        int para3 = atoi(parameters[2].c_str());
        bool para4 = atob(parameters[3].c_str());
        bool para5 = atob(parameters[4].c_str());
        this->extractor = new SURF(para1, para2, para3, para4, para5);
    }
    else if (name == "BRISK") {
        int para1 = atoi(parameters[0].c_str());
        int para2 = atoi(parameters[1].c_str());
        double para3 = atof(parameters[2].c_str());
        this->extractor = new BRISK(para1, para2, para3);
    }
    else if (name == "FREAK") {
        bool para1 = atob(parameters[0].c_str());
        bool para2 = atob(parameters[1].c_str());
        double para3 = atof(parameters[2].c_str());
        int para4 = atoi(parameters[3].c_str());
        this->extractor = new FREAK(para1, para2, para3, para4);
    }
    else {
        this->extractor = NULL;
    }
}

FysDescriptorExtractor::~FysDescriptorExtractor()
{
    if (this->extractor != NULL) {
        delete extractor;
        extractor = NULL;
    }
}

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

FysDescriptorMatcher::~FysDescriptorMatcher()
{
    if (this->matcher != NULL) {
        delete matcher;
        matcher = NULL;
    }
}

cv::DescriptorMatcher*
FysDescriptorMatcher::getMatcher()
{
    return this->matcher;
}

// -------- ALGORITHMS --------
FysAlgorithms::FysAlgorithms(string featureJsonFile, string imageJsonFile)
    : jf(featureJsonFile), ji(imageJsonFile)
{
    fysDetector = new (std::nothrow) FysFeatureDetector(jf.getDetectorType(jf.doc),
            jf.getParameters("detector"));
    fysExtractor = new (std::nothrow) FysDescriptorExtractor(jf.getExtractorType(jf.doc),
            jf.getParameters("extractor"));
    fysMatcher = new (std::nothrow) FysDescriptorMatcher(jf.getMatcherType(jf.doc),
            jf.getParameters("matcher"));
    if (fysDetector && fysExtractor && fysMatcher) {
        d = fysDetector->getDetector();
        e = fysExtractor->getExtractor();
        m = fysMatcher->getMatcher();
    }
    numImages = this->ji.getNumImages(this->ji.doc);
    querySize = numImages.train;
    testSize = 0;
}

FysAlgorithms::~FysAlgorithms()
{
    if (fysDetector != NULL) {
        delete fysDetector;
        fysDetector = NULL;
    }
    if (fysExtractor != NULL) {
        delete fysExtractor;
        fysExtractor = NULL;
    }
    if (fysMatcher != NULL) {
        delete fysMatcher;
        fysMatcher = NULL;
    }
}

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
FysAlgorithms::readImage(vector<cv::Mat>& images, unsigned int idx,
        const string& filename, int flags)
{
    if (idx < images.size()) {
        images[idx] = imread(filename, flags); 
    }
    else {
        std::cerr << "Read single image: given index is not available." << std::endl;
    }
}

void
FysAlgorithms::readImages(vector<cv::Mat>& images, int groupType,
        const vector<string>& filenames, int flags)
{
    images = vector<cv::Mat>(); // clear the image vector
    if (groupType == TRAIN_TYPE || groupType == VALIDATE_TYPE || groupType == TEST_TYPE) {
        for (unsigned int i = 0; i < filenames.size(); ++i) {
            images.push_back(imread(filenames[i], flags));
        }
        if (groupType == VALIDATE_TYPE || groupType == TEST_TYPE) {
            this->testDescriptions = vector<cv::Mat>(filenames.size(), cv::Mat());
        }
        else {
            this->queryDescriptions = vector<cv::Mat>(filenames.size(), cv::Mat());
            if (this->querySize != filenames.size()) {
                std::cerr << "Read batch images: warning, #images not consistent." << std::endl;
            }
        }
    }
    else {
        std::cerr << "Read batch images: wrong group type." << std::endl;
    }
}

cv::Mat
FysAlgorithms::getImage(const string& type, unsigned int idx)
{
    if (type == "query" && idx < queryMats.size()) {
        return queryMats[idx];
    }
    else if (type == "test" && idx < testMats.size()) {
        return testMats[idx];
    }
    else {
        std::cerr << "Get image: wrong group or index out of range." << std::endl;
        return cv::Mat(); // return empty image
    }
}

// -------- OpenCV Features2D Interface --------
void
FysAlgorithms::detect(vector<cv::Mat>& images, vector<KeyPoint>& keys, unsigned int idx)
{
    if (idx < images.size()) {
        d->detect(images[idx], keys);
    }
    else {
        std::cerr << "Feature detection: index out of range." << std::endl;
    }
}

void
FysAlgorithms::compute(vector<cv::Mat>& images, vector<KeyPoint>& keys,
        vector<cv::Mat>& descriptions, unsigned int idx)
{
    if (idx < images.size()) {
        e->compute(images[idx], keys, descriptions[idx]);
    }
    else {
        std::cerr << "Feature extraction: index out of range." << std::endl;
    }
}

void
FysAlgorithms::match(vector<cv::Mat>& queryDescriptions, vector<cv::Mat>& testDescriptions,
        vector<DMatch>& mapping, unsigned int queryIdx, unsigned int testIdx)
{
    if (queryIdx < queryDescriptions.size() && testIdx < testDescriptions.size()) {
        m->match(queryDescriptions[queryIdx], testDescriptions[testIdx], mapping);
    }
    else {
        std::cerr << "Matching: index out of range." << std::endl;
    }
}

int
FysAlgorithms::draw(vector<cv::Mat>& querys, vector<KeyPoint>& queryKeys, unsigned int queryIdx,
        vector<cv::Mat>& tests, vector<KeyPoint>& testKeys, unsigned int testIdx,
        vector<DMatch>& mapping, vector<cv::Mat>& outputs)
{
    if (queryIdx < querys.size() && testIdx < tests.size()) {
        Mat tmp;
        drawMatches(querys[queryIdx], queryKeys, tests[testIdx], testKeys, mapping, tmp);
        outputs.push_back(tmp);
        return outputs.size() - 1; // return the index of output image
    }
    else {
        return -1;
    }
}

// -------- RUN ANALYSIS --------
void
FysAlgorithms::loadInfo(int groupType)
{
    vector<string> filenames;
    vector<cv::KeyPoint> points;
    if (groupType == TRAIN_TYPE) {
        filenames = this->getFilenames(groupType);
        readImages(queryMats, groupType, filenames, 1); // Load 3-channel color images
        
        this->queryKeys = vector<vector<cv::KeyPoint> >(); // clear
        unsigned int i = 0;
        while (i < querySize) {
            this->detect(queryMats, points, i);
            // Remove the points outside the region
            this->queryObjects.push_back(ji.getObjectList(ji.doc, groupType, i));
            // points = pointsInRegion(); // Need the union of points, TODO
            this->queryKeys.push_back(points); 
            ++i;
        }

        i = 0;
        while (i < querySize) {
            this->compute(queryMats, queryKeys[i], queryDescriptions, i);
            ++i;
        }
    }

    else if (groupType == VALIDATE_TYPE || groupType == TEST_TYPE) {
        filenames = this->getFilenames(groupType);
        readImages(testMats, groupType, filenames, 1); // Load 3-channel color images

        this->testKeys = vector<vector<cv::KeyPoint> >(); // clear
        unsigned int i = 0;
        if (groupType == VALIDATE_TYPE) {
            this->testSize = this->numImages.validate;
        }
        else if (groupType == TEST_TYPE) {
            this->testSize = this->numImages.test;
        }

        while (i < testSize) {
            this->detect(testMats, points, i);
            this->testKeys.push_back(points);
            ++i;
        }

        i = 0;
        while (i < testSize) {
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
FysAlgorithms::runEach(int testIdx)
{
    vector<DMatch> mapping;
    unsigned int queryIdx = 0;
    while (queryIdx < querySize) {
        this->match(queryDescriptions, testDescriptions, mapping, queryIdx, testIdx);
        this->matches.push_back(mapping);
        // Add your own algorithm here
        ++queryIdx;
    }
}

void
FysAlgorithms::runValidate()
{
    this->loadInfo(TRAIN_TYPE);
    std::cout << "Load training set successfully!" << std::endl;
    this->loadInfo(VALIDATE_TYPE);
    std::cout << "Load validation set successfully!" << std::endl;
    this->runAlgorithm(VALIDATE_TYPE);
}

void
FysAlgorithms::runTest()
{
    this->loadInfo(TRAIN_TYPE);
    std::cout << "Load training set successfully!" << std::endl;
    this->loadInfo(TEST_TYPE);
    std::cout << "Load testing set successfully!" << std::endl;
    this->runAlgorithm(TEST_TYPE);
}

void
FysAlgorithms::runAlgorithm(int runType)
{
    unsigned int i = 0;
    while (i < testSize) {
        this->runEach(i);
        ++i;
    }
}

// -------- VISUALIZATION --------
cv::Mat
FysAlgorithms::visualizeMatch(unsigned int queryIdx, unsigned int testIdx)
{
    int idx = this->draw(queryMats, queryKeys[queryIdx], queryIdx,
            testMats, testKeys[testIdx], testIdx, // reducedKeys maybe used later
            matches[testIdx * querySize + queryIdx], outputMats); 
    return outputMats[idx];
}

} // namespace fys

