#pragma once


#include <iostream>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <tuple>
#include "../image/image.h"

class ImageAtlas {
    private:
        Image img;
        std::unordered_map<std::string, std::tuple<float, float, float, float>> imagesStitched;

    public:
        ImageAtlas();

        void init();

        void addImg(Image& img, std::string id);

        std::tuple<float, float, float, float> getTexCoords(std::string id);
};
