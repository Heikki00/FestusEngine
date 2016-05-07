#include "Texture.h"




Texture::Texture(const std::string& filename, GLenum textureTarget /*= GL_TEXTURE_2D*/, GLenum format /*= GL_NONE*/, GLenum internalFormat /*= GL_RGBA8*/, GLenum type/*= GL_NONE*/, GLenum filter /*= GL_LINEAR_MIPMAP_LINEAR*/, GLenum wrap /*= GL_REPEAT*/)
{

	
	this->name = filename;
	this->textureTarget = textureTarget;
	this->isSaveable = true;
	this->ID = 0;
	this->format = format;
	this->type = type;
	this->internalformat = internalformat;


	//Image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

	//Pointer to the image, once loaded
	FIBITMAP *dib = nullptr;


	//Pointer to the image data
	BYTE* bits = nullptr;

	

	//Check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename.c_str(), 0);
	//If still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename.c_str());

	//If still unknown, send an error message
	if (fif == FIF_UNKNOWN) {
		Debug::log(ErrorType::FILE_ERROR, "ERROR: Could not determine the type of the texture file %s\n", filename.c_str());
		return;
	}

	

	dib = FreeImage_Load(fif, filename.c_str());

	//If the image failed to load, send an error message
	if (!dib) {
		Debug::log(ErrorType::FILE_ERROR, "ERROR: Could not read the texture file %s\n", filename.c_str());
		return;
	}

	

	fillParameters(dib, format, type);

	//Retrieve the image data
	bits = FreeImage_GetBits(dib);

	//Get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	depth = 1;

	


	//Generate sampler and set its parameters
	glGenSamplers(1, &sampler);
	
	
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, filter);

	if (filter == GL_NEAREST) glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	else glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, wrap);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, wrap);


	if (textureTarget != GL_TEXTURE_2D) {
		//TODO: I guess I have to write a plugin for FreeImage...

		Debug::log(ErrorType::TEXTURE_ERROR, "ERROR: Only 2D texture loading is supported(currently), tried to load texture %s\n", filename.c_str());
		return;
	}


	
	//Does this texture use mipmapping
	bool usesMipmaps = filter == GL_LINEAR_MIPMAP_LINEAR ||
		filter == GL_NEAREST_MIPMAP_LINEAR ||
		filter == GL_LINEAR_MIPMAP_NEAREST ||
		filter == GL_NEAREST_MIPMAP_NEAREST;


	//Generate the texture
	glGenTextures(1, &ID);

	glBindTexture(textureTarget, ID);

	//If uses mipmaps, calculate the amount of them needed. Otherwise, just use one layer
	if(usesMipmaps) glTexStorage2D(textureTarget, (U32)floor(log2(Math::max((F32)width, (F32)height))), internalFormat, width, height);
	else glTexStorage2D(textureTarget, 1, internalFormat, width, height);

	//Actually set the data
	glTexSubImage2D(textureTarget, 0, 0, 0, width, height, format, type, bits);
	
	

	//If uses mipmaps, generate them, and set up anisotropic filtering
	if (usesMipmaps) {
		glGenerateMipmap(textureTarget);

		GLfloat maxAntisotropy;

		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAntisotropy);


		glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAntisotropy);

	}







	//Free FreeImage's copy of the data
	FreeImage_Unload(dib);




}






Texture::Texture(const string& name, void** data, U32 width, U32 height, U32 depth, GLenum textureTarget, GLenum format, GLenum internalFormat, GLenum type, GLenum filter, GLenum wrap, GLenum* attacments)
{
	this->name = name;
	this->width = width;
	this->height = height;
	this->depth = depth;
	this->textureTarget = textureTarget;
	this->isSaveable = false;
	this->format = format;
	this->type = type;
	
	//Generate sampler and set its parameters
	glGenSamplers(1, &sampler);


	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, filter);

	if (filter == GL_NEAREST) glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	else glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, wrap);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, wrap);

	//Does this texture use mipmapping
	bool usesMipmaps = filter == GL_LINEAR_MIPMAP_LINEAR ||
		filter == GL_NEAREST_MIPMAP_LINEAR ||
		filter == GL_LINEAR_MIPMAP_NEAREST ||
		filter == GL_NEAREST_MIPMAP_NEAREST;


	//Generate the texture
	glGenTextures(1, &ID);

	glBindTexture(textureTarget, ID);


	switch (textureTarget)
	{


	case GL_TEXTURE_1D: {
		if (usesMipmaps) glTexStorage1D(textureTarget, (U32)floor(log2(width)), internalFormat, width);
		else glTexStorage1D(textureTarget, 1, internalFormat, width);


		if (data == nullptr) break;

		glTexSubImage1D(textureTarget, 0, 0, width, format, type, data[0]);




		break;
	}


	case GL_TEXTURE_1D_ARRAY: {
		if (usesMipmaps) glTexStorage2D(textureTarget, (U32)floor(log2(width)), internalFormat, width, height);
		else glTexStorage2D(textureTarget, 1, internalFormat, width, height);


		if (data == nullptr) break;

		glTexSubImage2D(textureTarget, 0, 0, 0, width, 1, format, type, data[0]);

		for (U32 i = 1; i < height; i++) {
			glTexSubImage2D(textureTarget, 0, 0, i, width, 1, format, type, data[i]);

		}

		break;
	}


	case GL_TEXTURE_2D: {
		if (usesMipmaps) glTexStorage2D(textureTarget, (U32)floor(log2(Math::max(width, height))), internalFormat, width, height);
		else glTexStorage2D(textureTarget, 1, internalFormat, width, height);


		if (data == nullptr) break;

		glTexSubImage2D(textureTarget, 0, 0, 0, width, height, format, type, data[0]);



		break;
	}

	case GL_TEXTURE_2D_ARRAY: {
		if (usesMipmaps) glTexStorage3D(textureTarget, (U32)floor(log2(Math::max(width, height))), internalFormat, width, height, depth);
		else glTexStorage3D(textureTarget, 1, internalFormat, width, height, depth);


		if (data == nullptr) break;

		glTexSubImage3D(textureTarget, 0, 0, 0, 0, width, height, 1, format, type, data[0]);

		for (U32 i = 1; i < height; i++) {
			glTexSubImage3D(textureTarget, 0, 0, 0, i, width, height, 1, format, type, data[i]);

		}

		break;
	}


	case GL_TEXTURE_3D: {
		if (usesMipmaps) glTexStorage3D(textureTarget, (U32)floor(log2(Math::max(width, Math::max(height, depth)))), internalFormat, width, height, depth);
		else glTexStorage3D(textureTarget, 1, internalFormat, width, height, depth);


		if (data == nullptr) break;

		glTexSubImage3D(textureTarget, 0, 0, 0, 0, width, height, depth, format, type, data[0]);



		break;
	}

	default: {
		Debug::log(ErrorType::TEXTURE_ERROR, "ERROR: Texture %s had a unsupported texture type\n", name.c_str());
	
	}
	
	}







	//If uses mipmaps, generate them, and set up anisotropic filtering
	if (usesMipmaps) {
		glGenerateMipmap(textureTarget);

		GLfloat maxAntisotropy;

		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAntisotropy);


		glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAntisotropy);

	}



}

Texture* Texture::loadTexture(const string& saveData)
{
	

	if (saveData.empty()) {
		Debug::log(ErrorType::TEXTURE_ERROR, "ERROR: Tried to load texture with an empty save-string");
		return nullptr;
	 }

	string str = saveData;
	
	if (str.at(0) == '0') {
		str = str.substr(2);

		string filename = str.substr(0, str.find_first_of(' '));

		str = str.substr(str.find_first_of(' '));

		GLenum texTar = std::stoi(str.substr(str.find_first_of(' ')));

		str = str.substr(str.find_first_of(' '));

		GLenum format = std::stoi(str.substr(str.find_first_of(' ')));

		str = str.substr(str.find_first_of(' '));

		GLenum intFormat = std::stoi(str.substr(str.find_first_of(' ')));

		str = str.substr(str.find_first_of(' '));

		GLenum type = std::stoi(str.substr(str.find_first_of(' ')));

		str = str.substr(str.find_first_of(' '));

		GLenum filter = std::stoi(str.substr(str.find_first_of(' ')));

		str = str.substr(str.find_first_of(' '));

		GLenum wrap = std::stoi(str.substr(str.find_first_of(' ')));

		return new Texture(filename, texTar, format, intFormat, type, filter, wrap);
	}

	return nullptr;
}

string Texture::save()
{
	string res;

	if (!isSaveable) return "";


		res += "0 ";
	  
		res += name;

		res += " ";

		res += std::to_string((U32)textureTarget);
		
		res += " ";

		res += std::to_string((U32)format);
		
		res += " ";

		res += std::to_string((U32)internalformat);

		res += " ";

		res += std::to_string((U32)type);
	
		res += " ";

		GLint filter, wrap;
		glGetSamplerParameteriv(sampler, GL_TEXTURE_MAG_FILTER, &filter);

		glGetSamplerParameteriv(sampler, GL_TEXTURE_WRAP_S, &wrap);

		res += std::to_string((U32)filter);

		res += " ";

		res += std::to_string((U32)wrap);

		return res;
	

	


}

Texture::~Texture()
{
	glDeleteTextures(1, &ID);
	glDeleteSamplers(1, &sampler);
}

void Texture::bind(GLuint textureUnit)
{
	if (textureUnit < 0 || textureUnit > MAX_TEXTURE_UNIT) {
		Debug::log(ErrorType::RESOURCE_ERROR, "ERROR: Tried to bind texture %s to texture unit %i\n", name.c_str(), textureUnit);
		return;
	}

	glActiveTexture(GL_TEXTURE0 + textureUnit);

	glBindSampler(textureUnit, sampler);

	glBindTexture(textureTarget, ID);



}

void Texture::setParameter(GLenum name, I32 par)
{
	glSamplerParameteri(sampler, name, par);
}

void Texture::setParameter(GLenum name, F32 par)
{
	glSamplerParameterf(sampler, name, par);
}




GLuint Texture::getID()
{
	return ID;
}

U32 Texture::getWidth() const
{
	return width;
}

U32 Texture::getHeight() const
{
	return height;
}

U32 Texture::getDepth() const
{
	return depth;
}

void Texture::fillParameters(void* bm, GLenum& format, GLenum& type)
{
	FIBITMAP* bitm = static_cast<FIBITMAP*>(bm);
	//Fill the things that should be automatically filled
	if (format == GL_NONE) {
		U32 pixelDepth = FreeImage_GetBPP(bitm);

		if (pixelDepth == 8) format = GL_RED;
		if (pixelDepth == 24) format = GL_BGR;
		if (pixelDepth == 32) format = GL_BGRA;
		if (pixelDepth == 48) format = GL_BGR;
		if (pixelDepth == 64) format = GL_RGBA;
		
	}
	if (type == GL_NONE) {
		FREE_IMAGE_TYPE imgType = FreeImage_GetImageType(bitm);

		if (imgType == FIT_BITMAP) type = GL_UNSIGNED_BYTE;
		if (imgType == FIT_RGB16) { type = GL_UNSIGNED_SHORT; }
		if (imgType == FIT_RGBA16) { type = GL_UNSIGNED_SHORT; }
	}
}

