// Copyright (c) 2015, Ming Wen

#include "fys.hpp"
#include "features.hpp"

using namespace std;

namespace fys {

Features::Features(JsonFeatures& jf)
{
    detectorType = jf.getDetectorType(jf.doc);
    descriptorType = jf.getDescriptorType(jf.doc);
    matcherType = jf.getMatcherType(jf.doc);
}

Features::~Features() {}

} // namespace fys

