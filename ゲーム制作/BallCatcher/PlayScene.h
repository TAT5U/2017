/*PlayScene.h*/

#pragma once
#include "MyGameEngine\Scene.h"
#include "MyGameEngine\Game.h"
#include "MyGameEngine\Camera.h"
#include "GameOverScene.h"

class PlayScene : public Scene
{
	//Sprite�ϐ� �I�u�W�F�N�g�E�J�[�\���E�o�b�N�O���E���h
	Sprite **obj, *cursor, *backGround;

	//�ʒu
	Point *pos, *objpos;

	//�v�f���E�J�E���g�̕ϐ�
	int n, i, *flg, score, cnt, *workflg, *spFlg, prevDigit;

	//�I�u�W�F�N�g�̏Փ˔͈�
	MyRect *objRect, cursorRect;

	//�X�R�A�E�^�C�����x��
	Label *scoreText, *startTimeText;

	//�t���O
	bool speedFlg, *spobjFlg, timeFlg;

	//�J�n����
	float startTime;

	TCHAR text[128];
	TCHAR timeText[128];
	bool fadeFlg;

public:
	PlayScene();
	~PlayScene();

	void Init() override;
	void Update() override;
	void Input() override;

	//�������x
	void FallObj();

	//�I�u�W�F�N�g�ݒ�
	void SetObj();

	//���x���A�b�v��
	void LvUpObj();
};