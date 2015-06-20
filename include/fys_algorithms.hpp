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
    void readImage(vector<cv::Mat>& images, unsigned int idx, const string& filename, int flags);
    void readImages(vector<cv::Mat>& images, int groupType,
            const vector<string>& filenames, int flags);
    cv::Mat getImage(const string& type, unsigned int idx);


    // -------- OpenCV Features2D Interface --------
    void detect(vector<cv::Mat>& images, vector<KeyPoint>& keys, unsigned int idx);
    void compute(vector<cv::Mat>& images, vector<KeyPoint>& keys,
            vector<cv::Mat>& descriptions, unsigned int idx);
    void match(vector<cv::Mat>& queryDescriptions, vector<cv::Mat>& testDescriptions,
            vector<DMatch>& mapping, unsigned int queryIdx, unsigned int testIdx);
    int draw(vector<cv::Mat>& querys, vector<KeyPoint>& queryKeys, unsigned int queryIdx,
            vector<cv::Mat>& tests, vector<KeyPoint>& testKeys, unsigned int testIdx,
            vector<DMatch>& mapping, vector<cv::Mat>& outputs);

    // -------- RUN ANALYSIS --------
    void loadInfo(int groupType);
    void runEach(int testIdx);
    void runValidate(); // wrapper of runAlgorithm
    void runTest(); // wrapper of runAlgorithm
    void runAlgorithm(int runType);

    // -------- VISUALIZATION --------
    cv::Mat visualize(const string& type, unsigned int idx); // with keypoints TODO
    cv::Mat visualizeMatch(unsigned int queryIdx, unsigned int testIdx); // with matching lines

private:
    JsonFeatures jf; 
    JsonImages ji; 

    FysFeatureDetector* fysDetector;
    FysDescriptorExtractor* fysExtractor;
    FysDescriptorMatcher* fysMatcher;

    cv::FeatureDetector* d;
    cv::DescriptorExtractor* e;
    cv::DescriptorMatcher* m;

    vector<cv::Mat> queryMats; 
    vector<cv::Mat> testMats; 
    vector<cv::Mat> outputMats; 
    vector<cv::Mat> queryDescriptions; // the same size as queryMats 
    vector<cv::Mat> testDescriptions; // the same size as testMats

    vector<vector<ImageObject> > queryObjects;
    vector<vector<cv::KeyPoint> > queryKeys; 
    vector<vector<cv::KeyPoint> > testKeys; 
    vector<vector<cv::KeyPoint> > reducedKeys; // TODO 
    vector<vector<cv::DMatch> > matches; 

    ImageSample numImages;
    unsigned int querySize; // determine the size of image vector
    unsigned int testSize; // update in loadInfo()
};

} // namespace fys

#endif // _H_FYS_ALGORITHMS

