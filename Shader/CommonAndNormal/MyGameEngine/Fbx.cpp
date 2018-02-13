/*Fbx.cpp*/

/****�C���N���[�h****/
#include "Fbx.h"
#include "Camera.h"
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

	initialize = 0;
	initialize2 = 0;
	initialize3 = 0;
	nodeCount = 0;
	vertexCount = 0;
	polygonCount = 0;
	indexCount = 0;
	materialCount = 0;

	_materialData = nullptr;
}

//�f�X�g���N�^
Fbx::~Fbx()
{
	//�������

	//�z��Ȃ̂�1��1��Release���Ă���delete����
	while (initialize < materialCount)
	{
		SAFE_RELEASE(_materialData[initialize].indexBuffer);
		initialize++;
	}
	initialize = 0;
	delete[] _materialData;

	SAFE_RELEASE(_vertexBuffer);
	_manager->Destroy();
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

	// �m�[�}���}�b�s���O�Ŏg�p
	//D3DXCreateTextureFromFileEx(g.pDevice, "Assets/Normal.png", 0, 0, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, NULL, NULL, NULL, &_materialData[materialCount].normalTexture);
}

//�`�揈��
void Fbx::Draw()
{
	//���_�o�b�t�@���Z�b�g
	g.pDevice->SetStreamSource(0, _vertexBuffer, 0, sizeof(Vertex));

	//���̏��Ȃ̂�
	//�ʒu�Ɩ@����UV���W
	g.pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_TEX2);

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

	// �J�����̃x�N�g�����擾���ăZ�b�g
	// ���l�Ɠ����悤��w�l�������I�ɐݒ肷��
	D3DXVECTOR4 cameraVect = g.pCamera->GetPosition();
	cameraVect.w = 0;
	_shader->SetVector("vecCam", (D3DXVECTOR4*)&cameraVect);

	// ���C�g���擾���Đݒ�
	D3DLIGHT9 lightDir;
	g.pDevice->GetLight(0, &lightDir);
	_shader->SetVector("vecLightDir", (D3DXVECTOR4*)&lightDir.Direction);

	// �V�F�[�_�[��K�p(�����_�����O�J�n)
	_shader->Begin(NULL, 0);

	//�}�e���A���������[�v
	while (initialize < materialCount)
	{
		g.pDevice->SetIndices(_materialData[initialize].indexBuffer);
		g.pDevice->SetMaterial(&_materialData[initialize].material);

		//�e�N�X�`����I��
		//g.pDevice->SetTexture(0, _pTexture[initialize]);

		_shader->SetTexture("texDecal", _materialData[initialize].texture);
		_shader->SetTexture("texNormal", _materialData[initialize].normalTexture);

		_shader->SetVector("speculerColor", (D3DXVECTOR4*)&_materialData[initialize].material.Specular);
		_shader->SetVector("diffuseColor", (D3DXVECTOR4*)&_materialData[initialize].material.Diffuse);

		_shader->SetFloat("speculerSize", _materialData[initialize].material.Power);

		// ���[�v���ɓ���邱�Ƃ�
		// 1�̕`��ɐ������K�p�����(�����邱�Ƃ��ł���)
		_shader->BeginPass(_materialData[initialize].shaderPass);

		//�`��
		//���_��
		//�}�e���A�����Ƃ̃|���S����
		g.pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, _materialData[initialize].polygonCountOfMaterial);

		_shader->EndPass();

		initialize++;
	}
	initialize = 0;

	// �J�n������K���I��������
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
		_materialData[initialize].indexBuffer->Lock(0, 0, (void**)&iCopy, 0);

		while (initialize2 < _materialData[initialize].polygonCountOfMaterial)
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
		_materialData[initialize].indexBuffer->Unlock();
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
		//_material = new D3DMATERIAL9[materialCount];

		////�e�N�X�`�����}�e���A�����̔z��ō쐬
		//_pTexture = new LPDIRECT3DTEXTURE9[materialCount];

		_materialData = new MaterialData[materialCount];

		//�}�e���A�����ǂݍ���
		while (initialize < materialCount)
		{
			//�����o�[�g
			FbxSurfacePhong *lambert = (FbxSurfacePhong*)pNode->GetMaterial(initialize);

			//�f�B�t���[�Y
			FbxDouble3 diffuse = lambert->Diffuse;

			//�A���r�G���g
			FbxDouble3 ambient = lambert->Ambient;

			//�z������������Ċi�[
			ZeroMemory(&_materialData[initialize].material, sizeof(D3DMATERIAL9));
			_materialData[initialize].material.Diffuse.r = (float)diffuse[0];
			_materialData[initialize].material.Diffuse.g = (float)diffuse[1];
			_materialData[initialize].material.Diffuse.b = (float)diffuse[2];
			_materialData[initialize].material.Diffuse.a = 1.0f;

			_materialData[initialize].material.Ambient.r = (float)ambient[0];
			_materialData[initialize].material.Ambient.g = (float)ambient[1];
			_materialData[initialize].material.Ambient.b = (float)ambient[2];
			_materialData[initialize].material.Ambient.a = 1.0f;

			// ClassId => �N���X�̔ԍ����擾
			if (pNode->GetMaterial(initialize)->GetClassId().Is(FbxSurfacePhong::ClassId))
			{
				FbxDouble3 speculer = lambert->Specular;

				_materialData[initialize].material.Specular.r = (float)speculer[0];
				_materialData[initialize].material.Specular.g = (float)speculer[1];
				_materialData[initialize].material.Specular.b = (float)speculer[2];
				_materialData[initialize].material.Specular.a = 1.0f;

				_materialData[initialize].material.Power = (float)lambert->Shininess;
			}


			// �e�N�X�`��
			// TODO: �֐���������
			{
				//�e�N�X�`���̏��Ɖ摜�t�@�C���̏����擾
				FbxProperty lProperty = pNode->GetMaterial(initialize)->FindProperty(FbxSurfaceMaterial::sDiffuse);
				FbxFileTexture *textureFile = lProperty.GetSrcObject<FbxFileTexture>(0);

				//�e�N�X�`�����\���Ă��Ȃ�
				if (textureFile == NULL)
				{
					_materialData[initialize].texture = NULL;
					_materialData[initialize].shaderPass = 0;
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
						D3DX_FILTER_NONE, D3DX_DEFAULT, NULL, NULL, NULL, &_materialData[initialize].texture);

					_materialData[initialize].shaderPass = 1;
				}
			}


			// �@���}�b�v�Ǎ���
			// TODO: �֐���������
			{
				//�e�N�X�`���̏��Ɖ摜�t�@�C���̏����擾
				FbxProperty lProperty = pNode->GetMaterial(initialize)->FindProperty(FbxSurfaceMaterial::sBump);
				FbxFileTexture *textureFile = lProperty.GetSrcObject<FbxFileTexture>(0);

				//�e�N�X�`�����\���Ă��Ȃ�
				if (textureFile == NULL)
				{
					_materialData[initialize].normalTexture = NULL;
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
						D3DX_FILTER_NONE, D3DX_DEFAULT, NULL, NULL, NULL, &_materialData[initialize].normalTexture);

					_materialData[initialize].shaderPass += 2;
				}
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

		D3DXVECTOR3 tangent = CreateTangent(
			&vertexList[pMesh->GetPolygonVertices()[startIndex + 0]].pos,
			&vertexList[pMesh->GetPolygonVertices()[startIndex + 1]].pos,
			&vertexList[pMesh->GetPolygonVertices()[startIndex + 2]].pos,
			&vertexList[pMesh->GetPolygonVertices()[startIndex + 0]].uv,
			&vertexList[pMesh->GetPolygonVertices()[startIndex + 1]].uv,
			&vertexList[pMesh->GetPolygonVertices()[startIndex + 2]].uv);

		//�O�p�`��3�̒��_�����[�v
		while (initialize2 < 3)
		{
			//���_�ԍ��ꗗ�擾
			int index = pMesh->GetPolygonVertices()[startIndex + initialize2];
			vertexList[index].tangent = tangent;

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
	// tangent�Ȃǂ̂Ȃ����D3DFVF_TEX1�Ȃ�(�ԍ��͂ǂ�ǂ�ύX)�ő�p����
	// D3DFVF_TEX1�Ȃǂ̏��Ԃ͐錾����Ă��鏇�Ԃǂ���ɋL�q���Ȃ��Ƃǂꂪ�ǂ�Ȃ̂��킩��Ȃ��Ȃ��Ă��܂�
	g.pDevice->CreateVertexBuffer(sizeof(Vertex)* vertexCount, 0, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_TEX2, D3DPOOL_MANAGED, &_vertexBuffer, 0);

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

	////�C���f�b�N�X�o�b�t�@�̔z����쐬
	//_indexBuffer = new IDirect3DIndexBuffer9*[materialCount];

	////�}�e���A�����Ƃ̃|���S����������z����쐬
	//polygonCountOfMaterial = new int[materialCount];

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
		_materialData[initialize].polygonCountOfMaterial = count / 3;

		// �|�C���^������sizeof * �J�E���g
		g.pDevice->CreateIndexBuffer(sizeof(int)* indexCount, 0, D3DFMT_INDEX32, D3DPOOL_MANAGED, &_materialData[initialize].indexBuffer, 0);
		
		//�o�b�t�@�����b�N
		//�f�[�^���R�s�[����ɂ̓��b�N���Ȃ��Ƃ����Ȃ�
		DWORD *iCopy;
		_materialData[initialize].indexBuffer->Lock(0, 0, (void**)&iCopy, 0);

		//�f�[�^���R�s�[
		memcpy(iCopy, indexList, sizeof(int)* indexCount);

		//�R�s�[���I������烍�b�N���O��
		_materialData[initialize].indexBuffer->Unlock();

		//���
		delete[] indexList;
		initialize++;
	}
	initialize = 0;
}

//���_��񂩂�ڐ��x�N�g�������߂�
//�����Fpos0, pos1, pos2�@	�|���S���̂R���_�̈ʒu
//�����Fuv0, uv1, uv2�@		�|���S���̂R���_�̂t�u���W
//�ߒl�F���̃|���S���̐ڐ�
D3DXVECTOR3 Fbx::CreateTangent(
	D3DXVECTOR3 *pos0, D3DXVECTOR3 *pos1, D3DXVECTOR3 *pos2,
	D3DXVECTOR2 *uv0, D3DXVECTOR2 *uv1, D3DXVECTOR2 *uv2)
{
	D3DXVECTOR3 cp0[3] = {
		D3DXVECTOR3(pos0->x, uv0->x, uv0->y),
		D3DXVECTOR3(pos0->y, uv0->x, uv0->y),
		D3DXVECTOR3(pos0->z, uv0->x, uv0->y)
	};

	D3DXVECTOR3 cp1[3] = {
		D3DXVECTOR3(pos1->x, uv1->x, uv1->y),
		D3DXVECTOR3(pos1->y, uv1->x, uv1->y),
		D3DXVECTOR3(pos1->z, uv1->x, uv1->y)
	};

	D3DXVECTOR3 cp2[3] = {
		D3DXVECTOR3(pos2->x, uv2->x, uv2->y),
		D3DXVECTOR3(pos2->y, uv2->x, uv2->y),
		D3DXVECTOR3(pos2->z, uv2->x, uv2->y)
	};

	float f[3];
	for (int i = 0; i < 3; i++)
	{
		D3DXVECTOR3 v1 = cp1[i] - cp0[i];
		D3DXVECTOR3 v2 = cp2[i] - cp1[i];
		D3DXVECTOR3 cross;
		D3DXVec3Cross(&cross, &v1, &v2);

		f[i] = -cross.y / cross.x;
	}

	D3DXVECTOR3 tangent;
	memcpy(tangent, f, sizeof(float)* 3);
	D3DXVec3Normalize(&tangent, &tangent);
	return tangent;
}

void Fbx::SetShafer(LPD3DXEFFECT setShader)
{
	_shader = setShader;
}