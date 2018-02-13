// �O���[�o���ϐ�
// �s��
float4x4 matWorld, matView, matProj, matRotate;
float4 vecCam, vecLightDir, speculerColor, diffuseColor;
float speculerSize;
texture texDecal, texToon;


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

sampler SamplerToon = sampler_state
{
	Texture = <texToon>;

	// �j�A���X�g���C�o�[ = LINEAR
	// �o�C���j�A�⊮     = POINT
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
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


//���_�V�F�[�_�[
ShaderOUT VS(float4 pos : POSITION, float4 normal : NORMAL, float2 uv : TEXCOORD0, float4 tangent : TEXCOORD1)
{
	ShaderOUT outData;

	float4 outPos = pos;
		outPos = mul(outPos, matWorld);
	outPos = mul(outPos, matView);
	outPos = mul(outPos, matProj);
	outData.pos = outPos;


	float3 binormal = cross(tangent, normal);
		normal = mul(normal, matRotate);
	tangent = mul(tangent, matRotate);
	binormal = mul(binormal, matRotate);

	float4 worldPos = mul(pos, matWorld);
		float3 eye = normalize(vecCam - worldPos);
		outData.eye.x = dot(eye, tangent);
	outData.eye.y = dot(eye, binormal);
	outData.eye.z = dot(eye, normal);
	outData.eye.w = 0;

	float4 light = vecLightDir;
		light = normalize(light);
	outData.light.x = dot(light, tangent);
	outData.light.y = dot(light, binormal);
	outData.light.z = dot(light, normal);
	outData.light.w = 0;

	outData.uv = uv;

	return outData;
}


//�s�N�Z���V�F�[�_�[�i�e�N�X�`������A�@���}�b�v�Ȃ��j
float4 PS_T(ShaderOUT inShaderData) : COLOR
{
	float3 normal = float3(0, 0, 1);

	if (dot(inShaderData.eye, normal) < 0.30f)
	{
		return float4(0, 0, 0, 1);
	}

	float4 NL = tex2D(SamplerToon, float2(saturate(dot(float4(normal, 0), -inShaderData.light)), 0));

	float4 ref = reflect(inShaderData.light, float4(normal, 0));



	float speculerPower = 2.0f;

	float4 speculer = speculerPower *
		pow(saturate(dot(ref, inShaderData.eye)), speculerSize) * speculerColor;


	float4 color = NL * tex2D(SamplerDecal, inShaderData.uv) + speculer;
		color.a = tex2D(SamplerDecal, inShaderData.uv).a;


	return color;
}

float4 VS_OutLine(float4 pos : POSITION, float4 normal : NORMAL) : SV_POSITION
{
	normal.w = 0;
	float4 outPos = pos + normal * 0.010f;
	outPos = mul(outPos, matWorld);
	outPos = mul(outPos, matView);
	outPos = mul(outPos, matProj);

	return outPos;

}

float4 PS_OutLine(float4 pos : SV_POSITION) : COLOR
{
	return float4(0, 0, 0, 1);
}

technique
{
	//�e�N�X�`������A�@���Ȃ�
	pass
	{
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS_T();
	}

	// �֊s
	pass
	{
		VertexShader = compile vs_3_0 VS_OutLine();
		PixelShader = compile ps_3_0 PS_OutLine();
	}
}