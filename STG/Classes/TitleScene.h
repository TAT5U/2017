#pragma once

//�C���N���[�h
#include "cocos2d.h"

//namespace
USING_NS_CC;

//�~�~�V�[���N���X
class TitleScene :public Layer
{
protected:
	TitleScene();                       //�R���X�g���N�^
	virtual ~TitleScene();              //�f�X�g���N�^
	bool init() override;           //�������i�V�[���̍ŏ��ɂ�邱�Ɓj
	void update(float dt) override; //�X�V�i��ɂ�邱�Ɓj
	void input();                   //���͏���


									//�����o��ǉ�����ꍇ�͈ȉ��ɏ���

	float DisplaySizeWidth;
	float DisplaySizeHeight;




public:
	static Scene* createScene();    //�V�[���쐬
	CREATE_FUNC(TitleScene);            //����ƴݽ�ݽ�׸�
};