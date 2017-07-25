/*TitleScene*/

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

	//�X�v���C�g �w�i�E�^�C�g��
	Sprite *bk,*title;

	//���x�� �X�R�A
	Label *scorelbl;

	//�E�B���h�E�T�C�Y
	Size DisplaySize;

	//�}�E�X�C�x���g
	EventListenerTouchOneByOne *listener;

	//�V�[���ڍs
	TransitionFade *trans;

	static Scene* createScene();
	CREATE_FUNC(TitleScene);
};