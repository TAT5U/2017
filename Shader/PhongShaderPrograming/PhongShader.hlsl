
// �O���[�o���ϐ�
// �s��
float4x4 matWorld, matView, matProj, matRotate;
float4 vecCam, vecLightDir;

// �\����
// �ʒu�E�@���E����
// �V�F�[�_�Ŏg�p����̂ŃZ�}���e�B�N�X�ŋL�q����
struct ShaderOUT
{
	float4 pos    : SV_POSITION;
	float4 normal : NORMAL;
	float4 eye    : TEXCOORD1;
};

// ���_�V�F�[�_�[
// ���_�̏��������ɂ��Ă��̕ϐ��ɒ��_���i�[����
// SV_POSITION�ŃX�N���[���̈ʒu��ݒ肷��
// �L�q�@ : �Z�}���e�B�N�X
// �ʒu�E�@��
ShaderOUT VS(float4 pos : POSITION, float4 normal : NORMAL)
{
	// �\����
	ShaderOUT shaderData;

	// �Z�b�g����ϐ�
	// WXYZ or RGBA
	float4 outPos = pos;

	// ���[���h���W
	outPos = mul(outPos, matWorld);

	// �r���[���W
	outPos = mul(outPos, matView);

	// �v���W�F�N�V�������W
	outPos = mul(outPos, matProj);

	// ��]�����f���ꂽ�@����K�p
	normal = mul(normal, matRotate);

	// �ʒu���\���̂Ɋi�[
	shaderData.pos = outPos;

	// �@�����\���̂Ɋi�[
	shaderData.normal = normal;

	// �����I�ɐݒ�
	shaderData.normal.w = 0;

	// ���[���h���W
	float4 worldPos = mul(pos, matWorld);

	// �����𐳋K��
	shaderData.eye = normalize(vecCam - worldPos);

	// �����I�ɐݒ�
	shaderData.eye.w = 0;

	return shaderData;
}

// �s�N�Z���V�F�[�_�[
// ���_�V�F�[�_�Őݒ肵���\���̂������ɂ���
// �\���̂̐F�̕����݂̂�Ԃ�
float4 PS(ShaderOUT inShaderData) : COLOR
{
	// ���̃x�N�g��
	float4 light = vecLightDir;

	// �����I�ɐݒ�
	light.w = 0;

	// ���K��
	light = normalize(light);

	// ���ς����߂Ċi�[
	// �@���E���C�g�̋t�̃x�N�g��
	float4 NL = dot(inShaderData.normal, -light);

	// ���˃x�N�g��
	float4 reflection = reflect(light, inShaderData.normal);

	// �n�C���C�g�̑傫��
	float speculerSize = 3.0f;

	// ���ʔ��˗�
	float speculerPower = 2.0f;

	// �n�C���C�g
	// saturate�œ��ς�؂�l��
	float speculer = speculerPower * pow(saturate(dot(reflection, inShaderData.eye)), speculerSize);

	// ���߂��l��F�ɔ��f
	float4 color = NL * float4(1, 0, 0, 1) + speculer;

	// �����I�ɐݒ�
	color.a = 1;

	return color;
}

technique
{
	pass
	{
		// GPU�̃V�F�[�_�[�̃o�[�W�������w��
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();
	}
}
