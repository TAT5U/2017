class judge
{
public:
	//�R���X�g���N�^
	judge();

	//�f�X�g���N�^
	~judge();

	//�W�����P���̔���
	void Judgement(int pl1,int pl2);

	//�ŏI���ʂ̔���
	void WinnerJudge();

	//�Q�[���i�s
	void Disp();
private:

	//�������𐔂���ϐ�
	int i;

	//�v���C���[1�̎���i�[����ϐ�
	int p1;

	//�v���C���[2�̎���i�[����ϐ�
	int p2;
};