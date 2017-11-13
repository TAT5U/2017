/*Input.h*/

//�C���N���[�h�K�[�h
#pragma once

/****�C���N���[�h****/
#include <dInput.h>

//Xbox360�̃R���g���[����
//�g�p�\�ɂ���w�b�_
#include "XInput.h"

/********************/


/**************�����J**************/
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

//Xbox360�̃R���g���[����
//�g�p�\�ɂ��郊���J
#pragma comment(lib,"Xinput.lib")
/**********************************/

struct Point
{
	float pX, pY;
};

//���͑��u�œ��͂��ꂽ����Input�N���X
class Input
{


	//DirectInput
	//DirectX�œ��͑��u�̓��͂�ǂݎ�邽�߂̕ϐ�
	LPDIRECTINPUT8 _pDInput;

	//�L�[�{�[�h�f�o�C�X�I�u�W�F�N�g
	LPDIRECTINPUTDEVICE8 _pKeyDevice;

	//�}�E�X�f�o�C�X�I�u�W�F�N�g
	LPDIRECTINPUTDEVICE8 _pMouseDevice;

	//������Ă���L�[�̏����i�[����ϐ�
	BYTE _keyState[256];

	//�O�񉟂��ꂽ�L�[�̏����i�[����ϐ�
	BYTE _prevKeyState[256];

	//�N���b�N�Ȃǂ̃}�E�X�̓���̏����i�[����ϐ�
	DIMOUSESTATE2 _mouseState;

	DIMOUSESTATE2 _prevMouseState;

	//�R���g���[���[�̏����i�[����ϐ�
	XINPUT_STATE _controllerState;

	//�R���g���[���[�̃o�C�u���[�V����
	XINPUT_VIBRATION vib;

	//�o�C�u���[�V�����̃X�s�[�h
	int _speed;

	Point mousePos;

public:

	//�R���X�g���N�^
	Input();

	//�f�X�g���N�^
	~Input();

	//����������
	//�E�B���h�E�n���h�����g�p���邽�߈����ŃE�B���h�E�n���h�����擾����
	//����->�E�B���h�E�n���h��
	//�ߒl->�Ȃ�
	void Init(HWND hWnd);

	//�X�V����
	//����->�Ȃ�
	//�ߒl->�Ȃ�
	void Update();

	//�����ꂽ�L�[�̔���
	//����->�L�[�̏��
	//�ߒl->����̌���
	bool IsKeyPush(int keyCode);

	//�����ꂽ"��"�̃L�[�̔���
	//����->�L�[�̏��
	//�ߒl->����̌���
	bool IsKeyTap(int keyCode);

	//���������̃L�[�̔���
	//����->�L�[�̏��
	//�ߒl->����̌���
	bool IsKeyRelease(int keyCode);

	//�}�E�X�������ꂽ���̔���
	//����->�}�E�X�̃N���b�N�̏��
	//�ߒl->����̌���
	bool IsMousePush(int buttonCode);

	//�R���g���[���̓��͔���
	//����->���͂��ꂽ�R���g���[���[�̏��
	//�ߒl->����̌���
	bool IsControllerInputState(int controllerCode);

	/**********************�Q�b�^�[**********************/
	//����->�Ȃ�

	//�}�E�X�̓���̏����擾
	//�ߒl->�}�E�X�̏��
	DIMOUSESTATE2 GetMouseState();

	//�o�C�u���[�V�����̃X�s�[�h���擾
	//�ߒl->�o�C�u���[�V�����̃X�s�[�h
	int GetVibrationSpeed();
	/****************************************************/


	/***************�Z�b�^�[***************/
	//�o�C�u���[�V�������Z�b�g
	//����->�ݒ肷��o�C�u���[�V�����̃X�s�[�h
	//�ߒl->�Ȃ�
	void SetVibrationSpeed(int speed);

	void SetMousePos(float ptX, float ptY);
	/**************************************/

	/***************�Q�b�^�[***************/
	Point GetMousePos();
	/**************************************/
};