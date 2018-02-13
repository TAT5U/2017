/*Global.cpp*/

/*2017-06-07
	���B��
		�����̃t�@�C������
			�Q�Ƃ�����̂��L�q����Global�v���O����*/

/****�C���N���[�h****/
#include "Global.h"
/********************/


//�w�b�_�ŃC���N���[�h����ƃG���[�ɂȂ�̂�
//Global.cpp�Ŏg���ꍇ�͂����Ńw�b�_���C���N���[�h����
#include "Scene.h"

Global::Global()
: STANDARD_CONTENT_WIDTH(WINDOW_WIDTH / 2.0f), STANDARD_CONTENT_HEIGHT(WINDOW_HEIGHT / 2.0f),
	ALPHA_MAX(255), ALPHA_MIN(0)
{
	fadeFlg = false;
	endFlg = false;
}

//�V�[���؂�ւ�
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