/*Fbx.h*/

//�C���N���[�h�K�[�h
#pragma once

/****�C���N���[�h****/
#include "Node.h"
#include <fbxsdk.h>
/********************/


/**************�����J**************/
#pragma comment(lib, "libfbxsdk-mt.lib")
/**********************************/


//���C�L���X�g�\����
struct RayCastData
{
	//���ˈʒu
	D3DXVECTOR3 start;

	//���˕���
	D3DXVECTOR3 dir;

	//�����肩�ǂ���
	bool hit;

	//����
	float dist;

	//�@��
	D3DXVECTOR3 normal;
};


//Fbx���g�p���邽�߂̃N���X
//Node���p��
//Quad�N���X�Ǝ��Ă���
class Fbx : public Node
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

		D3DXVECTOR3 tangent;
	};

	// �G�t�F�N�g(�V�F�[�_�[)
	LPD3DXEFFECT _shader;

	//�}�l�[�W��
	FbxManager *_manager;

	//�C���|�[�^
	FbxImporter *_importer;

	//�V�[��
	FbxScene *_scene;

	//���_�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9 _vertexBuffer;

	struct MaterialData
	{
		//�C���f�b�N�X�o�b�t�@
		LPDIRECT3DINDEXBUFFER9 indexBuffer;

		//�}�e���A��
		D3DMATERIAL9 material;

		//�e�N�X�`��
		LPDIRECT3DTEXTURE9 texture;

		//�m�[�}���e�N�X�`��
		LPDIRECT3DTEXTURE9 normalTexture;

		//�}�e���A�����Ƃ̃|���S����
		int polygonCountOfMaterial;

		int shaderPass;

	}*_materialData;

	//���[�v�p�E���[�v�p2�E���[�v�p3�E�m�[�h�J�E���g�E�o�b�t�@�J�E���g�E�|���S���J�E���g�E�C���f�b�N�X�J�E���g�E�}�e���A���J�E���g
	int initialize, initialize2, initialize3, nodeCount, vertexCount, polygonCount, indexCount, materialCount;

public:

	//�R���X�g���N�^
	Fbx();

	//�f�X�g���N�^
	~Fbx();

	//�ÓI�֐�	Fbx�̍쐬
	//����->Fbx��
	//�ߒl->Fbx
	static Fbx *Create(LPCSTR fileName);

	//Fbx�̏���
	//����->Fbx
	//�ߒl->�Ȃ�
	void Load(LPCSTR fileName);

	//�`�揈��
	//����->�Ȃ�
	//�ߒl->�Ȃ�
	void Draw();

	//���͏���
	//����->�Ȃ�
	//�ߒl->�Ȃ�
	void Input(){};

	//���C�L���X�g�̓����蔻��
	void RayCast(RayCastData *data);

	//�m�[�h�̓��e�`�F�b�N
	//����->�m�[�h(���[�g�m�[�h�̎q)
	//�ߒl->�Ȃ�
	void CheckNode(FbxNode *pNode);

	//���b�V���m�[�h����
	//����->�m�[�h(�q)
	//�ߒl->�Ȃ�
	void CheckMesh(FbxMesh *pMesh);

	D3DXVECTOR3 CreateTangent(D3DXVECTOR3 *pos0, D3DXVECTOR3 *pos1, D3DXVECTOR3 *pos2,
		D3DXVECTOR2 *uv0, D3DXVECTOR2 *uv1, D3DXVECTOR2 *uv2);

	void SetShafer(LPD3DXEFFECT setShader);
};