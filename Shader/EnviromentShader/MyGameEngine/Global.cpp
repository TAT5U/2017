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

Global::Global()
: STANDARD_CONTENT_WIDTH(WINDOW_WIDTH / 2.0f), STANDARD_CONTENT_HEIGHT(WINDOW_HEIGHT / 2.0f),
	ALPHA_MAX(255), ALPHA_MIN(0)
{
	fadeFlg = false;
	endFlg = false;
}

//シーン切り替え
void Global::ReplaceScene(Scene *pNextScene)
{
	delete pScene;
	pScene = pNextScene;
	pScene->Init();
}

void Global::SetAlphaFlg(bool flg)
{
	fadeFlg = flg;
}

bool Global::GetAlphaFlg()
{
	return fadeFlg;
}

void Global::SetEndFlg(bool flg)
{
	endFlg = flg;
}

bool Global::GetEndFlg()
{
	return endFlg;
}