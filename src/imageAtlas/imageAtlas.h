#pragma once


#include <iostream>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <tuple>
#include <utility>
#include "../image/image.h"
#include "../util/util.h"

class ImageAtlas {
    private:
       
        std::unordered_map<std::string, std::tuple<int, int, int, int>> imagesStitched;

    public:

        Image img;
        ImageAtlas();

        void init();

        void addImg(Image& img, std::string id);

        std::tuple<float, float, float, float> getTexCoords(std::string id);
};
