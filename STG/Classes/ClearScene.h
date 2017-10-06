#pragma once

//�C���N���[�h
#include "cocos2d.h"

//namespace
USING_NS_CC;

//�~�~�V�[���N���X
class ClearScene :public Layer
{
protected:
	ClearScene();                       //�R���X�g���N�^
	virtual ~ClearScene();              //�f�X�g���N�^
	bool init() override;           //�������i�V�[���̍ŏ��ɂ�邱�Ɓj
	void update(float dt) override; //�X�V�i��ɂ�邱�Ɓj
	void input();                   //���͏���



	//�����o��ǉ�����ꍇ�͈ȉ��ɏ���
	float DisplaySizeWidth;
	float DisplaySizeHeight;
	Label* _clbl;

public:
	static Scene* createScene();    //�V�[���쐬
	CREATE_FUNC(ClearScene);            //����ƴݽ�ݽ�׸�
};