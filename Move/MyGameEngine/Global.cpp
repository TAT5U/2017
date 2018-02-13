#include "Global.h"
#include "Scene.h"


void Global::ReplaceScene(Scene* pNextScene)
{
	SAFE_DELETE(pScene);
	pScene = pNextScene;
	pScene->Init();

}