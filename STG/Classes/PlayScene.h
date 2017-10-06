#pragma once

//インクルード
#include "cocos2d.h"

//namespace
USING_NS_CC;

//××シーンクラス
class PlayScene :public Layer
{
protected:
	PlayScene();                       //コンストラクタ
	virtual ~PlayScene();              //デストラクタ
	bool init() override;           //初期化（シーンの最初にやること）
	void update(float dt) override; //更新（常にやること）
	void input();                   //入力処理


	//メンバを追加する場合は以下に書く
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
	static Scene* createScene();    //シーン作成
	CREATE_FUNC(PlayScene);            //ｺﾝﾋﾞﾆｴﾝｽｺﾝｽﾄﾗｸﾀ
};