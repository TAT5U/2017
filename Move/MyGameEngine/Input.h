#pragma once

#include <dInput.h>
#include "XInput.h"


#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")
#pragma comment(lib,"Xinput.lib")


#define MAX_CONTROLLER_NUM	4	//コントローラーの最大接続数


//スティックの識別
enum STICK_ID
{
	THUMB_LX,	//左スティックの横方向
	THUMB_LY,	//左スティックの縦方向
	THUMB_RX,	//右スティックの横方向
	THUMB_RY,	//右スティックの縦方向
};

//トリガーの識別
enum TRIGGER_ID
{
	LEFT_TRIGGER,	//左トリガー
	RIGHT_TRIGGER	//右トリガー
};



class Input
{
	LPDIRECTINPUT8 _pDInput;

	LPDIRECTINPUTDEVICE8 _pKeyDevice;
	BYTE _keyState[256];
	BYTE _prevKeyState[256];

	LPDIRECTINPUTDEVICE8 _pMouseDevice;
	DIMOUSESTATE2 _mouseState;
	DIMOUSESTATE2 _prevMouseState;
	POINT _mousePosition;

	XINPUT_STATE _controllerState[MAX_CONTROLLER_NUM];
	XINPUT_STATE _prevControllerState[MAX_CONTROLLER_NUM];

public:
	Input();
	~Input();

	void Init(HWND hWnd);
	void Update();


	//キーボード
	BOOL IsKeyPush(int keyCode);
	BOOL IsKeyTap(int keyCode);
	BOOL IsKeyRelease(int keyCode);

	//マウス
	BOOL IsMousePush(int buttonCode);
	BOOL IsMouseTap(int buttonCode);
	BOOL IsMouseRelease(int buttonCode);
	FLOAT GetMouseX();
	FLOAT GetMouseY();
	FLOAT GetMouseWheel();
	void SetMousePosition(int x, int y);
	POINT GetMousePosition();


	//機能：コントローラーのボタンを押しているか
	//引数：buttonCode　調べたいボタン（XINPUT_GAMEPAD_Aなど）
	//引数：padID		コントローラーの番号（省略すれば0）
	//戻値：押していればTRUE
	BOOL IsPadPush(int buttonCode, int padID = 0);

	//機能：コントローラーのボタンを押した瞬間か
	//引数：buttonCode　調べたいボタン（XINPUT_GAMEPAD_Aなど）
	//引数：padID		コントローラーの番号（省略すれば0）
	//戻値：押した瞬間ならTRUE
	BOOL IsPadTap(int buttonCode, int padID = 0);

	//機能：コントローラーのボタンを離した瞬間か
	//引数：buttonCode　調べたいボタン（XINPUT_GAMEPAD_Aなど）
	//引数：padID		コントローラーの番号（省略すれば0）
	//戻値：離した瞬間ならTRUE
	BOOL IsPadRelease(int buttonCode, int padID = 0);

	//機能：コントローラーのスティックの傾き具合を取得
	//引数：stickID　	スティックの識別（THUMB_LXなど）
	//引数：padID		コントローラーの番号（省略すれば0）
	//戻値：傾き具合（-1 ～ 1）
	float GetStick(STICK_ID stickID, int padID = 0);

	//機能：コントローラーのトリガーの押し込み具合を取得
	//引数：triggerID　	トリガーの識別（LEFT_TRIGGERなど）
	//引数：padID		コントローラーの番号（省略すれば0）
	//戻値：押し具合（0 ～ 1）
	float GetTrigger(TRIGGER_ID triggerID, int padID = 0);

	//機能：コントローラーを振動させる
	//引数：leftPower　	左モーターの振動の強さ（0～1）
	//引数：rightPower　右モーターの振動の強さ（0～1）
	//引数：padID		コントローラーの番号（省略すれば0）
	//戻値：なし
	void Vibration(float leftPower, float rightPower, int padID = 0);

};