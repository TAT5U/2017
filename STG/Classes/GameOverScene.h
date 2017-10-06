#pragma once

//インクルード
#include "cocos2d.h"

//namespace
USING_NS_CC;

//××シーンクラス
class GameOverScene :public Layer
{
protected:
	GameOverScene();                       //コンストラクタ
	virtual ~GameOverScene();              //デストラクタ
	bool init() override;           //初期化（シーンの最初にやること）
	void update(float dt) override; //更新（常にやること）
	void input();                   //入力処理


									//メンバを追加する場合は以下に書く
	float DisplaySizeWidth;
	float DisplaySizeHeight;

public:
	static Scene* createScene();    //シーン作成
	CREATE_FUNC(GameOverScene);            //ｺﾝﾋﾞﾆｴﾝｽｺﾝｽﾄﾗｸﾀ
};