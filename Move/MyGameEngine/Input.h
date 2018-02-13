#pragma once

#include <dInput.h>
#include "XInput.h"


#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")
#pragma comment(lib,"Xinput.lib")


#define MAX_CONTROLLER_NUM	4	//�R���g���[���[�̍ő�ڑ���


//�X�e�B�b�N�̎���
enum STICK_ID
{
	THUMB_LX,	//���X�e�B�b�N�̉�����
	THUMB_LY,	//���X�e�B�b�N�̏c����
	THUMB_RX,	//�E�X�e�B�b�N�̉�����
	THUMB_RY,	//�E�X�e�B�b�N�̏c����
};

//�g���K�[�̎���
enum TRIGGER_ID
{
	LEFT_TRIGGER,	//���g���K�[
	RIGHT_TRIGGER	//�E�g���K�[
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


	//�L�[�{�[�h
	BOOL IsKeyPush(int keyCode);
	BOOL IsKeyTap(int keyCode);
	BOOL IsKeyRelease(int keyCode);

	//�}�E�X
	BOOL IsMousePush(int buttonCode);
	BOOL IsMouseTap(int buttonCode);
	BOOL IsMouseRelease(int buttonCode);
	FLOAT GetMouseX();
	FLOAT GetMouseY();
	FLOAT GetMouseWheel();
	void SetMousePosition(int x, int y);
	POINT GetMousePosition();


	//�@�\�F�R���g���[���[�̃{�^���������Ă��邩
	//�����FbuttonCode�@���ׂ����{�^���iXINPUT_GAMEPAD_A�Ȃǁj
	//�����FpadID		�R���g���[���[�̔ԍ��i�ȗ������0�j
	//�ߒl�F�����Ă����TRUE
	BOOL IsPadPush(int buttonCode, int padID = 0);

	//�@�\�F�R���g���[���[�̃{�^�����������u�Ԃ�
	//�����FbuttonCode�@���ׂ����{�^���iXINPUT_GAMEPAD_A�Ȃǁj
	//�����FpadID		�R���g���[���[�̔ԍ��i�ȗ������0�j
	//�ߒl�F�������u�ԂȂ�TRUE
	BOOL IsPadTap(int buttonCode, int padID = 0);

	//�@�\�F�R���g���[���[�̃{�^���𗣂����u�Ԃ�
	//�����FbuttonCode�@���ׂ����{�^���iXINPUT_GAMEPAD_A�Ȃǁj
	//�����FpadID		�R���g���[���[�̔ԍ��i�ȗ������0�j
	//�ߒl�F�������u�ԂȂ�TRUE
	BOOL IsPadRelease(int buttonCode, int padID = 0);

	//�@�\�F�R���g���[���[�̃X�e�B�b�N�̌X������擾
	//�����FstickID�@	�X�e�B�b�N�̎��ʁiTHUMB_LX�Ȃǁj
	//�����FpadID		�R���g���[���[�̔ԍ��i�ȗ������0�j
	//�ߒl�F�X����i-1 �` 1�j
	float GetStick(STICK_ID stickID, int padID = 0);

	//�@�\�F�R���g���[���[�̃g���K�[�̉������݋���擾
	//�����FtriggerID�@	�g���K�[�̎��ʁiLEFT_TRIGGER�Ȃǁj
	//�����FpadID		�R���g���[���[�̔ԍ��i�ȗ������0�j
	//�ߒl�F������i0 �` 1�j
	float GetTrigger(TRIGGER_ID triggerID, int padID = 0);

	//�@�\�F�R���g���[���[��U��������
	//�����FleftPower�@	�����[�^�[�̐U���̋����i0�`1�j
	//�����FrightPower�@�E���[�^�[�̐U���̋����i0�`1�j
	//�����FpadID		�R���g���[���[�̔ԍ��i�ȗ������0�j
	//�ߒl�F�Ȃ�
	void Vibration(float leftPower, float rightPower, int padID = 0);

};