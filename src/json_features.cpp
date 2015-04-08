// Copyright (c) 2015, Ming Wen

#include "fys.hpp"
#include "json_features.hpp"

using namespace std;

namespace fys {

JsonFeatures::JsonFeatures(string filename) 
    : JsonHandler(filename) 
{
    detectorTypePath.push_back("detector");
    descriptorTypePath.push_back("descriptor");
    matcherTypePath.push_back("matcher");
    SIFT_ConfigPath.push_back("SIFT_config");
    SURF_ConfigPath.push_back("SURF_config");
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
    vector<string> path = this->SIFT_ConfigPath;
    path.push_back("nfeatures");
    return getIntVal(doc, path);
}

int
JsonFeatures::getSIFTnOctaveLayers(const rapidjson::Value& doc)
{
    vector<string> path = this->SIFT_ConfigPath;
    path.push_back("nOctaveLayers");
    return getIntVal(doc, path);
}

double
JsonFeatures::getSIFTcontrastThreshold(const rapidjson::Value& doc)
{
    vector<string> path = this->SIFT_ConfigPath;
    path.push_back("contrastThreshold");
    return getDoubleVal(doc, path);
}

double
JsonFeatures::getSIFTedgeThreshold(const rapidjson::Value& doc)
{
    vector<string> path = this->SIFT_ConfigPath;
    path.push_back("edgeThreshold");
    return getDoubleVal(doc, path);
}

double
JsonFeatures::getSIFTsigma(const rapidjson::Value& doc)
{
    vector<string> path = this->SIFT_ConfigPath;
    path.push_back("sigma");
    return getDoubleVal(doc, path);
}

// -------- SURF CONFIG --------

double
JsonFeatures::getSURFhessianThreshold(const rapidjson::Value& doc)
{
    vector<string> path = this->SURF_ConfigPath;
    path.push_back("hessianThreshold");
    return getDoubleVal(doc, path);
}

int
JsonFeatures::getSURFnOctaves(const rapidjson::Value& doc)
{
    vector<string> path = this->SURF_ConfigPath;
    path.push_back("nOctaves");
    return getIntVal(doc, path);
}

int
JsonFeatures::getSURFnOctaveLayers(const rapidjson::Value& doc)
{
    vector<string> path = this->SURF_ConfigPath;
    path.push_back("nOctaveLayers");
    return getIntVal(doc, path);
}

bool
JsonFeatures::getSURFextended(const rapidjson::Value& doc)
{
    vector<string> path = this->SURF_ConfigPath;
    path.push_back("extended");
    return getBoolVal(doc, path);
}

bool
JsonFeatures::getSURFupright(const rapidjson::Value& doc)
{
    vector<string> path = this->SURF_ConfigPath;
    path.push_back("upright");
    return getBoolVal(doc, path);
}

} // namespace fys

