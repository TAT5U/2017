/*
  Visual Studioで作成時、デフォルトではエントリポイントが
  『main』に設定されているので、他の関数で作成する場合は
  その関数名に設定する
*/


// グローバル変数
// 行列
float4x4 matWorld, matView, matProj, matRotate;

// 構造体
// 位置・色
// シェーダで使用するのでセマンティクスで記述する
struct ShaderOUT
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
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

	// 光のベクトル(normalizeで正規化)
	float4 light = normalize(float4(-1, 1, -1, 0));

	// 内積を求めて格納
	// 法線・ライトの逆のベクトル
	shaderData.color = dot(normal, light);

	// 内積を求めた際にα値も小さくなってしまう
	// そのまま反映させると後ろが透明になってしまうので
	// 強制的にα値に1を設定する
	shaderData.color.a = 1;

	return shaderData;
}

// ピクセルシェーダー
// 頂点シェーダで設定した構造体を引数にして
// 構造体の色の部分のみを返す
float4 PS(ShaderOUT inShaderData) : COLOR
{
	// 変えたい色を掛けることによって
	// 任意の色を反映させる
	return inShaderData.color * float4(1, 0, 0, 1);
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