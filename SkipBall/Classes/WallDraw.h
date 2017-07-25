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

	//スプライト 壁
	Sprite *WallUp, *WallRight, *WallLeft;

	//物理エンジン 上・右・左の壁
	PhysicsBody *WUPhysic, *WRPhysic, *WLPhysic;

	//ウィンドウサイズ
	Size DisplaySize;

	CREATE_FUNC(WallDraw);
};