/*PlayScene.cpp*/

/*2017-06-01
	TAT5U
		�v���C�V�[��*/

#include "PlayScene.h"
#include "GameOverScene.h"
#include "GameClearScene.h"
#include "WallDraw.h"
#include "Score.h"

//�X�e�[�W�̐�
#define StageMax 3

//�{�X�X�e�[�W���N���A����܂ł̃J�E���g
#define Boss_Stage 2

//��������
#define Time 120;

//�Q�[���J�n�܂ł̎���
#define Delay 3;

#pragma execution_character_set("utf-8");

PlayScene::PlayScene()
{
	//�E�B���h�E�T�C�Y�擾
	DisplaySize = Director::getInstance()->getVisibleSize();

	//������
	Stage = nullptr;
	Ball = nullptr;
	Goal = nullptr;
	Fake1 = nullptr;
	Fake2 = nullptr;
	Fake3 = nullptr;
	bk = nullptr;
	timelbl = nullptr;
	BallPhysic = nullptr;
	GoalPhysic = nullptr;
	StagePhysic = nullptr;
	Fake1Physic = nullptr;
	Fake2Physic = nullptr;
	Fake3Physic = nullptr;
	StageShape = nullptr;
	GoalShape = nullptr;
	Fake1Shape = nullptr;
	Fake2Shape = nullptr;
	Fake3Shape = nullptr;
	BallRect = Rect();
	TouchPos = Vec2();
	BallPos = Vec2();
	BallNode = nullptr;
	StageNum = 1;
	BossCnt = 0;
	ContactTime = 999;
	StageName = string();
	fakeflg = false;
	scheduleflg = true;
	contactflg = false;
	TouchFlg = false;
	delayflg = false;
	listener = nullptr;
	physicsContact = nullptr;
	contact = nullptr;
	trans = nullptr;
	time = Time;
	dtime = Delay;
}

PlayScene::~PlayScene()
{
	
}

Scene* PlayScene::createScene()
{
	//�V�[�����d�͕t���Ő���
	Scene *scene = Scene::createWithPhysics();
	PhysicsWorld *world = scene->getPhysicsWorld();
	world->setGravity(Vec2(0, -500));
	world->setSpeed(1.0f);
	
	//���C������
	Layer *layer = PlayScene::create();
	Layer *WallLayer = WallDraw::create();
	scene->addChild(layer);
	scene->addChild(WallLayer);
	return scene;
}

bool PlayScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//�ŏ��̃X�e�[�W�����i�[
	StageName = "St0" + to_string(StageNum);

	//�ePhysicsShapeCache�𗘗p�ł���悤�ɂ���
	StageShape = PhysicsShapeCache::getInstance();
	GoalShape = PhysicsShapeCache::getInstance();
	Fake1Shape = PhysicsShapeCache::getInstance();
	Fake2Shape = PhysicsShapeCache::getInstance();
	Fake3Shape = PhysicsShapeCache::getInstance();

	//�w�i�\��
	{
		bk = Sprite::create("images/background.png");
		bk->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		bk->setPosition(0, 0);
		this->addChild(bk);
	}

	//�������ԕ\��
	{
		timelbl = Label::createWithSystemFont(StringUtils::toString((int)time) + "�b", "fonts/arial.ttf", 100);
		timelbl->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
		timelbl->setPosition(DisplaySize.width, DisplaySize.height);

		//�e��t����
		timelbl->enableShadow(Color4B::BLACK, Size(4, -3), 10);
		this->addChild(timelbl,999);
	}

	//�X�e�[�W�̃v���p�e�B���X�g��ǂݍ���
	StageShape->addShapesWithFile("plist/"+StageName+".plist");

	//�X�e�[�W�\��
	{
		Stage = Sprite::create("images/"+StageName+".png");

		//�X�e�[�W�̕����G���W�����i�[����
		StagePhysic = StageShape->setPhysics(StageName, Stage);
		Stage->setPhysicsBody(StagePhysic);

		Stage->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		Stage->setPosition(0, 0);
		this->addChild(Stage);
	}

	//�S�[���̃v���p�e�B���X�g��ǂݍ���
	GoalShape->addShapesWithFile("plist/"+StageName+"Goal.plist");

	//�S�[���\��
	{
		Goal = Sprite::create("images/"+StageName+"Goal.png");

		//�S�[���̕����G���W�����i�[����
		GoalPhysic = GoalShape->setPhysics(StageName+"Goal", Goal);

		//�Փ˔��肷�邽�߂Ɏ��ʎq���i�[����
		GoalPhysic->setCategoryBitmask(static_cast<int>(PhysicName::Goal));
		GoalPhysic->setCollisionBitmask(static_cast<int>(PhysicName::Ball));
		GoalPhysic->setContactTestBitmask(INT_MAX);

		Goal->setPhysicsBody(GoalPhysic);
		Goal->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		Goal->setPosition(0, 0);
		this->addChild(Goal);

		//�������g�Ƀ^�O�t������
		Goal->setTag(static_cast<int>(PhysicName::Goal));
	}

	//�{�[���\��
	{
		Ball = Sprite::create("images/ball.png");

		Ball->setPosition(10, DisplaySize.height / 2);
		BallPhysic = PhysicsBody::createCircle(Ball->getContentSize().width / 2);

		//�Փ˔��肷�邽�߂Ɏ��ʎq���i�[����
		BallPhysic->setCategoryBitmask(static_cast<int>(PhysicName::Ball));
		BallPhysic->setCollisionBitmask(static_cast<int>(PhysicName::Goal));
		BallPhysic->setContactTestBitmask(INT_MAX);

		Ball->setPhysicsBody(BallPhysic);
		this->addChild(Ball);

		//�������g�Ƀ^�O�t������
		Ball->setTag(static_cast<int>(PhysicName::Ball));
	}
	input();
	this->scheduleUpdate();
	return true;
}

void PlayScene::update(float dt)
{
	//�Q�[�����J�n������
	if (delayflg==true)
	{
		//�X�e�[�W�ύX���Ă��Ȃ��Ƃ�
		if (scheduleflg == true)
		{
			//�{�[�����Ȃ��ꍇ
			if (Ball == NULL)
			{
				Ball = Sprite::create("images/ball.png");

				//�{�X�X�e�[�W�̍Ō�̃��[�h�ɂȂ��Ă���Ƃ�
				if (BossCnt>3)
				{
					//�S�[���̋߂��Ƀ{�[�����Z�b�g
					Ball->setPosition(900, 50);
				}
				else
				{
					Ball->setPosition(10, DisplaySize.height / 2);
				}

				BallPhysic = PhysicsBody::createCircle(Ball->getContentSize().width / 2);
				BallPhysic->setCategoryBitmask(static_cast<int>(PhysicName::Ball));
				BallPhysic->setCollisionBitmask(static_cast<int>(PhysicName::Goal));
				BallPhysic->setContactTestBitmask(INT_MAX);

				//�Փ˔��肷�邽�߂Ɏ��ʎq���i�[����
				Ball->setPhysicsBody(BallPhysic);
				this->addChild(Ball);
				Ball->setTag(static_cast<int>(PhysicName::Ball));
			}
			else
			{
				//�{�[������ʊO�ɍs�����Ƃ�
				if (Ball->getPositionY()<0 || Ball->getPositionY()>DisplaySize.height || Ball->getPositionX()<0 || Ball->getPositionX()>DisplaySize.width)
				{
					Ball->removeFromParent();
					//�{�[���̈ʒu���ŏ��̈ʒu�ɖ߂�
					Ball = Sprite::create("images/ball.png");

					if (BossCnt>3)
					{
						Ball->setPosition(900, 50);
					}
					else
					{
						Ball->setPosition(10, DisplaySize.height / 2);
					}

					BallPhysic = PhysicsBody::createCircle(Ball->getContentSize().width / 2);
					BallPhysic->setCategoryBitmask(static_cast<int>(PhysicName::Ball));
					BallPhysic->setCollisionBitmask(static_cast<int>(PhysicName::Goal));
					BallPhysic->setContactTestBitmask(INT_MAX);
					Ball->setPhysicsBody(BallPhysic);
					this->addChild(Ball);

					//�������g�Ƀ^�O�t������
					Ball->setTag(static_cast<int>(PhysicName::Ball));
				}
				//�{�[���͈͎̔擾
				BallRect = Ball->getBoundingBox();
			}
		}
	}
	//���Ԃ�1�b�����炷
	dtime -= dt;

	//�Q�[���J�n���ԂɂȂ�����
	if (dtime<0)
	{
		//���̏��������������߂Ƀt���O��ύX
		delayflg = true;

		//��������
		time -= dt;
		timelbl->setString(StringUtils::toString((int)time) + "�b");

		//�Q�[���I�[�o�[
		if (time<0)
		{
			trans = TransitionFade::create(3.0f, GameOverScene::createScene());
			Director::getInstance()->replaceScene(trans);
			this->unscheduleUpdate();
		}
	}
}
void PlayScene::input()
{
	//�^�b�`�C�x���g
	listener = EventListenerTouchOneByOne::create();
	
	//�^�b�`���n�߂��Ƃ�
	listener->onTouchBegan = [this](Touch *touch, Event *event)
	{
		//�Q�[���J�n�܂ő҂�
		if (delayflg==true)
		{
			//�{�[���͈͎̔擾
			BallRect = Ball->getBoundingBox();
			if (scheduleflg == true)
			{
				//�^�b�`�����ʒu�ƃ{�[���͈̔͂������̂Ƃ�
				if (BallRect.containsPoint(TouchPos = touch->getLocation()))
				{
					//�^�b�`�t���O��true��
					TouchFlg = true;
					
					//�m�[�h�Ƀ{�[�����i�[
					BallNode = Ball;
				}
			}
		}
		return true;
	};
	
	//�������Ƃ�
	listener->onTouchEnded = [this](Touch *touch, Event *event)
	{
		if (delayflg==true)
		{
			//�^�b�`�t���O��true�̂Ƃ�
			if (TouchFlg == true)
			{
				//�������������~500�̗͂Ŕ�΂�
				BallPos = (TouchPos - touch->getLocation()) * 500;
				
				//�i�[�����m�[�h�ɗ͂�������
				BallNode->getPhysicsBody()->applyImpulse(BallPos);
				
				//�^�b�`�t���O������
				TouchFlg = false;
			}
		}
	};
	
	//�^�b�`���邩�ǂ������Ď�
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	//�ڐG���ɌĂ΂��֐�������
	contact = EventListenerPhysicsContact::create();
	
	//�ڐG���ɌĂ΂��
	contact->onContactBegin = [this](PhysicsContact& c)
	{
		auto other = (c.getShapeA()->getBody() == this->getChildByTag(static_cast<int>(PhysicName::Goal))->getPhysicsBody()) ? c.getShapeB() : c.getShapeA();
		
		//�ڐG����̏����擾
		auto body = other->getBody();
		
		//���ʎq���擾
		auto cate = body->getCategoryBitmask();

		//�A���ŐڐG�����Ȃ�
		if (contactflg == false)
		{
			//�Փ˂��ăX�e�[�W�ڍs������̎��Ԃƈꏏ�ł���ꍇ�͓����蔻��ɓ���Ȃ�
			//�X�e�[�W�ڍs���Ă���{�[�����n�ʂɗ�������܂ł̎���(�{�X�X�e�[�W�̃S�[������)�͖�1�b������̂�
			//���ꂳ���Ȃ����Ƃɂ��A�����Đi�ނ��Ƃ�h��
			//�{�X�̃S�[���͖ڂ̑O�Ȃ̂�1�b������Ȃ����A���������ʂɂ���Ƃ܂��A���œ���
			//3�ڂ̃t�F�C�N��ʂ������_�ŃN���A�ɂȂ��Ă��܂�����1�b�ȏ�J��������
			if (ContactTime != (int)time)
			{
				//�S�[��(�t�F�C�N)�ƃ{�[��������������
				if (cate & static_cast<int>(PhysicName::Ball))
				{
					//�ڐG�����Ȃ����߂Ƀt���O�ύX
					contactflg = true;

					//�X�e�[�W�̐����X�e�[�W�ő吔�𒴂��Ă��邩�ǂ���
					if (StageNum < StageMax)
					{
						//�X�P�W���[�����~�߂邽�߂Ƀt���O��ύX
						scheduleflg = false;

						//�{�[������x����
						Ball->removeFromParent();

						//�ePhysicsShapeCache��������x�ݒ肷��
						StageShape = PhysicsShapeCache::getInstance();
						GoalShape = PhysicsShapeCache::getInstance();
						Fake1Shape = PhysicsShapeCache::getInstance();
						Fake2Shape = PhysicsShapeCache::getInstance();
						Fake3Shape = PhysicsShapeCache::getInstance();

						//�X�e�[�W�E�S�[��������
						Stage->removeFromParent();
						Goal->removeFromParent();

						//�t�F�C�N���\�����Ă�����t�F�C�N������
						if (BossCnt > 0 && (fakeflg == false))
						{
							Fake1->removeFromParent();
							Fake2->removeFromParent();
							Fake3->removeFromParent();
						}

						//�{�X�X�e�[�W�Ȃ�t�F�C�N�\���p�̃J�E���g������
						if ((StageNum == Boss_Stage) && (fakeflg == false))
						{
							BossCnt++;
						}
						else
						{
							StageNum++;
						}

						//�{�X�X�e�[�W��ǂݍ��܂��邽�߂̏���
						if ((StageNum == Boss_Stage) && (BossCnt > 0))
						{
							StageName = "St0" + to_string(StageNum + 1);
						}
						else
						{
							StageName = "St0" + to_string(StageNum);
						}

						//�X�e�[�W�̃v���p�e�B���X�g��ǂݍ���
						StageShape->addShapesWithFile("plist/" + StageName + ".plist");

						//�X�e�[�W�\��
						{
							Stage = Sprite::create("images/" + StageName + ".png");
							StagePhysic = StageShape->setPhysics(StageName, Stage);
							Stage->setPhysicsBody(StagePhysic);
							Stage->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
							Stage->setPosition(0, 0);
							this->addChild(Stage);
						}

						//�{�X�X�e�[�W�̎�
						if ((StageNum == Boss_Stage) && (BossCnt > 0) && (fakeflg == false))
						{
							//�S�[���E�t�F�C�N�̃v���p�e�B���X�g��ǂݍ���
							GoalShape->addShapesWithFile("plist/" + StageName + "Goal.plist");
							Fake1Shape->addShapesWithFile("plist/" + StageName + "-1.plist");
							Fake2Shape->addShapesWithFile("plist/" + StageName + "-2.plist");
							Fake3Shape->addShapesWithFile("plist/" + StageName + "-3.plist");

							//�S�[���E�t�F�C�N�̕\��
							Goal = Sprite::create("images/" + StageName + "Goal.png");
							Fake1 = Sprite::create("images/" + StageName + "-1.png");
							Fake2 = Sprite::create("images/" + StageName + "-2.png");
							Fake3 = Sprite::create("images/" + StageName + "-3.png");

							//�ŏ��̃t�F�C�N
							if (BossCnt == 1)
							{
								Fake1Physic = GoalShape->setPhysics(StageName + "-1", Fake1);

								//���ʎq�ƃ^�O�t��
								Fake1Physic->setCategoryBitmask(static_cast<int>(PhysicName::Goal));
								Fake1Physic->setCollisionBitmask(static_cast<int>(PhysicName::Ball));
								Fake1->setPhysicsBody(Fake1Physic);
								Fake1Physic->setContactTestBitmask(INT_MAX);
								Fake1->setTag(static_cast<int>(PhysicName::Goal));

							}

							//2�Ԗڂ̃t�F�C�N
							else if (BossCnt == 2)
							{
								Fake2Physic = GoalShape->setPhysics(StageName + "-2", Fake2);

								//���ʎq�ƃ^�O�t��
								Fake2Physic->setCategoryBitmask(static_cast<int>(PhysicName::Goal));
								Fake2Physic->setCollisionBitmask(static_cast<int>(PhysicName::Ball));
								Fake2->setPhysicsBody(Fake2Physic);
								Fake2Physic->setContactTestBitmask(INT_MAX);
								Fake2->setTag(static_cast<int>(PhysicName::Goal));
							}

							//3�Ԗڂ̃t�F�C�N
							else if (BossCnt == 3)
							{
								Fake3Physic = GoalShape->setPhysics(StageName + "-3", Fake3);

								//���ʎq�ƃ^�O�t��
								Fake3Physic->setCategoryBitmask(static_cast<int>(PhysicName::Goal));
								Fake3Physic->setCollisionBitmask(static_cast<int>(PhysicName::Ball));
								Fake3->setPhysicsBody(Fake3Physic);
								Fake3Physic->setContactTestBitmask(INT_MAX);
								Fake3->setTag(static_cast<int>(PhysicName::Goal));
							}

							//3�Ԗڂ̃t�F�C�N�܂ŏՓ˂��Đi�ނ��Ƃɂ���ăS�[���ɓ��B�ł���
							else
							{
								GoalPhysic = GoalShape->setPhysics(StageName + "Goal", Goal);

								//���ʎq�ƃ^�O�t��
								GoalPhysic->setCategoryBitmask(static_cast<int>(PhysicName::Goal));
								GoalPhysic->setCollisionBitmask(static_cast<int>(PhysicName::Ball));
								Goal->setPhysicsBody(GoalPhysic);
								GoalPhysic->setContactTestBitmask(INT_MAX);
								Goal->setTag(static_cast<int>(PhysicName::Goal));

								//�t�F�C�N�͎g��Ȃ��̂Ńt���O��ύX
								fakeflg = true;

								//�X�e�[�W�̃J�E���g���i�߂�
								//�S�[���ɓ����������ɃN���A�V�[���Ɉڍs�����邽��
								StageNum++;
							}

							//�e�X�v���C�g�̐ݒ�
							Goal->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
							Fake1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
							Fake2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
							Fake3->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
							Goal->setPosition(0, 0);
							Fake1->setPosition(0, 0);
							Fake2->setPosition(0, 0);
							Fake3->setPosition(0, 0);
							this->addChild(Goal);
							this->addChild(Fake1);
							this->addChild(Fake2);
							this->addChild(Fake3);
						}

						//�{�X�X�e�[�W�ȊO
						else
						{
							//�S�[���̃v���p�e�B���X�g��ǂݍ���
							GoalShape->addShapesWithFile("plist/" + StageName + "Goal.plist");

							//�S�[���\��
							{
								Goal = Sprite::create("images/" + StageName + "Goal.png");
								GoalPhysic = GoalShape->setPhysics(StageName + "Goal", Goal);

								//���ʎq�ƃ^�O�t��&�\��
								GoalPhysic->setCategoryBitmask(static_cast<int>(PhysicName::Goal));
								GoalPhysic->setCollisionBitmask(static_cast<int>(PhysicName::Ball));
								GoalPhysic->setContactTestBitmask(INT_MAX);
								Goal->setPhysicsBody(GoalPhysic);
								Goal->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
								Goal->setPosition(0, 0);
								this->addChild(Goal);
								Goal->setTag(static_cast<int>(PhysicName::Goal));
							}
						}

						//�{�[����������x�쐬
						Ball = Sprite::create("images/ball.png");

						//�{�X�X�e�[�W���N���A�ł���Ƃ�
						if (BossCnt > 3)
						{
							Ball->setPosition(900, 50);
						}
						else
						{
							Ball->setPosition(10, DisplaySize.height / 2);
						}
						BallPhysic = PhysicsBody::createCircle(Ball->getContentSize().width / 2);

						//���ʎq�ƃ^�O�t��&�\��
						BallPhysic->setCategoryBitmask(static_cast<int>(PhysicName::Ball));
						BallPhysic->setCollisionBitmask(static_cast<int>(PhysicName::Goal));
						BallPhysic->setContactTestBitmask(INT_MAX);
						Ball->setPhysicsBody(BallPhysic);
						this->addChild(Ball);
						Ball->setTag(static_cast<int>(PhysicName::Ball));

						//�X�P�W���[���̃t���O��ύX���ď����𓮂���
						scheduleflg = true;
					}

					//�N���A������
					else
					{
						//�Q�[���̐������Ԃ��炩���������Ԃ������ăX�R�A�̎��Ԃ��o��
						int score = Time;
						score = score - (int)time;

						Score sc;

						//�X�R�A����������
						sc.SetScore(score);
						trans = TransitionFade::create(3.0f, GameClearScene::createScene());
						Director::getInstance()->replaceScene(trans);
						this->unscheduleUpdate();
					}

					//�������I������̂ŐڐG�ł���悤�Ƀt���O��ύX
					contactflg = false;

					//�������I�������Ɏ��Ԃ�����
					ContactTime = (int)time;
				}
			}
			
		}
		return true;
	};
	//�ڐG����
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contact, this);
}
