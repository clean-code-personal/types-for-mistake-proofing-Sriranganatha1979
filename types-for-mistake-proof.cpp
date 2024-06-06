#include <iostream>
#include "brightener.h"

void StoreImageAnalytics(std::shared_ptr<RawImage> rawImage) {
	// This function will store the raw (non-brightened) image for analytics
	// Here we're just pretending :)
	std::cout << "- Storing the raw image for analytics\n";
}

int main() {
	auto image = std::make_shared<Image>(512, 512, [](uint8_t* pixels) {});
	auto rawimage = std::make_shared<RawImage>(image);
	std::cout << "Brightening a 512 x 512 image\n";
	int attenuatedPixelCount = 0;
	try {
		auto brightenedImage = BrightenWholeImage(rawimage, attenuatedPixelCount);
		std::cout << "Attenuated " << attenuatedPixelCount << " pixels\n";
	}
	catch (std::invalid_argument ex)
	{
		std::cout << ex.what();
	}

	StoreImageAnalytics(std::make_shared<RawImage>(image));
}
