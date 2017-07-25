#include "PlayScene.h"

//�ǉ��w�b�_
#include "GameOverScene.h"
#include "Score.h"

#pragma execution_character_set("utf-8");
#define EGL_SCALE cocos2d::Director::getInstance()->getOpenGLView()->getScaleX()

PlayScene::PlayScene()
{
	//�E�B���h�E�T�C�Y�擾
	DisplaySize = Director::getInstance()->getVisibleSize();

	//������
	cursor = nullptr;
	backGround = nullptr;
	pos = nullptr;
	workflg = nullptr;
	mouseListner = nullptr;
	mouse = nullptr;
	anime = nullptr;
	anim = nullptr;
	animate = nullptr;
	remove = nullptr;
	action = nullptr;
	n = 3;
	i = 0;
	cnt = 0;
	score = 0;
	scoreText = nullptr;
	startTimeText = nullptr;
	speedFlg = false;
	timeFlg = false;
	textTimeFlg = false;
	startTime = 4;
	startTextTime = 3;
	cursorRect = Rect();

	//���I������
	{
		obj = new Sprite *[n];
		objpos = new Vec2[n];
		flg = new int[n];
		objRect = new Rect[n];
		spFlg = new int[n];
		spobjFlg = new bool[n];
	}

	//����
	srand(time(NULL));
}
PlayScene::~PlayScene()
{
	
}
Scene* PlayScene::createScene()
{
	//Scene�쐬
	Scene *scene{ Scene::create() };
	Layer *layer{ PlayScene::create() };
	scene->addChild(layer);
	return scene;
}
bool PlayScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//�ŏ��̃I�u�W�F�N�g�ݒ�
	while (i<n)
	{
		//�I�u�W�F�N�g�ݒ�
		SetObj();
		i++;
	}

	//�g�p�㏉����
	i = 0;

	//�o�b�N�O���E���h�\��
	{
		backGround = Sprite::create("images/bk.png");
		backGround->setPosition(Vec2(DisplaySize.width/2,DisplaySize.height/2));
		this->addChild(backGround,0);
	}

	//�J�[�\��(basket)�\��
	{
		cursor = Sprite::create("images/basket.png");
		cursor->setPosition(DisplaySize.width / 2, DisplaySize.height / 10);
		this->addChild(cursor,2);
	}

	//�X�R�A�\��
	{
		scoreText = Label::createWithSystemFont("SCORE " + StringUtils::toString(score), "fonts/AdobeHeitiStd-Regular.otf", 30);
		scoreText->setPosition(DisplaySize.width - 100, DisplaySize.height - 20);
		scoreText->setColor(Color3B::BLACK);
		this->addChild(scoreText,3);
	}

	input();
	this->scheduleUpdate();
	return true;
}
void PlayScene::update(float dt)
{
	//�t�F�[�h���̑҂�����
	startTextTime -= dt;

	//�I�u�W�F�N�g�̓���͒�~
	if (textTimeFlg==false)
	{
		//�t�F�[�h���I��������\��
		if (startTextTime<=0)
		{
				startTimeText = Label::createWithSystemFont(StringUtils::toString((int)startTime), "fonts/AdobeHeitiStd-Regular.otf", 30);
				startTimeText->setPosition(DisplaySize.width / 2, DisplaySize.height / 2);
				startTimeText->setColor(Color3B::BLACK);
				this->addChild(startTimeText);
				textTimeFlg = true;
		}
	}
	else
	{
		//�J�n���Ԃ̕b�������炷
		startTime -= dt;
		if (startTime <= 1)
		{
			//0�ɂȂ��������
			if (timeFlg == false)
			{
				startTimeText->removeFromParent();
				timeFlg = true;
			}

			//�J�[�\���͈͎̔擾
			cursorRect = Rect(cursor->getPositionX() - 25, cursor->getPositionY() + (cursor->getPositionY() / 2), 50, 1);

			//�I�u�W�F�N�g�̊Ď�
			while (i<n)
			{
				//�I�u�W�F�N�g�͈͎̔擾
				objRect[i] = obj[i]->getBoundingBox();

				//�Փ˔���
				if (objRect[i].intersectsRect(cursorRect))
				{
					//�{�[���̏ꍇ
					if (flg[i] == 1)
					{
						//�X�R�A��
						score = score + 5;

						//������������X�s�[�h�ύX
						if (score>30)
						{
							speedFlg = true;
						}

						//�X�R�A�\���X�V
						scoreText->setString("SCORE " + StringUtils::toString(score));

						//���x���A�b�v�J�E���g
						cnt++;

						//���������̃G�t�F�N�g
						anime = Sprite::create("images/star0000.png");
						anime->setPosition(obj[i]->getPosition());
						this->addChild(anime);
						anim = Animation::create();
						anim->addSpriteFrameWithFileName("images/star0001.png");
						anim->addSpriteFrameWithFileName("images/star0002.png");
						anim->addSpriteFrameWithFileName("images/star0003.png");
						anim->addSpriteFrameWithFileName("images/star0004.png");
						anim->addSpriteFrameWithFileName("images/star0005.png");
						anim->addSpriteFrameWithFileName("images/star0006.png");
						anim->addSpriteFrameWithFileName("images/star0007.png");
						anim->addSpriteFrameWithFileName("images/star0008.png");
						anim->addSpriteFrameWithFileName("images/star0009.png");
						anim->addSpriteFrameWithFileName("images/star0010.png");
						anim->addSpriteFrameWithFileName("images/star0011.png");
						anim->addSpriteFrameWithFileName("images/star0012.png");
						anim->addSpriteFrameWithFileName("images/star0013.png");
						anim->addSpriteFrameWithFileName("images/star0014.png");
						anim->setDelayPerUnit(0.06f);
						animate = Animate::create(anim);
						remove = RemoveSelf::create(true);
						action = Sequence::create(animate, remove, NULL);
						anime->runAction(action);

						//�I�u�W�F�N�g�̏���
						obj[i]->removeFromParent();

						//�I�u�W�F�N�g�ݒ�
						SetObj();
					}

					//�{�[���ȊO
					else
					{
						//Score�𗘗p�ɂ���
						Score sc;

						//�X�R�A���i�[
						sc.SetScore(score);

						//�V�[���ڍs
						auto transition = TransitionFade::create(3.0f, GameOverScene::createScene());
						Director::getInstance()->replaceScene(transition);
						this->unscheduleUpdate();
					}
				}

				//�������x
				FallObj();

				//��ʊO�ɏo�����蒼��
				if (obj[i]->getPositionY() <= 0)
				{
					obj[i]->removeFromParent();
					SetObj();
				}

				//���x���A�b�v
				if (cnt >= 5)
				{
					i = 0;
					LvUpObj();
					cnt = 0;
				}
				i++;
			}

			//�g�p�㏉����
			i = 0;
		}

		//�J�n���ԍX�V
		else
		{
			startTimeText->setString(StringUtils::toString((int)startTime));
		}
	}
}
void PlayScene::input()
{
	//�}�E�X�C�x���g
	mouseListner = EventListenerMouse::create();
	mouseListner->onMouseMove = [=](Event *event)
	{
		//�}�E�X�J�[�\���C�x���g
		//�J�[�\����Y���Œ�
		mouse = (EventMouse *)event;
		cursor->setPosition(Point(mouse->getCursorX(), DisplaySize.height / 10) / EGL_SCALE);
	};

	//�C�x���g�Ď�
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListner, this);
}
//�I�u�W�F�N�g�ݒ�
void PlayScene::SetObj()
{
	//�����_���ɕύX
	flg[i] = rand() % (3 - 1 + 1) + 1;

	//�{�[���E�������E�r��
	if (flg[i] == 1)
	{
		obj[i] = Sprite::create("images/ball.png");
	}
	else if (flg[i] == 2)
	{
		obj[i] = Sprite::create("images/paper.png");
	}
	else if (flg[i] == 3)
	{
		obj[i] = Sprite::create("images/bin.png");
	}

	//���x���x���ύX�̎��̃t���O�L����
	spobjFlg[i] = true;

	//�����_���Ȉʒu�ɂ���
	obj[i]->setPosition(rand() % (((int)DisplaySize.width - 10) - 10 + 1), DisplaySize.height + 50);
	this->addChild(obj[i],1);
}
//���x���A�b�v��
void PlayScene::LvUpObj()
{
	workflg = new int[n];
	pos = new Vec2[n];
	while (i < n)
	{
		workflg[i] = flg[i];
		pos[i] = obj[i]->getPosition();
		obj[i]->removeFromParent();
		i++;
	}

	//�g�p�㏉����
	i = 0;

	//�I�u�W�F�N�g������
	n++;

	//���I�̉���Ə�����
	{
		delete[]obj;
		delete[]flg;
		delete[]objRect;
		delete[]objpos;
		delete[]spFlg;
		delete[] spobjFlg;

		obj = new Sprite *[n];
		flg = new int[n];
		objRect = new Rect[n];
		objpos = new Vec2[n];
		spFlg = new int[n];
		spobjFlg = new bool[n];
	}

	while (i<n)
	{
		//�Ō�
		if (i>=n-1)
		{
			//�I�u�W�F�N�g�ݒ�
			SetObj();
		}
		//�Ō�ȊO �I�u�W�F�N�g��ύX�����Ȃ�����
		else
		{
			flg[i] = workflg[i];
			if (flg[i] == 1)
			{
				obj[i] = Sprite::create("images/ball.png");

			}
			else if (flg[i] == 2)
			{
				obj[i] = Sprite::create("images/paper.png");

			}
			else if (flg[i] == 3)
			{
				obj[i] = Sprite::create("images/bin.png");

			}

			//���x���x���ύX�̎��̃t���O�L����
			spobjFlg[i] = true;

			//�ʒu�����̈ʒu�Ɠ�����
			obj[i]->setPosition(pos[i]);
			this->addChild(obj[i],1);
		}
		i++;
	}

	//�g�p�㏉����
	i = 0;

	//���I(work)�̉��
	{
		delete[]workflg;
		delete[]pos;
	}
}
//�������x
void PlayScene::FallObj()
{
	objpos[i] = obj[i]->getPosition();

	//�ŏ��̑��x
	if (speedFlg==false)
	{
		objpos[i].y -= 3;

	}

	//���x���x���ύX��
	else
	{
		//���x���x���𗐐��ŐU�蕪��
		if (spobjFlg[i] == true)
		{
			spFlg[i] = rand() % (3 - 1 + 1) + 1;
		}
		if (spFlg[i] == 1)
		{
			objpos[i].y -= 2;
		}
		else if (spFlg[i] == 2)
		{
			objpos[i].y -= 5;
		}
		else if (spFlg[i] == 3)
		{
			objpos[i].y -= 1;
		}

		//��ʊO�ɏo��܂ő��x���x����ύX���Ȃ�
		spobjFlg[i] = false;
	}

	//������̈ʒu���i�[
	obj[i]->setPosition(objpos[i]);
}