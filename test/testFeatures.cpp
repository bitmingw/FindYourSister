// Copyright (c) 2015, Ming Wen

#include "fys.hpp"
#include "util.hpp"
#include "json_base.hpp"
#include "json_images.hpp"
#include "json_features.hpp"
#include "fys_algorithms.hpp"
#include "test.hpp"

using namespace std;
using namespace cv;

namespace fys {

void testSIFTdetector(string featuresFile)
{
    std::cout << "==== Test Start: SIFT detector ====" << std::endl;

    Mat query = imread("../OneWaySignal/1.jpg", 0); // read gray image
    vector<KeyPoint> queryKeys;
 
    JsonFeatures jf(featuresFile);
    FysFeatureDetector fd(jf.getDetectorType(jf.doc), jf.getParameters("detector"));
    //FysFeatureDetector fd(jf.getDetectorType(jf.doc));
    FeatureDetector* d = fd.getDetector();
    // FeatureDetector* d = new SIFT();
    d->detect(query, queryKeys);
    std::cout << queryKeys.size() << std::endl;

    std::cout << "==== Test End: SIFT detector ====" << std::endl;
}

/*
void testSIFT(string featuresFile, string imagesFile)
{
    std::cout << "==== Test Start: SIFT Demo ====" << std::endl;

    Mat query = imread("../OneWaySignal/1.jpg", 0); // read gray image
    Mat test1 = imread("../OneWaySignal/2.jpg", 0);
    Mat test2 = imread("../OneWaySignal/5.jpg", 0);
    Mat test3 = imread("../OneWaySignal/9.jpg", 0);

    JsonFeatures jf(featuresFile);
    SIFT detectAndExtractor(jf.genSIFT());

    // Read images json file
    JsonImages ji(imagesFile);
    ImageObject ob = ji.getObjectByID(ji.doc, TRAIN_TYPE, 0, 0);

    vector<KeyPoint> queryKeys;
    vector<KeyPoint> testKeys;
    vector<KeyPoint> reducedKeys;
    Mat queryDescriptors, testDescriptors;
    BFMatcher matcher(jf.genBFMatcher());
    vector<DMatch> matches;
    Mat output;
    ImageRegion reg;
    Scalar color(0, 0, 255);
    
    detectAndExtractor.detect(query, queryKeys);

    // Delete the points outside the object region
    queryKeys = pointsInObject(queryKeys, ob);
    detectAndExtractor.compute(query, queryKeys, queryDescriptors);
    
    detectAndExtractor.detect(test1, testKeys);
    detectAndExtractor.compute(test1, testKeys, testDescriptors);

    matcher.match(queryDescriptors, testDescriptors, matches);

    // Delete unmatched points in train image
    reducedKeys = matchedPoints(testKeys, matches, TRAIN_PART_TYPE);
    reg = locateDenseRegion(reducedKeys, 0.2);

    drawMatches(query, queryKeys, test1, testKeys, matches, output);
    rectangle(output, Point(reg.xmin + query.cols, reg.ymin), Point(reg.xmax + query.cols, reg.ymax), color, 2);

    imwrite("1-2.jpg", output);

    
    detectAndExtractor.detect(test2, testKeys);
    detectAndExtractor.compute(test2, testKeys, testDescriptors);

    matcher.match(queryDescriptors, testDescriptors, matches);
    reducedKeys = matchedPoints(testKeys, matches, TRAIN_PART_TYPE);
    reg = locateDenseRegion(reducedKeys, 0.2);

    drawMatches(query, queryKeys, test2, testKeys, matches, output);
    rectangle(output, Point(reg.xmin + query.cols, reg.ymin), Point(reg.xmax + query.cols, reg.ymax), color, 2);
    imwrite("1-5.jpg", output);


    detectAndExtractor.detect(test3, testKeys);
    detectAndExtractor.compute(test3, testKeys, testDescriptors);

    matcher.match(queryDescriptors, testDescriptors, matches);
    reducedKeys = matchedPoints(testKeys, matches, TRAIN_PART_TYPE);
    reg = locateDenseRegion(reducedKeys, 0.2);

    drawMatches(query, queryKeys, test3, testKeys, matches, output);
    rectangle(output, Point(reg.xmin + query.cols, reg.ymin), Point(reg.xmax + query.cols, reg.ymax), color, 2);
    imwrite("1-9.jpg", output);

    //namedWindow("window");
    //imshow("window", output); 
    //waitKey(0);

    std::cout << "==== Test End: SIFT Demo ====" << std::endl;
}
*/

}

