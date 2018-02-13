
// グローバル変数
// 行列
float4x4 matWorld, matView, matProj, matRotate;
float4 vecCam, vecLightDir;

// 構造体
// 位置・法線・視線
// シェーダで使用するのでセマンティクスで記述する
struct ShaderOUT
{
	float4 pos    : SV_POSITION;
	float4 normal : NORMAL;
	float4 eye    : TEXCOORD1;
};

// 頂点シェーダー
// 頂点の情報を引数にしてその変数に頂点を格納する
// SV_POSITIONでスクリーンの位置を設定する
// 記述法 : セマンティクス
// 位置・法線
ShaderOUT VS(float4 pos : POSITION, float4 normal : NORMAL)
{
	// 構造体
	ShaderOUT shaderData;

	// セットする変数
	// WXYZ or RGBA
	float4 outPos = pos;

	// ワールド座標
	outPos = mul(outPos, matWorld);

	// ビュー座標
	outPos = mul(outPos, matView);

	// プロジェクション座標
	outPos = mul(outPos, matProj);

	// 回転が反映された法線を適用
	normal = mul(normal, matRotate);

	// 位置を構造体に格納
	shaderData.pos = outPos;

	// 法線を構造体に格納
	shaderData.normal = normal;

	// 強制的に設定
	shaderData.normal.w = 0;

	// ワールド座標
	float4 worldPos = mul(pos, matWorld);

	// 向きを正規化
	shaderData.eye = normalize(vecCam - worldPos);

	// 強制的に設定
	shaderData.eye.w = 0;

	return shaderData;
}

// ピクセルシェーダー
// 頂点シェーダで設定した構造体を引数にして
// 構造体の色の部分のみを返す
float4 PS(ShaderOUT inShaderData) : COLOR
{
	// 光のベクトル
	float4 light = vecLightDir;

	// 強制的に設定
	light.w = 0;

	// 正規化
	light = normalize(light);

	// 内積を求めて格納
	// 法線・ライトの逆のベクトル
	float4 NL = dot(inShaderData.normal, -light);

	// 反射ベクトル
	float4 reflection = reflect(light, inShaderData.normal);

	// ハイライトの大きさ
	float speculerSize = 3.0f;

	// 鏡面反射率
	float speculerPower = 2.0f;

	// ハイライト
	// saturateで内積を切り詰め
	float speculer = speculerPower * pow(saturate(dot(reflection, inShaderData.eye)), speculerSize);

	// 求めた値を色に反映
	float4 color = NL * float4(1, 0, 0, 1) + speculer;

	// 強制的に設定
	color.a = 1;

	return color;
}

technique
{
	pass
	{
		// GPUのシェーダーのバージョンを指定
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();
	}
}
