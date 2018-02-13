#pragma once
#include "Global.h"
#include "Sprite.h"
#include "Scene.h"

class Game
{
	LPDIRECT3D9	_pD3d;	    //Direct3Dオブジェクト
	Scene*     _pScene;


public:
	Game();			//コンストラクタ
	~Game();		//デストラクタ（開放処理）
	HRESULT Init(HWND hWnd);	//初期化処理
	void Update();			//更新処理
	void Input();			//入力処理
	void Draw();			//描画処理
};