/*PlayScene.cpp*/

/*2017-06-16
	狩野 達哉
		プレイシーンのプログラム*/

/****インクルード****/
#include "PlayScene.h"
/********************/


//コンストラクタ
PlayScene::PlayScene()
{
	//変数の初期化
	_sprite = nullptr;
	_label = nullptr;
	_spriteFlg = false;
}

//デストラクタ
PlayScene::~PlayScene()
{

}

//初期化処理
void PlayScene::Init()
{
	//画像の表示
	{
		auto sprite = Sprite::Create("Assets//aa.png");
		sprite->SetScale(0.5, 0.5);
		sprite->SetPosition(-300, 300);
		AddChild(sprite);
		_sprite = sprite;
	}

	/*
	//画像の表示
	{
	Sprite *sprite = Sprite::Create("Assets//jag.png");
	this->AddChild(sprite);
	}

	//画像の表示(範囲・アンカーポイント・位置指定)
	{
	Sprite *sprite2 = Sprite::Create("Assets//jag.png", MyRect(100, 100, 200, 200));
	sprite2->SetAnchorPoint(0, 0);
	sprite2->SetPosition(100, 100);
	this->AddChild(sprite2);
	}
	*/

	//ラベルの表示
	{
		auto label = Label::Create("てすとぉぉぉ", "MS ゴシック", 20);
		label->SetPosition(600, 300);
		label->SetString("こんばんは！！");
		AddChild(label);
		_label = label;
	}
}

//更新処理
void PlayScene::Update()
{
	if (_spriteFlg == false)
	{
		//スプライトの位置を取得して右にずらしてセットし、
		//スプライトが動いているように見せる
		D3DXVECTOR3 spritePos = _sprite->GetPosition();
		spritePos += D3DXVECTOR3(2, 0, 0);
		_sprite->SetPosition(spritePos.x, spritePos.y);

		/**********************当たり判定**********************/
		MyRect rectSprite = _sprite->GetBoundingBox();
		MyRect rectLabel = _label->GetBoundingBox();

		//ノードとノード
		if (rectSprite.IntersectsRect(rectLabel))
		{
			//当たったとき
			_label->SetString("衝突!!");
		}

		//ノードと点
		if (rectSprite.ContainsPoint(_label->GetPosition()))
		{
			//当たったとき
			_label->SetString("点で衝突!!");
		}
		/******************************************************/


		//押されたキーの判定
		if (g.pInput->IsKeyPush(DIK_A))
		{
			_sprite->RemoveFromParent();
			_spriteFlg = true;
			//g.ReplaceScene(new ClearScene);
		}

		////押された"時"のキーの判定
		//if (g.pInput->IsKeyTap(DIK_A))
		//{
		//	g.ReplaceScene(new ClearScene);
		//}

		////離した時のキーの判定
		//if (g.pInput->IsKeyRelease(DIK_A))
		//{
		//	g.ReplaceScene(new ClearScene);
		//}

		//マウスが押された時の判定
		if (g.pInput->IsMousePush(0))
		{
			_label->SetString("左クリック!!!!");
		}

		//コントローラのAが押されたときの判定
		if (g.pInput->IsControllerInputState(XINPUT_GAMEPAD_A))
		{
			//バイブレーションがONならば0にする
			//OFFならば最大の65535にする
			if (g.pInput->GetVibrationSpeed() != 0)
			{
				g.pInput->SetVibrationSpeed(0);
			}
			else
			{
				g.pInput->SetVibrationSpeed(65535);
			}
		}
	}



}

//入力処理
void PlayScene::Input()
{

}