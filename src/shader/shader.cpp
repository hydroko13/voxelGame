#include "shader.h"



Shader::Shader() {


}

void Shader::destroy() {
	std::cout << "Deleted shader: " << this->filename << std::endl;
	glCheckErrorBefore("glDeleteShader");
	glDeleteShader(shader_gpu_handle);
	glCheckErrorAfter("glDeleteShader");
}

GLuint Shader::getHandle() {
	return this->shader_gpu_handle;
}

GLenum Shader::getShaderType() {
	return this->shader_type;
}

ShaderStatus Shader::init(GLenum shader_type, const char* filename) {

	this->shader_type = shader_type;
	this->filename = filename;

	glCheckErrorBefore("glCreateShader");
	this->shader_gpu_handle = glCreateShader(shader_type);
	glCheckErrorAfter("glCreateShader");

	std::filesystem::path shaderPath("resources/shaders");
	shaderPath = shaderPath / filename;


	std::ifstream fileStream(shaderPath);
	if (!fileStream.is_open()) {
		std::cout << "File failed to open: " << shaderPath << std::endl;
		return ShaderStatus::FileOpenFailed;
	}


	this->shader_source_code.clear();

	std::string line;


	while (std::getline(fileStream, line)) {

		

		

		this->shader_source_code += line + "\n";




	}
	fileStream.close();

	const char* shader_source_cstr = this->shader_source_code.c_str();
	
	glCheckErrorBefore("glShaderSource");
	glShaderSource(this->shader_gpu_handle, 1, &shader_source_cstr, nullptr);
	glCheckErrorAfter("glShaderSource");

	return ShaderStatus::InitializedSuccessfully;


}
	


ShaderStatus Shader::compile() {
	glCheckErrorBefore("glCompileShader");
	glCompileShader(this->shader_gpu_handle);
	glCheckErrorAfter("glCompileShader");

	int statusCode;
	glCheckErrorBefore("glGetShaderiv");
	glGetShaderiv(this->shader_gpu_handle, GL_COMPILE_STATUS, &statusCode);
	glCheckErrorAfter("glGetShaderiv");
	
	if (statusCode == 0) {
		std::cout << "Shader compile failed: " << this->filename << std::endl;
		char infoLog[512];
		glCheckErrorBefore("glGetShaderInfoLog");
		glGetShaderInfoLog(this->shader_gpu_handle, 512, NULL, infoLog);
		glCheckErrorAfter("glGetShaderInfoLog");
		std::cout << "Failure log: " << infoLog << std::endl;
		return ShaderStatus::CompileFailed;
	} 
	else {
		std::cout << "Shader compile success: " << this->filename << std::endl;
	}

	return ShaderStatus::CompiledSuccessfully;
}




