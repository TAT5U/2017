// グローバル変数
// 行列
float4x4 matWorld, matView, matProj, matRotate;
float4 vecCam, vecLightDir, speculerColor, diffuseColor;
float speculerSize, uvScroll;
texture texDecal, texNormal;

//
float4x4 matLightView, matUV;
texture texShadowMap;


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
	AddressU = WRAP;
	AddressV = WRAP;
};

//ノーマルテクスチャの設定
sampler SamplerNormal = sampler_state
{
	Texture = <texNormal>;

	// ニアレストレイバー = LINEAR
	// バイリニア補完     = POINT
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};


//
sampler SamplerShadowMap = sampler_state
{
	Texture = <texShadowMap>;

	// ニアレストレイバー = LINEAR
	// バイリニア補完     = POINT
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
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



	//
	float4 lightTexCoord : TEXCOORD5;
	float4 lightViewPos  : TEXCOORD6;
};


// 頂点シェーダー
// 頂点の情報を引数にしてその変数に頂点を格納する
// SV_POSITIONでスクリーンの位置を設定する
// 記述法 : セマンティクス
// 位置・法線・UV・タンジェント
ShaderOUT VS(float4 pos : POSITION, float4 normal : NORMAL, float2 uv : TEXCOORD0, float4 tangent : TEXCOORD1)
{
	// 構造体
	ShaderOUT shaderData;

	// セットする変数
	// WXYZ or RGBA
	float4 outPos = pos;

	// 各座標をセットする
	outPos = mul(outPos, matWorld);
	outPos = mul(outPos, matView);
	outPos = mul(outPos, matProj);

	float3 biNormal = cross(tangent, normal);
	normal = mul(normal, matRotate);
	tangent = mul(tangent, matRotate);

	// float3をfloat4で使用する場合は
	// キャストした際にwの値を0にして初期化を行う
	biNormal = mul(float4(biNormal, 0), matRotate);

	// 強制的に設定
	normal.w = 0;
	tangent.w = 0;

	// 位置を構造体に格納
	shaderData.pos = outPos;

	// 法線を構造体に格納
	//shaderData.normal = normal;

	// 強制的に設定
	//shaderData.normal.w = 0;

	// ワールド座標
	float4 worldPos = mul(pos, matWorld);

	// 向きを正規化
	//shaderData.eye = normalize(vecCam - worldPos);

	// 斜めから見たときの視線ベクトルを設定
	float4 eye = normalize(vecCam - worldPos);
	shaderData.eye.x = dot(eye, tangent);
	shaderData.eye.y = dot(eye, biNormal);
	shaderData.eye.z = dot(eye, normal);
	shaderData.eye.w = 0;

	// 光のベクトル
	float4 light = vecLightDir;

	// 強制的に設定
	light.w = 0;

	// 正規化
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


// テクスチャ・法線マップあり
float4 PS_TextureNormal(ShaderOUT inShaderData) : COLOR
{
	float4 normal = (tex2D(SamplerNormal, inShaderData.uv)*2.0f - 1.0f
		+ tex2D(SamplerNormal, inShaderData.uv*1.2f - uvScroll) * 2.0f - 1.0f) / 2;

	normal.w = 0;

	// 内積を求めて格納
	// 法線・ライトの逆のベクトル
	float4 NL = saturate(dot(normal, -inShaderData.light));

	// 反射ベクトル
	float4 reflection = reflect(inShaderData.light, normal);

	// 鏡面反射率
	float speculerPower = 20.0f;

	// ハイライト
	// saturateで内積を切り詰め
	float speculer = speculerPower * pow(saturate(dot(reflection, inShaderData.eye)), 2);

	float4 ambient = float4(0.1, 0.1, 0.3, 1);

	// 求めた値をテクスチャに反映
	float4 color = NL * tex2D(SamplerDecal, inShaderData.uv) + speculer + ambient;

	// 強制的に設定
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


// パスの順番によって描画が変わるので注意
technique
{
	pass
	{
		// GPUのシェーダーのバージョンを指定
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS_TextureNormal();
	}
}
