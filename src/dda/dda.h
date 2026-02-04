#pragma once

#include <glad/glad.h>
#include  <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "../glerror/glerror.h"
#include <iostream>
#include "../image/image.h"
#include "../vertexBuffer/vertexBuffer.h"
#include "../elementBuffer/elementBuffer.h"
#include "../vertexArray/vertexArray.h"
#include "../imageAtlas/imageAtlas.h"
#include "../shaderProgram/shaderProgram.h"
#include <tuple>	

class DDA {
public:
	glm::fvec3 startPos;
	glm::fvec3 directionVectorNormalized;
	int stepX;
	int stepY;
	int stepZ;
	int voxelX;
	int voxelY;
	int voxelZ;

	DDA(glm::fvec3 pos, glm::fvec3 dir);

	void takeStep();

};
