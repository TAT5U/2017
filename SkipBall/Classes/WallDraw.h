/*WallDraw.h*/

#pragma once
#include "cocos2d.h"

USING_NS_CC;
class WallDraw : public Layer
{
public:
	WallDraw();
	~WallDraw();
	virtual bool init();

	//�X�v���C�g ��
	Sprite *WallUp, *WallRight, *WallLeft;

	//�����G���W�� ��E�E�E���̕�
	PhysicsBody *WUPhysic, *WRPhysic, *WLPhysic;

	//�E�B���h�E�T�C�Y
	Size DisplaySize;

	CREATE_FUNC(WallDraw);
};