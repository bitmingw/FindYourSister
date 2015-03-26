// Copyright (c) 2015, Ming Wen

#include "fys.hpp"
#include "json_handler.hpp"

using namespace std;

namespace fys{

// helper class
ImageSize::ImageSize()
    : nrows(0), ncols(0) {}
ImageSize::ImageSize(int nrows, int ncols)
    : nrows(nrows), ncols(ncols) {}
ImageSize::~ImageSize() {}

ImageRegion::ImageRegion()
    : xmin(0), xmax(0), ymin(0), ymax(0) {}
ImageRegion::ImageRegion(int xmin, int xmax, int ymin, int ymax)
    : xmin(xmin), xmax(xmax), ymin(ymin), ymax(ymax) {}
ImageRegion::~ImageRegion() {}

ImageObject::ImageObject(string name, int id, ImageRegion& region)
    : name(name), id(id), region(region) {}
ImageObject::~ImageObject() {}

ImageSample::ImageSample()
    : train(0), validate(0), test(0), total(0) {}
ImageSample::ImageSample(int train, int validate, int test)
    : train(train), validate(validate), test(test), total(train + validate + test) {}
ImageSample::~ImageSample() {}


// base class
JsonHandler::JsonHandler(string filename) 
    : jsonFilename(filename) {}

JsonHandler::~JsonHandler() {}

void
JsonHandler::readJsonFile()
{
    string fullPath = "../config/" + this->jsonFilename;
    ifstream stream_r;
    stream_r.open(fullPath.c_str(), ios_base::in);

    if (stream_r.is_open()) {
        char buf[MAX_LINE];
        string bufStr = "";
        while (!stream_r.eof()) {
            stream_r.getline(buf, MAX_LINE);
            bufStr = buf;
            this->jsonStr += bufStr;
        }
        stream_r.close();
    }
    else {
        std::cerr << "Error: can\'t open " << this->jsonFilename << " for reading!" << std::endl;
    }
}

string
JsonHandler::getFileStr()
{
    return this->jsonStr;
}

string
JsonHandler::getDocStr(rapidjson::StringBuffer& buffer)
{
    return buffer.GetString();
}

void
JsonHandler::updateStr(rapidjson::StringBuffer& buffer)
{
    this->jsonStr = buffer.GetString();
}

void
JsonHandler::writeJsonFile()
{
    string fullPath = "../config/" + this->jsonFilename;
    ofstream stream_w;
    stream_w.open(fullPath.c_str(), ios_base::out);

    if (stream_w.is_open()) {
        stream_w << this->jsonStr;
        stream_w.close();
    }
    else {
        std::cerr << "Error: can\'t open " << this->jsonFilename << " for writing!" << std::endl;
    }
}

int
JsonHandler::getIntVal(const rapidjson::Value& doc, vector<string> position)
{
    assert(position.size() >= 1);

    int checkVal; // convert string to number if necessary
    if ((checkVal = checkDigit(position[0])) == -1) {
        // position[0] is a string
        const rapidjson::Value& tmp = doc[position[0].c_str()]; 
        if (position.size() == 1 && tmp.IsInt()) {
            return tmp.GetInt();
        }
        else if (position.size() == 1 && (!tmp.IsInt())) {
            std::cerr << "Error: retrieved value is not type \'int\'!" << std::endl;
            return -1;
        }
        else {
            vector<string>::iterator it = position.begin();
            it++;
            vector<string> lessPosition(it, position.end());
            return getIntVal(tmp, lessPosition);
        }
    }
    else {
         // position[0] is a number
        const rapidjson::Value& tmp = doc[checkVal]; 
        if (position.size() == 1 && tmp.IsInt()) {
            return tmp.GetInt();
        }
        else if (position.size() == 1 && (!tmp.IsInt())) {
            std::cerr << "Error: retrieved value is not type \'int\'!" << std::endl;
            return -1;
        }
        else {
            vector<string>::iterator it = position.begin();
            it++;
            vector<string> lessPosition(it, position.end());
            return getIntVal(tmp, lessPosition);
        }
    }
}

void
JsonHandler::setIntVal(rapidjson::Value& doc, vector<string> position, int newVal)
{
    assert(position.size() >= 1);

    int checkVal; // convert string to number if necessary
    if ((checkVal = checkDigit(position[0])) == -1) {
        // position[0] is a string
        rapidjson::Value& tmp = doc[position[0].c_str()]; 
        if (position.size() == 1) {
            tmp.SetInt(newVal);
            return;
        }
        else {
            vector<string>::iterator it = position.begin();
            it++;
            vector<string> lessPosition(it, position.end());
            setIntVal(tmp, lessPosition, newVal);
        }
    }
    else {
         // position[0] is a number
        rapidjson::Value& tmp = doc[checkVal]; 
        if (position.size() == 1) {
            tmp.SetInt(newVal);
            return;
        }
        else {
            vector<string>::iterator it = position.begin();
            it++;
            vector<string> lessPosition(it, position.end());
            setIntVal(tmp, lessPosition, newVal);
        }
    }
}

double
JsonHandler::getDoubleVal(const rapidjson::Value& doc, vector<string> position)
{
    assert(position.size() >= 1);

    int checkVal; // convert string to number if necessary
    if ((checkVal = checkDigit(position[0])) == -1) {
        // position[0] is a string
        const rapidjson::Value& tmp = doc[position[0].c_str()]; 
        if (position.size() == 1 && tmp.IsDouble()) {
            return tmp.GetDouble();
        }
        else if (position.size() == 1 && (!tmp.IsDouble())) {
            std::cerr << "Error: retrieved value is not type \'double\'!" << std::endl;
            return -1.0;
        }
        else {
            vector<string>::iterator it = position.begin();
            it++;
            vector<string> lessPosition(it, position.end());
            return getDoubleVal(tmp, lessPosition);
        }
    }
    else {
         // position[0] is a number
        const rapidjson::Value& tmp = doc[checkVal]; 
        if (position.size() == 1 && tmp.IsDouble()) {
            return tmp.GetDouble();
        }
        else if (position.size() == 1 && (!tmp.IsDouble())) {
            std::cerr << "Error: retrieved value is not type \'double\'!" << std::endl;
            return -1.0;
        }
        else {
            vector<string>::iterator it = position.begin();
            it++;
            vector<string> lessPosition(it, position.end());
            return getDoubleVal(tmp, lessPosition);
        }
    }
}

void
JsonHandler::setDoubleVal(rapidjson::Value& doc, vector<string> position, double newVal)
{
    assert(position.size() >= 1);

    int checkVal; // convert string to number if necessary
    if ((checkVal = checkDigit(position[0])) == -1) {
        // position[0] is a string
        rapidjson::Value& tmp = doc[position[0].c_str()]; 
        if (position.size() == 1) {
            tmp.SetDouble(newVal);
            return;
        }
        else {
            vector<string>::iterator it = position.begin();
            it++;
            vector<string> lessPosition(it, position.end());
            setDoubleVal(tmp, lessPosition, newVal);
        }
    }
    else {
         // position[0] is a number
        rapidjson::Value& tmp = doc[checkVal]; 
        if (position.size() == 1) {
            tmp.SetDouble(newVal);
            return;
        }
        else {
            vector<string>::iterator it = position.begin();
            it++;
            vector<string> lessPosition(it, position.end());
            setDoubleVal(tmp, lessPosition, newVal);
        }
    }
}

string
JsonHandler::getStrVal(const rapidjson::Value& doc, vector<string> position)
{
    assert(position.size() >= 1);

    int checkVal; // convert string to number if necessary
    if ((checkVal = checkDigit(position[0])) == -1) {
        // position[0] is a string
        const rapidjson::Value& tmp = doc[position[0].c_str()]; 
        if (position.size() == 1 && tmp.IsString()) {
            return tmp.GetString();
        }
        else if (position.size() == 1 && (!tmp.IsString())) {
            std::cerr << "Error: retrieved value is not type \'string\'!" << std::endl;
            return "";
        }
        else {
            vector<string>::iterator it = position.begin();
            it++;
            vector<string> lessPosition(it, position.end());
            return getStrVal(tmp, lessPosition);
        }
    }
    else {
         // position[0] is a number
        const rapidjson::Value& tmp = doc[checkVal]; 
        if (position.size() == 1 && tmp.IsString()) {
            return tmp.GetString();
        }
        else if (position.size() == 1 && (!tmp.IsString())) {
            std::cerr << "Error: retrieved value is not type \'string\'!" << std::endl;
            return "";
        }
        else {
            vector<string>::iterator it = position.begin();
            it++;
            vector<string> lessPosition(it, position.end());
            return getStrVal(tmp, lessPosition);
        }
    }
}

void
JsonHandler::setStrVal(rapidjson::Value& doc, vector<string> position, string newVal)
{
    assert(position.size() >= 1);

    int checkVal; // convert string to number if necessary
    if ((checkVal = checkDigit(position[0])) == -1) {
        // position[0] is a string
        rapidjson::Value& tmp = doc[position[0].c_str()]; 
        if (position.size() == 1) {
            tmp.SetString(newVal.c_str(), newVal.size());
            return;
        }
        else {
            vector<string>::iterator it = position.begin();
            it++;
            vector<string> lessPosition(it, position.end());
            setStrVal(tmp, lessPosition, newVal);
        }
    }
    else {
         // position[0] is a number
        rapidjson::Value& tmp = doc[checkVal]; 
        if (position.size() == 1) {
            tmp.SetString(newVal.c_str(), newVal.size());
            return;
        }
        else {
            vector<string>::iterator it = position.begin();
            it++;
            vector<string> lessPosition(it, position.end());
            setStrVal(tmp, lessPosition, newVal);
        }
    }
}

size_t
JsonHandler::getArraySize(const rapidjson::Value& doc, vector<string> position)
{
    assert(position.size() >= 1);

    int checkVal; // convert string to number if necessary
    if ((checkVal = checkDigit(position[0])) == -1) {
        // position[0] is a string
        const rapidjson::Value& tmp = doc[position[0].c_str()]; 
        if (position.size() == 1 && tmp.IsArray()) {
            return tmp.Size();
        }
        else if (position.size() == 1 && (!tmp.IsArray())) {
            std::cerr << "Error: retrieved value is not type \'array\'!" << std::endl;
            return 0;
        }
        else {
            vector<string>::iterator it = position.begin();
            it++;
            vector<string> lessPosition(it, position.end());
            return getArraySize(tmp, lessPosition);
        }
    }
    else {
         // position[0] is a number
        const rapidjson::Value& tmp = doc[checkVal]; 
        if (position.size() == 1 && tmp.IsArray()) {
            return tmp.IsArray();
        }
        else if (position.size() == 1 && (!tmp.IsArray())) {
            std::cerr << "Error: retrieved value is not type \'array\'!" << std::endl;
            return 0;
        }
        else {
            vector<string>::iterator it = position.begin();
            it++;
            vector<string> lessPosition(it, position.end());
            return getArraySize(tmp, lessPosition);
        }
    }
}


// feature class
JsonFeatures::JsonFeatures(string filename) 
    : JsonHandler(filename) 
{
    detectorTypePath.push_back("detector");
    descriptorTypePath.push_back("descriptor");
    matcherTypePath.push_back("matcher");
}

JsonFeatures::~JsonFeatures() {}

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


// image class
JsonImages::JsonImages(string filename)
    : JsonHandler(filename) 
{
    trainImagePath.push_back("train");
    validateImagePath.push_back("validate");
    testImagePath.push_back("test");
}

JsonImages::~JsonImages() {}

ImageSample
JsonImages::getNumImage(const rapidjson::Value& doc)
{
    int train = getArraySize(doc, trainImagePath);
    int validate = getArraySize(doc, validateImagePath);
    int test = getArraySize(doc, testImagePath);
    return ImageSample(train, validate, test);
}

} // namespace fys

