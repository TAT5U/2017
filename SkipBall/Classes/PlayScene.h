/*PlayScene.h*/

#pragma once
#include "cocos2d.h"
#include "PhysicsShapeCache.h"

using namespace std;
USING_NS_CC;

//���ʎq�̒�`
enum  class PhysicName
{
	Goal = 1,
	Ball = 2,
};
class PlayScene : public Layer
{
public:
	PlayScene();
	~PlayScene();
	virtual bool init();
	void update(float dt) override;
	void input();

	//�X�v���C�g �X�e�[�W�E�{�[���E�S�[���E�t�F�C�N
	Sprite *Stage, *Ball, *Goal,*Fake1,*Fake2,*Fake3,*bk;

	//���x�� ��������
	Label *timelbl;

	//float�^ ���ԁE�Q�[���J�n����
	float time,dtime;

	//�����G���W�� �{�[���E�S�[���E�X�e�[�W�E�t�F�C�N
	PhysicsBody *BallPhysic,*GoalPhysic,*StagePhysic, *Fake1Physic, *Fake2Physic, *Fake3Physic;

	//PhysicsShapeCache�̓v���p�e�B���X�g�Ɋi�[����Ă���f�[�^���g���ĕ����G���W����
	//�摜�Ɏ��t���Ă����PhysicsShapeCache�N���X�ɂ���
	//PhysicsShapeCache �X�e�[�W�E�S�[���E�t�F�C�N
	PhysicsShapeCache *StageShape, *GoalShape, *Fake1Shape, *Fake2Shape, *Fake3Shape;

	//�I�u�W�F�N�g�̏Փ˔͈� �{�[��
	Rect BallRect;

	//�ʒu �N���b�N���E�{�[��
	Vec2 TouchPos, BallPos;

	//�m�[�h �{�[�����΂�����
	Node *BallNode;

	//int�^ �X�e�[�W�ԍ��E�{�X�X�e�[�W�J�E���g�E�Փˎ��̎���
	int StageNum,BossCnt,ContactTime;

	//string�^ �X�e�[�W��
	string StageName;

	//bool�^ �t���O
	bool fakeflg, scheduleflg,contactflg, TouchFlg, delayflg;

	//�}�E�X�C�x���g
	EventListenerTouchOneByOne *listener;
	EventListenerPhysicsContact *physicsContact;

	//�����蔻��C�x���g
	EventListenerPhysicsContact *contact;

	//�V�[���ڍs
	TransitionFade *trans;

	//�E�B���h�E�T�C�Y
	Size DisplaySize;

	static Scene* createScene();
	CREATE_FUNC(PlayScene);
};