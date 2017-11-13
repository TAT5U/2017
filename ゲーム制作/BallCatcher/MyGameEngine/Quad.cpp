/*Quad.cpp*/

/*2017-09-18
	��� �B��
		�|���S�����쐬���\������Quad�v���O����*/

/****�C���N���[�h****/
#include "Quad.h"
/********************/


//�R���X�g���N�^
Quad::Quad()
{
	//�ϐ��̏�����
	_pVertexBuffer = nullptr;
	_pIndexBuffer = nullptr;
	_pTexture = nullptr;
}

//�f�X�g���N�^
Quad::~Quad()
{
	//�������
	SAFE_RELEASE(_pTexture);
	SAFE_RELEASE(_pIndexBuffer);
	SAFE_RELEASE(_pVertexBuffer);
}

//�ÓI�֐�	�|���S���̍쐬
Quad *Quad::Create(LPCSTR fileName)
{
	Quad *pQuad = new Quad;
	pQuad->Load(fileName);
	return pQuad;
}

//�|���S���̏���
void Quad::Load(LPCSTR fileName)
{
	//���_��ݒ�
	//�@���͑S����O
	Vertex vertexList[] = { D3DXVECTOR3(-1, 1, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0, 0), 
							D3DXVECTOR3(1, 1, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(1, 0), 
							D3DXVECTOR3(1, -1, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(1, 1), 
							D3DXVECTOR3(-1, -1, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0, 1) };

	//�o�b�t�@���m��
	g.pDevice->CreateVertexBuffer(sizeof(vertexList), 0, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, D3DPOOL_MANAGED, &_pVertexBuffer, 0);

	//�o�b�t�@�����b�N
	//�f�[�^���R�s�[����ɂ̓��b�N���Ȃ��Ƃ����Ȃ�
	Vertex *pVCopy;
	_pVertexBuffer->Lock(0, 0, (void**)&pVCopy, 0);

	//�f�[�^���R�s�[
	memcpy(pVCopy, vertexList, sizeof(vertexList));

	//�R�s�[���I������烍�b�N���O��
	_pVertexBuffer->Unlock();

	//�C���f�b�N�X���
	//DirectX�̃|���S���͎O�p�`�����g���Ȃ��̂�
	//�O�p�`���g���ĕ\�����邽�߁A�ǂ̒��_���g�����w�肷��
	//���v���Ɏw�肷��
	int indexList[] = { 0, 2, 3, 0, 1, 2 };

	//�C���f�b�N�X�o�b�t�@���m��
	g.pDevice->CreateIndexBuffer(sizeof(indexList), 0, D3DFMT_INDEX32, D3DPOOL_MANAGED, &_pIndexBuffer, 0);

	//�C���f�b�N�X�o�b�t�@�����b�N
	DWORD *pICopy;
	_pIndexBuffer->Lock(0, 0, (void**)&pICopy, 0);

	//�f�[�^���R�s�[
	memcpy(pICopy, indexList, sizeof(indexList));

	//�R�s�[���I������烍�b�N���O��
	_pIndexBuffer->Unlock();

	//�}�e���A�������ׂď�����
	ZeroMemory(&_material, sizeof(D3DMATERIAL9));

	//�}�e���A���̐F��ݒ�
	//���ꂼ��̐F�𐔒l�����˕Ԃ�
	_material.Diffuse.r = 1.0f;
	_material.Diffuse.g = 1.0f;
	_material.Diffuse.b = 1.0f;

	//�e�N�X�`���I�u�W�F�N�g�̍쐬
	D3DXCreateTextureFromFileEx(g.pDevice, fileName, 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, NULL, NULL, NULL, &_pTexture);
}

//�`�揈��
void Quad::Draw()
{
	//���_�o�b�t�@���Z�b�g
	g.pDevice->SetStreamSource(0, _pVertexBuffer, 0, sizeof(Vertex));

	//�C���f�b�N�X�o�b�t�@���Z�b�g
	g.pDevice->SetIndices(_pIndexBuffer);

	//�}�e���A�����Z�b�g
	g.pDevice->SetMaterial(&_material);

	//�e�N�X�`�����Z�b�g
	g.pDevice->SetTexture(0, _pTexture);

	//���̏��Ȃ̂�
	//�ʒu�Ɩ@����UV���W
	g.pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1);

	//�ړ��s��
	D3DXMATRIX trans;
	D3DXMatrixTranslation(&trans, _position.x, _position.y, _position.z);

	//��]�s��
	D3DXMATRIX rotateX, rotateY, rotateZ;
	D3DXMatrixRotationX(&rotateX, D3DXToRadian(_rotate.x));
	D3DXMatrixRotationY(&rotateY, D3DXToRadian(_rotate.y));
	D3DXMatrixRotationZ(&rotateZ, D3DXToRadian(_rotate.z));

	//�g��k��
	D3DXMATRIX scale;
	D3DXMatrixScaling(&scale, _scale.x, _scale.y, _scale.z);

	//���[���h�s��
	//Unity���Q�l�ɂ�����]�̏���
	D3DXMATRIX world = scale * rotateZ * rotateX * rotateY * trans;

	//���[���h�s����Z�b�g
	g.pDevice->SetTransform(D3DTS_WORLD, &world);

	//�|���S����`��
	//4�͒��_��
	//2�̓|���S����(�O�p�`�̐�)
	g.pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}