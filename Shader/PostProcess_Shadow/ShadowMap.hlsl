// �O���[�o���ϐ�
// �s��
float4x4 matWorld, matView, matProj;

// �\����
// �ʒu�E�@���E�����EUV
// �V�F�[�_�Ŏg�p����̂ŃZ�}���e�B�N�X�ŋL�q����
struct ShaderOUT
{
	float4 pos	 : SV_POSITION;
	float4 world : TEXCOORD1;
};


// ���_�V�F�[�_�[
// ���_�̏��������ɂ��Ă��̕ϐ��ɒ��_���i�[����
// SV_POSITION�ŃX�N���[���̈ʒu��ݒ肷��
// �L�q�@ : �Z�}���e�B�N�X
// �ʒu
ShaderOUT VS(float4 pos : POSITION)
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

	// �ʒu���\���̂Ɋi�[
	shaderData.pos = outPos;
	shaderData.world = outPos;

	return shaderData;
}


// �e�N�X�`���E�@���}�b�v�Ȃ�
// �s�N�Z���V�F�[�_�[
// ���_�V�F�[�_�Őݒ肵���\���̂������ɂ���
// �\���̂̐F�̕����݂̂�Ԃ�
float4 PS(ShaderOUT inShaderData) : COLOR
{

	// �����̌���
	// z: �J��������̋���
	// w: �J������������ő�̋���
	float4 color = inShaderData.world.z / inShaderData.world.w;

	// �����I�ɐݒ�
	color.a = 1;

	return color;
}

// �p�X�̏��Ԃɂ���ĕ`�悪�ς��̂Œ���
technique
{
	pass
	{
		// GPU�̃V�F�[�_�[�̃o�[�W�������w��
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();
	}
}