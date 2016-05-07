#pragma once


//Basically a wrapper for framebuffer object. Is used to render stuff to textures, that can be attached with functions
class FrameBuffer {
public:
	FrameBuffer();

	~FrameBuffer();

	//Attaches texture t to attachment point
	void attachTexture(Texture* t, GLenum attachment);

	//Attaches each layer of texture t to attachment point
	void attachTextureLayers(Texture* t, GLenum* attachments);

	//Creates and attaches renderbuffer to the framebuffer
	void attachRenderbuffer(GLenum attachment, GLenum format, U32 width, U32 height);

private:
	GLuint ID;
	std::vector<Texture*> textures;
	std::vector<GLuint> renderbuffers;
};