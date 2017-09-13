/*2017-07-19
	狩野 達哉
		入力装置入力などのプログラムを記述するInputプログラム*/

/****インクルード****/
#include "Input.h"
/********************/


//コンストラクタ
Input::Input()
{
	//変数の初期化
	_pDInput = nullptr;
	_pKeyDevice = nullptr;
	_pMouseDevice = nullptr;
	_mouseState = DIMOUSESTATE2();
	ZeroMemory(_keyState, 256);
	ZeroMemory(_prevKeyState, 256);
	ZeroMemory(&vib, sizeof(_XINPUT_VIBRATION));
	_controllerState = XINPUT_STATE();
	_speed = 0;
}

//デストラクタ
Input::~Input()
{
	//開放処理
	_pKeyDevice->Release();
	_pMouseDevice->Release();
	//_pDInput->Release();
}

//初期化処理
//ウィンドウハンドルを使用するため引数でウィンドウハンドルを取得する
void Input::Init(HWND hWnd)
{
	//DirectInput本体を作成し、アドレスを入れる
	DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID **)&_pDInput, NULL);

	//キーボードのデバイスオブジェクト作成
	_pDInput->CreateDevice(GUID_SysKeyboard, &_pKeyDevice, NULL);

	//デバイスの種類(キーボード)を設定
	_pKeyDevice->SetDataFormat(&c_dfDIKeyboard);

	//実行しているアプリに対する優先度を設定
	_pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);



	//マウスのデバイスオブジェクト作成
	_pDInput->CreateDevice(GUID_SysMouse, &_pMouseDevice, NULL);

	//デバイスの種類(マウス)を設定
	_pMouseDevice->SetDataFormat(&c_dfDIMouse2);

	//実行しているアプリに対する優先度を設定
	_pMouseDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
}

//更新処理
void Input::Update()
{
	//キーの状態を取得して、
	//_keyStateの配列に格納する
	_pKeyDevice->Acquire();

	//キーの情報をコピー
	memcpy(_prevKeyState, _keyState, sizeof(_keyState));
	_pKeyDevice->GetDeviceState(sizeof(_keyState), &_keyState);


	//マウスのクリックの情報を取得して
	//_mouseStateの配列に格納する
	_pMouseDevice->Acquire();
	_pMouseDevice->GetDeviceState(sizeof(_mouseState), &_mouseState);

	//コントローラーの状態を_controllerStateに格納
	XInputGetState(0, &_controllerState);

	//バイブレーションのスピードを格納
	vib.wLeftMotorSpeed = _speed;
	vib.wRightMotorSpeed = _speed;

	//バイブレーションの設定
	XInputSetState(0, &vib);
}

//押されたキーの判定
bool Input::IsKeyPush(int keyCode)
{
	//キー & 0x80で押されたかどうかの判定
	if (_keyState[keyCode] & 0x80)
	{
		return true;
	}
	return false;
}

//押された"時"のキーの判定
bool Input::IsKeyTap(int keyCode)
{
	//キー & 0x80 && !キー & 0x80で押されたときの判定
	if ((_keyState[keyCode] & 0x80) && !(_prevKeyState[keyCode] & 0x80))
	{
		return true;
	}
	return false;
}

//離した時のキーの判定
bool Input::IsKeyRelease(int keyCode)
{
	//押されたときの判定の逆
	if (!(_keyState[keyCode] & 0x80) && (_prevKeyState[keyCode] & 0x80))
	{
		return true;
	}
	return false;
}

//マウスが押された時の判定
bool Input::IsMousePush(int buttonCode)
{
	//マウスの情報 & 0x80で判定
	//0 : 左クリック
	//1 : 右クリック
	//2 : ホイール
	if (_mouseState.rgbButtons[buttonCode] & 0x80)
	{
		return true;
	}
	return false;
}

//コントローラの入力判定
bool Input::IsControllerInputState(int controllerCode)
{
	if (_controllerState.Gamepad.wButtons & controllerCode)
	{
		return true;
	}
	return false;
}

//マウスの動作の情報を取得
DIMOUSESTATE2 Input::GetMouseState()
{
	return _mouseState;
}

//バイブレーションのスピードを取得
int Input::GetVibrationSpeed()
{
	return _speed;
}

//バイブレーションをセット
void Input::SetVibrationSpeed(int speed)
{
	_speed = speed;
}