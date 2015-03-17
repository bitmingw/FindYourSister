// Copyright (c) 2015, Ming Wen

#include "../include/fys.hpp"
#include "../include/json_handler.hpp"

using namespace std;

namespace fys{

JsonFeatures::JsonFeatures(string filename) 
    : jsonFilename(filename) {}

#if 0
void JsonFeatures::openJson()
{
    if (stream.is_open()) {
        std::cerr << "Warning: features file has been opened." << std::endl;
    }
    else {
        string fullPath = "../config/" + this->jsonFilename;
        this->stream.open(fullPath.c_str(), ios::in | ios::out);
    }
}

void JsonFeatures::readJson()
{
    if (stream.is_open()) {
        char buf[MAX_LINE];
        string bufStr = "";
        while (!stream.eof()) {
            stream.getline(buf, MAX_LINE);
            bufStr = buf;
            jsonStr += bufStr;
        }
    }
}
#endif

} // namespace fys

