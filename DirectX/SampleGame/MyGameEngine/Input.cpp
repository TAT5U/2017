/*2017-07-19
	��� �B��
		���͑��u���͂Ȃǂ̃v���O�������L�q����Input�v���O����*/

/****�C���N���[�h****/
#include "Input.h"
/********************/


//�R���X�g���N�^
Input::Input()
{
	//�ϐ��̏�����
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

//�f�X�g���N�^
Input::~Input()
{
	//�J������
	_pKeyDevice->Release();
	_pMouseDevice->Release();
	//_pDInput->Release();
}

//����������
//�E�B���h�E�n���h�����g�p���邽�߈����ŃE�B���h�E�n���h�����擾����
void Input::Init(HWND hWnd)
{
	//DirectInput�{�̂��쐬���A�A�h���X������
	DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID **)&_pDInput, NULL);

	//�L�[�{�[�h�̃f�o�C�X�I�u�W�F�N�g�쐬
	_pDInput->CreateDevice(GUID_SysKeyboard, &_pKeyDevice, NULL);

	//�f�o�C�X�̎��(�L�[�{�[�h)��ݒ�
	_pKeyDevice->SetDataFormat(&c_dfDIKeyboard);

	//���s���Ă���A�v���ɑ΂���D��x��ݒ�
	_pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);



	//�}�E�X�̃f�o�C�X�I�u�W�F�N�g�쐬
	_pDInput->CreateDevice(GUID_SysMouse, &_pMouseDevice, NULL);

	//�f�o�C�X�̎��(�}�E�X)��ݒ�
	_pMouseDevice->SetDataFormat(&c_dfDIMouse2);

	//���s���Ă���A�v���ɑ΂���D��x��ݒ�
	_pMouseDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
}

//�X�V����
void Input::Update()
{
	//�L�[�̏�Ԃ��擾���āA
	//_keyState�̔z��Ɋi�[����
	_pKeyDevice->Acquire();

	//�L�[�̏����R�s�[
	memcpy(_prevKeyState, _keyState, sizeof(_keyState));
	_pKeyDevice->GetDeviceState(sizeof(_keyState), &_keyState);


	//�}�E�X�̃N���b�N�̏����擾����
	//_mouseState�̔z��Ɋi�[����
	_pMouseDevice->Acquire();
	_pMouseDevice->GetDeviceState(sizeof(_mouseState), &_mouseState);

	//�R���g���[���[�̏�Ԃ�_controllerState�Ɋi�[
	XInputGetState(0, &_controllerState);

	//�o�C�u���[�V�����̃X�s�[�h���i�[
	vib.wLeftMotorSpeed = _speed;
	vib.wRightMotorSpeed = _speed;

	//�o�C�u���[�V�����̐ݒ�
	XInputSetState(0, &vib);
}

//�����ꂽ�L�[�̔���
bool Input::IsKeyPush(int keyCode)
{
	//�L�[ & 0x80�ŉ����ꂽ���ǂ����̔���
	if (_keyState[keyCode] & 0x80)
	{
		return true;
	}
	return false;
}

//�����ꂽ"��"�̃L�[�̔���
bool Input::IsKeyTap(int keyCode)
{
	//�L�[ & 0x80 && !�L�[ & 0x80�ŉ����ꂽ�Ƃ��̔���
	if ((_keyState[keyCode] & 0x80) && !(_prevKeyState[keyCode] & 0x80))
	{
		return true;
	}
	return false;
}

//���������̃L�[�̔���
bool Input::IsKeyRelease(int keyCode)
{
	//�����ꂽ�Ƃ��̔���̋t
	if (!(_keyState[keyCode] & 0x80) && (_prevKeyState[keyCode] & 0x80))
	{
		return true;
	}
	return false;
}

//�}�E�X�������ꂽ���̔���
bool Input::IsMousePush(int buttonCode)
{
	//�}�E�X�̏�� & 0x80�Ŕ���
	//0 : ���N���b�N
	//1 : �E�N���b�N
	//2 : �z�C�[��
	if (_mouseState.rgbButtons[buttonCode] & 0x80)
	{
		return true;
	}
	return false;
}

//�R���g���[���̓��͔���
bool Input::IsControllerInputState(int controllerCode)
{
	if (_controllerState.Gamepad.wButtons & controllerCode)
	{
		return true;
	}
	return false;
}

//�}�E�X�̓���̏����擾
DIMOUSESTATE2 Input::GetMouseState()
{
	return _mouseState;
}

//�o�C�u���[�V�����̃X�s�[�h���擾
int Input::GetVibrationSpeed()
{
	return _speed;
}

//�o�C�u���[�V�������Z�b�g
void Input::SetVibrationSpeed(int speed)
{
	_speed = speed;
}