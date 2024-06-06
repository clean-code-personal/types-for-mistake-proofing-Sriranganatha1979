#pragma once
#include <cstdint>
#include <iostream>
#include <functional>

class Image {
public:
	Image(uint16_t rows, uint16_t columns, std::function<void(uint8_t*)> pixelInitializer)
		: m_rows(rows), m_columns(columns) {
		m_pixels = new uint8_t[m_rows * m_columns];
		pixelInitializer(m_pixels);
	}
	~Image() {
		std::cout << "freeing pixel memory.\n";
		delete[] m_pixels;
	}
	bool imageSizeIsValid() {
		return m_rows <= 1024 && m_columns <= 1024;
	}
	uint16_t pixelIndex(const uint16_t x, const uint16_t y) {
		return x * m_columns + y;
	}
	uint8_t getPixelAtIndex(const uint16_t x, const uint16_t y) {
		return m_pixels[pixelIndex(x, y)];
	}
	void scanPixels(std::function<void(const uint8_t, const uint16_t, const uint16_t, const uint16_t)> takePixel) {
		for (int x = 0; x < m_rows; x++) {
			for (int y = 0; y < m_columns; y++) {
				takePixel(getPixelAtIndex(x, y), x, y, pixelIndex(x,y));
			}
		}
	}
	const uint16_t m_rows;
	const uint16_t m_columns;
	uint8_t* m_pixels; // max 1k x 1k image
};

class RawImage {
public:
	RawImage(std::shared_ptr<Image> rawImage) {	
		m_internalImage = rawImage;
	}
	std::shared_ptr<Image> m_internalImage;
};

class BrightenedImage {
public:
	BrightenedImage(std::shared_ptr<Image> brightenedImage) {
		m_internalImage = brightenedImage;
	}
	std::shared_ptr<Image> m_internalImage;
	int m_attenuatedPixelCount = 0;
};
