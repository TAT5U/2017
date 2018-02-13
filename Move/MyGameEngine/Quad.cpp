#include "Quad.h"
#include "Camera.h"

Quad::Quad()
{
	_camera = nullptr;
}


Quad::~Quad()
{
}

Quad* Quad::Create(LPCSTR fileName)
{
	auto quad = new Quad();
	quad->Load(fileName);
	return quad;
}

void Quad::Load(LPCSTR fileName)
{
	Vertex vertexList[] = {
		D3DXVECTOR3(-1, 1, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0, 0),
		D3DXVECTOR3(1, 1, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(1, 0),
		D3DXVECTOR3(1, -1, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(1, 1),
		D3DXVECTOR3(-1, -1, 0), D3DXVECTOR3(0, 0, -1), D3DXVECTOR2(0, 1),
	};

	g.pDevice->CreateVertexBuffer(sizeof(vertexList), 0, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, D3DPOOL_MANAGED, &_vertexBuffer, 0);
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

	ZeroMemory(&_material, sizeof(D3DMATERIAL9));
	_material.Diffuse.r = 1.0f;
	_material.Diffuse.g = 1.0f;
	_material.Diffuse.b = 1.0f;


	D3DXCreateTextureFromFileEx(g.pDevice, fileName, 0, 0, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT,
		NULL, NULL, NULL, &_pTexture);
}

void Quad::Draw()
{
	g.pDevice->SetStreamSource(0, _vertexBuffer, 0, sizeof(Vertex));
	g.pDevice->SetIndices(_indexBuffer);
	g.pDevice->SetMaterial(&_material);
	g.pDevice->SetTexture(0, _pTexture);
	g.pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1);

	//ˆÚ“®s—ñ
	D3DXMATRIX trans;
	D3DXMatrixTranslation(&trans, _position.x, _position.y, _position.z);

	//‰ñ“]s—ñ
	D3DXMATRIX rotateX, rotateY, rotateZ;
	D3DXMatrixRotationX(&rotateX, D3DXToRadian(_rotate.x));
	D3DXMatrixRotationY(&rotateY, D3DXToRadian(_rotate.y));
	D3DXMatrixRotationZ(&rotateZ, D3DXToRadian(_rotate.z));

	//Šg‘åk¬
	D3DXMATRIX scale;
	D3DXMatrixScaling(&scale, _scale.x, _scale.y, _scale.z);

	//ƒ[ƒ‹ƒhs—ñ
	D3DXMATRIX world = scale * rotateZ * rotateX * rotateY * trans;

	if (_camera)
	{
		world = scale * _camera->GetBillboard() * 
			rotateZ * rotateX * rotateY * trans;
	}

	g.pDevice->SetTransform(D3DTS_WORLD, &world);

	g.pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}