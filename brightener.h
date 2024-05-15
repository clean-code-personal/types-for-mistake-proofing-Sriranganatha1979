#include <cstdint>
#include "image.h"

using namespace std;

shared_ptr<Image> BrightenWholeImage(shared_ptr<Image> inputImage, int& attenuatedPixelCount);
// Throws the exception std::invalid_argument if there is a mismatch between rows and column of inputImage and imageToAdd
shared_ptr<Image> AddBrighteningImage(shared_ptr<Image> inputImage, shared_ptr<Image> imageToAdd,
    int& attenuatedPixelCount);
