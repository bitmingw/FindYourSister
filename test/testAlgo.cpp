// Copyright (c) 2015, Ming Wen

#include "fys.hpp"
#include "util.hpp"
#include "json_base.hpp"
#include "json_images.hpp"
#include "json_features.hpp"
#include "fys_algorithms.hpp"
#include "test.hpp"

using namespace std;

namespace fys {

/*
void testReadImageWrapper(string featuresFile, string imagesFile)
{
    std::cout << "==== Test Start: Read Image Wrapper ====" << std::endl;

    FysAlgorithms app(featuresFile, imagesFile);
    std::cout << "Construction of algorithms class: complete!" << std::endl;
    app.readImages(app.queryMats, app.getFilenames(TRAIN_TYPE), 0);

    namedWindow("readingTest");
    imshow("readingTest", app.getImage("query", 4));
    waitKey(5000);

    std::cout << "==== Test End: Read Image Wrapper ====" << std::endl;
}
*/

void testAlgoMatch(string featuresFile, string imagesFile)
{
    std::cout << "==== Test Start: Match Group of Images ====" << std::endl;

    FysAlgorithms app(featuresFile, imagesFile);
    app.runTest();

    namedWindow("matching");
    imshow("matching", app.visualizeMatch(0, 4));
    waitKey(5000);
}

} // namespace fys

