/*PlayScene.h*/

#pragma once
#include "cocos2d.h"
USING_NS_CC;
class PlayScene : public Layer
{
public:
	PlayScene();
	~PlayScene();
	virtual bool init();
	void update(float dt) override;
	void input();

	//�������x
	void FallObj();

	//�I�u�W�F�N�g�ݒ�
	void SetObj();

	//���x���A�b�v��
	void LvUpObj();

	//Sprite�ϐ� �I�u�W�F�N�g�E�J�[�\���E�o�b�N�O���E���h
	Sprite **obj,*cursor,*backGround;

	//�ʒu
	Vec2 *pos,*objpos;

	//�v�f���E�J�E���g�̕ϐ�
	int n,i,*flg,score,cnt,*workflg,*spFlg;

	//�I�u�W�F�N�g�̏Փ˔͈�
	Rect *objRect, cursorRect;

	//�X�R�A�E�^�C�����x��
	Label *scoreText,*startTimeText;

	//�t���O
	bool speedFlg,*spobjFlg,timeFlg,textTimeFlg;

	//�J�n����
	float startTime,startTextTime;

	//�}�E�X�C�x���g
	EventListenerMouse *mouseListner;

	//�}�E�X�J�[�\���C�x���g
	EventMouse *mouse;

	//�A�j���[�V�����E�V�[�P���X
	Sprite *anime;
	Animation *anim;
	Animate *animate;
	RemoveSelf *remove;
	Sequence *action;

	//�E�B���h�E�T�C�Y
	Size DisplaySize;

	static Scene* createScene();
	CREATE_FUNC(PlayScene);
};