texture tex;

sampler SamplerDecal = sampler_state
{
	Texture = <tex>;
};

struct ShaderOUT
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;

};


//���_�V�F�[�_
ShaderOUT VS(float4 pos : POSITION, float2 uv : TEXCOORD0)
{
	ShaderOUT shaderData;
	shaderData.pos = pos;
	shaderData.uv = uv;
	return shaderData;

}

//�s�N�Z���V�F�[�_
float4 PS(ShaderOUT inShaderData) : COLOR
{
	float4 color = float4(0, 0, 0, 0);
	int count = 0;


	for (float x = -10; x <= 10; x++)
	{
		for (float y = 0; y <= 10; y++)
		{
			color += tex2D(SamplerDecal, float2(inShaderData.uv.x + x / 800, inShaderData.uv.y + y / 600));
			count++;
		}
	}
	color /= count;

	//tex2D���̃s�N�Z���̐F
	/*color = (tex2D(SamplerDecal, inData.uv)
	+ tex2D(SamplerDecal, float2(inData.uv.x + 1.0 /60,inData.uv.y))
	+ tex2D(SamplerDecal, float2(inData.uv.x - 1.0 / 60, inData.uv.y))
	+ tex2D(SamplerDecal, float2(inData.uv.x , inData.uv.y + 1.0 /30))
	+ tex2D(SamplerDecal, float2(inData.uv.x , inData.uv.y - 1.0 /30)))/5;*/
	return color;

}


technique
{
	pass
	{
		//���_�V�F�[�_�[�̃o�[�W����3.0�ŃR���p�C��
		VertexShader = compile vs_3_0 VS();
		//�s�N�Z���V�F�[�_�[�̃o�[�W����3.0�ŃR���p�C��
		PixelShader = compile ps_3_0 PS();
	}
};