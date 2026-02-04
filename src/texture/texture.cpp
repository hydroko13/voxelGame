#include "texture.h"


Texture::Texture() {

}

void Texture::init() {
	glCheckErrorBefore("glGenTextures");
	glGenTextures(1, &gpu_texture_handle);
	glCheckErrorAfter("glGenTextures");
	
}

void Texture::bind() {
	glCheckErrorBefore("glBindTexture");
	glBindTexture(GL_TEXTURE_2D, gpu_texture_handle);
	glCheckErrorAfter("glBindTexture");
}


void Texture::fromImage(Image& image) {
	glCheckErrorBefore("glTexImage2D");
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)image.getRawData());
	glCheckErrorAfter("glTexImage2D");
	glCheckErrorBefore("glGenerateMipmap");
	glGenerateMipmap(GL_TEXTURE_2D);
	glCheckErrorAfter("glGenerateMipmap");

}


void Texture::destroy() {
	glCheckErrorBefore("glDeleteTextures");
	glDeleteTextures(1, &gpu_texture_handle);
	glCheckErrorAfter("glDeleteTextures");
}


GLuint Texture::getHandle() {
	return this->gpu_texture_handle;
}