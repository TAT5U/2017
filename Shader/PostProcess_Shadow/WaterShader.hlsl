// �O���[�o���ϐ�
// �s��
float4x4 matWorld, matView, matProj, matRotate;
float4 vecCam, vecLightDir, speculerColor, diffuseColor;
float speculerSize, uvScroll;
texture texDecal, texNormal;

//
float4x4 matLightView, matUV;
texture texShadowMap;


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
	AddressU = WRAP;
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


//
sampler SamplerShadowMap = sampler_state
{
	Texture = <texShadowMap>;

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



	//
	float4 lightTexCoord : TEXCOORD5;
	float4 lightViewPos  : TEXCOORD6;
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




	//
	shaderData.lightViewPos = pos;
	shaderData.lightViewPos = mul(shaderData.lightViewPos, matWorld);
	shaderData.lightViewPos = mul(shaderData.lightViewPos, matLightView);
	shaderData.lightViewPos = mul(shaderData.lightViewPos, matProj);
	shaderData.lightTexCoord = mul(shaderData.lightViewPos, matUV);



	return shaderData;
}


// �e�N�X�`���E�@���}�b�v����
float4 PS_TextureNormal(ShaderOUT inShaderData) : COLOR
{
	float4 normal = (tex2D(SamplerNormal, inShaderData.uv)*2.0f - 1.0f
		+ tex2D(SamplerNormal, inShaderData.uv*1.2f - uvScroll) * 2.0f - 1.0f) / 2;

	normal.w = 0;

	// ���ς����߂Ċi�[
	// �@���E���C�g�̋t�̃x�N�g��
	float4 NL = saturate(dot(normal, -inShaderData.light));

	// ���˃x�N�g��
	float4 reflection = reflect(inShaderData.light, normal);

	// ���ʔ��˗�
	float speculerPower = 20.0f;

	// �n�C���C�g
	// saturate�œ��ς�؂�l��
	float speculer = speculerPower * pow(saturate(dot(reflection, inShaderData.eye)), 2);

	float4 ambient = float4(0.1, 0.1, 0.3, 1);

	// ���߂��l���e�N�X�`���ɔ��f
	float4 color = NL * tex2D(SamplerDecal, inShaderData.uv) + speculer + ambient;

	// �����I�ɐݒ�
	color.a = color.b / 2;




	//
	inShaderData.lightTexCoord /= inShaderData.lightTexCoord.w;
	float texValue = tex2D(SamplerShadowMap, inShaderData.lightTexCoord);
	float lightLength = inShaderData.lightViewPos.z / inShaderData.lightViewPos.w;
	if (texValue + 0.002 < lightLength)
	{
		color.rgb /= 3;
	}



	return color;
}


// �p�X�̏��Ԃɂ���ĕ`�悪�ς��̂Œ���
technique
{
	pass
	{
		// GPU�̃V�F�[�_�[�̃o�[�W�������w��
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS_TextureNormal();
	}
}