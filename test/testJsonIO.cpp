// Copyright (c) 2015, Ming Wen

#include "../include/fys.hpp"
#include "../include/json_handler.hpp"

using namespace std;

void testBasicIO(string featuresFile)
{
    std::cout << "==== Test Start: BasicIO ====" << std::endl;

    fys::JsonFeature jf = new fys::JsonFeatures(featuresFile);
    jf.readJsonFile();
    std::cout << jf.getFileStr();

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
    std::cout << jf.getFileStr();
    jf.writeJsonFile();

    std::cout << "==== Test End: BasicIO ====" << std::endl;
}
