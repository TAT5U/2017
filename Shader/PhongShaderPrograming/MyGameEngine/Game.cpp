/*Player.cpp*/

/*2017-06-07
	��� �B��
		�Q�[����ʂ̕`����s��*/

/****�C���N���[�h****/
#include "Game.h"
/********************/


//�R���X�g���N�^
Game::Game()
{
	//�ϐ��̏�����
	_pD3d = nullptr;
	g.pDevice = nullptr;
	g.pScene = nullptr;
	g.pInput = nullptr;
	g.pFade = nullptr;
}

//�f�X�g���N�^
Game::~Game()
{
	//�v���O�����I�����ɂ̓I�u�W�F�N�g�ƃf�o�C�X�I�u�W�F�N�g���������Ȃ���΂Ȃ�Ȃ�
	//�Ȃ̂ŁA�I�����ɉ��������
	//������Ԃ͍쐬�������Ԃ̋t�ŉ�����s��
	//LP�Ŏn�܂�^�̕ϐ���Release�ŉ���ł���
	//�������
	SAFE_DELETE(g.pFade);
	SAFE_DELETE(g.pInput);
	SAFE_DELETE(g.pScene);
	SAFE_RELEASE(g.pDevice);
	SAFE_RELEASE(_pD3d)
}

//����������
HRESULT Game::Init(HWND hWnd)
{
	//Direct3D�I�u�W�F�N�g���쐬
	//DirectX�{�̏���
	_pD3d = Direct3DCreate9(D3D_SDK_VERSION);

	//DIRECT3D�f�o�C�X�I�u�W�F�N�g�̍쐬
	//Direct3D�I�u�W�F�N�g��pDevice���Q�[����ʂɂȂ�ApDevice�ɂ������đ��삪�ł���
	//DIRECT3D�f�o�C�X�I�u�W�F�N�g�̐�p�̍\����
	D3DPRESENT_PARAMETERS d3dpp;

	//�\���̂̒��g��������
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	//�E�B���h�E���[�h�̑I��
	d3dpp.Windowed = TRUE;

	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	//�N���C�A���g�̕��ƍ���
	d3dpp.BackBufferWidth = g.WINDOW_WIDTH;
	d3dpp.BackBufferHeight = g.WINDOW_HEIGHT;

	// ��ʃf�o�C�X�쐬�ɐ����������ǂ���
	if (FAILED(_pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g.pDevice)))
	{
		// �G���[
		MessageBox(NULL, "�f�o�C�X�I�u�W�F�N�g�̐����Ɏ��s���܂���", "�G���[", MB_OK);
		return E_FAIL;
	}

	g.pFade = new Fade;

	//PlayScene�̃I�u�W�F�N�g��錾
	g.pScene = new Sample;

	//PlayScene��Init���Ăяo��
	g.pScene->Init();

	//Input�̃I�u�W�F�N�g��錾
	//���ʂɂ���"Input"�����̃\�[�X�Ƃ��Ԃ��Ă��܂��̂�
	//new class�Ő錾����
	g.pInput = new class Input;

	//Input��Init���Ăяo��
	//���̂Ƃ��E�B���h�E�n���h���������Ƃ��đ���
	g.pInput->Init(hWnd);




	//�A���t�@�u�����h��L����
	g.pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	//�����������̕\��
	//��O
	g.pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	//��
	g.pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	return S_OK;
}

//�X�V����
void Game::Update()
{
	//PlayScene��Update���Ăяo��
	g.pScene->Update();
}

//���͏���
void Game::Input()
{
	//PlayScene��Input���Ăяo��
	g.pScene->Input();

	//Input��Update���Ăяo��
	g.pInput->Update();
	g.pFade->Update();
}

//�`�揈��
void Game::Draw()
{
	//�[�b�g�o�b�t�@�@�ŕ\�����Ă���	�\��������
	//��ʂ��N���A
	//�����Ŕw�i�̐F���w��ł���
	//���݂͐��F�Ɏw��
	g.pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 255, 255), 1.0f, 0);

	//������`�悷��Ƃ��́A�`�悷��O��BeginScene�֐��A�`����EndScene�֐����Ăяo��
	//�Ō�Ƀo�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���
	//�`��͌����Ȃ��Ƃ���ŕ`�悵�A������܂Ƃ߂ē���ւ��Ă���

	//�`��J�n
	g.pDevice->BeginScene();

	//PlayScene��Draw���Ăяo��
	g.pScene->Draw();

	//�`��I��
	g.pDevice->EndScene();

	//����ւ�
	g.pDevice->Present(NULL, NULL, NULL, NULL);
}