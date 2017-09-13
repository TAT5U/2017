/*PlayScene.cpp*/

/*2017-06-16
	��� �B��
		�v���C�V�[���̃v���O����*/

/****�C���N���[�h****/
#include "PlayScene.h"
/********************/


//�R���X�g���N�^
PlayScene::PlayScene()
{
	//�ϐ��̏�����
	_sprite = nullptr;
	_label = nullptr;
	_spriteFlg = false;
}

//�f�X�g���N�^
PlayScene::~PlayScene()
{

}

//����������
void PlayScene::Init()
{
	//�摜�̕\��
	{
		auto sprite = Sprite::Create("Assets//aa.png");
		sprite->SetScale(0.5, 0.5);
		sprite->SetPosition(-300, 300);
		AddChild(sprite);
		_sprite = sprite;
	}

	/*
	//�摜�̕\��
	{
	Sprite *sprite = Sprite::Create("Assets//jag.png");
	this->AddChild(sprite);
	}

	//�摜�̕\��(�͈́E�A���J�[�|�C���g�E�ʒu�w��)
	{
	Sprite *sprite2 = Sprite::Create("Assets//jag.png", MyRect(100, 100, 200, 200));
	sprite2->SetAnchorPoint(0, 0);
	sprite2->SetPosition(100, 100);
	this->AddChild(sprite2);
	}
	*/

	//���x���̕\��
	{
		auto label = Label::Create("�Ă��Ƃ�����", "MS �S�V�b�N", 20);
		label->SetPosition(600, 300);
		label->SetString("����΂�́I�I");
		AddChild(label);
		_label = label;
	}
}

//�X�V����
void PlayScene::Update()
{
	if (_spriteFlg == false)
	{
		//�X�v���C�g�̈ʒu���擾���ĉE�ɂ��炵�ăZ�b�g���A
		//�X�v���C�g�������Ă���悤�Ɍ�����
		D3DXVECTOR3 spritePos = _sprite->GetPosition();
		spritePos += D3DXVECTOR3(2, 0, 0);
		_sprite->SetPosition(spritePos.x, spritePos.y);

		/**********************�����蔻��**********************/
		MyRect rectSprite = _sprite->GetBoundingBox();
		MyRect rectLabel = _label->GetBoundingBox();

		//�m�[�h�ƃm�[�h
		if (rectSprite.IntersectsRect(rectLabel))
		{
			//���������Ƃ�
			_label->SetString("�Փ�!!");
		}

		//�m�[�h�Ɠ_
		if (rectSprite.ContainsPoint(_label->GetPosition()))
		{
			//���������Ƃ�
			_label->SetString("�_�ŏՓ�!!");
		}
		/******************************************************/


		//�����ꂽ�L�[�̔���
		if (g.pInput->IsKeyPush(DIK_A))
		{
			_sprite->RemoveFromParent();
			_spriteFlg = true;
			//g.ReplaceScene(new ClearScene);
		}

		////�����ꂽ"��"�̃L�[�̔���
		//if (g.pInput->IsKeyTap(DIK_A))
		//{
		//	g.ReplaceScene(new ClearScene);
		//}

		////���������̃L�[�̔���
		//if (g.pInput->IsKeyRelease(DIK_A))
		//{
		//	g.ReplaceScene(new ClearScene);
		//}

		//�}�E�X�������ꂽ���̔���
		if (g.pInput->IsMousePush(0))
		{
			_label->SetString("���N���b�N!!!!");
		}

		//�R���g���[����A�������ꂽ�Ƃ��̔���
		if (g.pInput->IsControllerInputState(XINPUT_GAMEPAD_A))
		{
			//�o�C�u���[�V������ON�Ȃ��0�ɂ���
			//OFF�Ȃ�΍ő��65535�ɂ���
			if (g.pInput->GetVibrationSpeed() != 0)
			{
				g.pInput->SetVibrationSpeed(0);
			}
			else
			{
				g.pInput->SetVibrationSpeed(65535);
			}
		}
	}



}

//���͏���
void PlayScene::Input()
{

}