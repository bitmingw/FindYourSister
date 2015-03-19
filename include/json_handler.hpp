// Copyright (c) 2015, Ming Wen

#ifndef _H_JSON_HANDLER
#define _H_JSON_HANDLER

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

using namespace std;

namespace fys{

// helper class
class ImageSize
{
public:
    ImageSize();
    ImageSize(int nrows, int ncols);
    ~ImageSize();
    int nrows;
    int ncols;
};

class ImageRegion
{
public:
    ImageRegion();
    ImageRegion(int xmin, int xmax, int ymin, int ymax);
    ~ImageRegion();
    int xmin;
    int xmax;
    int ymin;
    int ymax;
};

class ImageObject
{
public:
    ImageObject(string name, int id, ImageRegion& region);
    ~ImageObject(); 
    string name;
    int id;
    ImageRegion region;
};


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
    void setIntVal(const rapidjson::Document& doc, vector<string> position, int newVal);
    double getDoubleVal(const rapidjson::Document& doc, vector<string> position);
    void setDoubleVal(const rapidjson::Document& doc, vector<string> position, double newVal);
    string getStrVal(const rapidjson::Document& doc, vector<string> position);
    void setStrVal(const rapidjson::Document& doc, vector<string> position, string newVal);

private:
    string jsonFilename;
    string jsonStr;
};


// features class
class JsonFeatures : public JsonHandler
{

public:
    JsonFeatures(string filename);
    ~JsonFeatures();
    string getDetectorType();
    void setDetectorType(string type);
    string getDescriptorType();
    void setDescriptorType(string type);
    string getMatcherType();
    void setMatcherType(string type);

private:
    string detectorType;
    string descriptorType;
    string matcherType;
};


// images class
class JsonImages: public JsonHandler
{

public:
    JsonImages(string filename);
    ~JsonImages();
    int getNumImages();
    string getFilename(int imageIdx);
    string getFolderName(int imageIdx);
    ImageSize getImageSize(int imageIdx);
    int getNumObjects();
    string getObjectName(int imageIdx, int objectIdx);
    int getObjectId(int imageIdx, int objectIdx);
    ImageRegion getObjectRegion(int imageIdx, int objectIdx);
};

} // namespace fys

#endif // _H_JSON_HANDLER

