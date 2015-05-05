// Copyright (c) 2015, Ming Wen

#ifndef _H_FYS_TEST
#define _H_FYS_TEST

using namespace std;

namespace fys {

void testBasicIO(string featuresFile);
void testGetSet(string imagesFile);
void testFeatureType(string featuresFile);
void testImageProperties(string imagesFile);
void testSIFTGetting(string featuresFile);
void testSURFGetting(string featuresFile);
void testFREAKGetting(string featuresFile);
void testSIFT(string featuresFile, string imagesFile);
void testSIFTdetector(string featuresFile);
void testAlgoPara(string featuresFile);
void testReadImageWrapper(string featuresFile, string imagesFile);

} // namespace fys

#endif // _H_FYS_TEST

