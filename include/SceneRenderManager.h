#ifndef SCENE_RENDER_SDK_H
#define SCENE_RENDER_SDK_H

#ifndef WIN32
#define EXPORT_COMPILE __attribute__((visibility("default"))) 
#else
#define EXPORT_COMPILE 
#endif


#include <string>

namespace sceneRenderer
{
	class SceneRender;

class SceneRenderManager
{
public:
	SceneRender *glassManager;
	EXPORT_COMPILE SceneRenderManager();
	EXPORT_COMPILE ~SceneRenderManager();

	//////////////////////////////////////////////////////////////////////////
	EXPORT_COMPILE void InitWithAutoEnv(int x, int y, int w, int h,std::string path);
	EXPORT_COMPILE void SetViewPort(int x, int y, int w, int h);
	EXPORT_COMPILE void UpdateAutoEnv();
	EXPORT_COMPILE void SetBackGroundData(unsigned char* data,int dataType, int w, int h,int transpose,int flip);
	EXPORT_COMPILE void SetBackGroundData2(void* data,int dataType, int w, int h,int transpose,int flip);
	EXPORT_COMPILE void DeleteManager();
	EXPORT_COMPILE void SetOpenglESVersion(int value);

	
};


}




#endif
