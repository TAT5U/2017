/*Quad.h*/

//�C���N���[�h�K�[�h
#pragma once

/****�C���N���[�h****/
#include"Node.h"
/********************/

class Camera;

//�|���S�����g�p���邽�߂̃N���X
//Node�N���X���p��
class Quad : public Node
{
	//���_�̏��
	struct Vertex
	{
		//�ʒu
		D3DXVECTOR3 pos;

		//�@��
		D3DXVECTOR3 normal;

		//UV���W
		D3DXVECTOR2 uv;
	};

	//���_�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer;

	//�C���f�b�N�X�o�b�t�@
	LPDIRECT3DINDEXBUFFER9 _pIndexBuffer;

	//�}�e���A��
	D3DMATERIAL9 _material;

	//�e�N�X�`��
	LPDIRECT3DTEXTURE9 _pTexture;

	Camera* _camera;

public:

	//�R���X�g���N�^
	Quad();

	//�f�X�g���N�^
	~Quad();

	//�ÓI�֐�	�|���S���̍쐬
	//�|���S���Ƀe�N�X�`����\��
	//����->�摜��
	//�ߒl->�|���S��
	static Quad *Create(LPCSTR fileName);

	//�|���S���̏���
	//����->�摜��
	//�ߒl->�Ȃ�
	void Load(LPCSTR fileName);

	//�`�揈��
	//����->�Ȃ�
	//�ߒl->�Ȃ�
	void Draw();

	//�J�������Z�b�g
	void SetCamera(Camera* camera);
};

