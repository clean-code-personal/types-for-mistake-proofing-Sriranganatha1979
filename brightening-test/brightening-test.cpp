#include "CppUnitTest.h"
#include "../brightener.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace brighteningtest
{
	TEST_CLASS(BrighteningTest)
	{
	public:

		TEST_METHOD(CheckForRowColumnMismatch)
		{
			auto image = make_shared<RawImage>(CreateImage(45, 55, 65, 75));
			//auto brightenedImage = AddBrighteningImage(
			//	image, CreateImageWithDifferentMatrixSize(0, 25, 0, 25), attenuatedPixelCount);
			auto func = [image, this] {AddBrighteningImage(
				image, this->CreateImageWithDifferentMatrixSize(0, 25, 0, 25)); };
			Assert::ExpectException<std::invalid_argument>(func);
		}

		TEST_METHOD(BrightensWholeImage)
		{
			auto image = make_shared<RawImage>(CreateImage(45, 55, 65, 254));
			auto brightenedImage = BrightenWholeImage(image);
			Assert::AreEqual(1, brightenedImage->m_attenuatedPixelCount);
			Assert::AreEqual(90, int(brightenedImage->m_internalImage->getPixelAtIndex(1, 0)));
		}

		TEST_METHOD(BrightensWithAnotherImage)
		{
			auto image = make_shared<RawImage>(CreateImage(45, 55, 65, 75));
			auto brightenedImage = AddBrighteningImage(
				image, CreateImage(0, 25, 0, 25));
            Assert::AreEqual(45, int(brightenedImage->m_internalImage->getPixelAtIndex(0, 0))); // left-side pixel is unchanged
            Assert::AreEqual(80, int(brightenedImage->m_internalImage->getPixelAtIndex(0, 1))); // right-side pixel is brightened
            Assert::AreEqual(0, brightenedImage->m_attenuatedPixelCount);
		}

		shared_ptr<Image> CreateImage(uint8_t topLeft, uint8_t topRight, uint8_t bottomLeft, uint8_t bottomRight) {
			return make_shared<Image>(2, 2, [=](uint8_t* pixels) {
				pixels[0] = topLeft; pixels[1] = topRight;
				pixels[2] = bottomLeft; pixels[3] = bottomRight;
				});
		}

		shared_ptr<Image> CreateImageWithDifferentMatrixSize(uint8_t topLeft, uint8_t topRight, uint8_t bottomLeft, uint8_t bottomRight) {
			return make_shared<Image>(1, 1, [=](uint8_t* pixels) {
				pixels[0] = topLeft;
				});
		}
	};
}
