/*TitleScene.h*/

#pragma once
#include "cocos2d.h"

USING_NS_CC;
class TitleScene : public Layer
{
public:
	TitleScene();
	~TitleScene();
	virtual bool init();
	void update(float dt) override;
	void input();

	//�N���b�N������
	void ClickStart(Ref *pSender);

	//�^�C�g�����x��
	Label *title,*start;

	//Sprite�ϐ� �o�b�N�O���E���h�E���x�����n�E�J�[�\���Eselect
	Sprite *backGround,*labelFD,*cursor,*select, *select2;

	//start���x���ƃJ�[�\���̏Փ�
	Rect startRect,cursorRect;

	//select�̕\���t���O
	bool selectflg;

	//�^�C�g�����{�^����
	MenuItemLabel *startButton;
	Menu *startMenu;

	//�}�E�X�C�x���g
	EventListenerMouse *mouseListner;

	//�}�E�X�J�[�\���C�x���g
	EventMouse *mouse;

	//�E�B���h�E�T�C�Y
	Size DisplaySize;

	//�V�[���ڍs�p
	TransitionFade *transition;

	static Scene* createScene();
	CREATE_FUNC(TitleScene);
};