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
    vector<string> getFilenames(int groupType);
    void readImage(cv::Mat* images, unsigned int idx, const string& filename, int flags);
    void readImages(cv::Mat* images, const vector<string>& filenames, int flags);
    cv::Mat getImage(const string& type, unsigned int idx);

    cv::FeatureDetector* d;
    cv::DescriptorExtractor* e;
    cv::DescriptorMatcher* m;

    JsonFeatures jf; // MOVE TO PUBLIC FOR TEST
    JsonImages ji; // MOVE TO PUBLIC FOR TEST

    cv::Mat* queryMats; // MOVE TO PUBLIC FOR TEST
    cv::Mat* testMats; // MOVE TO PUBLIC FOR TEST
    cv::Mat* outputMats; // MOVE TO PUBLIC FOR TEST
    cv::Mat* queryDescriptions; // MOVE TO PUBLIC FOR TEST
    cv::Mat* testDescriptions; // MOVE TO PUBLIC FOR TEST 

    vector<vector<cv::KeyPoint> > queryKeys; // MOVE TO PUBLIC FOR TEST
    vector<vector<cv::KeyPoint> > testKeys; // MOVE TO PUBLIC FOR TEST
    vector<vector<cv::KeyPoint> > reducedKeys; // MOVE TO PUBLIC FOR TEST, TODO
    vector<vector<cv::DMatch> > matches; // MOVE TO PUBLIC FOR TEST

    // -------- OpenCV Features2D Interface --------
    void detect(cv::Mat* images, vector<KeyPoint>& keys, unsigned int idx);
    void compute(cv::Mat* images, vector<KeyPoint> keys,
            cv::Mat* descriptions, unsigned int idx);
    void match(cv::Mat* queryDescriptions, cv::Mat* testDescriptions,
            vector<DMatch> mapping, unsigned int queryIdx, unsigned int testIdx);
    void draw(cv::Mat* querys, vector<KeyPoint> queryKeys, unsigned int queryIdx,
            cv::Mat* tests, vector<KeyPoint> testKeys, unsigned int testIdx,
            vector<DMatch> mapping, cv::Mat* outputs, unsigned int outputIdx);

    // -------- RUN ANALYSIS --------
    void loadInfo(int groupType);
    void runValidate(); // wrapper of runAlgorithm
    void runTest(); // wrapper of runAlgorithm
    void runAlgorithm(int runType);

    // -------- VISUALIZATION --------
    cv::Mat visualize(const string& type, unsigned int idx); // with keypoints TODO
    cv::Mat visualizeMatch(unsigned int queryIdx, unsigned int testIdx); // with matching lines

private:
    FysFeatureDetector* fysDetector;
    FysDescriptorExtractor* fysExtractor;
    FysDescriptorMatcher* fysMatcher;
    ImageSample numImages;
    int querySize;
    int testSize; // update in loadInfo()
    unsigned int savingSlot;
};

} // namespace fys

#endif // _H_FYS_ALGORITHMS

