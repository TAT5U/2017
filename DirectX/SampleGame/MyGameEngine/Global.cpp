/*Global.cpp*/

/*2017-06-07
	狩野達哉
		複数のファイルから
			参照するものを記述するGlobalプログラム*/

/****インクルード****/
#include "Global.h"
/********************/


//ヘッダでインクルードするとエラーになるので
//Global.cppで使う場合はここでヘッダをインクルードする
#include "Scene.h"


//シーン切り替え
void Global::ReplaceScene(Scene *pNextScene)
{
	delete pScene;
	pScene = pNextScene;
	pScene->Init();
}