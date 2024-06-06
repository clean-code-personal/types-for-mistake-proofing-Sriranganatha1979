#include "brightener.h"

uint8_t brightenPixel(uint8_t inputPixel, uint8_t brighteningGrayscale, int& attenuatedPixelCount) {
    uint8_t brightened = inputPixel;
    if (int(inputPixel) + brighteningGrayscale > 255) {
        ++attenuatedPixelCount;
        brightened = 255;
    }
    else {
        brightened += brighteningGrayscale;
    }
    return brightened;
}

shared_ptr<BrightenedImage> BrightenWholeImage(shared_ptr<RawImage> rawInputImage ) {
    auto inputImage = rawInputImage->m_internalImage;
    int attenuatedPixelCount = 0;
    // For brightening, we add a certain grayscale (25) to every pixel.
    // While brightening, some pixels may cross the max brightness. They are
    // called 'attenuated' pixels
    auto brightenedImage = std::make_shared<BrightenedImage>(
        make_shared<Image>(inputImage->m_rows, inputImage->m_columns,
            [inputImage, &attenuatedPixelCount](uint8_t* initPixels) {
                inputImage->scanPixels([inputImage, &attenuatedPixelCount, initPixels](uint8_t inputPixel, uint16_t rows, uint16_t col, uint16_t index) {
                    initPixels[index] = brightenPixel(inputPixel, 25, attenuatedPixelCount);
                    });
        }));
    brightenedImage->m_attenuatedPixelCount = attenuatedPixelCount;
    return brightenedImage;
}

// Throws the exception std::invalid_argument if there is a mismatch between rows and column of inputImage and imageToAdd
shared_ptr<BrightenedImage> AddBrighteningImage(shared_ptr<RawImage> rawInputImage, shared_ptr<Image> imageToAdd) {
    auto inputImage = rawInputImage->m_internalImage;
    int attenuatedPixelCount = 0;
     if (imageToAdd->m_rows != inputImage->m_rows || imageToAdd->m_columns != inputImage->m_columns) {
         throw std::invalid_argument("Invalid arguments received. Mismatch between rows and column of inputImage and imageToAdd.\n");
     }
    auto brightenedImage = std::make_shared<BrightenedImage>(
        make_shared<Image>(inputImage->m_rows, inputImage->m_columns,
            [inputImage, imageToAdd, &attenuatedPixelCount](uint8_t* initPixels) {
                inputImage->scanPixels([inputImage, imageToAdd, &attenuatedPixelCount, initPixels](uint8_t inputPixel, uint16_t rows, uint16_t col, uint16_t index) {
                    initPixels[index] = brightenPixel(inputPixel, imageToAdd->getPixelAtIndex(rows, col), attenuatedPixelCount);
                    });
    }));
    brightenedImage->m_attenuatedPixelCount = attenuatedPixelCount;
    return brightenedImage;
}

