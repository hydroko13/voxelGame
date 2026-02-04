#include "vertexAttribute.h"

VertexAttribute::VertexAttribute(GLenum type, int count, int size) {
	this->type = type;
	this->count = count;
	this->size = size;
}