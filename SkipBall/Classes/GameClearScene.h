/*GameClearScene.h*/

#pragma once
#include "cocos2d.h"
USING_NS_CC;
class GameClearScene : public Layer
{
public:
	GameClearScene();
	~GameClearScene();
	virtual bool init();
	void update(float dt) override;
	void input();

	//�X�v���C�g �w�i�E�Q�[���N���A
	Sprite *bk, *gameClear;

	//���x�� �X�R�A�A�E�V�L�^
	Label *scorelbl,*newRecordlbl;

	//�E�B���h�E�T�C�Y
	Size DisplaySize;

	//�}�E�X�C�x���g
	EventListenerTouchOneByOne *listener;

	//�V�[���ڍs
	TransitionFade *trans;

	static Scene* createScene();
	CREATE_FUNC(GameClearScene);
};