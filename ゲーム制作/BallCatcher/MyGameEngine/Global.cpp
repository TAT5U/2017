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
{
	fadeFlg = false;
}

//�V�[���؂�ւ�
void Global::ReplaceScene(Scene *pNextScene)
{
	delete pScene;
	pScene = pNextScene;
	pScene->Init();
}

void Global::SetFadeFlg(bool flg)
{
	fadeFlg = flg;
}

bool Global::GetFadeFlg()
{
	return fadeFlg;
}