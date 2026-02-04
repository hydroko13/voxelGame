#include "imageAtlas.h"

ImageAtlas::ImageAtlas() {



}

void ImageAtlas::init() {

    this->img.initBlank(1000, 1000);



}



void ImageAtlas::addImg(Image &nimg, std::string id) {

    int width = nimg.width;
    int height = nimg.height;
    bool foundSpot = false;


    for (int x = 0; x < 1000;  x++) {
        if (foundSpot) {
            break;
        }


        for (int y = 0; y < 1000; y++)
        {

            if (foundSpot) {
                break;
            }
            std::tuple<int, int, int, int> newImgRect(x, y, width, height);

            bool overlapped = false;



            for (const auto& kv : this->imagesStitched) {
                std::tuple<int, int, int, int> rect = kv.second;

                if (rectOverlapsStrict(
                    ((float)std::get<0>(newImgRect)), ((float)std::get<1>(newImgRect)), ((float)std::get<2>(newImgRect)), ((float)std::get<3>(newImgRect)),
                    ((float)std::get<0>(rect)), ((float)std::get<1>(rect)), ((float)std::get<2>(rect)), ((float)std::get<3>(rect))
                )) {
                    overlapped = true;
                    break;
                }

            }
           


            if (!overlapped) {
                if ((x <= (1000 - width)) && (y <= (1000 - height))) {
                    for (int nx = x; nx < x + width; nx++) {
                        for (int ny = y; ny < y + height; ny++) {

                            std::tuple<int, int, int, int> rgba = nimg.getPixel(nx - x, ny - y);

                            this->img.setPixel(nx, ny, std::get<0>(rgba), std::get<1>(rgba), std::get<2>(rgba), std::get<3>(rgba));
                        }
                    }

                    std::pair<std::string, std::tuple<int, int, int, int>> p(id, newImgRect);

                    this->imagesStitched.insert(p);
                    foundSpot = true;
                }

                
                
            }


        }
    }
}

std::tuple<float, float, float, float> ImageAtlas::getTexCoords(std::string id) {



    std::tuple<int, int, int, int>& intRect = this->imagesStitched.at(id);

    

    return std::tuple<float, float, float, float>(
        ((float)std::get<0>(intRect)) / 1000,
        ((float)std::get<1>(intRect)) / 1000,
        (((float)std::get<0>(intRect)) + ((float)std::get<2>(intRect))) / 1000,
        (((float)std::get<1>(intRect)) + ((float)std::get<3>(intRect))) / 1000
    );


}
