#include "Input.h"

#define SAFE_RELEASE(X) if(X){ X->Release(); X = nullptr;}

Input::Input()
{
	_pKeyDevice = nullptr;
	ZeroMemory(_keyState, sizeof(_keyState));
	ZeroMemory(_prevKeyState, sizeof(_prevKeyState));

	_pMouseDevice = nullptr;
	ZeroMemory(&_mouseState, sizeof(_mouseState));
	ZeroMemory(&_prevMouseState, sizeof(_prevMouseState));
	_mousePosition.x = _mousePosition.y = 0;

	ZeroMemory(_controllerState, sizeof(_controllerState));
	ZeroMemory(_prevControllerState, sizeof(_prevControllerState));
}


Input::~Input()
{
	SAFE_RELEASE(_pKeyDevice);
	SAFE_RELEASE(_pMouseDevice);
	SAFE_RELEASE(_pDInput);
}


void Input::Init(HWND hWnd)
{
	DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION,
		IID_IDirectInput8, (VOID**)&_pDInput, NULL);

	//キーボード
	_pDInput->CreateDevice(GUID_SysKeyboard, &_pKeyDevice, NULL);
	_pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
	_pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

	//マウス
	_pDInput->CreateDevice(GUID_SysMouse, &_pMouseDevice, NULL);
	_pMouseDevice->SetDataFormat(&c_dfDIMouse2);
	_pMouseDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
}


void Input::Update()
{
	//キーボード
	_pKeyDevice->Acquire();
	memcpy(_prevKeyState, _keyState, sizeof(_keyState));
	_pKeyDevice->GetDeviceState(sizeof(_keyState), &_keyState);

	//マウス
	_pMouseDevice->Acquire();
	memcpy(&_prevMouseState, &_mouseState, sizeof(_mouseState));
	_pMouseDevice->GetDeviceState(sizeof(_mouseState), &_mouseState);

	//コントローラー
	for (int i = 0; i < MAX_CONTROLLER_NUM; i++)
	{
		memcpy(&_prevControllerState, &_controllerState, sizeof(_controllerState));
		XInputGetState(i, &_controllerState[i]);
	}
}




/////////////////////////////////////////キーボード///////////////////////////////////////////
BOOL Input::IsKeyPush(int keyCode)
{
	if (_keyState[keyCode] & 0x80)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL Input::IsKeyTap(int keyCode)
{
	if (IsKeyPush(keyCode) && (_prevKeyState[keyCode] & 0x80) == 0)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL Input::IsKeyRelease(int keyCode)
{
	if (!IsKeyPush(keyCode) && _prevKeyState[keyCode] & 0x80)
	{
		return TRUE;
	}
	return FALSE;
}




/////////////////////////////////////////マウス///////////////////////////////////////////
BOOL Input::IsMousePush(int buttonCode)
{
	if (_mouseState.rgbButtons[buttonCode] & 0x80)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL Input::IsMouseTap(int buttonCode)
{
	if (IsMousePush(buttonCode) && _prevMouseState.rgbButtons[buttonCode] & 0x80 == 0)
	{
		return TRUE;
	}
	return FALSE;
}


BOOL Input::IsMouseRelease(int buttonCode)
{
	if (!IsMousePush(buttonCode) && _prevMouseState.rgbButtons[buttonCode] & 0x80)
	{
		return TRUE;
	}
	return FALSE;
}



FLOAT Input::GetMouseX()
{
	return _mouseState.lX;
}

FLOAT Input::GetMouseY()
{
	return _mouseState.lY;
}

FLOAT Input::GetMouseWheel()
{
	return _mouseState.lZ;
}

void Input::SetMousePosition(int x, int y)
{
	_mousePosition.x = x;
	_mousePosition.y = y;
}

POINT Input::GetMousePosition()
{
	return _mousePosition;
}


/////////////////////////////////////////コントローラー///////////////////////////////////////////
BOOL Input::IsPadPush(int buttonCode, int padID)
{
	if (_controllerState[padID].Gamepad.wButtons & buttonCode)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL Input::IsPadTap(int buttonCode, int padID)
{
	if (IsPadPush(buttonCode, padID) && _prevControllerState[padID].Gamepad.wButtons & buttonCode == 0)
	{
		return TRUE;
	}
	return FALSE;
}


BOOL Input::IsPadRelease(int buttonCode, int padID)
{
	if (!IsPadPush(buttonCode, padID) && _prevControllerState[padID].Gamepad.wButtons & buttonCode)
	{
		return TRUE;
	}
	return FALSE;
}



float Input::GetStick(STICK_ID stickID, int padID)
{
	float v = 0.0f;
	switch (stickID)
	{
	case THUMB_LX: v = _controllerState[padID].Gamepad.sThumbLX; break;
	case THUMB_LY: v = _controllerState[padID].Gamepad.sThumbLY; break;
	case THUMB_RX: v = _controllerState[padID].Gamepad.sThumbRX; break;
	case THUMB_RY: v = _controllerState[padID].Gamepad.sThumbRY; break;
	}


	//デッドゾーンを切り捨てて、値を-1～1にする
	switch (stickID)
	{
	case THUMB_LX:
	case THUMB_LY:
		if (v > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && v < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			v = 0.0f;
		}
		else
		{
			if (v > 0)
				v = (v - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
			else
				v = (v + XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) / (32768 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		}

		break;

	case THUMB_RX:
	case THUMB_RY:
		if (v > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && v < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			v = 0.0f;
		}
		else
		{
			if (v > 0)
				v = (v - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) / (32767 - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
			else
				v = (v + XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) / (32768 - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
		}
		break;
	}

	return v;
}



float Input::GetTrigger(TRIGGER_ID triggerID, int padID)
{
	float v = 0.0f;

	switch (triggerID)
	{
	case LEFT_TRIGGER:	v = _controllerState[padID].Gamepad.bLeftTrigger;	break;
	case RIGHT_TRIGGER:	v = _controllerState[padID].Gamepad.bRightTrigger;	break;
	}

	if (v > -XINPUT_GAMEPAD_TRIGGER_THRESHOLD && v < XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
	{
		v = 0.0f;
	}
	else
	{
		v = (v - XINPUT_GAMEPAD_TRIGGER_THRESHOLD) / (255 - XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
	}

	return v;
}


void Input::Vibration(float leftPower, float rightPower, int padID)
{
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	vibration.wLeftMotorSpeed = leftPower * 65535;
	vibration.wRightMotorSpeed = rightPower * 65535;
	XInputSetState(padID, &vibration);
}