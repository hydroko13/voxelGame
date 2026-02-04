#include "glerror.h"

void _glCheckErrorBefore(const char* label) {
	while (true) {
		GLenum glerr = glGetError();
		if (glerr != GL_NO_ERROR) {
			switch (glerr) {
			case GL_INVALID_ENUM:
				std::cout << "uncaught ERROR before " << label << ": " << "GL_INVALID_ENUM" << std::endl;
				break;
			case GL_INVALID_VALUE:
				std::cout << "uncaught ERROR before " << label << ": " << "GL_INVALID_VALUE" << std::endl;
				break;
			case GL_INVALID_OPERATION:
				std::cout << "uncaught ERROR before " << label << ": " << "GL_INVALID_OPERATION" << std::endl;
				break;
			case GL_OUT_OF_MEMORY:
				std::cout << "uncaught ERROR before " << label << ": " << "GL_OUT_OF_MEMORY" << std::endl;
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				std::cout << "uncaught ERROR before " << label << ": " << "GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl;
				break;
			}

		}
		else {
			break;
		}

	}
	
}

void _glCheckErrorAfter(const char* label) {
	while (true) {
		GLenum glerr = glGetError();
		if (glerr != GL_NO_ERROR) {
			switch (glerr) {
			case GL_INVALID_ENUM:
				std::cout << "ERROR at " << label << " : " << "GL_INVALID_ENUM" << std::endl;
				break;
			case GL_INVALID_VALUE:
				std::cout << "ERROR at " << label << ": " << "GL_INVALID_VALUE" << std::endl;
				break;
			case GL_INVALID_OPERATION:
				std::cout << "ERROR at " << label << ": " << "GL_INVALID_OPERATION" << std::endl;
				break;
			case GL_OUT_OF_MEMORY:
				std::cout << "ERROR at " << label << ": " << "GL_OUT_OF_MEMORY" << std::endl;
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				std::cout << "ERROR at " << label << ": " << "GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl;
				break;
			}

		}
		else {
			break;
		}

	}
}

