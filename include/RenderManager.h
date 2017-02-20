#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "ShaderManager.h"
#include "vmath.h"
#include <vector>
using namespace std;

namespace sceneRenderer
{
	static GLuint LoadTexture2D(std::vector<unsigned char>& data,unsigned int width,unsigned int height)
	{
		GLubyte* pixels = &data[0];
		GLuint textureId;
		glGenTextures(1,&textureId);
		glBindTexture(GL_TEXTURE_2D,textureId);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,pixels);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
		return textureId;
	}

	static GLuint LoadTexture2D(unsigned char* pixels,unsigned int width,unsigned int height)
	{
		GLuint textureId;
		glGenTextures(1,&textureId);
		glBindTexture(GL_TEXTURE_2D,textureId);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,pixels);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

		return textureId;
	}

	static GLuint LoadTexture2DRGB(unsigned char* pixels,unsigned int width,unsigned int height)
	{
		GLuint textureId;
		glGenTextures(1,&textureId);
		glBindTexture(GL_TEXTURE_2D,textureId);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,pixels);

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

		return textureId;
	}

	static GLuint LoadTexture2DYUV(unsigned char* pixels,unsigned int width,unsigned int height)
	{
		GLuint textureId;
		glGenTextures(1,&textureId);
		glBindTexture(GL_TEXTURE_2D,textureId);
		glTexImage2D(GL_TEXTURE_2D,0,GL_LUMINANCE,width,height*3/2,0,GL_LUMINANCE,GL_UNSIGNED_BYTE,pixels);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

		return textureId;
	}

	static GLuint LoadTexture2DY(unsigned char* pixels,unsigned int width,unsigned int height)
	{
		GLuint textureId;
		glGenTextures(1,&textureId);
		glBindTexture(GL_TEXTURE_2D,textureId);
		glTexImage2D(GL_TEXTURE_2D,0,GL_LUMINANCE,width,height,0,GL_LUMINANCE,GL_UNSIGNED_BYTE,pixels);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

		return textureId;
	}

	static GLuint LoadTexture2DUV(unsigned char* pixels,unsigned int width,unsigned int height)
	{
		GLuint textureId;
		glGenTextures(1,&textureId);
		glBindTexture(GL_TEXTURE_2D,textureId);
		glTexImage2D(GL_TEXTURE_2D,0,GL_LUMINANCE_ALPHA,width/2,height/2,0,GL_LUMINANCE_ALPHA,GL_UNSIGNED_BYTE,pixels+width*height);

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

		return textureId;
	}

	static void ChangeTexture2D(GLuint textureId, std::vector<unsigned char>& data,unsigned int width,unsigned int height)
	{
		GLubyte* pixels = &data[0];
		glBindTexture(GL_TEXTURE_2D,textureId);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,pixels);
	}

	static void ChangeTexture2D(GLuint textureId, GLubyte* pixels,unsigned int width,unsigned int height)
	{
		glBindTexture(GL_TEXTURE_2D,textureId);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,pixels);
	}

	static void ChangeTexture2DRGB(GLuint textureId, GLubyte* pixels,unsigned int width,unsigned int height)
	{
		glBindTexture(GL_TEXTURE_2D,textureId);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,pixels);
	}

	static void ChangeTexture2DYUV(GLuint textureId, GLubyte* pixels,unsigned int width,unsigned int height)
	{
		glBindTexture(GL_TEXTURE_2D,textureId);
		glTexImage2D(GL_TEXTURE_2D,0,GL_LUMINANCE,width,height*3/2,0,GL_LUMINANCE,GL_UNSIGNED_BYTE,pixels);
	}

	static void ChangeTexture2DY(GLuint textureId, GLubyte* pixels,unsigned int width,unsigned int height)
	{
		glBindTexture(GL_TEXTURE_2D,textureId);
		glTexImage2D(GL_TEXTURE_2D,0,GL_LUMINANCE,width,height,0,GL_LUMINANCE,GL_UNSIGNED_BYTE,pixels);
	}

	static void ChangeTexture2DUV(GLuint textureId, GLubyte* pixels,unsigned int width,unsigned int height)
	{
		glBindTexture(GL_TEXTURE_2D,textureId);
		glTexImage2D(GL_TEXTURE_2D,0,GL_LUMINANCE_ALPHA,width/2,height/2,0,GL_LUMINANCE_ALPHA,GL_UNSIGNED_BYTE,pixels+width*height);
	}

	static void ChangeTexture2DRGB(GLuint textureId, std::vector<unsigned char>& data,unsigned int width,unsigned int height)
	{
		GLubyte* pixels = &data[0];
		glBindTexture(GL_TEXTURE_2D,textureId);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,pixels);
	}
}




#endif
