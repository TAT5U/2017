/*Game.h*/

//インクルードガード
#pragma once

/****インクルード****/
#include "Global.h"
#include "Sprite.h"
#include "Scene.h"
#include "Input.h"
#include "Fade.h"

//シーンのヘッダ
#include "../Sample.h"
/********************/


//ゲーム処理をするためのクラス(描画など)
class Game
{
	//LPは「Long　Pointer」なのでポインタとして扱う
	//Directx3Dオブジェクト
	LPDIRECT3D9 _pD3d;

public:

	//コンストラクタ
	Game();

	//デストラクタ
	~Game();

	//初期化処理
	//Direct3Dデバイスオブジェクトを使用するための引数にウィンドウハンドルを設定
	//引数->ウィンドウハンドル
	//戻値->なし
	HRESULT Init(HWND hWnd);

	//更新処理
	//引数->なし
	//戻値->なし
	void Update();

	//入力処理
	//引数->なし
	//戻値->なし
	void Input();

	//描画処理
	//引数->なし
	//戻値->なし
	void Draw();
};