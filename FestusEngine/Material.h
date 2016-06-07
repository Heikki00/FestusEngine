#pragma once
class GameObject;

//A class that represents a material of an object. Material inherits MappedValues, and all the uniforms with "M_" prefix will be retrieved from there.
class Material : public MappedValues{

public:


	Material(const string& filename);
	
	virtual ~Material() = default;

	//Function that is responsible for binding the shader of choice and updating its uniforms, ether automatically with Shader::updateUniforms() or manually
	//"object" is the object containing currently rendered thing that has this material, and rendertype is an typeID set by the RenderLayer.
	//Returns true if rendering should continue, or false to abort rendering
	virtual bool render(U32 renderType, GameObject* object) = 0;


	void save();

	string getFilename();;

protected:
	void load();
	string filename;
};