//�C���N���[�h
#include "PlayScene.h"
#include"ClearScene.h"
#include "GameOverScene.h"


//�ǉ�
#include<time.h>
#define EGL_SCALE cocos2d::Director::getInstance()->getOpenGLView()->getScaleX()
#include "SimpleAudioEngine.h" 
// ���� ����
const float TIME_LIMIT_SECOND = 60;
const float START_TIME = 4;


//���{��g�p��
#pragma execution_character_set("utf-8")
using namespace std;
//������������������������������������������������������
//�R���X�g���N�^
//������������������������������������������������������
PlayScene::PlayScene()
	:_second(TIME_LIMIT_SECOND)
,_startTime(START_TIME)
{
	//�E�B���h�E�̃T�C�Y�擾&�@�̂̏����ʒu�ݒ�
	DisplaySizeWidth = CCDirector::sharedDirector()->getWinSize().width;
	DisplaySizeHeight = CCDirector::sharedDirector()->getWinSize().height;
	cursorY = DisplaySizeHeight / 10;

	//�J�E���g�̏�����
	i = 0;

	//����������+���
	srand(time(NULL));
	rand(); rand(); rand(); rand(); rand();

	//�|�����G�̃J�E���g��������
	EnemyDeadCount = 0;
	EnemyCount = 0;

	//�G�̐����t���O�����ׂĐ����ɂ���&�ړ���̏�����
	while (i<3)
	{
		_isEnemyDead[i] = false;
		EnemyFlgposX[i] = 0;
		EnemyFlgposY[i] = 0;
		i++;
	}
	//�ė��p�̂��ߏ�����
	i = 0;
	startTimeTextflg = false;
}

//������������������������������������������������������
//�f�X�g���N�^
//������������������������������������������������������
PlayScene::~PlayScene()
{
}

//������������������������������������������������������
//�V�[���쐬
//�����F�Ȃ�
//�ߒl�F�쐬�����V�[���̃A�h���X
//������������������������������������������������������
Scene* PlayScene::createScene()
{
	auto scene = Scene::create();
	auto layer = PlayScene::create();
	scene->addChild(layer);
	return scene;
}

//������������������������������������������������������
//�������i�V�[���̍ŏ��ɂ�邱�Ɓj
//�����F�Ȃ�
//�ߒl�F�������ł������ǂ���
//������������������������������������������������������
bool PlayScene::init()
{
	//�V�[�����ł��ĂȂ������璆�f
	if (!Layer::init())
	{
		return false;
	}
	//���ʉ��v�����[�h
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("bomb.wav");



	//�@�̂̐錾
	{
		auto cursor = Sprite::create("player.png");
		cursor->setPosition(DisplaySizeWidth / 2, cursorY);
		this->addChild(cursor);
		_cursor = cursor;
	}


	
	//�G�̐錾
	while (i < 3)
	{
		auto enemy = Sprite::create("enemy.png");

		//�������g�p�����ʒu
		//�� ��ʂ���50�������Ƃ��납��50�������Ƃ���܂ł͈̔�
		EnemyFlgposX[i] = rand() % (((int)DisplaySizeWidth - 50) - 50 + 1) + 50;
		//�c ��ʂ���50�������Ƃ��납��@��+100�̂Ƃ���܂ł͈̔�
		EnemyFlgposY[i] = rand() % (((int)DisplaySizeHeight - 50) - (cursorY + 100) + 1) + (cursorY + 100);
		enemy->setPosition(EnemyFlgposX[i], EnemyFlgposY[i]);

		this->addChild(enemy);
		_enemy[i] = enemy;
		_isEnemyDead[i] = false;
		EnemyCount++;
		i++;
	}
	//�ė��p�̂��ߏ�����
	i = 0;

	int second = static_cast < int >(_second); // int �^ �� �L���X�g ����
	secondText = Label::createWithSystemFont("�������� " + StringUtils::toString(second) + " �b", "fonts/arial.ttf", 20);
	secondText->setPosition(DisplaySizeWidth / 6, DisplaySizeHeight - DisplaySizeHeight / 20);
	this->addChild(secondText);

	int startTime = static_cast <int>(_startTime);
	startTimeText=Label::createWithSystemFont( StringUtils::toString(startTime), "fonts/arial.ttf", 80);
	startTimeText->setPosition(DisplaySizeWidth / 2, DisplaySizeHeight / 2);
	this->addChild(startTimeText);
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
void PlayScene::update(float dt)
{
	_startTime -= dt;
	int startTime = static_cast <int>(_startTime);
	if (startTime<=0)
	{
		if (startTimeTextflg==false)
		{
			//�e�̐錾
			{
				auto bullet = Sprite::create("bullet.png");
				bullet->setPosition(_cursor->getPositionX(), cursorY);
				this->addChild(bullet);
				_bullet = bullet;
			}
			startTimeText->removeFromParent();
			startTimeTextflg = true;
		}

		// �c�� �b �� �� ���炷
		_second -= dt;
		// �c�� �b �� �� �\�� �� �X�V ����
		int second = static_cast < int >(_second); // int �^ �� �L���X�g ����
		secondText->setString("�������� " + StringUtils::toString(second) + " �b");


		if (second <= 0)
		{
			auto transition = TransitionFade::create(3.0f, GameOverScene::createScene());
			Director::getInstance()->replaceScene(transition);
			this->unscheduleUpdate();
		}
		//�e�̈ړ�
		Vec2 bulletpos = _bullet->getPosition();
		bulletpos.y += 10;
		_bullet->setPosition(bulletpos);

		//�e����ʊO�ɂ�������܂��o��
		if (_bullet->getPositionY() > DisplaySizeHeight)
		{
			_bullet->setPosition(_cursor->getPositionX(), cursorY);
		}

		//�e�̏Փ˂̔�����i�[
		Rect bulletRect = _bullet->getBoundingBox();
		while (i<3)
		{
			if (_isEnemyDead[i] == true)
			{

			}
			else
			{
				//�w�肵���Ƃ���܂ňړ����I�����Ƃ����̈ړ�����w��
				if (_enemy[i]->getPositionX() == EnemyFlgposX[i] && _enemy[i]->getPositionY() == EnemyFlgposY[i])
				{
					EnemyFlgposX[i] = rand() % (((int)DisplaySizeWidth - 50) - 50 + 1) + 50;
					EnemyFlgposY[i] = rand() % (((int)DisplaySizeHeight - 50) - (cursorY + 100) + 1) + (cursorY + 100);
					auto move = MoveTo::create(rand() % 3 + 1, Point(EnemyFlgposX[i], EnemyFlgposY[i]));
					_enemy[i]->runAction(move);
				}
				//�Փ˔���œG������
				Rect enemyRect = _enemy[i]->getBoundingBox();
				if (bulletRect.intersectsRect(enemyRect))
				{
					//����
					auto bomb = Sprite::create("bomb0000.png");
					bomb->setPosition(_enemy[i]->getPosition());
					this->addChild(bomb);

					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bomb.wav");
					auto anim = Animation::create();
					anim->addSpriteFrameWithFileName("bomb0001.png");
					anim->addSpriteFrameWithFileName("bomb0002.png");
					anim->addSpriteFrameWithFileName("bomb0003.png");
					anim->addSpriteFrameWithFileName("bomb0004.png");
					anim->addSpriteFrameWithFileName("bomb0005.png");
					anim->addSpriteFrameWithFileName("bomb0006.png");
					anim->addSpriteFrameWithFileName("bomb0007.png");
					anim->setDelayPerUnit(0.06f);
					auto animate = Animate::create(anim);
					auto removebomb = RemoveSelf::create(true);
					auto bombAction = Sequence::create(animate, removebomb, NULL);
					bomb->runAction(bombAction);


					//�G������
					_enemy[i]->removeFromParent();
					_isEnemyDead[i] = true;
					EnemyDeadCount++;
				}
			}
			i++;
		}
		//�ė��p�̂��ߏ�����
		i = 0;

		//�G�����ׂď�������N���A���
		if (EnemyDeadCount == EnemyCount)
		{
			auto transition = TransitionFade::create(3.0f, ClearScene::createScene());
			Director::getInstance()->replaceScene(transition);
			this->unscheduleUpdate();
		}
	}
	else
	{
		startTimeText->setString(StringUtils::toString(startTime));
	}
	
}

//������������������������������������������������������
//���͏���
//�����F�Ȃ�
//�ߒl�F�Ȃ�
//������������������������������������������������������
void PlayScene::input()
{
	auto mauseListnere = EventListenerMouse::create();
	mauseListnere->onMouseMove = [=](Event* event)
	{
		EventMouse* mouse = (EventMouse*)event;
		_cursor->setPosition(Point(mouse->getCursorX(), cursorY) / EGL_SCALE);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mauseListnere, this);
	
	auto touch = EventListenerTouchOneByOne::create();
	touch->onTouchBegan = [=](Touch* touc, Event* eve)
	{
		return true;
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touch, this);
}