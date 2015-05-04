// Copyright (c) 2015, Ming Wen

#include "fys.hpp"
#include "util.hpp"
#include "json_features.hpp"

using namespace std;
using namespace cv;

namespace fys {

// -------- JSON FEATURES --------

JsonFeatures::JsonFeatures(string filename) 
    : JsonHandler(filename) 
{
    // Set lookup values to json file
    detectorTypePath.push_back("detector");
    extractorTypePath.push_back("extractor");
    matcherTypePath.push_back("matcher");
    SIFTConfigPath.push_back("siftConfig");
    SURFConfigPath.push_back("surfConfig");
    FREAKConfigPath.push_back("freakConfig");
    BFMatcherConfigPath.push_back("BFMatcherConfig");

    // Set types
    this->detectorType = getDetectorType(this->doc);
    this->extractorType = getExtractorType(this->doc);
    this->matcherType = getMatcherType(this->doc);
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
JsonFeatures::getExtractorType(const rapidjson::Value& doc)
{
    return getStrVal(doc, this->extractorTypePath); 
}

void
JsonFeatures::setExtractorType(rapidjson::Value& doc, string newType)
{
    setStrVal(doc, this->extractorTypePath, newType);
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

// -------- BFMATCHER CONFIG --------

string
JsonFeatures::getBFMatcherNormStr(const rapidjson::Value& doc)
{
    vector<string> path = this->BFMatcherConfigPath;
    path.push_back("normType");
    return getStrVal(doc, path);
}

int
JsonFeatures::getBFMatcherNormType(string strType)
{
    if (strType == "NORM_L1") {
        return NORM_L1;
    }
    else if (strType == "NORM_L2") {
        return NORM_L2;
    }
    else if (strType == "NORM_HAMMING") {
        return NORM_HAMMING;
    }
    else if (strType == "NORM_HAMMING2") {
        return NORM_HAMMING2;
    }
    else {
        return NORM_L2;
    }
}

bool
JsonFeatures::getBFMatcherCrossCheck(const rapidjson::Value& doc)
{
    vector<string> path = this->BFMatcherConfigPath;
    path.push_back("crossCheck");
    return getBoolVal(doc, path);
}

// -------- CONFIG RETRIVAL --------

// Don't forget to register the algorithms here
vector<string>
JsonFeatures::getParameters(string usage)
{
    if (usage == "detector") {
        if (this->detectorType == "SIFT") {
            return this->getSIFTparameters();
        } 
        else if (this->detectorType == "SURF") {
            return this->getSURFparameters();
        }
        else if (this->detectorType == "FREAK") {
            return this->getFREAKparameters();
        }
    }
    else if (usage == "extractor") {
        if (this->extractorType == "SIFT") {
            return this->getSIFTparameters();
        } 
        else if (this->extractorType == "SURF") {
            return this->getSURFparameters();
        }
        else if (this->extractorType == "FREAK") {
            return this->getFREAKparameters();
        }
    }
    else if (usage == "matcher") {
        if (this->matcherType == "BFMatcher") {
            return this->getBFMatcherParameters();
        }
    }

    // Should not go here
    return vector<string>();
}

vector<string>
JsonFeatures::getSIFTparameters()
{
    vector<string> parameters;
    parameters.push_back(itoa(this->getSIFTnfeatures(this->doc)));
    parameters.push_back(itoa(this->getSIFTnOctaveLayers(this->doc)));
    parameters.push_back(ftoa(this->getSIFTcontrastThreshold(this->doc)));
    parameters.push_back(ftoa(this->getSIFTedgeThreshold(this->doc)));
    parameters.push_back(ftoa(this->getSIFTsigma(this->doc)));
    return parameters;
}

vector<string>
JsonFeatures::getSURFparameters()
{
    vector<string> parameters;
    parameters.push_back(ftoa(this->getSURFhessianThreshold(this->doc)));
    parameters.push_back(itoa(this->getSURFnOctaves(this->doc)));
    parameters.push_back(itoa(this->getSURFnOctaveLayers(this->doc)));
    parameters.push_back(btoa(this->getSURFextended(this->doc)));
    parameters.push_back(btoa(this->getSURFupright(this->doc)));
    return parameters;
}

vector<string>
JsonFeatures::getFREAKparameters()
{
    vector<string> parameters;
    parameters.push_back(btoa(this->getFREAKorientationNormalized(this->doc)));
    parameters.push_back(btoa(this->getFREAKscaleNormalized(this->doc)));
    parameters.push_back(ftoa(this->getFREAKpatternScale(this->doc)));
    parameters.push_back(itoa(this->getFREAKnOctaves(this->doc)));
    return parameters;
}

vector<string>
JsonFeatures::getBFMatcherParameters()
{
    vector<string> parameters;
    parameters.push_back(itoa(this->getBFMatcherNormType(this->getBFMatcherNormStr(this->doc))));
    parameters.push_back(btoa(this->getBFMatcherCrossCheck(this->doc)));
    return parameters;
}

} // namespace fys

