// Copyright (c) 2015, Ming Wen

#include "../include/fys.hpp"

using namespace std;

namespace fys{

class JsonFeatures
{

// function declarations
public:
    JsonFeatures(string filename);
    void openJson();
    int getDetectorType();
    void setDetectorType(int type_enum);
    int getDescriptorType();
    void setDescriptorType(int type_enum);
    int getMatcherType();
    void setMatcherType(int type_enum);

// variables
private:
    string jsonFilename;
    bool isOpen;
    fstream stream;
    Features thisFeature;
    int detectorType;
    int descriptorType;
    int matcherType;
};

JsonFeatures::JsonFeatures(string filename) : jsonFilename(filename) {}

void JsonFeatures::openJson()
{
    if (this->isOpen == true) {
        std::cerr << "Warning: features file has been opened." << std::endl;
    }
else {
        string fullPath = "../config/" + this->jsonFilename;
        this->stream.open(fullPath.c_str(), ios::in | ios::out);
    }
}

} // namespace fys

