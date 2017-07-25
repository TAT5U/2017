/*TitleScene.cpp*/

/*2017-02-17
		TAT5U
			�^�C�g���V�[��*/

#include "TitleScene.h"

//�ǉ��w�b�_
#include "PlayScene.h"

#pragma execution_character_set("utf-8");
#define EGL_SCALE cocos2d::Director::getInstance()->getOpenGLView()->getScaleX()
TitleScene::TitleScene()
{
	//�E�B���h�E�T�C�Y�擾
	DisplaySize = Director::getInstance()->getVisibleSize();

	//������
	title = nullptr;
	start = nullptr;
	backGround = nullptr;
	labelFD = nullptr;
	cursor = nullptr;
	select = nullptr;
	select2 = nullptr;
	startButton = nullptr;
	startMenu = nullptr;
	mouseListner = nullptr;
	mouse = nullptr;
	transition = nullptr;
	startRect = Rect();
	cursorRect = Rect();
	selectflg = false;
}
TitleScene::~TitleScene()
{

}
Scene* TitleScene::createScene()
{
	//Scene�쐬
	Scene *scene{ Scene::create() };
	Layer *layer{ TitleScene::create() };
	scene->addChild(layer);
	return scene;
}
bool TitleScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//�o�b�N�O���E���h�\��
	{
		backGround = Sprite::create("images/bk.png");
		backGround->setPosition(Vec2(DisplaySize.width / 2, DisplaySize.height / 2));
		this->addChild(backGround, 0);
	}

	//�^�C�g���\��
	{
		title = Label::createWithTTF("BallCatcher", "fonts/AdobeHeitiStd-Regular.otf", 50);
		title->setPosition(DisplaySize.width / 2, DisplaySize.height / 2);
		title->setColor(Color3B::BLACK);
		this->addChild(title);

	}

	//�X�^�[�g�\��
	{
		start = Label::createWithTTF("START!!", "fonts/AdobeHeitiStd-Regular.otf", 50);
		startButton = MenuItemLabel::create(start, CC_CALLBACK_1(TitleScene::ClickStart, this));
		startMenu = Menu::create(startButton, NULL);
		startMenu->setPosition(DisplaySize.width / 2-10, DisplaySize.height / 2-title->getContentSize().height);
		startMenu->setColor(Color3B::BLACK);
		this->addChild(startMenu);
	}

	//���n���X�^�[�g���x����(��\��)
	{
		labelFD = Sprite::create();
		labelFD->setTextureRect(Rect(0, 0, start->getContentSize().width, start->getContentSize().height / 2));
		labelFD->setPosition(DisplaySize.width / 2-10, DisplaySize.height / 2 - title->getContentSize().height/1.3);
		this->addChild(labelFD);
		labelFD->setVisible(false);
		startRect = labelFD->getBoundingBox();
	}

	//�J�[�\���̃��x��(��\��)
	{
		cursor = Sprite::create();
		cursor->setTextureRect(Rect(0, 0, 10, 10));
		this->addChild(cursor);
		cursor->setVisible(false);
	}

	input();
	this->scheduleUpdate();
	return true;
}
void TitleScene::update(float dt)
{
	//�}�E�X�C�x���g
	mouseListner = EventListenerMouse::create();
	mouseListner->onMouseMove = [=](Event *event)
	{
		//�}�E�X�J�[�\���C�x���g
		mouse = (EventMouse *)event;
		cursor->setPosition(Point(mouse->getCursorX(), mouse->getCursorY()) / EGL_SCALE);

		//�J�[�\���͈̔�
		cursorRect = cursor->getBoundingBox();

		//�J�[�\���ƃX�^�[�g���d�Ȃ����Ƃ�
		if (cursorRect.intersectsRect(startRect))
		{
			//select�\��
			if (selectflg == false)
			{
				select = Sprite::create("images/select.png");
				select->setPosition(labelFD->getPositionX()-120,labelFD->getPositionY());
				this->addChild(select);

				select2 = Sprite::create("images/select.png");
				select2->setRotation(180);
				select2->setPosition(labelFD->getPositionX() + labelFD->getContentSize().width/1.4, labelFD->getPositionY());
				this->addChild(select2);
				selectflg = true;
			}
		}
		else
		{
			//�G���[�΍�
			if (selectflg==true)
			{
				select->removeFromParent();
				select2->removeFromParent();
				selectflg = false;
			}
		}
	};

	//�C�x���g�Ď�
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListner, this);
}
void TitleScene::input()
{

}

//�N���b�N������
void TitleScene::ClickStart(Ref *pSender)
{
	//�V�[���ڍs
	transition = TransitionFade::create(3.0f, PlayScene::createScene());
	Director::getInstance()->replaceScene(transition);
	this->unscheduleUpdate();
}