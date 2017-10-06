#pragma once

//�C���N���[�h
#include "cocos2d.h"

//namespace
USING_NS_CC;

//�~�~�V�[���N���X
class PlayScene :public Layer
{
protected:
	PlayScene();                       //�R���X�g���N�^
	virtual ~PlayScene();              //�f�X�g���N�^
	bool init() override;           //�������i�V�[���̍ŏ��ɂ�邱�Ɓj
	void update(float dt) override; //�X�V�i��ɂ�邱�Ɓj
	void input();                   //���͏���


	//�����o��ǉ�����ꍇ�͈ȉ��ɏ���
	Sprite* _Player;
	Sprite* _bullet;
	Sprite* _cursor;
	Sprite* _enemy[5];
	float DisplaySizeWidth;
	float DisplaySizeHeight;
	int cursorY;
	int EnemyFlgposX[3];
	int EnemyFlgposY[3];
	int i;
	bool _isEnemyDead[3];
	int EnemyCount;
	int EnemyDeadCount;
	Label* secondText;
	Label* startTimeText;
	bool startTimeTextflg;

	CC_SYNTHESIZE(float, _second, Second);
	CC_SYNTHESIZE(float, _startTime, StartTime);
	//CC_SYNTHESIZE_RETAIN(cocos2d::Label*, _secondLabel, SecondLabel);
//	CC_SYNTHESIZE_RETAIN(cocos2d::Label*, _startTimeLabel, StartTimeLabel);


public:
	static Scene* createScene();    //�V�[���쐬
	CREATE_FUNC(PlayScene);            //����ƴݽ�ݽ�׸�
};