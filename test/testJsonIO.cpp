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

} // namespace fys

