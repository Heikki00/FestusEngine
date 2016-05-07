#pragma once



//Class that represents a SINGLE texture. Manages the loading, binding, samplers and all that shit. Currently uses FreeImage to load files. 
//TODO: cube maps, 3D textures
class Texture
{
public:

	//Loads a single texture from file. TextureTarget is the type of texture, format is the format the file is in, internalFormat is the format the texture will be stored,
	//type is the type of data that will be stored(esim.GL_FLOAT), filter is the type of filtering for min and mag(if filter is a mipmap filer, mipmaps will be generated), wrap is the way over 1 texture coordinates
	//will be handled. Value of GL_NONE in format or type means it will be detected form file. TODO: Only 2D textures currently supported with this constructor
	Texture(const std::string& filename, GLenum textureTarget = GL_TEXTURE_2D, GLenum format = GL_NONE, GLenum internalFormat = GL_RGBA8, GLenum type = GL_NONE, GLenum filter = GL_LINEAR_MIPMAP_LINEAR, GLenum wrap = GL_REPEAT);
	

	//The barebones constructor. Name is the name the texture will be referred as, data is an array of pointers that point to different arrays of data. All except cubemap supported.
	Texture(const string& name, void** data, U32 width, U32 height, U32 depth, GLenum textureTarget, GLenum format, GLenum internalFormat, GLenum type, GLenum filter,  GLenum wrap, GLenum* attacments);


	~Texture();

	//Tells OpenGL to use this texture. textureUnit must be between 1 and 32, otherwise writes to error file
	void bind(GLuint textureUnit);


	//Sets a sampler parameter
	void setParameter(GLenum name, I32 par);
	
	//Sets a sampler parameter
	void setParameter(GLenum name, F32 par);
	
	
	//Returns the OpenGL name for this texture
	GLuint getID();

	//Returns the name of this texture
	string getName() const { return name; }

	U32 getWidth() const;
	U32 getHeight() const;
	U32 getDepth() const;

protected:
	friend class FileManager;

	static Texture* loadTexture(const string& saveData);

	string save();

private:

	string name;



	bool isSaveable;

	GLuint ID;
	GLuint frameBuffer;
	GLuint renderBuffer;

	
	GLuint sampler;

	GLenum textureTarget;

	GLenum format;
	GLenum internalformat;
	GLenum type;

	U32 width, height, depth;

	//Fills format and type if they are GL_NONE. Non-GL_NONE values are ignored and not changed
	void fillParameters(void* bm, GLenum& format, GLenum& type);


	static const U32 MAX_TEXTURE_UNIT = 60;
};

