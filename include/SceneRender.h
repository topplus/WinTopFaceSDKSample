#ifndef SCENE_RENDER_H
#define SCENE_RENDER_H

#include "ShaderManager.h"
#include "vmath.h"
#include "time.h"
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include "RenderManager.h"

using namespace std;
namespace sceneRenderer
{
class ObjGLStruct
{
public:

	bool hasInit;
	string objName;
	GLuint program;
	map<string,GLuint> elementBufferMap;
	map<string,GLuint> textureIDs;
	//map<int,GLuint> cubemapIDMap;
	GLuint textureID;
	GLuint textureUVID;
	//GLuint textureCubeID;
	GLuint normIndex;
	GLuint normalBuffers;
	GLuint texCoordBuffers;
	GLuint texCoordIndex;
	GLuint vertexBuffers;
	GLuint elementBuffers;
	GLuint vertexIndex;
	GLuint elementArraySize;

	ObjGLStruct()
	{
		Clean();
	};

	void Clean()
	{
		hasInit = false;
		objName ="";
		program = 0;
		elementBufferMap.clear();
		textureIDs.clear();
		textureID = 0;
		//textureCubeID = 0;
		normIndex = 0;
		normalBuffers = 0;
		texCoordBuffers = 0;
		texCoordIndex = 0;
		vertexBuffers = 0;
		vertexIndex = 0;
		//cubemapIDMap.clear();
	}
};


class SceneRender
{
public:

	ObjGLStruct backgroundStruct;
	bool hasInit;
	bool hasBackground;
	int backgroundTranspos;
	int backgroundFlip;
	int backgroundImageType;
	int openglesVersion;
	SceneRender();
	~SceneRender();

	void InitBackground(int type,int transpose,int flip,int iamgeType);
	void DrawBackground();
	void SetViewPort(int x, int y, int w, int h);
	void UpdateADP();
	void SetBackGroundData(unsigned char* data,int dataType, int w, int h,int transpose,int flip);
	void SetBackGroundData2(void* data,int dataType, int w, int h,int transpose,int flip);
	void SetOpenglESVersion(int value){openglesVersion = value;};
	void InitWithAutoEnv(int x, int y, int w, int h, std::string path);
};

}




#endif
