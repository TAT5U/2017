#pragma once
#include "cocos2d.h"
USING_NS_CC;
class PlayScene;
class GameOverScene : public Layer
{
public:
	GameOverScene();
	~GameOverScene();
	virtual bool init();
	void update(float dt) override;
	void input();

	//�N���b�N������(GameOver)
	void ClickGameOver(Ref *pSender);

	//�N���b�N������(Score)
	void ClickScore(Ref *pSender);

	//�Q�[���I�[�o�[�E�X�R�A���x��
	Label *gameOver,*score;

	Sprite *backGround, *labelFD,*labelFD2,*cursor, *select, *select2,*select3, *select4;

	Rect scoreRect,gameOverRect,cursorRect;

	bool selectflg,selectflg2;

	//�Q�[���I�[�o�[�E�X�R�A���{�^����
	MenuItemLabel *gameOverButton,*scoreButton;
	Menu *gameOverMenu,*scoreMenu;

	//�}�E�X�C�x���g
	EventListenerMouse *mouseListner;

	//�}�E�X�J�[�\���C�x���g
	EventMouse *mouse;

	//�E�B���h�E�T�C�Y
	Size DisplaySize;

	//�V�[���ڍs�p
	TransitionFade *transition;

	static Scene* createScene();
	CREATE_FUNC(GameOverScene);
};