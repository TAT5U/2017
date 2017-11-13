/*Input.h*/

//インクルードガード
#pragma once

/****インクルード****/
#include <dInput.h>

//Xbox360のコントローラを
//使用可能にするヘッダ
#include "XInput.h"

/********************/


/**************リンカ**************/
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

//Xbox360のコントローラを
//使用可能にするリンカ
#pragma comment(lib,"Xinput.lib")
/**********************************/

struct Point
{
	float pX, pY;
};

//入力装置で入力された時のInputクラス
class Input
{


	//DirectInput
	//DirectXで入力装置の入力を読み取るための変数
	LPDIRECTINPUT8 _pDInput;

	//キーボードデバイスオブジェクト
	LPDIRECTINPUTDEVICE8 _pKeyDevice;

	//マウスデバイスオブジェクト
	LPDIRECTINPUTDEVICE8 _pMouseDevice;

	//押されているキーの情報を格納する変数
	BYTE _keyState[256];

	//前回押されたキーの情報を格納する変数
	BYTE _prevKeyState[256];

	//クリックなどのマウスの動作の情報を格納する変数
	DIMOUSESTATE2 _mouseState;

	DIMOUSESTATE2 _prevMouseState;

	//コントローラーの情報を格納する変数
	XINPUT_STATE _controllerState;

	//コントローラーのバイブレーション
	XINPUT_VIBRATION vib;

	//バイブレーションのスピード
	int _speed;

	Point mousePos;

public:

	//コンストラクタ
	Input();

	//デストラクタ
	~Input();

	//初期化処理
	//ウィンドウハンドルを使用するため引数でウィンドウハンドルを取得する
	//引数->ウィンドウハンドル
	//戻値->なし
	void Init(HWND hWnd);

	//更新処理
	//引数->なし
	//戻値->なし
	void Update();

	//押されたキーの判定
	//引数->キーの情報
	//戻値->判定の結果
	bool IsKeyPush(int keyCode);

	//押された"時"のキーの判定
	//引数->キーの情報
	//戻値->判定の結果
	bool IsKeyTap(int keyCode);

	//離した時のキーの判定
	//引数->キーの情報
	//戻値->判定の結果
	bool IsKeyRelease(int keyCode);

	//マウスが押された時の判定
	//引数->マウスのクリックの情報
	//戻値->判定の結果
	bool IsMousePush(int buttonCode);

	//コントローラの入力判定
	//引数->入力されたコントローラーの情報
	//戻値->判定の結果
	bool IsControllerInputState(int controllerCode);

	/**********************ゲッター**********************/
	//引数->なし

	//マウスの動作の情報を取得
	//戻値->マウスの情報
	DIMOUSESTATE2 GetMouseState();

	//バイブレーションのスピードを取得
	//戻値->バイブレーションのスピード
	int GetVibrationSpeed();
	/****************************************************/


	/***************セッター***************/
	//バイブレーションをセット
	//引数->設定するバイブレーションのスピード
	//戻値->なし
	void SetVibrationSpeed(int speed);

	void SetMousePos(float ptX, float ptY);
	/**************************************/

	/***************ゲッター***************/
	Point GetMousePos();
	/**************************************/
};