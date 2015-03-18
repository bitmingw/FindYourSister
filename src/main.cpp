// Copyright (c) 2015, Ming Wen

#include "../include/fys.hpp"
#include "../include/json_handler.hpp"

using namespace cv;

int main(int argc, char* argv[]) {
    
    // read command-line arguments
    string features_config_file = "features.json";
    string images_config_file = "images.json";

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

    fys::JsonFeatures jf = fys::JsonFeatures(features_config_file);
    jf.readJsonFile();
    std::cout << jf.getFileStr() << std::endl;

    rapidjson::Document doc;
    doc.Parse(jf.getFileStr().c_str());

    if (doc.HasMember("detector") && doc["detector"].IsNull()) {
        rapidjson::Value& detector = doc["detector"];
        detector.SetString("SIFT");
    }

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    std::cout << jf.getDocStr(buffer) << std::endl;
    jf.updateStr(buffer);
    jf.writeJsonFile();

    exit(EXIT_SUCCESS);
}
