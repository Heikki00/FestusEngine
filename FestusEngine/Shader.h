#pragma once

class ShaderStage;
class Material;

//Enum that defines where to get the uniform's value
enum UniformType {
	UNDEFINED,
	MATERIAL,
	RENDERINGENGINE,
	RENDERLAYER,
	MVP,
	MV,
	MODEL,
	PERSPECTIVE,
	EYEPOS

};

//Struct that represents a single uniform.
struct Uniform {

	//Name of the uniform, with prefix
	string name;
	//Type of the uniform, GL_FLOAT for example. GL_NONE for structs
	GLenum type;
	//Location of the uniform, 0 for structs
	U32 location;
	//Where to get the uniform's value
	UniformType uniformType = UNDEFINED;

	//Compares the names, used for sorting
	bool operator <(const Uniform& u) const{
		return name < u.name;
	}

};


//Class that represents a shader program. This class is used to bind the shader and to set it's uniforms. It offers automatic and manual uniform updating
class Shader {
public:

	//Compiles and links the shader stages, loads all of the uniforms
	Shader(const string& filename);

	~Shader();

	//Binds the shader
	void bind();

	//Returns the OpenGL name of the shader program
	GLuint getID() const{ return ID; }

	//Returns the .glsl filename of this shader
	string getFilename() const { return filename; }
	
	//Sets an uniform to a value. If the uniform is not found, does nothing. Use setUniformStructMember for struct members, this won't work for that
	template<typename T>
	void setUniform(const string& name, const T& val) const {
		Uniform u; u.name = name;

		auto i = std::lower_bound(uniforms.begin(), uniforms.end(), u);
		if (i->name == name)this->setUniform(i->location, val);
	}

	//Sets an uniform struct member to a value. If the uniform is not found, does nothing
	template<typename T>
	void setUniformStructMember(const string& name, const T& val) const {
		Uniform u; u.name = name;
		auto i = std::lower_bound(structMembers.begin(), structMembers.end(), u);
		if(i->name == name)this->setUniform(i->location, val);
	}

	//Automatically updates uniforms based on their UniformType.
	void updateUniforms(Material* m, Transform& t);


	
private:
	std::vector<ShaderStage*> shaders;

	GLuint ID;

	std::vector<Uniform> structMembers;

	std::vector<Uniform> uniforms;
	
	const string filename;


	void setUniform(GLuint loc, F32 val) const { glUniform1f(loc, val); };
	void setUniform(GLuint loc, I32 val) const { glUniform1i(loc, val); };
	void setUniform(GLuint loc, U32 val) const { glUniform1ui(loc, val); };

	void setUniform(GLuint loc, const Vector2& val) const { glUniform2fv(loc, 1, val.toArray()); };

	void setUniform(GLuint loc, const Vector3& val) const { glUniform3fv(loc, 1, val.toArray()); };

	void setUniform(GLuint loc, const Vector4& val) const { glUniform4fv(loc, 1, val.toArray()); };

	void setUniform(GLuint loc, const Matrix3& val) const { glUniformMatrix3fv(loc, 1, GL_TRUE, val.toArray()); };

	void setUniform(GLuint loc, const Matrix4& val) const { glUniformMatrix4fv(loc, 1, GL_TRUE, val.toArray()); };

};
