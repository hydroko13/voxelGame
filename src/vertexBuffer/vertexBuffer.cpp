#include "vertexBuffer.h"

VertexBuffer::VertexBuffer()
{

}


void VertexBuffer::destroy()
{

	
	glCheckErrorBefore("glDeleteBuffers");
	glDeleteBuffers(1, &vbo_gpu_handle);
	glCheckErrorAfter("glDeleteBuffers");
}

void VertexBuffer::init(GLenum usage) {
	glCheckErrorBefore("glGenBuffers");
	glGenBuffers(1, &vbo_gpu_handle);
	glCheckErrorAfter("glGenBuffers");
	this->usage = usage;
	

}

void VertexBuffer::bind() {
	glCheckErrorBefore("glBindBuffer");
	glBindBuffer(GL_ARRAY_BUFFER, vbo_gpu_handle);
	glCheckErrorAfter("glBindBuffer");
}

void VertexBuffer::setData(void* data, int size) {
	glCheckErrorBefore("glBufferData");
	glBufferData(GL_ARRAY_BUFFER, size, data, this->usage);
	glCheckErrorAfter("glBufferData");
}
