#pragma once

//�C���N���[�h
#include <Windows.h>
#include <d3dx9.h>
#include "MyRect.h"
#include "Input.h"

#define SAFE_DELETE(X) if(X){ delete X; X = nullptr;}
#define SAFE_RELEASE(X) if(X){ X->Release(); X = nullptr;}

class Scene;
class Camera;

//�O���[�o���ϐ�
class Global
{
public:
	//�萔
	const int	WINDOW_WIDTH = 800;		//�E�B���h�E�̕�
	const int	WINDOW_HEIGHT = 600;	//�E�B���h�E�̍���

	//�ϐ�
	LPDIRECT3DDEVICE9	pDevice;		//Direct3D�f�o�C�X�I�u�W�F�N�g
	Scene*				pScene;
	Input*				pInput;
	Camera*				pCamera;
	void ReplaceScene(Scene* pNextScene);
};

//�O���[�o���I�u�W�F�N�g�i�O���錾�j
extern Global g;