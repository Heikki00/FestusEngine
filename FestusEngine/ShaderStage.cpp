#pragma once
#include "ShaderStage.h"
#include "CoreEngine.h"
#include "ResourceManager.h"

ShaderStage::ShaderStage(const string& filename, GLenum type): filename(filename), type(type)
{
	ID = glCreateShader(type);

	const GLchar* srcStrings[1];

	std::string src = resourceManager->getShaderSource(filename);


	srcStrings[0] = src.c_str();
	GLint len = src.length();


	glShaderSource(ID, 1, srcStrings, &len);

	glCompileShader(ID);


	I32 param = -1;
	glGetShaderiv(ID, GL_COMPILE_STATUS, &param);

	if (param != GL_TRUE) {
		I32 maxLen = 2048;
		I32 actual_len = 0;
		char log[2048];
		glGetShaderInfoLog(ID, maxLen, &actual_len, log);
		Debug::log(ErrorType::SHADER_ERROR, "Failed to compile shader %s. Info log:\n%s", filename.c_str(), log);
		
		ID = 0;
		return;
	}




}

ShaderStage::~ShaderStage()
{
	glDeleteShader(ID);
}

GLuint ShaderStage::getID() const
{
	return ID;
}

GLenum ShaderStage::getType() const
{
	return type;
}

string ShaderStage::getFilename() const
{
	return filename;
}
