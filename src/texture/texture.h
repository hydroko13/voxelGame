#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../glerror/glerror.h"
#include <iostream>

#include "../image/image.h"

class Texture {

private:
	GLuint gpu_texture_handle = NULL;

public:




	Texture();

	void init();

	void fromImage(Image& image);

	GLuint getHandle();

	void bind();

	void destroy();

};
