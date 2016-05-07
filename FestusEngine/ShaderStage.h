#pragma once


//Class that represents a single stage of a shader program. Should ONLY be used in Shader.
class ShaderStage {
public:

	//Retrieves the source and compiles the shader
	ShaderStage(const string& filename, GLenum type);

	~ShaderStage();

	//Returns OpenGL name of the ShaderStage
	GLuint getID() const;
	
	//Returns the type of this shader, for example, GL_VERTEX_SHADER or GL_GEOMETRY_SHADER
	GLenum getType() const;

	//Returns the filename of this shader, for example, VS.vs
	string getFilename() const;

private:


	GLuint ID;
	const GLenum type;
	const string filename;
};