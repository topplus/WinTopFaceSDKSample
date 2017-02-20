#include "SceneRender.h"
#include "SceneRenderManager.h"

using namespace sceneRenderer;

SceneRenderManager::SceneRenderManager()
{
	glassManager = new SceneRender;
}

SceneRenderManager::~SceneRenderManager()
{
	delete glassManager;
	glassManager = NULL;
}

void SceneRenderManager::InitWithAutoEnv(int x, int y, int w, int h,std::string path)
{
	glassManager->InitWithAutoEnv(x, y, w, h,"");
}

void SceneRenderManager::SetViewPort(int x, int y, int w, int h)
{
	glassManager->SetViewPort(x, y, w, h);
}

void SceneRenderManager::UpdateAutoEnv()
{
	glassManager->UpdateADP();
}

void SceneRenderManager::SetBackGroundData(unsigned char* data,int dataType, int w, int h,int transpose,int flip)
{
	glassManager->SetBackGroundData(data,dataType, w, h,transpose,flip);
}

//es2.0 200;  es3.0 300
void SceneRenderManager::SetOpenglESVersion(int value)
{
	glassManager->SetOpenglESVersion(value);
}

void SceneRenderManager::SetBackGroundData2(void* data,int dataType, int w, int h,int transpose,int flip)
{
	glassManager->SetBackGroundData2(data,dataType, w, h,transpose,flip);
}

void  SceneRenderManager::DeleteManager()
{
	if (glassManager)
	{
		delete glassManager;
		glassManager = NULL;
	}
}