// グローバル変数
// 行列
float4x4 matWorld, matView, matProj;

// 構造体
// 位置・法線・視線・UV
// シェーダで使用するのでセマンティクスで記述する
struct ShaderOUT
{
	float4 pos	 : SV_POSITION;
	float4 world : TEXCOORD1;
};


// 頂点シェーダー
// 頂点の情報を引数にしてその変数に頂点を格納する
// SV_POSITIONでスクリーンの位置を設定する
// 記述法 : セマンティクス
// 位置
ShaderOUT VS(float4 pos : POSITION)
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

	// 位置を構造体に格納
	shaderData.pos = outPos;
	shaderData.world = outPos;

	return shaderData;
}


// テクスチャ・法線マップなし
// ピクセルシェーダー
// 頂点シェーダで設定した構造体を引数にして
// 構造体の色の部分のみを返す
float4 PS(ShaderOUT inShaderData) : COLOR
{

	// 距離の公式
	// z: カメラからの距離
	// w: カメラが見える最大の距離
	float4 color = inShaderData.world.z / inShaderData.world.w;

	// 強制的に設定
	color.a = 1;

	return color;
}

// パスの順番によって描画が変わるので注意
technique
{
	pass
	{
		// GPUのシェーダーのバージョンを指定
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();
	}
}