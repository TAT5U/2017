//�C���N���[�h
#include "TitleScene.h"
#include "PlayScene.h"
#include "SimpleAudioEngine.h" 

//���{��g�p��
#pragma execution_character_set("utf-8")
USING_NS_CC;
//������������������������������������������������������
//�R���X�g���N�^
//������������������������������������������������������
TitleScene::TitleScene()
{
	//�}�E�X�J�[�\����\��
	ShowCursor(false);
	DisplaySizeWidth = CCDirector::sharedDirector()->getWinSize().width;
	DisplaySizeHeight = CCDirector::sharedDirector()->getWinSize().height;
	//BGM�v�����[�h
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("BGM.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("BGM.mp3", true);
}

//������������������������������������������������������
//�f�X�g���N�^
//������������������������������������������������������
TitleScene::~TitleScene()
{



}

//������������������������������������������������������
//�V�[���쐬
//�����F�Ȃ�
//�ߒl�F�쐬�����V�[���̃A�h���X
//������������������������������������������������������
Scene* TitleScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TitleScene::create();
	scene->addChild(layer);
	return scene;
}

//������������������������������������������������������
//�������i�V�[���̍ŏ��ɂ�邱�Ɓj
//�����F�Ȃ�
//�ߒl�F�������ł������ǂ���
//������������������������������������������������������
bool TitleScene::init()
{
	//�V�[�����ł��ĂȂ������璆�f
	if (!Layer::init())
	{
		return false;
	}

	auto Title = Label::createWithTTF("Shooting Game\n     START!!", "fonts/arial.ttf", 50);
	Title->setPosition(DisplaySizeWidth / 2, DisplaySizeHeight / 2);
	this->addChild(Title);
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
void TitleScene::update(float dt)
{




}

//������������������������������������������������������
//���͏���
//�����F�Ȃ�
//�ߒl�F�Ȃ�
//������������������������������������������������������
void TitleScene::input()
{


	    //�^�b�`�C�x���g
    auto listener = EventListenerTouchOneByOne::create();

    //��ʂ��^�b�`�����Ƃ�
    listener->onTouchBegan = [this](Touch* touch, Event* event)
    {
		//auto transition = TransitionFade::create(3.0f, PlayScene::createScene());
		//Director::getInstance()->replaceScene(transition);
		//this->unscheduleUpdate();
		Director::getInstance()->replaceScene(PlayScene::createScene());
		return true;
    };

    //�^�b�`�Ď�
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

}