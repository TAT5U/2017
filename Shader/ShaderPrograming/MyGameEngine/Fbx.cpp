/*Fbx.cpp*/

/****�C���N���[�h****/
#include "Fbx.h"
/********************/


//�R���X�g���N�^
Fbx::Fbx()
{
	//�ϐ��̏�����
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

//�f�X�g���N�^
Fbx::~Fbx()
{
	//�������
	SAFE_DELETE(polygonCountOfMaterial);
	SAFE_DELETE(_pTexture);
	delete[] _pTexture;

	delete[] _material;

	//�z��Ȃ̂�1��1��Release���Ă���delete����
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

//�ÓI�֐�	Fbx�̍쐬
Fbx *Fbx::Create(LPCSTR fileName)
{
	Fbx *fbx = new Fbx();
	fbx->Load(fileName);
	return fbx;
}

//Fbx�̏���
void Fbx::Load(LPCSTR fileName)
{
	//�}�l�[�W���E�C���|�[�^�E�V�[�����쐬
	_manager = FbxManager::Create();
	_importer = FbxImporter::Create(_manager, "");
	_scene = FbxScene::Create(_manager, "");

	//Fbx���J��
	_importer->Initialize(fileName);

	//Fbx���V�[���ɓn��
	_importer->Import(_scene);

	//�C���|�[�^�����
	_importer->Destroy();

	//�ŏ��̃J�����g�f�B���N�g���̃p�X���擾
	char defaultCurrentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

	//�p�X���擾���ăJ�����g�f�B���N�g����ݒ�
	char dir[MAX_PATH];
	_splitpath_s(fileName, NULL, 0, dir, MAX_PATH, NULL, 0, NULL, 0);
	SetCurrentDirectory(dir);

	//Fbx���烋�[�g�m�[�h�����o��
	FbxNode *rootNode = _scene->GetRootNode();

	//���[�g�m�[�h�̎q�̐��J�E���g
	int childCount = rootNode->GetChildCount();

	//�q�̕����[�v
	while (nodeCount < childCount)
	{
		//�m�[�h���e�`�F�b�N
		CheckNode(rootNode->GetChild(nodeCount));
		nodeCount++;
	}

	//�J�����g�f�B���N�g�����ŏ��̃p�X�ɖ߂�
	SetCurrentDirectory(defaultCurrentDir);
	nodeCount = 0;

	// �G���[�p�ϐ�
	LPD3DXBUFFER error = 0;

	// �G�t�F�N�g��ݒ�
	// �Ō�̈����ɃG���[�p�ϐ������邱�Ƃ�
	// �ǂ��ŃG���[�ɂȂ�������������
	if (FAILED(D3DXCreateEffectFromFile(g.pDevice, "LambertShader.hlsl", NULL, NULL, NULL, NULL, &_shader, &error)))
	{
		//	�G���[���e
		MessageBox(NULL, (char*)error->GetBufferPointer(), "�V�F�[�_�[�G���[", MB_OK);
	}
}

//�`�揈��
void Fbx::Draw()
{
	//���_�o�b�t�@���Z�b�g
	g.pDevice->SetStreamSource(0, _vertexBuffer, 0, sizeof(Vertex));

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

	// ���[���h�s����Z�b�g
	g.pDevice->SetTransform(D3DTS_WORLD, &world);

	// �V�F�[�_�[��ݒ�
	_shader->SetMatrix("matWorld", &world);

	// �r���[�s��
	D3DXMATRIX view;
	g.pDevice->GetTransform(D3DTS_VIEW, &view);

	// �r���[�s����Z�b�g
	_shader->SetMatrix("matView", &view);

	// �v���W�F�N�V�����s��
	D3DXMATRIX proj;
	g.pDevice->GetTransform(D3DTS_PROJECTION, &proj);

	// �v���W�F�N�V�����s����Z�b�g
	_shader->SetMatrix("matProj", &proj);

	// ��]�𔽉f���ă��C�g�����̌������瓖�����Ă���悤�ɂ���(�������e�����悤�ɂ���)
	// ���[���h�s��ōs���̂Łw Z * X * Y�x�̏��Ŋ|����
	// �|���鏇�Ԃ��Ⴄ�Ɛ������e�����Ȃ�
	_shader->SetMatrix("matRotate", &(rotateZ * rotateX * rotateY));


	_shader->Begin(NULL, 0);
	_shader->BeginPass(0);

	//�}�e���A���������[�v
	while (initialize < materialCount)
	{
		g.pDevice->SetIndices(_indexBuffer[initialize]);
		g.pDevice->SetMaterial(&_material[initialize]);

		//�e�N�X�`����I��
		g.pDevice->SetTexture(0, _pTexture[initialize]);

		//�`��
		//���_��
		//�}�e���A�����Ƃ̃|���S����
		g.pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, polygonCountOfMaterial[initialize]);

		initialize++;
	}
	initialize = 0;

	// �J�n������K���I��������
	_shader->EndPass();
	_shader->End();
}

//���C�L���X�g�̓����蔻��
void Fbx::RayCast(RayCastData *data)
{
	//�����ݒ�
	data->hit = false;
	data->dist = 99999.0f;

	//�o�b�t�@�����b�N
	Vertex *vCopy;
	_vertexBuffer->Lock(0, 0, (void**)&vCopy, 0);

	while (initialize < materialCount)
	{
		//�o�b�t�@�����b�N
		DWORD *iCopy;
		_indexBuffer[initialize]->Lock(0, 0, (void**)&iCopy, 0);

		while (initialize2 < polygonCountOfMaterial[initialize])
		{
			//���_���擾
			D3DXVECTOR3 ver[3];
			ver[0] = vCopy[iCopy[initialize2 * 3 + 0]].pos;
			ver[1] = vCopy[iCopy[initialize2 * 3 + 1]].pos;
			ver[2] = vCopy[iCopy[initialize2 * 3 + 2]].pos;

			bool hit;
			float dist;
			hit = D3DXIntersectTri(&ver[0], &ver[1], &ver[2], &data->start, &data->dir, NULL, NULL, &dist);

			//�Փ˔���
			if (hit && dist < data->dist)
			{
				data->hit = true;
				data->dist = dist;

				//�O��
				D3DXVECTOR3 v1 = ver[2] - ver[0];
				D3DXVECTOR3 v2 = ver[2] - ver[1];
				D3DXVec3Cross(&data->normal, &v1, &v2);

				//���K��
				D3DXVec3Normalize(&data->normal, &data->normal);
			}
			initialize2++;
		}

		//�R�s�[���I������烍�b�N���O��
		_indexBuffer[initialize]->Unlock();
		initialize++;
		initialize2 = 0;
	}
	initialize = 0;
	initialize2 = 0;

	//�R�s�[���I������烍�b�N���O��
	_vertexBuffer->Unlock();
}

//�m�[�h�̓��e�`�F�b�N
void Fbx::CheckNode(FbxNode *pNode)
{
	//�m�[�h�̃^�C�v���擾
	FbxNodeAttribute *attr = pNode->GetNodeAttribute();

	//���b�V���m�[�h
	if (attr->GetAttributeType() == FbxNodeAttribute::eMesh)
	{
		//�}�e���A���̐����擾���Ă��̕��z����쐬
		materialCount = pNode->GetMaterialCount();
		_material = new D3DMATERIAL9[materialCount];

		//�e�N�X�`�����}�e���A�����̔z��ō쐬
		_pTexture = new LPDIRECT3DTEXTURE9[materialCount];

		//�}�e���A�����ǂݍ���
		while (initialize < materialCount)
		{
			//�����o�[�g
			FbxSurfaceLambert *lambert = (FbxSurfaceLambert*)pNode->GetMaterial(initialize);
			
			//�f�B�t���[�Y
			FbxDouble3 diffuse = lambert->Diffuse;
			
			//�A���r�G���g
			FbxDouble3 ambient = lambert->Ambient;

			//�z������������Ċi�[
			ZeroMemory(&_material[initialize], sizeof(D3DMATERIAL9));
			_material[initialize].Diffuse.r = (float)diffuse[0];
			_material[initialize].Diffuse.g = (float)diffuse[1];
			_material[initialize].Diffuse.b = (float)diffuse[2];
			_material[initialize].Diffuse.a = 1.0f;
			_material[initialize].Ambient.r = (float)ambient[0];
			_material[initialize].Ambient.g = (float)ambient[1];
			_material[initialize].Ambient.b = (float)ambient[2];
			_material[initialize].Ambient.a = 1.0f;

			//�e�N�X�`���̏��Ɖ摜�t�@�C���̏����擾
			FbxProperty lProperty = pNode->GetMaterial(initialize)->FindProperty(FbxSurfaceMaterial::sDiffuse);
			FbxFileTexture *textureFile = lProperty.GetSrcObject<FbxFileTexture>(0);

			//�e�N�X�`�����\���Ă��Ȃ�
			if (textureFile == NULL)
			{
				_pTexture[initialize] = NULL;
			}
			else
			{
				//�摜�t�@�C���ǂݍ���
				const char *textureFileName = textureFile->GetFileName();

				//�摜�̃t�@�C�����͐�΃p�X�œ����Ă��邽�ߕϊ����Ȃ���΂Ȃ�Ȃ�
				//�������t�@�C���̊K�w�͂��ꂼ��قȂ�̂Ńt�@�C�����Ɗg���q�����擾����
				//���ꂾ���𗘗p����
				char name[_MAX_FNAME];
				char ext[_MAX_EXT];

				//�p�X�𕪊�
				_splitpath_s(textureFileName, NULL, 0, NULL, 0, name, _MAX_FNAME, ext, _MAX_EXT);
				
				//����
				wsprintf(name, "%s%s", name, ext);

				//�e�N�X�`���I�u�W�F�N�g�̍쐬
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
		//�ċA�ł���ɂ��̉��̊K�w�����ׂ�
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

//���b�V���m�[�h����
void Fbx::CheckMesh(FbxMesh *pMesh)
{
	//���_���擾
	vertexCount = pMesh->GetControlPointsCount();

	//�|���S�����擾
	polygonCount = pMesh->GetPolygonCount();

	//�C���f�b�N�X���擾
	indexCount = pMesh->GetPolygonVertexCount();

	//���_���ǂݍ���
	FbxVector4 *pVertexPos = pMesh->GetControlPoints();

	//Vertex�\���̍쐬
	Vertex *vertexList = new Vertex[vertexCount];

	//�R�s�[
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
		//�|���S�����ǂ̒��_�ŏo���Ă��邩�擾
		int startIndex = pMesh->GetPolygonVertexIndex(initialize);

		//�O�p�`��3�̒��_�����[�v
		while (initialize2 < 3)
		{
			//���_�ԍ��ꗗ�擾
			int index = pMesh->GetPolygonVertices()[startIndex + initialize2];

			//�@���̎擾���Ċi�[
			FbxVector4 Normal;
			pMesh->GetPolygonVertexNormal(initialize, initialize2, Normal);
			vertexList[index].normal = D3DXVECTOR3((float)Normal[0], (float)Normal[1], (float)Normal[2]);
			
			//UV�̏����擾����X��Y�ɕ������Ċi�[
			FbxVector2 uv = pMesh->GetLayer(0)->GetUVs()->GetDirectArray().GetAt(index);
			vertexList[index].uv = D3DXVECTOR2((float)uv.mData[0], (float)(1.0 - uv.mData[1]));

			initialize2++;
		}
		initialize++;
		initialize2 = 0;
	}
	initialize = 0;
	initialize2 = 0;

	// �|�C���^������sizeof * �J�E���g
	g.pDevice->CreateVertexBuffer(sizeof(Vertex)* vertexCount, 0, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, D3DPOOL_MANAGED, &_vertexBuffer, 0);

	//�o�b�t�@�����b�N
	//�f�[�^���R�s�[����ɂ̓��b�N���Ȃ��Ƃ����Ȃ�
	Vertex *vCopy;
	_vertexBuffer->Lock(0, 0, (void**)&vCopy, 0);

	//�f�[�^���R�s�[
	memcpy(vCopy, vertexList, sizeof(Vertex)* vertexCount);

	//�R�s�[���I������烍�b�N���O��
	_vertexBuffer->Unlock();

	//���
	delete[] vertexList;

	//�C���f�b�N�X�o�b�t�@�̔z����쐬
	_indexBuffer = new IDirect3DIndexBuffer9*[materialCount];

	//�}�e���A�����Ƃ̃|���S����������z����쐬
	polygonCountOfMaterial = new int[materialCount];

	while (initialize < materialCount)
	{
		//�C���f�b�N�X�̔z����쐬
		int *indexList = new int[indexCount];
		int count = 0;
		while (initialize2 < polygonCount)
		{
			//�}�e���A�����Ƃ̃C���f�b�N�X�����擾
			int materialID = pMesh->GetLayer(0)->GetMaterials()->GetIndexArray().GetAt(initialize2);
			if (materialID == initialize)
			{
				//�C���f�b�N�X���i�[
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

		//�|���S�������擾
		//�O�p�`�ō���Ă���̂�3�Ŋ���
		polygonCountOfMaterial[initialize] = count / 3;

		// �|�C���^������sizeof * �J�E���g
		g.pDevice->CreateIndexBuffer(sizeof(int)* indexCount, 0, D3DFMT_INDEX32, D3DPOOL_MANAGED, &_indexBuffer[initialize], 0);
		
		//�o�b�t�@�����b�N
		//�f�[�^���R�s�[����ɂ̓��b�N���Ȃ��Ƃ����Ȃ�
		DWORD *iCopy;
		_indexBuffer[initialize]->Lock(0, 0, (void**)&iCopy, 0);

		//�f�[�^���R�s�[
		memcpy(iCopy, indexList, sizeof(int)* indexCount);

		//�R�s�[���I������烍�b�N���O��
		_indexBuffer[initialize]->Unlock();

		//���
		delete[] indexList;
		initialize++;
	}
	initialize = 0;
}