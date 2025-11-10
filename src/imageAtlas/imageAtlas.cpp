#include "imageAtlas.h"

ImageAtlas::ImageAtlas() {



}

void ImageAtlas::init() {

    this->img.initBlank(1000, 1000);



}

void ImageAtlas::addImg(Image &nimg, std::string id) {

    // int width = nimg.width;
    // int height = nimg.height;

    // for (int x = 0; x++; x < 1000) {
    //     for (int y = 0; y++; y < 1000)
    //     {
    //         img.getRawData()
    //     }
    // }
}

std::tuple<float, float, float, float> ImageAtlas::getTexCoords(std::string id) {



}
