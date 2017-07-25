/*GameOverScene.h*/

#pragma once
#include "cocos2d.h"
USING_NS_CC;
class GameOverScene : public Layer
{
public:
	GameOverScene();
	~GameOverScene();
	virtual bool init();
	void update(float dt) override;
	void input();

	//�X�v���C�g �w�i�E�Q�[���I�[�o�[
	Sprite *bk, *gameOver;

	//�E�B���h�E�T�C�Y
	Size DisplaySize;

	//�}�E�X�C�x���g
	EventListenerTouchOneByOne *listener;

	//�V�[���ڍs
	TransitionFade *trans;

	static Scene* createScene();
	CREATE_FUNC(GameOverScene);
};