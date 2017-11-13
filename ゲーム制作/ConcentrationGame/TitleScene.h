/*TitleScene.h*/

//�C���N���[�h�K�[�h
#pragma once

/**********�C���N���[�h**********/
#include "MyGameEngine\Scene.h"
#include "MyGameEngine\Game.h"

#include "BackGround.h"
#include "PlayScene.h"
/********************************/


class TitleScene : public Scene
{
	//�w�i
	BackGround *backGround;

	//�^�C�g��
	Sprite *title;

	//�t�F�[�h�t���O
	bool fadeFlg;

public:

	TitleScene();
	~TitleScene();

	void Init() override;
	void Update() override;
	void Input() override;
};