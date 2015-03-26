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

ImageObject::ImageObject(string name, int id, ImageRegion region)
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

const rapidjson::Value&
JsonHandler::getReference(const rapidjson::Value& doc, vector<string> position)
{
    assert(position.size() >= 1);

    int checkVal; // convert string to number if necessary
    if ((checkVal = checkDigit(position[0])) == -1) {
        // position[0] is a string
        const rapidjson::Value& tmp = doc[position[0].c_str()]; 
        if (position.size() == 1) {
            return tmp;
        }
        else {
            vector<string>::iterator it = position.begin();
            it++;
            vector<string> lessPosition(it, position.end());
            return getReference(tmp, lessPosition);
        }
    }
    else {
         // position[0] is a number
        const rapidjson::Value& tmp = doc[checkVal]; 
        if (position.size() == 1) {
            return tmp;
        }
        else {
            vector<string>::iterator it = position.begin();
            it++;
            vector<string> lessPosition(it, position.end());
            return getReference(tmp, lessPosition);
        }
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
        //ImageRegion reg = ImageRegion(objXMin, objXMax, objYMin, objYMax);
        objVec.push_back(ImageObject(objName, objID, ImageRegion(objXMin, objXMax, objYMin, objYMax)));
    }
    
    return objVec; 
}

} // namespace fys

