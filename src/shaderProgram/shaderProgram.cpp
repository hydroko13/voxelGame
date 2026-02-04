#include "shaderProgram.h"

ShaderProgram::ShaderProgram() {

}

void ShaderProgram::destroy() {

	

	glCheckErrorBefore("glDeleteProgram");
	glDeleteProgram(this->program_gpu_handle);
	glCheckErrorAfter("glDeleteProgram");

}

void ShaderProgram::init() {
	glCheckErrorBefore("glCreateProgram");
	this->program_gpu_handle = glCreateProgram();
	glCheckErrorAfter("glCreateProgram");



}

void ShaderProgram::use() {
	glCheckErrorBefore("glUseProgram");
	glUseProgram(this->program_gpu_handle);
	glCheckErrorAfter("glUseProgram");



}

void ShaderProgram::attachShader(Shader& shader) {
	
	glCheckErrorBefore("glAttachShader");
	glAttachShader(this->program_gpu_handle, shader.getHandle());
	glCheckErrorAfter("glAttachShader");
}

ShaderProgramStatus ShaderProgram::link() {

	glCheckErrorBefore("glLinkProgram");
	glLinkProgram(this->program_gpu_handle);
	glCheckErrorAfter("glLinkProgram");

	int linkStatus;

	glCheckErrorBefore("glGetProgramiv");
	glGetProgramiv(this->program_gpu_handle, GL_LINK_STATUS, &linkStatus);
	glCheckErrorAfter("glGetProgramiv");

	if (linkStatus == 0) {
		char infoLog[512];
		std::cout << "Shader Program Link failed: " << this->program_gpu_handle << std::endl;


		glCheckErrorBefore("glGetProgramInfoLog");
		glGetProgramInfoLog(this->program_gpu_handle, 512, NULL, infoLog);
		glCheckErrorAfter("glGetProgramInfoLog");

		std::cout << "Failure log: " << infoLog << std::endl;
		return ShaderProgramStatus::LinkFailed;
	}
	else {
		std::cout << "Shader Program Link success: " << this->program_gpu_handle << std::endl;
	}


	return ShaderProgramStatus::LinkedSuccessfully;


}

void ShaderProgram::setInt(const char* name, int v) {
	glCheckErrorBefore("glGetUniformLocation");
	GLint l = glGetUniformLocation(this->program_gpu_handle, name);
	glCheckErrorAfter("glGetUniformLocation");

	glCheckErrorBefore("glUniform1i");
	glUniform1i(l, v);
	glCheckErrorAfter("glUniform1i");


}

void ShaderProgram::setFloat(const char* name, float v) {
	glCheckErrorBefore("glGetUniformLocation");
	GLint l = glGetUniformLocation(this->program_gpu_handle, name);
	glCheckErrorAfter("glGetUniformLocation");

	glCheckErrorBefore("glUniform1f");
	glUniform1f(l, v);
	glCheckErrorAfter("glUniform1f");


}


void ShaderProgram::setMat4f(const char* name, glm::mat4& v) {
	glCheckErrorBefore("glGetUniformLocation");
	GLint l = glGetUniformLocation(this->program_gpu_handle, name);
	glCheckErrorAfter("glGetUniformLocation");

	glCheckErrorBefore("glUniformMatrix4fv");
	glUniformMatrix4fv(l, 1, GL_FALSE, glm::value_ptr(v));
	glCheckErrorAfter("glUniformMatrix4fv");

}
