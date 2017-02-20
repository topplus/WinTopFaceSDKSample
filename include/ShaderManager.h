#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H



#if WIN32
#include <GL/glew.h>
#include <gl/freeglut.h>

#elif IOS
//#import <OpenGLES/ES2/gl.h>
//#import <OpenGLES/ES2/glext.h>
#import <OpenGLES/ES3/gl.h>
#import <OpenGLES/ES3/glext.h>
#elif ANDROID_RENDER_OPENGLES2
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#elif ANDROID_RENDER_OPENGLES3
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#endif

#include <iostream>
#include "RenderUtility.h"
#define BUFFER_OFFSET(offset) ((void*)(offset))
#define     STRINGIFY(A)    #A
using namespace std;

namespace sceneRenderer
{

typedef struct 
{
	GLenum       type;
	const char*  filename;
	GLuint       shader;
} ShaderInfo;

static inline GLuint LoadShaders( ShaderInfo* shaders,char* vertShaderSource,char* fragShaderSource )
{
	if ( shaders == NULL ) { return 0; }

	GLuint program = glCreateProgram();

	const GLchar* vertSource = vertShaderSource;
	const	GLchar* fragSource = fragShaderSource;

	GLuint vertShader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vertShader, 1, &vertSource, NULL );
	glCompileShader( vertShader );
	GLint compiled;
	glGetShaderiv( vertShader, GL_COMPILE_STATUS, &compiled );
	if ( !compiled ) {
		GLsizei len;
		glGetShaderiv( vertShader, GL_INFO_LOG_LENGTH, &len );
		GLchar* log = new GLchar[len+1];
		glGetShaderInfoLog( vertShader, len, &len, log );
		//std::cerr << "\n\n Shader compilation failed: " << log << std::endl<<std::endl;

		stringstream ss;
		ss<<"Shader compilation failed: " << log << std::endl<<std::endl;
		LogUtility::Log(ss.str());

		delete [] log;
		return 0;
	}
	glAttachShader( program, vertShader );

	GLuint fragShader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fragShader, 1, &fragSource, NULL );
	glCompileShader( fragShader );
	//GLint compiled;
	glGetShaderiv( fragShader, GL_COMPILE_STATUS, &compiled );
	if ( !compiled ) {
		GLsizei len;
		glGetShaderiv( fragShader, GL_INFO_LOG_LENGTH, &len );
		GLchar* log = new GLchar[len+1];
		glGetShaderInfoLog( fragShader, len, &len, log );
		std::cerr << "\n\n Shader compilation failed: " << log << std::endl<<std::endl;
		delete [] log;
		return 0;
	}
	glAttachShader( program, fragShader );


	glLinkProgram( program );

	GLint linked;
	glGetProgramiv( program, GL_LINK_STATUS, &linked );
	if ( !linked ) {
		//#ifdef _DEBUG
		GLsizei len;
		glGetProgramiv( program, GL_INFO_LOG_LENGTH, &len );

		GLchar* log = new GLchar[len+1];
		glGetProgramInfoLog( program, len, &len, log );
		std::cerr << "\n\nShader linking failed: " << log << std::endl<<std::endl;
		delete [] log;
		//#endif /* DEBUG */

		//for ( entry = shaders; entry->type != GL_NONE; ++entry ) {
		//	glDeleteShader( entry->shader );
		//	entry->shader = 0;
		//}

		return 0;
	}

	return program;
}



//////////////////////////////////////////////////////////////////////////

static char  vertBackground[] = STRINGIFY
(
	varying vec3 texCoord0;
	attribute vec3 position;
	attribute vec3 texCoord;
	void main()
	{
		texCoord0 = texCoord;
		gl_Position = vec4(position.xyz,1.0);
	}
);


static char  fragBackground[] = STRINGIFY
	(
	precision highp float;
	varying vec3 texCoord0;
	uniform sampler2D tex;
	uniform int flip;
	uniform int transpose;
	uniform int backgroundImageType;
	void main()
	{
		vec2 st = vec2(texCoord0.s,1.0-texCoord0.t);

		if(transpose==1){
			st=vec2(st.t,st.s);
		}
		if(flip==1){
			st=vec2(st.x,1.0-st.y);
		}else if (flip==2)
		{
			st=vec2(1.0-st.x,st.y);
		}else if(flip==3)
		{
			st=vec2(1.0-st.x,1.0-st.y);
		}

		vec4 color = texture2D(tex,st);

		if(backgroundImageType == 3)
		{
			color.rgb = color.bgr;
		}

		color.a = 1.0;
		gl_FragColor=color;

	}
);


//////////////////////////////////////////////////////////////////////////

static char  vertBackgroundYUV[] = STRINGIFY
(
	varying vec3 texCoord0;
	attribute vec3 position;
	attribute vec3 texCoord;
	void main()
	{
		texCoord0 = texCoord;
		gl_Position = vec4(position.xyz,1.0);
	}
);


static char  fragBackgroundYUV[] = STRINGIFY
	(
	precision highp float;
	varying vec3 texCoord0;
	uniform sampler2D tex;
	uniform sampler2D texUV;
	uniform int flip;
	uniform int transpose;
	const mat3 yuv2rgb=mat3
	(1.164,0,1.596,
	1.164,-0.391,-0.813,
	1.164,2.018,0);
	void main()
	{
		vec2 st = vec2(texCoord0.s,1.0-texCoord0.t);
		if(transpose==1){
			st=vec2(st.t,st.s);
		}
		if(flip==1){
			st=vec2(st.x,1.0-st.y);
		}else if (flip==2)
		{
			st=vec2(1.0-st.x,st.y);
		}else if(flip==3)
		{
			st=vec2(1.0-st.x,1.0-st.y);
		}

		vec3 yuv=vec3(texture2D(tex,st).r-0.0625,
			texture2D(texUV,st).a-0.5,
			texture2D(texUV,st).r-0.5);
		vec3 rgb=yuv*yuv2rgb;
		gl_FragColor = vec4(rgb,1.0);
	}
);
}



#endif
