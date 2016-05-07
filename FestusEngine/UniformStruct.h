#pragma once


struct Uniform;
class Shader;


//A class that represent a struct defined in uniform
class UniformStruct {
public:

	virtual ~UniformStruct() = default;
	

	//Sets the uniform, must be implemented by child class.
	//(Use shader->setUniformStructMember(uniform + "..."))
	virtual void setUniform(const string& uniform, Shader* shader) = 0;



};