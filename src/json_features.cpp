// Copyright (c) 2015, Ming Wen

#include "fys.hpp"
#include "json_features.hpp"

using namespace std;

namespace fys {

// -------- SIFT CONFIG CLASS --------

SiftConfig::SiftConfig() {}

SiftConfig::SiftConfig(int nfeatures, int nOctaveLayers, double contrastThreshold,
        double edgeThreshold, double sigma)
    : nfeatures(nfeatures), nOctaveLayers(nOctaveLayers),
      contrastThreshold(contrastThreshold), edgeThreshold(edgeThreshold),
      sigma(sigma) {}

SiftConfig::~SiftConfig() {}

// -------- SURF CONFIG CLASS --------

SurfConfig::SurfConfig() {}

SurfConfig::SurfConfig(double hessianThreshold, int nOctaves, int nOctaveLayers,
        bool isExtended, bool isUpright)
    : hessianThreshold(hessianThreshold),
      nOctaves(nOctaves), nOctaveLayers(nOctaveLayers),
      isExtended(isExtended), isUpright(isUpright) {}

SurfConfig::~SurfConfig() {}

// -------- FREAK CONFIG CLASS --------

FreakConfig::FreakConfig() {}

FreakConfig::FreakConfig(bool orientNormal, bool scaleNormal, double patternScale, int nOctaves)
    : orientNormal(orientNormal), scaleNormal(scaleNormal),
      patternScale(patternScale), nOctaves(nOctaves) {}

FreakConfig::~FreakConfig() {}

// -------- JSON FEATURES --------

JsonFeatures::JsonFeatures(string filename) 
    : JsonHandler(filename) 
{
    detectorTypePath.push_back("detector");
    descriptorTypePath.push_back("descriptor");
    matcherTypePath.push_back("matcher");
    SIFTConfigPath.push_back("siftConfig");
    SURFConfigPath.push_back("surfConfig");
    FREAKConfigPath.push_back("freakConfig");
}

JsonFeatures::~JsonFeatures() {}

// -------- FEATURE TYPES --------

string
JsonFeatures::getDetectorType(const rapidjson::Value& doc)
{
    return getStrVal(doc, this->detectorTypePath); 
}

void
JsonFeatures::setDetectorType(rapidjson::Value& doc, string newType)
{
    setStrVal(doc, this->detectorTypePath, newType);
}

string
JsonFeatures::getDescriptorType(const rapidjson::Value& doc)
{
    return getStrVal(doc, this->descriptorTypePath); 
}

void
JsonFeatures::setDescriptorType(rapidjson::Value& doc, string newType)
{
    setStrVal(doc, this->descriptorTypePath, newType);
}

string
JsonFeatures::getMatcherType(const rapidjson::Value& doc)
{
    return getStrVal(doc, this->matcherTypePath); 
}

void
JsonFeatures::setMatcherType(rapidjson::Value& doc, string newType)
{
    setStrVal(doc, this->matcherTypePath, newType);
}

// -------- SIFT CONFIG --------

int
JsonFeatures::getSIFTnfeatures(const rapidjson::Value& doc)
{
    vector<string> path = this->SIFTConfigPath;
    path.push_back("nfeatures");
    return getIntVal(doc, path);
}

int
JsonFeatures::getSIFTnOctaveLayers(const rapidjson::Value& doc)
{
    vector<string> path = this->SIFTConfigPath;
    path.push_back("nOctaveLayers");
    return getIntVal(doc, path);
}

double
JsonFeatures::getSIFTcontrastThreshold(const rapidjson::Value& doc)
{
    vector<string> path = this->SIFTConfigPath;
    path.push_back("contrastThreshold");
    return getDoubleVal(doc, path);
}

double
JsonFeatures::getSIFTedgeThreshold(const rapidjson::Value& doc)
{
    vector<string> path = this->SIFTConfigPath;
    path.push_back("edgeThreshold");
    return getDoubleVal(doc, path);
}

double
JsonFeatures::getSIFTsigma(const rapidjson::Value& doc)
{
    vector<string> path = this->SIFTConfigPath;
    path.push_back("sigma");
    return getDoubleVal(doc, path);
}

// -------- SURF CONFIG --------

double
JsonFeatures::getSURFhessianThreshold(const rapidjson::Value& doc)
{
    vector<string> path = this->SURFConfigPath;
    path.push_back("hessianThreshold");
    return getDoubleVal(doc, path);
}

int
JsonFeatures::getSURFnOctaves(const rapidjson::Value& doc)
{
    vector<string> path = this->SURFConfigPath;
    path.push_back("nOctaves");
    return getIntVal(doc, path);
}

int
JsonFeatures::getSURFnOctaveLayers(const rapidjson::Value& doc)
{
    vector<string> path = this->SURFConfigPath;
    path.push_back("nOctaveLayers");
    return getIntVal(doc, path);
}

bool
JsonFeatures::getSURFextended(const rapidjson::Value& doc)
{
    vector<string> path = this->SURFConfigPath;
    path.push_back("extended");
    return getBoolVal(doc, path);
}

bool
JsonFeatures::getSURFupright(const rapidjson::Value& doc)
{
    vector<string> path = this->SURFConfigPath;
    path.push_back("upright");
    return getBoolVal(doc, path);
}

// -------- FREAK CONFIG --------

bool
JsonFeatures::getFREAKorientationNormalized(const rapidjson::Value& doc)
{
    vector<string> path = this->FREAKConfigPath;
    path.push_back("orientationNormalized");
    return getBoolVal(doc, path);
}

bool
JsonFeatures::getFREAKscaleNormalized(const rapidjson::Value& doc)
{
    vector<string> path = this->FREAKConfigPath;
    path.push_back("scaleNormalized");
    return getBoolVal(doc, path);
}

double
JsonFeatures::getFREAKpatternScale(const rapidjson::Value& doc)
{
    vector<string> path = this->FREAKConfigPath;
    path.push_back("patternScale");
    return getDoubleVal(doc, path);
}

int
JsonFeatures::getFREAKnOctaves(const rapidjson::Value& doc)
{
    vector<string> path = this->FREAKConfigPath;
    path.push_back("nOctaves");
    return getIntVal(doc, path);
}

} // namespace fys

