// Copyright (c) 2015, Ming Wen

#include "fys.hpp"
#include "json_base.hpp"
#include "json_images.hpp"
#include "json_features.hpp"
#include "fys_algorithms.hpp"
#include "test.hpp"

using namespace cv;

int main(int argc, char* argv[]) {
    
    // read command-line arguments
    string featuresConfigFile = "features.json";
    string imagesConfigFile = "images.json";

    int option = 0;
    while ((option = getopt(argc, argv, "f:i:")) != -1) {
        switch(option) {
            case 'f':
                featuresConfigFile = optarg;
                break;
            case 'i':
                imagesConfigFile = optarg;
                break;
            default:
                std::cout << "Usage: ./fys [-f feature config file] [-i image config file]" << std::endl;
        }
    }

    //fys::testBasicIO(featuresConfigFile);
    //fys::testGetSet(imagesConfigFile);
    //fys::testFeatureType(featuresConfigFile);
    //fys::testImageProperties(imagesConfigFile);
    //fys::testSIFTGetting(featuresConfigFile);
    //fys::testSURFGetting(featuresConfigFile);
    //fys::testFREAKGetting(featuresConfigFile);
    //fys::testSIFT(featuresConfigFile, imagesConfigFile);
    //fys::testAlgoPara(featuresConfigFile);
    //fys::testSIFTdetector(featuresConfigFile);
    fys::testReadImageWrapper(featuresConfigFile, imagesConfigFile);

    exit(EXIT_SUCCESS);
}
