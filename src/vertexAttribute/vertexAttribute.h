#pragma once

#include <glad/glad.h>


class VertexAttribute {
public:
	GLenum type;
	int count;
	int size;

	VertexAttribute(GLenum type, int count, int size);
};