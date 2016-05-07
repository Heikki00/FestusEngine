#pragma once
#include "Mesh.h"

class ShaderStage;
class Shader;
class Mesh;
class MeshLoader;
class Texture;

//Flag that controls when the resource will be deleted
enum LoadFlag {
	FOREVER,
	UNTIL_LAST_FREED
};


//Class that represents some resource T. Also has flag that represents lifetime and a reference counter
template<class T>
struct Resource {
	T* val;
	LoadFlag lifetime;
	U32 ref;
};

//Class that controls all the resources in the engine. It can be used to retrieve a pointer, and that pointer must be returned to ResourceManager.
//The class contains 6 different types of functions:
//load*(), which loads the resource from file and returns a pointer to it
//get*(), whitch returns a pointer to previously loaded resource, or nullptr if the resource has no been loaded
//fetch*(), whitch returns a pointer to the resource if it has been loaded. If the resource has not been loaded, the function will load it.
//free*(), whitch returns a pointer to the manager. The resource might not be deleted.
//delete*(), whitch deletes the resource. USE ONLY WHEN YOU REALLY KNOW WHAT YOU'RE DOING, because other references to the recource might still exist
//getNumReferences(), whitch returns the number of references(times it has been retrieved from the manager and not returned with free*()) to the object.
class ResourceManager {

public:

	ResourceManager();
	
	~ResourceManager();
	

	Shader* loadShader(const string& filename, LoadFlag flag = LoadFlag::UNTIL_LAST_FREED);
	
	Shader* getShader(const string& filename);

	Shader* fetchShader(const string& filename, LoadFlag flag = LoadFlag::UNTIL_LAST_FREED);

	void freeShader(Shader* s);

	void deleteShader(Shader* s);

	U32 getNumReferences(Shader* s);

	
	
	
	Mesh* loadMesh(const string& filename, VertexType type, LoadFlag flag = LoadFlag::UNTIL_LAST_FREED);

	Mesh* getMesh(const string& filename);

	Mesh* fetchMesh(const string& filename, VertexType type, LoadFlag flag = LoadFlag::UNTIL_LAST_FREED);


	void freeMesh(Mesh* m);

	void deleteMesh(Mesh* m);

	U32 getNumReferences(Mesh* s);




	Texture* loadTexture(const string& filename, LoadFlag flag = LoadFlag::UNTIL_LAST_FREED);

	Texture* loadTexture(Texture* t, LoadFlag flag = LoadFlag::UNTIL_LAST_FREED);

	Texture* fetchTexture(const string& filename, LoadFlag flag = LoadFlag::UNTIL_LAST_FREED);

	Texture* getTexture(const string& name);

	void freeTexture(Texture* t);
	
	void deleteTexture(Texture* t);

	U32 getNumReferences(Texture* t);


 


protected:

	friend class Shader;
	friend class ShaderStage;

	//Returns the contents of .shaders file
	string getShaderSources() const { return shaderSources; }

	//Returns the source of a singe shader file(relative to -shaders file), for example: VS.vs
	string getShaderSource(const string& filename) const;


	ShaderStage* loadShaderStage(const string& filename, GLenum type, LoadFlag flag = LoadFlag::UNTIL_LAST_FREED);

	ShaderStage* getShaderStage(const string& filename);

	void freeShaderStage(ShaderStage* s);

	void deleteShaderStage(ShaderStage* s);

	U32 getNumReferences(ShaderStage* s);




private:

	std::map<string, Resource<ShaderStage>> shaderStages;

	std::map<string, Resource<Shader>> shaders;

	std::map<string, Resource<Mesh>> meshes;

	std::map<string, Resource<Texture>> textures;

	std::string shaderSources;

	const std::string shadersFile;

};