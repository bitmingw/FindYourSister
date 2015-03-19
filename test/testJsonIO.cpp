// Copyright (c) 2015, Ming Wen

#include "fys.hpp"
#include "json_handler.hpp"

using namespace std;

namespace fys {

void testBasicIO(string featuresFile)
{
    std::cout << "==== Test Start: BasicIO ====" << std::endl;

    fys::JsonFeatures jf = fys::JsonFeatures(featuresFile);
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

    fys::JsonImages ji = fys::JsonImages(imageFile);
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
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    std::cout << "Json string after parse: " << ji.getDocStr(buffer) << std::endl;

    doc.Parse(ji.getFileStr().c_str());
    vector<string> path2 = vector<string>();
    path2.push_back("train");
    path2.push_back("0");
    path2.push_back("objects");
    path2.push_back("0");
    path2.push_back("region");
    path2.push_back("ymin");
    std::cout << "min y value of the object: " << ji.getIntVal(doc, path2) << std::endl;

    std::cout << "==== Test End: Getter and Setter ====" << std::endl;
}

} // namespace fys

