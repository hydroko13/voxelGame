#pragma once




#include <stb_image.h>
#include <iostream>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <tuple>

class Image {
private:
	unsigned char* data; // IMAGE DATA IS STORED ON HEAP
public:
	int width = -1;
	int height = -1;
	bool dataInitialized = false;


	Image();

	~Image();

	void initBlank(int width, int height);

	int initFromFile(std::filesystem::path fp);

	unsigned char* getRawData();

	std::tuple<int, int, int, int> getPixel(int x, int y);

	void setPixel(int x, int y, int r, int g, int b, int a);
};