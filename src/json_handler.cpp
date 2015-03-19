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
JsonHandler::getIntVal(rapidjson::Document& doc, vector<string> position)
{
    // Note: an index number is represented as a string
    // So we need to check digits before reference
    int checkVal = -1;
    string subVal = "";
    if ((checkVal = checkDigit(position[0])) == -1) {
        subVal = position[0];
        rapidjson::Value& tmp = doc[position[0].c_str()];
        for (unsigned int i = 1; i < position.size(); ++i) {
            if ((checkVal = checkDigit(position[i])) == -1) {
                tmp = tmp[position[i].c_str()];
            }
            else {
                tmp = tmp[checkVal];
            }
        }
        if (tmp.IsInt()) {
            return tmp.GetInt();
        }
        else {
            std::cerr << "Error: retrieved value is not of type \'int\'!" << std::endl;
            return -1;
        }
    }
    else {
        rapidjson::Value& tmp = doc[checkVal];
        for (unsigned int i = 1; i < position.size(); ++i) {
            if ((checkVal = checkDigit(position[i])) == -1) {
                tmp = tmp[position[i].c_str()];
            }
            else {
                tmp = tmp[checkVal];
            }
        }
        if (tmp.IsInt()) {
            return tmp.GetInt();
        }
        else {
            std::cerr << "Error: retrieved value is not of type \'int\'!" << std::endl;
            return -1;
        }
    }
    // should never reach here
    //return -1;
}


// feature class
JsonFeatures::JsonFeatures(string filename) 
    : JsonHandler(filename) {}

JsonFeatures::~JsonFeatures() {}

string
JsonFeatures::getDetectorType()
{
    return "";    
}

} // namespace fys

