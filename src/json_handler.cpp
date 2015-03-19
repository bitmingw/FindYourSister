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
            std::cerr << "Error: retrieved value if not of type \'int\'!" << std::endl;
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
            std::cerr << "Error: retrieved value if not of type \'int\'!" << std::endl;
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


// feature class
JsonFeatures::JsonFeatures(string filename) 
    : JsonHandler(filename) {}

JsonFeatures::~JsonFeatures() {}

string
JsonFeatures::getDetectorType()
{
    return "";    
}


// image class
JsonImages::JsonImages(string filename)
    : JsonHandler(filename) {}

JsonImages::~JsonImages() {}

} // namespace fys

