#include <cstdint>
#include "image.h"

using namespace std;

shared_ptr<BrightenedImage> BrightenWholeImage(shared_ptr<RawImage> inputImage);
// Throws the exception std::invalid_argument if there is a mismatch between rows and column of inputImage and imageToAdd
shared_ptr<BrightenedImage> AddBrighteningImage(shared_ptr<RawImage> inputImage, shared_ptr<Image> imageToAdd);
