// Copyright (c) 2015, Ming Wen

#include "fys.hpp"
#include "util.hpp"
#include "json_features.hpp"

using namespace std;
using namespace cv;

namespace fys {

// -------- SIFT CONFIG CLASS --------

SiftConfig::SiftConfig() {}

SiftConfig::SiftConfig(int nfeatures, int nOctaveLayers, double contrastThreshold,
        double edgeThreshold, double sigma)
    : nfeatures(nfeatures), nOctaveLayers(nOctaveLayers),
      contrastThreshold(contrastThreshold), edgeThreshold(edgeThreshold),
      sigma(sigma) {}

SiftConfig::~SiftConfig() {}

SIFT*
SiftConfig::genSIFT()
{
    return new SIFT(nfeatures, nOctaveLayers, contrastThreshold,
            edgeThreshold, sigma);
}

// -------- SURF CONFIG CLASS --------

SurfConfig::SurfConfig() {}

SurfConfig::SurfConfig(double hessianThreshold, int nOctaves, int nOctaveLayers,
        bool isExtended, bool isUpright)
    : hessianThreshold(hessianThreshold),
      nOctaves(nOctaves), nOctaveLayers(nOctaveLayers),
      isExtended(isExtended), isUpright(isUpright) {}

SurfConfig::~SurfConfig() {}

SURF*
SurfConfig::genSURF()
{
    return new SURF(hessianThreshold, nOctaves, nOctaveLayers, isExtended, isUpright);
}

// -------- FREAK CONFIG CLASS --------

FreakConfig::FreakConfig() {}

FreakConfig::FreakConfig(bool orientNormal, bool scaleNormal, double patternScale, int nOctaves)
    : orientNormal(orientNormal), scaleNormal(scaleNormal),
      patternScale(patternScale), nOctaves(nOctaves) {}

FreakConfig::~FreakConfig() {}

FREAK*
FreakConfig::genFREAK()
{
    return new FREAK(orientNormal, scaleNormal, patternScale, nOctaves);
}

// -------- BFMATCHER CONFIG CLASS --------

BFMatcherConfig::BFMatcherConfig() {}

BFMatcherConfig::BFMatcherConfig(string normTypeStr, bool isCrossCheck)
    : isCrossCheck(isCrossCheck)
{
    updateNormType(normTypeStr);
}

BFMatcherConfig::~BFMatcherConfig() {}

void
BFMatcherConfig::updateNormType(string normTypeStr)
{
    if (normTypeStr == "NORM_L1") {
        this->normType = NORM_L1;
    }
    else if (normTypeStr == "NORM_L2") {
        this->normType = NORM_L2;
    }
    else if (normTypeStr == "NORM_HAMMING") {
        this->normType = NORM_HAMMING;
    }
    else if (normTypeStr == "NORM_HAMMING2") {
        this->normType = NORM_HAMMING2;
    }
    else {
        this->normType = NORM_L2;
    }
}

BFMatcher*
BFMatcherConfig::genBFMatcher()
{
    return new BFMatcher(normType, isCrossCheck);
}

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

    // Set parameter class
    if (detectorType == "SIFT" || extractorType == "SIFT") {
        genSiftConfig(this->siftParam);
    }
    else if (detectorType == "SURF" || extractorType == "SURF") {
        genSurfConfig(this->surfParam);
    }
    else if (detectorType == "FREAK" || extractorType == "FREAK") {
        genFreakConfig(this->freakParam);
    }

    if (matcherType == "BFMatcher") {
        genBFMatcherConfig(this->bfMatcherParam);
    }
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

vector<string>
JsonFeatures::getSIFTparaTypes()
{
    vector<string> types;
    types.push_back("int");
    types.push_back("int");
    types.push_back("double");
    types.push_back("double");
    types.push_back("double");
    return types;
}

vector<string>
JsonFeatures::getSIFTparaStr()
{
    vector<string> parameters;
    parameters.push_back(itoa(this->getSIFTnfeatures(this->doc)));
    parameters.push_back(itoa(this->getSIFTnOctaveLayers(this->doc)));
    parameters.push_back(ftoa(this->getSIFTcontrastThreshold(this->doc)));
    parameters.push_back(ftoa(this->getSIFTedgeThreshold(this->doc)));
    parameters.push_back(ftoa(this->getSIFTsigma(this->doc)));
    return parameters;
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
JsonFeatures::getBFMatcherNormType(const rapidjson::Value& doc)
{
    vector<string> path = this->BFMatcherConfigPath;
    path.push_back("normType");
    return getStrVal(doc, path);
}

bool
JsonFeatures::getBFMatcherCrossCheck(const rapidjson::Value& doc)
{
    vector<string> path = this->BFMatcherConfigPath;
    path.push_back("crossCheck");
    return getBoolVal(doc, path);
}

// -------- GEN CONFIG CLASS --------

void
JsonFeatures::genSiftConfig(SiftConfig& config)
{
    config.nfeatures = getSIFTnfeatures(this->doc);
    config.nOctaveLayers = getSIFTnOctaveLayers(this->doc);
    config.contrastThreshold = getSIFTcontrastThreshold(this->doc);
    config.edgeThreshold = getSIFTedgeThreshold(this->doc);
    config.sigma = getSIFTsigma(this->doc);
}

void
JsonFeatures::genSurfConfig(SurfConfig& config)
{
    config.hessianThreshold = getSURFhessianThreshold(this->doc);
    config.nOctaves = getSURFnOctaves(this->doc);
    config.nOctaveLayers = getSURFnOctaveLayers(this->doc);
    config.isExtended = getSURFextended(this->doc);
    config.isUpright = getSURFupright(this->doc);
}

void
JsonFeatures::genFreakConfig(FreakConfig& config)
{
    config.orientNormal = getFREAKorientationNormalized(this->doc);
    config.scaleNormal = getFREAKscaleNormalized(this->doc);
    config.patternScale = getFREAKpatternScale(this->doc);
    config.nOctaves = getFREAKnOctaves(this->doc);
}

void
JsonFeatures::genBFMatcherConfig(BFMatcherConfig& config)
{
    config.updateNormType(getBFMatcherNormType(this->doc));
    config.isCrossCheck = getBFMatcherCrossCheck(this->doc);
}

// -------- GEN DETECTOR / DESCRIPTOR (WRAPPER) --------

SIFT&
JsonFeatures::genSIFT()
{
    siftPtr = this->siftParam.genSIFT();
    return *siftPtr;
}

SURF&
JsonFeatures::genSURF()
{
    surfPtr = this->surfParam.genSURF();
    return *surfPtr;
}

FREAK&
JsonFeatures::genFREAK()
{
    freakPtr = this->freakParam.genFREAK();
    return *freakPtr;
}

// -------- GEN MATCHER (WRAPPER) --------

BFMatcher&
JsonFeatures::genBFMatcher()
{
    bfMatcherPtr = this->bfMatcherParam.genBFMatcher();
    return *bfMatcherPtr;
}

} // namespace fys

