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

void testAlgoMatch(string featuresFile, string imagesFile)
{
    std::cout << "==== Test Start: Match Group of Images ====" << std::endl;

    FysAlgorithms app(featuresFile, imagesFile);
    app.runTest();

    namedWindow("matching");
    imshow("matching", app.visualizeMatch(0, 0));
    waitKey(5000);

    std::cout << "==== Test End: Match Group of Images ====" << std::endl;
}

} // namespace fys

