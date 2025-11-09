#pragma once

#include <glad/glad.h>
#include  <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "../glerror/glerror.h"
#include <iostream>
#include "../image/image.h"

class Camera {

public:
	glm::vec3 pos;
	glm::vec3 directionVec;
	float pitch;
	float yaw;
	glm::mat4 viewMat;

	Camera();

	void updateViewMat();


};
