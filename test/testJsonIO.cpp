// Copyright (c) 2015, Ming Wen

#include "fys.hpp"
#include "json_base.hpp"
#include "json_images.hpp"
#include "json_features.hpp"
#include "test.hpp"

using namespace std;

namespace fys {

void testBasicIO(string featuresFile)
{
    std::cout << "==== Test Start: BasicIO ====" << std::endl;

    JsonFeatures jf = JsonFeatures(featuresFile);
    jf.readJsonFile();
    std::cout << jf.getFileStr() << std::endl;

    rapidjson::Document doc;
    doc.Parse(jf.getFileStr().c_str());

    if (doc.HasMember("detector") && doc["detector"].IsNull()) {
        rapidjson::Value& detectorVal = doc["detector"];
        detectorVal.SetString("SIFT");
    }

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    jf.updateStr(buffer);
    std::cout << jf.getFileStr() << std::endl;
    jf.writeJsonFile();

    std::cout << "==== Test End: BasicIO ====" << std::endl;
}

void testGetSet(string imageFile) 
{
    std::cout << "==== Test Start: Getter and Setter ====" << std::endl;

    JsonImages ji = JsonImages(imageFile);
    ji.readJsonFile();
    
    rapidjson::Document doc;
    doc.Parse(ji.getFileStr().c_str());

    // getIntVal
    vector<string> path1 = vector<string>();
    path1.push_back("train");
    path1.push_back("0");
    path1.push_back("size");
    path1.push_back("nrows");
    std::cout << "Number of rows in the image: " << ji.getIntVal(doc, path1) << std::endl;

    // getDoubleVal & setDoubleVal
    vector<string> path2 = vector<string>();
    path2.push_back("train");
    path2.push_back("0");
    path2.push_back("objects");
    path2.push_back("0");
    path2.push_back("region");
    path2.push_back("ymin");
    std::cout << "Original: min y value of the object: " << ji.getDoubleVal(doc, path2) << std::endl;
    ji.setDoubleVal(doc, path2, 10);
    std::cout << "New: min y value of the object: " << ji.getDoubleVal(doc, path2) << std::endl;

    // getStrVal & setStrVal
    vector<string> path3 = vector<string>();
    path3.push_back("train");
    path3.push_back("0");
    path3.push_back("filename");
    std::cout << "Original: file name of image: " << ji.getStrVal(doc, path3) << std::endl;
    ji.setStrVal(doc, path3, "ff.jpg");
    std::cout << "New: file name of image: " << ji.getStrVal(doc, path3) << std::endl;

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    std::cout << "Json string after change: " << ji.getDocStr(buffer) << std::endl;

    std::cout << "==== Test End: Getter and Setter ====" << std::endl;
}

void testFeatureType(string featuresFile)
{
    std::cout << "==== Test Start: Feature Types ====" << std::endl;

    JsonFeatures jf = JsonFeatures(featuresFile);
    jf.readJsonFile();

    rapidjson::Document doc;
    doc.Parse(jf.getFileStr().c_str());

    std::cout << "Original: detector type: " << jf.getDetectorType(doc) << std::endl;
    jf.setDetectorType(doc, "SURF");
    std::cout << "New: detector type: " << jf.getDetectorType(doc) << std::endl;
    
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    std::cout << "Json string after change: " << jf.getDocStr(buffer) << std::endl;

    std::cout << "==== Test End: Feature Types ====" << std::endl;
}

void testImageProperties(string imagesFile)
{
    std::cout << "==== Test Start: Number of Images ====" << std::endl;

    JsonImages ji = JsonImages(imagesFile);
    ji.readJsonFile();

    rapidjson::Document doc;
    doc.Parse(ji.getFileStr().c_str());

    ImageSample stat = ji.getNumImage(doc);
    std::cout << "Training set: " << stat.train << std::endl;
    std::cout << "Validation set: " << stat.validate << std::endl;
    std::cout << "Test set: " << stat.test << std::endl;
    std::cout << "Total: " << stat.total << std::endl;
    std::cout << std::endl;
    std::cout << "File name of image 0: " << ji.getFileName(doc, TRAIN_TYPE, 0) << std::endl;
    std::cout << "Folder name of image 0: " << ji.getFolderName(doc, TRAIN_TYPE, 0) << std::endl;
    
    ImageSize is = ji.getImageSize(doc, TRAIN_TYPE, 0);
    std::cout << "Rows: " << is.nrows << std::endl;
    std::cout << "Columns: " << is.ncols << std::endl;

    std::cout << "Number of objects in image 0: " << ji.getNumObject(doc, TRAIN_TYPE, 0) << std::endl;
    vector<ImageObject> oblist = ji.getObjectList(doc, TRAIN_TYPE, 0);
    std::cout << "Object name: " << oblist[0].name << std::endl;
    std::cout << "Object ID: " << oblist[0].id << std::endl;
    std::cout << "Object region: " << oblist[0].region.xmin << " " << oblist[0].region.xmax << " " \
        << oblist[0].region.ymin << " " << oblist[0].region.ymax << std::endl;

    std::cout << std::endl;
    ImageObject ob = ji.getObjectByID(doc, TRAIN_TYPE, 0, 0);
    std::cout << "Object name: " << ob.name << std::endl;
    std::cout << "Object ID: " << ob.id << std::endl;
    std::cout << "Object region: " << ob.region.xmin << " " << ob.region.xmax << " " \
        << ob.region.ymin << " " << ob.region.ymax << std::endl;
    
    std::cout << std::endl;
    vector<ImageObject> oblist2 = ji.getObjectListByName(doc, TRAIN_TYPE, 0, "signal");
    std::cout << "Object name: " << oblist2[0].name << std::endl;
    std::cout << "Object ID: " << oblist2[0].id << std::endl;

    std::cout << "==== Test End: Number of Images ====" << std::endl;
}

void testSIFTGetting(string featuresFile)
{
    std::cout << "==== Test Start: Getting SIFT Config ====" << std::endl;

    JsonFeatures jf = JsonFeatures(featuresFile);
    jf.readJsonFile();

    rapidjson::Document doc;
    doc.Parse(jf.getFileStr().c_str());

    std::cout << "Number of features: " << jf.getSIFTnfeatures(doc) << std::endl;
    std::cout << "Number of layers: " << jf.getSIFTnOctaveLayers(doc) << std::endl;
    std::cout << "Contrast threshold: " << jf.getSIFTcontrastThreshold(doc) << std::endl;
    std::cout << "Edge threshold: " << jf.getSIFTedgeThreshold(doc) << std::endl;
    std::cout << "Sigma: " << jf.getSIFTsigma(doc) << std::endl;
    
    std::cout << "==== Test End: Getting SIFT Config ====" << std::endl;
}

void testSURFGetting(string featuresFile)
{
    std::cout << "==== Test Start: Getting SURF Config ====" << std::endl;

    JsonFeatures jf = JsonFeatures(featuresFile);
    jf.readJsonFile();

    rapidjson::Document doc;
    doc.Parse(jf.getFileStr().c_str());

    std::cout << "Hessian Threshold: " << jf.getSURFhessianThreshold(doc) << std::endl;
    std::cout << "Number of octaves: " << jf.getSURFnOctaves(doc) << std::endl;
    std::cout << "Number of layers: " << jf.getSURFnOctaveLayers(doc) << std::endl;
    std::cout << "Is extended: " << jf.getSURFextended(doc) << std::endl;
    std::cout << "Is upright: " << jf.getSURFupright(doc) << std::endl;
    
    std::cout << "==== Test End: Getting SURF Config ====" << std::endl;
}

} // namespace fys

