// Copyright (c) 2015, Ming Wen

#include "../include/fys.hpp"

using namespace cv;

int main(int argc, char* argv[]) {
    
    // read command-line arguments
    char* features_config_file = "features.json";
    char* images_config_file = "images.json";

    int option = 0;
    while ((option = getopt(argc, argv, "f:i:")) != -1) {
        switch(option) {
            case 'f':
                features_config_file = optarg;
                break;
            case 'i':
                images_config_file = optarg;
                break;
            default:
                std::cout << "Usage: ./fys [-f feature config file] [-i image config file]" << std::endl;
        }
    }

    std::cout << features_config_file << " " << images_config_file << std::endl;
    exit(EXIT_SUCCESS);
}
