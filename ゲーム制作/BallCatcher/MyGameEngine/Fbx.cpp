#include "Fbx.h"

Fbx::Fbx()
{
	//変数の初期化
	_manager = nullptr;
	_importer = nullptr;
	_scene = nullptr;
	_vertexBuffer = nullptr;
	_indexBuffer = nullptr;
	_material = nullptr;
	_pTexture = nullptr;

	initialize = 0;
	initialize2 = 0;
	initialize3 = 0;
	nodeCount = 0;
	vertexCount = 0;
	polygonCount = 0;
	indexCount = 0;
	materialCount = 0;

	polygonCountOfMaterial = nullptr;
}
Fbx::~Fbx()
{
	//解放処理
	SAFE_DELETE(polygonCountOfMaterial);
	SAFE_DELETE(_pTexture);
	delete[] _pTexture;
	//SAFE_DELETE(_material);

	delete[] _material;
	while (initialize < materialCount)
	{
		_indexBuffer[initialize]->Release();
		initialize++;
	}
	delete[] _indexBuffer;
	initialize = 0;
	SAFE_RELEASE(_vertexBuffer);
	_manager->Destroy();
}
Fbx *Fbx::Create(LPCSTR fileName)
{
	Fbx *fbx = new Fbx();
	fbx->Load(fileName);
	return fbx;
}

void Fbx::Load(LPCSTR fileName)
{
	_manager = FbxManager::Create();
	_importer = FbxImporter::Create(_manager, "");
	_scene = FbxScene::Create(_manager, "");

	_importer->Initialize(fileName);
	_importer->Import(_scene);
	_importer->Destroy();

	char defaultCurrentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

	char dir[MAX_PATH];
	_splitpath_s(fileName, NULL, 0, dir, MAX_PATH, NULL, 0, NULL, 0);
	SetCurrentDirectory(dir);

	FbxNode *rootNode = _scene->GetRootNode();

	int childCount = rootNode->GetChildCount();

	while (nodeCount < childCount)
	{
		CheckNode(rootNode->GetChild(nodeCount));
		nodeCount++;
	}
	SetCurrentDirectory(defaultCurrentDir);
	nodeCount = 0;
}

void Fbx::Draw()
{
	//頂点バッファをセット
	g.pDevice->SetStreamSource(0, _vertexBuffer, 0, sizeof(Vertex));

	//インデックスバッファをセット
	//g.pDevice->SetIndices(*_indexBuffer);

	//マテリアルをセット
	//g.pDevice->SetMaterial(&*_material);

	//テクスチャをセット
	//g.pDevice->SetTexture(0, _pTexture);

	//何の情報なのか
	//位置と法線とUV座標
	g.pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1);

	//移動行列
	D3DXMATRIX trans;
	D3DXMatrixTranslation(&trans, _position.x, _position.y, _position.z);

	//回転行列
	D3DXMATRIX rotateX, rotateY, rotateZ;
	D3DXMatrixRotationX(&rotateX, D3DXToRadian(_rotate.x));
	D3DXMatrixRotationY(&rotateY, D3DXToRadian(_rotate.y));
	D3DXMatrixRotationZ(&rotateZ, D3DXToRadian(_rotate.z));

	//拡大縮小
	D3DXMATRIX scale;
	D3DXMatrixScaling(&scale, _scale.x, _scale.y, _scale.z);

	//ワールド行列
	//Unityを参考にした回転の順番
	D3DXMATRIX world = scale * rotateZ * rotateX * rotateY * trans;

	//ワールド行列をセット
	g.pDevice->SetTransform(D3DTS_WORLD, &world);

	while (initialize < materialCount)
	{
		g.pDevice->SetIndices(_indexBuffer[initialize]);
		g.pDevice->SetMaterial(&_material[initialize]);

		g.pDevice->SetTexture(0, _pTexture[initialize]);
		//
		g.pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, polygonCountOfMaterial[initialize]);

		initialize++;
	}
	initialize = 0;
}

void Fbx::CheckNode(FbxNode *pNode)
{
	FbxNodeAttribute *attr = pNode->GetNodeAttribute();

	if (attr->GetAttributeType() == FbxNodeAttribute::eMesh)
	{
		materialCount = pNode->GetMaterialCount();
		_material = new D3DMATERIAL9[materialCount];
		_pTexture = new LPDIRECT3DTEXTURE9[materialCount];

		while (initialize < materialCount)
		{
			FbxSurfaceLambert *lambert = (FbxSurfaceLambert*)pNode->GetMaterial(initialize);
			FbxDouble3 diffuse = lambert->Diffuse;
			FbxDouble3 ambient = lambert->Ambient;

			ZeroMemory(&_material[initialize], sizeof(D3DMATERIAL9));

			_material[initialize].Diffuse.r = (float)diffuse[0];
			_material[initialize].Diffuse.g = (float)diffuse[1];
			_material[initialize].Diffuse.b = (float)diffuse[2];
			_material[initialize].Diffuse.a = 1.0f;

			_material[initialize].Ambient.r = (float)ambient[0];
			_material[initialize].Ambient.g = (float)ambient[1];
			_material[initialize].Ambient.b = (float)ambient[2];
			_material[initialize].Ambient.a = 1.0f;

			FbxProperty lProperty = pNode->GetMaterial(initialize)->FindProperty(FbxSurfaceMaterial::sDiffuse);
			FbxFileTexture *textureFile = lProperty.GetSrcObject<FbxFileTexture>(0);


			if (textureFile == NULL)
			{
				_pTexture[initialize] = NULL;
			}
			else
			{
				const char *textureFileName = textureFile->GetFileName();


				char name[_MAX_FNAME];
				char ext[_MAX_EXT];
				_splitpath_s(textureFileName, NULL, 0, NULL, 0, name, _MAX_FNAME, ext, _MAX_EXT);
				wsprintf(name, "%s%s", name, ext);

				D3DXCreateTextureFromFileEx(g.pDevice, name, 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT,
					D3DX_FILTER_NONE, D3DX_DEFAULT, NULL, NULL, NULL, &_pTexture[initialize]);


			}

			initialize++;
		}
		initialize = 0;
		CheckMesh(pNode->GetMesh());
	}
	else
	{
		int childCount = pNode->GetChildCount();
		while (initialize < childCount)
		{
			// 再帰
			CheckNode(pNode->GetChild(nodeCount));
			initialize++;
		}
		initialize = 0;
	}
}

void Fbx::CheckMesh(FbxMesh *pMesh)
{
	vertexCount = pMesh->GetControlPointsCount();
	polygonCount = pMesh->GetPolygonCount();
	indexCount = pMesh->GetPolygonVertexCount();

	FbxVector4 *pVertexPos = pMesh->GetControlPoints();
	Vertex *vertexList = new Vertex[vertexCount];

	while (initialize < vertexCount)
	{
		vertexList[initialize].pos.x = (float)pVertexPos[initialize][0];
		vertexList[initialize].pos.y = (float)pVertexPos[initialize][1];
		vertexList[initialize].pos.z = (float)pVertexPos[initialize][2];
		initialize++;
	}
	initialize = 0;

	while (initialize < polygonCount)
	{
		int startIndex = pMesh->GetPolygonVertexIndex(initialize);
		while (initialize2 < 3)
		{
			int index = pMesh->GetPolygonVertices()[startIndex + initialize2];

			FbxVector4 Normal;
			pMesh->GetPolygonVertexNormal(initialize, initialize2, Normal);

			vertexList[index].normal = D3DXVECTOR3((float)Normal[0], (float)Normal[1], (float)Normal[2]);
			FbxVector2 uv = pMesh->GetLayer(0)->GetUVs()->GetDirectArray().GetAt(index);

			vertexList[index].uv = D3DXVECTOR2((float)uv.mData[0], (float)(1.0 - uv.mData[1]));

			initialize2++;
		}
		initialize++;
		initialize2 = 0;
	}
	initialize = 0;
	initialize2 = 0;

	// ポインタだからsizeof * カウント
	g.pDevice->CreateVertexBuffer(sizeof(Vertex)* vertexCount, 0, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, D3DPOOL_MANAGED, &_vertexBuffer, 0);

	Vertex *vCopy;
	_vertexBuffer->Lock(0, 0, (void**)&vCopy, 0);
	memcpy(vCopy, vertexList, sizeof(Vertex)* vertexCount);
	_vertexBuffer->Unlock();

	delete[] vertexList;

	_indexBuffer = new IDirect3DIndexBuffer9*[materialCount];
	polygonCountOfMaterial = new int[materialCount];

	while (initialize < materialCount)
	{
		int *indexList = new int[indexCount];
		int count = 0;
		while (initialize2 < polygonCount)
		{
			int materialID = pMesh->GetLayer(0)->GetMaterials()->GetIndexArray().GetAt(initialize2);
			if (materialID == initialize)
			{
				while (initialize3 < 3)
				{
					indexList[count++] = pMesh->GetPolygonVertex(initialize2, initialize3);
					initialize3++;
				}
			}
			initialize3 = 0;
			initialize2++;
		}
		initialize2 = 0;
		initialize3 = 0;
		polygonCountOfMaterial[initialize] = count / 3;

		g.pDevice->CreateIndexBuffer(sizeof(int)* indexCount, 0, D3DFMT_INDEX32, D3DPOOL_MANAGED, &_indexBuffer[initialize], 0);
		DWORD *iCopy;
		_indexBuffer[initialize]->Lock(0, 0, (void**)&iCopy, 0);
		memcpy(iCopy, indexList, sizeof(int)* indexCount);
		_indexBuffer[initialize]->Unlock();
		delete[] indexList;
		initialize++;
	}
	initialize = 0;

}