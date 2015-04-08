// Copyright (c) 2015, Ming Wen

#ifndef _H_JSON_FEATURES
#define _H_JSON_FEATURES

#include "json_base.hpp"

using namespace std;

namespace fys {

class JsonFeatures : public JsonHandler
{

public:
    JsonFeatures(string filename);
    ~JsonFeatures();
    string getDetectorType(const rapidjson::Value& doc);
    void setDetectorType(rapidjson::Value& doc, string newType);
    string getDescriptorType(const rapidjson::Value& doc);
    void setDescriptorType(rapidjson::Value& doc, string newType);
    string getMatcherType(const rapidjson::Value& doc);
    void setMatcherType(rapidjson::Value& doc, string newType);

private:
    vector<string> detectorTypePath;
    vector<string> descriptorTypePath;
    vector<string> matcherTypePath;
    string detectorType;
    string descriptorType;
    string matcherType;
};

} // namespace fys

#endif // _H_JSON_FEATURES
