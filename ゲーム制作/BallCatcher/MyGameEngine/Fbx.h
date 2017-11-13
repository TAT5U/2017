#pragma once
#include "Node.h"
#include <fbxsdk.h>
#pragma comment(lib, "libfbxsdk-mt.lib")

class Fbx : public Node
{
	struct Vertex
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 normal;
		D3DXVECTOR2 uv;
	};

	FbxManager *_manager;
	FbxImporter *_importer;
	FbxScene *_scene;

	LPDIRECT3DVERTEXBUFFER9 _vertexBuffer;
	LPDIRECT3DINDEXBUFFER9 *_indexBuffer;
	D3DMATERIAL9 *_material;
	LPDIRECT3DTEXTURE9 *_pTexture;

	int initialize, initialize2, initialize3, nodeCount, vertexCount, polygonCount, indexCount, materialCount;
	int *polygonCountOfMaterial;

public:
	Fbx();
	~Fbx();

	static Fbx *Create(LPCSTR fileName);
	void Load(LPCSTR fileName);
	void Draw();

	void CheckNode(FbxNode *pNode);
	void CheckMesh(FbxMesh *pMesh);
};