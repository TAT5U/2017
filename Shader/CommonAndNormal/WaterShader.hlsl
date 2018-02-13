// �O���[�o���ϐ�
// �s��
float4x4 matWorld, matView, matProj, matRotate;
float4 vecCam, vecLightDir, speculerColor, diffuseColor;
float speculerSize;
texture texDecal, texNormal;

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

	AddressU  = WRAP;
	AddressV = WRAP;
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

// �e�N�X�`���Ȃ��E�@���}�b�v����
// �s�N�Z���V�F�[�_�[
// ���_�V�F�[�_�Őݒ肵���\���̂������ɂ���
// �\���̂̐F�̕����݂̂�Ԃ�
float4 PS_Normal(ShaderOUT inShaderData) : COLOR
{
	float4 normal = tex2D(SamplerNormal, inShaderData.uv)*2.0f - 1.0f;
	normal.w = 0;

	// ���ς����߂Ċi�[
	// �@���E���C�g�̋t�̃x�N�g��
	float4 NL = dot(normal, -inShaderData.light);

	// ���˃x�N�g��
	float4 reflection = reflect(inShaderData.light, normal);

	// ���ʔ��˗�
	float speculerPower = 2.0f;

	// �n�C���C�g
	// saturate�œ��ς�؂�l��
	float speculer = speculerPower * pow(saturate(dot(reflection, inShaderData.eye)), speculerSize) * speculerColor;

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
	//float4 NL = dot(normal, -inShaderData.light);
	float4 NL = dot(normal, -inShaderData.light);

	// ���˃x�N�g��
	float4 reflection = reflect(inShaderData.light, normal);

	// ���ʔ��˗�
	float speculerPower = 2.0f;

	// �n�C���C�g
	// saturate�œ��ς�؂�l��
	float speculer = speculerPower * pow(saturate(dot(reflection, inShaderData.eye)), speculerSize) * speculerColor;

	// ���߂��l���e�N�X�`���ɔ��f
	float4 color = NL;// *tex2D(SamplerDecal, inShaderData.uv) + speculer;

	// �����I�ɐݒ�
	color.a = tex2D(SamplerDecal, inShaderData.uv).a;

	return color;
}

// �e�N�X�`������E�@���}�b�v�Ȃ�
float4 PS_Texture(ShaderOUT inShaderData) : COLOR
{
	float4 normal = float4(0, 0, 1, 0);

	// ���ς����߂Ċi�[
	// �@���E���C�g�̋t�̃x�N�g��
	float4 NL = dot(normal, -inShaderData.light);

	// ���˃x�N�g��
	float4 reflection = reflect(inShaderData.light, normal);

	// ���ʔ��˗�
	float speculerPower = 2.0f;

	// �n�C���C�g
	// saturate�œ��ς�؂�l��
	float speculer = speculerPower * pow(saturate(dot(reflection, inShaderData.eye)), speculerSize) * speculerColor;

	// ���߂��l���e�N�X�`���ɔ��f
	float4 color = NL * tex2D(SamplerDecal, inShaderData.uv) + speculer;

	// �����I�ɐݒ�
	color.a = tex2D(SamplerDecal, inShaderData.uv).a;

	return color;
}


// �e�N�X�`���E�@���}�b�v�Ȃ�
float4 PS(ShaderOUT inShaderData) : COLOR
{
	float4 normal = float4(0, 0, 1, 0);

	// ���ς����߂Ċi�[
	// �@���E���C�g�̋t�̃x�N�g��
	float4 NL = dot(normal, -inShaderData.light);

	// ���˃x�N�g��
	float4 reflection = reflect(inShaderData.light, normal);

	// ���ʔ��˗�
	float speculerPower = 2.0f;

	// �n�C���C�g
	// saturate�œ��ς�؂�l��
	float speculer = speculerPower * pow(saturate(dot(reflection, inShaderData.eye)), speculerSize) * speculerColor;

	// ���߂��l���e�N�X�`���ɔ��f
	float4 color = NL * diffuseColor + speculer;

	// �����I�ɐݒ�
	color.a = 1;

	return color;
}


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