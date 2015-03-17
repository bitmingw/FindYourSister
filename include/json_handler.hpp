// Copyright (c) 2015, Ming Wen

#ifndef _H_JSON_HANDLER
#define _H_JSON_HANDLER

using namespace std;

namespace fys{

class JsonFeatures
{

// function declarations
public:
    JsonFeatures(string filename);
    void openJson();
    void readJson();
    int getDetectorType();
    void setDetectorType(int type_enum);
    int getDescriptorType();
    void setDescriptorType(int type_enum);
    int getMatcherType();
    void setMatcherType(int type_enum);

// variables
private:
    string jsonFilename;
    string jsonStr;
    int detectorType;
    int descriptorType;
    int matcherType;
};

enum Detectors {null_t};
enum Descriptors {null_c};
enum Matchers {null_m};

} // namespace fys

#endif // _H_JSON_HANDLER

