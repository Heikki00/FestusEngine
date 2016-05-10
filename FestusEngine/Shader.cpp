#pragma once
#include "Shader.h"
#include "FileManager.h"
#include "ResourceManager.h"
#include "ShaderStage.h"
#include "boost/algorithm/string.hpp"
#include "boost/regex.hpp"
#include "Material.h"
#include "RenderingEngine.h"
#include "Texture.h"
#include "UniformStruct.h"


Shader::Shader(const string& filename) : filename(filename)
{

	
	string src = fileManager->getContents(filename);
	bool hasVert = false, hasFrag = false;
	U32 off = 0, iteration = 0;
	while (src.find_first_of('\n', off) != -1) {
		U32 loc = src.find_first_of('\n', off);
		iteration++;
		//If first line, skip the .shaders file
		if (iteration < 3) {
			off = loc + 1;
			continue;
		}



		//Relative path from .glsl file and type prefix
		string str = src.substr(off, loc - off);
		
		//type prefix
		string typeString = str.substr(0, 2);
		
		//Prefix to enum
		GLenum type = typeString == "vs" ? GL_VERTEX_SHADER : typeString == "fs" ? GL_FRAGMENT_SHADER :
			typeString == "gs" ? GL_GEOMETRY_SHADER : typeString == "tc" ? GL_TESS_CONTROL_SHADER :
			typeString == "ts" ? GL_TESS_EVALUATION_SHADER : GL_FALSE;

		//Path to shader
		string shaderFilename = str.substr(2);

		ShaderStage* s = resourceManager->getShaderStage(shaderFilename);
		shaders.push_back(s == nullptr ? resourceManager->loadShaderStage(shaderFilename, type, LoadFlag::UNTIL_LAST_FREED) : s);

		//Once true, always true
		hasVert = hasVert ? true : type == GL_VERTEX_SHADER;
		hasFrag = hasFrag ? true : type == GL_FRAGMENT_SHADER;
		off = loc + 1;
	}

	//Does this shaderProgram have vertex and fragment shaders?
	if (!hasVert || !hasFrag) {
		Debug::log(ErrorType::SHADER_ERROR, "ShaderProgram %s does not have vertex or/and fragment shader!\n", filename.c_str());
		return;
	}
	

	ID = glCreateProgram();

	for (ShaderStage* s : shaders) {
		glAttachShader(ID, s->getID());
	}

	glLinkProgram(ID);


	//Error checking
	I32 params = -1;
	bool failed = false;

	glGetProgramiv(ID, GL_LINK_STATUS, &params);
	failed = params != GL_TRUE;

	glValidateProgram(ID);
	glGetProgramiv(ID, GL_VALIDATE_STATUS, &params);
	failed = params != GL_TRUE;

	if (failed) {
		I32 max_length = 2048;
		I32 actual_length = 0;
		char log[2048];
		glGetProgramInfoLog(ID, max_length, &actual_length, log);
		Debug::log(ErrorType::SHADER_ERROR, "Failed to link or validate program %s\n", filename.c_str());
	}


	



	


	//Uniforms:

	
	
	int amtUniforms;

	glGetProgramiv(ID, GL_ACTIVE_UNIFORMS, &amtUniforms);

	//Iterate through them
	for (unsigned int i = 0; i < amtUniforms; ++i) {

		//If uniform is a block, skip it
		int blockIndex = -1;
		glGetActiveUniformsiv(ID, 1, &i, GL_UNIFORM_BLOCK_INDEX, &blockIndex);
		if (blockIndex != -1) continue;


		//Get uniform parameters
		char cname[100];
		GLsizei len;
		GLint size;
		GLenum type;
		glGetActiveUniform(ID, i, 1024, &len, &size, &type, cname);

		std::string name(cname), structType;
			

		//If uniforms name has a '.', a.k.a. if it is a struct.
		if (name.find_first_of('.') != name.npos) {
			//Get the name of the uniform 
			string baseName = name.substr(0, name.find_first_of('.'));
			Uniform member;
			member.location = glGetUniformLocation(ID, name.c_str());
			member.name = name;
			member.type = type;
			
			structMembers.push_back(member);

			//Check if the uniform struct(as a whole) has already been added.
			//Has to be doe the wierd way, because contiue doesn't work inside another loop
			bool foundSame = false;
			for (Uniform& u : uniforms) {
				
				if (u.name == baseName) {
					foundSame = true;
					break;
				}
			}
			if(foundSame) continue;


			Uniform u;
			u.type = GL_NONE;
			u.name = baseName;
			u.location = 0;
			uniforms.push_back(u);
		}
		//If uniform is not struct, just add it
		else {
			Uniform u;
			u.name = name;
			u.type = type;
			u.location = glGetUniformLocation(ID, name.c_str());
			//std::cout << "|" << glGetUniformLocation(ID, name.c_str()) << "|" << std::endl;
			uniforms.push_back(u);

		}


		std::sort(structMembers.begin(), structMembers.end());
		std::sort(uniforms.begin(), uniforms.end());
	}
	
	
	for (Uniform& u : uniforms) {
		
		if (strncmp(u.name.c_str(), "R_", 2) == 0) {
			u.uniformType = RENDERINGENGINE;
		}
		
		else if (strncmp(u.name.c_str(), "M_", 2) == 0) {
			u.uniformType = MATERIAL;
			
		}

		else if (strncmp(u.name.c_str(), "RL_", 3) == 0) {
			u.uniformType = RENDERLAYER;
			
		}

		else if (u.name == "MVP") {
			u.uniformType = MVP;
		}
		
		else if (u.name == "MV") {
			u.uniformType = MV;
		}

		else if (u.name == "model") {
			u.uniformType = MODEL;
		}

		else if (u.name == "perspective") {
			u.uniformType = PERSPECTIVE;
		}

		else if (u.name == "eyepos") {
			u.uniformType = EYEPOS;
		}
	}



}

Shader::~Shader()
{
	

	for (ShaderStage* s : shaders) {
		resourceManager->freeShaderStage(s);
	}

	glDeleteProgram(ID);
}
 
void Shader::bind()
{

	if (glIsProgram(ID)) {

		glUseProgram(ID);
		
	}
	else {
		Debug::log(ErrorType::SHADER_ERROR, "Tried to use invalid shader program &s\n", filename.c_str());
	}
}



void Shader::updateUniforms(Material* m, Transform& t)
{

	for (auto& u : uniforms) {

		MappedValues* map = nullptr;
		U32 prefixLenght = 0;
		if (u.uniformType == MATERIAL) {
			map = m;
			prefixLenght = 2;
		}

		else if (u.uniformType == RENDERINGENGINE){
			map = renderingEngine;
			prefixLenght = 2;
		}

		else if (u.uniformType == RENDERLAYER) {
			map = renderingEngine->getCurrentLayer();
			prefixLenght = 3;
		}

		if (map) {
			switch (u.type)
			{

			case GL_FLOAT: {
				glUniform1f(u.location, map->getFloat(u.name.substr(prefixLenght)));
				break;
			}

			case GL_INT: {
				glUniform1i(u.location, map->getI32(u.name.substr(prefixLenght)));
				break;
			}

						 //TODO: Check if uint works
			case GL_UNSIGNED_INT: {
				glUniform1ui(u.location, map->getU32(u.name.substr(prefixLenght)));
				break;
			}

			case GL_FLOAT_VEC2: {
				glUniform2fv(u.location, 1, map->getVector2(u.name.substr(prefixLenght)).toArray());
				break;
			}

			case GL_FLOAT_VEC3: {
				Vector3 v = map->getVector3(u.name.substr(prefixLenght));
				glUniform3fv(u.location, 1, v.toArray());
				break;
			}

			case GL_FLOAT_VEC4: {
				glUniform4fv(u.location, 1, map->getVector4(u.name.substr(prefixLenght)).toArray());
				break;
			}

			case GL_FLOAT_MAT2: {
				glUniformMatrix2fv(u.location, 1, GL_TRUE, map->getMatrix2(u.name.substr(prefixLenght)).toArray());
				break;
			}

			case GL_FLOAT_MAT3: {
				glUniformMatrix3fv(u.location, 1, GL_TRUE, map->getMatrix3(u.name.substr(prefixLenght)).toArray());
				break;
			}

			case GL_FLOAT_MAT4: {
				glUniformMatrix4fv(u.location, 1, GL_TRUE, map->getMatrix4(u.name.substr(prefixLenght)).toArray());
				break;
			}
			
			case GL_NONE: {
				UniformStruct* struc = map->getUniformStruct(u.name.substr(prefixLenght));

				if (struc) {
					struc->setUniform(u.name, this);
				}
				else {
					Debug::log(ErrorType::SHADER_ERROR, "ERROR: Uniform struct %s not found!\n", u.name.c_str());
				}
				break;
			
			}



			default: {

				if (u.type == GL_SAMPLER_2D || u.type == GL_SAMPLER_2D_ARRAY || u.type == GL_SAMPLER_1D || u.type == GL_SAMPLER_1D_ARRAY ||
					u.type == GL_SAMPLER_3D || u.type == GL_SAMPLER_CUBE || u.type == GL_SAMPLER_CUBE_MAP_ARRAY) {

					U32 slot = renderingEngine->getSamplerslot(u.name.substr(prefixLenght));

					auto t = map->getTexture(u.name.substr(prefixLenght));

					if (!t) {
						Debug::log(ErrorType::SHADER_ERROR, "ERROR: Did not find texture: %s\n", u.name.substr(prefixLenght).c_str());
						return;
					}
					t->bind(slot);

					//std::cout << "Bound texture " << t->getName() << " to slot " << slot << " and set uniform " << u.name << " at " << u.location << " to " << slot << std::endl;

					glUniform1i(u.location, slot);

				}


					

				


			}

			}
			continue;
		}


		if (u.uniformType == MVP) {
			glUniformMatrix4fv(u.location,  1, GL_TRUE, (renderingEngine->getCamera()->getVP() * t.getTransform()).toArray());
		}

		else if (u.uniformType == MV) {
			glUniformMatrix4fv(u.location, 1, GL_TRUE, (renderingEngine->getCamera()->getV() * t.getTransform()).toArray());
		}

		else if (u.uniformType == MODEL) {
			glUniformMatrix4fv(u.location, 1, GL_TRUE, (t.getTransform()).toArray());
		}

		else if (u.uniformType == PERSPECTIVE) {
			glUniformMatrix4fv(u.location, 1, GL_TRUE, renderingEngine->getCamera()->getP().toArray());
		}

		else if (u.uniformType == EYEPOS) {
			glUniform3fv(u.location, 1, renderingEngine->getCamera()->getTransform().getWorldPosition().toArray());
		}

	
		


	}

}
