#pragma once




#include <stb_image.h>
#include <iostream>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>

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

};