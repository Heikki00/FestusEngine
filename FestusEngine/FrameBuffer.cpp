#include "FrameBuffer.h"
#include "Texture.h"

FrameBuffer::FrameBuffer()
{

	glGenFramebuffers(1, &ID);
	glBindFramebuffer(GL_FRAMEBUFFER, ID);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		//Debug::log(ErrorType::OPENGL_ERROR, "ERROR: Problem creating framebuffer: %i\n", glCheckFramebufferStatus(GL_FRAMEBUFFER));
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	width = height = 0;
	
}

FrameBuffer::~FrameBuffer()
{
	if(renderbuffers.size()) glDeleteRenderbuffers(renderbuffers.size(), &renderbuffers[0]);
	glDeleteFramebuffers(1, &ID);
}

void FrameBuffer::attachTexture(Texture* t, GLenum attachment)
{
	width = t->getWidth();
	height = t->getHeight();
	glBindFramebuffer(GL_FRAMEBUFFER, ID);

	glFramebufferTexture(GL_FRAMEBUFFER, attachment, t->getID(), 0);


	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		Debug::log(ErrorType::OPENGL_ERROR, "ERROR: Error attaching texture to framebuffer\n");
	}

	
	if (attachment >= GL_COLOR_ATTACHMENT0 && attachment <= GL_COLOR_ATTACHMENT15) colorBuffers.push_back(attachment);

	
	glDrawBuffers(colorBuffers.size(), &colorBuffers[0]);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::attachTextureLayers(Texture* t, GLenum* attachments)
{
	width = t->getWidth();
	height = t->getHeight();

	glBindFramebuffer(GL_FRAMEBUFFER, ID);
	
	for (U32 i = 0; i < t->getDepth(); ++i) {
	
		glFramebufferTextureLayer(GL_FRAMEBUFFER, attachments[i], t->getID(), 0, i);
		
		if (attachments[i] >= GL_COLOR_ATTACHMENT0 && attachments[i] <= GL_COLOR_ATTACHMENT15) colorBuffers.push_back(attachments[i]);
	}
	
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		Debug::log(ErrorType::OPENGL_ERROR, "ERROR: Error attaching texture layers to framebuffer\n");
	}

	glDrawBuffers(colorBuffers.size(), &colorBuffers[0]);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::attachRenderbuffer(GLenum attachment, GLenum format, U32 width, U32 height)
{
	
	this->width = width;
	this->height = height;

	GLuint rb = 0;

	//Generate renderbuffer, bind it and allocate storage for it
	glGenRenderbuffers(1, &rb);
	glBindRenderbuffer(GL_RENDERBUFFER, rb);
	glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);

	//Attach the renderbuffer to the framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, ID);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, rb);

	
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		Debug::log(ErrorType::OPENGL_ERROR, "ERROR: Error attaching renderbuffer to framebuffer\n");
	}
	
	if (attachment >= GL_COLOR_ATTACHMENT0 && attachment <= GL_COLOR_ATTACHMENT15) colorBuffers.push_back(attachment);
	
	glDrawBuffers(colorBuffers.size(), &colorBuffers[0]);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	

	//Add renderbuffer to the list of them(so it can be deleted in the destructor)
	renderbuffers.push_back(rb);
}

void FrameBuffer::bindAsRenderTarget()
{
	glBindFramebuffer(GL_FRAMEBUFFER, ID);
	glViewport(0, 0, width, height);
}
