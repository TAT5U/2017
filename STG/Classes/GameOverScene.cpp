//�C���N���[�h
#include "GameOverScene.h"
#include "TitleScene.h"

//���{��g�p��
#pragma execution_character_set("utf-8")

//������������������������������������������������������
//�R���X�g���N�^
//������������������������������������������������������
GameOverScene::GameOverScene()
{
	DisplaySizeWidth = CCDirector::sharedDirector()->getWinSize().width;
	DisplaySizeHeight = CCDirector::sharedDirector()->getWinSize().height;


}

//������������������������������������������������������
//�f�X�g���N�^
//������������������������������������������������������
GameOverScene::~GameOverScene()
{



}

//������������������������������������������������������
//�V�[���쐬
//�����F�Ȃ�
//�ߒl�F�쐬�����V�[���̃A�h���X
//������������������������������������������������������
Scene* GameOverScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOverScene::create();
	scene->addChild(layer);
	return scene;
}

//������������������������������������������������������
//�������i�V�[���̍ŏ��ɂ�邱�Ɓj
//�����F�Ȃ�
//�ߒl�F�������ł������ǂ���
//������������������������������������������������������
bool GameOverScene::init()
{
	//�V�[�����ł��ĂȂ������璆�f
	if (!Layer::init())
	{
		return false;
	}
	auto GameOverlbl = Label::createWithTTF("GameOver!!", "fonts/arial.ttf", 50);
	GameOverlbl->setPosition(DisplaySizeWidth / 2, DisplaySizeHeight / 2);
	this->addChild(GameOverlbl);

	//���͏���
	input();

	//����I��update�֐����Ă�
	this->scheduleUpdate();

	return true;
}

//������������������������������������������������������
//�X�V�i��ɂ�邱�Ɓj
//�����Fdt�@�O��X�V���Ă���̎��ԁi�b�j
//�ߒl�F�Ȃ�
//������������������������������������������������������
void GameOverScene::update(float dt)
{




}

//������������������������������������������������������
//���͏���
//�����F�Ȃ�
//�ߒl�F�Ȃ�
//������������������������������������������������������
void GameOverScene::input()
{

	auto mauseListnere = EventListenerMouse::create();
	mauseListnere->onMouseDown = [=](Event* event)
	{
		EventMouse* mouse = (EventMouse*)event;
		if (mouse->getMouseButton() == MOUSE_BUTTON_LEFT)
		{
			Director::getInstance()->replaceScene(TitleScene::createScene());
		}
		else if (mouse->getMouseButton() == MOUSE_BUTTON_RIGHT)
		{
			exit(1);
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mauseListnere, this);

	//�L�[�{�[�h�C�x���g
	auto keyListener = EventListenerKeyboard::create();

	//�L�[�������ꂽ�Ƃ�
	keyListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
	{
		if (keyCode==EventKeyboard::KeyCode::KEY_ESCAPE)
		{
			exit(1);
		}
	};

	//�L�[�{�[�h�Ď�
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, this);

}