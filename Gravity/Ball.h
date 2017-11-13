#include "constants.h"

// �d���h�~
#ifndef _BALL_H_
#define	_BALL_H_


class Ball{
private:
	int _x;					// ���S�ʒu x���W
	int _y;					// ���S�ʒu y���W
	int _dx;				// �ړ����� x����
	int _dy;				// �ړ����� y����
	int _speed;				// ���x( �ړ��� )
	int _radius;				// ���a
	int height;
	int prev;
	bool isBounce;
	float t;
	
public:
	Ball();																// �R���X�g���N�^
	~Ball();															// �f�X�g���N�^

	// setter
	void SetX( int x );
	void SetY( int y );
	void SetDx( int dx );
	void SetDy( int dy );
	void SetSpeed(float speed);
	void SetRadius( int radius );
	void SetPosition( int x, int y );
	void SetDirection( int dx, int dy );

	// getter
	int GetX();
	int GetY();
	int GetTop();
	int GetBottom();
	int GetLeft();
	int GetRight();
	RECT GetRect();
	int GetDx();
	int GetDy();
	float GetSpeed();
	int GetRadius();
	void GetRect( RECT* rect );

	void Init( int x, int y, int dx, int dy, int speed, int radius );	// ����������
	void Update();														// �X�V����
	void Draw( HDC hdc );												// �`�揈��
	void Move();														// �ړ�����

	void Bounce(int fall);
};


#endif // !_BALL_H_
