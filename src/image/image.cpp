#define STB_IMAGE_IMPLEMENTATION
#include "image.h"

Image::Image() {

}

Image::~Image() {
	if (this->dataInitialized) {
		stbi_image_free(this->data);
	}
	
}

void Image::initBlank(int width, int height) {
	if (dataInitialized) {
		stbi_image_free(this->data);
	}
	this->width = width;
	this->height = height;
	this->data = (unsigned char*) malloc(width * height * 4);

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			int idx = (y * width + x) * 4;
			this->data[idx] = 0;
			this->data[idx+1] = 0;
			this->data[idx+2] = 0;
			this->data[idx+3] = 0;

		}
	}

	this->dataInitialized = true;
}

int Image::initFromFile(std::filesystem::path fp) {
	if (dataInitialized) {
		stbi_image_free(this->data);
	}
	int channels;
	stbi_set_flip_vertically_on_load(true);
	std::string fpString = fp.string();
	const char* filepathCstr = fpString.c_str();
	this->data = stbi_load(filepathCstr, &this->width, &this->height, &channels, 4);
	if (!this->data) {
		std::cout << "IMAGE FAILED TO LOAD: " << filepathCstr << std::endl;
		return 1;
	}
	else {
		std::cout << "IMAGE LOAD SUCCESS: " << filepathCstr << std::endl;
		std::cout << "CHANNELS IN IMAGE FILE: " << channels << std::endl;
	}
	this->dataInitialized = true;

	return 0;


}


unsigned char* Image::getRawData() {
	return this->data;
}

std::tuple<int, int, int, int> Image::getPixel(int x, int y)
{
	int idx = (y * width + x) * 4;
	return std::tuple<int, int, int, int>((int) this->data[idx], (int) this->data[idx + 1], (int) this->data[idx + 2], (int) this->data[idx+3]);
}

void Image::setPixel(int x, int y, int r, int g, int b, int a)
{
	int idx = (y * width + x) * 4;
	this->data[idx] = (unsigned char) r;
	this->data[idx+1] = (unsigned char) g;
	this->data[idx + 2] = (unsigned char) b;
	this->data[idx + 3] = (unsigned char) a;


}