// Copyright (c) 2015, Ming Wen

#ifndef _H_JSON_FEATURES
#define _H_JSON_FEATURES

#include "fys.hpp"
#include "json_base.hpp"

using namespace std;
using namespace cv;

namespace fys {

class JsonFeatures : public JsonHandler
{

public:
    JsonFeatures(string filename);
    ~JsonFeatures();

    // -------- FEATURE TYPES --------
    string getDetectorType(const rapidjson::Value& doc);
    void setDetectorType(rapidjson::Value& doc, string newType);
    string getExtractorType(const rapidjson::Value& doc);
    void setExtractorType(rapidjson::Value& doc, string newType);
    string getMatcherType(const rapidjson::Value& doc);
    void setMatcherType(rapidjson::Value& doc, string newType);
    vector<string> getAlgoParaStr(string usage);

    // -------- SIFT CONFIG --------
    int getSIFTnfeatures(const rapidjson::Value& doc);
    int getSIFTnOctaveLayers(const rapidjson::Value& doc);
    double getSIFTcontrastThreshold(const rapidjson::Value& doc);
    double getSIFTedgeThreshold(const rapidjson::Value& doc);
    double getSIFTsigma(const rapidjson::Value& doc);
    vector<string> getSIFTparaStr();

    // -------- SURF CONFIG --------
    double getSURFhessianThreshold(const rapidjson::Value& doc);
    int getSURFnOctaves(const rapidjson::Value& doc);
    int getSURFnOctaveLayers(const rapidjson::Value& doc);
    bool getSURFextended(const rapidjson::Value& doc);
    bool getSURFupright(const rapidjson::Value& doc);

    // -------- FREAK CONFIG --------
    bool getFREAKorientationNormalized(const rapidjson::Value& doc);
    bool getFREAKscaleNormalized(const rapidjson::Value& doc);
    double getFREAKpatternScale(const rapidjson::Value& doc);
    int getFREAKnOctaves(const rapidjson::Value& doc);
    // TODO: getFREAKselectedPairs()

    // -------- BFMATCHER CONFIG --------
    string getBFMatcherNormType(const rapidjson::Value& doc);
    bool getBFMatcherCrossCheck(const rapidjson::Value& doc);

private:
    string detectorType;
    string extractorType;
    string matcherType;

    vector<string> detectorTypePath;
    vector<string> extractorTypePath;
    vector<string> matcherTypePath;
    vector<string> SIFTConfigPath;
    vector<string> SURFConfigPath;
    vector<string> FREAKConfigPath;
    vector<string> BFMatcherConfigPath;
};

} // namespace fys

#endif // _H_JSON_FEATURES

