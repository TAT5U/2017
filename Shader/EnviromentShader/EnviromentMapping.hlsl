////�O���[�o���ϐ�
////const �Ƃ��Ȃ�����
//float4x4 matWorld;				//���[���h�s��
//float4x4 matView;				//�r���[�s��
//float4x4 matProj;				//�v���W�F�N�V�����s��
//float4x4 matRotate;				//��]�s��
//float3 vecCam;					//�J�����̈ʒu(���_)
//float3 vecLightDir;				//���C�g�̌���
//texture texDecal;				//�e�N�X�`��
//texture texNormal;				//�m�[�}���e�N�X�`��
//float4 speculerColor;			//Maya�ɓ����Ă���n�C���C�g�̏��
//float speculerSize;				//�n�C���C�g�̑傫��
//float4 diffuseColor;
//textureCUBE texCube;			//�p�m���}�摜������ϐ�
//
////�e�N�X�`���̓\����̐ݒ�
//sampler SamplerDecal = sampler_state
//{
//	Texture = <texDecal>;		//�ǂ̃e�N�X�`���ɓ\��̂�
//	//�o�C���j�A�⊮(�ד��m�̃s�N�Z���̕��ς�����ăW���M��Ȃ�����)
//	//LINEAR�ł͂Ȃ�POINT�ɂ���ƃj�A���X�g�l�C�o�[
//	//���ʂ�LINEAR
//	MipFilter = LINEAR;
//	MinFilter = LINEAR;
//	MagFilter = LINEAR;
//};
////�m�[�}���e�N�X�`���̐ݒ�
//sampler SamplerNormal = sampler_state
//{
//	Texture = <texNormal>;		//�ǂ̃e�N�X�`���ɓ\��̂�
//	//�o�C���j�A�⊮(�ד��m�̃s�N�Z���̕��ς�����ăW���M��Ȃ�����)
//	//LINEAR�ł͂Ȃ�POINT�ɂ���ƃj�A���X�g�l�C�o�[
//	//���ʂ�LINEAR
//	MipFilter = LINEAR;
//	MinFilter = LINEAR;
//	MagFilter = LINEAR;
//};
////Cube
//sampler SamplerCube = sampler_state
//{
//	Texture = <texCube>;		//�ǂ̃e�N�X�`���ɓ\��̂�
//	MipFilter = LINEAR;
//	MinFilter = LINEAR;
//	MagFilter = LINEAR;
//};
////���_�V�F�[�_�̍\����
//struct ShaderOUT
//{
//	float4 pos : SV_POSITION;					//�ʒu
//	//float4 normal : NORMAL;						//�@�����
//	//TEXCOORD�̓Z�}���e�B�N�X���Ȃ��Ƃ��Ɏg��
//	float4 eye : TEXCOORD1;						//�����x�N�g��
//	float2 uv : TEXCOORD0;						//uv���
//	float4 light:TEXCOORD2;						//���C�g�̃x�N�g��
//};
//
//
////���_�V�F�[�_�[
////�e���_����ʂ̂ǂ��ɗ���̂�
////�����F���_�̏��(�ʒu�E�@���EUV���W�E�Fetc..)
////�߂�l�F���_�̈ʒu
////float4:float�^�S���܂Ƃ߂�����
//ShaderOUT VS(float4 pos:POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD0, float3 tangent : TEXCOORD1)	//�Z�}���e�B�N�X(�����ɂ���ϐ����Ȃɂ�����킷��)
//{
//	ShaderOUT outData;
//	float4 outPos = pos;
//		outPos = mul(outPos, matWorld);						//���[�J�����W�Ƀ��[���h�s���������̂Ń��[���h�s�񂪑�������
//	outPos = mul(outPos, matView);							//���[���h�r���[�s���������
//	outPos = mul(outPos, matProj);							//�v���W�F�N�V�����s���������
//	outData.pos = outPos;
//
//	float3 binormal = cross(tangent, normal);			//�ڐ��Ɩ@���̊O�ς���]�@�������߂�
//		////�x�N�g���𐳋K��(�x�N�g���̒�����1�ɂ���)
//		//light = normalize(light);
//		normal = mul(float4(normal, 0), matRotate);			//�@�����܂킷���߁A��]�s���������
//
//	tangent = mul(float4(tangent, 0), matRotate);
//	binormal = mul(float4(binormal, 0), matRotate);
//	////outData.color = dot(normal, light);					//�@���ƌ��x�N�g���̓��ς���
//	////outData.color.a = 1;
//
//	float4 worldPos = mul(pos, matWorld);					//���_�̈ʒu���擾
//		//�����x�N�g�������߂�
//		//���������K�v�Ȃ̂Ő��K������
//		float3 eye = normalize(float4(vecCam, 0) - worldPos);	//����ʒu-���钸�_�̈ʒu=�����x�N�g��
//		outData.eye.x = dot(eye, tangent);
//	outData.eye.y = dot(eye, binormal);
//	outData.eye.z = dot(eye, normal);
//	outData.eye.w = 0;
//
//	//float4 light = float4(1, -1, 1, 0);					//���̌���(�����O�����������)
//	float4 light = float4(vecLightDir, 0);					//���C�g�̌���
//		//�x�N�g���𐳋K��(�x�N�g���̒�����1�ɂ���)
//		light = normalize(light);
//
//	outData.light.x = dot(light, tangent);
//	outData.light.y = dot(light, binormal);
//	outData.light.z = dot(light, normal);
//	outData.light.w = 0;
//
//
//	outData.uv = uv;										//�s�N�Z���V�F�[�_�[��uv�����̂܂ܓn�����
//
//	return outData;
//}
//
////�@��//////////////////////////////////////
////float4 VS(float4 nor:NORMAL):SV_NORMAL
//
//
//
////�s�N�Z���V�F�[�_�[(�@���}�b�v�Ȃ�
////�s�N�Z�����Ƃɉ��F�ɂ��邩
////�F��RGBA�ł���킷
////�����F���_�V�F�[�_�[�̖߂�l(�e���_����ʏ�̂ǂ��ɂ��邩)
////�߂�l�F�e�s�N�Z���̐F
//float4 PS(ShaderOUT inShaderData) : COLOR
//{
//
//
//	float3 normal = float3(0, 0, 1);			//�@���̕ϐ�
//
//	//���˃x�N�g�������߂�
//	//�@���ƃ��C�g�̓��ς����߂�
//	float4 NL = saturate(dot(float4(normal, 0), -inShaderData.light));
//	//���̎��Ŕ��˃x�N�g�������܂�
//	//���˃x�N�g��=2*�@���ƃx�N�g���̓���*�@��-�x�N�g��
//	//float4 refrect = normalize(2 * NL * inShaderData.normal - light);
//	//���˃x�N�g�������߂�֐�
//	float4 ref = reflect(inShaderData.light, float4(normal, 0));
//	//�n�C���C�g�̃T�C�Y
//	float speculerPower = 1.0f;								//�n�C���C�g�̋���(���ʔ��˗�)
//
//
//	//�n�C���C�g=���ʔ��˗�*���̋���*(���˃x�N�g���E����)^�T�C�Y
//	//saturate�͓��ς����߂�Ƃ����Ă������ق����悢(0�`1�ɐ؂�l�߂邽��)
//	float4 speculer = speculerPower * pow(saturate(dot(ref, inShaderData.eye)), speculerSize)*speculerColor;
//		//�e�N�X�`����\��
//		float4 color = NL * diffuseColor + speculer;										//�@���ƌ��x�N�g���̓��ς���
//		color.a = 1;
//
//	return color;		//�n�C���C�g�𑫂��ĕԂ�
//}
////�s�N�Z���V�F�[�_�[(�@���}�b�v����
////�s�N�Z�����Ƃɉ��F�ɂ��邩
////�F��RGBA�ł���킷
////�����F���_�V�F�[�_�[�̖߂�l(�e���_����ʏ�̂ǂ��ɂ��邩)
////�߂�l�F�e�s�N�Z���̐F
//float4 PS_N(ShaderOUT inShaderData) : COLOR
//{
//
//
//	float3 normal = tex2D(SamplerNormal, inShaderData.uv)*2.0f - 1.0f;			//�@���̕ϐ�
//
//	//���˃x�N�g�������߂�
//	//�@���ƃ��C�g�̓��ς����߂�
//	float4 NL = saturate(dot(float4(normal, 0), -inShaderData.light));
//	//���̎��Ŕ��˃x�N�g�������܂�
//	//���˃x�N�g��=2*�@���ƃx�N�g���̓���*�@��-�x�N�g��
//	//float4 refrect = normalize(2 * NL * inShaderData.normal - light);
//	//���˃x�N�g�������߂�֐�
//	float4 ref = reflect(inShaderData.light, float4(normal, 0));
//	//�n�C���C�g�̃T�C�Y
//	float speculerPower = 1.0f;								//�n�C���C�g�̋���(���ʔ��˗�)
//
//
//	//�n�C���C�g=���ʔ��˗�*���̋���*(���˃x�N�g���E����)^�T�C�Y
//	//saturate�͓��ς����߂�Ƃ����Ă������ق����悢(0�`1�ɐ؂�l�߂邽��)
//	float4 speculer = speculerPower * pow(saturate(dot(ref, inShaderData.eye)), speculerSize)*speculerColor;
//		//�e�N�X�`����\��
//		float4 color = NL * diffuseColor + speculer;										//�@���ƌ��x�N�g���̓��ς���
//		color.a = 1;
//
//	return color;		//�n�C���C�g�𑫂��ĕԂ�
//}
//
////�s�N�Z���V�F�[�_�[(�@���}�b�v�Ȃ�
////�s�N�Z�����Ƃɉ��F�ɂ��邩
////�F��RGBA�ł���킷
////�����F���_�V�F�[�_�[�̖߂�l(�e���_����ʏ�̂ǂ��ɂ��邩)
////�߂�l�F�e�s�N�Z���̐F
//float4 PS_T(ShaderOUT inShaderData) : COLOR
//{
//
//	//tex2d�͂��̃e�N�X�`���̐F���擾�ł���
//	float3 normal = float3(0, 0, 1);			//�@���̕ϐ�
//
//	//���˃x�N�g�������߂�
//	//�@���ƃ��C�g�̓��ς����߂�
//	float4 NL = saturate(dot(float4(normal, 0), -inShaderData.light));
//	//���̎��Ŕ��˃x�N�g�������܂�
//	//���˃x�N�g��=2*�@���ƃx�N�g���̓���*�@��-�x�N�g��
//	//float4 refrect = normalize(2 * NL * inShaderData.normal - light);
//	//���˃x�N�g�������߂�֐�
//	float4 ref = reflect(inShaderData.light, float4(normal, 0));
//	//�n�C���C�g�̃T�C�Y
//	float speculerPower = 1.0f;								//�n�C���C�g�̋���(���ʔ��˗�)
//
//
//	//�n�C���C�g=���ʔ��˗�*���̋���*(���˃x�N�g���E����)^�T�C�Y
//	//saturate�͓��ς����߂�Ƃ����Ă������ق����悢(0�`1�ɐ؂�l�߂邽��)
//	float4 speculer = speculerPower * pow(saturate(dot(ref, inShaderData.eye)), speculerSize)*speculerColor;
//		//�e�N�X�`����\��
//		float4 color = NL * (tex2D(SamplerDecal, inShaderData.uv) + speculer);										//�@���ƌ��x�N�g���̓��ς���
//		color.a = tex2D(SamplerDecal, inShaderData.uv).a;
//
//	return color;		//�n�C���C�g�𑫂��ĕԂ�
//}
//
////�s�N�Z���V�F�[�_�[(�@���}�b�v����
////�s�N�Z�����Ƃɉ��F�ɂ��邩
////�F��RGBA�ł���킷
////�����F���_�V�F�[�_�[�̖߂�l(�e���_����ʏ�̂ǂ��ɂ��邩)
////�߂�l�F�e�s�N�Z���̐F
//float4 PS_T_N(ShaderOUT inShaderData) : COLOR
//{
//
//	//tex2d�͂��̃e�N�X�`���̐F���擾�ł���
//	float3 normal = tex2D(SamplerNormal, inShaderData.uv)*2.0f - 1.0f;			//�@���̕ϐ�
//
//	//���˃x�N�g�������߂�
//	//�@���ƃ��C�g�̓��ς����߂�
//	float4 NL = saturate(dot(float4(normal, 0), -inShaderData.light));
//
//	//�����̔��˃x�N�g�������߂�
//	float3 refEye = reflect(inShaderData.eye, normal);
//
//	//���̎��Ŕ��˃x�N�g�������܂�
//	//���˃x�N�g��=2*�@���ƃx�N�g���̓���*�@��-�x�N�g��
//	//float4 refrect = normalize(2 * NL * inShaderData.normal - light);
//	//���˃x�N�g�������߂�֐�
//	float4 ref = reflect(inShaderData.light, float4(normal, 0));
//	//�n�C���C�g�̃T�C�Y
//	float speculerPower = 1.0f;								//�n�C���C�g�̋���(���ʔ��˗�)
//
//
//	//�n�C���C�g=���ʔ��˗�*���̋���*(���˃x�N�g���E����)^�T�C�Y
//	//saturate�͓��ς����߂�Ƃ����Ă������ق����悢(0�`1�ɐ؂�l�߂邽��)
//	float4 speculer = speculerPower * pow(saturate(dot(ref, inShaderData.eye)), speculerSize)*speculerColor;
//	////�e�N�X�`����\��
//	float4 color = NL * (tex2D(SamplerDecal, inShaderData.uv) + speculer) + texCUBE(SamplerCube, refEye)*0.5;										//�@���ƌ��x�N�g���̓��ς���
//	//float4 color=texCUBE(SamplerCube,refEye);
//		color.a = tex2D(SamplerDecal, inShaderData.uv).a;
//
//	return color;		//�n�C���C�g�𑫂��ĕԂ�
//}
//
//technique
//{
//	pass
//	{
//		//���_�V�F�[�_�[�̃o�[�W����3.0�ŃR���p�C��
//		VertexShader = compile vs_3_0 VS();
//		//�s�N�Z���V�F�[�_�[�̃o�[�W����3.0�ŃR���p�C��
//		PixelShader = compile ps_3_0 PS();
//	}
//
//	pass
//	{
//		//���_�V�F�[�_�[�̃o�[�W����3.0�ŃR���p�C��
//		VertexShader = compile vs_3_0 VS();
//		//�s�N�Z���V�F�[�_�[�̃o�[�W����3.0�ŃR���p�C��
//		PixelShader = compile ps_3_0 PS_T();
//	}
//	pass
//	{
//		//���_�V�F�[�_�[�̃o�[�W����3.0�ŃR���p�C��
//		VertexShader = compile vs_3_0 VS();
//		//�s�N�Z���V�F�[�_�[�̃o�[�W����3.0�ŃR���p�C��
//		PixelShader = compile ps_3_0 PS_N();
//	}
//
//	pass
//	{
//		//���_�V�F�[�_�[�̃o�[�W����3.0�ŃR���p�C��
//		VertexShader = compile vs_3_0 VS();
//		//�s�N�Z���V�F�[�_�[�̃o�[�W����3.0�ŃR���p�C��
//		PixelShader = compile ps_3_0 PS_T_N();
//	}
//}


// �O���[�o���ϐ�
// �s��
float4x4 matWorld, matView, matProj, matRotate;
float4 vecCam, vecLightDir, speculerColor, diffuseColor;
float speculerSize;
texture texDecal, texNormal;

// �p�m���}�摜
textureCUBE texCube;


// �e�N�X�`���̐ݒ�
// �j�A���X�g���C�o�[(�ł��߂��s�N�Z���̐F�ɂ���)
// ���x�͑������A�W���M�[����������
// �o�C���j�A�⊮(���ϐF�ɂ���)
// ���炩�ɂ��ă\�t�g�ɂ���
sampler SamplerDecal = sampler_state
{
	Texture = <texDecal>;

	// �j�A���X�g���C�o�[ = LINEAR
	// �o�C���j�A�⊮     = POINT
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

//�m�[�}���e�N�X�`���̐ݒ�
sampler SamplerNormal = sampler_state
{
	Texture = <texNormal>;

	// �j�A���X�g���C�o�[ = LINEAR
	// �o�C���j�A�⊮     = POINT
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

//�p�m���}�̐ݒ�
sampler SamplerCube = sampler_state
{
	// �j�A���X�g���C�o�[ = LINEAR
	// �o�C���j�A�⊮     = POINT
	Texture = <texCube>;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};


// �\����
// �ʒu�E�@���E�����EUV
// �V�F�[�_�Ŏg�p����̂ŃZ�}���e�B�N�X�ŋL�q����
struct ShaderOUT
{
	float4 pos    : SV_POSITION;
	//float4 normal : NORMAL;
	float4 eye    : TEXCOORD1;
	float2 uv	  : TEXCOORD0;
	float4 light  : TEXCOORD2;
};


// ���_�V�F�[�_�[
// ���_�̏��������ɂ��Ă��̕ϐ��ɒ��_���i�[����
// SV_POSITION�ŃX�N���[���̈ʒu��ݒ肷��
// �L�q�@ : �Z�}���e�B�N�X
// �ʒu�E�@���EUV�E�^���W�F���g
ShaderOUT VS(float4 pos : POSITION, float4 normal : NORMAL, float2 uv : TEXCOORD0, float4 tangent : TEXCOORD1)
{
	// �\����
	ShaderOUT shaderData;

	// �Z�b�g����ϐ�
	// WXYZ or RGBA
	float4 outPos = pos;

		// �e���W���Z�b�g����
		outPos = mul(outPos, matWorld);
	outPos = mul(outPos, matView);
	outPos = mul(outPos, matProj);

	float3 biNormal = cross(tangent, normal);
		normal = mul(normal, matRotate);
	tangent = mul(tangent, matRotate);

	// float3��float4�Ŏg�p����ꍇ��
	// �L���X�g�����ۂ�w�̒l��0�ɂ��ď��������s��
	biNormal = mul(float4(biNormal, 0), matRotate);

	// �����I�ɐݒ�
	normal.w = 0;
	tangent.w = 0;

	// �ʒu���\���̂Ɋi�[
	shaderData.pos = outPos;

	// �@�����\���̂Ɋi�[
	//shaderData.normal = normal;

	// �����I�ɐݒ�
	//shaderData.normal.w = 0;

	// ���[���h���W
	float4 worldPos = mul(pos, matWorld);

		// �����𐳋K��
		//shaderData.eye = normalize(vecCam - worldPos);

		// �΂߂��猩���Ƃ��̎����x�N�g����ݒ�
		float4 eye = normalize(vecCam - worldPos);
		shaderData.eye.x = dot(eye, tangent);
	shaderData.eye.y = dot(eye, biNormal);
	shaderData.eye.z = dot(eye, normal);
	shaderData.eye.w = 0;

	// ���̃x�N�g��
	float4 light = vecLightDir;

		// �����I�ɐݒ�
		light.w = 0;

	// ���K��
	light = normalize(light);

	shaderData.light.x = dot(light, tangent);
	shaderData.light.y = dot(light, biNormal);
	shaderData.light.z = dot(light, normal);
	shaderData.light.w = 0;

	shaderData.uv = uv;

	return shaderData;
}


// �e�N�X�`���E�@���}�b�v�Ȃ�
// �s�N�Z���V�F�[�_�[
// ���_�V�F�[�_�Őݒ肵���\���̂������ɂ���
// �\���̂̐F�̕����݂̂�Ԃ�
float4 PS(ShaderOUT inShaderData) : COLOR
{
	float4 normal = float4(0, 0, 1, 0);

	// ���ς����߂Ċi�[
	// �@���E���C�g�̋t�̃x�N�g��
	float4 NL = saturate(dot(normal, -inShaderData.light));

	// ���˃x�N�g��
	float4 reflection = reflect(inShaderData.light, normal);

	// ���ʔ��˗�
	float speculerPower = 1.0f;

	// �n�C���C�g
	// saturate�œ��ς�؂�l��
	float4 speculer = speculerPower * pow(saturate(dot(reflection, inShaderData.eye)), speculerSize) * speculerColor;

	// ���߂��l���e�N�X�`���ɔ��f
	float4 color = NL * diffuseColor + speculer;

	// �����I�ɐݒ�
	color.a = 1;

	return color;
}

// �e�N�X�`������E�@���}�b�v�Ȃ�
float4 PS_Texture(ShaderOUT inShaderData) : COLOR
{
	float4 normal = float4(0, 0, 1, 0);

	// ���ς����߂Ċi�[
	// �@���E���C�g�̋t�̃x�N�g��
	float4 NL = saturate(dot(normal, -inShaderData.light));

	// ���˃x�N�g��
	float4 reflection = reflect(inShaderData.light, normal);

	// ���ʔ��˗�
	float speculerPower = 1.0f;

	// �n�C���C�g
	// saturate�œ��ς�؂�l��
	float4 speculer = speculerPower * pow(saturate(dot(reflection, inShaderData.eye)), speculerSize) * speculerColor;

	// ���߂��l���e�N�X�`���ɔ��f
	float4 color = NL * tex2D(SamplerDecal, inShaderData.uv) + speculer;

	// �����I�ɐݒ�
	color.a = tex2D(SamplerDecal, inShaderData.uv).a;

	return color;
}

// �e�N�X�`���Ȃ��E�@���}�b�v����
float4 PS_Normal(ShaderOUT inShaderData) : COLOR
{
	float4 normal = tex2D(SamplerNormal, inShaderData.uv)*2.0f - 1.0f;
	normal.w = 0;

	// ���ς����߂Ċi�[
	// �@���E���C�g�̋t�̃x�N�g��
	float4 NL = saturate(dot(normal, -inShaderData.light));

	// ���˃x�N�g��
	float4 reflection = reflect(inShaderData.light, normal);

	// ���ʔ��˗�
	float speculerPower = 1.0f;

	// �n�C���C�g
	// saturate�œ��ς�؂�l��
	float4 speculer = speculerPower * pow(saturate(dot(reflection, inShaderData.eye)), speculerSize) * speculerColor;

	// ���߂��l���e�N�X�`���ɔ��f
	float4 color = NL * diffuseColor + speculer;

	// �����I�ɐݒ�
	color.a = 1;

	return color;
}

// �e�N�X�`���E�@���}�b�v����
float4 PS_TextureNormal(ShaderOUT inShaderData) : COLOR
{
	float4 normal = tex2D(SamplerNormal, inShaderData.uv)*2.0f - 1.0f;
	normal.w = 0;

	// ���ς����߂Ċi�[
	// �@���E���C�g�̋t�̃x�N�g��
	float4 NL = saturate(dot(normal, -inShaderData.light));

	// ���˃x�N�g��
	float4 reflectionEye = reflect(inShaderData.eye, normal);
	reflectionEye.w = 0;
	float4 reflection = reflect(inShaderData.light, normal);

	// ���ʔ��˗�
	float speculerPower = 1.0f;

	// �n�C���C�g
	// saturate�œ��ς�؂�l��
	float4 speculer = speculerPower * pow(saturate(dot(reflection, inShaderData.eye)), speculerSize) * speculerColor;

	// ���߂��l���e�N�X�`���ɔ��f
	float4 color = NL * (tex2D(SamplerDecal, inShaderData.uv) + speculer) + texCUBE(SamplerCube, reflectionEye) * 0.5;

	// �����I�ɐݒ�
	color.a = tex2D(SamplerDecal, inShaderData.uv).a;

	return color;
}


// �p�X�̏��Ԃɂ���ĕ`�悪�ς��̂Œ���
technique
{
	pass
	{
		// GPU�̃V�F�[�_�[�̃o�[�W�������w��
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();
	}

	pass
	{
		// GPU�̃V�F�[�_�[�̃o�[�W�������w��
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS_Texture();
	}
	pass
	{
		// GPU�̃V�F�[�_�[�̃o�[�W�������w��
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS_Normal();
	}

	pass
	{
		// GPU�̃V�F�[�_�[�̃o�[�W�������w��
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS_TextureNormal();
	}
}
