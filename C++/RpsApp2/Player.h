#include<string>
using namespace std;
class player
{
public:
	//�����t���R���X�g���N�^
	//�v���C���[�̖��O�ݒ�
	player(string _name);

	//�f�X�g���N�^
	~player();

	//����o��
	int showHand();

	//�������񐔂𓚂���
	int getWinCount();

	//�R�����猋�ʂ��󂯎��
	void notifyResult(bool result);

	string getName();
private:

	//�������𐔂���ϐ�
	int winCount;

	//����i�[����ϐ�
	int n;

	//�[�����������֐�
	int GetRnd(int min, int max);

	string name;
};