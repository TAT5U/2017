////グローバル変数
////const とおなじ扱い
//float4x4 matWorld;				//ワールド行列
//float4x4 matView;				//ビュー行列
//float4x4 matProj;				//プロジェクション行列
//float4x4 matRotate;				//回転行列
//float3 vecCam;					//カメラの位置(視点)
//float3 vecLightDir;				//ライトの向き
//texture texDecal;				//テクスチャ
//texture texNormal;				//ノーマルテクスチャ
//float4 speculerColor;			//Mayaに入っているハイライトの情報
//float speculerSize;				//ハイライトの大きさ
//float4 diffuseColor;
//textureCUBE texCube;			//パノラマ画像を入れる変数
//
////テクスチャの貼り方の設定
//sampler SamplerDecal = sampler_state
//{
//	Texture = <texDecal>;		//どのテクスチャに貼るのか
//	//バイリニア補完(隣同士のピクセルの平均を取ってジャギらなくする)
//	//LINEARではなくPOINTにするとニアレストネイバー
//	//普通はLINEAR
//	MipFilter = LINEAR;
//	MinFilter = LINEAR;
//	MagFilter = LINEAR;
//};
////ノーマルテクスチャの設定
//sampler SamplerNormal = sampler_state
//{
//	Texture = <texNormal>;		//どのテクスチャに貼るのか
//	//バイリニア補完(隣同士のピクセルの平均を取ってジャギらなくする)
//	//LINEARではなくPOINTにするとニアレストネイバー
//	//普通はLINEAR
//	MipFilter = LINEAR;
//	MinFilter = LINEAR;
//	MagFilter = LINEAR;
//};
////Cube
//sampler SamplerCube = sampler_state
//{
//	Texture = <texCube>;		//どのテクスチャに貼るのか
//	MipFilter = LINEAR;
//	MinFilter = LINEAR;
//	MagFilter = LINEAR;
//};
////頂点シェーダの構造体
//struct ShaderOUT
//{
//	float4 pos : SV_POSITION;					//位置
//	//float4 normal : NORMAL;						//法線情報
//	//TEXCOORDはセマンティクスがないときに使う
//	float4 eye : TEXCOORD1;						//視線ベクトル
//	float2 uv : TEXCOORD0;						//uv情報
//	float4 light:TEXCOORD2;						//ライトのベクトル
//};
//
//
////頂点シェーダー
////各頂点が画面のどこに来るのか
////引数：頂点の情報(位置・法線・UV座標・色etc..)
////戻り値：頂点の位置
////float4:float型４つをまとめたもの
//ShaderOUT VS(float4 pos:POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD0, float3 tangent : TEXCOORD1)	//セマンティクス(左側にある変数がなにをあらわすか)
//{
//	ShaderOUT outData;
//	float4 outPos = pos;
//		outPos = mul(outPos, matWorld);						//ローカル座標にワールド行列をかけるのでワールド行列が代入される
//	outPos = mul(outPos, matView);							//ワールドビュー行列をかける
//	outPos = mul(outPos, matProj);							//プロジェクション行列をかける
//	outData.pos = outPos;
//
//	float3 binormal = cross(tangent, normal);			//接線と法線の外積から従法線を求める
//		////ベクトルを正規化(ベクトルの長さを1にする)
//		//light = normalize(light);
//		normal = mul(float4(normal, 0), matRotate);			//法線をまわすため、回転行列をかける
//
//	tangent = mul(float4(tangent, 0), matRotate);
//	binormal = mul(float4(binormal, 0), matRotate);
//	////outData.color = dot(normal, light);					//法線と光ベクトルの内積を代入
//	////outData.color.a = 1;
//
//	float4 worldPos = mul(pos, matWorld);					//頂点の位置を取得
//		//視線ベクトルを求める
//		//向きだけ必要なので正規化する
//		float3 eye = normalize(float4(vecCam, 0) - worldPos);	//見る位置-見る頂点の位置=視線ベクトル
//		outData.eye.x = dot(eye, tangent);
//	outData.eye.y = dot(eye, binormal);
//	outData.eye.z = dot(eye, normal);
//	outData.eye.w = 0;
//
//	//float4 light = float4(1, -1, 1, 0);					//光の向き(左上手前から光が来る)
//	float4 light = float4(vecLightDir, 0);					//ライトの向き
//		//ベクトルを正規化(ベクトルの長さを1にする)
//		light = normalize(light);
//
//	outData.light.x = dot(light, tangent);
//	outData.light.y = dot(light, binormal);
//	outData.light.z = dot(light, normal);
//	outData.light.w = 0;
//
//
//	outData.uv = uv;										//ピクセルシェーダーにuvがそのまま渡される
//
//	return outData;
//}
//
////法線//////////////////////////////////////
////float4 VS(float4 nor:NORMAL):SV_NORMAL
//
//
//
////ピクセルシェーダー(法線マップなし
////ピクセルごとに何色にするか
////色はRGBAであらわす
////引数：頂点シェーダーの戻り値(各頂点が画面上のどこにあるか)
////戻り値：各ピクセルの色
//float4 PS(ShaderOUT inShaderData) : COLOR
//{
//
//
//	float3 normal = float3(0, 0, 1);			//法線の変数
//
//	//反射ベクトルを求める
//	//法線とライトの内積を求める
//	float4 NL = saturate(dot(float4(normal, 0), -inShaderData.light));
//	//この式で反射ベクトルが求まる
//	//反射ベクトル=2*法線とベクトルの内積*法線-ベクトル
//	//float4 refrect = normalize(2 * NL * inShaderData.normal - light);
//	//反射ベクトルを求める関数
//	float4 ref = reflect(inShaderData.light, float4(normal, 0));
//	//ハイライトのサイズ
//	float speculerPower = 1.0f;								//ハイライトの強さ(鏡面反射率)
//
//
//	//ハイライト=鏡面反射率*光の強さ*(反射ベクトル・視線)^サイズ
//	//saturateは内積を求めるときつけておいたほうがよい(0～1に切り詰めるため)
//	float4 speculer = speculerPower * pow(saturate(dot(ref, inShaderData.eye)), speculerSize)*speculerColor;
//		//テクスチャを貼る
//		float4 color = NL * diffuseColor + speculer;										//法線と光ベクトルの内積を代入
//		color.a = 1;
//
//	return color;		//ハイライトを足して返す
//}
////ピクセルシェーダー(法線マップあり
////ピクセルごとに何色にするか
////色はRGBAであらわす
////引数：頂点シェーダーの戻り値(各頂点が画面上のどこにあるか)
////戻り値：各ピクセルの色
//float4 PS_N(ShaderOUT inShaderData) : COLOR
//{
//
//
//	float3 normal = tex2D(SamplerNormal, inShaderData.uv)*2.0f - 1.0f;			//法線の変数
//
//	//反射ベクトルを求める
//	//法線とライトの内積を求める
//	float4 NL = saturate(dot(float4(normal, 0), -inShaderData.light));
//	//この式で反射ベクトルが求まる
//	//反射ベクトル=2*法線とベクトルの内積*法線-ベクトル
//	//float4 refrect = normalize(2 * NL * inShaderData.normal - light);
//	//反射ベクトルを求める関数
//	float4 ref = reflect(inShaderData.light, float4(normal, 0));
//	//ハイライトのサイズ
//	float speculerPower = 1.0f;								//ハイライトの強さ(鏡面反射率)
//
//
//	//ハイライト=鏡面反射率*光の強さ*(反射ベクトル・視線)^サイズ
//	//saturateは内積を求めるときつけておいたほうがよい(0～1に切り詰めるため)
//	float4 speculer = speculerPower * pow(saturate(dot(ref, inShaderData.eye)), speculerSize)*speculerColor;
//		//テクスチャを貼る
//		float4 color = NL * diffuseColor + speculer;										//法線と光ベクトルの内積を代入
//		color.a = 1;
//
//	return color;		//ハイライトを足して返す
//}
//
////ピクセルシェーダー(法線マップなし
////ピクセルごとに何色にするか
////色はRGBAであらわす
////引数：頂点シェーダーの戻り値(各頂点が画面上のどこにあるか)
////戻り値：各ピクセルの色
//float4 PS_T(ShaderOUT inShaderData) : COLOR
//{
//
//	//tex2dはそのテクスチャの色を取得できる
//	float3 normal = float3(0, 0, 1);			//法線の変数
//
//	//反射ベクトルを求める
//	//法線とライトの内積を求める
//	float4 NL = saturate(dot(float4(normal, 0), -inShaderData.light));
//	//この式で反射ベクトルが求まる
//	//反射ベクトル=2*法線とベクトルの内積*法線-ベクトル
//	//float4 refrect = normalize(2 * NL * inShaderData.normal - light);
//	//反射ベクトルを求める関数
//	float4 ref = reflect(inShaderData.light, float4(normal, 0));
//	//ハイライトのサイズ
//	float speculerPower = 1.0f;								//ハイライトの強さ(鏡面反射率)
//
//
//	//ハイライト=鏡面反射率*光の強さ*(反射ベクトル・視線)^サイズ
//	//saturateは内積を求めるときつけておいたほうがよい(0～1に切り詰めるため)
//	float4 speculer = speculerPower * pow(saturate(dot(ref, inShaderData.eye)), speculerSize)*speculerColor;
//		//テクスチャを貼る
//		float4 color = NL * (tex2D(SamplerDecal, inShaderData.uv) + speculer);										//法線と光ベクトルの内積を代入
//		color.a = tex2D(SamplerDecal, inShaderData.uv).a;
//
//	return color;		//ハイライトを足して返す
//}
//
////ピクセルシェーダー(法線マップあり
////ピクセルごとに何色にするか
////色はRGBAであらわす
////引数：頂点シェーダーの戻り値(各頂点が画面上のどこにあるか)
////戻り値：各ピクセルの色
//float4 PS_T_N(ShaderOUT inShaderData) : COLOR
//{
//
//	//tex2dはそのテクスチャの色を取得できる
//	float3 normal = tex2D(SamplerNormal, inShaderData.uv)*2.0f - 1.0f;			//法線の変数
//
//	//反射ベクトルを求める
//	//法線とライトの内積を求める
//	float4 NL = saturate(dot(float4(normal, 0), -inShaderData.light));
//
//	//視線の反射ベクトルを求める
//	float3 refEye = reflect(inShaderData.eye, normal);
//
//	//この式で反射ベクトルが求まる
//	//反射ベクトル=2*法線とベクトルの内積*法線-ベクトル
//	//float4 refrect = normalize(2 * NL * inShaderData.normal - light);
//	//反射ベクトルを求める関数
//	float4 ref = reflect(inShaderData.light, float4(normal, 0));
//	//ハイライトのサイズ
//	float speculerPower = 1.0f;								//ハイライトの強さ(鏡面反射率)
//
//
//	//ハイライト=鏡面反射率*光の強さ*(反射ベクトル・視線)^サイズ
//	//saturateは内積を求めるときつけておいたほうがよい(0～1に切り詰めるため)
//	float4 speculer = speculerPower * pow(saturate(dot(ref, inShaderData.eye)), speculerSize)*speculerColor;
//	////テクスチャを貼る
//	float4 color = NL * (tex2D(SamplerDecal, inShaderData.uv) + speculer) + texCUBE(SamplerCube, refEye)*0.5;										//法線と光ベクトルの内積を代入
//	//float4 color=texCUBE(SamplerCube,refEye);
//		color.a = tex2D(SamplerDecal, inShaderData.uv).a;
//
//	return color;		//ハイライトを足して返す
//}
//
//technique
//{
//	pass
//	{
//		//頂点シェーダーのバージョン3.0でコンパイル
//		VertexShader = compile vs_3_0 VS();
//		//ピクセルシェーダーのバージョン3.0でコンパイル
//		PixelShader = compile ps_3_0 PS();
//	}
//
//	pass
//	{
//		//頂点シェーダーのバージョン3.0でコンパイル
//		VertexShader = compile vs_3_0 VS();
//		//ピクセルシェーダーのバージョン3.0でコンパイル
//		PixelShader = compile ps_3_0 PS_T();
//	}
//	pass
//	{
//		//頂点シェーダーのバージョン3.0でコンパイル
//		VertexShader = compile vs_3_0 VS();
//		//ピクセルシェーダーのバージョン3.0でコンパイル
//		PixelShader = compile ps_3_0 PS_N();
//	}
//
//	pass
//	{
//		//頂点シェーダーのバージョン3.0でコンパイル
//		VertexShader = compile vs_3_0 VS();
//		//ピクセルシェーダーのバージョン3.0でコンパイル
//		PixelShader = compile ps_3_0 PS_T_N();
//	}
//}


// グローバル変数
// 行列
float4x4 matWorld, matView, matProj, matRotate;
float4 vecCam, vecLightDir, speculerColor, diffuseColor;
float speculerSize;
texture texDecal, texNormal;

// パノラマ画像
textureCUBE texCube;


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

//パノラマの設定
sampler SamplerCube = sampler_state
{
	// ニアレストレイバー = LINEAR
	// バイリニア補完     = POINT
	Texture = <texCube>;
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

	return shaderData;
}


// テクスチャ・法線マップなし
// ピクセルシェーダー
// 頂点シェーダで設定した構造体を引数にして
// 構造体の色の部分のみを返す
float4 PS(ShaderOUT inShaderData) : COLOR
{
	float4 normal = float4(0, 0, 1, 0);

	// 内積を求めて格納
	// 法線・ライトの逆のベクトル
	float4 NL = saturate(dot(normal, -inShaderData.light));

	// 反射ベクトル
	float4 reflection = reflect(inShaderData.light, normal);

	// 鏡面反射率
	float speculerPower = 1.0f;

	// ハイライト
	// saturateで内積を切り詰め
	float4 speculer = speculerPower * pow(saturate(dot(reflection, inShaderData.eye)), speculerSize) * speculerColor;

	// 求めた値をテクスチャに反映
	float4 color = NL * diffuseColor + speculer;

	// 強制的に設定
	color.a = 1;

	return color;
}

// テクスチャあり・法線マップなし
float4 PS_Texture(ShaderOUT inShaderData) : COLOR
{
	float4 normal = float4(0, 0, 1, 0);

	// 内積を求めて格納
	// 法線・ライトの逆のベクトル
	float4 NL = saturate(dot(normal, -inShaderData.light));

	// 反射ベクトル
	float4 reflection = reflect(inShaderData.light, normal);

	// 鏡面反射率
	float speculerPower = 1.0f;

	// ハイライト
	// saturateで内積を切り詰め
	float4 speculer = speculerPower * pow(saturate(dot(reflection, inShaderData.eye)), speculerSize) * speculerColor;

	// 求めた値をテクスチャに反映
	float4 color = NL * tex2D(SamplerDecal, inShaderData.uv) + speculer;

	// 強制的に設定
	color.a = tex2D(SamplerDecal, inShaderData.uv).a;

	return color;
}

// テクスチャなし・法線マップあり
float4 PS_Normal(ShaderOUT inShaderData) : COLOR
{
	float4 normal = tex2D(SamplerNormal, inShaderData.uv)*2.0f - 1.0f;
	normal.w = 0;

	// 内積を求めて格納
	// 法線・ライトの逆のベクトル
	float4 NL = saturate(dot(normal, -inShaderData.light));

	// 反射ベクトル
	float4 reflection = reflect(inShaderData.light, normal);

	// 鏡面反射率
	float speculerPower = 1.0f;

	// ハイライト
	// saturateで内積を切り詰め
	float4 speculer = speculerPower * pow(saturate(dot(reflection, inShaderData.eye)), speculerSize) * speculerColor;

	// 求めた値をテクスチャに反映
	float4 color = NL * diffuseColor + speculer;

	// 強制的に設定
	color.a = 1;

	return color;
}

// テクスチャ・法線マップあり
float4 PS_TextureNormal(ShaderOUT inShaderData) : COLOR
{
	float4 normal = tex2D(SamplerNormal, inShaderData.uv)*2.0f - 1.0f;
	normal.w = 0;

	// 内積を求めて格納
	// 法線・ライトの逆のベクトル
	float4 NL = saturate(dot(normal, -inShaderData.light));

	// 反射ベクトル
	float4 reflectionEye = reflect(inShaderData.eye, normal);
	reflectionEye.w = 0;
	float4 reflection = reflect(inShaderData.light, normal);

	// 鏡面反射率
	float speculerPower = 1.0f;

	// ハイライト
	// saturateで内積を切り詰め
	float4 speculer = speculerPower * pow(saturate(dot(reflection, inShaderData.eye)), speculerSize) * speculerColor;

	// 求めた値をテクスチャに反映
	float4 color = NL * (tex2D(SamplerDecal, inShaderData.uv) + speculer) + texCUBE(SamplerCube, reflectionEye) * 0.5;

	// 強制的に設定
	color.a = tex2D(SamplerDecal, inShaderData.uv).a;

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

	pass
	{
		// GPUのシェーダーのバージョンを指定
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS_Texture();
	}
	pass
	{
		// GPUのシェーダーのバージョンを指定
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS_Normal();
	}

	pass
	{
		// GPUのシェーダーのバージョンを指定
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS_TextureNormal();
	}
}
