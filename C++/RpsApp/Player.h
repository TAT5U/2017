class player
{
public:
	//�R���X�g���N�^
	player();

	//�f�X�g���N�^
	~player();

	//����o��
	int showHand();

	//�������񐔂𓚂���
	int getWinCount();

	//�R�����猋�ʂ��󂯎��
	void notifyResult(bool result);
private:

	//�������𐔂���ϐ�
	int winCount;

	//����i�[����ϐ�
	int n;

	//�[�����������֐�
	int GetRnd(int min, int max);
};