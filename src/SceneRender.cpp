#include "SceneRender.h"
#include <cmath>
#include "RenderUtility.h"


using namespace sceneRenderer;

SceneRender::SceneRender()
{
	hasInit = false;
	hasBackground = false;
	backgroundTranspos = 0;
	backgroundFlip = 0;
	backgroundImageType = 0;
}

SceneRender::~SceneRender()
{
}

void SceneRender::InitWithAutoEnv(int x, int y, int w, int h, std::string path)
{
	stringstream s;
	if(hasInit)
	{
		s<<__FILE__<<" "<<__LINE__<<" has Init"<<endl;
		LogUtility::LogError(s.str());
		s.str("");
		return;
	}
	s<<"InitWithAutoEnv";
	//LogUtility::Log(s.str());

	glViewport(x,y,w,h);
	glEnable(GL_DEPTH_TEST);
	glClearColor(1,1,1,1);
	hasInit = true;
}

void SceneRender::InitBackground(int type,int transpose,int flip,int iamgeType)
{
	GLfloat vertexsArray[] ={
		-1.0f, -1.0f,  0.0f, 
		1.0f, -1.0f,  0.0f, 
		-1.0f,  1.0f,  0.0f, 
		1.0f, 1.0f,  0.0f
	} ;
	GLuint vertexElements[]= {
		0,1,2,
		1,3,2
	};

	GLfloat texCoordArray[] ={
		0.0f, 0.0f,0.0f,   
		1.0f, 0.0f,0.0f,  
		0.0f,  1.0f,   0.0f,
		1.0f, 1.0f,  0.0f
	} ;

	GLuint &rprogram = backgroundStruct.program;
	map<string,GLuint>& relementBufferMap = backgroundStruct.elementBufferMap;
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "" },
		{ GL_FRAGMENT_SHADER, "" },
		{ GL_NONE, NULL }
	};

	if(type == 0 || type == 1)
	{
		rprogram = LoadShaders(shaders,vertBackground,fragBackground);
		backgroundTranspos = transpose;
		backgroundFlip = flip;
	}else if(type ==2)
	{
		rprogram = LoadShaders(shaders,vertBackgroundYUV,fragBackgroundYUV);
		backgroundTranspos = transpose;
		backgroundFlip = flip;
	}else if(type == 3)
	{
		rprogram = LoadShaders(shaders,vertBackground,fragBackground);
		backgroundTranspos = transpose;
		backgroundFlip = flip;
		backgroundImageType = type;
	}

	GLuint texCoordBuffers;
	glGenBuffers(1, &texCoordBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffers);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoordArray),texCoordArray, GL_STATIC_DRAW);
	backgroundStruct.texCoordBuffers =texCoordBuffers;

	GLuint texCoordIndex=glGetAttribLocation(rprogram,"texCoord");
	glVertexAttribPointer(texCoordIndex, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(texCoordIndex);
	backgroundStruct.texCoordIndex = texCoordIndex;

	GLuint vertexBuffers;
	glGenBuffers(1, &vertexBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexsArray),vertexsArray, GL_STATIC_DRAW);
	backgroundStruct.vertexBuffers = vertexBuffers;
	GLuint vertexIndex=glGetAttribLocation(rprogram,"position");
	glVertexAttribPointer(vertexIndex, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vertexIndex);
	backgroundStruct.vertexIndex = vertexIndex;

	GLuint elementBuffers;
	glGenBuffers(1,&elementBuffers);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,elementBuffers);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(vertexElements),vertexElements,GL_STATIC_DRAW);
	backgroundStruct.elementBuffers = elementBuffers;
	backgroundStruct.elementArraySize = sizeof(vertexElements)/sizeof(unsigned int);
}

void SceneRender::DrawBackground()
{
	if(!hasBackground)
	{
		return;
	}

	GLuint &rprogram = backgroundStruct.program;
	glDisable(GL_DEPTH_TEST);
	glUseProgram(rprogram);

	glUniform1i(glGetUniformLocation(rprogram,"transpose"),backgroundTranspos);
	glUniform1i(glGetUniformLocation(rprogram,"flip"),backgroundFlip);
	glUniform1i(glGetUniformLocation(rprogram,"backgroundImageType"),backgroundImageType);

	glBindBuffer(GL_ARRAY_BUFFER, backgroundStruct.texCoordBuffers);
	glVertexAttribPointer(backgroundStruct.texCoordIndex, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(backgroundStruct.texCoordIndex);

	glBindBuffer(GL_ARRAY_BUFFER, backgroundStruct.vertexBuffers);
	glVertexAttribPointer(backgroundStruct.vertexIndex, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(backgroundStruct.vertexIndex);

	glUniform1i(glGetUniformLocation(rprogram,"tex"),0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,backgroundStruct.textureID);

	glUniform1i(glGetUniformLocation(rprogram,"texUV"),1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D,backgroundStruct.textureUVID);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,backgroundStruct.elementBuffers);
	glDrawElements(GL_TRIANGLES,backgroundStruct.elementArraySize,GL_UNSIGNED_INT,NULL);

	glDisableVertexAttribArray(backgroundStruct.vertexIndex);
	glDisableVertexAttribArray(backgroundStruct.texCoordIndex);
}

void SceneRender::SetViewPort(int x, int y, int w, int h)
{
	glViewport(x,y,w,h);
}


void SceneRender::UpdateADP()
{
	glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT );
	DrawBackground();
	glFlush();
}

void SceneRender::SetBackGroundData(unsigned char* data,int dataType, int w, int h,int transpose,int flip)
{
	if(!hasBackground)
	{
		InitBackground(dataType,transpose,flip,dataType);
		hasBackground = true;

		GLuint textureID;
		if(dataType ==0) //rgba
		{
			textureID = LoadTexture2D(data,w,h);
		}else if(dataType ==1) //rgb
		{
			textureID = LoadTexture2DRGB(data,w,h);
		}else if(dataType ==2)//yuv
		{
			textureID = LoadTexture2DY(data,w,h);

			backgroundStruct.textureUVID = LoadTexture2DUV(data,w,h);

		}else if(dataType ==3)//BGRA
		{
			//textureID = LoadTexture2DBGRA(data,w,h);
		}
		backgroundStruct.textureID = textureID;
	}else
	{
		if(dataType ==0) //rgba
		{
			ChangeTexture2D(backgroundStruct.textureID,data,w,h);
		}else if(dataType ==1) //rgb
		{
			ChangeTexture2DRGB(backgroundStruct.textureID,data,w,h);
		}else if(dataType ==2)//yuv
		{
			ChangeTexture2DY(backgroundStruct.textureID,data,w,h);
			ChangeTexture2DUV(backgroundStruct.textureUVID,data,w,h);

		}else if(dataType ==3)//BGRA
		{
			//ChangeTexture2DBGRA(backgroundStruct.textureID,data,w,h);
		}
	}
}


void SceneRender::SetBackGroundData2(void* vdata,int dataType, int w, int h,int transpose,int flip)
{
	unsigned char* data = (unsigned char*)vdata;
	if(!hasBackground)
	{
		InitBackground(dataType,transpose,flip,dataType);

		hasBackground = true;

		GLuint textureID;
		if(dataType ==0) //rgba
		{
			textureID = LoadTexture2D(data,w,h);
		}else if(dataType ==1) //rgb
		{
			textureID = LoadTexture2DRGB(data,w,h);
		}else if(dataType ==2)//yuv
		{
			textureID = LoadTexture2DY(data,w,h);

			backgroundStruct.textureUVID = LoadTexture2DUV(data,w,h);

		}else if(dataType ==3)//BGRA
		{
			textureID = LoadTexture2D(data,w,h);
		}
		backgroundStruct.textureID = textureID;
	}else
	{
		if(dataType ==0) //rgba
		{
			ChangeTexture2D(backgroundStruct.textureID,data,w,h);
		}else if(dataType ==1) //rgb
		{
			ChangeTexture2DRGB(backgroundStruct.textureID,data,w,h);
		}else if(dataType ==2)//yuv
		{
			ChangeTexture2DY(backgroundStruct.textureID,data,w,h);
			ChangeTexture2DUV(backgroundStruct.textureUVID,data,w,h);

		}else if(dataType ==3)//BGRA
		{
			ChangeTexture2D(backgroundStruct.textureID,data,w,h);
		}
	}


}





