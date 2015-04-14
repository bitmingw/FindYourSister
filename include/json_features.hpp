// Copyright (c) 2015, Ming Wen

#ifndef _H_JSON_FEATURES
#define _H_JSON_FEATURES

#include "json_base.hpp"

using namespace std;

namespace fys {

class SiftConfig
{
public:
    SiftConfig();
    SiftConfig(int nfeatures, int nOctaveLayers, double contrastThreshold,
            double edgeThreshold, double sigma);
    ~SiftConfig();
    int nfeatures;
    int nOctaveLayers;
    double contrastThreshold;
    double edgeThreshold;
    double sigma;
};

class SurfConfig
{
public:
    SurfConfig();
    SurfConfig(double hessianThreshold, int nOctaves, int nOctaveLayers,
            bool isExtended, bool isUpright);
    ~SurfConfig();
    double hessianThreshold;
    int nOctaves;
    int nOctaveLayers;
    bool isExtended;
    bool isUpright;
};

class FreakConfig
{
public:
    FreakConfig();
    FreakConfig(bool orientNormal, bool scaleNormal, double patternScale, int nOctaves);
    ~FreakConfig();
    bool orientNormal;
    bool scaleNormal;
    double patternScale;
    int nOctaves;
};


class JsonFeatures : public JsonHandler
{

public:
    JsonFeatures(string filename);
    ~JsonFeatures();

    // -------- FEATURE TYPES --------
    string getDetectorType(const rapidjson::Value& doc);
    void setDetectorType(rapidjson::Value& doc, string newType);
    string getDescriptorType(const rapidjson::Value& doc);
    void setDescriptorType(rapidjson::Value& doc, string newType);
    string getMatcherType(const rapidjson::Value& doc);
    void setMatcherType(rapidjson::Value& doc, string newType);

    // -------- SIFT CONFIG --------
    int getSIFTnfeatures(const rapidjson::Value& doc);
    int getSIFTnOctaveLayers(const rapidjson::Value& doc);
    double getSIFTcontrastThreshold(const rapidjson::Value& doc);
    double getSIFTedgeThreshold(const rapidjson::Value& doc);
    double getSIFTsigma(const rapidjson::Value& doc);

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

private:
    vector<string> detectorTypePath;
    vector<string> descriptorTypePath;
    vector<string> matcherTypePath;
    vector<string> SIFTConfigPath;
    vector<string> SURFConfigPath;
    vector<string> FREAKConfigPath;
};

} // namespace fys

#endif // _H_JSON_FEATURES

