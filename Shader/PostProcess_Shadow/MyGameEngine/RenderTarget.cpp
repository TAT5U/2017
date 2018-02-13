

/****�C���N���[�h****/
#include "RenderTarget.h"
/********************/


//�R���X�g���N�^
RenderTarget::RenderTarget()
{
	//�ϐ��̏�����
	_vertexBuffer = nullptr;
	_indexBuffer = nullptr;
	_renderTexture = nullptr;
	_renderSurface = nullptr;
	_renderZBuffer = nullptr;

	_defaultSurface = nullptr;
	_defaultZBuffer = nullptr;
}

//�f�X�g���N�^
RenderTarget::~RenderTarget()
{
	//�������
	SAFE_RELEASE(_defaultZBuffer);
	SAFE_RELEASE(_defaultSurface);

	SAFE_RELEASE(_renderZBuffer);
	SAFE_RELEASE(_renderSurface);
	
	SAFE_RELEASE(_renderTexture);
	SAFE_RELEASE(_indexBuffer);
	SAFE_RELEASE(_vertexBuffer);
}

void RenderTarget::Load()
{
	////���_��ݒ�
	////�@���͑S����O
	//Vertex vertexList[] = 
	//{ 
	//	D3DXVECTOR3(-1, 1, 0), D3DXVECTOR2(0, 0),
	//	D3DXVECTOR3(1, 1, 0), D3DXVECTOR2(1, 0),
	//	D3DXVECTOR3(1, -1, 0), D3DXVECTOR2(1, 1),
	//	D3DXVECTOR3(-1, -1, 0), D3DXVECTOR2(0, 1) 
	//};

	////�o�b�t�@���m��
	//g.pDevice->CreateVertexBuffer(sizeof(vertexList), 0, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, D3DPOOL_MANAGED, &_vertexBuffer, 0);

	////�o�b�t�@�����b�N
	////�f�[�^���R�s�[����ɂ̓��b�N���Ȃ��Ƃ����Ȃ�
	//Vertex *pVCopy;
	//_vertexBuffer->Lock(0, 0, (void**)&pVCopy, 0);

	////�f�[�^���R�s�[
	//memcpy(pVCopy, vertexList, sizeof(vertexList));

	////�R�s�[���I������烍�b�N���O��
	//_vertexBuffer->Unlock();

	////�C���f�b�N�X���
	////DirectX�̃|���S���͎O�p�`�����g���Ȃ��̂�
	////�O�p�`���g���ĕ\�����邽�߁A�ǂ̒��_���g�����w�肷��
	////���v���Ɏw�肷��
	//int indexList[] = { 0, 2, 3, 0, 1, 2 };

	////�C���f�b�N�X�o�b�t�@���m��
	//g.pDevice->CreateIndexBuffer(sizeof(indexList), 0, D3DFMT_INDEX32, D3DPOOL_MANAGED, &_indexBuffer, 0);

	////�C���f�b�N�X�o�b�t�@�����b�N
	//DWORD *pICopy;
	//_indexBuffer->Lock(0, 0, (void**)&pICopy, 0);

	////�f�[�^���R�s�[
	//memcpy(pICopy, indexList, sizeof(indexList));

	////�R�s�[���I������烍�b�N���O��
	//_indexBuffer->Unlock();


	//// ��ʃT�C�Y�̃e�N�X�`���I�u�W�F�N�g���쐬
	//D3DXCreateTexture(g.pDevice, g.WINDOW_WIDTH, g.WINDOW_HEIGHT, 1, D3DUSAGE_RENDERTARGET, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &_renderTexture);

	//_renderTexture->GetSurfaceLevel(0, &_renderSurface);

	//g.pDevice->CreateDepthStencilSurface(g.WINDOW_WIDTH, g.WINDOW_HEIGHT, D3DFMT_D16, D3DMULTISAMPLE_NONE, 0, TRUE, &_renderZBuffer, NULL);

	//g.pDevice->GetRenderTarget(0, &_defaultSurface);
	//g.pDevice->GetDepthStencilSurface(&_defaultZBuffer);



	Vertex vertexList[] = {
		D3DXVECTOR3(-1, 1, 0), D3DXVECTOR2(0, 0),
		D3DXVECTOR3(1, 1, 0), D3DXVECTOR2(1, 0),
		D3DXVECTOR3(1, -1, 0), D3DXVECTOR2(1, 1),
		D3DXVECTOR3(-1, -1, 0), D3DXVECTOR2(0, 1),
	};

	g.pDevice->CreateVertexBuffer(sizeof(vertexList), 0, D3DFVF_XYZ | D3DFVF_TEX1, D3DPOOL_MANAGED, &_vertexBuffer, 0);
	Vertex *vCopy;
	_vertexBuffer->Lock(0, 0, (void**)&vCopy, 0);
	memcpy(vCopy, vertexList, sizeof(vertexList));
	_vertexBuffer->Unlock();


	int indexList[] = { 0, 2, 3, 0, 1, 2 };
	g.pDevice->CreateIndexBuffer(sizeof(indexList), 0, D3DFMT_INDEX32, D3DPOOL_MANAGED, &_indexBuffer, 0);
	DWORD *iCopy;
	_indexBuffer->Lock(0, 0, (void**)&iCopy, 0);
	memcpy(iCopy, indexList, sizeof(indexList));
	_indexBuffer->Unlock();


	D3DXCreateTexture(g.pDevice, g.WINDOW_WIDTH, g.WINDOW_HEIGHT,
		1, D3DUSAGE_RENDERTARGET, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT,
		&_renderTexture);

	_renderTexture->GetSurfaceLevel(0, &_renderSurface);

	g.pDevice->CreateDepthStencilSurface(
		g.WINDOW_WIDTH, g.WINDOW_HEIGHT, D3DFMT_D16,
		D3DMULTISAMPLE_NONE, 0, TRUE, &_renderZBuffer, NULL);


	g.pDevice->GetRenderTarget(0, &_defaultSurface);
	g.pDevice->GetDepthStencilSurface(&_defaultZBuffer);

	LPD3DXBUFFER err = 0;
	if (FAILED(D3DXCreateEffectFromResource(g.pDevice, NULL, MAKEINTRESOURCE(IDR_ON_SCREEN), NULL, NULL, NULL, NULL, &_shader, &err)))
	{
		MessageBox(NULL, (char*)err->GetBufferPointer(),
			"�V�F�[�_�[�G���[", MB_OK);
	}
}

//�`�揈��
void RenderTarget::Draw()
{
	g.pDevice->SetStreamSource(0, _vertexBuffer, 0, sizeof(Vertex));
	g.pDevice->SetIndices(_indexBuffer);


	g.pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);

	_shader->SetTexture("tex", _renderTexture);

	_shader->Begin(NULL, 0);
	_shader->BeginPass(0);
	g.pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	_shader->EndPass();
	_shader->End();
}


void RenderTarget::ChangeTarget()
{
	g.pDevice->SetRenderTarget(0, _renderSurface);
	g.pDevice->SetDepthStencilSurface(_renderZBuffer);
	g.pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
}

void RenderTarget::ReturnTarget()
{
	g.pDevice->SetRenderTarget(0, _defaultSurface);
	g.pDevice->SetDepthStencilSurface(_defaultZBuffer);
	
	//D3DXSaveTextureToFile("Assets//Capture//Test.jpeg", D3DXIFF_JPG, _renderTexture, NULL);
}

LPDIRECT3DTEXTURE9 RenderTarget::GetRenderTexture()
{
	return _renderTexture;
}