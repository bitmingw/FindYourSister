// Copyright (c) 2015, Ming Wen

#ifndef _H_JSON_BASE
#define _H_JSON_BASE

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

using namespace std;

namespace fys {

// base class
class JsonHandler
{

public:
    JsonHandler(string filename);
    ~JsonHandler();
    void readJsonFile(); // open & read json file
    string getFileStr(); // return json file as string
    string getDocStr(rapidjson::StringBuffer& buffer); // return json document as string
    void updateStr(rapidjson::StringBuffer& buffer); // update this->jsonStr
    void writeJsonFile(); // open & write json file

    int getIntVal(const rapidjson::Value& doc, vector<string> position);
    void setIntVal(rapidjson::Value& doc, vector<string> position, int newVal);
    double getDoubleVal(const rapidjson::Value& doc, vector<string> position);
    void setDoubleVal(rapidjson::Value& doc, vector<string> position, double newVal);
    string getStrVal(const rapidjson::Value& doc, vector<string> position);
    void setStrVal(rapidjson::Value& doc, vector<string> position, string newVal);
    size_t getArraySize(const rapidjson::Value& doc, vector<string> position);

private:
    string jsonFilename;
    string jsonStr;

protected:
    const rapidjson::Value& getReference(const rapidjson::Value& doc, vector<string> position);
};

} // namespace fys

#endif // _H_JSON_BASE
