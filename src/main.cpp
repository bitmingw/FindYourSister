// Copyright (c) 2015, Ming Wen

#include "../include/fys.hpp"
#include "../include/json_handler.hpp"

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

    testBasicIO();

    exit(EXIT_SUCCESS);
}
