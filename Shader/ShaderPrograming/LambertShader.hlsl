/*
  Visual Studio�ō쐬���A�f�t�H���g�ł̓G���g���|�C���g��
  �wmain�x�ɐݒ肳��Ă���̂ŁA���̊֐��ō쐬����ꍇ��
  ���̊֐����ɐݒ肷��
*/


// �O���[�o���ϐ�
// �s��
float4x4 matWorld, matView, matProj, matRotate;

// �\����
// �ʒu�E�F
// �V�F�[�_�Ŏg�p����̂ŃZ�}���e�B�N�X�ŋL�q����
struct ShaderOUT
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
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

	// ���̃x�N�g��(normalize�Ő��K��)
	float4 light = normalize(float4(-1, 1, -1, 0));

	// ���ς����߂Ċi�[
	// �@���E���C�g�̋t�̃x�N�g��
	shaderData.color = dot(normal, light);

	// ���ς����߂��ۂɃ��l���������Ȃ��Ă��܂�
	// ���̂܂ܔ��f������ƌ�낪�����ɂȂ��Ă��܂��̂�
	// �����I�Ƀ��l��1��ݒ肷��
	shaderData.color.a = 1;

	return shaderData;
}

// �s�N�Z���V�F�[�_�[
// ���_�V�F�[�_�Őݒ肵���\���̂������ɂ���
// �\���̂̐F�̕����݂̂�Ԃ�
float4 PS(ShaderOUT inShaderData) : COLOR
{
	// �ς������F���|���邱�Ƃɂ����
	// �C�ӂ̐F�𔽉f������
	return inShaderData.color * float4(1, 0, 0, 1);
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