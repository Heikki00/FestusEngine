#include "ResourceManager.h"
#include "ShaderStage.h"
#include "Shader.h"
#include "FileManager.h"
#include "Mesh.h"
#include "Texture.h"

//TODO: Move file name to some sort of configuration file maybe?
ResourceManager::ResourceManager(): shadersFile("Resources/Shaders/Shaders.shaders")
{
	shaderSources = fileManager->getContents(shadersFile);
	

}

ResourceManager::~ResourceManager()
{
	for(auto a : shaders){
		delete a.second.val;
	}

	for (auto a : shaderStages) {
		delete a.second.val;
	}

	for (auto a : meshes) {
		delete a.second.val;
	}

	for (auto a : textures) {
		delete a.second.val;
	}

}

ShaderStage* ResourceManager::loadShaderStage(const string& filename, GLenum type, LoadFlag flag)
{
	Resource<ShaderStage> r;
	r.lifetime = flag;
	r.ref = 1;
	r.val = new ShaderStage(filename, type);
	shaderStages[filename] = r;
	return r.val;
}

ShaderStage* ResourceManager::getShaderStage(const string& filename)
{
	auto i = shaderStages.find(filename);
	if (i != shaderStages.end()) {
		i->second.ref += 1;
		return i->second.val;
	}
	else return nullptr;
}

void ResourceManager::freeShaderStage(ShaderStage* s)
{

	
	auto i = shaderStages.find(s->getFilename());
	
	if (i == shaderStages.end()) {
		Debug::log(ErrorType::RESOURCE_ERROR, "ERROR: Tried to free ShaderStage that was not stored in ResourceManager: %s\n", s->getFilename());
		return;
	}
	
	i->second.ref -= 1;
	
	if (i->second.ref == 0 && i->second.lifetime == LoadFlag::UNTIL_LAST_FREED) {
		delete i->second.val;
		shaderStages.erase(i);
	}

}

void ResourceManager::deleteShaderStage(ShaderStage* s)
{
	shaderStages.erase(s->getFilename());
	delete s;
}



U32 ResourceManager::getNumReferences(Shader* s)
{
	auto i = shaders.find(s->getFilename());
	return i == shaders.end() ? 0 : i->second.ref;
}

U32 ResourceManager::getNumReferences(ShaderStage* s)
{
	auto i = shaderStages.find(s->getFilename());
	return i == shaderStages.end() ? 0 : i->second.ref;
}

U32 ResourceManager::getNumReferences(Mesh* m)
{
	
	auto i = meshes.find(m->getFilename());
	return i == meshes.end() ? 0 : i->second.ref;

}

U32 ResourceManager::getNumReferences(Texture* t)
{
	auto i = textures.find(t->getName());
	return i == textures.end() ? 0 : i->second.ref;

}

Texture* ResourceManager::loadTexture(const string& filename, LoadFlag flag)
{
	Resource<Texture> r;

	r.lifetime = flag;
	r.ref = 1;
	r.val = new Texture(filename);

	textures[filename] = r;

	return r.val;
}

Texture* ResourceManager::loadTexture(Texture* t, LoadFlag flag)
{
	Resource<Texture> r;

	r.lifetime = flag;
	r.ref = 1;
	r.val = t;

	textures[t->getName()] = r;

	return r.val;
}

Texture* ResourceManager::fetchTexture(const string& str, LoadFlag flag /*= LoadFlag::UNTIL_LAST_FREED*/)
{

		auto i = textures.find(str);
		if (i != textures.end()) {
			i->second.ref += 1;
			return i->second.val;
		}
		else return loadTexture(str, flag);

}

Texture* ResourceManager::fetchTextureLoad(const string& saveData, LoadFlag flag /*= LoadFlag::UNTIL_LAST_FREED*/)
{
	string line;

	std::istringstream ss(saveData);
	std::getline(ss, line, ' ');
	std::getline(ss, line, ' ');
	string filename = line;

	auto i = textures.find(filename);
	if (i != textures.end()) {
		i->second.ref += 1;
		return i->second.val;
	}
	else return loadTexture(Texture::loadTexture(saveData), flag);
}

Texture* ResourceManager::getTexture(const string& name)
{
	auto i = textures.find(name);
	if (i != textures.end()) {
		i->second.val += 1;
		return i->second.val;
	}
	else return nullptr;
}

void ResourceManager::freeTexture(Texture* t)
{
	auto i = textures.find(t->getName());

	if (i == textures.end()) {
		Debug::log(ErrorType::RESOURCE_ERROR, "ERROR: Tried to free Texture that was not stored in ResourceManager: %s\n", t->getName().c_str());
		return;
	}

	i->second.ref -= 1;

	if (i->second.ref == 0 && i->second.lifetime == LoadFlag::UNTIL_LAST_FREED) {
		delete i->second.val;
		textures.erase(i);
	}
}

void ResourceManager::deleteTexture(Texture* t)
{
	textures.erase(t->getName());
	delete t;
}

Mesh* ResourceManager::loadMesh(const string& filename, VertexType type, LoadFlag flag)
{
	Resource<Mesh> r;

	r.lifetime = flag;
	r.ref = 1;
	r.val = new Mesh(filename, type);

	meshes[filename] = r;

	return r.val;
}

Mesh* ResourceManager::getMesh(const string& filename)
{
	auto i = meshes.find(filename);
	if (i != meshes.end()) {
		i->second.val += 1;
		return i->second.val;
	}
	else return nullptr;
}

Mesh* ResourceManager::fetchMesh(const string& filename, VertexType type, LoadFlag flag)
{
	auto i = meshes.find(filename);
	if (i != meshes.end()) {
		i->second.ref += 1;
		return i->second.val;
	}
	else return loadMesh(filename, type, flag);

}

void ResourceManager::freeMesh(Mesh* m)
{
	auto i = meshes.find(m->getFilename());

	if (i == meshes.end()) {
		Debug::log(ErrorType::RESOURCE_ERROR, "ERROR: Tried to free Mesh that was not stored in ResourceManager: %s\n", m->getFilename());
		return;
	}

	i->second.ref -= 1;

	if (i->second.ref == 0 && i->second.lifetime == LoadFlag::UNTIL_LAST_FREED) {
		delete i->second.val;
		meshes.erase(i);
	}
	
}

void ResourceManager::deleteMesh(Mesh* m)
{
	meshes.erase(m->getFilename());
	delete m;
}

Shader* ResourceManager::loadShader(const string& filename, LoadFlag flag)
{
	Resource<Shader> r;
	r.lifetime = flag;
	r.ref = 1;
	r.val = new Shader(filename);
	shaders[filename] = r;
	return r.val;
}

Shader* ResourceManager::getShader(const string& filename)
{
	auto i = shaders.find(filename);
	if (i != shaders.end()) {
		i->second.val += 1;
		return i->second.val;
	}
	else return nullptr;
}

Shader* ResourceManager::fetchShader(const string& filename, LoadFlag flag)
{
	auto i = shaders.find(filename);
	if (i != shaders.end()) {
		i->second.ref += 1;
		return i->second.val;
	}
	else return loadShader(filename, flag);
}

void ResourceManager::freeShader(Shader* s)
{
	auto i = shaders.find(s->getFilename());

	if (i == shaders.end()) {
		Debug::log(ErrorType::RESOURCE_ERROR, "ERROR: Tried to free Mesh that was not stored in ResourceManager: %s\n", s->getFilename());
		return;
	}

	i->second.ref -= 1;

	if (i->second.ref == 0 && i->second.lifetime == LoadFlag::UNTIL_LAST_FREED) {
		delete i->second.val;
		shaders.erase(i);
	}
}

void ResourceManager::deleteShader(Shader* s)
{
	shaderStages.erase(s->getFilename());
	delete s;
}

string ResourceManager::getShaderSource(const string& filename) const
{

	U32 markPos = shaderSources.find_first_of('$');


	string::const_iterator start = shaderSources.begin(), end = shaderSources.end();

	boost::regex expres(filename + " (\\d+) (\\d+)");
	
	boost::match_results<string::const_iterator> what;
	if (boost::regex_search(start, end, what, expres)) {

		U32 startInd = std::stoi(what[1]) + markPos;
		U32 endInd = std::stoi(what[2]) + markPos;


		return shaderSources.substr(startInd, endInd - startInd);




	}


	Debug::log(ErrorType::SHADER_ERROR, "ERROR: Requested shader source not found: %s\n", filename.c_str());

	return "";

}

