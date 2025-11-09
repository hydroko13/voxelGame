#include "elementBuffer.h"

ElementBuffer::ElementBuffer()
{

}


void ElementBuffer::destroy()
{


	glCheckErrorBefore("glDeleteBuffers");
	glDeleteBuffers(1, &ebo_gpu_handle);
	glCheckErrorAfter("glDeleteBuffers");
}

void ElementBuffer::init(GLenum usage) {
	glCheckErrorBefore("glGenBuffers");
	glGenBuffers(1, &ebo_gpu_handle);
	glCheckErrorAfter("glGenBuffers");
	this->usage = usage;


}

void ElementBuffer::bind() {
	glCheckErrorBefore("glBindBuffer");
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_gpu_handle);
	glCheckErrorAfter("glBindBuffer");
}

void ElementBuffer::setData(void* data, int size) {
	glCheckErrorBefore("glBufferData");
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, this->usage);
	glCheckErrorAfter("glBufferData");
}
