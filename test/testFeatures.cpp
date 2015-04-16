// Copyright (c) 2015, Ming Wen

#include "fys.hpp"
#include "json_base.hpp"
#include "json_images.hpp"
#include "json_features.hpp"
#include "test.hpp"

using namespace std;
using namespace cv;

namespace fys {

void testSIFT(string featuresFile)
{
    std::cout << "==== Test Start: SIFT Demo ====" << std::endl;

    Mat query = imread("../OneWaySignal/1.jpg", 0); // read gray image
    Mat test = imread("../OneWaySignal/12.jpg", 0);

    JsonFeatures jf(featuresFile);
    SIFT detectAndExtractor(jf.genSIFT());

    vector<KeyPoint> queryKeys;
    vector<KeyPoint> testKeys;

    detectAndExtractor.detect(query, queryKeys);
    detectAndExtractor.detect(test, testKeys);

    Mat queryDescriptors, testDescriptors;
    detectAndExtractor.compute(query, queryKeys, queryDescriptors);
    detectAndExtractor.compute(test, testKeys, testDescriptors);

    BFMatcher matcher(jf.genBFMatcher());
    vector<DMatch> matches;
    matcher.match(queryDescriptors, testDescriptors, matches);

    Mat output;
    drawMatches(query, queryKeys, test, testKeys, matches, output);
    imwrite("../OneWaySignal/1-12.jpg", output);

    namedWindow("window");
    imshow("window", output); 
    waitKey(0);

    std::cout << "==== Test End: SIFT Demo ====" << std::endl;
}

}

