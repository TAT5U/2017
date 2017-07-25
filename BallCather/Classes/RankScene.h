/*RankScene.h*/

#pragma once
#include "cocos2d.h"
USING_NS_CC;
class RankScene : public Layer
{
public:
	RankScene();
	~RankScene();
	virtual bool init();
	void update(float dt) override;
	void input();

	//�N���b�N������
	void ClickBack(Ref *pSender);

	//�}�C�X�R�A�E�����N�E�o�b�N���x��
	Label *myScore, *rank, *rankScore,*back;

	//Sprite�ϐ� �o�b�N�O���E���h�E���x�����n�E�J�[�\���Eselect
	Sprite *backGround, *labelFD, *cursor, *select, *select2;

	//back���x���ƃJ�[�\���̏Փ�
	Rect backRect, cursorRect;

	//select�̕\���t���O
	bool selectflg;

	//�o�b�N���{�^����
	MenuItemLabel *backButton;
	Menu *backMenu;

	//�v�f���E�J�E���g
	int n,i;

	//�X�R�A�i�[�p
	std::string str,str2,s,maxScore;

	//�}�E�X�C�x���g
	EventListenerMouse *mouseListner;

	//�}�E�X�J�[�\���C�x���g
	EventMouse *mouse;

	//�E�B���h�E�T�C�Y
	Size DisplaySize;

	//�V�[���ڍs�p
	TransitionFade *transition;

	static Scene* createScene();
	CREATE_FUNC(RankScene);
};