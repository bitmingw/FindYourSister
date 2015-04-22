// Copyright (c) 2015, Ming Wen

#include "fys.hpp"
#include "util.hpp"
#include "json_images.hpp"

using namespace std;

namespace fys {

// -------- HELPER --------

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

ImageObject::ImageObject()
    : name(""), id(-1), region(ImageRegion()) {}
ImageObject::ImageObject(string name, int id, ImageRegion region)
    : name(name), id(id), region(region) {}
ImageObject::~ImageObject() {}

ImageSample::ImageSample()
    : train(0), validate(0), test(0), total(0) {}
ImageSample::ImageSample(int train, int validate, int test)
    : train(train), validate(validate), test(test), total(train + validate + test) {}
ImageSample::~ImageSample() {}

// -------- JSON IMAGES CLASS --------

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

vector<string>
JsonImages::getTypePath(int imageType)
{
    vector<string> searchPath;
    switch (imageType) {
        case TRAIN_TYPE:
            searchPath = trainImagePath;
            break;
        case VALIDATE_TYPE:
            searchPath = validateImagePath;
            break;
        case TEST_TYPE:
            searchPath = testImagePath;
            break;
        default:
            std::cerr << "Invalid image category!" << std::endl;
            return searchPath; 
    }
    return searchPath; 
}

string
JsonImages::getFileName(const rapidjson::Value& doc, int imageType, int imageIdx)
{
    vector<string> searchPath = getTypePath(imageType);
    if (searchPath.size() == 0) {
        return "";
    }
    searchPath.push_back(itoa(imageIdx));
    searchPath.push_back("filename");
    return getStrVal(doc, searchPath);
}

string
JsonImages::getFolderName(const rapidjson::Value& doc, int imageType, int imageIdx)
{
    vector<string> searchPath = getTypePath(imageType);
    if (searchPath.size() == 0) {
        return "";
    }
    searchPath.push_back(itoa(imageIdx));
    searchPath.push_back("folder");
    return getStrVal(doc, searchPath);
}

ImageSize
JsonImages::getImageSize(const rapidjson::Value& doc, int imageType, int imageIdx)
{
    vector<string> searchPath = getTypePath(imageType);
    if (searchPath.size() == 0) {
        return ImageSize();
    }
    searchPath.push_back(itoa(imageIdx));
    searchPath.push_back("size");

    // check nrows and ncols one by one
    searchPath.push_back("nrows");
    int nrows = getIntVal(doc, searchPath);
    searchPath.pop_back();
    searchPath.push_back("ncols");
    int ncols = getIntVal(doc, searchPath);
    return ImageSize(nrows, ncols);
}

int
JsonImages::getNumObject(const rapidjson::Value& doc, int imageType, int imageIdx)
{
    vector<string> searchPath = getTypePath(imageType);
    if (searchPath.size() == 0) {
        return 0; // return empty
    }
    searchPath.push_back(itoa(imageIdx));
    searchPath.push_back("objects");
    return getArraySize(doc, searchPath);
}

ImageObject
JsonImages::getObjectByID(const rapidjson::Value& doc, int imageType, int imageIdx, int objectIdx)
{
    // value to be returned
    ImageObject dummyObj;

    vector<string> searchPath = getTypePath(imageType);
    if (searchPath.size() == 0) {
        return dummyObj; // return an empty vector
    }
    searchPath.push_back(itoa(imageIdx));
    searchPath.push_back("objects");

    // local variables used in the loop
    vector<string> tmpPath;
    string objName;
    int objID;
    int objXMin, objXMax, objYMin, objYMax;

    // check each object one by one, until the id is found
    const rapidjson::Value& objRoot = getReference(doc, searchPath);
    for (size_t i = 0; i < objRoot.Size(); ++i) {
        tmpPath = searchPath;
        tmpPath.push_back(itoa(i));
        tmpPath.push_back("id");
        objID = getIntVal(doc, tmpPath);
        if (objID != objectIdx) {
            continue;
        }
        tmpPath.pop_back();
        tmpPath.push_back("name");
        objName = getStrVal(doc, tmpPath);
        tmpPath.pop_back();
        tmpPath.push_back("region");
        tmpPath.push_back("xmin");
        objXMin = getIntVal(doc, tmpPath);
        tmpPath.pop_back();
        tmpPath.push_back("xmax");
        objXMax = getIntVal(doc, tmpPath);
        tmpPath.pop_back();
        tmpPath.push_back("ymin");
        objYMin = getIntVal(doc, tmpPath);
        tmpPath.pop_back();
        tmpPath.push_back("ymax");
        objYMax = getIntVal(doc, tmpPath);
        return ImageObject(objName, objID, ImageRegion(objXMin, objXMax, objYMin, objYMax));
    }
    // should NOT visit here
    return dummyObj; 
}

vector<ImageObject>
JsonImages::getObjectList(const rapidjson::Value& doc, int imageType, int imageIdx)
{
    // value to be returned
    vector<ImageObject> objVec;

    vector<string> searchPath = getTypePath(imageType);
    if (searchPath.size() == 0) {
        return objVec; // return an empty vector
    }
    searchPath.push_back(itoa(imageIdx));
    searchPath.push_back("objects");

    // local variables used in the loop
    vector<string> tmpPath;
    string objName;
    int objID;
    int objXMin, objXMax, objYMin, objYMax;

    // check each object one by one
    const rapidjson::Value& objRoot = getReference(doc, searchPath);
    for (size_t i = 0; i < objRoot.Size(); ++i) {
        tmpPath = searchPath;
        tmpPath.push_back(itoa(i));
        tmpPath.push_back("name");
        objName = getStrVal(doc, tmpPath);
        tmpPath.pop_back();
        tmpPath.push_back("id");
        objID = getIntVal(doc, tmpPath);
        tmpPath.pop_back();
        tmpPath.push_back("region");
        tmpPath.push_back("xmin");
        objXMin = getIntVal(doc, tmpPath);
        tmpPath.pop_back();
        tmpPath.push_back("xmax");
        objXMax = getIntVal(doc, tmpPath);
        tmpPath.pop_back();
        tmpPath.push_back("ymin");
        objYMin = getIntVal(doc, tmpPath);
        tmpPath.pop_back();
        tmpPath.push_back("ymax");
        objYMax = getIntVal(doc, tmpPath);
        objVec.push_back(ImageObject(objName, objID, 
            ImageRegion(objXMin, objXMax, objYMin, objYMax)));
    }
    
    return objVec; 
}

vector<ImageObject>
JsonImages::getObjectListByName(const rapidjson::Value& doc, int imageType,
    int imageIdx, string objectName)
{
    // value to be returned
    vector<ImageObject> objVec;

    vector<string> searchPath = getTypePath(imageType);
    if (searchPath.size() == 0) {
        return objVec; // return an empty vector
    }
    searchPath.push_back(itoa(imageIdx));
    searchPath.push_back("objects");

    // local variables used in the loop
    vector<string> tmpPath;
    string objName;
    int objID;
    int objXMin, objXMax, objYMin, objYMax;

    // check each object one by one
    const rapidjson::Value& objRoot = getReference(doc, searchPath);
    for (size_t i = 0; i < objRoot.Size(); ++i) {
        tmpPath = searchPath;
        tmpPath.push_back(itoa(i));
        tmpPath.push_back("name");
        objName = getStrVal(doc, tmpPath);
        if (objName != objectName) {
            continue;
        }
        tmpPath.pop_back();
        tmpPath.push_back("id");
        objID = getIntVal(doc, tmpPath);
        tmpPath.pop_back();
        tmpPath.push_back("region");
        tmpPath.push_back("xmin");
        objXMin = getIntVal(doc, tmpPath);
        tmpPath.pop_back();
        tmpPath.push_back("xmax");
        objXMax = getIntVal(doc, tmpPath);
        tmpPath.pop_back();
        tmpPath.push_back("ymin");
        objYMin = getIntVal(doc, tmpPath);
        tmpPath.pop_back();
        tmpPath.push_back("ymax");
        objYMax = getIntVal(doc, tmpPath);
        objVec.push_back(ImageObject(objName, objID, 
            ImageRegion(objXMin, objXMax, objYMin, objYMax)));
    }
     
    return objVec; 
}

} // namespace fys

