#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "../glerror/glerror.h"
#include <iostream>
#include <unordered_map>
#include "../image/image.h"
#include <string>
#include <tuple>
#include "../imageAtlas/imageAtlas.h"


class Block {
    public:
        std::tuple<float, float, float, float> texCoordsTopFace;
        std::tuple<float, float, float, float> texCoordsBottomFace;
        std::tuple<float, float, float, float> texCoordsNorthFace;
        std::tuple<float, float, float, float> texCoordsSouthFace;
        std::tuple<float, float, float, float> texCoordsWestFace;
        std::tuple<float, float, float, float> texCoordsEastFace;

        Block();

        Block(ImageAtlas &atlas, std::string topFace, std::string bottomFace, std::string northFace, std::string southFace, std::string westFace, std::string eastFace);
};