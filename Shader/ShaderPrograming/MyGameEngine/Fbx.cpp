/*Fbx.cpp*/

/****インクルード****/
#include "Fbx.h"
/********************/


//コンストラクタ
Fbx::Fbx()
{
	//変数の初期化
	_shader = nullptr;
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

//デストラクタ
Fbx::~Fbx()
{
	//解放処理
	SAFE_DELETE(polygonCountOfMaterial);
	SAFE_DELETE(_pTexture);
	delete[] _pTexture;

	delete[] _material;

	//配列なので1つ1つReleaseしてからdeleteする
	while (initialize < materialCount)
	{
		_indexBuffer[initialize]->Release();
		initialize++;
	}
	delete[] _indexBuffer;
	initialize = 0;
	SAFE_RELEASE(_vertexBuffer);
	_manager->Destroy();
	SAFE_RELEASE(_shader);
}

//静的関数	Fbxの作成
Fbx *Fbx::Create(LPCSTR fileName)
{
	Fbx *fbx = new Fbx();
	fbx->Load(fileName);
	return fbx;
}

//Fbxの準備
void Fbx::Load(LPCSTR fileName)
{
	//マネージャ・インポータ・シーンを作成
	_manager = FbxManager::Create();
	_importer = FbxImporter::Create(_manager, "");
	_scene = FbxScene::Create(_manager, "");

	//Fbxを開く
	_importer->Initialize(fileName);

	//Fbxをシーンに渡す
	_importer->Import(_scene);

	//インポータを解放
	_importer->Destroy();

	//最初のカレントディレクトリのパスを取得
	char defaultCurrentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

	//パスを取得してカレントディレクトリを設定
	char dir[MAX_PATH];
	_splitpath_s(fileName, NULL, 0, dir, MAX_PATH, NULL, 0, NULL, 0);
	SetCurrentDirectory(dir);

	//Fbxからルートノードを取り出す
	FbxNode *rootNode = _scene->GetRootNode();

	//ルートノードの子の数カウント
	int childCount = rootNode->GetChildCount();

	//子の分ループ
	while (nodeCount < childCount)
	{
		//ノード内容チェック
		CheckNode(rootNode->GetChild(nodeCount));
		nodeCount++;
	}

	//カレントディレクトリを最初のパスに戻す
	SetCurrentDirectory(defaultCurrentDir);
	nodeCount = 0;

	// エラー用変数
	LPD3DXBUFFER error = 0;

	// エフェクトを設定
	// 最後の引数にエラー用変数を入れることで
	// どこでエラーになったかが分かる
	if (FAILED(D3DXCreateEffectFromFile(g.pDevice, "LambertShader.hlsl", NULL, NULL, NULL, NULL, &_shader, &error)))
	{
		//	エラー内容
		MessageBox(NULL, (char*)error->GetBufferPointer(), "シェーダーエラー", MB_OK);
	}
}

//描画処理
void Fbx::Draw()
{
	//頂点バッファをセット
	g.pDevice->SetStreamSource(0, _vertexBuffer, 0, sizeof(Vertex));

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

	// ワールド行列をセット
	g.pDevice->SetTransform(D3DTS_WORLD, &world);

	// シェーダーを設定
	_shader->SetMatrix("matWorld", &world);

	// ビュー行列
	D3DXMATRIX view;
	g.pDevice->GetTransform(D3DTS_VIEW, &view);

	// ビュー行列をセット
	_shader->SetMatrix("matView", &view);

	// プロジェクション行列
	D3DXMATRIX proj;
	g.pDevice->GetTransform(D3DTS_PROJECTION, &proj);

	// プロジェクション行列をセット
	_shader->SetMatrix("matProj", &proj);

	// 回転を反映してライトを一定の向きから当たっているようにする(正しい影がつくようにする)
	// ワールド行列で行うので『 Z * X * Y』の順で掛ける
	// 掛ける順番が違うと正しく影がつかない
	_shader->SetMatrix("matRotate", &(rotateZ * rotateX * rotateY));


	_shader->Begin(NULL, 0);
	_shader->BeginPass(0);

	//マテリアル数分ループ
	while (initialize < materialCount)
	{
		g.pDevice->SetIndices(_indexBuffer[initialize]);
		g.pDevice->SetMaterial(&_material[initialize]);

		//テクスチャを選択
		g.pDevice->SetTexture(0, _pTexture[initialize]);

		//描画
		//頂点数
		//マテリアルごとのポリゴン数
		g.pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, polygonCountOfMaterial[initialize]);

		initialize++;
	}
	initialize = 0;

	// 開始したら必ず終了させる
	_shader->EndPass();
	_shader->End();
}

//レイキャストの当たり判定
void Fbx::RayCast(RayCastData *data)
{
	//初期設定
	data->hit = false;
	data->dist = 99999.0f;

	//バッファをロック
	Vertex *vCopy;
	_vertexBuffer->Lock(0, 0, (void**)&vCopy, 0);

	while (initialize < materialCount)
	{
		//バッファをロック
		DWORD *iCopy;
		_indexBuffer[initialize]->Lock(0, 0, (void**)&iCopy, 0);

		while (initialize2 < polygonCountOfMaterial[initialize])
		{
			//頂点を取得
			D3DXVECTOR3 ver[3];
			ver[0] = vCopy[iCopy[initialize2 * 3 + 0]].pos;
			ver[1] = vCopy[iCopy[initialize2 * 3 + 1]].pos;
			ver[2] = vCopy[iCopy[initialize2 * 3 + 2]].pos;

			bool hit;
			float dist;
			hit = D3DXIntersectTri(&ver[0], &ver[1], &ver[2], &data->start, &data->dir, NULL, NULL, &dist);

			//衝突判定
			if (hit && dist < data->dist)
			{
				data->hit = true;
				data->dist = dist;

				//外積
				D3DXVECTOR3 v1 = ver[2] - ver[0];
				D3DXVECTOR3 v2 = ver[2] - ver[1];
				D3DXVec3Cross(&data->normal, &v1, &v2);

				//正規化
				D3DXVec3Normalize(&data->normal, &data->normal);
			}
			initialize2++;
		}

		//コピーが終わったらロックを外す
		_indexBuffer[initialize]->Unlock();
		initialize++;
		initialize2 = 0;
	}
	initialize = 0;
	initialize2 = 0;

	//コピーが終わったらロックを外す
	_vertexBuffer->Unlock();
}

//ノードの内容チェック
void Fbx::CheckNode(FbxNode *pNode)
{
	//ノードのタイプを取得
	FbxNodeAttribute *attr = pNode->GetNodeAttribute();

	//メッシュノード
	if (attr->GetAttributeType() == FbxNodeAttribute::eMesh)
	{
		//マテリアルの数を取得してその分配列を作成
		materialCount = pNode->GetMaterialCount();
		_material = new D3DMATERIAL9[materialCount];

		//テクスチャをマテリアル分の配列で作成
		_pTexture = new LPDIRECT3DTEXTURE9[materialCount];

		//マテリアル情報読み込み
		while (initialize < materialCount)
		{
			//ランバート
			FbxSurfaceLambert *lambert = (FbxSurfaceLambert*)pNode->GetMaterial(initialize);
			
			//ディフューズ
			FbxDouble3 diffuse = lambert->Diffuse;
			
			//アンビエント
			FbxDouble3 ambient = lambert->Ambient;

			//配列を初期化して格納
			ZeroMemory(&_material[initialize], sizeof(D3DMATERIAL9));
			_material[initialize].Diffuse.r = (float)diffuse[0];
			_material[initialize].Diffuse.g = (float)diffuse[1];
			_material[initialize].Diffuse.b = (float)diffuse[2];
			_material[initialize].Diffuse.a = 1.0f;
			_material[initialize].Ambient.r = (float)ambient[0];
			_material[initialize].Ambient.g = (float)ambient[1];
			_material[initialize].Ambient.b = (float)ambient[2];
			_material[initialize].Ambient.a = 1.0f;

			//テクスチャの情報と画像ファイルの情報を取得
			FbxProperty lProperty = pNode->GetMaterial(initialize)->FindProperty(FbxSurfaceMaterial::sDiffuse);
			FbxFileTexture *textureFile = lProperty.GetSrcObject<FbxFileTexture>(0);

			//テクスチャが貼られていない
			if (textureFile == NULL)
			{
				_pTexture[initialize] = NULL;
			}
			else
			{
				//画像ファイル読み込み
				const char *textureFileName = textureFile->GetFileName();

				//画像のファイル名は絶対パスで入っているため変換しなければならない
				//しかしファイルの階層はそれぞれ異なるのでファイル名と拡張子だけ取得して
				//それだけを利用する
				char name[_MAX_FNAME];
				char ext[_MAX_EXT];

				//パスを分割
				_splitpath_s(textureFileName, NULL, 0, NULL, 0, name, _MAX_FNAME, ext, _MAX_EXT);
				
				//結合
				wsprintf(name, "%s%s", name, ext);

				//テクスチャオブジェクトの作成
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
		//再帰でさらにその下の階層も調べる
		int count = 0;
		int childCount = pNode->GetChildCount();
		while (count < childCount)
		{
			CheckNode(pNode->GetChild(count));
			count++;
		}
		count = 0;
	}
}

//メッシュノード処理
void Fbx::CheckMesh(FbxMesh *pMesh)
{
	//頂点数取得
	vertexCount = pMesh->GetControlPointsCount();

	//ポリゴン数取得
	polygonCount = pMesh->GetPolygonCount();

	//インデックス数取得
	indexCount = pMesh->GetPolygonVertexCount();

	//頂点情報読み込み
	FbxVector4 *pVertexPos = pMesh->GetControlPoints();

	//Vertex構造体作成
	Vertex *vertexList = new Vertex[vertexCount];

	//コピー
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
		//ポリゴンがどの頂点で出来ているか取得
		int startIndex = pMesh->GetPolygonVertexIndex(initialize);

		//三角形の3つの頂点分ループ
		while (initialize2 < 3)
		{
			//頂点番号一覧取得
			int index = pMesh->GetPolygonVertices()[startIndex + initialize2];

			//法線の取得して格納
			FbxVector4 Normal;
			pMesh->GetPolygonVertexNormal(initialize, initialize2, Normal);
			vertexList[index].normal = D3DXVECTOR3((float)Normal[0], (float)Normal[1], (float)Normal[2]);
			
			//UVの情報を取得してXとYに分割して格納
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

	//バッファをロック
	//データをコピーするにはロックしないといけない
	Vertex *vCopy;
	_vertexBuffer->Lock(0, 0, (void**)&vCopy, 0);

	//データをコピー
	memcpy(vCopy, vertexList, sizeof(Vertex)* vertexCount);

	//コピーが終わったらロックを外す
	_vertexBuffer->Unlock();

	//解放
	delete[] vertexList;

	//インデックスバッファの配列を作成
	_indexBuffer = new IDirect3DIndexBuffer9*[materialCount];

	//マテリアルごとのポリゴン数を入れる配列を作成
	polygonCountOfMaterial = new int[materialCount];

	while (initialize < materialCount)
	{
		//インデックスの配列を作成
		int *indexList = new int[indexCount];
		int count = 0;
		while (initialize2 < polygonCount)
		{
			//マテリアルごとのインデックス情報を取得
			int materialID = pMesh->GetLayer(0)->GetMaterials()->GetIndexArray().GetAt(initialize2);
			if (materialID == initialize)
			{
				//インデックス情報格納
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

		//ポリゴン数を取得
		//三角形で作られているので3で割る
		polygonCountOfMaterial[initialize] = count / 3;

		// ポインタだからsizeof * カウント
		g.pDevice->CreateIndexBuffer(sizeof(int)* indexCount, 0, D3DFMT_INDEX32, D3DPOOL_MANAGED, &_indexBuffer[initialize], 0);
		
		//バッファをロック
		//データをコピーするにはロックしないといけない
		DWORD *iCopy;
		_indexBuffer[initialize]->Lock(0, 0, (void**)&iCopy, 0);

		//データをコピー
		memcpy(iCopy, indexList, sizeof(int)* indexCount);

		//コピーが終わったらロックを外す
		_indexBuffer[initialize]->Unlock();

		//解放
		delete[] indexList;
		initialize++;
	}
	initialize = 0;
}