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
    std::cout << "==== Test Start: SIFT Constructor ====" << std::endl;

    Mat input = imread("../OneWaySignal/1.jpg");
    std::cout << input.rows << " " << input.cols << std::endl;
    Mat output;
    JsonFeatures jf(featuresFile);
    SIFT detector(jf.siftParam.genSIFT());
    vector<KeyPoint> points;
    detector.detect(input, points);

    drawKeypoints(input, points, output);

    namedWindow("window");
    imshow("window", output); 
    waitKey(5000);

    std::cout << "==== Test End: SIFT Constructor ====" << std::endl;
}

}

