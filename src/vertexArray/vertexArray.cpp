#include "vertexArray.h"

VertexArray::VertexArray()
{
	
}


void VertexArray::destroy()
{
	glCheckErrorBefore("glDeleteVertexArrays");
	glDeleteVertexArrays(1, &vao_gpu_handle);
	glCheckErrorAfter("glDeleteVertexArrays");
}

void VertexArray::init() {
	glCheckErrorBefore("glGenVertexArrays");
	glGenVertexArrays(1, &vao_gpu_handle);
	glCheckErrorAfter("glGenVertexArrays");

}

void VertexArray::beginAttribs() {
	this->attrs.clear();
}


void VertexArray::doneAttribs() {

	

	int idx = 0;
	int stride = 0;
	int offset = 0;


	for (VertexAttribute attr : this->attrs) {
		stride += attr.size;

	}



	for (VertexAttribute attr : this->attrs) {
		glCheckErrorBefore("glVertexAttribPointer");
		glVertexAttribPointer(idx, attr.count, attr.type, false, stride, (void*)offset);
		glCheckErrorAfter("glVertexAttribPointer");

		glCheckErrorBefore("glEnableVertexAttribArray");
		glEnableVertexAttribArray(idx);
		glCheckErrorAfter("glEnableVertexAttribArray");

		idx++;
		offset += attr.size;
	}
	
	
}

void VertexArray::attrib(GLenum type, int count, int size) {
	this->attrs.push_back(VertexAttribute(type, count, size));
	
}

void VertexArray::bind() {
	glCheckErrorBefore("glBindVertexArray");
	glBindVertexArray(vao_gpu_handle);
	glCheckErrorAfter("glBindVertexArray");
}


void VertexArray::unbind() {
	glCheckErrorBefore("glBindVertexArray");
	glBindVertexArray(0);
	glCheckErrorAfter("glBindVertexArray");
}