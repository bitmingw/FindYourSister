// Copyright (c) 2015, Ming Wen

#ifndef _H_JSON_IMAGES
#define _H_JSON_IMAGES

#include "json_base.hpp"

using namespace std;

namespace fys {

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
    ImageObject();
    ImageObject(string name, int id, ImageRegion region);
    ~ImageObject(); 
    string name;
    int id;
    ImageRegion region;
};

class ImageSample
{
public:
    ImageSample();
    ImageSample(int train, int validate, int test);
    ~ImageSample();
    int train;
    int validate;
    int test;
    int total;
};

// images class
class JsonImages: public JsonHandler
{

public:
    JsonImages(string filename);
    ~JsonImages();

    ImageSample getNumImage(const rapidjson::Value& doc);
    string getFileName(const rapidjson::Value& doc, int imageType, int imageIdx);
    string getFolderName(const rapidjson::Value& doc, int imageType, int imageIdx);
    ImageSize getImageSize(const rapidjson::Value& doc, int imageType, int imageIdx);
    int getNumObject(const rapidjson::Value& doc, int imageType, int imageIdx); 

    ImageObject getObjectByID(const rapidjson::Value& doc, int imageType,
        int imageIdx, int objectIdx);
    vector<ImageObject> getObjectList(const rapidjson::Value& doc, int imageType, int imageIdx);
    vector<ImageObject> getObjectListByName(const rapidjson::Value& doc, int imageType,
        int imageIdx, string objectName);

private:
    vector<string> trainImagePath;
    vector<string> validateImagePath;
    vector<string> testImagePath;

protected:
    vector<string> getTypePath(int imageType);
};

} // namespace fys

#endif // _H_JSON_IMAGES

