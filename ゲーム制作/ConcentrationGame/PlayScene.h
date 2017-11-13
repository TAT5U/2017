/*PlayScene.h*/

//�C���N���[�h�K�[�h
#pragma once

/**********�C���N���[�h**********/
#include "MyGameEngine\Scene.h"
#include "MyGameEngine\Game.h"
#include "Player.h"
#include "BackGround.h"
#include "Trump.h"
#include "Judge.h"
/********************************/


class PlayScene : public Scene
{
	//�w�i
	BackGround *backGround;

	//�g�����v(�\�Ɨ�)
	Trump **trump[2];

	//�v���C���[
	Player **player;

	//����
	Judge *judge;

	//�I���E���g���C
	Sprite *end, *retry;

	//�^�[�����x��
	Label *turnLabel;

	//�^�[���\���p�e�L�X�g
	TCHAR turnText[32];

	//���[�v�p�J�E���g�E�Q�[���J�E���g
	int count, gameCount;

	//�^�[��
	int turn;

	//�N���b�N�����Ƃ���̗v�f�i�[�p�ϐ�
	int clickNumber[2], clickCount;

	//�N���b�N����Ă��邩�ǂ���
	bool handleOpenFlg;

	//�Q�[�������ǂ���
	bool gamePlayFlg;

	//�t�F�[�h�t���O
	bool fadeFlg;

public:

	PlayScene();
	~PlayScene();

	void Init() override;
	void Update() override;
	void Input() override;

	//���g���C��Exit�������ꂽ�Ƃ�
	void RetryORExit();

	//Judge�Ăяo��
	bool CallJudgement();

	//�Ֆʂ̊Ď�
	void BoardMonitor();

	//�^�[���ύX
	void ChangeTurn();

	//�g�����v�̃N���b�N��
	void OnClick();



};