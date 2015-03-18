// Copyright (c) 2015, Ming Wen

#ifndef _H_JSON_HANDLER
#define _H_JSON_HANDLER

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

using namespace std;

namespace fys{

// base class
class JsonHandler
{

public:
    JsonHandler(string filename);
    ~JsonHandler();
    void readJsonFile(); // open & read json file
    string getFileStr(); // return json file as string
    string getDocStr(rapidjson::StringBuffer& buffer); // return json document as string
    void updateStr(rapidjson::StringBuffer& buffer); // update this->jsonStr
    void writeJsonFile(); // open & write json file

private:
    string jsonFilename;
    string jsonStr;
};


class JsonFeatures : public JsonHandler
{

public:
    JsonFeatures(string filename);
    ~JsonFeatures();
    int getDetectorType();
    void setDetectorType(int type_enum);
    int getDescriptorType();
    void setDescriptorType(int type_enum);
    int getMatcherType();
    void setMatcherType(int type_enum);

private:
    int detectorType;
    int descriptorType;
    int matcherType;
};

enum Detectors {null_t};
enum Descriptors {null_c};
enum Matchers {null_m};

} // namespace fys

#endif // _H_JSON_HANDLER

