/*Main.cpp*/

/*2017-06-06
	���B��
		Windows�̃E�B���h�E�̕\�����s��*/


/*****�C���N���[�h*****/
#include "Global.h"
#include "Game.h"
/**********************/


/**************�����J**************/
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
/**********************************/


//�萔�錾
//�E�B���h�E�N���X��	const�ŕύX�s�ɂ���
//LPCSTR�ŕ������p�^
const LPCSTR WIN_CLASS_NAME = "Sample";


//�v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

/********************�O���[�o���ϐ�********************/
//�O���錾�����I�u�W�F�N�g��錾���邱�Ƃ�
//���̂Ƃ���ł��O���[�o���N���X���g����悤�ɂȂ�
//�O���[�o���N���X
Global g;

//�Q�[���I�u�W�F�N�g
Game *pGame;
/******************************************************/




/****���������[�N�����o���邽�߂Ƀf�o�b�O�@�\�Ȃǂ�ݒ�****/
#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>
#include<crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
/**********************************************************/

//�G���g���[�|�C���g
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{


/*********************���������[�N�����o���ďo��*********************/
#if _DEBUG
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
/********************************************************************/




	//�E�B���h�E�N���X�̍쐬
	WNDCLASSEX wc;

	//�쐬�����E�B���h�E�N���X�̏��
	//�\���̂̃T�C�Y
	wc.cbSize = sizeof(WNDCLASSEX);

	//�C���X�^���X�n���h��
	wc.hInstance = hInstance;

	//�E�B���h�E�N���X��
	wc.lpszClassName = WIN_CLASS_NAME;

	//�E�B���h�E�v���V�[�W��
	wc.lpfnWndProc = WndProc;

	//�E�B���h�E�X�^�C��(�f�t�H���g)
	wc.style = CS_VREDRAW | CS_HREDRAW;

	//�A�C�R��
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	//�������A�C�R��
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	//�}�E�X�J�[�\��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	//���j���[(�Ȃ�)
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	//�w�i(��)
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	//�쐬�����N���X��o�^
	RegisterClassEx(&wc);

	//�E�B���h�E�T�C�Y�̌v�Z(�g�̓�������)
	RECT winRect = { 0, 0, g.WINDOW_WIDTH, g.WINDOW_HEIGHT };

	//�T�C�Y(RECT),�E�B���h�E�X�^�C��,���j���[�o�[�̗L��
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�̕����i�[
	int winW = winRect.right - winRect.left;

	//�E�B���h�E�̍������i�[
	int winH = winRect.bottom - winRect.top;

	//�E�B���h�E�쐬
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,			//�E�B���h�E�N���X��
		"Sample",		//�^�C�g���o�[�̓��e
		WS_OVERLAPPEDWINDOW,	//�X�^�C��(���ʂ̃E�B���h�E)
		CW_USEDEFAULT,			//�\���ʒu��(���܂���)
		CW_USEDEFAULT,			//�\���ʒu��(���܂���)
		winW,					//�E�B���h�E��
		winH,					//�E�B���h�E����
		NULL,					//�e�E�B���h�E(�Ȃ�)
		NULL,					//���j���[
		hInstance,				//�C���X�^���X
		NULL					//�p�����[�^(�Ȃ�)
		);

	//�E�B���h�E�\��
	ShowWindow(hWnd, nCmdShow);

	//�Q�[���I�u�W�F�N�g�쐬
	pGame = new Game;

	//�Q�[��(DirectX)�̏�����
	// �G���[���o���炻���ŏI��������
	if (FAILED(pGame->Init(hWnd)))
	{
		return 0;
	}


	//���b�Z�[�W���[�v
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//���b�Z�[�W����
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//���b�Z�[�W�Ȃ�
		else
		{
			//�Q�[���̏���
			//���͏���
			pGame->Input();

			//�X�V����
			pGame->Update();

			//��ʕ\��
			pGame->Draw();
		}
	}

	//DirectX�J������
	delete pGame;

	return 0;
}

//�E�B���h�E�v���V�[�W��(�����������Ƃ��ɌĂяo�����)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//����ȊO�ŏI���������ꍇ�Ƀt���O��ς��邱�Ƃ�
	//�I���������s��
	if (g.GetEndFlg())
	{
		PostQuitMessage(0);
		return 0;
	}

	switch (msg)
	{
	case WM_MOUSEMOVE:
		g.pInput->SetMousePos(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_DESTROY:
		//�v���O�����I��
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}