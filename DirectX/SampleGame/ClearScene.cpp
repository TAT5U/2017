/*ClearScene.cpp*/

/*2017-07-04
	��� �B��
		�N���A�V�[���̃v���O����*/

/****�C���N���[�h****/
#include "ClearScene.h"
/********************/


//�R���X�g���N�^
ClearScene::ClearScene()
{

}

//�f�X�g���N�^
ClearScene::~ClearScene()
{

}

//����������
void ClearScene::Init()
{
	//�摜�̕\��
	{
		Sprite *sprite = Sprite::Create("Assets//jag.png");
		sprite->SetAnchorPoint(0, 0);
		sprite->SetPosition(100, 100);
		this->AddChild(sprite);
	}

}

//�X�V����
void ClearScene::Update()
{

}

//���͏���
void ClearScene::Input()
{

}