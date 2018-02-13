// グローバル変数
// 行列
float4x4 matWorld, matView, matProj, matRotate;
float4 vecCam, vecLightDir, speculerColor, diffuseColor;
float speculerSize;
texture texDecal, texToon;


// テクスチャの設定
// ニアレストレイバー(最も近いピクセルの色にする)
// 速度は速いが、ジャギーが発生する
// バイリニア補完(平均色にする)
// 滑らかにしてソフトにする
sampler SamplerDecal = sampler_state
{
	Texture = <texDecal>;

	// ニアレストレイバー = LINEAR
	// バイリニア補完     = POINT
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

sampler SamplerToon = sampler_state
{
	Texture = <texToon>;

	// ニアレストレイバー = LINEAR
	// バイリニア補完     = POINT
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

// 構造体
// 位置・法線・視線・UV
// シェーダで使用するのでセマンティクスで記述する
struct ShaderOUT
{
	float4 pos    : SV_POSITION;
	//float4 normal : NORMAL;
	float4 eye    : TEXCOORD1;
	float2 uv	  : TEXCOORD0;
	float4 light  : TEXCOORD2;
};


//頂点シェーダー
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


//ピクセルシェーダー（テクスチャあり、法線マップなし）
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
	//テクスチャあり、法線なし
	pass
	{
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS_T();
	}

	// 輪郭
	pass
	{
		VertexShader = compile vs_3_0 VS_OutLine();
		PixelShader = compile ps_3_0 PS_OutLine();
	}
}