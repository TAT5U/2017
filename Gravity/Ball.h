#include "constants.h"

// 重複防止
#ifndef _BALL_H_
#define	_BALL_H_


class Ball{
private:
	int _x;					// 中心位置 x座標
	int _y;					// 中心位置 y座標
	int _dx;				// 移動方向 x方向
	int _dy;				// 移動方向 y方向
	int _speed;				// 速度( 移動量 )
	int _radius;				// 半径
	int height;
	int prev;
	bool isBounce;
	float t;
	
public:
	Ball();																// コンストラクタ
	~Ball();															// デストラクタ

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

	void Init( int x, int y, int dx, int dy, int speed, int radius );	// 初期化処理
	void Update();														// 更新処理
	void Draw( HDC hdc );												// 描画処理
	void Move();														// 移動処理

	void Bounce(int fall);
};


#endif // !_BALL_H_
