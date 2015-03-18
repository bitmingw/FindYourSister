// Copyright (c) 2015, Ming Wen

#include "../include/fys.hpp"
#include "../include/json_handler.hpp"

using namespace std;

namespace fys{

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

JsonFeatures::JsonFeatures(string filename) 
    : JsonHandler(filename) {}

JsonFeatures::~JsonFeatures() {}

} // namespace fys

