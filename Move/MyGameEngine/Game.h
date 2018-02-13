#pragma once
#include "Global.h"
#include "Sprite.h"
#include "Scene.h"

class Game
{
	LPDIRECT3D9	_pD3d;	    //Direct3D�I�u�W�F�N�g
	Scene*     _pScene;


public:
	Game();			//�R���X�g���N�^
	~Game();		//�f�X�g���N�^�i�J�������j
	HRESULT Init(HWND hWnd);	//����������
	void Update();			//�X�V����
	void Input();			//���͏���
	void Draw();			//�`�揈��
};