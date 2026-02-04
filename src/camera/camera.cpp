#include "camera.h"


Camera::Camera() {
	this->pos = glm::vec3(0.0f, 0.0f, 0.0f);
	this->yaw = 0.0f;
	this->pitch = 0.0f;
	this->directionVec = glm::vec3(0.0f, 0.0f, -1.0f);

}



void Camera::updateViewMat() {
	this->directionVec = glm::normalize(glm::vec3(
		glm::cos(glm::radians(pitch)) * glm::cos(glm::radians(yaw)),
		glm::sin(glm::radians(pitch)),
		glm::cos(glm::radians(pitch)) * glm::sin(glm::radians(yaw))));

	

	this->viewMat = glm::lookAt(
		this->pos,
		this->pos + directionVec,
		glm::vec3(0.0f, 1.0f, 0.0f)
	);

}