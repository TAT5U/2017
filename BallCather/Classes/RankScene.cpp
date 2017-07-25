/*RankScene.cpp*/

/*2017-02-17
		TAT5U
			�����N�V�[��*/

#include "RankScene.h"

//�ǉ��w�b�_
#include "GameOverScene.h"
#include "Score.h"
#include<iomanip>

#pragma execution_character_set("utf-8");
#define EGL_SCALE cocos2d::Director::getInstance()->getOpenGLView()->getScaleX()

RankScene::RankScene()
{
	//�E�B���h�E�T�C�Y�擾
	DisplaySize = Director::getInstance()->getVisibleSize();

	//������
	myScore = nullptr;
	rank = nullptr;
	rankScore = nullptr;
	back = nullptr;
	backGround = nullptr;
	labelFD = nullptr;
	cursor = nullptr;
	select = nullptr;
	select2 = nullptr;
	backButton = nullptr;
	backMenu = nullptr;
	mouseListner = nullptr;
	mouse = nullptr;
	transition = nullptr;
	backRect = Rect();
	cursorRect = Rect();
	selectflg = false;
	i = 0;
	n = 0;


}
RankScene::~RankScene()
{

}
Scene* RankScene::createScene()
{
	//Scene�쐬
	Scene *scene{ Scene::create() };
	Layer *layer{ RankScene::create() };
	scene->addChild(layer);
	return scene;
}
bool RankScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//Score�𗘗p�ɂ���
	Score sc;

	//�o�b�N�O���E���h�\��
	{
		backGround = Sprite::create("images/bk.png");
		backGround->setPosition(Vec2(DisplaySize.width / 2, DisplaySize.height / 2));
		this->addChild(backGround, 0);
	}

	//�o�b�N�\��
	{
		back = Label::createWithSystemFont("BACK", "fonts/AdobeHeitiStd-Regular.otf", 40);
		backButton = MenuItemLabel::create(back, CC_CALLBACK_1(RankScene::ClickBack, this));
		backMenu = Menu::create(backButton, NULL);
		backMenu->setPosition(DisplaySize.width - 95,DisplaySize.height-25);
		backMenu->setColor(Color3B::BLACK);
		this->addChild(backMenu);
	}

	//���n���o�b�N���x����(��\��)
	{
		labelFD = Sprite::create();
		labelFD->setTextureRect(Rect(0, 0, back->getContentSize().width, back->getContentSize().height / 2));
		labelFD->setPosition(DisplaySize.width - 95, DisplaySize.height - 25);
		this->addChild(labelFD);
		labelFD->setVisible(false);
		backRect = labelFD->getBoundingBox();
	}

	//�}�C�X�R�A�\��
	{
		myScore = Label::createWithSystemFont("SCORE    " + StringUtils::toString(sc.GetScore(0, NULL)) + "\nRANK     " + StringUtils::toString(sc.GetScore(1, NULL))+"th", "fonts/AdobeHeitiStd-Regular.otf", 50);
		myScore->setPosition(DisplaySize.width / 2, (DisplaySize.height / 2 + DisplaySize.height / 3)+5);
		myScore->setColor(Color3B::BLACK);
		this->addChild(myScore);
	}

	//�J�[�\���̃��x��(��\��)
	{
		cursor = Sprite::create();
		cursor->setTextureRect(Rect(0, 0, 10, 10));
		this->addChild(cursor);
		cursor->setVisible(false);
	}

	//�ۑ�����Ă���X�R�A���擾
	n = sc.GetScore(3,NULL);

	//9�ȉ��̎�
	if (n<10)
	{
		while (i<n)
		{
			//�����낦
			s = StringUtils::toString(sc.GetScore(2, i));
			if (i==0)
			{
				maxScore = s;
			}
			while (s.length()<maxScore.length())
			{
				s = " " + s;
			}
			str2.append(StringUtils::toString(i + 1) + "th    \n");
			str.append(s + "\n");
			i++;
		}
	}

	//10�ȏ�̎�
	else
	{
		while (i<10)
		{
			//�����낦
			s = StringUtils::toString(sc.GetScore(2, i));
			if (i == 0)
			{
				maxScore = s;
			}
			while (s.length()<maxScore.length())
			{
				s = " " + s;
			}
			str2.append(StringUtils::toString(i + 1) + "th    \n");
			str.append(s + "\n");
			i++;
		}
	}

	//�g�p�ς݂Ȃ̂ŏ�����
	i = 0;

	{
		rank = Label::createWithSystemFont(str2, "fonts/AdobeHeitiStd-Regular.otf", 50);
		rank->setPosition(myScore->getPositionX()/1.5, myScore->getPositionY() - 350);
		rank->setColor(Color3B::BLACK);
		rank->setAlignment(CCTextAlignment::RIGHT);
		this->addChild(rank);
	}
	//�����N�\��
	{
		rankScore = Label::createWithSystemFont(str, "fonts/AdobeHeitiStd-Regular.otf", 50);
		rankScore->setPosition(rank->getPositionX()+rank->getContentSize().width, myScore->getPositionY() - 350);
		rankScore->setColor(Color3B::BLACK);
		rankScore->setAlignment(CCTextAlignment::RIGHT);
		this->addChild(rankScore);
	}

	input();
	this->scheduleUpdate();
	return true;
}
void RankScene::update(float dt)
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

		//�J�[�\���ƃo�b�N���d�Ȃ����Ƃ�
		if (cursorRect.intersectsRect(backRect))
		{
			//select�\��
			if (selectflg == false)
			{
				select = Sprite::create("images/select.png");
				select->setScale(0.7);
				select->setPosition(labelFD->getPositionX() - 80, labelFD->getPositionY());
				this->addChild(select);

				select2 = Sprite::create("images/select.png");
				select2->setRotation(180);
				select2->setScale(0.7);
				select2->setPosition(labelFD->getPositionX() + labelFD->getContentSize().width / 1.4, labelFD->getPositionY());
				this->addChild(select2);
				selectflg = true;
			}
		}
		else
		{
			//�G���[�΍�
			if (selectflg == true)
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
void RankScene::input()
{

}
//�N���b�N������
void RankScene::ClickBack(Ref *pSender)
{
	//�V�[���ڍs
	transition = TransitionFade::create(3.0f, GameOverScene::createScene());
	Director::getInstance()->replaceScene(transition);
	this->unscheduleUpdate();
}
